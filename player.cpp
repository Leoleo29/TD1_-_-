#include "game.h"

void InitializePlayer(Player& player)
{
	// 左下の通路
	player.x = 120.0f;
	player.y = 3080.0f;

	// 最初は右
	player.direction = 1;

	// 最初から動く
	player.isMoving = true;

	// 移動速度
	player.speed = 2.0f;
}

void UpdatePlayer(
	Player& player,
	char* keys,
	char* preKeys
)
{
	// SPACEを押した瞬間
	if (
		preKeys[DIK_SPACE] == 0 &&
		keys[DIK_SPACE] != 0
		)
	{
		// 反時計回りに90度
		player.direction--;

		if (player.direction < 0)
		{
			player.direction = 3;
		}

		// また動く
		player.isMoving = true;
	}

	// 止まっているなら動かない
	if (!player.isMoving)
	{
		return;
	}

	float nextX = player.x;
	float nextY = player.y;

	// 進行方向
	if (player.direction == 0)
	{
		// 上
		nextY -= player.speed;
	}
	else if (player.direction == 1)
	{
		// 右
		nextX += player.speed;
	}
	else if (player.direction == 2)
	{
		// 下
		nextY += player.speed;
	}
	else if (player.direction == 3)
	{
		// 左
		nextX -= player.speed;
	}

	// 今いるマス
	int currentMapX =
		static_cast<int>(player.x) / kMapSize;

	int currentMapY =
		static_cast<int>(player.y) / kMapSize;

	// 次に入るマス
	int nextMapX =
		static_cast<int>(nextX) / kMapSize;

	int nextMapY =
		static_cast<int>(nextY) / kMapSize;

	// 別のマスに入ろうとしたとき
	if (
		currentMapX != nextMapX ||
		currentMapY != nextMapY
		)
	{
		// マップ外または壁
		if (
			nextMapX < 0 ||
			nextMapX >= kMaxWidth ||
			nextMapY < 0 ||
			nextMapY >= kMaxHeight ||
			mapData[nextMapY][nextMapX] == 1
			)
		{
			// そこで止まる
			player.isMoving = false;

			return;
		}
	}

	// 滑らかに移動
	player.x = nextX;
	player.y = nextY;
}