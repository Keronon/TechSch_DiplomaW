#ifndef GUI_H
#define GUI_H

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	const float p2pX(const float perc, const VideoMode& vm);
	const float p2pY(const float perc, const VideoMode& vm);
	const unsigned calcCharSize(const VideoMode& vm, const unsigned modifier = 60);

	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		Font* font;
		Text text;

		Color textIdleColor;
		Color textHoverColor;
		Color textActiveColor;

		Color idleColor;
		Color hoverColor;
		Color activeColor;

		Color outlineIdleColor;
		Color outlineHoverColor;
		Color outlineActiveColor;

		SoundBuffer hoverSB;
		Sound hover;
		SoundBuffer activeSB;
		Sound active;

	public:
		Button(float x, float y, float width, float height,
			Font* font, string text, unsigned character_size,
			Color text_idle_color, Color text_hover_color, Color text_active_color,
			Color idle_color, Color hover_color, Color active_color,
			Color outline_idle_color = Color::Transparent, Color outline_hover_color = Color::Transparent, Color outline_active_color = Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const string text);
		void setId(const short unsigned id);

		//Functions
		void update(const Vector2i& mousePosWindow);
		void render(RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		Font& font;
		gui::Button* activeElement;
		vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, float width, float height, 
			Font& font, string list[], 
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;

		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const Vector2i& mousePosWindow, const float& dt);
		void render(RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		Sprite sheet;
		sf::RectangleShape selector;
		Vector2u mousePosGrid;
		IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height, 
			float gridSize, const Texture* texture_sheet, 
			Font& font, string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const IntRect& getTextureRect() const;

		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const Vector2i& mousePosWindow, const float& dt);
		void render(RenderTarget& target);
	};

	class ProgressBar
	{
	private:
		string barString;
		Text text;
		float maxWidth;
		int maxValue;
		sf::RectangleShape back;
		sf::RectangleShape inner;

	public:
		ProgressBar(float x, float y, float width, float height, int max_value,
			Color inner_color, Color outline_color, unsigned character_size,
			VideoMode& vm, Font* font = NULL);
		~ProgressBar();

		//Accessors

		//Modifiers

		//Functions
		void update(const int current_value, const int max_value);
		void render(RenderTarget & target);
	};
}

#endif
