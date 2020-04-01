#include "StdAfx.h"
#include "HanoiDrawer.h"


int const HanoiDrawer::SOURCE = 1;
int const HanoiDrawer::INTERMEDIATE = 2;
int const HanoiDrawer::DESTINATION = 3;
int const HanoiDrawer::STAND_WIDTH = 40;
int const HanoiDrawer::STAND_HEIGHT = 400;
int const HanoiDrawer::PLATE_HEIGHT = 18;
int const HanoiDrawer::INIT_PLATES_COUNT = 3;
int const HanoiDrawer::MAX_PALTES_COUNT = 6;
int const HanoiDrawer::MIN_PALTES_COUNT = 1;
int const HanoiDrawer::DEFAULT_PALTES_COUNT = 4;
int const HanoiDrawer::DEFAULT_STEP_TIME = 2000;
int const HanoiDrawer::MAX_STEP_TIME_IN_SECONDS = 6;
int const HanoiDrawer::MIN_STEP_TIME_IN_SECONDS = 1;


HanoiDrawer::HanoiDrawer()
{
	this->hdc = NULL;
	this->iPlatesCount = 0;
	this->autoSolve = false;
	this->iMovesCount = 0;
	this->stand1.clear();
	this->stand2.clear();
	this->stand3.clear();
	this->listStand1GUI.clear();
	this->listStand2GUI.clear();
	this->listStand3GUI.clear();
	this->solved = false;
}

HanoiDrawer::HanoiDrawer(HDC hdc)
{
	this->hdc = hdc;
	this->iPlatesCount = 0;
	this->autoSolve = false;
	this->iMovesCount = 0;
	this->stand1.clear();
	this->stand2.clear();
	this->stand3.clear();
	this->listStand1GUI.clear();
	this->listStand2GUI.clear();
	this->listStand3GUI.clear();
	this->solved = false;
}

HanoiDrawer::HanoiDrawer(HDC hdc, int iPlatesCount)
{
	this->hdc = hdc;
	this->iPlatesCount = iPlatesCount;
	this->autoSolve = false;
	this->iMovesCount = 0;
	this->stand1.clear();
	this->stand2.clear();
	this->stand3.clear();
	this->listStand1GUI.clear();
	this->listStand2GUI.clear();
	this->listStand3GUI.clear();
	this->solved = false;
}

HanoiDrawer::HanoiDrawer(HDC hdc=NULL, int platesCount=HanoiDrawer::MIN_PALTES_COUNT, bool autoSolve=false, int movesCount=0)
{
	this->hdc = hdc;
	this->iPlatesCount = platesCount;
	this->autoSolve = autoSolve;
	this->iMovesCount = movesCount;
	this->stand1.clear();
	this->stand2.clear();
	this->stand3.clear();
	this->listStand1GUI.clear();
	this->listStand2GUI.clear();
	this->listStand3GUI.clear();
	this->solved = false;
}

void HanoiDrawer::SetStandCoordinates(Stand stand, int left, int top)
{
	switch (stand)
	{
	case No1 :
		this->arrStandsCoor[0] = HanoiDrawer::PointF(left, top);
		break;
	case No2:
		this->arrStandsCoor[1] = HanoiDrawer::PointF(left, top);
		break;
	case No3:
		this->arrStandsCoor[2] = HanoiDrawer::PointF(left, top);
		break;
	}
}

void HanoiDrawer::DrawStands()
{
	DrawOneStand(No1);
	DrawOneStand(No2);
	DrawOneStand(No3);
}

void HanoiDrawer::DrawOneStand(Stand stand)
{
	Rectangle(this->hdc, this->arrStandsCoor[stand].x, this->arrStandsCoor[stand].y, this->arrStandsCoor[stand].x + STAND_WIDTH, this->arrStandsCoor[stand].y + STAND_HEIGHT);
}

void HanoiDrawer::DrawPlates()
{
	DrawPlates(No1, this->stand1);
	DrawPlates(No2, this->stand2);
	DrawPlates(No3, this->stand3);
}

void HanoiDrawer::DrawPlates(Stand stand, list<int> listPlates)
{
	DrawPlatesInList(No1, this->stand1);
	DrawPlatesInList(No2, this->stand2);
	DrawPlatesInList(No3, this->stand3);
}

