#include<graphics.h>
#include<conio.h>
#include"start.h"
#include<string>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
IMAGE background_start,guide;
extern ExMessage msg;

int menu() {
	int volume = 300;// 初始音量30%
	bool operate = false; // 是否正在拖动音量条
	RECT vol = { 400, 600, 800, 620 }; // 音量条
	button startbutton;
	button setbutton;
	int judge=0,judgeset=0;
	int set = 0;
	bool iFguide = false;
	loadimage(&background_start,"start.bmp",1200,800);
	loadimage(&guide,"guide.png", 800, 600);
	startbutton.init("button_idle.png","button_hover.png",500,500,200,100);//判断点击范围
	setbutton.init("set.png", "set.png", 850, 500, 150, 150);
	putimage(0,0,&background_start);
	mciSendString("open whispers-of-calm_93399.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("open off-button-on-table-lamp.mp3 alias click", NULL, 0, NULL);
	void fade_out_bgm(const char* alias, int current_vol);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	while (true) {
		BeginBatchDraw();
		putimage(0, 0, &background_start);
		while (peekmessage(&msg, EM_MOUSE | EM_KEY))
		{
			if (!iFguide) {//没看说明书的时候
				judge = startbutton.update(msg);
				judgeset = setbutton.update(msg);

				startbutton.draw(judge);
				if (judge == 2) {
					mciSendString("play click from 0", NULL, 0, NULL);

					fade_out_bgm("bgm", volume);
					return 1;
				}
				if (judgeset == 2) {
					mciSendString("play click from 0", NULL, 0, NULL);
					iFguide = true;

				}
			}
			else//打开了说明书
			{
				if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
					iFguide = false;

				if (msg.message == WM_LBUTTONDOWN) {
					if (msg.x >= vol.left && msg.x <= vol.right &&
						msg.y >= vol.top && msg.y <= vol.bottom) {//移动音量
						operate = true;
					}
				}
				else if (msg.message == WM_LBUTTONUP) {
					operate = false; // 鼠标停止移动
				}
				else if (msg.message == WM_MOUSEMOVE && operate) {
					if (msg.x >= vol.left && msg.x <= vol.right) {
						volume = (msg.x - vol.left) * 1000 / (vol.right - vol.left);
						char cmd[100];
						sprintf_s(cmd, "setaudio bgm volume to %d", volume);
						mciSendString(cmd, NULL, 0, NULL);
					}
				}
			}

		}
		startbutton.draw(judge == 1);
		setbutton.draw(judgeset == 1);
		if (iFguide) {
			putimage_alpha(200, 100, &guide);
			setlinecolor(WHITE);
			rectangle(vol.left, vol.top, vol.right, vol.bottom);
			int fill_width = (volume * (vol.right - vol.left)) / 1000;
			setfillcolor(LIGHTGRAY);
			fillrectangle(vol.left, vol.top, vol.left + fill_width, vol.bottom);
			outtextxy(vol.left, vol.top + 35, _T("调节音量"));
		}
		FlushBatchDraw();
	}
	}
void fade_out_bgm(const char* alias, int current_vol) {
	for (int v = 500; v >= 0; v -= 10) {
		char cmd[50];
		sprintf_s(cmd, "setaudio bgm volume to %d", v);
		mciSendString(cmd, NULL, 0, NULL);
		Sleep(20); // 每 20 毫秒降低一点音量
	}
	mciSendString("stop bgm", NULL, 0, NULL);
	mciSendString("close bgm", NULL, 0, NULL);
}