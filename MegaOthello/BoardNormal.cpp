#include "BoardNormal.h"
#include "DxLib.h"

BoardNormal::BoardNormal() {
}

BoardNormal::~BoardNormal() {
}

void BoardNormal::reset() {
	turn = black;
	boardsize = 7;
	finishFlag = false;
	mode = NORMAL;

	for (int i = 0; i < boardsize+1; i++) {
		for (int j = 0; j < boardsize+1; j++) {
			SetBoard(i, j, none);
			if ((i == 4 && j == 3) || (i == 3 && j == 4)) {
				SetBoard(i, j, black);
			}
			else if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
				SetBoard(i, j, white);
			}
		}
	}
}

void BoardNormal::resetMurora(){
	turn = black;
	boardsize = 9;
	finishFlag = false;
	mode = MURORA;

	for (int i = 0; i < boardsize+1; i++) {
		for (int j = 0; j < boardsize+1; j++) {
			SetBoard(i, j, none);
			if ((i == 5 && j == 4) || (i == 4 && j == 5)) {
				SetBoard(i, j, black);
			}
			else if ((i == 4 && j == 4) || (i == 5 && j == 5)) {
				SetBoard(i, j, white);
			}
			else if ((i == 0 || i == 9) && (j == 0 || j == 9)) {
				SetBoard(i, j, gray);
			}
		}
	}
}

void BoardNormal::resetMega() {
	turn = black;
	boardsize = 15;
	finishFlag = false;
	mode = MEGA;

	for (int i = 0; i < boardsize + 1; i++) {
		for (int j = 0; j < boardsize + 1; j++) {
			SetBoard(i, j, none);
			if ((i == 8 && j == 7) || (i == 7 && j == 8)) {
				SetBoard(i, j, black);
			}
			else if ((i == 7 && j == 7) || (i == 8 && j == 8)) {
				SetBoard(i, j, white);
			}
		}
	}
}

void BoardNormal::resetMoroi() {
	turn = black;
	boardsize = 11;
	finishFlag = false;
	mode = MOROI;

	for (int i = 0; i < boardsize + 1; i++) {
		for (int j = 0; j < boardsize + 1; j++) {
			SetBoard(i, j, none);
			if ((i == 6 && j == 5) || (i == 5 && j == 6)) {
				SetBoard(i, j, black);
			}
			else if ((i == 5 && j == 5) || (i == 6 && j == 6)) {
				SetBoard(i, j, white);
			}
		}
	}
}

void BoardNormal::resetCustom8() {
	reset();

	turn = gray;
	mode = CUSTOM8;
}

void BoardNormal::resetCustom16() {
	resetMega();

	turn = gray;
	mode = CUSTOM16;

}

//ターン交代。ついでに次に置く方がパスしなくても大丈夫かも返す。
bool BoardNormal::TurnChange() {
	bool result = false;

	if (turn == black) {
		turn = white;
	}
	else
	{
		turn = black;
	}

	for (int i = 0; i <= GetBoardSize(); i++) {
		for (int j = 0; j <= GetBoardSize(); j++) {
			if (put(i, j, true) == true) {
				result = true;
			}
		}
	}


	return result;
}

bool BoardNormal::CheckPass(BorW turn) {
	bool result=false;

	for (int i = 0; i <= GetBoardSize(); i++) {
		for (int j = 0; j <= GetBoardSize(); j++) {
			if (put(i, j, true,turn) == true) {
				result = true;
			}
		}
	}

	return result;
}

BorW BoardNormal::GetBoard(int x, int y) {
	return editingBoard[x][y];
}

void BoardNormal::SetBoard(int x, int y, BorW bw) {
	editingBoard[x][y] = bw;
}

BorW BoardNormal::GetTurn() {
	return turn;
}

int BoardNormal::GetBoardSize() {
	return boardsize;
}

int BoardNormal::CountStone(BorW color) {
	int result = 0;
	for (int i = 0; i <= GetBoardSize(); i++) {
		for (int j = 0; j <= GetBoardSize(); j++) {
			if (GetBoard(i, j) == color) {
				result++;
			}
		}
	}

	return result;
}

