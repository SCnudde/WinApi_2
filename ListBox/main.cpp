#include<Windows.h>
#include "resource.h"


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{


	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_ADD:
			{

			}
			break;
			case IDC_BUTTON_DELETE:
			{

			}
			break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);

	}
	return 
}