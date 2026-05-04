#pragma once
#include<graphics.h>
#include<conio.h>
#include<string>
int card();
extern IMAGE allimg[4][13];
extern void loadAll();
class Card {
private:RECT region_,word;
public:
	int num, suit,count=0,score;//用数字1-13分别代表A-K，0-3分别代表黑桃、红桃、梅花、方块
	IMAGE *img;
	void init_(int x, int y, int width, int height);
    Card(int x, int y,int z) :num(x), suit(y),score(z) {
		img = &allimg[suit][num - 1];
	/*显示牌型的文字区域：word.left=...*/
	
	}
	void update(ExMessage msg) {
		if (msg.x >= region_.left && msg.x <= region_.right && msg.y >= region_.top && msg.y <= region_.bottom) {
			if (msg.message == WM_LBUTTONDOWN) {
				count++;//count为奇数，说明此牌被选中；count为偶数说明又点击了一次牌，取消选中
			}
		}
		
	}
	void showtype1() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("对子", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype2() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("两对", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype3() {
		setbkmode(TRANSPARENT);
		drawtext("三条", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype4(){
			setbkmode(TRANSPARENT);
			drawtext("顺子", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
		}
	void showtype5() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("同花", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype6() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("葫芦", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype7() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("四条", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype8() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("同花顺", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void showtype9() {//显示牌型
		setbkmode(TRANSPARENT);
		drawtext("皇家同花顺", &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
};

