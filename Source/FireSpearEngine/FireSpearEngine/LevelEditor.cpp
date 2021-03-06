#include "LevelEditor.h"



std::string LevelEditor::OpenFileExplorer(HWND hWnd)
{
    OPENFILENAME ofn;

    char fileName[100];

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = fileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "Scripts\0*.lua*\0Scenes\0*.xml*\0Audio\0*.wav*\0";
    ofn.nFilterIndex = 1;
    GetOpenFileName(&ofn);

    auto path = std::string(ofn.lpstrFile);
    if (path.empty()) return "";

    return path;
}

std::string LevelEditor::SaveFileExplorer(HWND hWnd)
{
    OPENFILENAME ofn;

    char fileName[100];

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = fileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "Scripts\0*.lua*\0Scenes\0*.xml*\0Audio\0*.wav*\0";
    ofn.nFilterIndex = 1;
    GetSaveFileName(&ofn);

    auto path = std::string(ofn.lpstrFile);
    if (path.empty()) return "";

    return path;
}

LevelEditor::LevelEditor(FireSpear* e)
{
    engine = e;
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::StartEngine() 
{
   // FireSpear* engine = new FireSpear();
    engine->isRunning = true;
    engine->InitilizeSystem();
    runBtn->setEnabled(!engine->isRunning);

    //engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene1.xml");
    //engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene2.xml");
    //engine->sceneManager->SetActive(0);

    // make a scene
    for (auto i : gameObjects)
    {
        for (auto g : engine->gameObjectManager->gameObjects)
        {
            if (g.second->GetID() == i->id)
            {
                g.second->transformComponent.position = sf::Vector2f(i->container->getPosition().x + i->container->getSize().x / 2, i->container->getPosition().y + i->container->getSize().y / 2);

                if (i->hasRenderComponent)
                {
                    g.second->GetComponent<RenderComponent*>()->SetSize(i->container->getSize());
                    g.second->GetComponent<RenderComponent*>()->SetColor(i->container->getRenderer()->getBackgroundColor());
                }

                if (i->hasRigidbodyComponent)
                {
                    g.second->GetComponent<RigidbodyComponent*>()->SetObeyGravity(i->inspectorTab->checkbox->isChecked());

                    g.second->GetComponent<RigidbodyComponent*>()->SetMass(i->inspectorTab->mass->getText().isEmpty() ? 1 : std::stoi(std::string(i->inspectorTab->mass->getText())));

                    if (!i->inspectorTab->velocityX->getText().isEmpty())
                    {
                        int x;
                        std::stringstream(i->inspectorTab->velocityX->getText()) >> x;
                        g.second->GetComponent<RigidbodyComponent*>()->velocity.x = x;
                    }
                    else
                    {
                        g.second->GetComponent<RigidbodyComponent*>()->velocity.x = 0;
                    }

                    if (!i->inspectorTab->velocityY->getText().isEmpty())
                    {
                        int y;
                        std::stringstream(i->inspectorTab->velocityY->getText()) >> y;
                        g.second->GetComponent<RigidbodyComponent*>()->velocity.y = y;
                    }
                    else
                    {
                        g.second->GetComponent<RigidbodyComponent*>()->velocity.y = 0;
                    }


                }
            }
        }
    }


    engine->Run();
  
}

void LevelEditor::ClickToolBar(std::string name)
{
    if (name == "Empty")
    {
        auto g = engine->gameObjectManager->CreateObject();

        auto gameObject = new GameObjectEditor();
        gameObject->container = tgui::ChildWindow::create();
        gameObject->container->setTitle("GameObject");
        gameObject->container->setSize(110, 0);
        sf::Vector2f position = sf::Vector2f(100, 100);
       // gameObject->container->setPosition(position.x - gameObject->container->getSize().x / 2.f, position.y - gameObject->container->getSize().y / 2.f);
        gameObject->container->setPosition(position.x, position.y);
        gameObject->container->getRenderer()->setMinimumResizableBorderWidth(20);

        // destroy object
        gameObject->container->connect("closed", [&]() { 
            for (int i = 0; i < gameObjects.size(); i++)
            {
                if (gameObjects[i]->container->isFocused())
                {
                    for (auto g : engine->gameObjectManager->gameObjects)
                    {
                        if (g.second->GetID() == gameObjects[i]->id)
                        {
                            engine->gameObjectManager->DestroyObject(g.second);
                            break;
                        }
                    }

                    hierarchy->remove(gameObjects[i]->hierarchyTab);
                    editor->remove(gameObjects[i]->container);
                    inspector->remove(gameObjects[i]->inspectorTab->editor);
                    delete gameObjects[i];  
                    gameObjects.erase(gameObjects.begin() + i);
                    return;
                }
            }
           
        });
        gameObject->id = gameObjectId;
        editor->add(gameObject->container);
       

         gameObject->hierarchyTab = tgui::EditBox::create();
         gameObject->hierarchyTab->setSize(hierarchy->getSize().x, 30);
         gameObject->hierarchyTab->setTextSize(18);
         gameObject->hierarchyTab->setPosition(0, 30 * gameObjectId);
         gameObject->hierarchyTab->setDefaultText("Game Object");

         gameObjects.push_back(gameObject);

         gameObject->hierarchyTab->connect("TextChanged", [&](sf::String text) {
            for (auto i : gameObjects)
            {
                if (i->hierarchyTab->isFocused())
                {
                    i->container->setTitle(text);
                    i->inspectorTab->editor->setTitle(text);
                    return;
                }
            }
        });

        hierarchy->add(gameObject->hierarchyTab);

        gameObject->inspectorTab = new InspectorEditor(inspector->getSize().x, 600, position);
        inspector->add(gameObject->inspectorTab->editor);

        // Change object position x using inspector value
        gameObject->inspectorTab->positionX->connect("TextChanged", [&](std::string text) {
            int x = text.empty() ? 0 : std::stoi(text);
            for (auto i : gameObjects)
            {
                if (i->inspectorTab->positionX->isFocused())
                {
                    auto p = sf::Vector2f(x, i->container->getPosition().y);
                    i->container->setPosition(p.x, p.y);
                    return;
                }
            }
        });

        // Change object position y using inspector value
        gameObject->inspectorTab->positionY->connect("TextChanged", [&](std::string text) {

            int y = text.empty() ? 0: std::stoi(text);

            for (auto i : gameObjects)
            {
                if (i->inspectorTab->positionY->isFocused())
                {
                    auto p = sf::Vector2f(i->container->getPosition().x, y);
                    i->container->setPosition(p.x, p.y);
                    return;
                }
            }
        });

        gameObject->inspectorTab->componentsBtn->connect("MouseEntered", [&]() {
            for (auto i : gameObjects)
            {
                i->inspectorTab->componentsBtn->moveToFront();
            }
        });

        // Add component components
        gameObject->inspectorTab->componentsBtn->connect("MenuItemClicked", [&](std::string text) {
         
            if (text == "Render Component")
            {
                for (auto i : gameObjects)
                {
                    if (i->inspectorTab->componentsBtn->isFocused())
                    {
                        if (!i->hasRenderComponent)
                        {
                            for (auto g : engine->gameObjectManager->gameObjects)
                            {
                                if (g.second->GetID() == i->id)
                                {
                                    g.second->AddComponent(new RenderComponent());
                                    g.second->hasRenderComponent = true;
                                    break;
                                }
                            }
                            i->hasRenderComponent = true;
                            i->inspectorTab->AddRenderComponent(i->container);
                            i->container->setResizable();
                            i->inspectorTab->renderComponent->connect("closed", [&]()
                            {
                                for (auto j : gameObjects)
                                {
                                    if (j->inspectorTab->editor->isFocused())
                                    {
                                        for (auto g : engine->gameObjectManager->gameObjects)
                                        {
                                            if (g.second->GetComponent<RenderComponent*>()) 
                                            {
                                                //g.second->RemoveComponent(3);
                                            }
                                        }
                                        return;
                                    }
                                }
                            });

                            i->inspectorTab->sizeX->connect("TextChanged", [&](std::string text) {
                                float x = text.empty() ? 0 : std::stoi(text);
                                for (auto j : gameObjects)
                                {
                                    if (j->inspectorTab->sizeX->isFocused())
                                    {
                                        auto s = sf::Vector2f(x, j->container->getPosition().y);
                                        j->container->setSize(s.x, s.y);
                                        return;
                                    }
                                }
                            });

                            i->inspectorTab->sizeY->connect("TextChanged", [&](std::string text) {
                                float y = text.empty() ? 0 : std::stoi(text);
                                for (auto k : gameObjects)
                                {
                                    if (k->inspectorTab->sizeY->isFocused())
                                    {
                                        auto s = sf::Vector2f(k->container->getPosition().x, y);
                                        k->container->setSize(s.x, s.y);
                                        return;
                                    }
                                }
                            });

                            return;
                        }
                       
                    }
                }
            }

            if (text == "Rigidbody Component")
            {
                for (auto i : gameObjects)
                {
                    if (i->inspectorTab->componentsBtn->isFocused())
                    {
                        if (!i->hasRigidbodyComponent)
                        {
                            for (auto g : engine->gameObjectManager->gameObjects)
                            {
                                if (g.second->GetID() == i->id)
                                {
                                    //std::cout << "DEBUG: ADD RIGIDBODY" << std::endl;
                                    g.second->AddComponent(new RigidbodyComponent());
                                    g.second->hasRigidbodyComponent = true;
                                    engine->physicEngine->AddRigidBody(g.second->GetComponent<RigidbodyComponent*>());
                                    break;
                                }
                            }

                            i->hasRigidbodyComponent = true;
                            i->inspectorTab->AddRigidbodyComponent();
                            i->inspectorTab->checkbox->connect("checked", [&]() {changedObbeyGravity = true; });
                            i->inspectorTab->checkbox->connect("unchecked", [&]() {changedObbeyGravity = true; });
                            i->inspectorTab->velocityX->connect("TextChanged", [&]() {changedVelocityX = true; });
                            i->inspectorTab->velocityY->connect("TextChanged", [&]() {changedVelocityY = true; });
                            i->inspectorTab->mass->connect("TextChanged", [&]() {changedMass = true; });
                            return;
                        }
                    }
                }
            }

            if (text == "Script Component")
            {
                auto path = OpenFileExplorer(window.getSystemHandle());
                if (!path.empty())
                {
                    path = path.substr(path.find("Scripts") + 8);
                    for (auto i : gameObjects)
                    {
                        if (i->inspectorTab->componentsBtn->isFocused())
                        {
                            for (auto g : engine->gameObjectManager->gameObjects)
                            {
                                if (g.second->GetID() == i->id)
                                {
                                    i->inspectorTab->AddScriptComponent(path);
                                    g.second->AddComponent(new ScriptComponent(path));
                                    g.second->hasScriptComponent = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (text == "Audio Component")
            {
                auto path = OpenFileExplorer(window.getSystemHandle());
                if (!path.empty())
                {
                    path = path.substr(path.find("Audio") + 6);
                    for (auto i : gameObjects)
                    {
                        if (i->inspectorTab->componentsBtn->isFocused())
                        {
                            for (auto g : engine->gameObjectManager->gameObjects)
                            {
                                if (g.second->GetID() == i->id)
                                {
                                    i->inspectorTab->AddAudioComponent(path, g.second);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        });
       
        gameObjectId++;

    }
    else if (name == "Exit")
    {
        exit(0);
    }
    else if (name == "About")
    {
    std::cout << "~~~~~~~~~~~~~Fire Spear Eninge~~~~~~~~~~~~~" << std::endl;
    std::cout << "A Simple 2D Game Engine using Lua as a scripting language and SFML for graphic." << std::endl;
    std::cout << "Features: Simple 2D Physics, Components Architecture, Lua Scripting, Level Editor." << std::endl;
    std::cout << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "------------Made by NeZhaS team------------" << std::endl;
    std::cout << "---------------Tuan Minh Vu----------------" << std::endl;
    std::cout << "----------------Ding Zhang-----------------" << std::endl;
    std::cout << "---------------Hsiaote Tang----------------" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << std::endl;
    std::cout << "Libraries: SFML, luaPlus, tinyxml2, tgui" << std::endl;
    }
    else if(name == "Save")
    {

    auto file = SaveFileExplorer(window.getSystemHandle());
    if(!file.empty())

        // make a scene
        for (auto i : gameObjects)
        {
            for (auto g : engine->gameObjectManager->gameObjects)
            {
                if (g.second->GetID() == i->id)
                {
                    g.second->transformComponent.position = sf::Vector2f(i->container->getPosition().x + i->container->getSize().x / 2, i->container->getPosition().y + i->container->getSize().y / 2);

                    if (i->hasRenderComponent)
                    {
                        g.second->GetComponent<RenderComponent*>()->SetSize(i->container->getSize());
                        g.second->GetComponent<RenderComponent*>()->SetColor(i->container->getRenderer()->getBackgroundColor());
                    }

                    if (i->hasRigidbodyComponent)
                    {
                        g.second->GetComponent<RigidbodyComponent*>()->SetObeyGravity(i->inspectorTab->checkbox->isChecked());

                        g.second->GetComponent<RigidbodyComponent*>()->SetMass(i->inspectorTab->mass->getText().isEmpty() ? 1 : std::stoi(std::string(i->inspectorTab->mass->getText())));

                        if (!i->inspectorTab->velocityX->getText().isEmpty())
                        {
                            int x;
                            std::stringstream(i->inspectorTab->velocityX->getText()) >> x;
                            g.second->GetComponent<RigidbodyComponent*>()->velocity.x = x;
                        }
                        else
                        {
                            g.second->GetComponent<RigidbodyComponent*>()->velocity.x = 0;
                        }

                        if (!i->inspectorTab->velocityY->getText().isEmpty())
                        {
                            int y;
                            std::stringstream(i->inspectorTab->velocityY->getText()) >> y;
                            g.second->GetComponent<RigidbodyComponent*>()->velocity.y = y;
                        }
                        else
                        {
                            g.second->GetComponent<RigidbodyComponent*>()->velocity.y = 0;
                        }


                    }
                }
            }
        }
    engine->sceneManager->SaveScene(file.c_str());
    }
    else if(name == "Load")
    {
    auto path = OpenFileExplorer(window.getSystemHandle());

    if (!path.empty())
    {
        path = path.substr(path.find("Scenes") + 7);
        path = "../../Assets/Scenes/" + path;
        std::cout << path;
        engine->InitilizeSystem();
        engine->sceneManager->LoadScene(path.c_str());
        
        engine->sceneManager->SetActive(0);
        engine->Run();
    }
    }
}

int LevelEditor::Run()
{
    window.create(sf::VideoMode(1850, 900), "Fire Spear Engine");
    window.setFramerateLimit(60);

    tgui::Gui gui(window);

    try
    {
        
        hierarchy = tgui::ChildWindow::create();
        hierarchy->setSize("15%", 768);
        hierarchy->setPosition(0, "5%");
        hierarchy->setTitle("Hierarchy");
        hierarchy->moveWidgetToBack(hierarchy);
        gui.add(hierarchy);
        

        inspector = tgui::ChildWindow::create();
        inspector->setSize("15%", 768);
        inspector->setPosition("15%", "5%");
        inspector->setTitle("Inspector");
        gui.add(inspector);

        editor = tgui::ChildWindow::create();
        editor->setSize(1280, 768);
        editor->setPosition("30%", "5%");
        editor->setTitle("Editor");
        gui.add(editor);

        runBtn = tgui::Button::create();
        runBtn->setPosition("50%", "95%");
        runBtn->setText("Run");
        runBtn->setSize(100, 30);
        runBtn->connect("pressed", &LevelEditor::StartEngine, this);
        gui.add(runBtn);

        /*auto pauseBtn = tgui::Button::create();
        pauseBtn->setPosition("60%", "95%");
        pauseBtn->setText("Pause");
        pauseBtn->setSize(100, 30);
        gui.add(pauseBtn);*/

        auto menu = tgui::MenuBar::create();
        menu->setSize(static_cast<float>(window.getSize().x), "2%");
        menu->addMenu("Scenes");
        menu->addMenuItem("Load");
        menu->addMenuItem("Save");

        menu->addMenuItem("Exit");
        menu->connect("MenuItemClicked", &LevelEditor::ClickToolBar, this);
        menu->addMenu("Game Object");
        menu->addMenuItem("Empty");
        menu->addMenu("Help");
        menu->addMenuItem("About");
        gui.add(menu);
    }
    catch (const tgui::Exception & e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    while (window.isOpen())
    {
        if (!runBtn->isEnabled())
        runBtn->setEnabled(!engine->isRunning);
        for (auto i : gameObjects)
        {
            // select object using the hierarchy
            if (i->hierarchyTab->isFocused())
                i->inspectorTab->editor->moveToFront();

            // update position value when drag
            i->inspectorTab->positionY->setDefaultText(std::to_string(i->container->getPosition().y));
            i->inspectorTab->positionX->setDefaultText(std::to_string(i->container->getPosition().x));

            if (i->hasRenderComponent)
            {
                //update size
                i->inspectorTab->sizeX->setDefaultText(std::to_string(i->container->getSize().x));
                i->inspectorTab->sizeY->setDefaultText(std::to_string(i->container->getSize().y));

                //update color
                auto r = i->inspectorTab->rSlider->getValue();
                auto g = i->inspectorTab->gSlider->getValue();
                auto b = i->inspectorTab->bSlider->getValue();
                auto a = i->inspectorTab->aSlider->getValue();
                i->container->getRenderer()->setBackgroundColor(tgui::Color(r, g, b, a));
            
            }
            

            if (!i->inspectorTab->positionY->isFocused())
                i->inspectorTab->positionY->setText(std::to_string(i->container->getPosition().y ));

            if(!i->inspectorTab->positionX->isFocused())
                i->inspectorTab->positionX->setText(std::to_string(i->container->getPosition().x));
        }
       
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            gui.handleEvent(event);
            
        }

        window.clear(sf::Color(255, 230, 171, 100));
        gui.draw();
        window.display();


    }

    return EXIT_SUCCESS;
}
