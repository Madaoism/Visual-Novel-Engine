#include "UnhideCommand.h"

UnhideCommand::UnhideCommand(std::vector<std::string> args)
	:ScriptCommand(args)
{
	// checking if the first argument is show
	if (UTILITY->toLower(args[COLUMN_ACTION]) != "unhide")
	{
		LOGGER->Log("UnhideCommand", "Invalid Command Input");
		valid = false;
		return;
	}

	// parse the arguments
	objectTypeName = UTILITY->toLower(args[COLUMN_OBJECT]);	// column 2 : object type character or background
	flag = UTILITY->toLower(args[COLUMN_FLAG]);				// column 3 : flag

	// optional argument: time
	time = 0;
	if (args.size() > COLUMN_ARG1)
	{
		try {
			time = std::stof(args[COLUMN_ARG1]); // column 8: time it should take to full finish the fade
		}
		catch (exception e)
		{
			LOGGER->Log("PlayCommand", "Failed to convert time into float");
		}
	}

	// check the flag validity
	if (flag == "" || flag == "none" || time <= 0)
	{
		wait = false;
		animationType = ANIMATION_NONE;
		currentAlpha = finalAlpha;
		time = 0;
	}
	else if (flag == "fadeinwait" || flag == "fw")
	{
		wait = true;
		animationType = ANIMATION_FADEIN;
	}
	else if (flag == "fadein" || flag == "f")
	{
		wait = false;
		animationType = ANIMATION_FADEIN;
	}
	else
	{
		LOGGER->Log("UnhideCommand", "Invalid Flag");
		valid = false;
		return;
	}

	// check object type validity
	if (objectTypeName == "textbox" || objectTypeName == "tb" || objectTypeName == "t")
	{
		objectType = OBJECT_TEXTBOX;
	}
	else
	{
		valid = false;
		LOGGER->Log("UnhideCommand", "Invalid Object Type");
		return;
	}
}

UnhideCommand::~UnhideCommand()
{
}

void UnhideCommand::execute(ScriptLine * scriptLine)
{
	if (valid)
	{
		scriptLine->hideTextbox = false;

		if (objectType == OBJECT_TEXTBOX)
		{			
			scriptLine->setTextboxAlpha(currentAlpha);
		}

		if (doneAnimation)
		{
			done = true;
			wait = false;
			scriptLine->setTextboxAlpha(255.f);
		}
	}
	else
	{
		done = true;
		wait = false;
	}
}

void UnhideCommand::skipUpdate()
{
	currentAlpha = finalAlpha;
	doneAnimation = true;
}

void UnhideCommand::update(float delta_t)
{
	if (valid && animationType == ANIMATION_FADEIN)
	{
		float offset = delta_t / time * 255.f;
		currentAlpha += offset;

		if (currentAlpha >= finalAlpha)
		{
			currentAlpha = finalAlpha;
			doneAnimation = true;
		}
	}
	else
	{
		doneAnimation = true;
		currentAlpha = finalAlpha;
	}
}
