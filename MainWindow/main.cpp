#include <Windows.h>
#include "resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Mijn eerste venster";
CONST CHAR mainMessage[] = "Mijn eerste tekst";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;//создаём экземпляр класса окна,для обращения к членам класса WNDCLASSEX
	
	ZeroMemory(&wClass, sizeof(wClass));
	
	//Инициализируем поля класса окна размерами и стилями:
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);//cb_ - Count Bytes. Размер структуры в байтах.
	wClass.cbClsExtra = 0;// число освобождаемых байтов при создании экземпляра приложения
	wClass.cbWndExtra = 0;// число освобождаемых байтов в конце структуры

	//Инициализируем внешний вид окон
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE (IDI_ICON_RUBLE)); // дескриптор значка
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE (IDI_ICON_PALM)); // дескриптор цвета фона окошка
	//wClass.hIcon = (HICON) LoadImage(NULL, "ruble.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(NULL, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	
	wClass.hCursor = (HICON) LoadImage(hInstance, "starcraft-original\\Busy.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE (IDC_CURSOR1)); // дескриптор курсора мыши
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	//Инициализация системных переменных:
	wClass.hInstance = hInstance;//дескриптор экземпляра приложения
	wClass.lpszClassName = g_sz_WINDOW_CLASS;// указатель на const-строку, содержащюю имя класса
	wClass.lpszMenuName = NULL; // указатель на const-строку, содержащюю имя меню, применяемого для класса
	wClass.lpfnWndProc = WndProc; // указатель на имя пользовательской функции

	if (RegisterClassEx(&wClass) == NULL)// проверяtv, зарегистрирован ли класс
	{
		MessageBox(NULL, "Het registratie het Class is mislukt", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}	
	//2) Создание окна:

	int width = 640; 
	int height = 480; 

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	int center_screen_X = (screenX - width) / 2;
	int center_screen_Y = (screenY - height) / 2;


	HWND hwnd = CreateWindowEx
	(
		NULL, //exStyle
		g_sz_WINDOW_CLASS,//Имя класса окна
		g_sz_WINDOW_CLASS,//Заголок окна
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,//Стиль окна, Стили всегда зависят от класса окна
		//CW_USEDEFAULT,CW_USEDEFAULT, //Позиция
		center_screen_X, center_screen_Y,
		width, height, //Размер окна
		NULL,
		NULL, //Для главного окна это ResourceID главного меню,
				//для дочернего окна (Control) -ResourceID дочернего окна (IDC_BUTTON_COPY)
		hInstance,
		NULL
	);

	if (!hwnd) 
	{	
		MessageBox(NULL, "Ontwerp van het venster is mislukt!","FOUT",MB_OK);
		return 0;
	}

	//3) Запуск цикла сообщений

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Het venster is niet geslagd", NULL, MB_OK | MB_ICONERROR);
	}

	ShowWindow(hwnd, nCmdShow);//вызывает дескриптор окна и CreateWindow(), 2 параметр вызывает стиль отображения
						//Задаетрежим отображения окна - Развернуто на весь экран
	UpdateWindow(hwnd);//обновляет рабочую область окна, отправляя сообщение в WM_PAINT,
						//если клиентская область окна не пустая
	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL) > NULL) 
	{
		TranslateMessage(&msg);//преобразует сообщения виртуальных клавиш в символьные
		DispatchMessage(&msg);//Отправляет сообщения в процедуру окна
	}
	return msg.wParam;	

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect; // стр-ра, определяющая размер клиентской области
	COLORREF colorText = 0x00FF0000;

	switch (uMsg)
	{		
	case WM_PAINT: // если нужно нарисовать, то:
		hDC = BeginPaint(hwnd, &ps); // инициализируем контекст устройства
		GetClientRect(hwnd, &rect); // получаем ширину и высоту области для рисования
		SetTextColor(hDC, colorText); // устанавливаем цвет контекстного устройства
		DrawText(hDC, mainMessage, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // рисуем текст
		EndPaint(hwnd, &ps); // заканчиваем рисовать
		break;
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}