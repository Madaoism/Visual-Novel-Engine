#pragma once
#include <ctype.h>
#include <stdio.h>
#include <iostream>

#include "ScriptCommand.h"
#include "Config.h"

class HideCommand : public ScriptCommand
{
public:

	HideCommand(std::vector<std::string> args);
	~HideCommand();

	// serialize the file
	HideCommand(ifstream& savefile);
	void serialize(ofstream& savefile) const override;

	void execute(ScriptLine* scriptLine);
	void skipUpdate();
	void update(float delta_t);

private:

	std::string objectTypeName;
	std::string flag;

	// type of animation
	int animationType;

	// type of object: choice or line
	int objectType;

	float currentAlpha = 255;
	float finalAlpha = 0;
	bool doneAnimation = false;

	float time = 0;

	const static int ANIMATION_FADEOUT = 1;
	const static int ANIMATION_NONE = 0;

	const static int OBJECT_TEXTBOX = 0;

};