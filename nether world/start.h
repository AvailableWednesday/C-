#pragma once	
#include<graphics.h>
#include<conio.h>
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(img);
	int	w = img->getwidth();
	int	h = img->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER,0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
int menu();
	class button {
	private:
		IMAGE idlebutton,hoveredbutton;
		RECT region;//矩形结构体，用来判定按钮区域
	public:
		void init( const char* button_idle,const char* button_hover,int x,int y,int width,int height) {
			loadimage(&idlebutton,button_idle,width,height);
			loadimage(&hoveredbutton,button_hover,width,height);
			region.left=x;
			region.top=y;
			region.right=x+width;
			region.bottom=y+height;
		}
		void draw(bool hovered) {
			if (hovered) {//如果update判断鼠标在按钮内右键点击，draw(true)加载hoveredbutton图片
				putimage_alpha(region.left, region.top, &hoveredbutton);
			}
			else {
				putimage_alpha(region.left, region.top, &idlebutton);
			}
		}
		int update(ExMessage msg) {
			//鼠标停在按钮上则按钮变化
				if(msg.x>=region.left&&msg.x<= region.right&& msg.y>= region.top&&msg.y<=region.bottom) {
					
						if (msg.message == WM_LBUTTONDOWN) {//鼠标右键，跳出初始界面开始进入对话
							return 2;
						}
						if (msg.message == WM_MOUSEMOVE) return 1;//鼠标在按钮上但未点击，返回1

					
				}
				
				return 0;
			}
		
	};