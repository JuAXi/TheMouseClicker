#include <Windows.h>
#include "resource.h"
#include <atlstr.h>
#include <thread>
#include <fstream>
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")	//更改UI		//Change UI

CString version = L"鼠标点击7.0.0";
CString add = L"https://github.com/JuAXi/TheMouseClicker";

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define KEY_UP(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 0:1)

#define BUTTON1 5336
#define BUTTON2 5337
#define BUTTON3 5338
#define BUTTON4 5339
#define BUTTON_SUREL 5340
#define BUTTON_SURER 5341
#define BUTTON_CANCEL 5342
#define Input_Time 5343
#define Output_Name 5344
#define Input_Name 5345
#define BUTTON_OUTPUT 5346
#define BUTTON_INPUT 5347

const int minutes = 60;
const int time_interval = 10;
const int total_times = minutes * 60 * (1000 / time_interval);

bool input_success = false;

int key_press[total_times][255] = { 0 }, count = 0;
bool i_down[255] = { false };
POINT point[total_times];

HFONT font = CreateFont(18, 9, 0, 0, 600, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"宋体");

void CreateData()
{
	CString str = L"./data";
	if (!PathIsDirectory(str))
	{
		CreateDirectory(str, NULL);
	}
}

bool IsSameName(CString output_txt)
{
	std::ifstream input(output_txt);
	if (input.is_open())
		return true;
	else
		return false;
}

void ClickR(double count_time)
{
	bool Continue = true;
	double time0 = GetTickCount(), time1 = 0;
	while (true)
	{
		if (Continue == true)
		{
			time1 = GetTickCount();
			if (KEY_DOWN(4))
			{
				Continue = false;
				Sleep(500);
			}
			if (KEY_DOWN(27))
			{
				break;
			}
			if ((time1 - time0) > count_time)
			{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				Sleep(10);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				time0 = GetTickCount();
			}
		}
		if (Continue == false)
		{
			if (KEY_DOWN(4))
			{
				Continue = true;
				Sleep(500);
			}
			if (KEY_DOWN(27))
			{
				break;
			}
		}
		Sleep(1);
	}
}

void ClickL(double count_time)
{
	bool Continue = true;
	double time0 = GetTickCount(), time1 = 0;
	while (true)
	{
		if (Continue == true)
		{
			time1 = GetTickCount();
			if (KEY_DOWN(4))
			{
				Continue = false;
				Sleep(500);
			}
			if (KEY_DOWN(27))
			{
				break;
			}
			if ((time1 - time0) > count_time)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(10);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				time0 = GetTickCount();
			}
		}
		if (Continue == false)
		{
			if (KEY_DOWN(4))
			{
				Continue = true;
				Sleep(500);
			}
			if (KEY_DOWN(27))
			{
				break;
			}
		}
		Sleep(1);
	}
}

void Record()
{
	int i = 0;
	bool left_down = false, right_down = false;
	HWND hwnd = FindWindow(NULL, version);
	POINT p;
	while (true)
	{
		GetCursorPos(&p);
		point[count] = p;
		for (i = 0; i < 255; i++)
		{
			if (i != 27)
			{
				if (KEY_DOWN(i) == true && i_down[i] == false)
				{
					key_press[count][i] = 1;
					i_down[i] = true;
				}
				if (KEY_UP(i) == true && i_down[i] == true)
				{
					key_press[count][i] = -1;
					i_down[i] = false;
				}
			}
		}
		if (KEY_DOWN(27))
		{
			break;
		}
		count++;
		Sleep(time_interval);
	}
	CreateWindowEx(NULL, L"Record_Output", L"输入保存的文件名（不带后缀）", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 150, 150, 400, 200, hwnd, NULL, NULL, NULL);
	MSG msg_newpage;
	while (GetMessageW(&msg_newpage, NULL, 0, 0))
	{
		TranslateMessage(&msg_newpage);
		DispatchMessageW(&msg_newpage);
	}
}

