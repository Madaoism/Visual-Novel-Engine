#include "DisplayCommand.h"

DisplayCommand::DisplayCommand(std::vector<std::string> args)
	: ScriptCommand(args)
{
	// checking if the first argument is show
	if (UTILITY->toLower(args[COLUMN_ACTION]) != "display")
	{
		LOGGER->Log("ShowCommand", "Invalid Command Input");
		valid = false;
		return;
	}

	if (args.size() < 5)
	{
		LOGGER->Log("DisplayCommand", "Too few arguments");
		valid = false;
		return;
	}

	// parse the arguments
	objectTypeName = UTILITY->toLower(args[COLUMN_OBJECT]);	// column 2 : object type character or background
	flag = UTILITY->toLower(args[COLUMN_FLAG]);				// column 3 : flag

	if (objectTypeName == "line" || objectTypeName == "l" || objectTypeName == "")
	{
		objectType = OBJECT_LINE;
	}
	else if (objectTypeName == "choice" || objectTypeName == "c")
	{
		objectType = OBJECT_CHOICE;
	}
	else
	{
		string err = "Invalid Object Type: " + objectTypeName;
		LOGGER->Log("DisplayCommand", err);
		valid = false;
		return;
	}

	// parse the flag
	if (flag == "none" || flag == "n" || flag == "" || flag == "default")
	{
		animationType = ANIMATION_NONE;
	}
	else if (flag == "exclaimation" || flag == "e" || flag == "ex")
	{
		animationType = ANIMATION_EXCLAIMATION;
	}
	else if (flag == "gorey" || flag == "g")
	{
		animationType = ANIMATION_GOREY;
	}
	else if (flag == "instant" || flag == "i")
	{
		animationType = ANIMATION_INSTANT;
	}
	else
	{
		string err = "Invalid Flag: " + flag;
		LOGGER->Log("DisplayCommand", err);
		valid = false;
		return;
	}

	displayName = args[COLUMN_ARG1];		// column 4 : character name, also work as num of choices

	if (objectType == OBJECT_LINE)
	{
		for (int i = COLUMN_ARG2; i < COLUMN_ARG7; i++)
		{
			if (args[i].empty()) break;

			displayLines.push_back(args[i]);
		}
	}
	else if (objectType == OBJECT_CHOICE)
	{
		int numChoices = 0;
		try 
		{
			numChoices = stoi(displayName);
		}
		catch (exception e)
		{
			LOGGER->Log("DisplayCommand", "Invalid Number of Choices");
			valid = false;
			return;
		}

		bool choice = false;
		for (int i = COLUMN_ARG2; i < COLUMN_ARG2 + 2 * numChoices; i++)
		{
			if (choice)
			{
				displayLines.push_back(args[i]);
			}
			else
			{
				sceneLabels.push_back(args[i]);
			}
			choice = !choice;
		}
	}

	wait = true;
	done = false;
	valid = true;
	currentLine = "";
	timer = 0;
	currentLineIndex = 0;
	currentCharIndex = 0;

	if (animationType == ANIMATION_INSTANT)
	{
		for (string s : displayLines)
		{
			currentLine += s;
		}
		currentLineIndex = displayLines.size() - 1;
		currentCharIndex = displayLines[currentLineIndex].length() - 1;
	}
}

DisplayCommand::~DisplayCommand()
{
}

void DisplayCommand::execute(ScriptLine * scriptLine)
{
	if (objectType == OBJECT_LINE)
	{
		scriptLine->setDialogue(displayName, currentLine);
	}
	else if (objectType == OBJECT_CHOICE)
	{

	}
}

void DisplayCommand::skipUpdate()
{
	if (objectType == OBJECT_LINE && animationType == ANIMATION_NONE)
	{
		if (currentLineIndex < displayLines.size())
		{
			if (currentCharIndex < displayLines[currentLineIndex].length() - 1)
			{
				currentCharIndex = displayLines[currentLineIndex].length() - 1;
			}
			else
			{
				currentLineIndex++;
				currentCharIndex = 0;
			}

			if (currentLineIndex < displayLines.size())
			{
				currentLine = assembleString(displayLines, currentLineIndex, currentCharIndex);
			}
			else
			{
				wait = false;
				done = true;
			}
		}
	}
	else
	{
		wait = false;
		done = true;
	}
}

void DisplayCommand::update(float delta_t)
{
	if (objectType == OBJECT_LINE && animationType == ANIMATION_NONE)
	{

		if (currentLineIndex >= displayLines.size() || currentCharIndex >= displayLines[currentLineIndex].length() - 1)
		{
			return;
		}

		float interval;
		if (GLOBAL->autoMode)
		{
			if (CONFIG->autoTextSpeed >= 1.0f)
			{
				currentCharIndex = displayLines[currentLineIndex].length() - 1;
				currentLine += displayLines[currentLineIndex];
				return;
			}

			interval = 1.0f / (CONFIG->autoTextSpeed) - 1.0f;
		}
		else
		{
			if (CONFIG->manualTextSpeed >= 1.0f)
			{
				currentCharIndex = displayLines[currentLineIndex].length() - 1;
				currentLine += displayLines[currentLineIndex];
				return;
			}

			interval = 1.0f / (CONFIG->manualTextSpeed) - 1.0f;
		}

		interval *= .1f;

		timer += delta_t;
		if (timer > interval)
		{
			int numChars = (int)(timer / interval);
			timer -= numChars * interval;
			currentCharIndex += numChars;	// note currentCharIndex might exceed actual length

			currentLine = assembleString(displayLines, currentLineIndex, currentCharIndex);
		}
	}
}

std::string DisplayCommand::assembleString(const std::vector<std::string>& lines, int lineIndex, int charIndex)
{
	std::string str = "";
	for (int i = 0; i < lineIndex; i++)
	{
		str += lines[i];
		str += " ";
	}
	str += lines[lineIndex].substr(0, charIndex + 1);
	return str;
}
