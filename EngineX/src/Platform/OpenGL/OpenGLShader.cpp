#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace EngineX
{

    static uint32_t OpenGLShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        EX_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        std::string source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);

        // Extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);

        ExtractUniforms(source);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
            : m_Name(name)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);

        ExtractUniforms(vertexSrc);
        ExtractUniforms(fragmentSrc);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            EX_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<uint32_t, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<uint32_t, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            // eol - end of line
            // \r - return
            // \n - new line
            size_t eol = source.find_first_of("\r\n", pos);
            EX_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            EX_CORE_ASSERT(OpenGLShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[OpenGLShaderTypeFromString(type)] =
                    source.substr(
                            nextLinePos,
                            pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
                    );
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<uint32_t, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        EX_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
        std::array<uint32_t, 2> glShaderIDs;
        int glShaderIDIndex = 0;
        for (auto& kv : shaderSources)
        {
            uint32_t type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, nullptr);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                EX_CORE_ERROR("{0}", infoLog.data());
                EX_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        m_RendererID = program;

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);

            for (auto id : glShaderIDs)
                glDeleteShader(id);

            EX_CORE_ERROR("{0}", infoLog.data());
            EX_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto id : glShaderIDs)
            glDetachShader(program, id);
    }

    void OpenGLShader::ExtractUniforms(const std::string& source)
    {
        // todo: improve to extract struct members in shader
//        std::string uniformToken = "uniform";
//        size_t lastPos = 0;
//        while (lastPos != std::string::npos) {
//            size_t uniformTokenPos = source.find(uniformToken, lastPos);
//            size_t eof = source.find_first_of("\r\n", uniformTokenPos);
//            lastPos = eof;
//
//            if (uniformTokenPos == std::string::npos) break;
//
//            std::string line = source.substr(uniformTokenPos, eof - uniformTokenPos);
//            size_t spaceFromEndPos = line.find_last_of(' ');
//            size_t semicolonPos = line.find_last_of(';');
//
//            std::string uniformName = line.substr(spaceFromEndPos + 1, semicolonPos - spaceFromEndPos - 1);
//            int uniformLocation = glGetUniformLocation(m_RendererID, uniformName.c_str());
//            EX_CORE_ASSERT(uniformLocation != -1, "Failed to extract uniform location: " + uniformName + " of " + m_Name);
//            uniforms[uniformName] = uniformLocation;
//        }
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    Ref<OpenGLShader> OpenGLShader::Create(const std::string& filepath)
    {
        return std::make_shared<OpenGLShader>(filepath);
    }

    Ref<OpenGLShader> OpenGLShader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value)
    {
        glUniform1i(GetLocation(name), value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
    {
        glUniform1f(GetLocation(name), value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        glUniform2f(GetLocation(name), value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(GetLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(GetLocation(name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    uint32_t OpenGLShader::GetLocation(const std::string& name)
    {
        if (!uniforms[name])
            uniforms[name] = glGetUniformLocation(m_RendererID, name.c_str());

        return uniforms[name];
    }

    std::unordered_map<std::string, Ref<OpenGLShader>> OpenGLShaderLibrary::s_Shaders = std::unordered_map<std::string, Ref<OpenGLShader>>();

    void OpenGLShaderLibrary::Add(const std::string& name, const Ref <OpenGLShader>& shader)
    {
        EX_CORE_ASSERT(!Exists(name), "Shader " + name + " already exists!");
        s_Shaders[name] = shader;
    }

    void OpenGLShaderLibrary::Add(const Ref <OpenGLShader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<OpenGLShader> OpenGLShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = OpenGLShader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<OpenGLShader> OpenGLShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = OpenGLShader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<OpenGLShader> OpenGLShaderLibrary::Get(const std::string& name)
    {
        EX_CORE_ASSERT(Exists(name), ("Shader " + name + " not found!"));
        return s_Shaders[name];
    }

    bool OpenGLShaderLibrary::Exists(const std::string& name)
    {
        return s_Shaders.find(name) != s_Shaders.end();
    }

}