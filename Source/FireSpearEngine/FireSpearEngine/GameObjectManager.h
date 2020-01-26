#pragma once
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
public:
    GameObjectManager() {};
    ~GameObjectManager();
    GameObject* CreateObject();
    void DestroyObject(GameObject* o);

    void Update(sf::Time msec);
    void Awake();
    void Start();
    void LateUpdate(sf::Time msec);
    std::vector<GameObject*> DrawableObjects();

private:
    std::map<int, GameObject*> gameObjects;
    static int nextObjectID;
};

