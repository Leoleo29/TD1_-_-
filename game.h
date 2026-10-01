#pragma once

#include <Novice.h>

// 画面サイズ
const int kWindowWidth = 800;
const int kWindowHeight = 800;

// マップ
const int kMaxWidth = 40;
const int kMaxHeight = 40;
const int kMapSize = 80;

// プレイヤーの向き
// 0 = 上 / 1 = 右 / 2 = 下 / 3 = 左
enum PlayerDirection
{
	kUp = 0,
	kRight = 1,
	kDown = 2,
	kLeft = 3
};

struct Player
{
	float x;
	float y;

	// 単体版の velocity を分割版へ移植
	float velocityX;
	float velocityY;

	int direction;

	// 壁にぶつかったとき停止するために使用
	bool isMoving;

	// 最大速度
	float speed;
};

struct Camera
{
	float x;
	float y;
};

extern int mapData[kMaxHeight][kMaxWidth];

void InitializePlayer(Player& player);

void UpdatePlayer(
	Player& player,
	char* keys,
	char* preKeys
);

void InitializeMap();

void UpdateCamera(
	Camera& camera,
	const Player& player
);

void DrawMap(
	int block,
	const Camera& camera
);

void DrawPlayer(
	const Player& player,
	const Camera& camera
);
