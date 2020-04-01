#pragma once

#include "Tools.h"
#include "PlateGUIInfo.h"
#include <list>
#include <cmath>

#define LIST_ELEMENT_NOT_FOUND -1

using std::list;
using std::abs;

class HanoiDrawer
{
public:
	
	// Represents the tower
	enum Stand
	{
		Nothing = -1,
		No1 = 0,
		No2 = 1,
		No3 = 2
	};

	// Used for specify the coordinates
	struct PointF
	{
		PointF()
		{
			x = y = 0;
		}

		PointF(double dx,double dy)
		{
			x = dx;
			y = dy;
		}

		double x, y;
	};

	// constants
	static const int DEFAULT_PALTES_COUNT
		, DEFAULT_STEP_TIME
		, SOURCE
		, DESTINATION
		, INTERMEDIATE
		, STAND_WIDTH
		, STAND_HEIGHT		
		, PLATE_HEIGHT
		, INIT_PLATES_COUNT
		, MAX_PALTES_COUNT
		, MIN_PALTES_COUNT
		, MAX_STEP_TIME_IN_SECONDS
		, MIN_STEP_TIME_IN_SECONDS
		;

	// Constructor
	HanoiDrawer();
	HanoiDrawer(HDC);
	HanoiDrawer(HDC, int);
	HanoiDrawer(HDC, int, bool, int);

	// Adjust stand in App main window
	void SetStandCoordinates(Stand, int, int);
	// Advance one step to solve Hanoi
	void SolveNextStep();

	void DrawStands();
	void DrawPlates();
	// Draws stands and plates
	// then do Invalidate
	void ReDraw();

	/*	Start of Setters and getters*/
	int GetMovesCount();
	int GetTotalMovesCount();
	bool GetAutoSolve();
	int GetPlatesCount();
	void SetAutoSolve(bool);
	void SetOwnerInstance(HINSTANCE);
	void SetOwner(HWND);
	void SetHDC(HDC);
	void SetCountContainer(int);
	void SetFromTextContainer(int);
	void SetToTextContainer(int);
	void SetThroughTextContainer(int);
	void SetPlatesCount(int);
	void SetStepTime(int);
	bool autoSolve;
	int GetStepTime();
	/*	End of Setters and getters*/

	// Display information about the current step in the main window
	void ShowCurrentStepInfo();
	// Hide information about the current step from the main window
	void HideCurrentStepInfo();

	// Draws a given plate in the main window
	void DrawGUIPlate(string, POINT, RECT);

	// Invalidate the area of drawing
	void Invalidate();
	// did we finish solving the problem
	bool IsSolved();

	~HanoiDrawer();
private:

	// lists save the status
	// of each stand
	list<int> stand1
		, stand2
		, stand3
		// list of integers each 4 integers represent a step
		// each step consist of :
		//				- number of plates
		//				- index of the current source
		//				- index of the current destination
		//				- index of the current intermediate
		, listSavedState;

	// lists save the visual appearance
	// of each plate in its corresponding
	// stand
	list<PlateGUIInfo*> listStand1GUI, listStand2GUI, listStand3GUI;


	bool proceedNextStep
		, solved;
	// Coordinates of the 3 stands
	PointF arrStandsCoor[3];

	int iPlatesCount, iMovesCount, iStepTime
		, countContainerResourceId
		, fromContainerResourceId
		, toContainerResourceId
		, throughContainerResourceId ;
	

	HINSTANCE hInstance;
	HWND hWnd;
	HDC hdc;

	// Draws the initial state
	void PopulatePlatesList();

	// Draws a stand
	void DrawOneStand(Stand);

	// Draws plates in a given stand
	void DrawPlates(Stand, list<int>);

	// Related to DrawPlates by doing
	// the low level tasks
	void DrawPlatesInList(Stand, list<int>);

	// The internal function that is responsible
	// about solve the problem.
	// platesCount : how many plates
	// source : the index of the source
	// destination : the index of the destination
	// intermediate : the index of the intermediate
	void Hanoi(int platesCount, int source, int destination, int intermediate);

	// As its name implies
	void MovePlateFromTo(int source, int destination);

	// Returns element in a given
	// list at a specified index
	int GetListElement(list<int>, int);

	// Convert plate place index
	// to its corresponding string
	string PlaceIntToString(int);
};