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
    std::map<int, GameObject*> gameObjects; // should change to private later ????
    void DeleteAllGameObjects();
private:
    
    static int nextObjectID;
};

