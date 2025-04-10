#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../utils/camera.hpp"

class Game{
    private:
        void Init();

        void SetParameters();
        void SetCallback();
        void ProcessInput();
        void UpdateDeltaTime();

        // Callback
        static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
        static void MouseCallback(GLFWwindow *window, double xpos, double ypos);


    public:
        static GLFWwindow *window;
        static Camera camera;
        static float deltaTime;
        Game();
        ~Game();

        void Update();
};

#endif
