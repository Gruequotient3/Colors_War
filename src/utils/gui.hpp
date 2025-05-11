#ifndef GUI_HPP
#define GUI_HPP

#include <vector>

#include "button.hpp"


class GUI{
    private:
    public:
        bool enable;

        GUI();
        virtual void Init() = 0;
        virtual void RenderGui(Shader &shader) = 0;
};

class GUISpawnPawn : public GUI{
    private:
    public:
        std::vector<SpawnPawnButton> buttons;
        Sprite coinSprite;

        GUISpawnPawn();
        void Init();
        int Update(Player &player, Pawn &pawn, Tilemap &tilemap);
        void RenderGui(Shader &shader);
};

class GUITransformLord : public GUI{
    private:
    public:
        TransformLordButton button;

        GUITransformLord();
        void Init();
        int Update(Player &player, Pawn &pawn, Tilemap &tilemap);
        void RenderGui(Shader &shader);
};

class GUIHarvest : public GUI{
    private:
    public:
        HarvestButton button;

        GUIHarvest();
        void Init();
        int Update(Player &player, Pawn &pawn);
        void RenderGui(Shader &shader);
};

class GUIHud : public GUI{
    private:
    public:
        Sprite coins;
        EndTurnButton endTurn;

        int nbCoins;
        int playerTurn;
        Player *player;

        GUIHud();
        void Init();
        int Update();
        void RenderGui(Shader &shader);
};

#endif