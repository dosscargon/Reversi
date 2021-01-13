#include"DxLib.h"
#include"Input.h"
#include"BoardNormal.h"
#include"Hand.h"
#include"Scenegame.h"
#include<string>
#include<stdio.h>

#define DEBUG

enum scene {
	TITLE,
	GAME,
	PAUSE,
	OPTION,
	CREDIT
};

void Init();

int font128;
int font100;
int font32;
int bgm;
int putsound;
int buttonsound;
int cancelsound;
int fallsound;

enum scene scene = TITLE;
BorW ComFlag;
ComType comtype;
bool guide = true;

void Title();
void Game();
void GetResultMessage(char str[]);
void Pause();
void Option();
void Credit();

Input input;
BoardNormal board;
Hand hand;

const int SCREEN_SIZE_X = 1280;
const int SCREEN_SIZE_Y = 720;
const int COLORBIT = 16;

const char thinking[] = "sound\\thinking.wav";
const char pachin[] = "sound\\pachin4.wav";
const char pochi[] = "sound\\pochi.wav";
const char cancel[] = "sound\\pochib.wav";
const char fall[] = "sound\\fall.wav";

const int MESSAGEWAIT = 120;
const int COMWAIT = 60;
const int FALLWAIT = 40;
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	Init();
	
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		input.GetMouseInfo();
		hand.SetClick(input.getMouseClick());
		switch (scene)
		{
		case TITLE:
			Title();
			break;
		case GAME:
			Game();
			break;
		case PAUSE:
			Pause();
			break;
		case OPTION:
			Option();
			break;
		case CREDIT:
			Credit();
			break;
		default:
			break;
		}
		
		
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void Init() {
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLORBIT);//��ʃT�C�Y�̎w��
	
	if (MessageBox(NULL, "�t���X�N���[���ŋN�����܂����H", "���o�[�V", MB_YESNO) == IDYES) {
		ChangeWindowMode(false);//�E�B���h�E���[�h�ݒ�
	}
	else {
		ChangeWindowMode(true);
	}
	
	SetMainWindowText("���o�[�V");
	SetWindowIconID(333);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		exit(0);			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);//����ʂɕ`��

	SetMouseDispFlag(TRUE);

	SetFontSize(64);

	font128 = CreateFontToHandle(NULL, 128, 3);
	font100 = CreateFontToHandle(NULL, 100, 3);
	font32 = CreateFontToHandle(NULL, 32, 3);

	bgm = LoadSoundMem(thinking);
	SetLoopPosSoundMem(105600, bgm);
	putsound = LoadSoundMem(pachin);
	buttonsound = LoadSoundMem(pochi);
	cancelsound = LoadSoundMem(cancel);
	fallsound = LoadSoundMem(fall);

	board.resetMurora();
}

