#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::StartEngine()
{
    FireSpear* engine = new FireSpear();
    engine->InitilizeSystem();

    engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene1.xml");
    engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene2.xml");
    engine->sceneManager->SetActive(0);
    engine->Run();
}

void LevelEditor::CreateGameObject(std::string name)
{
    if (name == "Empty" || name == "Rectangle")
    {
        auto gameObject = new GameObjectEditor();
        gameObject->container = tgui::ChildWindow::create();
        gameObject->container->setTitle("GameObject");
        gameObject->container->setSize(100, 100);
        sf::Vector2f position = sf::Vector2f(100, 100);
        gameObject->container->setPosition(position.x - gameObject->container->getSize().x / 2.f, position.y - gameObject->container->getSize().y / 2.f);
        gameObject->container->connect("closed", [&]() { 
            for (int i = 0; i < gameObjects.size(); i++)
            {
                if (gameObjects[i]->container->isFocused())
                {
                    hierarchy->remove(gameObjects[i]->hierarchyTab);
                    editor->remove(gameObjects[i]->container);
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

        gameObject->inspectorTab = new InspectorEditor(inspector->getSize().x, 100, position);
        inspector->add(gameObject->inspectorTab->editor);

        // Change object position x using inspector value
        gameObject->inspectorTab->positionX->connect("TextChanged", [&](std::string text) {
            int x = std::stoi(text);
            for (auto i : gameObjects)
            {
                if (i->inspectorTab->positionX->isFocused())
                {
                    auto p = sf::Vector2f(x, i->container->getPosition().y);
                    i->container->setPosition(p.x - i->container->getSize().x / 2.f, p.y);
                    return;
                }
            }
        });

        // Change object position y using inspector value
        gameObject->inspectorTab->positionY->connect("TextChanged", [&](std::string text) {
            int y = std::stoi(text);
            for (auto i : gameObjects)
            {
                if (i->inspectorTab->positionY->isFocused())
                {
                    auto p = sf::Vector2f(i->container->getPosition().x, y);
                    i->container->setPosition(p.x, p.y - i->container->getSize().y / 2.f);
                    return;
                }
            }
        });
       
        gameObjectId++;

        if (name == "Rectangle")
        {
            gameObject->container->getRenderer()->setBackgroundColor(tgui::Color(255, 1, 0, 255));
        }

    }
}

int LevelEditor::Run()
{
    sf::RenderWindow window(sf::VideoMode(1850, 900), "Fire Spear Engine");
    window.setFramerateLimit(60);

    tgui::Gui gui(window);

    try
    {
        
        hierarchy = tgui::ChildWindow::create();
        hierarchy->setSize("15%", 768);
        hierarchy->setPosition(0, "2.5%");
        hierarchy->setTitle("Hierarchy");
        hierarchy->moveWidgetToBack(hierarchy);
        gui.add(hierarchy);
        

        inspector = tgui::ChildWindow::create();
        inspector->setSize("15%", 768);
        inspector->setPosition("15%", "2.5%");
        inspector->setTitle("Inspector");
        gui.add(inspector);

        editor = tgui::ChildWindow::create();
        editor->setSize(1280, 768);
        editor->setPosition("30%", "2.5%");
        editor->setTitle("Editor");
        gui.add(editor);

        auto runBtn = tgui::Button::create();
        runBtn->setPosition("40%", "95%");
        runBtn->setText("Run");
        runBtn->setSize(100, 30);
        runBtn->connect("pressed", &LevelEditor::StartEngine, this);
        gui.add(runBtn);

        auto pauseBtn = tgui::Button::create();
        pauseBtn->setPosition("60%", "95%");
        pauseBtn->setText("Pause");
        pauseBtn->setSize(100, 30);
        
       // pauseBtn->connect("pressed", [&]() {engine->Pause(); }, this);
        gui.add(pauseBtn);

        auto menu = tgui::MenuBar::create();
        menu->setSize(static_cast<float>(window.getSize().x), "2%");
        menu->addMenu("Scenes");
        menu->addMenuItem("Load");
        menu->addMenuItem("Save");
        menu->addMenuItem("Exit");
        menu->connect("MenuItemClicked", &LevelEditor::CreateGameObject, this);
        menu->addMenu("Game Object");
        menu->addMenuItem("Empty");
        menu->addMenuItem("Rectangle");
        menu->addMenu("Help");
        menu->addMenuItem("About");
        gui.add(menu);

      /*  auto tabs = tgui::Tabs::create();
        tabs->setTabHeight(30);
        tabs->setPosition(70, 40);
        tabs->add("Tab - 1");
        tabs->add("Tab - 2");
        tabs->add("Tab - 3");
        gui.add(tabs);*/

        //auto label = tgui::Label::create();
        ////label->setRenderer(theme.getRenderer("Label"));
        //label->setText("This is a label.\nAnd these are radio buttons:");
        //label->setPosition(10, 90);
        //label->setTextSize(18);
        //gui.add(label);

     //   auto radioButton = tgui::RadioButton::create();
     ////   radioButton->setRenderer(theme.getRenderer("RadioButton"));
     //   radioButton->setPosition(20, 140);
     //   radioButton->setText("Yep!");
     //   radioButton->setSize(25, 25);
     //   gui.add(radioButton);

      //  auto editBox = tgui::EditBox::create();
      ////  editBox->setRenderer(theme.getRenderer("EditBox"));
      //  editBox->setSize(200, 25);
      //  editBox->setTextSize(18);
      //  editBox->setPosition(10, 270);
      //  editBox->setDefaultText("Game Object");
      //  gui.add(editBox);

      //  auto listBox = tgui::ListBox::create();
      ////  listBox->setRenderer(theme.getRenderer("ListBox"));
      //  listBox->setSize(250, 120);
      //  listBox->setItemHeight(24);
      //  listBox->setPosition(10, 340);
      //  listBox->addItem("Item 1");
      //  listBox->addItem("Item 2");
      //  listBox->addItem("Item 3");
      //  gui.add(listBox);


    //    auto progressBar = tgui::ProgressBar::create();
    // //   progressBar->setRenderer(theme.getRenderer("ProgressBar"));
    //    progressBar->setPosition(10, 500);
    //    progressBar->setSize(200, 20);
    //    progressBar->setValue(50);
    //    gui.add(progressBar);


    //    auto slider = tgui::Slider::create();
    ////    slider->setRenderer(theme.getRenderer("Slider"));
    //    slider->setPosition(10, 560);
    //    slider->setSize(200, 18);
    //    slider->setValue(4);
    //    gui.add(slider);

    //    auto scrollbar = tgui::Scrollbar::create();
    ////    scrollbar->setRenderer(theme.getRenderer("Scrollbar"));
    //    scrollbar->setPosition(380, 40);
    //    scrollbar->setSize(18, 540);
    //    scrollbar->setMaximum(100);
    //    scrollbar->setViewportSize(70);
    //    gui.add(scrollbar);



      //  auto comboBox = tgui::ComboBox::create();
      ////  comboBox->setRenderer(theme.getRenderer("ComboBox"));
      //  comboBox->setSize(120, 21);
      //  comboBox->setPosition(420, 40);
      //  comboBox->addItem("Item 1");
      //  comboBox->addItem("Item 2");
      //  comboBox->addItem("Item 3");
      //  comboBox->setSelectedItem("Item 2");
      //  gui.add(comboBox);


     //   auto button = tgui::Button::create();
     ////   button->setRenderer(theme.getRenderer("Button"));
     //   button->setPosition(75, 70);
     //   button->setText("OK");
     //   button->setSize(100, 30);
     //   button->connect("pressed", [=]() { child->setVisible(false); });
     //   child->add(button);

    //    auto checkbox = tgui::CheckBox::create();
    //  //  checkbox->setRenderer(theme.getRenderer("CheckBox"));
    //    checkbox->setPosition(420, 240);
    //    checkbox->setText("Ok, I got it");
    //    checkbox->setSize(25, 25);
    //    gui.add(checkbox);


    //    auto chatbox = tgui::ChatBox::create();
    //   // chatbox->setRenderer(theme.getRenderer("ChatBox"));
    //    chatbox->setSize(300, 100);
    //    chatbox->setTextSize(18);
    //    chatbox->setPosition(420, 310);
    //    chatbox->setLinesStartFromTop();
    //    chatbox->addLine("texus: Hey, this is TGUI!", sf::Color::Green);
    //    chatbox->addLine("Me: Looks awesome! ;)", sf::Color::Yellow);
    //    chatbox->addLine("texus: Thanks! :)", sf::Color::Green);
    //    chatbox->addLine("Me: The widgets rock ^^", sf::Color::Yellow);
    //    gui.add(chatbox);

    /*    sf::Texture texture;
        sf::Sprite  sprite;
        texture.loadFromFile("../../../Assets/Images/NeZhas_Logo.png");
        sprite.setTexture(texture);
        sprite.setScale(200.f / texture.getSize().x, 140.f / texture.getSize().y);

        auto canvas = tgui::Canvas::create({ 200, 140 });
        canvas->setPosition(0, 0);
        canvas->clear();
        canvas->draw(sprite);
        canvas->display();
        gui.add(canvas);*/

    }
    catch (const tgui::Exception & e)
    {
        std::cerr << "TGUI Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
