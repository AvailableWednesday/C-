#include<graphics.h>
#include<conio.h>
#include <random>
#include<string>
#include"joker.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
extern ExMessage msg;
extern int coin;extern int currj;
extern Joker currjoker[3];
void joker() {
	mciSendString("open sound-take-one-coin-from-the-bag.mp3 alias coin", NULL, 0, NULL);
	IMAGE shop, joker[10], jokerback[10], jokerpicked[10];
	Joker card[10];
	loadimage(&shop, "shop.png", 1200, 800);
	putimage(0, 0, &shop);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9);
	for (int i = 0; i < 10; i++)
	{
		if (i != 9)
			card[i].price = 5;
		else card[i].price = 4;
		card[i].num = i + 1;
		std::string path = "joker" + std::to_string(i + 1) + ".png";
		loadimage(&joker[i], path.c_str(), 175, 340);
		loadimage(&jokerback[i], ("joker" + std::to_string(i + 1) + "back" + ".png").c_str(), 175, 340);
		loadimage(&jokerpicked[i], ("joker" + std::to_string(i + 1) + "picked" + ".png").c_str(), 175, 340);
		card[i].front = joker[i]; card[i].back = jokerback[i]; card[i].picked = jokerpicked[i];

	}
	Joker random[4] = { card[dis(gen)], card[dis(gen)], card[dis(gen)] ,card[dis(gen)] };
	int picture = 0;
	while (true) {
		BeginBatchDraw();
		putimage(0, 0, &shop);
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 3);
		rectangle(50, 80, 500, 155); // 在左上角画一个矩形框
		settextcolor(WHITE);
		settextstyle(30, 0, _T("Consolas"));
		std::string coinStr = "当前持有钱币: " + std::to_string(coin);
		outtextxy(75, 92, coinStr.c_str());
		for (int i = 0; i < 4; i++) {
			random[i].init(130 + i * 255, 270, 175, 337);
			random[i].draw();
		}
		while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
			for (int i = 0; i < 4; i++) {
				picture = random[i].update(msg);
			}
			if ((msg.x >= 345 && msg.x <= 655 && msg.y >= 610 && msg.y <= 720) && msg.message == WM_LBUTTONDOWN) {
				if (coin >= 1) {
					mciSendString("play coin from 0", NULL, 0, NULL);
					coin -= 1;
					for (int i = 0; i < 4; i++) {
						random[i] = card[dis(gen)];
						random[i].init(130 + i * 255, 270, 175, 337);
					}
				}
			}
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_RETURN) {
				for (int i = 0; i < 4; i++) {
					if (currj < 3 && random[i].count % 2 && random[i].onsale) {//正面被选中状态并且没卖出
						if (coin >= random[i].price) {
							coin -= random[i].price;
							currjoker[currj] = random[i];
							currj++;
							random[i].onsale = 0;
							mciSendString("play coin from 0", NULL, 0, NULL);
						}
					}
				}
			}
			if (msg.x >= 840 && msg.x <= 1070 && msg.y >= 685 && msg.y <= 770 && msg.message == WM_LBUTTONDOWN)//跳过
			{
				EndBatchDraw();
				return;
			}
		}
		FlushBatchDraw();
	}
}