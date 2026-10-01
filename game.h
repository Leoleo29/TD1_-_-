#pragma once

#include <Novice.h>

const int kMaxWidth = 40;
const int kMaxHeight = 40;
const int kMapSize = 80;

struct Player
{
	float x;
	float y;

	int direction;

	bool isMoving;

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