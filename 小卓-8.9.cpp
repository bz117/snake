#include<graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

void renderGameView() {
	initgraph(800, 600); //窗口大小
	setbkcolor(WHITE); //窗口背景色
	cleardevice(); //刷新窗口
	IMAGE map;
	loadimage(&map, _T("map.png"), 520, 520); //载入地图图片，调整大小，修改橙色的图片地址即可
	putimage(150, 40, &map); //显示图片

	//顶部显示：时间、长度、分数
	settextstyle(40, 0, _T("Consolas")); //设置字体为高40像素的“Consolas”
	settextcolor(BLACK); //字体颜色
	setbkmode(TRANSPARENT); //文字背景色透明
	outtextxy(75, 0, _T("time"));
	outtextxy(345, 0, _T("length"));
	outtextxy(645, 0, _T("score"));

	//底部显示：游戏操作提示
	settextstyle(40, 0, _T("Consolas")); //设置字体为高40像素的“Consolas”
	settextcolor(BLACK); //字体颜色
	outtextxy(155, 560, _T("wasd修改方向，空格暂停游戏"));

	//显示蛇头
	IMAGE head;
	loadimage(&head, _T("head.png"), 26, 26); //载入图片，调整大小，修改橙色的图片地址即可
	putimage(snake[0][0], snake[0][1], &head); //显示图片

	//显示蛇身
	IMAGE body;
	loadimage(&body, _T("body.png"), 26, 26); //载入图片，调整大小，修改橙色的图片地址即可
	for (int i = 1; i < snakeLength; i++)
	{
		putimage(snake[i][0], snake[i][1], &body); //显示图片
	}

	cout << "renderGameView works!\n";		//测试gameLoopView()
}




