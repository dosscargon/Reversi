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
// プログラムは WinMain から始まります
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

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void Init() {
	// 画面モードの設定
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLORBIT);//画面サイズの指定
	
	if (MessageBox(NULL, "フルスクリーンで起動しますか？", "リバーシ", MB_YESNO) == IDYES) {
		ChangeWindowMode(false);//ウィンドウモード設定
	}
	else {
		ChangeWindowMode(true);
	}
	
	SetMainWindowText("リバーシ");
	SetWindowIconID(333);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		exit(0);			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);//裏画面に描画

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
	static int mode;//どんなリバーシ？
	static bool oldtmk = false;
	static bool tmk = false;
	static int menumega = 0;//モード選択何ページ？
	static bool mega;
	static BorW comturn;
	static int difficult;
	static char button1[17] = "ひとりでプレイ";
	static char button2[17] = "ふたりでプレイ";

	static bool oldclick = false;

	point = 0;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 180, 200), true);

	//タイトル
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (128 * 2), 50, "リバーシ", GetColor(0, 0, 0), font128);

	//ボタンその1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY()&&input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 1;
	}else{
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, button1, GetColor(0, 0, 0), font100);

	//ボタンその2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 2;
	}else{
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 500, button2, GetColor(0, 0, 0), font100);

	//戻るボタン
	
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10 && 480 + 64 - 10 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10  , 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5)+10 , 620, GetColor(255, 255, 0), true);
		point = 3;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5)+10, 620, GetColor(0, 255, 0), true);

	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5)+10, 620, GetColor(0,0 , 0), false);
	if (step != 1) {
		DrawString((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5), 480 + 64, "戻る", GetColor(0, 0, 0));
	}
	else {
		DrawString((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5), 480 + 64, "終了", GetColor(0, 0, 0));
	}

	//設定ボタン
	if (step == 1) {
		if ((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10 && 480 + 64 - 10 < input.getMouseY() && input.getMouseY() < 620) {
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10, 620, GetColor(255, 255, 0), true);
			point = 4;
		}
		else {
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10, 620, GetColor(0, 255, 0), true);

		}
		DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3.5) + 10, 620, GetColor(0, 0, 0), false);

		DrawString((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5), 480 + 64, "設定", GetColor(0, 0, 0));
	}

	//スクロールボタン1
	if (menumega != 0) {
		if (step == 2) {
			if ((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3) && 280 < input.getMouseY() && input.getMouseY() < 420) {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 420, GetColor(255, 255, 0), true);
				point = 5;
			} else {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 420, GetColor(0, 255, 0), true);

			}
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 420, GetColor(0, 0, 0), false);


			DrawString((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) + 10, 320, "▲", GetColor(0, 0, 0));
		}
	}

	//スクロールボタン2
	if (menumega != 2) {
		if (step == 2) {
			if ((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3) && 480 < input.getMouseY() && input.getMouseY() < 620) {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 620, GetColor(255, 255, 0), true);
				point = 6;
			} else {
				DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 620, GetColor(0, 255, 0), true);

			}
			DrawBox((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) - 10, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 3), 620, GetColor(0, 0, 0), false);


			DrawString((SCREEN_SIZE_X / 2) + (100 * 3.5) + (64 * 1.5) + 10, 520, "▼", GetColor(0, 0, 0));
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
			//一人で？二人で?
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
			//どんなリバーシ？
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
			//先攻？後攻？
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
			//難易度
			if (point == 1) {
				difficult = 0;
				step = 9;
			}else if(point==2){
				difficult = 1;
				step = 9;
			}
		}

		//ボタンテキスト設定
		switch (step) {
		case 1:
			sprintf_s(button1, "ひとりでプレイ");
			sprintf_s(button2, "ふたりでプレイ");
			break;
		case 2:
			if (menumega == 0) {
				sprintf_s(button1, "普通のリバーシ");
				sprintf_s(button2, "へんなリバーシ");
			} else if (menumega == 1) {
				sprintf_s(button1, " メガリバーシ");
				sprintf_s(button2, "もろいリバーシ");
			} else if(menumega == 2) {
				sprintf_s(button1, "カスタム 8×8");
				sprintf_s(button2, "カスタム16×16");
			}
			break;
		case 3:
			sprintf_s(button1, " 先攻で始める");
			sprintf_s(button2, " 後攻で始める");
			break;
		case 4:
			sprintf_s(button1, "   やさしい");
			sprintf_s(button2, "   たいへん");
			break;
		case 9:
			//ゲーム開始処理
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

			sprintf_s(button1, "ひとりでプレイ");
			sprintf_s(button2, "ふたりでプレイ");

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

	//盤面描画----------------------------------------------------
	DrawBox(0, 0, 720, 720, GetColor(0, 255, 0), true);//盤面の背景

	//置ける場所の色を変える(ガイド)
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
	//カーソル
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


	//縦の線を引く
	for (int i = 0; i < board.GetBoardSize() + 1 + 1; i++) {
		DrawLine(i*(720 / (board.GetBoardSize() + 1)), 0, i*(720 / (board.GetBoardSize() + 1)), 720, GetColor(0, 0, 0), 2);
	}

	//横の線を引く
	for (int i = 0; i < board.GetBoardSize() + 1 + 1; i++) {
		DrawLine(0, i*(720 / (board.GetBoardSize() + 1)), 720, i*(720 / (board.GetBoardSize() + 1)), GetColor(0, 0, 0), 2);
	}

	//石を置く
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

	//情報描画----------------------------------------------
	DrawBox(721, 0, 1280, 720, GetColor(150, 150, 255), TRUE);
	
	DrawFormatString(800, 45, GetColor(0, 0, 0), "黒　%d個", board.CountStone(black));
	DrawFormatString(800, 125, GetColor(0, 0, 0), "白　%d個", board.CountStone(white));

	//DrawFormatString(800, 45, GetColor(0, 0, 0), "X　%d個",hand.GetPointX());
	//DrawFormatString(800, 125, GetColor(0, 0, 0), "Y　%d個",hand.GetPointY());

	if (!board.isFinish()) {
		if (board.GetTurn() == black) {
			sprintf_s(TurnMsg, "黒の番です");
		} else if (board.GetTurn() == white) {
			sprintf_s(TurnMsg, "白の番です");
		} else if (board.GetTurn() == gray) {
			sprintf_s(TurnMsg, "カスタムモード");
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
		DrawFormatString(1000, 600, GetColor(0, 0, 0), "ポーズ");
	} else {
		DrawFormatString(1000, 600, GetColor(0, 0, 0), " 開始");
	}

	if (fallFlag == true && !board.isFinish()) {
		//もろい処理
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
		//パスとかゲーム終了時のメッセージボックス
		if (!board.isFinish()) {
			DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
			DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
			DrawStringToHandle(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 - 100 / 2, "パス", GetColor(0, 0, 0), font100);
		}else{
			DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
			DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
			DrawStringToHandle(SCREEN_SIZE_X / 2 - 100*2.5, SCREEN_SIZE_Y / 2 - 100 / 2, "ゲーム終了", GetColor(0, 0, 0), font100);

		}
		timer++;
		//メッセージボックスを消す
		if (timer > MESSAGEWAIT) {
			messageFlag = false;
			fallFlag = false;
			if (board.GetTurn() != ComFlag || board.isFinish()) {
				hand.SetInputFlag(true);
			}
			timer = 0;
		}
	} else if (messageFlag == false && (board.GetTurn() == ComFlag) && !board.isFinish()) {
		//COMを呼び出す
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
			
			//ターンチェンジとパス&ゲームセット判定
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

	//プレイヤーがどこかクリックしたときの処理
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

	//inputFlagに関係ないクリック処理
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
		sprintf_s(str,13, "黒の勝ちです");
	}
	else if (board.CountStone(black) < board.CountStone(white)) {
		sprintf_s(str,13, "白の勝ちです");
	}
	else {
		sprintf_s(str,13, "引き分けです");
	}
}

void Pause() {
	static int point = 0;
	static bool oldclick = false;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 100, 0), true);

	//ボタンその1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 80 < input.getMouseY() && input.getMouseY() < 220) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(255, 255, 0), true);
		point = 1;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 100, "ゲームを続ける", GetColor(0, 0, 0), font100);


	//ボタンその2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY() && input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 2;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, "最初から始める", GetColor(0, 0, 0), font100);

	//ボタンその3
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 3;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 500, "タイトルに戻る", GetColor(0, 0, 0), font100);

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
	static char button1[15] = " ガイド：オン";

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(200, 200, 255), true);

	//タイトル
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (128 * 2), 50, "  設定", GetColor(0, 0, 0), font128);

	//ボタンその1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY() && input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 1;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, button1, GetColor(0, 0, 0), font100);

	//ボタンその2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20< input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 2;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 500, "  クレジット", GetColor(0, 0, 0), font100);

	//戻るボタン

	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10 && 480 + 64 - 10 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10, 620, GetColor(255, 255, 0), true);
		point = 3;
	}
	else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10, 620, GetColor(0, 255, 0), true);

	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5) - 10, 480 + 64 - 10, (SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 1.5) + 10, 620, GetColor(0, 0, 0), false);
	DrawString((SCREEN_SIZE_X / 2) - (100 * 3.5) - (64 * 3.5), 480 + 64, "戻る", GetColor(0, 0, 0));
	
	if (input.getMouseClick() == true && oldclick == false) {
		switch (point)
		{
		case 1:
			PlaySoundMem(buttonsound, DX_PLAYTYPE_BACK);
			if (guide == true) {
				guide = false;
				sprintf_s(button1, " ガイド：オフ");
			}else{
				guide = true;
				sprintf_s(button1, " ガイド：オン");
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
	DrawFormatStringFToHandle(64,64, GetColor(0, 0, 0),font32, "プログラム・BGM・効果音\n  ドスカルゴン\n\nアイコン・スマホアプリ化\n  ugonight\n\n\n遊んでくださった皆様、特にネットでの配信を希望してくださった方に\n深く感謝します。\n\n\n感想、要望はtwitter(@dosscargon)までお願いします。\n\n\n\n\n                                                    クリックで戻る");

	if (input.getMouseClick() == true && oldclick == false) {
		PlaySoundMem(cancelsound, DX_PLAYTYPE_BACK);
		scene = OPTION;
	}
	oldclick = input.getMouseClick();
}