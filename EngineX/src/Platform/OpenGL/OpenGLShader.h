#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace EngineX {

    class OpenGLShader
    {

    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const;
        void Unbind() const;

        const std::string& GetName() const { return m_Name; };

    public:
        static Ref<OpenGLShader> Create(const std::string& filepath);
        static Ref<OpenGLShader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

    public:
        void UploadUniformInt(const std::string& name, int value);

        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<uint32_t, std::string> PreProcess(const std::string& source);

        void Compile(const std::unordered_map<uint32_t, std::string>& shaderSources);
        void ExtractUniforms(const std::string& source);
        uint32_t GetLocation(const std::string& name);

    private:
        uint32_t m_RendererID;
        std::unordered_map<std::string, int> uniforms;
        std::string m_Name;

    };

    class OpenGLShaderLibrary
    {

    public:
        static void Add(const std::string& name, const Ref<OpenGLShader>& shader);
        static void Add(const Ref<OpenGLShader>& shader);
        static Ref<OpenGLShader> Load(const std::string& filepath);
        static Ref<OpenGLShader> Load(const std::string& name, const std::string& filepath);

        static Ref<OpenGLShader> Get(const std::string& name);

        static bool Exists(const std::string& name);

    private:
        static std::unordered_map<std::string, Ref<OpenGLShader>> s_Shaders;

    };

}
