#include "DrawMainButton.h"

void DrawMainButton::init()
{
	configButton = new MainButton(GLOBAL->AssetRoot + "Config55x100.png", "", "", 1574.0f, 838.0f, 0, 0, 0, 0, 55, 50, 0, 50, 55, 50);
	configButton->load();
	buttons.push_back(configButton);

	exitButton = new MainButton(GLOBAL->AssetRoot + "Exit55x112.png", "", "", 1575.0f, 903.0f, 0, 0, 0, 0, 55, 56, 0, 56, 55, 56);
	exitButton->load();
	buttons.push_back(exitButton);

	QSButton = new MainButton(GLOBAL->AssetRoot + "QuickSave53x106.png", "", "", 1437.0f, 900.0f, 0, 0, 0, 0, 53, 53, 0, 53, 53, 53);
	QSButton->load();
	buttons.push_back(QSButton);

	QLButton = new MainButton(GLOBAL->AssetRoot + "QuickLoad64x104.png", "", "", 1507.0f, 900.0f, 0, 0, 0, 0, 64, 52, 0, 52, 64, 52);
	QLButton->load();
	buttons.push_back(QLButton);

	saveButton = new MainButton(GLOBAL->AssetRoot + "Save53x102.png", "", "", 1302.0f, 900.0f, 0, 0, 0, 0, 53, 51, 0, 51, 53, 51);
	saveButton->load();
	buttons.push_back(saveButton);

	loadButton = new MainButton(GLOBAL->AssetRoot + "Load63x104.png", "", "", 1367.0f, 900.0f, 0, 0, 0, 0, 63, 52, 0, 52, 63, 52);
	loadButton->load();
	buttons.push_back(loadButton);

	logButton = new MainButton(GLOBAL->AssetRoot + "Log64X126.png", "", "", 1232.0f, 905.0f, 0, 0, 0, 0, 64, 63, 0, 63, 64, 63);
	logButton->load();
	buttons.push_back(logButton);

	autoButton = new MainButton(GLOBAL->AssetRoot + "Auto72x88.png", "", "", 1157.0f, 898.0f, 0, 0, 0, 0, 72, 44, 0, 44, 72, 44);
	autoButton->load();
	buttons.push_back(autoButton);
	autoButton->highlightColor = sf::Color(210, 100, 240, 255);

	skipButton = new MainButton(GLOBAL->AssetRoot + "Skip69x98.png", "", "", 1085.0f, 902.0f, 0, 0, 0, 0, 69, 49, 0, 49, 69, 49);
	skipButton->load();
	buttons.push_back(skipButton);
	skipButton->highlightColor = sf::Color(255, 60, 60, 255);

	closeButton = new MainButton(GLOBAL->AssetRoot + "CloseButton34x70.png", "", "", 1520.0f, 735.0f, 0, 0, 0, 0, 34, 35, 0, 35, 34, 35);
	closeButton->load();
	buttons.push_back(closeButton);
}

void DrawMainButton::handleInput(sf::Event & e, sf::RenderWindow & window)
{
	for (MainButton* button : buttons)
	{
		button->handleInput(e, window);
	}

	if (configButton->isClicked(true))
	{
		configButtonClicked = true;
	}
	if (exitButton->isClicked(true))
	{
		exitButtonClicked = true;
	}
	if (QLButton->isClicked(true))
	{
		quickLoadButtonClicked = true;
	}
	if (loadButton->isClicked(true))
	{
		loadButtonClicked = true;
	}
	if (QSButton->isClicked(true))
	{
		quickSaveButtonClicked = true;
	}
	if (saveButton->isClicked(true))
	{
		saveButtonClicked = true;
	}
	if (logButton->isClicked(true))
	{
		logButtonClicked = true;
	}
	if (autoButton->isClicked(true))
	{
		autoButtonClicked = true;
	}
	if (skipButton->isClicked(true))
	{
		skipButtonClicked = true;
	}
	if (closeButton->isClicked(true))
	{
		closeButtonClicked = true;
	}
}

void DrawMainButton::render(sf::RenderWindow & window)
{
	for (MainButton* button : buttons)
	{
		window.draw(*button);
	}
}

void DrawMainButton::update(float delta_t)
{
	for (MainButton* button : buttons)
	{
		button->update(delta_t);
	}
}

void DrawMainButton::cleanup()
{
	for (MainButton* button : buttons)
	{
		delete button;
	}
	buttons.clear();
}

void DrawMainButton::setAlpha(float a)
{
	for (MainButton* button : buttons)
	{
		button->setAlpha(a);
	}

}

void DrawMainButton::addAlpha(float offset)
{
	for (MainButton* button : buttons)
	{
		button->addAlpha(offset);
	}
}

void DrawMainButton::highlightAutoButton(bool h)
{
	autoButton->highlight = h;
}

void DrawMainButton::highlightSkipButton(bool h)
{
	skipButton->highlight = h;

}

DrawMainButton::DrawMainButton()
{
	init();
}

DrawMainButton::~DrawMainButton()
{
	cleanup();
}

