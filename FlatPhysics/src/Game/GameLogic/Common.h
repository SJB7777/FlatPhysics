#pragma once
#include <vector>
#include "raylib.h"
#include "..\..\Engine\GameEngine.h"

enum class ApplicationStates {
	Startup,
	Loading,
	Menu,
	Running,
	Paused,
	GameOver,
	Quiting
};

inline ApplicationStates ApplicationState = ApplicationStates::Running;