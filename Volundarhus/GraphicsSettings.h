#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings
{
public:
	GraphicsSettings();

	//Variables
	string title;
	VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	ContextSettings contextSettings;
	vector<VideoMode> videoModes;

	//Functions
	void saveToFile(const string path);
	void loadFromFile(const string path);
};

#endif // !GRAPHICSSETTINGS_H