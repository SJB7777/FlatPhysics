#pragma once
#include "Common.h"
namespace Screen
{
	void DimScreen(float alpha = 0.5f);

}

class TextureButton
{
public:
	void SetButton(float width, float height, float x = 0, float y = 0)
	{
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
	}
		
	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void Draw() {
		if (pressed)
		{
			DrawTexturePro(texture1, { 0, 0, (float)texture1.width, (float)texture1.height }, { x, y, width, height }, { 0.0f, 0.0f }, 0.0f, WHITE);
		}
		else
		{
			DrawTexturePro(texture2, { 0, 0, (float)texture2.width, (float)texture2.height }, { x, y, width, height }, { 0.0f, 0.0f }, 0.0f, WHITE);
		}
	}

	template<class ListenerClass, typename ListenerMethod>
	void click_connect(ListenerClass* self, ListenerMethod method) 
	{

		Vector2 mouse_pos = GetMousePosition();
		if (CheckCollisionPointRec(mouse_pos, rect)) 
		{
			

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
			{
				
				pressed = !pressed;

			}
			else 
			{
				
				if (pressed) 
				{
					
					(self->*method)();
					pressed = !pressed;
				}
			}
		}
		else 
		{
			

		}

	}

private:
	Texture2D texture1;
	Texture2D texture2;
	Rectangle rect;
	bool pressed = false;

	float x, y, width, height;
};

class Button {
public:

	void SetButton(const char *str, float width, float height, int fontSize, float elevation = 6, float x = 0, float y = 0);
	void SetPosition(float x, float y);
	void draw();


	template<class ListenerClass, typename ListenerMethod>
	void click_connect(ListenerClass* self, ListenerMethod method) {

		Vector2 mouse_pos = GetMousePosition();
		if (CheckCollisionPointRec(mouse_pos, top_rect)) {
			top_color = { 215, 75, 75, 255 };

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				dynamic_elevation = 0;
				pressed = true;

			}
			else {
				dynamic_elevation = _elevation;
				if (pressed) {
					std::cout << text << " clicked" << std::endl;
					(self->*method)();
					pressed = false;
				}
			}
		}
		else {
			dynamic_elevation = _elevation;
			top_color = { 71, 95, 119, 255 };

		}

	}

	bool IsPressed() const {
		return pressed;
	}

	float GetX() const { return _x; }
	float GetY() const { return _y; }
	float GetWidth() const { return _width; }
	float GetHeight() const { return _height; }
	Rectangle GetRect() const {
		return top_rect;
	}

protected:
	float _x, _y, _width, _height;

	bool pressed = false;
	Rectangle top_rect;
	Rectangle bottom_rect;
	Rectangle text_rect;
	Color top_color{ 71, 95, 119, 255};
	Color bottom_color{ 53, 75, 94, 255 };
	Color text_color{ 255, 255, 255, 255 };
	const char *text;
	Font font;
	int fontSize;
	float _elevation;
	float dynamic_elevation;
	float original_y_pos;
};