void Title() {
	static int step = 1;
	static int point;
	static bool com;
	static int mode;//�ǂ�ȃ��o�[�V�H
	static bool oldtmk = false;
	static bool tmk = false;
	static int menumega = 0;//���[�h�I�����y�[�W�H
	static bool mega;
	static BorW comturn;
	static int difficult;
	static char button1[17] = "�ЂƂ�Ńv���C";
	static char button2[17] = "�ӂ���Ńv���C";

	static bool oldclick = false;

	point = 0;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 180, 200), true);

	//�^�C�g��
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (128 * 2), 50, "���o�[�V", GetColor(0, 0, 0), font128);

	//�{�^������1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY()&&input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 1;
	}else{
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, button1, GetColor(0, 0, 0), font100);

	//�{�^������2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 2;
	}else{
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 500, button2, GetColor(0, 0, 0), font100);

	//�߂�{�^��
	
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10 && 480 + 64 - 10 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10  , 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5)+10 , 620, GetColor(255, 255, 0), true);
		point = 3;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5)+10, 620, GetColor(0, 255, 0), true);

	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5)+10, 620, GetColor(0,0 , 0), false);
	if (step != 1) {
		DrawString((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5), 480 + 64, "�߂�", GetColor(0, 0, 0));
	}
	else {
		DrawString((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5), 480 + 64, "�I��", GetColor(0, 0, 0));
	}

	//�ݒ�{�^��
	if (step == 1) {
		if ((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10 && 480 + 64 - 10 < input.getMouseY() && input.getMouseY() < 620) {
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10, 620, GetColor(255, 255, 0), true);
			point = 4;
		}
		else {
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10, 620, GetColor(0, 255, 0), true);

		}
		DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10, 620, GetColor(0, 0, 0), false);

		DrawString((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5), 480 + 64, "�ݒ�", GetColor(0, 0, 0));
	}

	//�X�N���[���{�^��1
	if (menumega != 0) {
		if (step == 2) {
			if ((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3) && 280 < input.getMouseY() && input.getMouseY() < 420) {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 420, GetColor(255, 255, 0), true);
				point = 5;
			} else {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 420, GetColor(0, 255, 0), true);

			}
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 420, GetColor(0, 0, 0), false);


			DrawString((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) + 10, 320, "��", GetColor(0, 0, 0));
		}
	}

	//�X�N���[���{�^��2
	if (menumega != 2) {
		if (step == 2) {
			if ((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3) && 480 < input.getMouseY() && input.getMouseY() < 620) {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 620, GetColor(255, 255, 0), true);
				point = 6;
			} else {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 620, GetColor(0, 255, 0), true);

			}
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 620, GetColor(0, 0, 0), false);


			DrawString((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) + 10, 520, "��", GetColor(0, 0, 0));
		}
	}

	if (input.getMouseClick() == true && oldclick == false) {
		if (point == 3) {
			if (step == 1) {
				PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
				DxLib_End();
				exit(0);
			}
			menumega = 0;
			step--;
		}

		if (point == 4) {
			PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
			scene = OPTION;
		}

		switch (step) {
		case 1:
			//��l�ŁH��l��?
			if (point == 1) {
				com = true;
			}
			else if (point == 2) {
				com = false;
				
			}
			if (point == 1 || point == 2) {
				step = 2;
				menumega = 0;
			}
			break;

		case 2:
			//�ǂ�ȃ��o�[�V�H
			if (point == 1) {
				if (menumega == 0) {
					mode = 0;
				} else if (menumega==1) {
					mode = 2;
				} else if (menumega == 2) {
					mode = 4;
				}
			}
			else if (point == 2) {
				if (menumega == 0) {
					mode = 1;
				} else if(menumega == 1) {
					mode = 3;
				} else if (menumega == 2) {
					mode = 5;
				}

			}
			if (point == 1 || point == 2) {
				if (com == true) {
					step = 3;
				} else {
					step = 9;
				}
			}

			if (point == 5) {
				menumega--;
			}
			if (point == 6) {
				menumega++;
			}

			break;

		case 3:
			//��U�H��U�H
			if (point == 1) {
				comturn = white;
			}
			else if (point == 2) {
				comturn = black;
			}
			if (point == 1 || point == 2) {
				if (com == false) {
					step = 9;
				}else{
					step = 4;
				}
			}
			break;

		case 4:
			//��Փx
			if (point == 1) {
				difficult = 0;
				step = 9;
			}else if(point==2){
				difficult = 1;
				step = 9;
			}
		}

		//�{�^���e�L�X�g�ݒ�
		switch (step) {
		case 1:
			sprintf_s(button1, "�ЂƂ�Ńv���C");
			sprintf_s(button2, "�ӂ���Ńv���C");
			break;
		case 2:
			if (menumega == 0) {
				sprintf_s(button1, "���ʂ̃��o�[�V");
				sprintf_s(button2, "�ւ�ȃ��o�[�V");
			} else if (menumega == 1) {
				sprintf_s(button1, " ���K���o�[�V");
				sprintf_s(button2, "���낢���o�[�V");
			} else if(menumega == 2) {
				sprintf_s(button1, "�J�X�^�� 8�~8");
				sprintf_s(button2, "�J�X�^��16�~16");
			}
			break;
		case 3:
			sprintf_s(button1, " ��U�Ŏn�߂�");
			sprintf_s(button2, " ��U�Ŏn�߂�");
			break;
		case 4:
			sprintf_s(button1, "   �₳����");
			sprintf_s(button2, "   �����ւ�");
			break;
		case 9:
			//�Q�[���J�n����
			hand.SetInputFlag(true);
			if (com == true) {
				ComFlag = comturn;
				if (ComFlag == black) {
					hand.SetInputFlag(false);
				}
			}
			else {
				ComFlag = none;
				
			}
			if (mode == 0) {
				board.reset();
				if (difficult == 0) {
					comtype = com2;
				}
				else {
					comtype = com1;
				}
			} else if (mode == 1) {
				board.resetMurora();
				if (difficult == 0) {
					comtype = com2murora;
				}
				else {
					comtype = com1murora;
				}
			} else if (mode == 2) {
				board.resetMega();
				if (difficult == 0) {
					comtype = com2;
				}
				else {
					comtype = com1;
				}
			} else if (mode == 3) {
				board.resetMoroi();
				if (difficult == 0) {
					comtype = com2moroi;
				}
				else {
					comtype = com1moroi;
				}
			} else if(mode == 4) {
				board.resetCustom8();
				hand.SetInputFlag(true);
				if (difficult == 0) {
					comtype = com2;
				} else {
					comtype = com1;
				}
			} else if (mode == 5) {
				board.resetCustom16();
				hand.SetInputFlag(true);
				if (difficult == 0) {
					comtype = com2;
				} else {
					comtype = com1;
				}
			}

			step = 1;

			sprintf_s(button1, "�ЂƂ�Ńv���C");
			sprintf_s(button2, "�ӂ���Ńv���C");

			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
			scene = GAME;

			break;
		}

		if (point == 1 || point == 2 || point == 5 || point == 6) {
			PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
		}
		else if (point == 3) {
			PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
		}
		
	}

	point = 0;
	oldclick = input.getMouseClick();
}

