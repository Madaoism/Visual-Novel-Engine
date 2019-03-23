#pragma once
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class GameState {

public:

	// handle user inputs (keyboard/gamepad/mouse/etc)
	virtual void handleInput(sf::Event& e, sf::RenderWindow& window) = 0;		

	// render the window display: all rendering functions (like drawing images, fonts, etc. should be here)
	virtual void render(sf::RenderWindow& window) = 0;	

	// all non-rendering game logics/mechanics should be implemented here
	virtual void update(float delta_t) = 0;		

	// initialize instance
	virtual void init() = 0;

	virtual void cleanup() = 0;

	bool shouldChangeState = false;
	int nextState = -1;
	int myState = -1;

	static const int STATE_INIT = 0;
	static const int STATE_MENU = 1;
	static const int STATE_LOAD = 2;
	static const int STATE_SAVE = 3;
	static const int STATE_CONFIG = 4;
	static const int STATE_NEW_GAME = 5;
	static const int STATE_MAIN = 6;
	static const int STATE_EXIT = 7;

	static const int STATE_BACK = 8;
	static const int STATE_LOADING_SCREEN = 9;
};