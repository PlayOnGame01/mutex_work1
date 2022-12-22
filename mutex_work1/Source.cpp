#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <fstream>
#include "resource.h"
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hButton;
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	if (IDC_BUTTON1 == id) {
		CreateMutex(0, FALSE, TEXT("{58DD501A-EFE8-4A5C-B637-54B72F512CCB}"));

		STARTUPINFO st = { sizeof(st) };
		PROCESS_INFORMATION pr;

		TCHAR filename[20];
		wsprintf(filename, TEXT("%s"), TEXT("WriteFile.exe"));

		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr)) {
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);

		ZeroMemory(&st, sizeof(st));
		st.cb = sizeof(st);

		std::ofstream file(TEXT("TestFile.txt"));

		wsprintf(filename, TEXT("%s"), TEXT("ReadFile.exe"));

		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr)) {
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);
	}
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG: {
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
	}
					  break;

					  HANDLE_MSG(hWnd, WM_COMMAND, Cls_OnCommand);

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}