void Game() {
	static char TurnMsg[20];
	
	static bool messageFlag = false;
	static int timer = 0;
	static bool fallFlag = false;
	static bool button;

	//�Ֆʕ`��----------------------------------------------------
	DrawBox(0, 0, 720, 720, GetColor(0, 255, 0), true);//�Ֆʂ̔w�i

	//�u����ꏊ�̐F��ς���(�K�C�h)
	if (guide == true) {
		if (hand.GetInputFlag() == true) {
			for (int i = 0; i < board.GetBoardSize() + 1; i++) {
				for (int j = 0; j < (board.GetBoardSize() + 1); j++) {
					if (board.put(i, j, true)) {
						DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(255, 186, 216), TRUE);
					}
				}
			}
		}
	}
	//�J�[�\��
	if (hand.GetInputFlag() == true&&!board.isFinish()) {
		for (int i = 0; i < board.GetBoardSize() + 1; i++) {
			for (int j = 0; j < (board.GetBoardSize() + 1); j++) {
				if (i*(720 / (board.GetBoardSize() + 1)) < input.getMouseX() && j*(720 / (board.GetBoardSize() + 1)) < input.getMouseY() && input.getMouseX() < (i + 1)*(720 / (board.GetBoardSize() + 1)) && input.getMouseY() < (j + 1)*(720 / (board.GetBoardSize() + 1))) {
					DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(255, 255, 0), TRUE);
				}
			}
		}
	}

	hand.CheckPoint(input.getMouseX(), input.getMouseY(),board.GetBoardSize());


	//�c�̐�������
	for (int i = 0; i < board.GetBoardSize() + 1 + 1; i++) {
		DrawLine(i*(720 / (board.GetBoardSize() + 1)), 0, i*(720 / (board.GetBoardSize() + 1)), 720, GetColor(0, 0, 0), 2);
	}

	//���̐�������
	for (int i = 0; i < board.GetBoardSize() + 1 + 1; i++) {
		DrawLine(0, i*(720 / (board.GetBoardSize() + 1)), 720, i*(720 / (board.GetBoardSize() + 1)), GetColor(0, 0, 0), 2);
	}

	//�΂�u��
	for (int i = 0; i < board.GetBoardSize() + 1; i++) {
		for (int j = 0; j < board.GetBoardSize() + 1; j++) {
			if (board.GetBoard(i, j) == black) {
				DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), TRUE);
			}
			else if (board.GetBoard(i, j) == white) {
				DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(255, 255, 255), TRUE);
				DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), FALSE);
			}
			else if (board.GetBoard(i, j) == gray) {
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(100, 100, 100), TRUE);
				//DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), FALSE);
			
				DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(0, 0, 0), TRUE);

			}
		}
	}

	//���`��----------------------------------------------
	DrawBox(721, 0, 1280, 720, GetColor(150, 150, 255), TRUE);
	
	DrawFormatString(800, 45, GetColor(0, 0, 0), "���@%d��", board.CountStone(black));
	DrawFormatString(800, 125, GetColor(0, 0, 0), "���@%d��", board.CountStone(white));

	//DrawFormatString(800, 45, GetColor(0, 0, 0), "X�@%d��",hand.GetPointX());
	//DrawFormatString(800, 125, GetColor(0, 0, 0), "Y�@%d��",hand.GetPointY());

	if (!board.isFinish()) {
		if (board.GetTurn() == black) {
			sprintf_s(TurnMsg, "���̔Ԃł�");
		} else if (board.GetTurn() == white) {
			sprintf_s(TurnMsg, "���̔Ԃł�");
		} else if (board.GetTurn() == gray) {
			sprintf_s(TurnMsg, "�J�X�^�����[�h");
		}
	}
	DrawFormatString(800, 300, GetColor(0, 0, 0), TurnMsg);

	if (990 < input.getMouseX() && input.getMouseX() < 1202 && 590 < input.getMouseY() && input.getMouseY() < 674 && hand.GetInputFlag() == true) {
		DrawBox(990, 590, 1202, 674, GetColor(255, 255, 50), TRUE);
	}else{
		DrawBox(990, 590, 1202, 674, GetColor(255, 50, 50), TRUE);
	}
	DrawBox(990, 590, 1202, 674, GetColor(0, 0, 0), FALSE);
	if (board.GetTurn() != gray) {
		DrawFormatString(1000, 600, GetColor(0, 0, 0), "�|�[�Y");
	} else {
		DrawFormatString(1000, 600, GetColor(0, 0, 0), " �J�n");
	}

	if (fallFlag == true && !board.isFinish()) {
		//���낢����
		timer++;
		if (timer > FALLWAIT) {
			board.fall();

			if (board.CheckPass(board.GetTurn())==false) {
				if (board.CheckPass(board.NotTurn(board.GetTurn()))==true) {
					hand.SetInputFlag(false);
					messageFlag = true;
					board.TurnChange();
				} else {
					GetResultMessage(TurnMsg);
					messageFlag = true;
					hand.SetInputFlag(false);
					board.finish();
				}
			}

			PlaySoundMem(fallsound, DX_PLAYTYPE_BACK);

			if (board.GetTurn() != ComFlag && !board.isFinish() && messageFlag == false) {
				hand.SetInputFlag(true);
			}

			fallFlag = false;
			timer = 0;
		}
	} else if (messageFlag == true) {
		//�p�X�Ƃ��Q�[���I�����̃��b�Z�[�W�{�b�N�X
		if (!board.isFinish()) {
			DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
			DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
			DrawStringToHandle(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 - 100 / 2, "�p�X", GetColor(0, 0, 0), font100);
		}else{
			DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
			DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
			DrawStringToHandle(SCREEN_SIZE_X / 2 - 100*2.5, SCREEN_SIZE_Y / 2 - 100 / 2, "�Q�[���I��", GetColor(0, 0, 0), font100);

		}
		timer++;
		//���b�Z�[�W�{�b�N�X������
		if (timer > MESSAGEWAIT) {
			messageFlag = false;
			fallFlag = false;
			if (board.GetTurn() != ComFlag || board.isFinish()) {
				hand.SetInputFlag(true);
			}
			timer = 0;
		}
	} else if (messageFlag == false && (board.GetTurn() == ComFlag) && !board.isFinish()) {
		//COM���Ăяo��
		timer++;
		if (timer > COMWAIT) {
#ifdef DEBUG
			char debugLog[100];
			sprintf_s(debugLog, "b:%d,w:%d\n", board.CountStone(black), board.CountStone(white));
			OutputDebugString(debugLog);
#endif // DEBUG

			if (comtype == com1) {
				board.Com1();
			} else if (comtype == com1murora) {
				board.Com1Murora();
			} else if (comtype == com1mega) {
				board.Com1();
			} else if (comtype == com1moroi) {
				board.Com1moroi();
			} else if (comtype == com2) {
				board.Com2();
			} else if (comtype == com2murora) {
				board.Com2Murora();
			} else if (comtype == com2mega) {
				board.Com2();
			} else if (comtype == com2moroi) {
				board.Com2moroi();
			}

#ifdef DEBUG
			sprintf_s(debugLog, "b:%d,w:%d\n", board.CountStone(black), board.CountStone(white));
			OutputDebugString(debugLog);
#endif // DEBUG

			PlaySoundMem	(putsound, DX_PLAYTYPE_BACK);
			
			//�^�[���`�F���W�ƃp�X&�Q�[���Z�b�g����
			if (board.TurnChange() == false) {
				if (board.TurnChange() == false) {
			
					GetResultMessage(TurnMsg);
					messageFlag = true;
					board.finish();
					//break;

				}
				else {
					hand.SetInputFlag(false);
					messageFlag = true;
				}
			} else {
				hand.SetInputFlag(true);
			}
			if (board.getMode() == MOROI) {
				hand.SetInputFlag(false);
				fallFlag = true;
			}
			
			timer = 0;
		}
	}

	//�v���C���[���ǂ����N���b�N�����Ƃ��̏���
	if (hand.CheckMouseDown() == true) {
		if (board.GetTurn() == gray) {
			if (board.put(hand.GetPointX(), hand.GetPointY())) {
				PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
			}
		} else if (board.put(hand.GetPointX(), hand.GetPointY()) == true) {
			PlaySoundMem(putsound, DX_PLAYTYPE_BACK);

			if (board.TurnChange() == false) {
				if (board.TurnChange() == false) {
					GetResultMessage(TurnMsg);
					messageFlag = true;
					hand.SetInputFlag(false);
					board.finish();
					//break;

				}
				else {
					hand.SetInputFlag(false);
					messageFlag = true;
				}
			}
			if (board.GetTurn() == ComFlag) {
				hand.SetInputFlag(false);
			}

			if (board.getMode() == MOROI) {
				hand.SetInputFlag(false);
				fallFlag = true;
			}
		}
		
	}

	//inputFlag�Ɋ֌W�Ȃ��N���b�N����
	if (hand.CheckMouseDownNoCheckFlag() == true) {
		if (990 < input.getMouseX() && input.getMouseX() < 1202 && 590 < input.getMouseY() && input.getMouseY() < 674) {
			if (hand.GetInputFlag() == true) {
				PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
				if (board.GetTurn() != gray) {
					scene = PAUSE;
				} else {
					if (board.TurnChange() == false) {
						if (board.TurnChange() == false) {
							GetResultMessage(TurnMsg);
							messageFlag = true;
							hand.SetInputFlag(false);
							board.finish();
							//break;

						} else {
							hand.SetInputFlag(false);
							messageFlag = true;
						}
					}
					if (board.GetTurn() == ComFlag) {
						hand.SetInputFlag(false);
					}
				}
			}
		}
	}
}

