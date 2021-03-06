#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "Utility.h"
#include "Global.h"
using namespace std;

class ItemImage : public sf::Drawable{
protected:

	// transformation values
	float xPos, yPos;
	float xScale, yScale;
	float rotationDegree;
	bool loaded;

	// for fading
	bool fading;
	float duration;
	float finalAlpha = 255.f;
	string nextExpression;	
	sf::Color nextColor;
	sf::Texture nextTexture;
	sf::Sprite nextSprite;
	float nextXPos, nextYPos;
	
	// name and expression of the character
	string name;
	string expression;

	// texture options
	float alpha = 255.f;
	sf::Color color;
	sf::Texture texture;
	sf::Sprite sprite;

	// shader variables
	std::map<std::string, float> uniformParams;
	sf::Shader shader;
	bool hasShader = false;
	std::string fragShaderPath, vertShaderPath;

	// helper functions
	void setImage();
	std::string getImagePath(const std::string& name, const std::string& expression) const;

public:
	ItemImage(string name, string expression, float xPos, float yPos);
	ItemImage(ifstream& file); // deserialize constructor

	void setAlpha(float alpha);
	void addAlpha(float alphaOffset);

	void move(float xOffset, float yOffset);
	void rotate(bool clockwise, float angle_degree);
	void scale(float xOffset, float yOffset, float xPos = 0, float yPos = 0);

	void setPosition(float xPos, float yPos);
	void setRotation(bool clockwise, float angle_degree);
	void setScale(float xScale, float yScale, float xPos = 0, float yPos = 0);
	sf::Vector2f getScale() const;

	void changeExpression(string expression, float time=0);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float delta_t);

	bool isLoaded() const;
	bool isFading() const;

	std::string getName() const;
	std::string getExpression() const;
	float getAlpha() const;
	sf::FloatRect getLocalBoundary() const;
	sf::FloatRect getGlobalBoundary() const;

	void setFragShader(string src);
	void setVertShader(string src);
	void tickShader(bool isTrue);
	void setShaderParam(std::string uniform, float shaderParam);
	float getShaderParam(std::string uniform) const;

	bool shouldUseShader() const { return hasShader; }
	sf::Shader* getShader() { return &shader; }

	void serialize(ofstream& savefile) const;
};
