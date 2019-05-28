#include <client/RenderSystem.hpp>

#include <iostream>

RenderSystem::RenderSystem()
{
 
}

RenderSystem::~RenderSystem()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

int RenderSystem::init()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        std::cerr << "ERROR: Could not open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    return 0;
}

int RenderSystem::start()
{
    running = true;

    glfwMakeContextCurrent(window);

    // Start GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

#ifdef DEBUG

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    std::cout << "Render: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

    renderer = 0;
    version = 0;

#endif

    do {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            !glfwWindowShouldClose(window));

    return 0;
}

void RenderSystem::stop()
{
    running = false;
}
