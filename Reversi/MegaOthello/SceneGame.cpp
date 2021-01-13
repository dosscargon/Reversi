#include "Scenegame.h"
#include "DxLib.h"

void Game() {
	static char TurnMsg[20];
	static bool megamsgflag = true;


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
	if (hand.GetInputFlag() == true && !board.isFinish()) {
		for (int i = 0; i < board.GetBoardSize() + 1; i++) {
			for (int j = 0; j < (board.GetBoardSize() + 1); j++) {
				if (i*(720 / (board.GetBoardSize() + 1)) < input.getMouseX() && j*(720 / (board.GetBoardSize() + 1)) < input.getMouseY() && input.getMouseX() < (i + 1)*(720 / (board.GetBoardSize() + 1)) && input.getMouseY() < (j + 1)*(720 / (board.GetBoardSize() + 1))) {
					DrawBox(i*(720 / (board.GetBoardSize() + 1)), j*(720 / (board.GetBoardSize() + 1)), (i + 1)*(720 / (board.GetBoardSize() + 1)), (j + 1)*(720 / (board.GetBoardSize() + 1)), GetColor(255, 255, 0), TRUE);
				}
			}
		}
	}

	hand.CheckPoint(input.getMouseX(), input.getMouseY(), board.GetBoardSize());


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
			} else if (board.GetBoard(i, j) == white) {
				DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(255, 255, 255), TRUE);
				DrawCircle((i + 0.5)*(720 / (board.GetBoardSize() + 1)), (j + 0.5)*(720 / (board.GetBoardSize() + 1)), (720 / (board.GetBoardSize() + 1)) / 2 * 0.8, GetColor(0, 0, 0), FALSE);
			} else if (board.GetBoard(i, j) == gray) {
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
	} else {
		DrawBox(990, 590, 1202, 674, GetColor(255, 50, 50), TRUE);
	}
	DrawBox(990, 590, 1202, 674, GetColor(0, 0, 0), FALSE);
	if (board.GetTurn() != gray) {
		DrawFormatString(1000, 600, GetColor(0, 0, 0), "ポーズ");
	} else {
		DrawFormatString(1000, 600, GetColor(0, 0, 0), " 開始");
	}



	if (fallFlag == true && !board.isFinish()) {
		timer++;
		if (timer > FALLWAIT) {
			board.fall();

			if (board.CheckPass(board.GetTurn()) == false) {
				if (board.CheckPass(board.NotTurn(board.GetTurn())) == true) {
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
		if (!board.isFinish()) {
			DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
			DrawBox(SCREEN_SIZE_X / 2 - 100 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
			DrawStringToHandle(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 - 100 / 2, "パス", GetColor(0, 0, 0), font100);
		} else {
			DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 255, 255), true);
			DrawBox(SCREEN_SIZE_X / 2 - 100 * 2.5 - 10, SCREEN_SIZE_Y / 2 - 100 / 2 - 10, SCREEN_SIZE_X / 2 + 100 * 2.5 + 10, SCREEN_SIZE_Y / 2 + 100 / 2 + 10, GetColor(0, 0, 0), false);
			DrawStringToHandle(SCREEN_SIZE_X / 2 - 100 * 2.5, SCREEN_SIZE_Y / 2 - 100 / 2, "ゲーム終了", GetColor(0, 0, 0), font100);

		}
		timer++;
		if (timer > MESSAGEWAIT) {
			messageFlag = false;
			fallFlag = false;
			if (board.GetTurn() != ComFlag || board.isFinish()) {
				hand.SetInputFlag(true);
			}
			timer = 0;
		}
	} else if (messageFlag == false && (board.GetTurn() == ComFlag) && !board.isFinish()) {
		timer++;
		if (timer > COMWAIT) {
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
				board.Com2Mega();
			} else if (comtype == com2moroi) {
				board.Com2moroi();
			}

			PlaySoundMem(putsound, DX_PLAYTYPE_BACK);

			//if (1) {
				//if (0) {
			if (board.TurnChange() == false) {
				if (board.TurnChange() == false) {

					GetResultMessage(TurnMsg);
					messageFlag = true;
					board.finish();
					//break;

				} else {
					hand.SetInputFlag(false);
					messageFlag = true;
				}
			} else {
				hand.SetInputFlag(true);

			}
			if (comtype == com1moroi || comtype == com2moroi) {
				hand.SetInputFlag(false);
				fallFlag = true;
			}

			timer = 0;
		}
	}

	if (hand.CheckMouseDown() == true) {
		if (board.GetTurn() == gray) {
			board.put(hand.GetPointX(), hand.GetPointY());
			PlaySoundMem(fallsound, DX_PLAYTYPE_BACK);

		} else if (board.put(hand.GetPointX(), hand.GetPointY()) == true) {
			PlaySoundMem(putsound, DX_PLAYTYPE_BACK);

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

			if (comtype == com1moroi || comtype == com2moroi) {
				hand.SetInputFlag(false);
				fallFlag = true;
			}
		}

	}

	/*if (board.GetTurn() == gray&& comtype == com1murora&&megamsgflag == true) {
		if ((board.CountStone(black) > board.CountStone(white)&&ComFlag==white)||(board.CountStone(black) < board.CountStone(white)&&ComFlag==black)) {
			megamsgflag = false;
			scene = MEGAMSG;
		}
	}*/

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
		sprintf_s(str, 13, "黒の勝ちです");
	} else if (board.CountStone(black) < board.CountStone(white)) {
		sprintf_s(str, 13, "白の勝ちです");
	} else {
		sprintf_s(str, 13, "引き分けです");
	}
}

void Pause() {
	static int point = 0;
	static bool oldclick = false;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 100, 0), true);

	//ボタンその1
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 80 < input.getMouseY() && input.getMouseY() < 220) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(255, 255, 0), true);
		point = 1;
	} else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 80, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 220, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 100, "ゲームを続ける", GetColor(0, 0, 0), font100);


	//ボタンその2
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 280 < input.getMouseY() && input.getMouseY() < 420) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(255, 255, 0), true);
		point = 2;
	} else {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 255, 0), true);
	}
	DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 280, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 420, GetColor(0, 0, 0), false);
	DrawStringToHandle((SCREEN_SIZE_X / 2) - (100 * 3.5), 300, "最初から始める", GetColor(0, 0, 0), font100);

	//ボタンその3
	if ((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20 < input.getMouseX() && input.getMouseX() < (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20 && 480 < input.getMouseY() && input.getMouseY() < 620) {
		DrawBox((SCREEN_SIZE_X / 2) - (100 * 3.5) - 20, 480, (SCREEN_SIZE_X / 2) + (100 * 3.5) + 20, 620, GetColor(255, 255, 0), true);
		point = 3;
	} else {
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
			if (board.GetBoardSize() == 7) {
				board.reset();
			} else if (board.GetBoardSize() == 9) {
				board.resetMurora();
			} else if (board.GetBoardSize() == 15) {
				board.resetMega();
			} else {
				board.resetMoroi();
			}
			if (ComFlag == black) {
				hand.SetInputFlag(false);
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
