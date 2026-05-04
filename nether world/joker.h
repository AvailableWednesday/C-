#pragma once
#include<graphics.h>
#include<conio.h>
#include <random>
#include<string>
#include"card.h"
#include<vector>
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(img);
	int	w = img->getwidth();
	int	h = img->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER,0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
extern ExMessage msg;
extern int coin;
extern int mult;
extern bool dusk;
extern int times;
class Joker {
	
	RECT region;
	bool state = 0;
public:
	IMAGE front, back, picked;
	bool  onsale = 1;
	int count = 0,price,num;
	Joker() {};
	Joker(int x, int y) : price(x), num(y) {};
	Joker(IMAGE x, IMAGE y, IMAGE z) :front(x), back(y), picked(z) {}
	 void init(int x, int y, int width, int height) {
		region.left = x;
		region.top = y;
		region.right = x + width;
		region.bottom = y + height;
	}
	int update(ExMessage msg) {
		if (msg.x >= region.left && msg.x <= region.right && msg.y >= region.top && msg.y <= region.bottom) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (state == 0)//在正面
				{
					count++;
					return 1;
				}
				else {//在反面，左键可翻面到正面
					state = !state;
					return 1;
				}


			}
			else if (msg.message == WM_RBUTTONDOWN)
			{
				state = !state;
				return 2;//右键翻面到反面
			}
			else return 0;
		}
		 return 0;
	}

	void draw() {
		if (!state) {
			if (count % 2 == 0&&onsale) {
				putimage_alpha(region.left, region.top, &front);
			}
			else putimage_alpha(region.left, region.top, &picked);
		}
		else
			putimage_alpha(region.left, region.top, &back);
		
	}
};
