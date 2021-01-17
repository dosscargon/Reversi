#include"Hand.h"



Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::CheckPoint(int MouseX,int MouseY,int boardsize) {
	pointX = -1;
	pointY = -1;
	for (int i = 0; i < boardsize+1; i++) {
		for (int j = 0; j < (boardsize+1); j++) {
			if (i*(720 / (boardsize+1)) < MouseX && j*(720 / (boardsize+1)) < MouseY && MouseX < (i + 1)*(720 / (boardsize+1)) && MouseY < (j + 1)*(720 / (boardsize+1))) {
				 
				pointX = i;
				pointY = j;
			}
		}
	}
}

void Hand::SetClick(bool input) {
	clickOld = click;
	click = input;
}

//マウスが押されたかどうか
bool Hand::CheckMouseDown() {
	if (inputFlag == true) {
		if (clickOld == false && click == true) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Hand::CheckMouseLeave() {
	if (inputFlag == true) {
		if (clickOld == true && click == false) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

//inputFlagに関係ないクリック判定
bool Hand::CheckMouseDownNoCheckFlag() {
	if (clickOld == false && click == true) {
		return true;
	}
	else {
		return false;
	}
}

int Hand::GetPointX() {
	return pointX;
}

int Hand::GetPointY() {
	return pointY;
}

void Hand::SetInputFlag(bool input) {
	inputFlag = input;
}

bool Hand::GetInputFlag() {
	return inputFlag;
}