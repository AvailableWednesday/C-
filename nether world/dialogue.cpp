#include<graphics.h>
#include<conio.h>
#include "dialogue.h"
extern ExMessage msg;
bool next = 0,dialog=0;
int dialogue() {
	
	int end = 0;
	IMAGE first,dia;
	death conversation;
	IMAGE photo;
	loadimage(&photo, "clown.png", 1200, 800);
	loadimage(&first, "death.png", 600, 800);
	loadimage(&dia, "dialog.png", 1200,800);
	BeginBatchDraw();
	while (true) {
		cleardevice();
		if(!next)putimage(300, 0, &first);//未点击，加载初始图片
		while (peekmessage(&msg, EM_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN)
			{
				next = true;
				//先加载图片再更新对话
				if(dialog)conversation.clicked();
			}
		}
		if (dialog)conversation.update();//如果已经进入对话，打字
		
		if (next) { 
			if (!conversation.clown)putimage(0, 0, &dia);
			if (conversation.clown)conversation.draw_photo(photo);
			conversation.draw(); 
			dialog = true;
		
		}
		
			if (conversation.sentence > 13) return 2;//如果对话结束，返回2进入游戏
			FlushBatchDraw();
			Sleep(20);
	}
	EndBatchDraw();
	return 2;
}