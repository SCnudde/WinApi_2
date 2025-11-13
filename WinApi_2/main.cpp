#include <Windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL,
	//	"Hello WinAPI", 
	//	"MessageBox",MB_ICONERROR| MB_HELP| MB_DEFBUTTON3); //MB MessageBox
	//	return 0;

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL,(DLGPROC)DlgProc, 0);
		return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://Выполняется 1 раз, при запуске окна
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(NULL, "была нажате кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION);
			break;
			//Обрабатывает комманды с клавиатуры и мыши
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE://Выполняется при нажатии кнопки "Х"
		EndDialog(hwnd,0);
	}
	return FALSE;
}