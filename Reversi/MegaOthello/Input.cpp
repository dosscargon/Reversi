#include "DxLib.h"
#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::GetMouseInfo() {
	GetMousePoint(&mouseX, &mouseY);
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		mouseClick = TRUE;
	}
	else
	{
		mouseClick = FALSE;
	}
}

int Input:: getMouseX() {
	return mouseX;
}

int Input::getMouseY() {
	return mouseY;
}

bool Input::getMouseClick() {
	return mouseClick;
}

