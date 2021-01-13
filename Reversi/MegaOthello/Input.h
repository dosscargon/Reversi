#pragma once
class Input
{
//マウスからの情報を取得するクラス。
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