void HanoiDrawer::DrawPlatesInList(Stand stand, list<int> listPlates)
{
	list <int>::iterator listPlatesIter;
	int i=0, plateNumber;
	double plateWidth;
	const int TEXT_OFFSET_IN_PLATE = 4;
	const double PLATE_SIZE_ENLARGMENT_CONSTANT = 1.1;

	double x1, y1, x2, y2;
	POINT textCoor;
	RECT rectArea;
	string strPlateLabel;

	// clearing plates in a specific GUI's list
	switch(stand)
	{
	case No1:
		listStand1GUI.clear();
		break;
	case No2:
		listStand2GUI.clear();
		break;
	case No3:
		listStand3GUI.clear();
		break;
	}

	for (listPlatesIter = listPlates.begin();listPlatesIter!=listPlates.end();listPlatesIter++)
	{
		plateNumber = *listPlatesIter;
		plateWidth = STAND_WIDTH/2 * plateNumber * PLATE_SIZE_ENLARGMENT_CONSTANT;

		x1 = this->arrStandsCoor[stand].x - plateWidth + STAND_WIDTH / 2;
		y1 = this->arrStandsCoor[stand].y + STAND_HEIGHT - PLATE_HEIGHT * i - PLATE_HEIGHT;
		x2 = this->arrStandsCoor[stand].x + plateWidth + STAND_WIDTH / 2;
		y2 = this->arrStandsCoor[stand].y + STAND_HEIGHT - PLATE_HEIGHT * i;

		rectArea.left = x1;
		rectArea.top = y1;
		rectArea.right = x2;
		rectArea.bottom = y2;
		textCoor.x = x1 + plateWidth - TEXT_OFFSET_IN_PLATE;
		textCoor.y = y1+1;

		strPlateLabel = Tools::IntToString(plateNumber);
		PlateGUIInfo* currentPlateGUIInfo = new PlateGUIInfo(strPlateLabel, textCoor, rectArea, x2-x1, y2-y1);

		// adding plate to a specific GUI's list
		switch(stand)
		{
		case No1:
			listStand1GUI.push_back(currentPlateGUIInfo);
			break;
		case No2:
			listStand2GUI.push_back(currentPlateGUIInfo);
			break;
		case No3:
			listStand3GUI.push_back(currentPlateGUIInfo);
			break;
		}

		DrawGUIPlate(strPlateLabel, textCoor, rectArea);
		i++;
	}
}

