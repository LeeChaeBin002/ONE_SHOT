#pragma once
#include "Defines.h"
#define DEF_DEV

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Title,
	Mode,
	Room,
	Computer,
	LivingRoom,
	cellar,
	cellar2,
	building,
	Stage1,
	Storege,
	Count
};

enum class Cellar2State
{
	Default,
	SecretAnimation
};

enum class Sides
{
	Left,
	Right,
	None
};
enum class PlayerState
{
	Default,
	HoldingBulb
};