#pragma once
#include "GameState.h"
#include "Logger.h"

class ExitState : public GameState
{
public:
	void handleInput(sf::Event& e, sf::RenderWindow& window);		// handle user inputs (keyboard/gamepad/mouse/etc)
	void render(sf::RenderWindow& window);							// render the window display: all rendering functions (like drawing images, fonts, etc. should be here)
	void update(float delta_t);										// all non-rendering game logics/mechanics should be implemented here
	void init();
	void cleanup();

	ExitState();
	~ExitState();
};
