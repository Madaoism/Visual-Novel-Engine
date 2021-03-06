#include "HideCommand.h"

HideCommand::HideCommand(std::vector<std::string> args)
	:ScriptCommand(args)
{
	// checking if the first argument is show
	if (UTILITY->toLower(args[COLUMN_ACTION]) != "hide")
	{
		LOGGER->Log("HideCommand", "Invalid Command Input");
		valid = false;
		return;
	}
	commandType = COMMAND_HIDE;

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
			//LOGGER->Log("HideCommand", "Failed to convert time into float");
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
	else if (flag == "fadeoutwait" || flag == "fw")
	{
		wait = true;
		animationType = ANIMATION_FADEOUT;
	}
	else if (flag == "fadeout" || flag == "f")
	{
		wait = false;
		animationType = ANIMATION_FADEOUT;
	}
	else
	{
		LOGGER->Log("HideCommand", "Invalid Flag");
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
		LOGGER->Log("HideCommand", "Invalid Object Type");
		return;
	}
}

HideCommand::~HideCommand()
{
}

HideCommand::HideCommand(ifstream & savefile)
	:ScriptCommand(savefile)
{
	try
	{
		objectTypeName = UTILITY->readFromBinaryFile(savefile);
		flag = UTILITY->readFromBinaryFile(savefile);

		savefile.read(reinterpret_cast<char *> (&animationType), sizeof(animationType));
		savefile.read(reinterpret_cast<char *> (&objectType), sizeof(objectType));

		savefile.read(reinterpret_cast<char *> (&currentAlpha), sizeof(currentAlpha));
		savefile.read(reinterpret_cast<char *> (&finalAlpha), sizeof(finalAlpha));
		savefile.read(reinterpret_cast<char *> (&doneAnimation), sizeof(doneAnimation));
		savefile.read(reinterpret_cast<char *> (&time), sizeof(time));
	}
	catch (exception e)
	{
		LOGGER->Log("HideCommand", "Unable to read Hide command from savedata");
		valid = false;
		return;
	}
}

void HideCommand::serialize(ofstream & savefile) const
{
	ScriptCommand::serialize(savefile);

	UTILITY->writeToBinaryFile(savefile, objectTypeName);
	UTILITY->writeToBinaryFile(savefile, flag);

	savefile.write(reinterpret_cast<const char *> (&animationType), sizeof(animationType));
	savefile.write(reinterpret_cast<const char *> (&objectType), sizeof(objectType));

	savefile.write(reinterpret_cast<const char *> (&currentAlpha), sizeof(currentAlpha));
	savefile.write(reinterpret_cast<const char *> (&finalAlpha), sizeof(finalAlpha));
	savefile.write(reinterpret_cast<const char *> (&doneAnimation), sizeof(doneAnimation));
	savefile.write(reinterpret_cast<const char *> (&time), sizeof(time));
}

void HideCommand::execute(ScriptLine * scriptLine)
{
	if (valid)
	{
		if (objectType == OBJECT_TEXTBOX)
		{
			scriptLine->setTextboxAlpha(currentAlpha);
		}

		if (doneAnimation)
		{
			done = true;
			wait = false;
			scriptLine->setTextboxAlpha(255.f);
			scriptLine->hideTextbox = true;
		}
	}
	else
	{
		done = true;
		wait = false;
	}
}

void HideCommand::skipUpdate()
{
	currentAlpha = finalAlpha;
	doneAnimation = true;
}

void HideCommand::update(float delta_t)
{
	if (valid && animationType == ANIMATION_FADEOUT)
	{
		float offset = delta_t / time * 255.f;
		currentAlpha -= offset;
		
		if (currentAlpha < finalAlpha)
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
