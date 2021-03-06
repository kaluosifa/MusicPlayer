﻿#pragma once

#include "resource.h"
#include "framework.h"

// 引入皮肤库头文件
#include "SkinH.h"
#pragma comment(lib, "SkinHu.lib")


// 句柄菜单
#define LISTBOX 70
#define BUTTON_PLAY 80
#define BUTTON_PAUSE 81
#define TIMELINE 90
#define TIMETEXT 91
#define ID_TRACKBAR 100
#define rMenuAdd	110
#define rMenuDelete	111
#define rMenuClear	112

// 字符串常量
#define PAUSESTRING L"暂停"
#define RESUMESTRING L"继续"

#define MUSICFILEFORMATNUMBER 2					// 文件格式数量
#define FORMATLENGTH 5							// 格式字符串长度
#define ONEFILE 0								// 状态值，一个文件
#define MULTIPLEFILE 1							// 状态值，多个文件
#define MUSICNAMELENGTH	MAX_PATH				// 歌曲名最大长度
#define MUSICSHORTNAME MAX_PATH					// 没有格式的歌曲名

// 音乐播放器的全局变量
WCHAR currentMusic[MAX_PATH];					// 当前歌曲
WCHAR SongLength[10];							// 歌曲长度
WCHAR SongTime[10];								// 歌曲当前播放位置时间
WCHAR CONFIGURATIONFILE[MAX_PATH] = L"C:\\Users\\17123\\Desktop\\Music_Player_configuration_file.ini";
WCHAR MUSICPLAYLIST[MAX_PATH] = L"MUSIC PLAY LIST";

WCHAR szFileName[MAX_PATH * 30];

HWND hListBox;						// 列表框句柄
HWND hMusicPlay;					// 播放按钮句柄
HWND hMusicPause;					// 暂停继续按钮句柄
HWND hSongCurrentTime;				// 当前歌曲时间
HWND hProgressBar;					// 时间轴，进度条
HWND hSongLength;					// 歌曲时间
HWND hwndTrack;						// 进度条滑块

// 音乐文件夹路径
unsigned int index;								// 选中的音乐文件索引
WCHAR MusicFileShortPath[MAX_PATH] = L"";		// 短路径

// 按钮
WCHAR ButtonText[10];						// 按钮上的文本
WCHAR ButtonLengthText[10];					// 歌曲时长按钮文本
WCHAR ButtonTimeText[10];					// 歌曲当前时间按钮文本


// 歌曲相关参数
long length;								// 总的时间长度
int minute;									// 分
int second;									// 秒
long position;								// 歌曲当前位置
int m_pos;									// 当前位置分
int s_pos;									// 当前位置秒

// 计时器相关参数
UINT_PTR TimerID;							// 定时器ID
UINT barPos;								// 滑块位置
UINT PlayListIndex;							// 播放列表序列

// 菜单
HMENU rightMenu;								// 右键菜单


// 音乐播放器的前向函数声明
void				InitControl(HWND);			// 控件初始化
void				GetMusicFromConfig(void);
void				InitMusicTimeText(void);	// 初始化歌曲信息

void				MusicOpen(LPCWSTR);
void				MusicPlay(LPCWSTR);
void				MUSICPAUSE(LPCWSTR);
void				MUSICRESUME(LPCWSTR);
void				MUSICSTOP(LPCWSTR);
void				GetMusicLength(LPCWSTR);
void				GetCurrentPosition(LPCWSTR);
void				PlayFrom(LPCWSTR, UINT);

// 音乐文件格式
WCHAR MusicFileFormat[MUSICFILEFORMATNUMBER][FORMATLENGTH] = {L".mp3", L".wav"};

// 添加歌曲相关函数
void				AddMusicFiles(HWND);
void				FullPathToMusicName(WCHAR *, WCHAR *);	// 从完整路径中取出歌曲名
void				RemoveFormatString(WCHAR *);			// 移除歌名中的格式子串
void				OneFile(WCHAR *);						// 添加一个歌曲
void				MultipleFiles(OPENFILENAME, WCHAR *);	// 添加多首歌