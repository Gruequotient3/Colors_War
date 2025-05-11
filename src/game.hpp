#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "utils/camera.hpp"
#include "utils/tilemap.hpp"
#include "gfx/texture.hpp"
#include "gfx/shader.hpp"
#include "gfx/text.hpp" 
#include "player.hpp"
#include "utils/gui.hpp"

enum State{
    START,
    ROUND_START,
    ROUND,
    ROUND_END,
    GAME_OVER
};

class Game{
    private:
        void Init();
        void Start();
        void Render();

        void SetParameters();
        void SetCallback();
        void ProcessInput();
        void UpdateDeltaTime();

        // Opengl Callback
        static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
        static void MouseCallback(GLFWwindow *window, double xpos, double ypos);


    public:
        static GLFWwindow *window;
        static TextureList textureList;
        static ShaderList shaderList;
        static Camera camera;
        static float deltaTime;
        static TextMesh textRenderer;
        
        Tilemap tilemap;
        State gameState;
        Player players[2];
        Pawn *selected;

        GUISpawnPawn pawnSpawnGUI;
        GUITransformLord transformLordGUI;
        GUIHarvest harvestGUI;
        GUIHud hudGUI;


        int playerTurn;
        Player *winner;

        Game();
        ~Game();

        void Play();
};

#endif
