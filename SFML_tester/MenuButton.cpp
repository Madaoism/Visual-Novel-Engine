#include "MenuButton.h"

bool MenuButton::onLoad()
{
	bool ret = Button::onLoad();
	sf::IntRect rectSourceSprite(startSpriteSheetXPos, startSpriteSheetYPos, endSpriteSheetXPos, endSpriteSheetYPos);
	sprite.setTextureRect(rectSourceSprite);
	scaleMultiply = 1;
	sprite.setOrigin(sf::Vector2f( texWidth / 2, texHeight / 2));
	return ret;
}

void MenuButton::onUpdate(float delta_t)
{
	Button::onUpdate(delta_t);
}

void MenuButton::onDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Button::onDraw(target, states);
}

void MenuButton::onHandleInput(sf::Event & e, sf::RenderWindow & window)
{
	Button::onHandleInput(e, window);

	sf::Vector2f mousePosF = CONFIG->getCursorPosition(window);
	switch (e.type)
	{
		case sf::Event::MouseMoved:
		{
			if (sprite.getGlobalBounds().contains(mousePosF))
			{
				if (clock.getElapsedTime().asMilliseconds() > 100.00f) {
					while (scaleMultiply < 1.015) {
						sprite.setScale(sf::Vector2f((1.0f*scaleMultiply), (1.0f*scaleMultiply)));
						scaleMultiply += 0.005;
					}
					clock.restart();
				}
			}
			else
			{
				sprite.setScale(sf::Vector2f(1.0f, 1.0f));
				scaleMultiply = 1.0;
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (sprite.getGlobalBounds().contains(mousePosF))
				{
					pressed = true;
				}
			}
			break;
		}
		case sf::Event::MouseButtonReleased:
		{			
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (pressed)
				{
					pressed = false;
					clicked = true;
				}
				break;
			}
		}
	}
}

void MenuButton::setSpriteSheetPos(float startX, float startY, float endX, float endY)
{
	startSpriteSheetXPos = startX;
	startSpriteSheetYPos = startY;
	endSpriteSheetXPos = endX;
	endSpriteSheetYPos = endY;
}
