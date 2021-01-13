#pragma once
class Hand
{
//Input�֐��œ��������g���āA�v���C���[���ǂ��ɒu���������߂�N���X
public:
	Hand();
	~Hand();
	void CheckPoint(int MouseX, int MouseY,int boardsize);
	void SetClick(bool input);
	bool CheckMouseDown();
	bool CheckMouseLeave();
	bool CheckMouseDownNoCheckFlag();
	int GetPointX();
	int GetPointY();
	void SetInputFlag(bool input);
	bool GetInputFlag();

private:
	int pointX;
	int pointY;
	bool click = false;
	bool clickOld = false;
	bool inputFlag = true;
};