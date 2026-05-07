#include<graphics.h>
#include<conio.h>
#include <random>
#include "card.h"
#include<vector>
#include <algorithm>
#include"joker.h"
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
extern ExMessage msg;
extern int count;
extern void joker();
inline void putimage_alpha(int x, int y, IMAGE* img);
IMAGE allimg[4][13];//一次性加载所有图片，避免图片过多导致每次调用loadimage时卡顿
std::string type[9] = {
    "对子", "两对", "三条", "顺子",
    "同花", "葫芦", "四条", "同花顺", "皇家同花顺"
};
void loadAll() {
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            std::string path = std::to_string(i) + std::to_string(j) + ".png";
            loadimage(&allimg[i][j-1], path.c_str(), 100, 156);
        }
    }
}
std::vector<Card> setpoker() {
    std::vector<Card> poker;
    // 遍历 4 种花色
    for (int i = 0; i < 4; i++) {
        // 遍历 13 个点数
        for (int j = 1; j <= 13; j++) {
            Card temp(j, i,j);
            poker.push_back(temp);
        }
    }
    return poker;
}
Joker currjoker[3];
int currj = 0,times;
bool dusk = 0;
int score_time = 0, score_row = 0, score_all = 0, coin = 0, mult = 1;
int card() {
    mciSendString("open one-card-is-taken-from-the-deck.mp3 alias card", NULL, 0, NULL);
	std::vector <Card> poker = setpoker();//整个牌组
    std::random_device rd;
    std::mt19937 gen(rd());
	std::vector<Card> curr;//现在屏幕上发到的牌
    loadAll();
	IMAGE desk, hand,win,lose;
    loadimage(&hand, "hand.png", 1150, 650);
	loadimage(&desk, "desk.png", 1200, 800);
	loadimage(&win, "win.png", 1200, 800);
	loadimage(&lose, "lose.png", 1200, 800);
    int accomplish = count * 65 + 350;
    int judgetype(std::vector<Card>a);
    for (int row = 0; row < 3; ) {//每次游戏共三局
        std::shuffle(poker.begin(), poker.end(), gen);//使用随机数引擎进行洗牌
        std::vector <Card> poker = setpoker();
        std::shuffle(poker.begin(), poker.end(), gen);
        times = 1;
        score_row = 0;
        curr.clear();
        for (int i = 0; i < 8; i++) {
            Card c = poker.back(); // 取最后一张
            poker.pop_back();      // 弹出
            putimage_alpha(150 + i * 110, 520, c.img);
            curr.push_back(c);
        }
        while (times <= 6) {
            BeginBatchDraw();
            cleardevice();
            putimage(0, 0, &desk);
            for (int i = 0; i<currj; i++) {//在画面中显示当前持有的小丑牌
                int x = 450 + i * 100;
                int y = 20;
                IMAGE* img = &currjoker[i].front;//缩小原牌面
                HDC dstDC = GetImageHDC();
                HDC srcDC = GetImageHDC(img);
                int width = 85;
                int height = 165;
                BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
                AlphaBlend(dstDC, x,y, width, height, srcDC, 0, 0, img->getwidth(), img->getheight(), bf);
                putimage_alpha(x,y, &currjoker[i].front);
            }
            setlinecolor(WHITE);
            settextcolor(BLACK);
            settextstyle(25, 0, _T("微软雅黑 Bold"));
            rectangle(30, 260, 230, 340);
            outtextxy(40, 270, _T("牌型:"));
            outtextxy(40, 370, _T("得分:"));
            char score_buf[50];
            sprintf_s(score_buf, "%d / %d", score_row, accomplish);
            outtextxy(40, 400, score_buf);
            std::vector<Card> currentlypicked;
            for (int i = 0; i < 8; i++) {
                if (curr[i].count % 2 == 1) currentlypicked.push_back(curr[i]);
            }int Type = judgetype(currentlypicked);
            setbkmode(TRANSPARENT);
            settextstyle(28, 0, _T("微软雅黑"));
            settextcolor(BLACK);
            RECT word = { 40, 300, 230, 340 };
            if(Type<9)
            drawtext(type[Type].c_str(), &word, DT_LEFT | DT_TOP | DT_WORDBREAK);
            bool enter = false;
            std::vector<Card> selected_;
            while (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
                for (int i = 0; i < 8; i++) {
                    curr[i].init_(150 + i * 110, 550, 100, 156);
                    curr[i].update(msg);
                }
                enter = (msg.message == WM_KEYDOWN && msg.vkcode == VK_RETURN);
            }
            for (int i = 0; i < 8; i++) {
                if (curr[i].count % 2 == 1)
                    putimage_alpha(150 + i * 110, 550, curr[i].img);
                else putimage_alpha(150 + i * 110, 520, curr[i].img);
            }

            if (enter) {//如果按下回车，进入下一轮发牌

                int target = 0, j = 0, selected = 0; std::vector<int>location;
                for (int i = 0; i < 8; i++) {
                    if (curr[i].count % 2) {
                        curr[i].score = curr[i].num;
                        selected_.push_back(curr[i]);
                        location.push_back(i);//select最终值即打出牌的数量
                        selected++;
                        j = 0;
                    }
                }

                    /*else
                    {
                        float speed = 15.0f;//移动速度
                        int currx = 150 + i * 110;
                        target = 150 + location[j++] * 110;//把打出的牌右侧没被选中的牌平移到空缺位置
                        while (currx > target) {
                            if (currx - target > speed) currx -= speed;
                            else
                            {
                                currx = target;
                                // 足够接近时直接重合，防止抖动
                            }
                            putimage_alpha(currx, 550, curr[i].img);
                        }
                    }
                    curr[i].count = 0;//重置牌的状态
                }*/
                if (selected > 5 || selected == 0) {
                    enter = false;
                    for (int i = 0; i < (int)curr.size(); i++) {
                        curr[i].count = 0; // 强制所有牌回到下方位置
                    }
                    selected_.clear();
                }
                else {
                    mciSendString("play card from 0", NULL, 0, NULL);
                    int countscore(std::vector<Card> a);
                    void function(std::vector<Card> &a);
                    function(selected_);
                    score_time = countscore(selected_);
                    if (dusk)  score_time *= 2;
                    score_row += score_time;
                    for (int i = (int)location.size() - 1; i >= 0; i--) {
                        curr.erase(curr.begin() + location[i]);
                    } // 从 curr 中移除打出的牌
                    for (int j = 0; j < selected; j++) {
                        Card add = poker.back();
                        poker.pop_back();
                        int start = 1250, target = 150 + 110 * (8 - selected + j);
                        float speed = 25.0f;
                        curr.push_back(add);
                        while (start > target) {
                            if (start - target > speed) {
                                start -= speed;
                                putimage(0, 0, &desk);
                                putimage_alpha(75, -35, &hand);
                                for (int k = 0; k < (int)curr.size() - 1; k++) {
                                    putimage_alpha(150 + k * 110, 520, curr[k].img);
                                }
                                putimage_alpha(start, 520, add.img);
                                FlushBatchDraw();
                                Sleep(10);
                            }
                            else {
                                start = target;
                            }
                            putimage_alpha(start, 550, add.img);
                        }


                    }
                }
                times++;
                for (int i = 0; i < (int)curr.size(); i++) {
                    curr[i].count = 0; // 牌状态还原
                }
                selected_.clear();

            }//一次得分

            FlushBatchDraw();

        }//一局得分
        if (accomplish <= score_row) score_all++;
        coin += score_row /50;
        EndBatchDraw();
        while (peekmessage(&msg, EX_MOUSE | EX_KEY));
        if(row!=2)
        joker();
        row++;
		accomplish += row * 140;//每局目标分数递增
        BeginBatchDraw(); // 从商店回来后重新开启绘制
    }
    if (score_all < 2)//结算画面
    {
        while (true) {
            BeginBatchDraw();
            putimage(0, 0, &lose);
            while (peekmessage(&msg, EM_MOUSE)) {
                if (msg.message == WM_LBUTTONDOWN && msg.x < 750 && msg.y < 765 && msg.x>450 && msg.y>685) {
                    EndBatchDraw();
                    return 2;//重新开始
                }
            }
            FlushBatchDraw();
        }
       
    }
    else {
       
        while (true) {
            BeginBatchDraw();
            putimage(0, 0, &win);
            while (peekmessage(&msg, EM_MOUSE)) {
                if (msg.message == WM_LBUTTONDOWN && msg.x < 750 && msg.y < 765 && msg.x>450 && msg.y>685) {
                    EndBatchDraw();
                    return 2;//重新开始
                }
            }
            FlushBatchDraw();
        }
    }
}
int countscore(std::vector<Card> a) {//牌型判断函数，返回单次打出牌的得分
    int add=0;
    for (int i = 0; i < a.size(); i++) {
        add += a[i].score;

    }
        if (a.empty()) return 0;
        // 1. 按点数排序 (从小到大)
        std::sort(a.begin(), a.end(), [](const Card& c1, const Card& c2) {
                return c1.num < c2.num; });
// 2. 统计频率
        int counts[15] = { 0 }; // 统计 1-13 每个点数出现的次数
        for (const auto & card : a) {
            if (card.num >= 1 && card.num <= 13 ) {
                counts[card.num]++;
            }
        }
        std::vector<int> freq; // 提取非零次数并降序排列，例如三条会得到 {3, 1, 1}
        for (int i = 1; i <= 13; i++) {
            if (counts[i] > 0) freq.push_back(counts[i]);
        }
        std::sort(freq.begin(), freq.end(), std::greater<int>());
        // 3. 基本特征判定
        // 同花判定
        bool isFlush = (a.size() >= 2); ;
        for (size_t i = 1; i < a.size(); i++) {
            if (a[i].suit != a[0].suit) {
                isFlush = false;
                break;
            }
        }
        // 顺子判定 (仅针对 5 张牌的情况)
        bool isStraight = false;
        if (a.size() == 5) {
            // 普通顺子 (例如 2-3-4-5-6)
            if (a[4].num - a[0].num == 4 && freq.size() == 5) {
                isStraight = true;
            }
            // 特殊顺子 (A-2-3-4-5): 在你的系统中 A=1, 10=10, J=11, Q=12, K=13
            // 如果是 A, 2, 3, 4, 5，排序后应该是 1, 2, 3, 4, 5
            // 如果是 10, J, Q, K, A，排序后应该是 1, 10, 11, 12, 13
            if (a[0].num == 1 && a[1].num == 10 && a[2].num == 11 && a[3].num == 12 && a[4].num == 13) {
                isStraight = true;
            }
        }
        // 4. 牌型组合得分逻辑
        if(isFlush && isStraight) {
            // 皇家同花顺 (10, J, Q, K, A 且同花)
            if (a[0].num == 1 && a[1].num == 10) return 800;
            return 500; // 同花顺
        }

        if (!freq.empty()) {
            if (freq[0] == 4) return 400; // 四条
            if (freq[0] == 3 && freq.size() >= 2 && freq[1] == 2) return 300; // 葫芦
            if (isFlush) return 200; // 同花
            if (isStraight) return 150; // 顺子
            if (freq[0] == 3) return 100; // 三条
            if (freq.size() >= 2 && freq[0] == 2 && freq[1] == 2) return 50+add; // 两对
            if (freq[0] == 2) return 20+add; // 对子
        }
        return add; // 无特殊牌型
    }
