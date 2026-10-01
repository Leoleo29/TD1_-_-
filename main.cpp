#include <Novice.h>
#include "game.h"

const char kWindowTitle[] =
"AL2_01_02_02_LC1D_22_ホズミ_キンヤ.exe";

int WINAPI WinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int
)
{
	Novice::Initialize(
		kWindowTitle,
		kWindowWidth,
		kWindowHeight
	);

	int block = Novice::LoadTexture("./block.png");

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player player;
	InitializePlayer(player);

	Camera camera = { 0.0f, 0.0f };

	InitializeMap();

	while (Novice::ProcessMessage() == 0)
	{
		Novice::BeginFrame();

		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// 更新
		UpdatePlayer(
			player,
			keys,
			preKeys
		);

		UpdateCamera(
			camera,
			player
		);

		// 描画
		DrawMap(
			block,
			camera
		);

		DrawPlayer(
			player,
			camera
		);

		Novice::EndFrame();

		if (
			preKeys[DIK_ESCAPE] == 0 &&
			keys[DIK_ESCAPE] != 0
			)
		{
			break;
		}
	}

	Novice::Finalize();

	return 0;
}