void GetResultMessage(char str[]) {
	if (board.CountStone(black) > board.CountStone(white)) {
		sprintf_s(str,13, "���̏����ł�");
	}
	else if (board.CountStone(black) < board.CountStone(white)) {
		sprintf_s(str,13, "���̏����ł�");
	}
	else {
		sprintf_s(str,13, "���������ł�");
	}
}

void Pause() {
	static int point = 0;
	static bool oldclick = false;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 100, 0), true);

	//�{�^������1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 80 < input.getMouseY() && input.getMouseY() < 220) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(255, 255, 0), true);
		point = 1;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 100, "�Q�[���𑱂���", GetColor(0, 0, 0), font100);


	//�{�^������2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY() && input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 2;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, "�ŏ�����n�߂�", GetColor(0, 0, 0), font100);

	//�{�^������3
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 3;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 500, "�^�C�g���ɖ߂�", GetColor(0, 0, 0), font100);

	if (input.getMouseClick() == true && oldclick == false) {
		switch (point)
		{
		case 1:
			PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
			scene = GAME;
			break;
		case 2:
			PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
			hand.SetInputFlag(true);
			if (ComFlag == black) {
				hand.SetInputFlag(false);
			}
			switch (board.getMode()) {
			case NORMAL:
				board.reset();
				break;
			case MURORA:
				board.resetMurora();
				break;
			case MEGA:
				board.resetMega();
				break;
			case MOROI:
				board.resetMoroi();
				break;
			case CUSTOM8:
				board.resetCustom8();
				hand.SetInputFlag(true);
				break;
			case CUSTOM16:
				board.resetCustom16();
				hand.SetInputFlag(true);
				break;
			}
			
			scene = GAME;
			break;
		case 3:
			PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
			StopSoundMem(bgm);
			scene = TITLE;
			break;
		}
	}
	point = 0;
	oldclick = input.getMouseClick();
}

