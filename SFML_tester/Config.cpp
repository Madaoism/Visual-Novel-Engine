#include "Config.h"
using namespace std;

const string Config::CF_MASTER_VOLUME = "MasterVolume";
const string Config::CF_BGM_VOLUME = "BGMVolume";
const string Config::CF_VOICE_VOLUME = "VoiceVolume";
const string Config::CF_SFX_VOLUME = "SFXVolume";
const string Config::CF_FULLSCREEN = "Fullscreen";
const string Config::CF_MANUAL_TEXT_SPEED = "ManualTextSpeed";
const string Config::CF_AUTO_TEXT_SPEED = "AutoTextSpeed";
const string Config::CF_AUTO_TEXT_WAIT_TIME = "AutoTextWaitTime";
const string Config::CF_TEXT_FADE = "TextFade";
const string Config::CF_SKIP_UNREAD_TEXT = "SkipUnreadText";
const string Config::CF_DISPLAY_TEXT_FONT_NAME = "FontFileName";
const string Config::CF_TEXT_WINDOW_ALPHA = "TextWindowTransparency";
const string Config::CF_WINDOW_WIDTH = "WindowWidth";
const string Config::CF_WINDOW_HEIGHT = "WindowHeight";
const string Config::CF_MENU_ITERATOR = "MenuIteration";
const string Config::CF_STOP_VOICE_NEXT_LINE = "StopVoiceNextLine";
const string Config::CF_STOP_SKIPPING_AT_CHOICE = "StopSkippingAtChoice";
const string Config::CF_SAVE_INIT_PAGE_NUMBER = "SaveInitPageNumber";
const string Config::CF_LOAD_INIT_PAGE_NUMBER = "LoadInitPageNumber";

Config* Config::currentConfig = nullptr;

Config::Config()
{
	init();
}

void Config::initWindowResize(sf::RenderWindow & window,
	int originalWidth, int originalHeight, 
	int windowWidth, int windowHeight)
{
	// set the window zoom to the smaller of the 2 sizes
	float windowZoom = std::max(float(originalWidth) / float(windowWidth), float(originalHeight) / float(windowHeight));

	sf::View defView = window.getView();
	sf::View newView = defView;
	newView.zoom(windowZoom);
	newView.setCenter(originalWidth / 2.0f, originalHeight / 2.0f);
	window.setView(newView);
}

void Config::write(string configFile) 
{
	ofstream myfile(configFile);
	if (myfile.is_open())
	{
		myfile << "### This is the Configuration file for Visual Novel Engine.\n";
		myfile << "### Please avoid editting this file unless you know what you are doing.\n";

		myfile << CF_MASTER_VOLUME << "="  << to_string(masterVolume) << endl;
		myfile << CF_BGM_VOLUME << "="  << to_string(bgmVolume) << endl;
		myfile << CF_VOICE_VOLUME << "="  << to_string(voiceVolume) << endl;
		myfile << CF_SFX_VOLUME << "="  << to_string(sfxVolume) << endl;
		myfile << CF_FULLSCREEN << "="  << to_string(enableFullscreen) << endl;
		myfile << CF_MANUAL_TEXT_SPEED << "="  << to_string(manualTextSpeed) << endl;
		myfile << CF_AUTO_TEXT_SPEED << "="  << to_string(autoTextSpeed) << endl;
		myfile << CF_AUTO_TEXT_WAIT_TIME << "="  << to_string(autoTextWaitTime) << endl;
		myfile << CF_TEXT_FADE << "="  << UTILITY->bool2str(textFade) << endl;
		myfile << CF_SKIP_UNREAD_TEXT << "="  << UTILITY->bool2str(skipUnreadText) << endl;
		myfile << CF_DISPLAY_TEXT_FONT_NAME << "="  << displayTextFontName << endl;
		myfile << CF_TEXT_WINDOW_ALPHA << "="  << to_string(textWindowAlpha) << endl;
		myfile << CF_WINDOW_WIDTH << "=" << to_string(windowWidth) << endl;
		myfile << CF_WINDOW_HEIGHT << "=" << to_string(windowHeight) << endl;
		myfile << CF_MENU_ITERATOR << "=" << to_string(menuIteration) << endl;
		myfile << CF_STOP_VOICE_NEXT_LINE << "=" << UTILITY->bool2str(stopVoiceNextLine) << endl;
		myfile << CF_STOP_SKIPPING_AT_CHOICE << "=" << UTILITY->bool2str(stopSkippingAtChoice) << endl;
		myfile << CF_LOAD_INIT_PAGE_NUMBER << "=" << to_string(loadInitPageNumber) << endl;
		myfile << CF_SAVE_INIT_PAGE_NUMBER << "=" << to_string(saveInitPageNumber) << endl;
		myfile.close();
	}
	else
	{
		string err = "Failed to write to " + configFile;
		LOGGER->Log("Config", err);
	}
}

Config * Config::GetConfig()
{
	if (currentConfig == nullptr) 
	{
		currentConfig = new Config();
	}
	return currentConfig;
}

void Config::Cleanup()
{
	if (currentConfig)
	{
		delete currentConfig;
	}
}

