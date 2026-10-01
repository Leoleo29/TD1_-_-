#include "game.h"

void UpdateCamera(
	Camera& camera,
	const Player& player
)
{
	// プレイヤーを画面中央にする
	camera.x = player.x - kWindowWidth / 2.0f;
	camera.y = player.y - kWindowHeight / 2.0f;

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
	// マップ全体の幅 - 画面幅
	float maxCameraX =
		kMaxWidth * kMapSize - kWindowWidth;

	if (camera.x > maxCameraX)
	{
		camera.x = maxCameraX;
	}

	// 下端
	// マップ全体の高さ - 画面高さ
	float maxCameraY =
		kMaxHeight * kMapSize - kWindowHeight;

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
		kWindowWidth,
		kWindowHeight,
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
		BLUE,
		kFillModeSolid
	);

	// 向いている方向を確認しやすくするため、
	// 画面の4辺を表示する単体版の処理も分割側へ移植
	if (player.direction == kUp)
	{
		Novice::DrawBox(
			0, 0,
			kWindowWidth, 20,
			0.0f,
			RED,
			kFillModeSolid
		);
	}
	else
	{
		Novice::DrawBox(
			0, 0,
			kWindowWidth, 20,
			0.0f,
			WHITE,
			kFillModeSolid
		);
	}

	if (player.direction == kDown)
	{
		Novice::DrawBox(
			0, kWindowHeight - 20,
			kWindowWidth, 20,
			0.0f,
			RED,
			kFillModeSolid
		);
	}
	else
	{
		Novice::DrawBox(
			0, kWindowHeight - 20,
			kWindowWidth, 20,
			0.0f,
			WHITE,
			kFillModeSolid
		);
	}

	if (player.direction == kRight)
	{
		Novice::DrawBox(
			kWindowWidth - 20, 0,
			20, kWindowHeight,
			0.0f,
			RED,
			kFillModeSolid
		);
	}
	else
	{
		Novice::DrawBox(
			kWindowWidth - 20, 0,
			20, kWindowHeight,
			0.0f,
			WHITE,
			kFillModeSolid
		);
	}

	if (player.direction == kLeft)
	{
		Novice::DrawBox(
			0, 0,
			20, kWindowHeight,
			0.0f,
			RED,
			kFillModeSolid
		);
	}
	else
	{
		Novice::DrawBox(
			0, 0,
			20, kWindowHeight,
			0.0f,
			WHITE,
			kFillModeSolid
		);
	}

	// デバッグ表示
	Novice::ScreenPrintf(
		10,
		30,
		"Player Position: (%.2f, %.2f)",
		player.x,
		player.y
	);

	Novice::ScreenPrintf(
		10,
		50,
		"Camera Position: (%.2f, %.2f)",
		camera.x,
		camera.y
	);
}
