#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int mouseX, mouseY;

	int boardsize = 8;
	int board[8][8] = { 0 };

	board[3][4] = 1;
	board[4][3] = 1;
	board[3][3] = 2;
	board[4][4] = 2;

	// 画面モードの設定
	SetGraphMode(1280, 720, 16);
	SetBackgroundColor(255, 255, 255);
	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetMouseDispFlag(TRUE);

	while (ProcessMessage() != -1 && ScreenFlip() != -1 && ClearDrawScreen() != -1) {
		GetMousePoint(&mouseX, &mouseY);

		DrawBox(0, 0, 720, 720, GetColor(0, 255, 0), TRUE);
		DrawBox(721, 0, 1280, 720, GetColor(150, 150, 255), TRUE);

		for (int i = 0; i < boardsize; i++) {
			for (int j = 0; j < boardsize; j++) {
				if (i*(720 / boardsize) < mouseX&& j*(720 / boardsize) < mouseY&& mouseX < (i + 1)*(720 / boardsize) && mouseY < (j + 1)*(720 / boardsize)) {
					DrawBox(i*(720 / boardsize), j*(720 / boardsize), (i + 1)*(720 / boardsize), (j + 1)*(720 / boardsize), GetColor(255, 255, 0), TRUE);
				}
			}
		}

		//縦の線を引く
		for (int i = 0; i < boardsize + 1; i++) {
			DrawLine(i*(720 / boardsize), 0, i*(720 / boardsize), 720, GetColor(0, 0, 0), 2);
		}

		//横の線を引く
		for (int i = 0; i < boardsize + 1; i++) {
			DrawLine(0, i*(720 / boardsize), 720, i*(720 / boardsize), GetColor(0, 0, 0), 2);
		}

		SetFontSize(64);
		DrawFormatString(800, 45, GetColor(0, 0, 0), "黒　？？個");
		DrawFormatString(800, 125, GetColor(0, 0, 0), "白　？？個");

		DrawFormatString(800, 300, GetColor(0, 0, 0), "○○の番です");

		DrawBox(990, 590, 1202, 674, GetColor(255, 50, 50), TRUE);
		DrawBox(990, 590, 1202, 674, GetColor(0, 0, 0), FALSE);
		DrawFormatString(1000, 600, GetColor(0, 0, 0), "ポーズ");

		for (int i = 0; i < boardsize; i++) {
			for (int j = 0; j < boardsize; j++) {
				if (board[i][j] == 1) {
					DrawCircle((i + 0.5)*(720 / boardsize), (j + 0.5)*(720 / boardsize), (720 / boardsize) / 2 * 0.8, GetColor(0, 0, 0), TRUE);
				}
				else if (board[i][j] == 2) {
					DrawCircle((i + 0.5)*(720 / boardsize), (j + 0.5)*(720 / boardsize), (720 / boardsize) / 2 * 0.8, GetColor(255, 255, 255), TRUE);
					DrawCircle((i + 0.5)*(720 / boardsize), (j + 0.5)*(720 / boardsize), (720 / boardsize) / 2 * 0.8, GetColor(0, 0, 0), FALSE);
				}
			}
		}

		//DrawCircle(mouseX, mouseY, 50, GetColor(0, 0, 0));



	}

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}