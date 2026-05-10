#include<graphics.h>
#include<conio.h>
#include "work.h"
#include<random>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#include<string>
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(img);
	int	w = img->getwidth();
	int	h = img->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER,0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC,0, 0, w, h, bf);
}
int count=0;
extern ExMessage msg;
int work() {
	settextstyle(
	34, 0, _T("微软雅黑"));
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	mciSendString("open colorful-adventures_88142.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("open sound5.mp3 alias next", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	std::random_device rd;
	std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 17);
	IMAGE office, office_, yes,Yes,YES,no,No,NO,num;
	character person[18] = {//有19种回答组
		character("Michael","28","我是一个作家，至少我这样称呼自己。","我总是试图找寻人生的方向，没想到一次意外直接给了我答案——但这并非无法接受，因为我只是生命的承受者。","npc_1.png","npc1.png","frame.png"),
		character("Michael","28","作家","非常不幸，我在睡着的时候被砸死了，但事实就是这样。","npc_1.png","npc1.png","frame.png"),
		character("Emma Johnson","19","我还没有从学校毕业呢","我不知道……我还无法接受最后的记忆是一场幻觉，我也无法接受我的死亡——明明一切都在慢慢变好，不是吗？","npc_2.png","npc2.png","frame.png"),
		character("Emma Johnson","19","学生","无可奉告","npc_2+.png","npc2.png","frame.png"),
		character("May Taylor 你可以叫我Viper，这是我的绰号","52","……统治者。","其实我根本没指望自己能活到这么久，毕竟对于我们这些人来说，我已经算是幸运了，对吧？","npc_3.png","npc3.png","frame.png"),
		character("Ms.Williams","27","杀手。","这是我的耻辱！","npc_4.png","npc4.png","frame.png"),
		character("Olivia Williams","27","杀手。","我被别人杀掉了。","npc_4+.png","npc4.png","frame.png"),
		character("Mr.Hernandez","36","我是个设计师，哈哈哈。","说来话长。这是一场悲剧，它本不该发生。被火烧死是最痛苦的死法之一，但我又有什么办法呢？该过去的都过去了，伙计。","npc_5.png","npc5.png","frame.png"),
		character("Mr.Hermandez","36","我是个设计师，哈哈哈。","说来话长。这是一场悲剧，它本不该发生。被火烧死是最痛苦的死法之一，但我又有什么办法呢？该过去的都过去了，伙计。","npc_5.png","npc5.png","frame.png"),
		character("Christopher 朋友们直接称呼我Chris","25","我是摄影师；这是我的爱好，也是我的职业。这样的生活本该持续很久很久的。","我的死亡实在是荒谬。请替我问候我的朋友和亲人，拜托你了，我的朋友。","npc_6.png","npc6.png","frame.png"),
		character("Christopher Jackson","25","如你所见，我是一名摄影师","我知道你想问什么，我的眼镜被榴莲砸碎了。现在我只感到震惊。","npc_6+.png","npc6.png","frame.png"),
		character("Sam","22","呃……实话实说，还没找到。","我昏了过去，醒来之后就来到了这个地方。这是哪里？你是外星人吗？","npc_7.png","npc7.png","frame.png"),
		character("Sam","22","我是科学家！","你把我捕获到了飞船上，因为我偷了你的燃料；你能接受我的采访再把我放回去吗？","npc_7.png","npc7.png","frame.png"),
		character("Dr.Reid","65","我曾经是一名医生。","命运无常。生命是脆弱的东西，只是我不够幸运。愿你幸运，孩子。","npc_8.png","npc8.png","frame.png"),
		character("我是羊驼人。","999","我是羊驼人。","我是羊驼人。","npc_10.png","npc10.png","frame.png"),
		character("Ms.Vesper","37","大家叫我艺术家，实际上我最擅长雕刻。","生命是一场旅行，而我像我的姓氏一般，在黄昏进行着永恒的晚祷。很高兴认识你。","npc_9.png","npc9.png","frame.png"),
		character("Sloane","37","无可奉告。","无可奉告","npc_9+.png","npc9.png","frame.png"),
		character("Ms.Vesper","37","雕刻家","我坚信人的归宿是自然，所以我选择了死后进行水葬。","npc_9.png","npc9.png","frame.png"),
	};
	loadimage(&office, "office.png", 1200, 800);
	loadimage(&office_, "copyoffice.png", 1200, 800);
	putimage(0, 0, &office);
	loadimage(&yes, "yes_03.png", 120, 140);
	loadimage(&no, "no_03.png", 120, 140);
	loadimage(&No, "no_04.png", 120, 140);
	loadimage(&NO, "no_05.png", 120, 140);
	loadimage(&Yes, "yes_04.png", 120, 140);
	loadimage(&YES, "yes_05.png", 120, 140);
	loadimage(&num, "num.png", 1200, 800);
	Sleep(500);
	bool mouse,start=0;//更新鼠标点击
	int i = 1,temp=0,next=0,index;
	count = 0;//每次进入work函数时重置count，防止重复进入work函数时count叠加
	character random;//先随机第一个人物的立绘和卡片，
	//进入循环后如果i自增，则检测到进入下一个人物，再随机一个立绘和卡片
		while (i < 7) {//一轮游戏六个人物，结束后进入balatro
			BeginBatchDraw();

			while (peekmessage(&msg, EM_MOUSE)) {
				if (msg.message == WM_LBUTTONDOWN)
					mouse = 1;
				else mouse = 0;
			}
			if (i > temp)//用temp存i的旧值，如果i自增，则检测到进入下一个人物
			{
				mciSendString("play next from 0", NULL, 0, NULL);
				start = 0;
				next = 0;
				temp = i;
				random = person[index = dis(gen)];//立绘和卡牌各随机一个人物
				cleardevice;
				putimage(0, 0, &office); Sleep(300);
				random.displayperson();
				putimage_alpha(0, 0, &office_);
			}
			if (random.change(msg) == 4)
				putimage_alpha(1000, 350, &Yes);
			if (random.change(msg) == 7)
				putimage_alpha(1000, 200, &No);
			if (!random.change(msg))
				putimage_alpha(1000, 350, &yes);
			if (!random.change(msg))
				putimage_alpha(1000, 200, &no);
			if (mouse)
			{
				if (!start) {//如果是新一个角色，点击后显示卡片
					start = 1;
					random.displaycard();
					next = 1;
					putimage_alpha(1000, 350, &yes);
					putimage_alpha(1000, 200, &no);
				}
				else {
					if (next) {
						random.init(195, 170, 90, 45);//已经显示了卡片，则判断在卡片上的点击区域以进入不同回答
						if (random.update(msg)) {
							random.sayname();
						}
						else {
							random.init(195, 225, 70, 45);
							if (random.update(msg))
								random.sayage();
							else {
								random.init(195, 250, 100, 45);
								if (random.update(msg))
									random.saycareer();
								else {
									random.init(195, 300, 180, 40);
									if (random.update(msg))
										random.saystory();

								}
							}

						}
						int update = random.change(msg);
						switch (update) {

						case 6:	putimage_alpha(1000, 200, &NO); break;
						case 5:putimage_alpha(1000, 350, &YES); break;

						}
						if (random.next(msg)) {
							i++;
							bool result = (random.YesOrNo(msg));
							if ((result == true && (index == 1 || index == 3 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14 ))||(result==false && (index == 0 || index == 2 || index == 4 || index == 5 || index == 7 || index == 9 || index == 11 || index == 13 || index == 15)))
								count++;
						}//点击判断按钮跳出此人物

					}
				}
			}
			FlushBatchDraw();
		}
		mciSendString("stop bgm", NULL, 0, NULL);
		mciSendString("close bgm", NULL, 0, NULL);
		mciSendString("open distant-bell-tower-of-the-basilica-of-the-national-sanctuary-of-the-immaculate-conception.mp3 alias bgm2", NULL, 0, NULL);
		mciSendString("play bgm2 from 0", NULL, 0, NULL);
		putimage(0,0,&num);
		
		settextstyle(240, 0, _T("Copperplate Gothic Bold"));
		settextcolor(WHITE);
		std::string c = std::to_string(count);
		outtextxy(555, 275, c.c_str());
		FlushBatchDraw();
		Sleep(5000);
		mciSendString("close bgm2", NULL, 0, NULL);
	return 3;
}