void Display()
{
	HWND hwnd = FindWindow(NULL, version);
	CreateWindowEx(NULL, L"Record_Input", L"输入保存的文件名（不带后缀）", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 150, 150, 400, 200, hwnd, NULL, NULL, NULL);
	MSG msg_newpage;
	while (GetMessageW(&msg_newpage, NULL, 0, 0))
	{
		TranslateMessage(&msg_newpage);
		DispatchMessageW(&msg_newpage);
	}
	Sleep(10);
	if (input_success == true)
	{
		bool display_continue = true;
		int i = 0;
		double time0 = 0, time1 = 0;
		while (display_continue == true)
		{
			i = 0;
			while (i <= count)
			{
				SetCursorPos(point[i].x, point[i].y);
				for (int j = 0; j < 255; j++)
				{
					if (j < 6)
					{
						switch (j)
						{
						case 1:
							if (key_press[i][j] == 1)
								mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
							if (key_press[i][j] == -1)
								mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							break;
						case 2:
							if (key_press[i][j] == 1)
								mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
							if (key_press[i][j] == -1)
								mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							break;
						case 4:
							if (key_press[i][j] == 1)
								mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
							if (key_press[i][j] == -1)
								mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
							break;
						default:
							break;
						}
					}
					else
					{
						if (key_press[i][j] > 0)
						{
							keybd_event(j, 0, 0, 0);
						}
						if (key_press[i][j] < 0)
						{
							keybd_event(j, 0, KEYEVENTF_KEYUP, 0);
						}
					}

				}
				if (KEY_DOWN(27))
				{
					display_continue = false;
					break;
				}
				i++;
				Sleep(time_interval);
			}
			time0 = GetTickCount();
			time1 = GetTickCount();
			while (time1 - time0 < 3000)
			{
				time1 = GetTickCount();
				if (KEY_DOWN(27))
				{
					display_continue = false;
					break;
				}
				Sleep(time_interval);
			}
		}
	}
	input_success = false;
}

