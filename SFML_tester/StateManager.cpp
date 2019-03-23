#include "StateManager.h"
#include "InitState.h"
#include "MenuState.h"
#include "NewGameState.h"
#include "MainState.h"
#include "SaveState.h"
#include "ExitState.h"
#include "SettingsState.h"
#include "LoadState.h"
#include "LoadingScreenState.h"

StateManager::~StateManager()
{
	if (currentState != nullptr)
		delete currentState;
}

StateManager::StateManager()
{
	init();
}

void StateManager::handleInput(sf::Event& e, sf::RenderWindow& window)
{
	currentState->handleInput(e, window);
}

void StateManager::render(sf::RenderWindow & window)
{
	currentState->render(window);
}

void StateManager::update(float delta_t)
{
	currentState->update(delta_t);
	manageStates();
}

void StateManager::init()
{
	currentState = new InitState();
}

void StateManager::manageStates()
{
	if (currentState->shouldChangeState)
	{
		switch (currentState->nextState)
		{
		case GameState::STATE_MENU:
			if (currentState->myState == GameState::STATE_INIT)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new MenuState();
			}
			else if (currentState->myState == GameState::STATE_MAIN)
			{
				LOGGER->Log("StateManager", "Switching to menu state from main");
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new MenuState();
			}
			else if (currentState->myState == GameState::STATE_NEW_GAME)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new MenuState();
			}
			else if (currentState->myState == GameState::STATE_LOAD)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new MenuState();
			}
			break;

		case GameState::STATE_INIT:
			prevStates.push(currentState);
			clearPrevStates();
			currentState = new InitState();
			break;

		//case GameState::STATE_LOADING_SCREEN:
		//	prevStates.push(currentState);
		//	currentState->shouldChangeState = false;
		//	currentState = new LoadingScreenState();
		//	break;

		case GameState::STATE_NEW_GAME:
			if (currentState->myState == GameState::STATE_MENU)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new NewGameState();
			}
			else if (currentState->myState == GameState::STATE_LOAD)
			{
				// push currentState into the stack so that we can delete that too
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new NewGameState();
			}
			break;

		case GameState::STATE_MAIN:
			if (currentState->myState == GameState::STATE_NEW_GAME)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new MainState(GLOBAL->playerName);
			}
			else if (currentState->myState == GameState::STATE_LOAD)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new MainState();
			}
			break;

		case GameState::STATE_SAVE:
			if (currentState->myState == GameState::STATE_MAIN)
			{
				prevStates.push(currentState);
				currentState->shouldChangeState = false;

				currentState = new SaveState( GLOBAL->scriptManagerPtr, 
					UTILITY->getScreenshot(*(GLOBAL->windowPtr), 5, 5 ) );
			}
			break;

		case GameState::STATE_LOAD:		//Check
			if (currentState->myState == GameState::STATE_MENU)
			{
				prevStates.push(currentState);
				currentState->shouldChangeState = false;
				currentState = new LoadState();
			}
			else if (currentState->myState == GameState::STATE_MAIN)
			{
				prevStates.push(currentState);
				currentState->shouldChangeState = false;
				currentState = new LoadState();
			}
			break;

		case GameState::STATE_EXIT:
			if (currentState->myState == GameState::STATE_MENU)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new ExitState();
			}
			else if (currentState->myState == GameState::STATE_MAIN)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new ExitState();
			}
			else if (currentState->myState == GameState::STATE_LOAD)
			{
				prevStates.push(currentState);
				clearPrevStates();
				currentState = new ExitState();
			}
			break;

		case GameState::STATE_CONFIG:
			if (currentState->myState == GameState::STATE_MENU)
			{
				prevStates.push(currentState);
				currentState->shouldChangeState = false;
				currentState = new SettingsState();
			}
			else if (currentState->myState == GameState::STATE_MAIN)
			{
				prevStates.push(currentState);
				currentState->shouldChangeState = false;
				currentState = new SettingsState();
			}
			break;

		case GameState::STATE_BACK:
			currentState->cleanup();
			delete currentState;
			currentState = prevStates.top();
			prevStates.pop();
			break;
		}
		//currentState->init();
	}
}

void StateManager::clearPrevStates()
{
	while (prevStates.size() > 0)
	{
		GameState * temp = (prevStates.top());
		prevStates.pop();
		temp->cleanup();
		delete temp;
	}
}

