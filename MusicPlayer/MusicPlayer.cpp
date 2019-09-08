﻿// MusicPlayer.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MusicPlayer.h"
#include "MusicPlayer.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
	

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MUSICPLAYER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MUSICPLAYER));

    MSG msg;

    // 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDI_ICON2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, L"千千动听", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		
	case WM_CREATE:
		{
			// 窗口控件
			// 歌曲列表
			hListBox = CreateWindow(L"LISTBOX", L"", 
				WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
				0, 0, 625, 400, hWnd, (HMENU)LISTBOX, hInst, nullptr);
			// 播放按钮
			hMusicPlay = CreateWindow(L"BUTTON", L"播放", 
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				0, 410, 60, 30, hWnd, (HMENU)BUTTON_PLAY, hInst, nullptr);
			// 暂停按钮
			hMusicPause = CreateWindow(L"BUTTON", L"暂停", 
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				80, 410, 60, 30, hWnd, (HMENU)BUTTON_PAUSE, hInst, nullptr);
			// 歌曲当前时间文本框
			hSongCurrentTime = CreateWindow(L"STATIC", L"00:00",
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
				200, 410, 60, 30, hWnd, (HMENU)TIMELINE, hInst, nullptr);
			// 歌曲时长文本框
			hSongLength = CreateWindow(L"STATIC", L"4:00",
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
				563, 410, 60, 30, hWnd, (HMENU)TIMETEXT, hInst, nullptr);

			// 歌曲进度滑块
			InitCommonControls(); // loads common control's DLL
			hwndTrack = CreateWindow(TRACKBAR_CLASS, L"", 
				WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_FIXEDLENGTH | TBS_HORZ,
				280, 410, 260, 30, hWnd, (HMENU)ID_TRACKBAR, hInst, NULL);
			SendMessage(hwndTrack, TBM_SETRANGE,
				(WPARAM)TRUE,                   // redraw flag 
				(LPARAM)MAKELONG(0, 100));  // min. & max. positions

			SendMessage(hwndTrack, TBM_SETPAGESIZE,
				0, (LPARAM)4);                  // new page size 

			SendMessage(hwndTrack, TBM_SETSEL,
				(WPARAM)FALSE,                  // redraw flag 
				(LPARAM)MAKELONG(0, 100));

			SendMessage(hwndTrack, TBM_SETPOS,
				(WPARAM)TRUE,                   // redraw flag 
				(LPARAM)0);


			
			// 给列表框添加文件
			//DlgDirListA(hListBox, (LPSTR)FileRoot, LISTBOX, 0, 0);
			SendMessage(hListBox, LB_INSERTSTRING, -1, 
				(LPARAM)L"C:\\Users\\卡里\\Music\\出山.mp3");
			SendMessage(hListBox, LB_INSERTSTRING, -1,
				(LPARAM)L"C:\\Users\\卡里\\Music\\水星记.mp3");
			SendMessage(hListBox, LB_INSERTSTRING, -1,
				(LPARAM)L"C:\\Users\\卡里\\Music\\芒种.mp3");

			// 默认选中列表框第一个列表
			SendMessage(hListBox, LB_SETCURSEL, 0, 0);

			// 将键盘焦点设置为列表框
			SetFocus(hListBox);
		}
		break;
	case WM_TIMER:
		{
			if (wParam == TimerID)
			{
				// 当歌曲没有暂停时才同步
				Button_GetText(hMusicPause, ButtonText, 10);
				if (lstrcmp(ButtonText, PAUSESTRING) == 0)
				{
					GetCurrentPosition(MusicFileShortPath);
					position = _wtol(SongTime);

					if (position < length)
					{
						// 更新时间
						m_pos = position / 1000 / 60;
						s_pos = position / 1000 % 60;
						wsprintf(SongTime, L"%02d:%02d", m_pos, s_pos);
						Button_SetText(hSongCurrentTime, SongTime);
						
						// 更新进度条
						UINT now_barpos = position * 100 / length + 1;
						if (barPos < now_barpos)
							barPos = now_barpos;

						SendMessage(hwndTrack, TBM_SETPOS,
							(WPARAM)TRUE,                   // redraw flag 
							(LPARAM)barPos);
					}
					else if (position == length)
					{
						// 换播放列表的下一首歌
						PlayListIndex++;
						if (SendMessage(hListBox, LB_GETITEMDATA, PlayListIndex, 0) == LB_ERR)
							PlayListIndex = 0;
						SendMessage(hListBox, LB_SETCURSEL, PlayListIndex, 0);
						SendMessage(hMusicPlay, BM_CLICK, 0, 0);

					}
				}
			}
		}
		break;
	case WM_HSCROLL:
		{
			switch (LOWORD(wParam))
			{
			case TB_THUMBTRACK:
				{
					barPos = SendMessage(hwndTrack, TBM_GETPOS, 0, 0);
					PlayFrom(MusicFileShortPath, barPos);
				}
				break;
			}
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case BUTTON_PLAY:
				{
					// 单击播放选中歌曲
					index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
					if (LB_ERR != index)
					{
						// 解决要播放第二首歌曲时，第一首歌曲未停
						if (lstrlen(currentMusic) != 0)
						{
							MUSICSTOP(currentMusic);
							KillTimer(hWnd, TimerID);
						}

						// 当前歌曲暂停并更换另一首歌曲时，暂停按钮显示继续
						Button_GetText(hMusicPause, ButtonText, 10);
						if (lstrcmp(ButtonText, RESUMESTRING) == 0)
						{
							Button_SetText(hMusicPause, PAUSESTRING);
						}
						// 获取选中列表的音乐路径
						SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)MusicFileName);
						GetShortPathName(MusicFileName, MusicFileShortPath, MAX_PATH);

						// 播放歌曲时初始化时间、长度和进度条
						GetMusicLength(MusicFileShortPath);
						length = _wtol(SongLength);
						minute = length / 1000 / 60;
						second = length / 1000 % 60;
						wsprintf(ButtonLengthText, L"%02d:%02d", minute, second);
						Button_SetText(hSongLength, ButtonLengthText);
						wsprintf(ButtonTimeText, L"00:00");
						Button_SetText(hSongCurrentTime, ButtonTimeText);
						barPos = 0;
						SendMessage(hwndTrack, TBM_SETPOS,
							(WPARAM)TRUE,                   // redraw flag 
							(LPARAM)barPos);

						// 打开音乐文件
						lstrcpy(currentMusic, MusicFileShortPath);
						MusicPlay(MusicFileShortPath);

						// 创建定时器用于同步
						TimerID = SetTimer(hWnd, 1, 1000, nullptr);

					}
					else
					{
						MessageBox(hWnd, L"请选择歌曲", L"", 0);
					}
				}
				break;
			case BUTTON_PAUSE:
				{
					// 获取按钮文本
					Button_GetText(hMusicPause, ButtonText, 10);

					if (lstrcmp(ButtonText, PAUSESTRING) == 0)
					{
						MUSICPAUSE(currentMusic);
						Button_SetText(hMusicPause, RESUMESTRING);
					}
					else if (lstrcmp(ButtonText, RESUMESTRING) == 0)
					{
						MUSICRESUME(currentMusic);
						Button_SetText(hMusicPause, PAUSESTRING);
					}
				}
				break;
			case LISTBOX:
				{
					switch (HIWORD(wParam))
					{
					// 列表框的项目被双击时会发送通知码
					case LBN_DBLCLK:
						{
							SendMessage(hMusicPlay, BM_CLICK, 0, 0);
						}
						break;
					}
				}
				break;
			}
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void MusicOpen(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	// 打开文件
	wsprintf(command, L"open %s", musicpath);
	mciSendString(command, nullptr, 0, nullptr);
}