LRESULT WINAPI RecordInputReact(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND name_get = NULL, button_ok;
	switch (msg)
	{
		case WM_CREATE:
		{
			name_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 35, 360, 30, hwnd, (HMENU)Input_Name, NULL, NULL);
			button_ok = CreateWindow(L"button", L"确定", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 165, 100, 70, 50, hwnd, (HMENU)BUTTON_INPUT, NULL, NULL);
			SendMessage(name_get, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(button_ok, WM_SETFONT, (WPARAM)font, TRUE);
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case BUTTON_INPUT:
				{
					CString temp;
					CString storage_address = L"./data/";
					GetDlgItemText(hwnd, Input_Name, temp.GetBuffer(100), 100);
					temp.ReleaseBuffer();
					temp += ".txt";
					storage_address += temp;
					int a = 0, b = 0;
					std::ifstream input(storage_address);
					if (input.is_open())
					{
						input >> count;
						for (int i = 0; i <= count; i++)
						{
							input >> point[i].x;
						}
						for (int i = 0; i <= count; i++)
						{
							input >> point[i].y;
						}
						while (!input.eof())
						{
							input >> a >> b >> key_press[a][b];
						}
						input_success = true;
						input.close();
						SendMessage(hwnd, WM_CLOSE, NULL, NULL);
					}
					else
					{
						MessageBox(NULL, L"找不到文件", L"Warning", MB_OK);
					}
				}
			}
		}
		case WM_CLOSE:
		{
			DeleteObject(font);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI RecordOutputReact(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND name_get = NULL, button_ok;
	switch (msg)
	{
	case WM_CREATE:
	{
		name_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 35, 360, 30, hwnd, (HMENU)Output_Name, NULL, NULL);
		button_ok = CreateWindow(L"button", L"确定", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 165, 100, 70, 50, hwnd, (HMENU)BUTTON_OUTPUT, NULL, NULL);
		SendMessage(name_get, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(button_ok, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BUTTON_OUTPUT:
		{
			CString temp;
			CString storage_address = L"./data/";
			GetDlgItemText(hwnd, Output_Name, temp.GetBuffer(100), 100);
			temp.ReleaseBuffer();
			temp += ".txt";
			storage_address += temp;
			if (IsSameName(storage_address))
			{
				MessageBox(NULL, L"已存在同名文件", L"Warning", MB_OK);
			}
			else
			{
				std::ofstream output;
				CreateData();
				output.open(storage_address);
				output << count << std::endl;
				for (int i = 0; i <= count; i++)
				{
					output << point[i].x << " ";
				}
				output << std::endl;
				for (int i = 0; i <= count; i++)
				{
					output << point[i].y << " ";
				}
				output << std::endl;
				for (int i = 0; i <= count; i++)
				{
					for (int j = 0; j < 255; j++)
					{
						if (key_press[i][j] != 0)
						{
							output << i << ' ' << j << ' ' << key_press[i][j] << std::endl;
						}
					}
				}
				output.close();
				SendMessage(hwnd, WM_CLOSE, NULL, NULL);
				MessageBox(NULL, storage_address, storage_address, MB_OK);
				break;
			}
		}
		}
	case WM_CLOSE:
	{
		DeleteObject(font);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI TimeReact(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND text1, time_get = NULL, button_okl, button_cancel, button_okr, text2, main_win;
	main_win = FindWindow(NULL, version);
	double count_time = 0;
	switch (msg)
	{
		case WM_CREATE:
		{
			text1 = CreateWindow(L"static", L"请输入时间（单位:秒）", WS_CHILD | WS_VISIBLE, 10, 10, 200, 30, hwnd, (HMENU)1, NULL, 0);
			text2 = CreateWindow(L"static", L"开始后，按鼠标滚轮停止，按‘ESC’结束", WS_CHILD | WS_VISIBLE, 5, 70, 400, 30, hwnd, (HMENU)1, NULL, 0);
			time_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 35, 250, 30, hwnd, (HMENU)Input_Time, NULL, NULL);
			button_okl = CreateWindow(L"button", L"左键", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 100, 70, 50, hwnd, (HMENU)BUTTON_SUREL, NULL, NULL);
			button_okr = CreateWindow(L"button", L"右键", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 100, 70, 50, hwnd, (HMENU)BUTTON_SURER, NULL, NULL);
			button_cancel = CreateWindow(L"button", L"取消", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 180, 100, 70, 50, hwnd, (HMENU)BUTTON_CANCEL, NULL, NULL);
			SendMessage(text1, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(button_okl, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(button_okr, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(button_cancel, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(time_get, WM_SETFONT, (WPARAM)font, TRUE);
			break;
		}
		case WM_CTLCOLORSTATIC:
		{
			if ((HWND)lParam == GetDlgItem(hwnd, 1))//获得指定标签句柄用来对比
			{
				SetTextColor((HDC)wParam, RGB(0, 0, 0));//设置文本颜色
				SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
			}
			return (INT_PTR)GetStockObject((NULL_BRUSH));
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case BUTTON_SUREL:
				{
					CString temp;
					GetDlgItemText(hwnd, Input_Time, temp.GetBuffer(11), 11);
					temp.ReleaseBuffer();
					double count_time = _wtof(temp);
					if (count_time < 0 || count_time >= 10000000000)
						MessageBox(NULL, L"输入范围在0~9999999999之间", L"FBI Warning!", MB_OK);
					else if (count_time == 9999999999)
						MessageBox(NULL, L"经计算，您可能至少需要等10代人的时间才能实现一次单击", L"FBI Warning!", MB_OK);
					else if (count_time >= 2491344000)
						MessageBox(NULL, L"您知道人类平均寿命在79年吗？", L"FBI Warning!", MB_OK);
					else
					{
						count_time *= 1000;
						SendMessage(hwnd, WM_CLOSE, NULL, NULL);
						SendMessage(main_win, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
						std::thread click(ClickL, count_time);
						Sleep(1000);
						click.detach();
						Sleep(10);
						temp.ReleaseBuffer(10);
					}
					break;
				}
				case BUTTON_SURER:
				{
					CString temp;
					GetDlgItemText(hwnd, Input_Time, temp.GetBuffer(10), 10);
					temp.ReleaseBuffer();
					double count_time = _wtof(temp);
					if (count_time < 0 || count_time >= 10000000000)
						MessageBox(NULL, L"输入范围在0~9999999999之间", L"FBI Warning!", MB_OK);
					else if (count_time == 9999999999)
						MessageBox(NULL, L"经计算，您可能至少需要等10代人的时间才能实现一次单击", L"FBI Warning!", MB_OK);
					else if (count_time >= 2491344000)
						MessageBox(NULL, L"您知道人类平均寿命在79年吗？", L"FBI Warning!", MB_OK);
					else
					{
						count_time *= 1000;
						SendMessage(hwnd, WM_CLOSE, NULL, NULL);
						SendMessage(main_win, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
						std::thread click(ClickR, count_time);
						Sleep(1000);
						click.detach();
						Sleep(10);
						temp.ReleaseBuffer(10);
					}
					break;
				}
				case BUTTON_CANCEL:
				{
					SendMessage(hwnd, WM_CLOSE, NULL, NULL);
					break;
				}
			}
		}
		case WM_CLOSE:
		{
			DeleteObject(font);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI React(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndButton1, hwndButton2, hwndButton3, hwndButton4, text;
	bool record_button = false;
	switch (msg)
	{
		case WM_CREATE:
		{
			text = CreateWindow(L"static", version, WS_CHILD | WS_VISIBLE, 90, 50, 200, 20, hwnd, (HMENU)1, NULL, 0);
			hwndButton1 = CreateWindowEx(NULL, TEXT("Button"), TEXT("1.连点器（按“ESC”退出）"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 265, 50, hwnd, (HMENU)BUTTON1, NULL, NULL);
			hwndButton2 = CreateWindowEx(NULL, TEXT("Button"), TEXT("2.录制"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 175, 265, 50, hwnd, (HMENU)BUTTON2, NULL, NULL);
			hwndButton3 = CreateWindowEx(NULL, TEXT("Button"), TEXT("3.播放"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 250, 265, 50, hwnd, (HMENU)BUTTON3, NULL, NULL);
			hwndButton4 = CreateWindowEx(NULL, TEXT("Button"), TEXT("4.项目地址"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 325, 265, 50, hwnd, (HMENU)BUTTON4, NULL, NULL);
			SendMessage(text, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(hwndButton1, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(hwndButton2, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(hwndButton3, WM_SETFONT, (WPARAM)font, TRUE);
			SendMessage(hwndButton4, WM_SETFONT, (WPARAM)font, TRUE);
			break;
		}
		case WM_CTLCOLORSTATIC:
		{
			if ((HWND)lParam == GetDlgItem(hwnd, 1))//获得指定标签句柄用来对比
			{
				SetTextColor((HDC)wParam, RGB(0, 0, 0));//设置文本颜色
				SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
			}
			return (INT_PTR)GetStockObject((NULL_BRUSH));
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case BUTTON1 :
				{
					CreateWindowEx(NULL, L"Time_Input", L"输入", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 150, 150, 410, 200, hwnd, NULL, NULL, NULL);
					MSG msg_newpage;
					while (GetMessageW(&msg_newpage, NULL, 0, 0))
					{
						TranslateMessage(&msg_newpage);
						DispatchMessageW(&msg_newpage);
					}
					break;
				}
				case BUTTON2:
				{
					memset(point, 0, sizeof(point));
					memset(key_press, 0, sizeof(key_press));
					memset(i_down, 0, sizeof(i_down));
					count = 0;
					record_button = true;
					MessageBox(hwnd, L"点击确定开始录制(按‘ESC’结束)", L"准备开始", MB_OK);
					UpdateWindow(hwnd);
					break;
				}
				case BUTTON3:
				{
					memset(point, 0, sizeof(point));
					memset(key_press, 0, sizeof(key_press));
					memset(i_down, 0, sizeof(i_down));
					count = 0;
					std::thread display(Display);
					SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
					Sleep(10);
					display.detach();
					UpdateWindow(hwnd);
					break;
				}
				case BUTTON4:
				{
					ShellExecute(NULL, L"open", L"explorer.exe", add, NULL, SW_SHOW);
					Sleep(10);
					break;
				}
			}
		}
		case IDH_OK:
		{
			if (record_button)
			{
				std::thread record(Record);
				Sleep(10);
				record.detach();
				SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
				record_button = false;
				UpdateWindow(hwnd);
				break;
			}
		}
		case WM_CLOSE:
		{
			DeleteObject(font);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CreateData();
	memset(point, 0, sizeof(point));
	memset(key_press, 0, sizeof(key_press));
	memset(i_down, 0, sizeof(i_down));

	WNDCLASSEX main_window, time_input, record_input, record_output;

	//main_window属性
	main_window.cbSize = sizeof(main_window);
	main_window.style = CS_VREDRAW | CS_HREDRAW;
	main_window.lpfnWndProc = React;
	main_window.cbClsExtra = 0;
	main_window.cbWndExtra = 0;
	main_window.hInstance = hInstance;
	main_window.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	main_window.hCursor = LoadCursorW(hInstance, IDC_ARROW);
	main_window.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	main_window.lpszMenuName = NULL;
	main_window.lpszClassName = L"Main";
	main_window.hIconSm = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));

	time_input.cbSize = sizeof(time_input);
	time_input.style = CS_VREDRAW | CS_HREDRAW;
	time_input.lpfnWndProc = TimeReact;
	time_input.cbClsExtra = 0;
	time_input.cbWndExtra = 0;
	time_input.hInstance = hInstance;
	time_input.hIcon = NULL;
	time_input.hCursor = NULL;
	time_input.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	time_input.lpszMenuName = NULL;
	time_input.lpszClassName = L"Time_Input";
	time_input.hIconSm = NULL;

	record_input.cbSize = sizeof(record_input);
	record_input.style = CS_VREDRAW | CS_HREDRAW;
	record_input.lpfnWndProc = RecordInputReact;
	record_input.cbClsExtra = 0;
	record_input.cbWndExtra = 0;
	record_input.hInstance = hInstance;
	record_input.hIcon = NULL;
	record_input.hCursor = NULL;
	record_input.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	record_input.lpszMenuName = NULL;
	record_input.lpszClassName = L"Record_Input";
	record_input.hIconSm = NULL;

	record_output.cbSize = sizeof(record_output);
	record_output.style = CS_VREDRAW | CS_HREDRAW;
	record_output.lpfnWndProc = RecordOutputReact;
	record_output.cbClsExtra = 0;
	record_output.cbWndExtra = 0;
	record_output.hInstance = hInstance;
	record_output.hIcon = NULL;
	record_output.hCursor = NULL;
	record_output.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	record_output.lpszMenuName = NULL;
	record_output.lpszClassName = L"Record_Output";
	record_output.hIconSm = NULL;


	//注册窗口
	if (0 == RegisterClassExW(&main_window))
	{
		MessageBoxW(NULL, L"main wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&time_input))
	{
		MessageBox(NULL, L"time input wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&record_input))
	{
		MessageBox(NULL, L"record input wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&record_output))
	{
		MessageBox(NULL, L"record output wrong", L"Regist", MB_OK);
		return 0;
	}

	//创建窗口
	HWND main_win = CreateWindowEx(NULL, L"Main", version, WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 100, 100, 300, 450, NULL, NULL, hInstance, NULL);

	//ShowWindow(main_win, SW_SHOW);
	UpdateWindow(main_win);
	
	//数据刷新
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		//TranslateMessage(&msg);	//仅键盘 
		DispatchMessageW(&msg);
	}

	return 0;
}