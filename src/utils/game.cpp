#ifndef GAME_CPP
#define GAME_CPP

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <cstdlib>

#include "game.hpp"
#include "mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

GLFWwindow *Game::window = nullptr;
Camera Game::camera{16.0f / 9.0f};
float Game::deltaTime = 0.0f;
Game::Game(){
    Init();
}

Game::~Game(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::Init(){
    // Initialise GLFW
    if (!glfwInit()){
        std::cout << "Failed to initialise GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // OpenGL context Parameters
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialise OpenGL context
    window = glfwCreateWindow(1920, 1080, "Color Battle", NULL, NULL);
    if (!window){
        std::cout << "Failed to initialise OpenGL Context" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD" << std::endl;
        glfwTerminate();
        glfwDestroyWindow(window);
        exit(EXIT_FAILURE);
    }

    SetParameters();
    SetCallback();
}

void Game::Update(){
    Shader shader = {"res/shaders/shader.vert", "res/shaders/shader.frag"};
    Mesh quad = Mesh::GetQuadMesh();
    quad.GenerateMesh();
    while(!glfwWindowShouldClose(window)){
        camera.Update();
        UpdateDeltaTime();
        ProcessInput();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glm::mat4 model = glm::mat4(1.0f);
        shader.SetMat4("model", false, glm::value_ptr(model));
        shader.SetMat4("view", false, camera.GetViewMatrice());
        shader.SetMat4("projection", false, camera.GetProjectionMatrice());

        shader.SetVec3("color", glm::vec3(0.0f, 0.5f, 0.0f));
        quad.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::SetParameters(){
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
}

void Game::SetCallback(){
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    //glfwSetCursorPosCallback(window, MouseCallback);
}

void Game::ProcessInput(){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    float velocity = 0.1f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.position +=  camera.front * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.position -=  camera.front * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.position -=
            glm::normalize(glm::cross(camera.front, camera.up)) * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.position +=
            glm::normalize(glm::cross(camera.front, camera.up)) * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        camera.position += camera.up * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        camera.position -= camera.up * velocity;
    }
}

void Game::UpdateDeltaTime(){
    static float lastFrame = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = ceilf((currentFrame - lastFrame) * 1000) / 1000;
    lastFrame = currentFrame;
}

void Game::FrameBufferSizeCallback(GLFWwindow *, int width, int height){
    glViewport(0, 0, width, height);
    camera.ratio = width / (float)height;
}

void Game::MouseCallback(GLFWwindow* , double xpos, double ypos){
    static float lastX = xpos;
    static float lastY = ypos;


    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 4.0f;

    xoffset *= sensitivity * deltaTime;
    yoffset *= sensitivity * deltaTime;

    camera.yaw += xoffset;
    camera.pitch += yoffset;

    if (camera.pitch > 89.0f){
        camera.pitch = 89.0f;
    }
    if (camera.pitch < -89.0f){
        camera.pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    direction.y = sin(glm::radians(camera.pitch));
    direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));

    camera.front = glm::normalize(direction);
}



#endif