void HanoiDrawer::DrawGUIPlate(string textString, POINT textCoor, RECT drawingArea)
{
	COLORREF fillColor = RGB(0xff,0x00,0x00) // red ;)
		, borderColor = RGB(0x00,0x00,0x00);  // black

	SelectObject(this->hdc, CreatePen(PS_SOLID, 1, borderColor));
	SelectObject(this->hdc, CreateSolidBrush(fillColor));

	Ellipse(this->hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

	// THE FIX: by setting the background mode 
	// to transparent, the region is the text itself
	SetBkMode(this->hdc, TRANSPARENT);
	SetTextColor(this->hdc, RGB(0xff,0xff,0x00));

	TextOut(this->hdc, textCoor.x, textCoor.y, textString.c_str(), textString.length());
}

void HanoiDrawer::PopulatePlatesList()
{
	this->iMovesCount = 0;
	this->stand1.clear();
	for (int i = this->iPlatesCount; i > 0; i--)
	{
		this->stand1.push_back(i);
	}

	this->DrawPlates();
}

void HanoiDrawer::SolveNextStep()
{
	int platesCount
		, source
		, destination
		, intermediate;

	if(listSavedState.size()==0)
	{
		this->Hanoi(this->iPlatesCount, HanoiDrawer::SOURCE, HanoiDrawer::DESTINATION, HanoiDrawer::INTERMEDIATE);
	}

	if(listSavedState.size() % 4 != 0 )
	{
		return;
	}

	platesCount = listSavedState.front();
	listSavedState.pop_front();

	source = listSavedState.front();
	listSavedState.pop_front();

	destination = listSavedState.front();
	listSavedState.pop_front();

	intermediate = listSavedState.front();
	listSavedState.pop_front();

	MovePlateFromTo(source, destination);

	this->iMovesCount++;

	if(iMovesCount == this->GetTotalMovesCount())
	{
		this->solved = true;
	}

	SetDlgItemInt(this->hWnd, this->countContainerResourceId, GetMovesCount(), FALSE);

	SetDlgItemText(this->hWnd, this->fromContainerResourceId, PlaceIntToString(source).c_str() );
	SetDlgItemText(this->hWnd, this->toContainerResourceId, PlaceIntToString(destination).c_str() );
	SetDlgItemText(this->hWnd, this->throughContainerResourceId, PlaceIntToString(intermediate).c_str() );
}

bool HanoiDrawer::IsSolved()
{
	return this->solved;
}

void HanoiDrawer::ReDraw()
{
	DrawStands();
	DrawPlates();

	Invalidate();
}

void HanoiDrawer::Invalidate()
{
	RECT rect;
	GetClientRect(this->hWnd, &rect);
	InvalidateRect(this->hWnd, &rect, TRUE);
}


void HanoiDrawer::Hanoi(int platesCount, int source, int destination, int intermediate)
{
	if (platesCount == 1)
	{
		listSavedState.push_back(platesCount);
		listSavedState.push_back(source);
		listSavedState.push_back(destination);
		listSavedState.push_back(intermediate);
		return;
	}
	else
	{
		Hanoi(platesCount - 1, source, intermediate, destination);
		Hanoi(1, source, destination, intermediate);
		Hanoi(platesCount - 1, intermediate, destination, source);
		return;
	}
}

int HanoiDrawer::GetMovesCount()
{
	return this->iMovesCount;
}

int HanoiDrawer::GetTotalMovesCount()
{
	return (pow((double)2, (double)this->iPlatesCount) - 1);
}

bool HanoiDrawer::GetAutoSolve()
{
	return this->autoSolve;
}

int HanoiDrawer::GetPlatesCount()
{
	return this->iPlatesCount;
}

void HanoiDrawer::SetAutoSolve(bool value)
{
	this->autoSolve = value;
}

void HanoiDrawer::SetOwnerInstance(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}
void HanoiDrawer::SetOwner(HWND hWnd)
{
	this->hWnd = hWnd;
}

void HanoiDrawer::SetHDC(HDC hdc)
{
	this->hdc = hdc;
}

void HanoiDrawer::SetCountContainer(int resourceId)
{
	this->countContainerResourceId = resourceId;
}

void HanoiDrawer::SetFromTextContainer(int resourceId)
{
	this->fromContainerResourceId = resourceId;
}

void HanoiDrawer::SetToTextContainer(int resourceId)
{
	this->toContainerResourceId = resourceId;
}

void HanoiDrawer::SetThroughTextContainer(int resourceId)
{
	this->throughContainerResourceId = resourceId;
}

void HanoiDrawer::SetPlatesCount(int platesCount)
{
	if(platesCount>HanoiDrawer::MAX_PALTES_COUNT || platesCount<HanoiDrawer::MIN_PALTES_COUNT)
	{
		platesCount = HanoiDrawer::MAX_PALTES_COUNT;
	}
	this->iPlatesCount = platesCount;
	this->PopulatePlatesList();
}

void HanoiDrawer::SetStepTime(int seconds)
{
	if(seconds<MAX_STEP_TIME_IN_SECONDS && seconds>MIN_STEP_TIME_IN_SECONDS)
	{
		this->iStepTime = seconds * 1000;
	}
	else
	{
		this->iStepTime = DEFAULT_STEP_TIME;
	}
}

int HanoiDrawer::GetStepTime()
{
	return this->iStepTime;
}

void HanoiDrawer::MovePlateFromTo(int source, int destination)
{
	int element;

	switch(source - 1)	// subtract one from "source" to convert
						// it to number represents index
	{
	case 0:
		element = GetListElement(stand1, stand1.size() - 1);
		break;
	case 1:
		element = GetListElement(stand2, stand2.size() - 1);
		break;
	case 2:
		element = GetListElement(stand3, stand3.size() - 1);
		break;
	}

	if(element != LIST_ELEMENT_NOT_FOUND)
	{
		switch(source - 1)
		{
		case 0:
			stand1.remove(element);
			break;
		case 1:
			stand2.remove(element);
			break;
		case 2:
			stand3.remove(element);
			break;
		}

		switch(destination - 1)
		{
		case 0:
			stand1.push_back(element);
			break;
		case 1:
			stand2.push_back(element);
			break;
		case 2:
			stand3.push_back(element);
			break;
		}
	}

	ReDraw();
}

int HanoiDrawer::GetListElement(list<int> aList, int index)
{
	list<int>::iterator myIterator = aList.begin();

	for ( int i=0; myIterator != aList.end(); myIterator++, i++ )
	{
		if(i==index)
		{
			return *myIterator;
		}
	}

	return LIST_ELEMENT_NOT_FOUND;
}

string HanoiDrawer::PlaceIntToString(int placeNum)
{
	switch(placeNum)
	{
	case 1:
		return "Source";
		break;
	case 2:
		return "Intermediate";
		break;
	case 3:
		return "Destination";
		break;

	}
	return "";
}

void HanoiDrawer::ShowCurrentStepInfo()
{
	ShowWindow(GetDlgItem(this->hWnd, this->fromContainerResourceId), TRUE);
	ShowWindow(GetDlgItem(this->hWnd, this->toContainerResourceId), TRUE);
	ShowWindow(GetDlgItem(this->hWnd, this->throughContainerResourceId), TRUE);
}

void HanoiDrawer::HideCurrentStepInfo()
{
	ShowWindow(GetDlgItem(this->hWnd, this->fromContainerResourceId), FALSE);
	ShowWindow(GetDlgItem(this->hWnd, this->toContainerResourceId), FALSE);
	ShowWindow(GetDlgItem(this->hWnd, this->throughContainerResourceId), FALSE);
}

HanoiDrawer::~HanoiDrawer()
{
	this->stand1.clear();
	this->stand2.clear();
	this->stand3.clear();
	this->listStand1GUI.clear();
	this->listStand2GUI.clear();
	this->listStand3GUI.clear();
}