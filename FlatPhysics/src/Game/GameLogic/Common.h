#pragma once
#include <vector>
#include "raylib.h"
#include "..\..\Engine\GameEngine.h"

enum class ApplicationStates {
	Menu,
	Running,
	Paused,
	GameOver,
	GameClear
};

inline ApplicationStates ApplicationState = ApplicationStates::Running;