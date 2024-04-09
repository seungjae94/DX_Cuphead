#pragma once

namespace GConstant
{
	
};

namespace GLevelName
{
	const std::string TestLevel = "TestLevel";
	const std::string TitleLevel = "TitleLevel";
	const std::string OverworldLevel = "OverworldLevel";
	const std::string BossDragonLevel = "BossDragonLevel";
};

namespace GImageName
{
	const std::string Noise = "common_noise";

	// 타이틀
	const std::string TitleScreenBack = "title_screen_back.png";
	const std::string TitleScreenCharacters = "title_screen_characters";

	// 오버월드
	const std::string OverworldIsle1Back = "overworld_isle1_back.png";
	const std::string OverworldIsle1Front = "overworld_isle1_front.png";
	const std::string OverworldIsle1Pixel = "overworld_isle1_pixel.png";

	const std::string OverworldCharDownIdle = "overworld_char_down_idle";
	const std::string OverworldCharDownWalk = "overworld_char_down_walk";
	const std::string OverworldCharRightDownIdle = "overworld_char_right_down_idle";
	const std::string OverworldCharRightDownWalk = "overworld_char_right_down_walk";
	const std::string OverworldCharRightUpIdle = "overworld_char_right_up_idle";
	const std::string OverworldCharRightUpWalk = "overworld_char_right_up_walk";
	const std::string OverworldCharRightIdle = "overworld_char_right_idle";
	const std::string OverworldCharRightWalk = "overworld_char_right_walk";
	const std::string OverworldCharUpIdle = "overworld_char_up_idle";
	const std::string OverworldCharUpWalk = "overworld_char_up_walk";

	// 보스 드래곤
	const std::string BossDragonMapBackground = "boss_dragon_map_back.png";
};

namespace GAnimName
{
	const std::string TitleDance = "Dance";
	const std::string Noise = "Noise";

	const std::string OverworldCharDownIdle = "DownIdle";
	const std::string OverworldCharDownWalk = "DownWalk";
	const std::string OverworldCharRightDownIdle = "RightDownIdle";
	const std::string OverworldCharRightDownWalk = "RightDownWalk";
	const std::string OverworldCharRightUpIdle = "RightUpIdle";
	const std::string OverworldCharRightUpWalk = "RightUpWalk";
	const std::string OverworldCharUpIdle = "UpIdle";
	const std::string OverworldCharUpWalk = "UpWalk";
	const std::string OverworldCharRightIdle = "RightIdle";
	const std::string OverworldCharRightWalk = "RightWalk";
};

namespace GStateName
{
	const std::string Idle = "Idle";
	const std::string Walk = "Walk";
}

enum class ERenderingOrder
{
	Back,
	Character,
	Front,
	UI
};

enum class EDirection
{
	Right,
	RightUp,
	Up,
	LeftUp,
	Left,
	LeftDown,
	Down,
	RightDown,
};