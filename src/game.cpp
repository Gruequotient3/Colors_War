#ifndef GAME_CPP
#define GAME_CPP

#include <iostream>
#include <cstdlib>

#include <ft2build.h>
#include FT_FREETYPE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "game.hpp"
#include "utils/mesh.hpp"
#include "utils/grid.hpp"
#include "entity/pawn.hpp"


#define WIDTH 1920
#define HEIGHT 1080

#define TILEMAP_W 16
#define TILEMAP_H 9

GLFWwindow *Game::window = nullptr;
Camera Game::camera{WIDTH / (float)HEIGHT, WIDTH, HEIGHT};
TextureList Game::textureList;
ShaderList Game::shaderList;
float Game::deltaTime = 0.0f;
TextMesh Game::textRenderer;

Game::Game() : tilemap{3, TILEMAP_W, TILEMAP_H} {
    Init();
    gameState = START;
}

Game::~Game(){
    Sprite::mesh.DestroyMesh();
    textRenderer.DestroyMesh();
    
    
    textureList.Destroy();
    shaderList.Destroy();
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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Color Battle", glfwGetPrimaryMonitor(), NULL);
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
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    
    SetParameters();
    SetCallback();

    selected = nullptr;

    // Load Textures / Shaders
    textureList.LoadTexture();
    shaderList.LoadShader();

    // Generate Sprites Mesh
    Sprite::mesh.GenerateMesh();
    // Generate Tilemap
    tilemap.GenerateTilemap();
    // GenerateTextRenderer
    textRenderer.GenerateMesh();    

    // Load GUI
    hudGUI.Init();
    pawnSpawnGUI.Init();
    transformLordGUI.Init();
    harvestGUI.Init();

}

void Game::Start(){
    playerTurn = 0;
    winner = nullptr;

    // Clear players pawn data
    players[0].pawns.Clear();
    players[1].pawns.Clear();
    
    // Set Player color;
    players[0].color = glm::vec3(0.15f, 0.38f, 0.74f);
    players[1].color = glm::vec3(0.74f, 0.27f, 0.15f);

    // Store new Game pawns data
    glm::vec2 position = glm::vec2(-TILEMAP_W / 2, -TILEMAP_H / 2);
    Tile *tile = tilemap.GetTile(glm::ivec2(position));
    players[0].AddPawn(position, CASTLE);
    if (tile) tile->tags.occupied = 1;

    position = -position;
    tile = tilemap.GetTile(glm::ivec2(position));
    players[1].AddPawn(position, CASTLE);
    if (tile) tile->tags.occupied = 1;
}

