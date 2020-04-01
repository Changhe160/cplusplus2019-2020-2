#pragma once

#include <string>

using std::string;


class PlateGUIInfo
{
public:
	// Constructors
	PlateGUIInfo();
	PlateGUIInfo(string strLabel, POINT textCoor, RECT rect, int width, int height);

	// Getters and setters :)
	POINT GetPlateCoordinate();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	RECT GetRect();
	POINT GetTextCoor();
	string GetLabel();

	// Change plate coordinates
	void MoveCoordinateTo(int, int);

	~PlateGUIInfo(void);
private:
	int width, height;
	RECT rect;
	POINT textCoor;
	string strLabel;
};
