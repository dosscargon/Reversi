#pragma once
class Input
{
//�}�E�X����̏����擾����N���X�B
public:
	Input();
	~Input();
	void GetMouseInfo();
	int getMouseX();
	int getMouseY();
	bool getMouseClick();

private:
	int mouseX;
	int mouseY;
	bool mouseClick;
};