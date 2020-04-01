#include "StdAfx.h"
#include "PlateGUIInfo.h"

PlateGUIInfo::PlateGUIInfo()
{
}

PlateGUIInfo::PlateGUIInfo(string strLabel, POINT textCoor, RECT rect, int width, int height)
{
	this->strLabel = strLabel;
	this->textCoor = textCoor;
	this->rect = rect;
	this->width = width;
	this->height = height;
}

POINT PlateGUIInfo::GetPlateCoordinate()
{
	POINT coord;
	coord.x = this->rect.left;
	coord.y = this->rect.top;
	return coord;
}

int PlateGUIInfo::GetX()
{
	return this->rect.left;
}

int PlateGUIInfo::GetY()
{
	return this->rect.top;
}

int PlateGUIInfo::GetWidth()
{
	return this->width;
}

int PlateGUIInfo::GetHeight()
{
	return this->height;
}

void PlateGUIInfo::MoveCoordinateTo(int x, int y)
{
	this->rect.left = x;
	this->rect.top = y;
	this->rect.right = x + this->width;
	this->rect.bottom = y + this->height;
}

POINT PlateGUIInfo::GetTextCoor()
{
	return this->textCoor;
}

RECT PlateGUIInfo::GetRect()
{
	return this->rect;
}

string PlateGUIInfo::GetLabel()
{
	return this->strLabel;
}

PlateGUIInfo::~PlateGUIInfo(void)
{
	// do nothing
}