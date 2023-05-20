#pragma once
#include "Common.h"
#include <string>



using namespace FlatPhysics;



struct CameraExtents {
	float left;
	float right;
	float bottom;
	float top;
};

struct CameraManager {
	Camera2D camera;
	float linearSpeed;
	float zoomSpeed;
	CameraExtents GetExtents();
};

class Game
{
public:
	void Setting();
	void UpdateLoad();
	void UpdateGame(float time);
	void UpdateMainMenu();
	void UpdatePaused();
	void UpdateGameOver();
	void Draw(float time);
	void End();
	
private:
	double stepTime;
	float alpha = 0.75f;
	
	std::string errorMessage;
	
	const float defaultZoom = 2.0f;
	CameraManager camera
	{ 
		{ 
			{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 },
			{ 0, 0 },
			0.0f, defaultZoom
		}, 
		70.0f, 0.5f
	};

	
	std::vector<FlatEntity*> entityVector;
	std::vector<FlatEntity*> entityRemovalVector;
	
	FlatWorld world{ {0, 98.1} };
	std::vector<Vector2> vertexBuffer;

	Button Btn;
	void run() { ApplicationState = ApplicationStates::Running; }
	void pause() { ApplicationState = ApplicationStates::Paused; }
};



