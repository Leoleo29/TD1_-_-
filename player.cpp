#include "game.h"

void InitializePlayer(Player& player)
{
	// 左下の通路
	player.x = 120.0f;
	player.y = 3080.0f;

	// 最初は右
	player.direction = kRight;

	// 単体版の速度計算を使用
	player.velocityX = 0.0f;
	player.velocityY = 0.0f;

	// 最初から動く
	player.isMoving = true;

	// 単体版の最大速度
	player.speed = 5.0f;
}

void UpdatePlayer(
	Player& player,
	char* keys,
	char* preKeys
)
{
	// SPACEを押した瞬間に方向を切り替える
	if (
		preKeys[DIK_SPACE] == 0 &&
		keys[DIK_SPACE] != 0
		)
	{
		// 単体版と同じく、現在の向きから反時計回りに90度回転
		player.direction--;

		if (player.direction < kUp)
		{
			player.direction = kLeft;
		}

		// 向きを変えたら速度をリセット
		player.velocityX = 0.0f;
		player.velocityY = 0.0f;

		// 壁にぶつかって停止していても再開
		player.isMoving = true;
	}

	// 止まっている場合、SPACEを押すまで動かさない
	if (!player.isMoving)
	{
		return;
	}

	// 引っ張られる力
	const float acceleration = 0.2f;

	// 現在の方向に加速
	switch (player.direction)
	{
	case kUp:
		player.velocityY -= acceleration;

		if (player.velocityY < -player.speed)
		{
			player.velocityY = -player.speed;
		}
		break;

	case kRight:
		player.velocityX += acceleration;

		if (player.velocityX > player.speed)
		{
			player.velocityX = player.speed;
		}
		break;

	case kDown:
		player.velocityY += acceleration;

		if (player.velocityY > player.speed)
		{
			player.velocityY = player.speed;
		}
		break;

	case kLeft:
		player.velocityX -= acceleration;

		if (player.velocityX < -player.speed)
		{
			player.velocityX = -player.speed;
		}
		break;
	}

	// 次の位置を計算
	float nextX = player.x + player.velocityX;
	float nextY = player.y + player.velocityY;

	// 現在いるマス
	int currentMapX =
		static_cast<int>(player.x) / kMapSize;

	int currentMapY =
		static_cast<int>(player.y) / kMapSize;

	// 次に入るマス
	int nextMapX =
		static_cast<int>(nextX) / kMapSize;

	int nextMapY =
		static_cast<int>(nextY) / kMapSize;

	// 別のマスへ入ろうとした場合だけ壁判定
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
			// 単体版の「端で止まる」に相当
			player.isMoving = false;
			player.velocityX = 0.0f;
			player.velocityY = 0.0f;

			return;
		}
	}

	// 滑らかに移動
	player.x = nextX;
	player.y = nextY;
}
