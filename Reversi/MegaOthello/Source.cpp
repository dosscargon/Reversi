#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int mouseX, mouseY;

	int boardsize = 8;
	int board[8][8] = { 0 };

	board[3][4] = 1;
	board[4][3] = 1;
	board[3][3] = 2;
	board[4][4] = 2;

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1280, 720, 16);
	SetBackgroundColor(255, 255, 255);
	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
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

		//�c�̐�������
		for (int i = 0; i < boardsize + 1; i++) {
			DrawLine(i*(720 / boardsize), 0, i*(720 / boardsize), 720, GetColor(0, 0, 0), 2);
		}

		//���̐�������
		for (int i = 0; i < boardsize + 1; i++) {
			DrawLine(0, i*(720 / boardsize), 720, i*(720 / boardsize), GetColor(0, 0, 0), 2);
		}

		SetFontSize(64);
		DrawFormatString(800, 45, GetColor(0, 0, 0), "���@�H�H��");
		DrawFormatString(800, 125, GetColor(0, 0, 0), "���@�H�H��");

		DrawFormatString(800, 300, GetColor(0, 0, 0), "�����̔Ԃł�");

		DrawBox(990, 590, 1202, 674, GetColor(255, 50, 50), TRUE);
		DrawBox(990, 590, 1202, 674, GetColor(0, 0, 0), FALSE);
		DrawFormatString(1000, 600, GetColor(0, 0, 0), "�|�[�Y");

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

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}