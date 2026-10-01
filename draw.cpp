#include "game.h"

void UpdateCamera(
	Camera& camera,
	const Player& player
)
{
	// プレイヤーを画面中央にする
	camera.x = player.x - 400.0f;
	camera.y = player.y - 400.0f;

	// 左端
	if (camera.x < 0.0f)
	{
		camera.x = 0.0f;
	}

	// 上端
	if (camera.y < 0.0f)
	{
		camera.y = 0.0f;
	}

	// 右端
	float maxCameraX =
		kMaxWidth * kMapSize - 800.0f;

	if (camera.x > maxCameraX)
	{
		camera.x = maxCameraX;
	}

	// 下端
	float maxCameraY =
		kMaxHeight * kMapSize - 800.0f;

	if (camera.y > maxCameraY)
	{
		camera.y = maxCameraY;
	}
}

void DrawMap(
	int block,
	const Camera& camera
)
{
	// 背景
	Novice::DrawBox(
		0,
		0,
		800,
		800,
		0,
		BLACK,
		kFillModeSolid
	);

	// マップ
	for (int i = 0; i < kMaxHeight; i++)
	{
		for (int j = 0; j < kMaxWidth; j++)
		{
			if (mapData[i][j] == 1)
			{
				int posX =
					j * kMapSize -
					static_cast<int>(camera.x);

				int posY =
					i * kMapSize -
					static_cast<int>(camera.y);

				Novice::DrawSprite(
					posX,
					posY,
					block,
					1,
					1,
					0,
					WHITE
				);
			}
		}
	}
}

void DrawPlayer(
	const Player& player,
	const Camera& camera
)
{
	int drawX =
		static_cast<int>(
			player.x - camera.x
			);

	int drawY =
		static_cast<int>(
			player.y - camera.y
			);

	Novice::DrawEllipse(
		drawX,
		drawY,
		20,
		20,
		0,
		RED,
		kFillModeSolid
	);
}