#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../gfx/sprite.hpp"
#include "../utils/tilemap.hpp"
#include "../player.hpp"


enum ButtonState {IDLE, HOVER, CLICKED};

class Button{
    private:
        Sprite sprites[3];
        enum ButtonState state;
    
    public:
        bool enable;

        glm::vec2 position;
        glm::vec2 size;
        

        Button();
        Button(glm::vec2 position, glm::vec2 size);

        void SetSprite(enum ButtonState state, Texture &texture);
        
        enum ButtonState GetState();
        
        void RenderButton(Shader &shader) const;
        void Update();
};

class SpawnPawnButton : public Button{
    private:
    public:
        enum PawnType type;
        SpawnPawnButton();
        SpawnPawnButton(glm::vec2 position, glm::vec2 size, enum PawnType type);
        
        int Clicked(Player &player, Pawn &pawn, Tilemap &tilemap);
};

class TransformLordButton : public Button{
    private:
    public:
        TransformLordButton();
        TransformLordButton(glm::vec2 position, glm::vec2 size);

        int Clicked(Player &player, Pawn &pawn, Tilemap &tilemap);
};

class HarvestButton : public Button{
    private:
    public:
        HarvestButton();
        HarvestButton(glm::vec2 position, glm::vec2 size);

        int Clicked(Player &player, Pawn &pawn);
};

class EndTurnButton : public Button{
    private:
    public:
        EndTurnButton();
        EndTurnButton(glm::vec2 position, glm::vec2 size);

        int Clicked();
};



#endif