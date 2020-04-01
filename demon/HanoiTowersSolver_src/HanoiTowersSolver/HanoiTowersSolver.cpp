// HanoiTowersSolver.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HanoiTowersSolver.h"
#include "Classes/HanoiDrawer.h"
#include "commctrl.h"


#define MAX_LOADSTRING 100
#define IDT_TIMER1 1234567

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HanoiDrawer* hanoiDrawer;
void DrawNextStep(HWND);
bool disposeed = false;
bool plateFounded = false;
BOOL bTermenateApp = FALSE;
POINTS plateCoor;

// Forward declarations of functions included in this code module:
HRESULT				OnInitDialog(HWND hDlg);
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SettingsMsgHndl(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SolveMsgHndl(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	InitCommonControls();
	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HANOITOWERSSOLVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HANOITOWERSSOLVER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


//
//  FUNCTION: OnInitDialog(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Setting the App icons.
//
HRESULT OnInitDialog( HWND hDlg )
{
    // Load the icon
#ifdef _WIN64
    HINSTANCE hInst = (HINSTANCE) GetWindowLongPtr( hDlg, GWLP_HINSTANCE );
#else
    HINSTANCE hInst = (HINSTANCE) GetWindowLong( hDlg, GWL_HINSTANCE );
#endif
    HICON hIcon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_HANOITOWERSSOLVER ) );

    // Set the icon for this dialog.
    PostMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
    PostMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

	return S_OK;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HANOITOWERSSOLVER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}			
	
	DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, (DLGPROC)SettingsMsgHndl);


	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_SETFONT:
		return (INT_PTR)TRUE;

	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Message handler for Settings dialog.
INT_PTR CALLBACK SettingsMsgHndl(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	HWND hwndSolve = NULL;
	UINT userPlatesCount = 0;
	switch (message)
	{
	case WM_SETFONT:
		return (INT_PTR)TRUE;
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg, IDC_EDIT1, (UINT)hanoiDrawer->DEFAULT_PALTES_COUNT, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_STEP_TIME, (UINT)hanoiDrawer->DEFAULT_STEP_TIME/1000, FALSE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			userPlatesCount = GetDlgItemInt(hDlg, IDC_EDIT1 , NULL, FALSE);

			hanoiDrawer = new HanoiDrawer();
			disposeed = false;
			hanoiDrawer->SetPlatesCount(userPlatesCount);
			hanoiDrawer->SetAutoSolve(IsDlgButtonChecked(hDlg, IDC_CHECK1));
			if(hanoiDrawer->GetAutoSolve()==true){
				hanoiDrawer->SetStepTime(GetDlgItemInt(hDlg, IDC_EDIT_STEP_TIME, NULL, FALSE));
			}
			EndDialog(hDlg, LOWORD(wParam));
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SOLVE), hDlg, SolveMsgHndl);

			break;
		case IDC_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, About);
			break;
		case IDCANCEL:
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
			break;
		}
	case BN_CLICKED:
		if (LOWORD(wParam) == IDC_CHECK1)
		{
			SendDlgItemMessage(hDlg, IDC_EDIT_STEP_TIME, EM_SETREADONLY, !IsDlgButtonChecked(hDlg, IDC_CHECK1), NULL);
		}
		break;
	case WM_DESTROY:
		try
		{
			if(disposeed == false)
			{
				disposeed = true;
				delete hanoiDrawer;
			}
		}
		catch(...){}
		break;
	}
	return (INT_PTR)FALSE;
}

// Message handler for Solve dialog.
INT_PTR CALLBACK SolveMsgHndl(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	PAINTSTRUCT ps;
	HDC hdc(NULL);
	POINTS ptsBegin;
	POINT ptCursor;

	switch (message)
	{
	case WM_INITDIALOG:
		OnInitDialog( hDlg );

		hanoiDrawer->SetOwnerInstance(hInst);
		hanoiDrawer->SetOwner(hDlg);
		hanoiDrawer->SetCountContainer(IDC_STATIC_MOVES_COUNT);
		hanoiDrawer->SetFromTextContainer(IDC_STATIC_FROM);
		hanoiDrawer->SetToTextContainer(IDC_STATIC_TO);
		hanoiDrawer->SetThroughTextContainer(IDC_STATIC_THROUGH);

		SetDlgItemInt(hDlg, IDC_STATIC_PLATES_COUNT, (UINT)hanoiDrawer->GetPlatesCount(), FALSE);
		SetDlgItemInt(hDlg, IDC_STATIC_MOVES_COUNT, (UINT)hanoiDrawer->GetMovesCount(), FALSE);
		SetDlgItemInt(hDlg, IDC_STATIC_TOTAL_MOVES_COUNT, (UINT)hanoiDrawer->GetTotalMovesCount(), FALSE);

		if(hanoiDrawer->GetAutoSolve() == true){
			SetDlgItemText(hDlg, IDC_SOLVE, _T("&Start"));
			SetDlgItemText(hDlg, IDC_STATIC_AUTO_MODE_ENABLED, _T("Yes"));
		}
		break;

	case WM_TIMER:
		switch(wParam)
		{
		case IDT_TIMER1:
			if(hanoiDrawer->IsSolved() == true)
			{
				KillTimer(hDlg, IDT_TIMER1);
				return 0;
			}
			DrawNextStep(hDlg);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_ABOUT:
			break;
		case IDC_SOLVE:
			if(hanoiDrawer->GetAutoSolve() == true)
			{
				SetTimer(hDlg, IDT_TIMER1, hanoiDrawer->GetStepTime(), (TIMERPROC) NULL);     
				EnableWindow(GetDlgItem(hDlg, IDC_SOLVE), FALSE);
			}

			DrawNextStep(hDlg);

			if(hanoiDrawer->IsSolved() == true)
			{
				EnableWindow(GetDlgItem(hDlg, IDC_SOLVE), FALSE);
			}
			break;
		case IDC_BTN_NEW_SESSION:
			try
			{
				if(disposeed == false)
				{
					disposeed=true;
					delete hanoiDrawer;
				}
			}
			catch(...){}
			KillTimer(hDlg, IDT_TIMER1);
			EndDialog(hDlg, LOWORD(wParam));
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hDlg, SettingsMsgHndl);
			break;
		case IDC_BTN_EXIT:
		case IDCANCEL:
			if ( MessageBox(hDlg, _T("Are you sure you want exit ?"), szTitle, MB_OKCANCEL | MB_ICONQUESTION)==IDOK )
			{
				bTermenateApp = TRUE;
				EndDialog(hDlg, LOWORD(wParam));
			}
		}

		break;
	case WM_DESTROY:
		KillTimer(hDlg, IDT_TIMER1);
		if(bTermenateApp){
			try
			{
				if(disposeed == false)
				{
					disposeed=true;
					delete hanoiDrawer;
				}
			}
			catch(...){}
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		{
			hanoiDrawer->SetHDC(hdc);

			hanoiDrawer->SetStandCoordinates(HanoiDrawer::No1, 120, 62);
			hanoiDrawer->SetStandCoordinates(HanoiDrawer::No2, 400, 62);
			hanoiDrawer->SetStandCoordinates(HanoiDrawer::No3, 670, 62);

			hanoiDrawer->DrawStands();
			hanoiDrawer->DrawPlates();
		}
		EndPaint(hDlg, &ps);
		break;
	}

	return (INT_PTR)FALSE;
}

void DrawNextStep(HWND hWnd)
{
	hanoiDrawer->ShowCurrentStepInfo();
	hanoiDrawer->SolveNextStep();
}