bool BoardNormal::put(int x, int y, bool checkOnly, BorW turn) {

	int result[8] = { 2 }; //それぞれ８方向の判定結果。真上から時計回り(0:すぐ隣が同じ色だからおけない,1:おける,2:壁のせいでおけない,3:空白のせいでおけない)0,2,3の区別は動作テストでのみ用いる。
						   //bool result[8];

	if (turn == none) {
		turn = GetTurn();
	}

	//カスタムモード
	if (x != -1 && y != -1) {
		if (turn == gray) {
			if (!checkOnly) {
				switch (GetBoard(x, y)) {
				case none:
					SetBoard(x, y, gray);
					break;
				case gray:
					SetBoard(x, y, black);
					break;
				case black:
					SetBoard(x, y, white);
					break;
				case white:
					SetBoard(x, y, none);
					break;
				}
				return true;
			}
		}
	}

	//置きたい場所が空白かどうか
	if (GetBoard(x, y) != 0 || (x == -1 || y == -1)) {
		return false;
	}

	//8方向それぞれひっくり返せるか確かめる。mode==1の時はひっくり返せるならひっくり返しちゃう
	//up
	{
		int c;
		int count;
		int i, j;

		for (i = x, j = y - 1, c = 0; j >= 0; j--, c++) {
			result[0] = check(GetBoard(i, j), c, turn);

			if (result[0] != 2) {
				break;
			}

		}
		if (checkOnly == false) {
			if (result[0] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x, j = y - 1, c = 0; c < count; j--, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}


		//upright
		for (i = x + 1, j = y - 1, c = 0; i <= boardsize && j >= 0; i++, j--, c++) {
			result[1] = check(GetBoard(i, j), c, turn);

			if (result[1] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[1] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x + 1, j = y - 1, c = 0; c < count; i++, j--, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}

		//right
		for (i = x + 1, j = y, c = 0; i <= boardsize; i++, c++) {

			result[2] = check(GetBoard(i, j), c, turn);

			if (result[2] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[2] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x + 1, j = y, c = 0; c < count; i++, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}

		//downright
		for (i = x + 1, j = y + 1, c = 0; i <= boardsize && j <= boardsize; i++, j++, c++) {

			result[3] = check(GetBoard(i, j), c, turn);

			if (result[3] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[3] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x + 1, j = y + 1, c = 0; c < count; i++, j++, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}

		//down
		for (i = x, j = y + 1, c = 0; j <= boardsize; j++, c++) {

			result[4] = check(GetBoard(i, j), c, turn);

			if (result[4] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[4] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x, j = y + 1, c = 0; c < count; i, j++, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}

		//downledt
		for (i = x - 1, j = y + 1, c = 0; i >= 0 && j <= boardsize; i--, j++, c++) {

			result[5] = check(GetBoard(i, j), c, turn);

			if (result[5] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[5] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x - 1, j = y + 1, c = 0; c < count; i--, j++, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}

		//ledt
		for (i = x - 1, j = y, c = 0; i >= 0; i--, c++) {

			result[6] = check(GetBoard(i, j), c, turn);

			if (result[6] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[6] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x - 1, j = y, c = 0; c < count; i--, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}

		//upleft
		for (i = x - 1, j = y - 1, c = 0; i >= 0 && j >= 0; i--, j--, c++) {

			result[7] = check(GetBoard(i, j), c, turn);

			if (result[7] != 2) {
				break;
			}
		}
		if (checkOnly == false) {
			if (result[7] == 1) {
				count = c;
				//printf("%d\n",count);//動作テスト用
				for (i = x - 1, j = y - 1, c = 0; c < count; i--, j--, c++) {
					//printf("%d %d\n",x,y);//動作テスト用

					SetBoard(i, j, turn);
				}
			}
		}
	}

	if (result[0] == 1 || result[1] == 1 || result[2] == 1 || result[3] == 1 || result[4] == 1 || result[5] == 1 || result[6] == 1 || result[7] == 1) {
		if (checkOnly == false) {
			SetBoard(x, y, turn);

			pass = 0;
		}
		return true;
	}
	else {
		return false;
	}

}

//checkput関数のチェック処理をするところをまとめたもの。mainからは呼び出さない
int BoardNormal::check(BorW board, int c, int turn) {
	//黒の番のとき
	if (turn == black) {
		switch (board) {
		case black:
			if (c == 0) {
				return 0;
			}
			else {
				return 1;
			}
		case none:
			return 3;
		case gray:
			return 4;
		default:
			return 2;
		}

		//白の番のとき
	}
	else if (turn == white) {
		switch (board) {
		case white:
			if (c == 0) {
				return 0;
			}
			else {
				return 1;
			}
		case none:
			return 3;
		case gray:
			return 4;
		default:
			return 2;
		}
	}

	return 4;
}

int BoardNormal::fall() {
	int r;
	int nonenum = 0;
	for (int i=0; i <= boardsize; i++) {
		for (int j=0; j <= boardsize; j++) {
			if (GetBoard(i, j) == none) {
				nonenum++;
			}
		}
	}
	if (nonenum == 0) { return 0; }
	r = GetRand(nonenum - 1) + 1;

	nonenum = 0;
	for (int i=0; i <= boardsize; i++) {
		for (int j=0; j <= boardsize; j++) {
			if (GetBoard(i, j) == none) {
				nonenum++;
				if (r == nonenum) {
					SetBoard(i, j, gray);
					return 1;
				}
			}
		}
	}
}

void BoardNormal::finish() {
	finishFlag = true;
}

BorW BoardNormal::NotTurn(BorW turn) {
	if (turn == black) {
		return white;
	}
	else if (turn == white) {
		return black;
	}
	else {
		return turn;
	}
}

bool BoardNormal::isFinish() {
	return finishFlag;
}

gameMode BoardNormal::getMode() {
	return mode;
}

void BoardNormal::Com1() {
	//COMの思考ルーチン。自分のおける場所がどれくらいあるか、相手のおける場所がどれくらいあるかを基準に考える。相手のおける場所をなくす傾向強め
	//たぶん少なくともりんなよりは強い
	BorW boardcopy[16][16];//シミュレート用の盤面のコピー
	int mytecount, usertecount;//置ける場所がどれくらいあるか覚えとく
	int score[16][16] = { -1000 };//マスごとの得点。これが一番高いところに置く。
	int memox, memoy, memos = -1000;//スコア比較用変数

	BorW userturn;

	if (GetTurn() == black) {
		userturn = white;
	}
	else if (GetTurn() == white) {
		userturn = black;
	}

	for (int j = 0; j<boardsize+1; j++) {
		for (int i = 0; i<boardsize+1; i++) {
			score[i][j] = -1001;
		}
	}

	for (int y = 0; y < boardsize + 1; y++) {
		for (int x = 0; x < boardsize + 1; x++) {
			//いじくってもいいように盤面をコピーする
			for (int j = 0; j<=boardsize; j++) {
				for (int i = 0; i<=boardsize; i++) {
					boardcopy[i][j] = board[i][j];
				}
			}
			editingBoard = boardcopy;

			//コピーした盤面に試しに置いてみて自分と相手のおける場所を数える
			mytecount = 0;
			usertecount = 0;

			if (put(x, y) == true) {

				for (int j = 0; j<=boardsize; j++) {
					for (int i = 0; i<=boardsize; i++) {
						if (put(i, j, true, GetTurn())) {
							mytecount++;
						}
						if (put(i, j, true, userturn)) {
							usertecount++;
						}

					}
				}
				//採点
				score[x][y] = mytecount - 2 * usertecount;
				if ((x == 0 || x == boardsize) && (y == 0 || y == boardsize)) {
					score[x][y] += 10;
				} else if ((x <= 1 || boardsize - 1 <= x) && (y <= 1 || boardsize - 1 <= y)) {
					score[x][y] -= 10;
				}
			}
			else {
				score[x][y] = -1000;
			}

		}
	}

	//点数比較
	for (int y = 0; y<=boardsize; y++) {
		for (int x = 0; x<=boardsize; x++) {
			//printf("%d %d %d \n",x,y,score[x][y]);//動作確認用
			if (score[x][y] > memos) {
				memox = x;
				memoy = y;
				memos = score[x][y];
			}
		}
	}

	editingBoard = board;
	if (!put(memox, memoy)) {
		OutputDebugString("COMERROR\n");
	}

}

void BoardNormal::Com1Murora() {
	//COMの思考ルーチン。自分のおける場所がどれくらいあるか、相手のおける場所がどれくらいあるかを基準に考える。相手のおける場所をなくす傾向強め
	//たぶん少なくともりんなよりは強い
	BorW boardcopy[16][16];//シミュレート用の盤面のコピー
	int mytecount, usertecount;//置ける場所がどれくらいあるか覚えとく
	int score[16][16] = { -1000 };//マスごとの得点。これが一番高いところに置く。
	int memox, memoy, memos = -1000;//スコア比較用変数

	BorW userturn;

	if (GetTurn() == black) {
		userturn = white;
	}
	else if (GetTurn() == white) {
		userturn = black;
	}

	for (int j = 0; j<8; j++) {
		for (int i = 0; i<8; i++) {
			score[i][j] = -1001;
		}
	}

	for (int y = 0; y < boardsize + 1; y++) {
		for (int x = 0; x < boardsize + 1; x++) {
			//いじくってもいいように盤面をコピーする
			for (int j = 0; j <= boardsize; j++) {
				for (int i = 0; i <= boardsize; i++) {
					boardcopy[i][j] = board[i][j];
				}
			}
			editingBoard = boardcopy;

			//コピーした盤面に試しに置いてみて自分と相手のおける場所を数える
			mytecount = 0;
			usertecount = 0;



			if (put(x, y) == 1) {

				for (int j = 0; j<boardsize + 1; j++) {
					for (int i = 0; i<boardsize + 1; i++) {
						if (put(i, j, true, GetTurn())) {
							mytecount++;
						}
						if (put(i, j, true, userturn)) {
							usertecount++;
						}

					}
				}
				//採点
				score[x][y] = mytecount - 2 * usertecount;
				if (((x == 1 || x == 8) && (y == 0 || y == 9)) || ((x == 0 || x == 9) && (y == 1 || y == 8))) {
					score[x][y] += 20;
				}
				else if (((x <= 2 || x >= 7) && (y <= 1 || y >= 8)) || ((x <= 1 || x >= 8) && (y <= 2 || y >= 7))) {
					score[x][y] -= 20;
				}
			}
			else {
				score[x][y] = -1000;
			}

		}
	}

	//点数比較
	for (int y = 0; y<boardsize + 1; y++) {
		for (int x = 0; x<boardsize + 1; x++) {
			//printf("%d %d %d \n",x,y,score[x][y]);//動作確認用
			if (score[x][y]>memos) {
				memox = x;
				memoy = y;
				memos = score[x][y];
			}
		}
	}

	editingBoard = board;
	put(memox, memoy);

}

void BoardNormal::Com1moroi() {
	BorW boardcopy[16][16];//シミュレート用の盤面のコピー
	int mytecount, usertecount;//置ける場所がどれくらいあるか覚えとく
	int score[16][16] = { -1000 };//マスごとの得点。これが一番高いところに置く。
	int memox, memoy, memos = -1000;//スコア比較用変数

	BorW userturn;

	if (GetTurn() == black) {
		userturn = white;
	}
	else if (GetTurn() == white) {
		userturn = black;
	}

	for (int j = 0; j<boardsize + 1; j++) {
		for (int i = 0; i<boardsize + 1; i++) {
			score[i][j] = -1001;
		}
	}

	for (int y = 0; y < boardsize + 1; y++) {
		for (int x = 0; x < boardsize + 1; x++) {
			//いじくってもいいように盤面をコピーする
			for (int j = 0; j <= boardsize; j++) {
				for (int i = 0; i <= boardsize; i++) {
					boardcopy[i][j] = board[i][j];
				}
			}
			editingBoard = boardcopy;

			//コピーした盤面に試しに置いてみて自分と相手のおける場所を数える
			mytecount = 0;
			usertecount = 0;

			if (put(x, y) == 1) {
				for (int j = 0; j <= boardsize; j++) {
					for (int i = 0; i <= boardsize; i++) {
						if (put(i, j, true, GetTurn())) {
							mytecount++;
						}
						if (put(i, j, true, userturn)) {
							usertecount++;
						}

					}
				}
				//採点
				score[x][y] = mytecount - 2 * usertecount;
			}
			else {
				score[x][y] = -1000;
			}

		}
	}

	//点数比較
	for (int y = 0; y <= boardsize; y++) {
		for (int x = 0; x <= boardsize; x++) {
			//printf("%d %d %d \n",x,y,score[x][y]);//動作確認用
			if (score[x][y]>memos) {
				memox = x;
				memoy = y;
				memos = score[x][y];
			}
		}
	}


	editingBoard = board;
	put(memox, memoy);

}

void BoardNormal::Com2() {
	//COMの思考ルーチン。自分のおける場所がどれくらいあるか、相手のおける場所がどれくらいあるかを基準に考える。相手のおける場所をなくす傾向強め
	//たぶん少なくともりんなよりは強い
	BorW boardcopy[16][16];//シミュレート用の盤面のコピー
	int mytecount, usertecount;//置ける場所がどれくらいあるか覚えとく
	int score[16][16] = { 1000 };//マスごとの得点。これが一番高いところに置く。
	int memox, memoy, memos = 1000;//スコア比較用変数

	BorW userturn;

	if (GetTurn() == black) {
		userturn = white;
	}
	else if (GetTurn() == white) {
		userturn = black;
	}

	for (int j = 0; j<boardsize+1; j++) {
		for (int i = 0; i<boardsize+1; i++) {
			score[i][j] = -1001;
		}
	}

	for (int y = 0; y < boardsize + 1; y++) {
		for (int x = 0; x < boardsize + 1; x++) {
			//いじくってもいいように盤面をコピーする
			for (int j = 0; j <= boardsize; j++) {
				for (int i = 0; i <= boardsize; i++) {
					boardcopy[i][j] = board[i][j];
				}
			}
			editingBoard = boardcopy;

			//コピーした盤面に試しに置いてみて自分と相手のおける場所を数える
			mytecount = 0;
			usertecount = 0;



			if (put(x, y) == 1) {

				for (int j = 0; j<boardsize + 1; j++) {
					for (int i = 0; i<boardsize + 1; i++) {
						if (put(i, j, true, GetTurn())) {
							mytecount++;
						}
						if (put(i, j, true, userturn)) {
							usertecount++;
						}

					}
				}
				//採点
				score[x][y] = mytecount - 2 * usertecount;
				if ((x == 0 || x == boardsize) && (y == 0 || y == boardsize)) {
					score[x][y] += 10;
				} else if ((x <= 1 || boardsize - 1 <= x) && (y <= 1 || boardsize - 1 <= y)) {
					score[x][y] -= 10;
				}
			}
			else {
				score[x][y] = 1000;
			}

		}
	}

	//点数比較
	for (int y = 0; y<boardsize + 1; y++) {
		for (int x = 0; x<boardsize + 1; x++) {
			//printf("%d %d %d \n",x,y,score[x][y]);//動作確認用
			if (score[x][y] < memos) {
				memox = x;
				memoy = y;
				memos = score[x][y];
			}
		}
	}


	editingBoard = board;
	put(memox, memoy);

}

void BoardNormal::Com2Murora() {
	//COMの思考ルーチン。自分のおける場所がどれくらいあるか、相手のおける場所がどれくらいあるかを基準に考える。相手のおける場所をなくす傾向強め
	//たぶん少なくともりんなよりは強い
	BorW boardcopy[16][16];//シミュレート用の盤面のコピー
	int mytecount, usertecount;//置ける場所がどれくらいあるか覚えとく
	int score[16][16] = { 1000 };//マスごとの得点。これが一番高いところに置く。
	int memox, memoy, memos = 1000;//スコア比較用変数

	BorW userturn;

	if (GetTurn() == black) {
		userturn = white;
	}
	else if (GetTurn() == white) {
		userturn = black;
	}

	for (int j = 0; j<boardsize+1; j++) {
		for (int i = 0; i<boardsize+1; i++) {
			score[i][j] = -1001;
		}
	}

	for (int y = 0; y < boardsize + 1; y++) {
		for (int x = 0; x < boardsize + 1; x++) {
			//いじくってもいいように盤面をコピーする
			for (int j = 0; j <= boardsize; j++) {
				for (int i = 0; i <= boardsize; i++) {
					boardcopy[i][j] = board[i][j];
				}
			}
			editingBoard = boardcopy;

			//コピーした盤面に試しに置いてみて自分と相手のおける場所を数える
			mytecount = 0;
			usertecount = 0;



			if (put(x, y) == 1) {

				for (int j = 0; j<boardsize + 1; j++) {
					for (int i = 0; i<boardsize + 1; i++) {
						if (put(i, j, true, GetTurn())) {
							mytecount++;
						}
						if (put(i, j, true, userturn)) {
							usertecount++;
						}

					}
				}
				//採点
				score[x][y] = mytecount - 2 * usertecount;
				if (((x == 1 || x == boardsize+1) && (y == 0 || y == 9)) || ((x == 0 || x == 9) && (y == 1 || y == boardsize+1))) {
					score[x][y] += 20;
				}
				else if (((x <= 2 || x >= boardsize) && (y <= 1 || y >= boardsize+1)) || ((x <= 1 || x >= boardsize+1) && (y <= 2 || y >= boardsize))) {
					score[x][y] -= 20;
				}
			}
			else {
				score[x][y] = 1000;
			}

		}
	}

	//点数比較
	for (int y = 0; y<boardsize + 1; y++) {
		for (int x = 0; x<boardsize + 1; x++) {
			//printf("%d %d %d \n",x,y,score[x][y]);//動作確認用
			if (score[x][y]<memos) {
				memox = x;
				memoy = y;
				memos = score[x][y];
			}
		}
	}
	

	editingBoard = board;
	put(memox, memoy);

}

void BoardNormal::Com2moroi() {
	BorW boardcopy[16][16];//シミュレート用の盤面のコピー
	int mytecount, usertecount;//置ける場所がどれくらいあるか覚えとく
	int score[16][16] = { 1000 };//マスごとの得点。これが一番高いところに置く。
	int memox, memoy, memos = 1000;//スコア比較用変数

	BorW userturn;

	if (GetTurn() == black) {
		userturn = white;
	}
	else if (GetTurn() == white) {
		userturn = black;
	}

	for (int j = 0; j<boardsize + 1; j++) {
		for (int i = 0; i<boardsize + 1; i++) {
			score[i][j] = -1001;
		}
	}

	for (int y = 0; y < boardsize + 1; y++) {
		for (int x = 0; x < boardsize + 1; x++) {
			//いじくってもいいように盤面をコピーする
			for (int j = 0; j <= boardsize; j++) {
				for (int i = 0; i <= boardsize; i++) {
					boardcopy[i][j] = board[i][j];
				}
			}
			editingBoard = boardcopy;

			//コピーした盤面に試しに置いてみて自分と相手のおける場所を数える
			mytecount = 0;
			usertecount = 0;



			if (put(x, y) == 1) {

				for (int j = 0; j<boardsize + 1; j++) {
					for (int i = 0; i<boardsize + 1; i++) {
						if (put(i, j, true, GetTurn())) {
							mytecount++;
						}
						if (put(i, j, true, userturn)) {
							usertecount++;
						}

					}
				}
				//採点
				score[x][y] = mytecount - 2 * usertecount;
			}
			else {
				score[x][y] = 1000;
			}

		}
	}

	//点数比較
	for (int y = 0; y<boardsize + 1; y++) {
		for (int x = 0; x<boardsize + 1; x++) {
			//printf("%d %d %d \n",x,y,score[x][y]);//動作確認用
			if (score[x][y] < memos) {
				memox = x;
				memoy = y;
				memos = score[x][y];
			}
		}
	}


	editingBoard = board;
	put(memox, memoy);

}