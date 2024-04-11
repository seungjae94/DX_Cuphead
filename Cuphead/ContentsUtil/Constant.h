#pragma once

namespace GConstant
{

};

namespace GLevelName
{
	const std::string TestLevel = "TestLevel";
	const std::string TitleLevel = "TitleLevel";
	const std::string OverworldLevel = "OverworldLevel";
	const std::string BossFarmLevel = "BossFarmLevel";
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

	// 플레이어
	const std::string PlayerLeftIdle = "player_left_idle.png";
	const std::string PlayerRightIdle = "player_right_idle.png";
	const std::string PlayerLeftJump = "player_left_jump.png";
	const std::string PlayerRightJump = "player_right_jump.png";
	const std::string PlayerLeftDash = "player_left_dash.png";
	const std::string PlayerRightDash = "player_right_dash.png";
	const std::string PlayerLeftShoot = "player_left_shoot.png";
	const std::string PlayerRightShoot = "player_right_shoot.png";
	const std::string PlayerLeftRun = "player_left_run.png";
	const std::string PlayerRightRun = "player_right_run.png";
	const std::string PlayerLeftRunShoot = "player_left_run_shoot.png";
	const std::string PlayerRightRunShoot = "player_right_run_shoot.png";
	const std::string PlayerLeftSit = "player_left_sit.png";
	const std::string PlayerRightSit = "player_right_sit.png";

	// 총알
	const std::string BulletSpawn = "bullet_spawn.png";
	const std::string BulletMove = "bullet_move";
	const std::string BulletDestroy = "bullet_destroy.png";

	// 보스 드래곤
	const std::string BossDragonMapBackground = "boss_dragon_map_back.png";
	const std::string BossDragonMapTower = "boss_dragon_map_tower";
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

	// 플레이어
	const std::string PlayerLeftIdle = "player_left_idle";
	const std::string PlayerRightIdle = "player_right_idle";
	const std::string PlayerLeftJump = "player_left_jump";
	const std::string PlayerRightJump = "player_right_jump";
	const std::string PlayerLeftDash = "player_left_dash";
	const std::string PlayerRightDash = "player_right_dash";
	const std::string PlayerLeftShoot = "player_left_shoot";
	const std::string PlayerRightShoot = "player_right_shoot";
	const std::string PlayerLeftRun = "player_left_run";
	const std::string PlayerRightRun = "player_right_run";
	const std::string PlayerLeftRunShoot = "player_left_run_shoot";
	const std::string PlayerRightRunShoot = "player_right_run_shoot";
	const std::string PlayerLeftSit = "player_left_sit";
	const std::string PlayerRightSit = "player_right_sit";

	// 총알
	const std::string BulletSpawn = "bullet_spawn";
	const std::string BulletMove = "bullet_move";
	const std::string BulletDestroy = "bullet_destroy";

	// 보스 드래곤
	const std::string BossDragonMapTower = "BossDragonMapTower";
};

namespace GStateName
{
	const std::string Idle = "Idle";
	const std::string Walk = "Walk";
	const std::string Run = "Run";
	const std::string Sit = "Sit";
	const std::string Dash = "Dash";
	const std::string Jump = "Jump";

	const std::string Spawn = "Spawn";
	const std::string Move = "Move";
	const std::string Destroy = "Destroy";
}

enum class ERenderingOrder
{
	Back0,
	Back1,
	Back2,
	Back3,
	Character,
	Bullet,
	Front,
	Collider,
	UI,
	Noise,
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