void Config::resetWindowSize(sf::RenderWindow & window)
{
	if (CONFIG->enableFullscreen == FullscreenOpts::fullscreen)
	{
		window.create(sf::VideoMode(CONFIG->getWindowWidth(), CONFIG->getWindowHeight()),
			CONFIG->getTitle(), sf::Style::Default | sf::Style::Fullscreen);
	}
	else if (CONFIG->enableFullscreen == FullscreenOpts::windowed)
	{
		window.create(sf::VideoMode(CONFIG->getWindowWidth(), CONFIG->getWindowHeight()),
			CONFIG->getTitle(), sf::Style::Default & ~sf::Style::Resize);
	}
	else if (CONFIG->enableFullscreen == FullscreenOpts::borderless)
	{
		window.create(sf::VideoMode::getDesktopMode(),
			CONFIG->getTitle(), sf::Style::None);
	}
	initWindowResize(window, CONFIG->defaultWidth, CONFIG->defaultHeight, 
		window.getSize().x, window.getSize().y);
	window.setFramerateLimit(CONFIG->getFps());
}

sf::Vector2f Config::getCursorPosition(sf::RenderWindow & window)
{
	sf::Vector2i mousePos =( sf::Mouse::getPosition(window) );

	return window.mapPixelToCoords(mousePos);
}

void Config::init()
{
	windowWidth = 1600;
	windowHeight = 900;
	windowTitle = "Visual Novel Engine";
	fps = 120;
	masterVolume = 0.8f;
	bgmVolume = 0.8f;
	voiceVolume = 1.0f;
	sfxVolume = 1.0f;
	enableFullscreen = windowed;
	manualTextSpeed = 0.8f;
	autoTextSpeed = 0.7f;
	autoTextWaitTime = 0.3f;
	textFade = false;
	skipUnreadText = false;
	displayTextFontName = GLOBAL->DisplayTextFont;
	textWindowAlpha = 0.3f;
	menuIteration = 1;
	stopVoiceNextLine = true;
	stopSkippingAtChoice = true;
	loadInitPageNumber = 0;
	saveInitPageNumber = 0;
}

void Config::parse(string configFile)
{
	init();

	ifstream configFileStream(configFile);
	if (!configFileStream)
	{
		write(configFile);
	}
	else
	{
		string line;			// An ENTIRE row of the file stored as a string
		while (getline(configFileStream, line)) 
		{
			int pos = line.find('#');
			if (pos != string::npos)
			{
				line = line.substr(0, pos);
			}
			line = UTILITY->trim(line);
			vector<string> tokens = UTILITY->split(line, '=');
			if (tokens.size() == 2)
			{
				try
				{
					string varName = UTILITY->trim(tokens[0]);
					string varValue = UTILITY->trim(tokens[1]);
					if (varName == CF_MASTER_VOLUME)
					{
						masterVolume = stof(varValue);
					}
					else if (varName == CF_BGM_VOLUME)
					{
						bgmVolume = stof(varValue);
					}
					else if (varName == CF_VOICE_VOLUME)
					{
						voiceVolume = stof(varValue);
					}
					else if (varName == CF_SFX_VOLUME)
					{
						sfxVolume = stof(varValue);
					}
					else if (varName == CF_FULLSCREEN)
					{
						enableFullscreen = static_cast<FullscreenOpts>(stoi(varValue));
					}
					else if (varName == CF_MANUAL_TEXT_SPEED)
					{
						manualTextSpeed = stof(varValue);
					}
					else if (varName == CF_AUTO_TEXT_SPEED)
					{
						autoTextSpeed = stof(varValue);
					}
					else if (varName == CF_AUTO_TEXT_WAIT_TIME)
					{
						autoTextWaitTime = stof(varValue);
					}
					else if (varName == CF_TEXT_FADE)
					{
						textFade = UTILITY->str2bool(varValue);
					}
					else if (varName == CF_SKIP_UNREAD_TEXT)
					{
						skipUnreadText = UTILITY->str2bool(varValue);
					}
					else if (varName == CF_DISPLAY_TEXT_FONT_NAME)
					{
						displayTextFontName = varValue;
						if (UTILITY->checkFileExist(displayTextFontName))
						{
							GLOBAL->DisplayTextFont = displayTextFontName;
						}
					}
					else if (varName == CF_TEXT_WINDOW_ALPHA)
					{
						textWindowAlpha = stof(varValue);
					}
					else if (varName == CF_WINDOW_WIDTH)
					{
						windowWidth = stoi(varValue);
					}
					else if (varName == CF_WINDOW_HEIGHT)
					{
						windowHeight = stoi(varValue);
					}
					else if (varName == CF_MENU_ITERATOR)
					{
						menuIteration = stoi(varValue);
					}
					else if (varName == CF_STOP_VOICE_NEXT_LINE)
					{
						stopVoiceNextLine = UTILITY->str2bool(varValue);
					}
					else if (varName == CF_STOP_SKIPPING_AT_CHOICE)
					{
						stopSkippingAtChoice = UTILITY->str2bool(varValue);
					}
					else if (varName == CF_LOAD_INIT_PAGE_NUMBER)
					{
						loadInitPageNumber = stoi(varValue);
					}
					else if (varName == CF_SAVE_INIT_PAGE_NUMBER)
					{
						saveInitPageNumber = stoi(varValue);
					}
					else if (varName != "")
					{
						string err = "Invalid config option found: " + varName;
						LOGGER->Log("Config", err);
					}
				}
				catch (invalid_argument e)
				{
					string err = "Invalid number detected from arguments: " + tokens[1];
					LOGGER->Log("Config", err);
				}
			}
		}
		configFileStream.close();
		write(configFile);
	}
}

string Config::getTitle()
{
	return windowTitle;
}

int Config::getWindowWidth()
{
	return windowWidth;
}

int Config::getWindowHeight()
{
	return windowHeight;
}

float Config::getFps()
{
	return fps;
}
