#pragma once
#include <stack>
#include "Global.h"
#include "GameState.h"

class StateManager 
{
public:

	~StateManager();
	StateManager();

	void handleInput(sf::Event& e, sf::RenderWindow& window);			// handle user inputs (keyboard/gamepad/mouse/etc)
	void render(sf::RenderWindow& window);	// render the window display: all rendering functions (like drawing images, fonts, etc. should be here)
	void update(float delta_t);							// all non-rendering game logics/mechanics should be implemented here
	void init();

private:
	void manageStates();
	void clearPrevStates();

	GameState * currentState;
	int currentStateCode;

	std::stack<GameState *> prevStates;
};