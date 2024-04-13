#pragma once

namespace GConstant
{
	const FVector WindowScale = { 1280.0f, 720.0f, 0.0f };
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

	const std::string OverworldCharDust = "overworld_char_dust";

	// 플레이어
	const std::string PlayerIdle = "player_idle.png";
	const std::string PlayerShootUp = "player_shoot_up";
	const std::string PlayerShootHalfUp = "player_shoot_halfup";
	const std::string PlayerShootForward = "player_shoot_forward";
	const std::string PlayerShootHalfDown = "player_shoot_halfdown";
	const std::string PlayerShootDown = "player_shoot_down";
	const std::string PlayerRun = "player_run.png";
	const std::string PlayerRunShootHalfUp = "player_run_shoot_halfup";
	const std::string PlayerRunShootForward = "player_run_shoot_forward";
	const std::string PlayerJump = "player_jump.png";
	const std::string PlayerDash = "player_dash.png";
	const std::string PlayerSit = "player_sit.png";

	// 플레이어 먼지
	const std::string PlayerLandingDust = "player_landing_dust";
	const std::string PlayerDashDust = "player_dash_dust";

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

	// 오버월드
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

	const std::string OverworldCharDust = "overworld_char_dust";

	// 플레이어
	const std::string PlayerIdle = "player_idle";
	const std::string PlayerShootUp = "player_shoot_up";
	const std::string PlayerShootHalfUp = "player_shoot_halfup";
	const std::string PlayerShootForward = "player_shoot_forward";
	const std::string PlayerShootHalfDown = "player_shoot_halfdown";
	const std::string PlayerShootDown = "player_shoot_down";
	const std::string PlayerRun = "player_run";
	const std::string PlayerRunShootHalfUp = "player_run_shoot_halfup";
	const std::string PlayerRunShootForward = "player_run_shoot_forward";
	const std::string PlayerJump = "player_jump";
	const std::string PlayerDash = "player_dash";
	const std::string PlayerSit = "player_sit";

	// 플레이어 먼지
	const std::string PlayerLandingDust = "player_landing_dust";
	const std::string PlayerDashDust = "player_dash_dust";

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
	const std::string Aim = "Aim";
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
	Zero,
	Right,
	RightUp,
	Up,
	LeftUp,
	Left,
	LeftDown,
	Down,
	RightDown,
};