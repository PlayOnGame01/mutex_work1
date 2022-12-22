#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <fstream>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hButton;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));
	switch (message)
	{
	case WM_INITDIALOG: {
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
	}
					  break;

	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_BUTTON1) {
			std::fstream file(TEXT("CopyFile.txt"));
		}
	}
				   break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}