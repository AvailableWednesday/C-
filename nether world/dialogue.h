#pragma once
#include<graphics.h>
#include<conio.h>
#include<cstring>
int dialogue();
class death {
private:
	char text[14][200] = { "你就是新来的守门人吧？" ,"我是死神。接下来我会说明你的工作内容。",
		"你负责检查从人间来的灵魂，驱逐试图混入这里的恶灵。","简单来说，阅读一个灵魂的生平，并审问它以找出伪装者。"
	,"死神的世界很无聊。这也许是因为我活的实在太久了。","下班之后，我喜欢玩一种特殊的扑克牌。","你在工作期间错判的灵魂越多，当天的对局中得分要求越高。","也就是说，越难赢过我。",
		"每次赢过我，你都会得到一些冥币。你可以在牌局结束后用它们来换取道具。","这能帮助你工作更轻松，又或者在明天的比赛中多一些胜算。",
	"总之，你需要认真对待你的工作","————以及下班后的牌局。","这里的上一任守门人？辞职了。","最后，祝你好运。" },
		temp[200];//对话文本，二维数组，每行200字，一共10行
	

public:
	int sentence = 0, letter = 0;
	bool clown = 0;//标记当前第几个字，用以动态显示
	void update() {
		static int lastTime = 0;//控制显示速度
		int now = GetTickCount();
		if (now - lastTime > 50) {
			if (letter < strlen(text[sentence])) {
				letter++;
				lastTime = now;
			}
			
		}
	}
	void clicked() {
		
			if (letter < strlen(text[sentence]))
			{
				letter = strlen(text[sentence]);
				
			}
			//如果鼠标点击且一句话未显示完成，直接显示整句话
			else {
				sentence++;
				letter = 0;
				//如果已经显示整句话，点击进入下一句话

			}
		
		if (sentence == 5||sentence==6) {
			clown = true;//在第四句话时显示小丑照片
		}
		else clown = 0;
	};

		void draw() { 
			settextstyle(33, 0, "宋体");
			strcpy_s(temp, text[sentence]);//把当前句子复制到temp
			temp[letter] = '\0';//一句话一点一点显示，直到显示完整
			outtextxy(100,645, temp);
			
		};
		void draw_photo(IMAGE a) {
			
			putimage(0, 0, &a);
		};
	};