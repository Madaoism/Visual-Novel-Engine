#pragma once
#include <string>

#include "GameState.h"
#include "Button.h"
#include "ScriptManager.h"
#include "LoadfileImage.h"
#include "SavedataUtility.h"
#include "MainButton.h"
#include "DarkenButton.h"

class LoadState : public GameState
{
public:
	LoadState();
	~LoadState();

	// handle user inputs (keyboard/gamepad/mouse/etc)
	void handleInput(sf::Event& e, sf::RenderWindow& window);

	// render the window display: all rendering functions (like drawing images, fonts, etc. should be here)
	void render(sf::RenderWindow& window);

	// all non-rendering game logics/mechanics should be implemented here
	void update(float delta_t);

	// initialize instance
	void init();

	void cleanup();

	const static int INDEX_SAVE_1 = 0;
	const static int INDEX_SAVE_2 = 1;
	const static int INDEX_SAVE_3 = 2;
	const static int INDEX_SAVE_4 = 3;
	const static int INDEX_SAVE_5 = 4;
	const static int INDEX_SAVE_6 = 5;
	const static int INDEX_SAVE_7 = 6;
	const static int INDEX_SAVE_8 = 7;

private:
	sf::Texture saveTexture;
	sf::Sprite saveBackground;

	MainButton * menuButton;
	MainButton * returnButton;
	MainButton * quitButton;

	vector<MainButton*> buttons;

	DarkenButton * qButton;
	DarkenButton * upArrow;
	DarkenButton * oneButton;
	DarkenButton * twoButton;
	DarkenButton * threeButton;
	DarkenButton * fourButton;
	DarkenButton * fiveButton;
	DarkenButton * sixButton;
	DarkenButton * sevenButton;
	DarkenButton * eightButton;
	DarkenButton * downArrow;


	unsigned int currentPageNumber = 0;
	const unsigned int savePerPage = 8;


	std::vector<LoadfileImage *> savefileImages;

	ScriptManager* scriptManager;

	void loadSavesByPage(int pageNumber);

	int currentAlpha, endAlpha;
	bool exitGame;
	sf::RectangleShape rectangle;
	sf::Clock clock;
};