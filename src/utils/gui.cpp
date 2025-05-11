#ifndef GUI_CPP
#define GUI_CPP

#include "gui.hpp"
#include "../game.hpp"
#include "grid.hpp"

#include <iostream>
#include <string>

GUI::GUI() : enable{true} { }

GUISpawnPawn::GUISpawnPawn() : GUI{} { }

void GUISpawnPawn::Init(){
    SpawnPawnButton button{};
    button.size = glm::vec2(1.0f);
    button.position = glm::vec2(-0.12f, -0.88f);
    button.type = WARRIOR;
    button.SetSprite(IDLE, Game::textureList.textures[IWARRIOR_TEX]);
    button.SetSprite(HOVER, Game::textureList.textures[HWARRIOR_TEX]);
    button.SetSprite(CLICKED, Game::textureList.textures[CWARRIOR_TEX]);
    buttons.push_back(button);   

    button.position = glm::vec2{0.0f, -0.88f};
    button.type = LORD;
    button.SetSprite(IDLE, Game::textureList.textures[ILORD_TEX]);
    button.SetSprite(HOVER, Game::textureList.textures[HLORD_TEX]);
    button.SetSprite(CLICKED, Game::textureList.textures[CLORD_TEX]);
    buttons.push_back(button);   

    button.position = glm::vec2{0.12f, -0.88f};
    button.type = FARMER;
    button.SetSprite(IDLE, Game::textureList.textures[IFARMER_TEX]);
    button.SetSprite(HOVER, Game::textureList.textures[HFARMER_TEX]);
    button.SetSprite(CLICKED, Game::textureList.textures[CFARMER_TEX]);
    buttons.push_back(button);   

    coinSprite.texture = &Game::textureList.textures[COIN_TEX];
}

int GUISpawnPawn::Update(Player &player, Pawn &pawn, Tilemap &tilemap){
    std::vector<SpawnPawnButton>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it){
        ButtonState state = it->GetState();
        it->Update();
        if (state != CLICKED && it->GetState() == CLICKED)
            if (it->Clicked(player, pawn, tilemap) == 1) return 1;
    }
    return 0;
}



void GUISpawnPawn::RenderGui(Shader &shader){
    // Render Buttons
    std::vector<SpawnPawnButton>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it){
        it->RenderButton(shader);
    }
}



GUITransformLord::GUITransformLord() { }
void GUITransformLord::Init(){
    button.position = glm::vec2(0.0f, -0.88f);
    button.size = glm::vec2(1.0f);
    button.SetSprite(IDLE, Game::textureList.textures[ICASTLE_TEX]);
    button.SetSprite(HOVER, Game::textureList.textures[HCASTLE_TEX]);
    button.SetSprite(CLICKED, Game::textureList.textures[CCASTLE_TEX]);
}

int GUITransformLord::Update(Player &player, Pawn &pawn, Tilemap &tilemap){
    ButtonState state = button.GetState();
    button.Update();
    if (state != CLICKED && button.GetState() == CLICKED)
        return button.Clicked(player, pawn, tilemap);
    return 0;
}

void GUITransformLord::RenderGui(Shader &shader){
    button.RenderButton(shader);
}

GUIHarvest::GUIHarvest() { }
void GUIHarvest::Init(){
    button.position = glm::vec2(0.0f, -0.88f);
    button.size = glm::vec2(1.0f);
    button.SetSprite(IDLE, Game::textureList.textures[IFARMER_TEX]);
    button.SetSprite(HOVER, Game::textureList.textures[HFARMER_TEX]);
    button.SetSprite(CLICKED, Game::textureList.textures[CFARMER_TEX]);
}

int GUIHarvest::Update(Player &player, Pawn &pawn){
    ButtonState state = button.GetState();
    button.Update();
    if (state != CLICKED && button.GetState() == CLICKED)
        return button.Clicked(player, pawn);
    return 0;
}

void GUIHarvest::RenderGui(Shader &shader){
    button.RenderButton(shader);
}

GUIHud::GUIHud() : GUI{} { 
    nbCoins = 0;
    playerTurn = 0;
}

void GUIHud::Init(){
    coins.texture = &Game::textureList.textures[COIN_TEX];
    endTurn.position =  glm::vec2(0.8f, -0.9);
    endTurn.size = glm::vec2(1.0f);
    endTurn.SetSprite(IDLE, Game::textureList[ISKIP_TEX]);
    endTurn.SetSprite(HOVER, Game::textureList[HSKIP_TEX]);
    endTurn.SetSprite(CLICKED, Game::textureList[CSKIP_TEX]);
}

int GUIHud::Update(){
    ButtonState state = endTurn.GetState();
    endTurn.Update();
    if (state != CLICKED && endTurn.GetState() == CLICKED){
        if(endTurn.Clicked()) return 1;
    }
    return 0;
}

void GUIHud::RenderGui(Shader &shader){
    int w, h;
    glfwGetWindowSize(Game::window, &w, &h);

    shader.Use();
    shader.SetInt("outlined", 0);
    // Render sprites
    float sizeFactor = Game::camera.position.z * 0.2f;
    coins.Draw(shader, Grid::ScreenToWorld(glm::vec2(-0.8f, -0.9)), glm::vec3(glm::vec2(0.9f) * sizeFactor, 1.0f));
    Game::textRenderer.RenderText(std::to_string(nbCoins), - w * 0.5f + w * 0.05, - h * 0.5 + h * 0.05, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    Game::textRenderer.RenderText("Player " + std::to_string(playerTurn), -w * 0.025, h * 0.5 - h * 0.1, 1.0f, player ? player->color : glm::vec3(1.0f));
    endTurn.RenderButton(shader);
}


#endif