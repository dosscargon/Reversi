#pragma once
enum BorW {
	none,
	black,
	white,
	gray
};

enum gameMode {
	NORMAL,
	MURORA,
	MEGA,
	MOROI,
	CUSTOM8,
	CUSTOM16
};

//実際にオセロをする部分。ひっくり返したりターン制御したり。
class BoardNormal {
public:
	BoardNormal();
	~BoardNormal();
	void reset();
	void resetMurora();
	void resetMega();
	void resetMoroi();
	void resetCustom8();
	void resetCustom16();
	bool TurnChange();
	bool CheckPass(BorW turn);
	BorW GetBoard(int x, int y);
	void SetBoard(int x, int y, BorW bw);
	BorW GetTurn();
	int GetBoardSize();
	int CountStone(BorW color);
	bool put(int x, int y, bool checkOnly = false, BorW turn = none);
	int fall();
	void finish();
	BorW NotTurn(BorW turn);
	bool isFinish();
	gameMode getMode();

	void Com1();
	void Com1Murora();
	void Com1moroi();
	void Com2();
	void Com2Murora();
	void Com2moroi();

private:
	BorW board[16][16];
	BorW turn;
	int boardsize = 7;
	int pass=0;
	bool finishFlag = false;
	gameMode mode;
	BorW (*editingBoard)[16] = board;

	int check(BorW board, int c, int turn);
};
