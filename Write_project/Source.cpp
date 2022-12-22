#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <fstream>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hButton, hText;
TCHAR str[100];

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG: {
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hText = GetDlgItem(hWnd, IDC_EDIT1);
	}
					  break;

	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_BUTTON1) {
			int count = GetWindowTextLength(hText);
			GetWindowText(hText, str, count + 1);

			std::ofstream file;
			file.open(TEXT("C:\\TestFile.txt"));
			file << str;
			if (!file) {
				MessageBox(hWnd, TEXT("Ошибка открытия файла!"), TEXT("TestFile"), MB_OK | MB_ICONINFORMATION);
				return 1;
			}
			HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{58DD501A-EFE8-4A5C-B637-54B72F512CCB}"));

			DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
			if (dwAnswer == WAIT_OBJECT_0) {
				ReleaseMutex(hMutex);
				MessageBox(hWnd, TEXT("Запись данных в файл coding.txt завершена!"), TEXT("TestFile"), MB_OK | MB_ICONINFORMATION);
			}
		}
	}
				   break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}