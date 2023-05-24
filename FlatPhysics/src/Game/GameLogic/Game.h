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

class Cannon
{
public:
	Cannon(FlatWorld& world, float radius)
	{
		cannon = new FlatEntity(world, radius, false, RAYWHITE, origin);
		cannon->GetBody()->IsStatic = true;
	}
	FlatVector origin = { -250.0f, 100.0f };
	FlatEntity* cannon = new FlatEntity();
	FlatVector displacement = FlatVector::Zero();
	FlatVector GetDisplacement()
	{
		return cannon->GetPosition() - origin;
	}
	void DrawSlingshot()
	{
		FlatVector endPos = cannon->GetPosition();
		displacement = endPos - origin;
		float thick = sqrt(100.0f / FlatMath::Length(displacement));
		GameDraw::DrawLine(origin, endPos, thick, BROWN);
	}
	FlatEntity* GetEntity() { return cannon; }
	bool isClicked = false;
};

class Game
{
public:
	void Setting();
	
	void UpdateGame(float time);
	void Draw(float time);

	void UpdateMainMenu();
	void DrawMainMenu();

	void UpdatePaused();
	void DrawPaused();

	void UpdateGameOver();
	void DrawGameOver();

	void UpdateGameClear();
	void DrawGameClear();

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

	
	FlatVector cannonOrigin = { -250.0f, 150.0f };
	Cannon* cannon = new Cannon(world, 10.0f);
};



