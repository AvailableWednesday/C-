#include<iostream>
using namespace std;
#include<graphics.h>
#include<conio.h>
#include"start.h"
#include"dialogue.h"
#include"work.h"
#include"card.h"
ExMessage msg;//定义存储消息的结构体
int main() {
	int state=0;
	initgraph(1200, 800);
	while (true) {

		switch (state) {
		case 0:state = menu(); break;
		case 1:	state = dialogue(); break;
		case 2:state = work(); break;
		case 3:state = card(); break;
		}
	
	}
	
	_getch();
	closegraph();
	return 0;





}