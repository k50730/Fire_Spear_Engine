#pragma once
#include "TGUI/TGUI.hpp"
#include <iostream>

class LevelEditor
{ 
private:

	static void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);
	void loadWidgets(tgui::Gui& gui);

public:

	int run();
};