void Option() {
	static int point ;
	static bool oldclick = false;
	static char button1[15] = " �K�C�h�F�I��";

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(200, 200, 255), true);

	//�^�C�g��
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (128 * 2), 50, "  �ݒ�", GetColor(0, 0, 0), font128);

	//�{�^������1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY() && input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 1;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, button1, GetColor(0, 0, 0), font100);

	//�{�^������2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 2;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 500, "  �N���W�b�g", GetColor(0, 0, 0), font100);

	//�߂�{�^��

	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10 && 480 + 64 - 10 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10, 620, GetColor(255, 255, 0), true);
		point = 3;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10, 620, GetColor(0, 255, 0), true);

	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10, 620, GetColor(0, 0, 0), false);
	DrawString((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5), 480 + 64, "�߂�", GetColor(0, 0, 0));
	
	if (input.getMouseClick() == true && oldclick == false) {
		switch (point)
		{
		case 1:
			PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
			if (guide == true) {
				guide = false;
				sprintf_s(button1, " �K�C�h�F�I�t");
			}else{
				guide = true;
				sprintf_s(button1, " �K�C�h�F�I��");
			}
			break;
		case 2:
			PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
			scene = CREDIT;
			break;
		case 3:
			PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
			scene = TITLE;
			break;
		}
	}
	point = 0;
	oldclick = input.getMouseClick();
}

void Credit()
{
	static bool oldclick = true;
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(100, 255, 255), true);
	DrawFormatStringFToHandle(64,64, GetColor(0, 0, 0),font32, "�v���O�����EBGM�E���ʉ�\n  �h�X�J���S��\n\n�A�C�R���E�X�}�z�A�v����\n  ugonight\n\n\n�V��ł����������F�l�A���Ƀl�b�g�ł̔z�M����]���Ă�������������\n�[�����ӂ��܂��B\n\n\n���z�A�v�]��twitter(@dosscargon)�܂ł��肢���܂��B\n\n\n\n\n                                                    �N���b�N�Ŗ߂�");

	if (input.getMouseClick() == true && oldclick == false) {
		PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
		scene = OPTION;
	}
	oldclick = input.getMouseClick();
}