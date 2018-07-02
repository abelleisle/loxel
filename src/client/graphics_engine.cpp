#include <client/graphics_engine.hpp>

#include <iostream>
#include <thread>
#include <chrono>

GraphicsEngine::GraphicsEngine()
{
    // Initialize configs and their default values
    GameState::clientConfig.addItem("monitor_width", 1280);
    GameState::clientConfig.addItem("monitor_height", 720);
    GameState::clientConfig.addItem("game_title", std::string("loxel"));
}

GraphicsEngine::~GraphicsEngine()
{
    if (context != nullptr)
        SDL_GL_DeleteContext(context);
}

int GraphicsEngine::init()
{
    double width;
    double height;
    std::string title;

    try {
        width = GameState::clientConfig.getItem<double>("monitor_width");
        height = GameState::clientConfig.getItem<double>("monitor_height");
        title = GameState::clientConfig.getItem<std::string>("game_title");
    } catch (std::exception &oof) {}

    display = Display(title, static_cast<int>(width),
                             static_cast<int>(height));
    
    // Select an OpenGL 3.0 profile.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    display.create();

    context = SDL_GL_CreateContext(display.getWindow()); 

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

    world.addAttribute("vertex");

    addShader("world", world);

    glEnableVertexAttribArray(shaders.at("world").getAttribute("vertex"));

    glUseProgram(world.getProgram());

    glPolygonOffset(1.0, 1.0);

    glClearColor(0.6, 0.8, 1.0, 0.0);

    cam = Camera();

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

    static GLfloat tri_data[] = {
        -1.0, -1.0, 0.0,
        1.0, -1.0, 0.0,
        0.0, 1.0, 0.0,
    };

    float startTime;
    float endTime;

    while (GameState::isRunning()) {
        // update time schtuff
        startTime = SDL_GetTicks();
        GameState::gameObject()->setDeltaTime(startTime - endTime);
        endTime = startTime;

        cam.update();
        glm::mat4 view = glm::lookAt(cam.pos,
                                     cam.pos+cam.rot, 
                                     glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(45.0f, 
                                                (1280.0f/720.0f), 
                                                0.01f, 
                                                2048.0f);

        glm::mat4 model = glm::mat4(1.0f);

        glUseProgram(s);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(m, 1, GL_FALSE, glm::value_ptr(model));

        glEnable(GL_CULL_FACE);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glEnableVertexAttribArray(a);

        // draw world

        GLuint tri_vbo;
        
        glGenBuffers(1, &tri_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, tri_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tri_data), tri_data, GL_STREAM_DRAW);

        glVertexAttribPointer(a, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(a);

        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_CULL_FACE);

        glUseProgram(0);

        // draw text

        SDL_GL_SwapWindow(display.getWindow());
    }

    return 0;
}

void GraphicsEngine::addShader(std::string shaderName, Shader shader)
{
    shaders.emplace(shaderName, shader);
}

Camera* GraphicsEngine::getCamera()
{
    return &cam;
}

Display* GraphicsEngine::getDisplay()
{
    return &display;
}

void GraphicsEngine::setDisplay(Display d)
{
    display = d;
}
