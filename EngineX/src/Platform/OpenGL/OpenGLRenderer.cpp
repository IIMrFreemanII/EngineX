#include "OpenGLRenderer.h"

#include "glad/glad.h"
#include "EngineX/Application.h"
#include "iostream"

namespace EngineX {

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] =  {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f, 0.5f, 0.0f  // top
    };

    OpenGLRenderer::OpenGLRenderer()
    {
        m_RenderAPI = OpenGLRendererAPI();
        m_ClearColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);

        Window& window = Application::Get().GetWindow();
        FrameBufferConfiguration configuration{};
        configuration.size = { window.GetWidth(), window.GetHeight() };

        m_FrameBuffer = std::make_unique<OpenGLFrameBuffer>(configuration);

        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }

    void OpenGLRenderer::BeginScene()
    {
        // init scene data
//        m_RenderAPI.SetClearColor(m_ClearColor);
//        m_RenderAPI.Clear();
    }

    void OpenGLRenderer::EndScene()
    {
        // render submitted objects
    }

    void OpenGLRenderer::OnUpdate()
    {
        EX_PROFILE_FUNCTION();

        BeginScene();

        Application& app = Application::Get();
        Editor& editor = app.GetEditor();
        Window& window = app.GetWindow();
        glm::vec2& sceneSize = editor.sceneEditor->Size;

        m_FrameBuffer->HandleResize(sceneSize);

        // bind to framebuffer and draw scene as we normally would to color texture
        m_FrameBuffer->Bind();
        glViewport(0, 0, sceneSize.x, sceneSize.y);

        // make sure we clear the framebuffer's content
        m_RenderAPI.SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        m_RenderAPI.Clear();

        // submit objects to render
        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // now bind back to default framebuffer
        m_FrameBuffer->UnBind();

        glViewport(0, 0, window.GetWidth(), window.GetHeight());

        m_RenderAPI.SetClearColor(m_ClearColor);
        m_RenderAPI.Clear();

        EndScene();
    }

}
