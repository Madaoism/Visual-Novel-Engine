#pragma once
#include "ScriptCommand.h"

class DelayCommand : public ScriptCommand
{
public:

	DelayCommand(std::vector<std::string> args);
	~DelayCommand();

	// serialize the file
	DelayCommand(ifstream& savefile);
	void serialize(ofstream& savefile) const override;

	void execute(ScriptLine* scriptLine);
	void skipUpdate();
	void update(float delta_t);

private:

	std::string objectTypeName;
	std::string flag;
		
	float time;
	float currentTime = 0;
	bool finishedTime = false;

	int animationType;

	int objectType;

	const static int ANIMATION_NONE = 0;

	const static int OBJECT_TIME = 0;
};