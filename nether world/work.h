	#pragma once
#include <string>
#include <graphics.h>
#include<conio.h>
#pragma comment(lib, "MSImg32.lib")
void putimage_alpha(int x, int y, IMAGE* img);

int work();
class character {
	private:
		RECT region, word = {300,660,975,760};
		int wid = 500;
		int len= 1100;
		int x = 75, y = 400;
		std::string name, age;
		std::string career, story;
		bool judge;
		IMAGE card, frame, portrait;
		std::string pathPor, pathCard, pathFrame;
public:
	character(std::string a, std::string b, std::string c, std::string d, std::string e, std::string f, std::string g) {
		name = a;
		age = b;
		career = c;
		story = d;
		pathPor = e;
		pathCard = f;
		pathFrame = g;
	}
	character()= default;
	void displayperson() {//参数传入文件夹内图片路径，图片大小 显示人物立绘
		loadimage(&portrait, pathPor.c_str(), 400, 500);//由于loadimage无法识别string，所以需要.c_str()转换成char*
		putimage_alpha(450, 150, &portrait);
	}
	
	void displaycard() {//显示身份卡
		loadimage(&card, pathCard.c_str(),582 , 465);
		putimage_alpha(50, 100, &card);
	}
	void sayname() {//负责点击不同区域后分别进入对name\age\career\story的回答
		loadimage(&frame, pathFrame.c_str(), len, wid);
		putimage_alpha(x, y, &frame);
		setbkmode(TRANSPARENT);
		drawtext(name.c_str(), &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void sayage() {
		loadimage(&frame,pathFrame.c_str(), len, wid);
		putimage_alpha(x, y, &frame);
		setbkmode(TRANSPARENT);
		drawtext(age.c_str(), &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}	
	void saycareer() {
		loadimage(&frame,pathFrame.c_str(), len, wid);
		putimage_alpha(x, y, &frame);
		setbkmode(TRANSPARENT);
		drawtext(career.c_str(), &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void saystory() {
		loadimage(&frame, pathFrame.c_str(), len, wid);
		putimage_alpha(x, y, &frame);
		setbkmode(TRANSPARENT);
		drawtext(story.c_str(), &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}
	void init( int x, int y, int width, int height) {//鼠标点击区域限定 name:320,65 150*50 age(320,145) 115*50 
		region.left = x;                             //career(320,225) 190*50 death:329*310 330*50
		region.top = y;
		region.right = x + width;
		region.bottom = y + height;
	}
	bool update(ExMessage msg) {//鼠标点击判定，判定成功后输出对应的say函数
		if (msg.x >= region.left && msg.x <= region.right && msg.y >= region.top && msg.y <= region.bottom) {
			if (msg.message == WM_LBUTTONDOWN) {
				judge = true;
				return judge;
			}
		}
		return 0;
	}
	bool next(ExMessage msg) {//判断是否进入下一个人物，返回true则进入下一个人物
		if (msg.x >= 1000 && msg.x <= 1120 && msg.y >= 200 && msg.y <= 470) {//判断按钮区域
			if (msg.message == WM_LBUTTONDOWN) {
				return true;
			}
		}
		return false;
	}
	bool YesOrNo(ExMessage msg) {
		bool result=0;
		if (msg.x >= 1000 && msg.x <= 1120 && msg.y >= 350 && msg.y <= 470) {//勾
			if (msg.message == WM_LBUTTONDOWN) {
				result = true;
			}
		}
		else if (msg.x >= 1000 && msg.x <= 1120 && msg.y >= 200 && msg.y <= 320) {//叉
		
			if (msg.message == WM_LBUTTONDOWN) {
				result = false;
			}
		}
		return result;
	}
	int change(ExMessage msg) {
		if (msg.x >= 1000 && msg.x <= 1120 && msg.y >= 350 && msg.y <= 470) {//勾

			if (msg.message == WM_LBUTTONDOWN)
				return 5;
			else if (msg.message == WM_MOUSEMOVE)
				return 4;
		}
		else if (msg.x >= 1000 && msg.x <= 1120 && msg.y >= 200 && msg.y <= 320) {//叉

			if (msg.message == WM_LBUTTONDOWN)
				return 6;
			else if (msg.message == WM_MOUSEMOVE)
				return 7;

		}
		else return 0;
	}
	






};
