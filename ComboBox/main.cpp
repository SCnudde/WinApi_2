#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include <cstdio>


CONST CHAR* g_SZ_VALUES[] = { "This", "is", "my", "first", "ComboBox" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, 0);


	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_SZ_VALUES)/ sizeof(g_SZ_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_SZ_VALUES[i]);

		}
	}
		break;
	case WM_COMMAND:
	{


		switch (LOWORD(wParam))
		{
		case IDOK:	
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};// sz_ - string Zero
			CHAR sz_message[SIZE] = {};// sz_ - string Zero
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);//GETCURSEL - GET CURRENT SELECTION Получить текущий выбранный элемент
			if (i!= CB_ERR)
			{
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
				sprintf(sz_message, "Вы выбрали элемент %i со значением \"%s\"", i, sz_buffer);
				MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Вы ничего не выбрали", "Info", MB_OK | MB_ICONINFORMATION);
			}
			
		}
			break;
			
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);		
	}
	return FALSE;
}