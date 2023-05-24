
#include "GameLogic\Game.h"


int main(int argc, char** argv)
{
	ApplicationState = ApplicationStates::Running;
	Game game;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
	SetWindowState(FLAG_VSYNC_HINT);
	

	game.Setting();

	while (!WindowShouldClose()) {
		float time = GetFrameTime();
		

		switch (ApplicationState)
		{
		case ApplicationStates::Menu:
			game.UpdateMainMenu();
			break;
		case ApplicationStates::Running:
			game.UpdateGame(time);
			break;
		case ApplicationStates::Paused:
			game.UpdatePaused();
			break;
		case ApplicationStates::GameOver:
			game.UpdateGameOver();
			break;
		case ApplicationStates::GameClear:
			game.UpdateGameClear();
			break;
		}

		BeginDrawing();
		ClearBackground(SKYBLUE);

			game.Draw(time);

		EndDrawing();
	}

	game.End();

	return 0;
}




