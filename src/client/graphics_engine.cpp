#include <client/graphics_engine.hpp>
#include <client/display.hpp>

#include <iostream>

GraphicsEngine::GraphicsEngine()
{
    client = nullptr;
    context = nullptr;
}

GraphicsEngine::GraphicsEngine(Game* client)
    : client(client)
{
    context = nullptr;
}

GraphicsEngine::~GraphicsEngine()
{
    if (context != nullptr)
        SDL_GL_DeleteContext(context);

    client = NULL;
}

int GraphicsEngine::init()
{
    // Select an OpenGL 4.5 profile.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    client->getDisplay()->create();

    context = SDL_GL_CreateContext(client->getDisplay()->getWindow()); 

    GLenum err;
    glewExperimental = GL_TRUE;
    if((err=glewInit()) != GLEW_OK){
        std::cerr << "GLEW was not able to initialize! Error: " << 
            glewGetErrorString(err) << std::endl;
        return -1;
    }

    SDL_GL_SetSwapInterval(0);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    Shader world;
    world.createProgram("shaders/world/vert.glsl", "shaders/world/frag.glsl");

    world.addUniform("projection");
    world.addUniform("view");
    world.addUniform("model");

    GLint a = world.addAttribute("vertex");

    addShader("world", world);

    glEnableVertexAttribArray(a);

    glUseProgram(world.getProgram());

    glPolygonOffset(1.0, 1.0);

    glClearColor(0.6, 0.8, 1.0, 0.0);

    return 0;
}

int GraphicsEngine::drawLoop()
{
    GLint a = shaders.at("world").getAttribute("vertex");
    GLint p = shaders.at("world").getUniform("projection");
    GLint v = shaders.at("world").getUniform("view");
    GLint m = shaders.at("world").getUniform("model");
    GLuint s = shaders.at("world").getProgram();

    std::cout << a << "," << p << "," << v << "," << m << std::endl;
    std::cout << s << std::endl;

    glm::vec3 cpos = glm::vec3(0.0, 0.0, 10.0);
    //glm::vec3 crot = glm::vec3(0.0, 0.0, 0.0);

    static const GLfloat tri_data[] = {
        -1.0, -1.0, 0.0,
        1.0, -1.0, 0.0,
        0.0, 1.0, 0.0,
    };

    while (client->isRunning()) {
        glm::mat4 view = glm::lookAt(cpos, 
                                     glm::vec3(0.0f, 0.0f, 0.0f), 
                                     glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(90.0f, 
                                                (1280.0f/720.0f), 
                                                0.01f, 
                                                2048.0f);

        glm::mat4 model = glm::mat4(1.0f);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(m, 1, GL_FALSE, glm::value_ptr(model));

        //glEnable(GL_CULL_FACE);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glUseProgram(s);

        glEnableVertexAttribArray(a);

        // draw world

        GLuint tri_vbo;
        
        glGenBuffers(1, &tri_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, tri_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tri_data), 
                tri_data, GL_STATIC_DRAW);

        glVertexAttribPointer(a, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(a);

        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_CULL_FACE);

        glUseProgram(0);

        // draw text

        SDL_GL_SwapWindow(client->getDisplay()->getWindow());
    }

    return 0;
}

void GraphicsEngine::addShader(std::string shaderName, Shader shader)
{
    shaders.emplace(shaderName, shader);
}