void MusicPlay(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	// 打开文件
	MusicOpen(musicpath);

	// 播放歌曲
	wsprintf(command, L"play %s", musicpath);
	mciSendString(command, nullptr, 0, nullptr);
}

void MUSICPAUSE(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	// 暂停歌曲
	wsprintf(command, L"pause %s", musicpath);
	mciSendString(command, nullptr, 0, nullptr);
}

void MUSICRESUME(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	// 继续播放歌曲
	wsprintf(command, L"resume %s", musicpath);
	mciSendString(command, nullptr, 0, nullptr);
}

void MUSICSTOP(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	// 停止歌曲
	wsprintf(command, L"stop %s", musicpath);
	mciSendString(command, nullptr, 0, nullptr);
	// 关闭文件
	wsprintf(command, L"close %s", musicpath);
	mciSendString(command, nullptr, 0, nullptr);
}

void GetMusicLength(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	wsprintf(command, L"status %s length", musicpath);
	mciSendString(command, SongLength, sizeof(SongLength), nullptr);
}

void GetCurrentPosition(LPCWSTR musicpath)
{
	WCHAR command[MAX_PATH];

	wsprintf(command, L"status %s position", musicpath);
	mciSendString(command, SongTime, sizeof(SongTime), nullptr);
}

void PlayFrom(LPCWSTR musicpath, UINT barpos)
{
	WCHAR command[MAX_PATH];
	MUSICSTOP(musicpath);
	MusicOpen(musicpath);

	// 获取滑块的等比例长度
	long pos;
	pos = (length / 100) * barpos;

	wsprintf(command, L"play %s from %ld", musicpath, pos);
	mciSendString(command, nullptr, 0, nullptr);
}


// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
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