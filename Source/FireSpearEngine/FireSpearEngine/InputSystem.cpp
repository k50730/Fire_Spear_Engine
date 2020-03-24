#include "InputSystem.h"

InputSystem::InputSystem(GameObjectManager* g)
{
	gameObjectManager = g;
}

InputSystem::~InputSystem()
{
}

void InputSystem::Instantiate()
{
}

void InputSystem::Awake()
{
}

void InputSystem::Start()
{
}

void InputSystem::Update(sf::Time dt)
{
}

bool InputSystem::GetKeyDown(const char* Key)
{
#pragma region KeyCode
    static std::map<std::string, sf::Keyboard::Key> KeyCode {
        {"None", sf::Keyboard::Unknown},
        { "A", sf::Keyboard::A },
        { "B", sf::Keyboard::B },
        { "C", sf::Keyboard::C },
        { "D", sf::Keyboard::D },
        { "E", sf::Keyboard::E },
        { "F", sf::Keyboard::F },
        { "G", sf::Keyboard::G },
        { "H", sf::Keyboard::H },
        { "I", sf::Keyboard::I },
        { "J", sf::Keyboard::J },
        { "K", sf::Keyboard::K },
        { "L", sf::Keyboard::L },
        { "M", sf::Keyboard::M },
        { "N", sf::Keyboard::N },
        { "O", sf::Keyboard::O },
        { "P", sf::Keyboard::P },
        { "Q", sf::Keyboard::Q },
        { "R", sf::Keyboard::R },
        { "S", sf::Keyboard::S },
        { "T", sf::Keyboard::T },
        { "U", sf::Keyboard::U },
        { "V", sf::Keyboard::V },
        { "W", sf::Keyboard::W },
        { "X", sf::Keyboard::X },
        { "Y", sf::Keyboard::Y },
        { "Z", sf::Keyboard::Z },
        { "0", sf::Keyboard::Num0 },
        { "1", sf::Keyboard::Num1 },
        { "2", sf::Keyboard::Num2 },
        { "3", sf::Keyboard::Num3 },
        { "4", sf::Keyboard::Num4 },
        { "5", sf::Keyboard::Num5 },
        { "6", sf::Keyboard::Num6 },
        { "7", sf::Keyboard::Num7 },
        { "8", sf::Keyboard::Num8 },
        { "9", sf::Keyboard::Num9 },
        { "ESC", sf::Keyboard::Escape },
        { "LCtrl", sf::Keyboard::LControl },
        { "LShift", sf::Keyboard::LShift },
        { "LAlt", sf::Keyboard::LAlt },
        { "LSystem", sf::Keyboard::LSystem },
        { "RCtrl", sf::Keyboard::RControl },
        { "RShift", sf::Keyboard::RShift },
        { "RAlt", sf::Keyboard::RAlt },
        { "RSystem", sf::Keyboard::RSystem },
        { "Menu", sf::Keyboard::Menu },
        { "[", sf::Keyboard::LBracket },
        { "]", sf::Keyboard::RBracket },
        { ";", sf::Keyboard::Semicolon},
        { ",", sf::Keyboard::Comma},
        { ".", sf::Keyboard::Period},
        { "'", sf::Keyboard::Quote},
        { "Slash", sf::Keyboard::Slash},
        { "Backslash", sf::Keyboard::Backslash},
        { "~", sf::Keyboard::Tilde},
        { "=", sf::Keyboard::Equal},
        { "Hyphen", sf::Keyboard::Hyphen}, //conflict with subtract
        { " ", sf::Keyboard::Space},
        { "Enter", sf::Keyboard::Enter},
        { "Backspace", sf::Keyboard::Backspace},
        { "Tab", sf::Keyboard::Tab},
        { "PageUp", sf::Keyboard::PageUp},
        { "PageDown", sf::Keyboard::PageDown},
        { "End", sf::Keyboard::End},
        { "Home", sf::Keyboard::Home},
        { "Insert", sf::Keyboard::Insert},
        { "Delete", sf::Keyboard::Delete},
        { "+", sf::Keyboard::Add},
        { "-", sf::Keyboard::Subtract},
        { "*", sf::Keyboard::Multiply},
        { "/", sf::Keyboard::Divide},
        { "Left", sf::Keyboard::Left},
        { "Right", sf::Keyboard::Right},
        { "Up", sf::Keyboard::Up},
        { "Down", sf::Keyboard::Down},
        { "Numpad0", sf::Keyboard::Numpad0},
        { "Numpad1", sf::Keyboard::Numpad1},
        { "Numpad2", sf::Keyboard::Numpad2},
        { "Numpad3", sf::Keyboard::Numpad3},
        { "Numpad4", sf::Keyboard::Numpad4},
        { "Numpad5", sf::Keyboard::Numpad5},
        { "Numpad6", sf::Keyboard::Numpad6},
        { "Numpad7", sf::Keyboard::Numpad7},
        { "Numpad8", sf::Keyboard::Numpad8},
        { "Numpad9", sf::Keyboard::Numpad9},
        { "F1", sf::Keyboard::F1},
        { "F2", sf::Keyboard::F2},
        { "F3", sf::Keyboard::F3},
        { "F4", sf::Keyboard::F4},
        { "F5", sf::Keyboard::F5},
        { "F6", sf::Keyboard::F6},
        { "F7", sf::Keyboard::F7},
        { "F8", sf::Keyboard::F8},
        { "F9", sf::Keyboard::F9},
        { "F10", sf::Keyboard::F10},
        { "F11", sf::Keyboard::F11},
        { "F12", sf::Keyboard::F12},
        { "F13", sf::Keyboard::F13},
        { "F14", sf::Keyboard::F14},
        { "F15", sf::Keyboard::F15},
        { "Pause", sf::Keyboard::Pause}
    };
#pragma endregion

    auto k = KeyCode.find(Key);
    if (k != std::end(KeyCode))
    {
        return sf::Keyboard::isKeyPressed(k->second);
    }
}