void Game::Play(){
    textRenderer.SetShader(shaderList[TEXT_SHAD]);

    shaderList[DEFAULT_SHAD].SetInt("texture2D[0]", 0);
    shaderList[DEFAULT_SHAD].SetInt("texture2D[1]", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureList.textures[FARMER_TEX].id);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        UpdateDeltaTime();
        camera.Update();
        switch (gameState){
            case START:
                Start();
                gameState = ROUND_START;
                break;

            case ROUND_START:
                players[playerTurn].ResetPawn();
                players[playerTurn].HarvestCoins();

                hudGUI.playerTurn = playerTurn;
                hudGUI.player = &players[playerTurn];
                gameState = ROUND;   
                break;

            case ROUND_END:
                if (!players[0].HaveCastle()){
                    winner = &players[0];
                    gameState = GAME_OVER;
                    break;
                }
                if (!players[1].HaveCastle()){
                    winner = &players[1];
                    gameState = GAME_OVER;
                    break;
                }
                playerTurn = (playerTurn + 1) % 2;
                gameState = ROUND_START;
                break;

            case GAME_OVER: 
                glfwSetWindowShouldClose(window, true);
                break;
                
            default:
                break;
        }

        
        Render();
        ProcessInput();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::Render(){
    // Render Tilemap
    if (selected){
        shaderList[DEFAULT_SHAD].Use();
        shaderList[DEFAULT_SHAD].SetInt("tilemapMode", 1);
        shaderList[DEFAULT_SHAD].SetIvec2("selPos", glm::ivec2(selected->position));
        shaderList[DEFAULT_SHAD].SetInt("mp", selected->stat.mp);
    }
    tilemap.Draw(shaderList[DEFAULT_SHAD]);
    shaderList[DEFAULT_SHAD].SetInt("tilemapMode", 0);

    // Render Players Pawns
    for (int i = 0; i < 2; ++i){
        players[i].RenderPawns(shaderList[DEFAULT_SHAD], selected);
    }
    
    if (selected){
        const PawnTags &tags = selected->GetTags();
        switch(selected->type){
            case CASTLE:
                if (!tags.on_cooldown && players[playerTurn].ContainPawn(*selected)){
                    if (pawnSpawnGUI.Update(players[playerTurn], *selected, tilemap)){
                        selected = nullptr;
                    }
                    pawnSpawnGUI.RenderGui(shaderList[DEFAULT_SHAD]);
                }
                break;
            case LORD:
                if (!(tags.on_cooldown) && players[playerTurn].ContainPawn(*selected)){
                    if (transformLordGUI.Update(players[playerTurn], *selected, tilemap)){
                        selected = nullptr;
                    }
                    transformLordGUI.RenderGui(shaderList[DEFAULT_SHAD]);
                }
                break;
            case FARMER:
                if (!tags.on_cooldown && players[playerTurn].ContainPawn(*selected)){
                    Tile *tile = tilemap.GetTile(glm::ivec2(selected->position));
                    if (tile && tile->tags.can_harvest){
                        if (harvestGUI.Update(players[playerTurn], *selected)){
                            selected = nullptr;
                        }
                        harvestGUI.RenderGui(shaderList[DEFAULT_SHAD]);
                    }
                }
                break;
            default:
                break;
        }
    }
    
    // Render HUD
    hudGUI.nbCoins = players[playerTurn].coins;
    if (hudGUI.Update() && gameState == ROUND) gameState = ROUND_END;
    hudGUI.RenderGui(shaderList[DEFAULT_SHAD]);
}


void Game::SetParameters(){
    glfwSwapInterval(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Game::SetCallback(){
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    //glfwSetCursorPosCallback(window, MouseCallback);
}
void Game::ProcessInput(){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        Pawn *pawn = nullptr;
        glm::ivec2 gridPosition = glm::ivec2(Grid::WorldToGrid(Grid::ScreenToWorld()));
        for (int i = 0; i < 2; ++i){
            if ((pawn = players[i].GetPawn(gridPosition))){
                break;
            }
            pawn = nullptr;
        }

        switch (gameState){
            case ROUND:
                if (!selected) break;
                if (!pawn){
                    if (players[playerTurn].ContainPawn(*selected))
                        selected->Move(glm::vec3(gridPosition, 0.0f), tilemap);
                }
                else{
                    int playerId = (playerTurn + 1) % 2;
                    if (players[playerId].ContainPawn(*pawn) && players[playerTurn].ContainPawn(*selected)){
                        selected->Attack(*pawn, tilemap);
                        if (pawn->IsDead()){
                            Tile *tile = nullptr;
                            tile = tilemap.GetTile(gridPosition);
                            if (tile) tile->tags.occupied = 0;
                            players[playerId].RemovePawn(gridPosition);
                            pawn = nullptr;
                        }
                    }
                }
            default:
                break;
        }
        if (pawn) selected = pawn;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        selected = nullptr;
    }

    float velocity = 2.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.position += camera.up * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.position -= camera.up * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.position -=
            glm::normalize(glm::cross(camera.front, camera.up)) * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.position +=
            glm::normalize(glm::cross(camera.front, camera.up)) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        camera.position += camera.front * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        camera.position -= camera.front * velocity;
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
    camera.width = width;
    camera.height = height;
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