void Card::init_(int x, int y, int width, int height) {
    region_.left = x;
    region_.top = y;
    region_.right = x + width;
    region_.bottom = y + height;
}
void function(std::vector<Card>&a) {
    bool duskused = 0;
    for (int i = 0; i < 3; i++) {
        int n = currjoker[i].num;
        if (n == 10) { //印刷错误
            for(int j=0;j<a.size();j++)
            a[j].score*= rand() % 21;
        }
        else if (n == 4) { // 半个小丑
            if (a.size() <= 3) {
                for (int j = 0; j < a.size(); j++)
                    a[j].score *= 20;
            }
        }
        for (int j = 0; j < (int)a.size(); j++) {
            if (n == 3) { // 恐怖面孔(QJK+30)
                if (a[j].num >= 11) { // J=11, Q=12, K=13
                    a[j].score += 30;
                }
            }
            else if (n == 1) { //偶数史蒂文
                if (a[j].num % 2 == 0) {
                    a[j].score *= 4;
                }
            }
            else if (n == 5) {    //贪婪小丑
                if (a[j].suit == 3) {
                    a[j].score *= 3;
                }
            }
            else if (n == 7) {    //色欲小丑
                if (a[j].suit == 1) {
                    a[j].score *= 3;
                }
            }
            else if (n == 6) {    //愤怒小丑
                if (a[j].suit == 0) {
                    a[j].score *= 3;
                }
            }
            else if (n == 8) {    //暴食小丑
                if (a[j].suit == 2) {
                    a[j].score *= 3;
                }
            }
            else if (n == 9) { //黄昏
                if (times == 4 && !duskused)
                {
                    dusk = 1; duskused = 1;
                }
                else dusk = 0;
            }
        }
    }
}
int judgetype(std::vector<Card> a) {//牌型判断函数，返回单次打出牌的得分
    // 1. 按点数排序 (从小到大)
    std::sort(a.begin(), a.end(), [](const Card& c1, const Card& c2) {
        return c1.num < c2.num; });
    // 2. 统计频率
    int counts[15] = { 0 }; // 统计 1-13 每个点数出现的次数
    for (const auto& card : a) {
        if (card.num >= 1 && card.num <= 13) {
            counts[card.num]++;
        }
    }
    std::vector<int> freq; // 提取非零次数并降序排列，例如三条会得到 {3, 1, 1}
    for (int i = 1; i <= 13; i++) {
        if (counts[i] > 0) freq.push_back(counts[i]);
    }
    std::sort(freq.begin(), freq.end(), std::greater<int>());
    // 3. 基本特征判定
    // 同花判定
    bool isFlush = (a.size() >= 2);
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i].suit != a[0].suit) {
            isFlush = false;
            break;
        }
    }
    // 顺子判定 (仅针对5张牌的情况)
    bool isStraight = false;
    if (a.size() == 5) {
        // 普通顺子
        if (a[4].num - a[0].num == 4 && freq.size() == 5) {
            isStraight = true;
        }
        // 特殊顺子 (A-2-3-4-5):  A=1, 10=10, J=11, Q=12, K=13
        // 如果是 A, 2, 3, 4, 5，排序后应该是 1, 2, 3, 4, 5
        // 如果是 10, J, Q, K, A，排序后应该是 1, 10, 11, 12, 13
        if (a[0].num == 1 && a[1].num == 10 && a[2].num == 11 && a[3].num == 12 && a[4].num == 13) {
            isStraight = true;
        }
    }
    // 4. 牌型组合得分逻辑
    
       if (isFlush && isStraight) {
        // 皇家同花顺 (10, J, Q, K, A 且同花)
        if (a[0].num == 1 && a[1].num == 10) return 8;
        return 7; // 同花顺
    }

    if (!freq.empty()) {
        if (freq[0] == 4) return 6; // 四条
        if (freq[0] == 3 && freq.size() >= 2 && freq[1] == 2) return 5; // 葫芦
        if (isFlush) return 4; // 同花
        if (isStraight) return 3; // 顺子
        if (freq[0] == 3) return 2; // 三条
        if (freq.size() >= 2 && freq[0] == 2 && freq[1] == 2) return 1; // 两对
        if (freq[0] == 2) return 0; // 对子
    }
    return 9;
}
