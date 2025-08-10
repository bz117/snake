#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>

using namespace std;


// 皮肤
int _skin = 0;


void _renderGameView(int _mode = 0) {
	setbkcolor(WHITE);  // 窗口背景色
	cleardevice();      // 刷新窗口

	// 绘制游戏区域边框（20x20网格，每格26像素）
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(150, 40, 150 + 20 * 26, 40 + 20 * 26);  // 游戏区域边框：520x520像素

	// 根据模式展示不同的地图
	if (_mode == 1)
	{
		IMAGE map1;
		loadimage(&map1, _T("map.png"));
		putimage(150, 40, &map1);
	}
	else if (_mode == 2)
	{
		IMAGE map2;
		loadimage(&map2, _T("./项目细节/res/海洋.png"));
		putimage(150, 40, &map2);
	}
	else if (_mode == 3)
	{
		IMAGE map3;
		loadimage(&map3, _T("./项目细节/res/蜜蜂地图.png"));
		putimage(150, 40, &map3);
	}
	else if (_mode == 4)
	{
		IMAGE map4;
		loadimage(&map4, _T("./项目细节/res/岩浆地图.png"));
		putimage(150, 40, &map4);
	}


	// 绘制网格线
	setlinecolor(LIGHTGRAY);
	setlinestyle(PS_SOLID, 1);
	for (int i = 1; i < 20; i++) {
		// 垂直线
		line(150 + i * 26, 40, 150 + i * 26, 40 + 20 * 26);
		// 水平线
		line(150, 40 + i * 26, 150 + 20 * 26, 40 + i * 26);
	}

	// 顶部显示：长度、分数
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(75, 5, _T("时间"));    // 预留时间显示位置
	outtextxy(300, 5, _T("长度"));
	outtextxy(500, 5, _T("分数"));

	// 显示实际数值（长度和分数）
	char lengthStr[20], scoreStr[20];
	sprintf_s(lengthStr, "%d", snakeLength);
	sprintf_s(scoreStr, "%d", currentScore);

	outtextxy(350, 5, lengthStr);  // 显示长度
	outtextxy(550, 5, scoreStr);   // 显示分数

	// 底部显示：游戏操作提示
	settextstyle(20, 0, _T("微软雅黑"));
	outtextxy(250, 580, _T("WASD控制方向，空格暂停游戏"));

	// 显示墙体 - 棕色方块
	setfillcolor(BROWN);
	setlinecolor(BLACK);
	int wall_pixel_x = 150;  // 墙体像素x坐标
	int wall_pixel_y = 40;   // 墙体像素y坐标
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (_map0[i][j] == 1)
			{
				wall_pixel_x = 150 + j * 26;
				wall_pixel_y = 40 + i * 26;
				fillrectangle(wall_pixel_x + 2, wall_pixel_y + 2, wall_pixel_x + 24, wall_pixel_y + 24);  // 填充方块
				rectangle(wall_pixel_x + 2, wall_pixel_y + 2, wall_pixel_x + 24, wall_pixel_y + 24);      // 边框
			}
		}
	}

	// 根据皮肤显示蛇头蛇身
	if (_skin == 0) // 默认红头绿身
	{
		// 显示蛇头 - 红色方块
		setfillcolor(RED);
		setlinecolor(BLACK);
		int head_pixel_x = 150 + snake[0][0] * 26;  // 蛇头像素x坐标
		int head_pixel_y = 40 + snake[0][1] * 26;   // 蛇头像素y坐标
		fillrectangle(head_pixel_x + 2, head_pixel_y + 2, head_pixel_x + 24, head_pixel_y + 24);  // 填充方块
		rectangle(head_pixel_x + 2, head_pixel_y + 2, head_pixel_x + 24, head_pixel_y + 24);      // 边框

		// 显示蛇身 - 绿色方块
		setfillcolor(GREEN);
		setlinecolor(BLACK);
		for (int i = 1; i < snakeLength; i++)
		{
			int body_pixel_x = 150 + snake[i][0] * 26;  // 蛇身像素x坐标
			int body_pixel_y = 40 + snake[i][1] * 26;   // 蛇身像素y坐标
			fillrectangle(body_pixel_x + 2, body_pixel_y + 2, body_pixel_x + 24, body_pixel_y + 24);
			rectangle(body_pixel_x + 2, body_pixel_y + 2, body_pixel_x + 24, body_pixel_y + 24);
		}
	}
	else if (_skin == 1) // 蜜蜂皮肤
	{
		// 显示蛇头 
		IMAGE head1;
		loadimage(&head1, _T("./项目细节/res/蜜蜂头.png", 26, 26));
		int head_pixel_x = 150 + snake[0][0] * 26;  // 蛇头像素x坐标
		int head_pixel_y = 40 + snake[0][1] * 26;   // 蛇头像素y坐标
		putimage(head_pixel_x, head_pixel_y, &head1);

		// 显示蛇身 
		IMAGE body1;
		loadimage(&body1, _T("./项目细节/res/蜜蜂身体.png", 26, 26));
		for (int i = 1; i < snakeLength; i++)
		{
			int body_pixel_x = 150 + snake[i][0] * 26;  // 蛇身像素x坐标
			int body_pixel_y = 40 + snake[i][1] * 26;   // 蛇身像素y坐标
			putimage(body_pixel_x, body_pixel_y, &body1);
		}
	}
	else if (_skin == 2) // 鱼皮肤
	{
		// 显示蛇头
		IMAGE head2;
		loadimage(&head2, _T("./项目细节/res/鱼头.png", 26, 26));
		int head_pixel_x = 150 + snake[0][0] * 26;  // 蛇头像素x坐标
		int head_pixel_y = 40 + snake[0][1] * 26;   // 蛇头像素y坐标
		putimage(head_pixel_x, head_pixel_y, &head2);

		// 显示蛇身
		IMAGE body2;
		loadimage(&body2, _T("./项目细节/res/鱼身体.png", 26, 26));
		for (int i = 1; i < snakeLength; i++)
		{
			int body_pixel_x = 150 + snake[i][0] * 26;  // 蛇身像素x坐标
			int body_pixel_y = 40 + snake[i][1] * 26;   // 蛇身像素y坐标
			putimage(body_pixel_x, body_pixel_y, &body2);
		}
	}

	// 显示食物 - 黄色圆圈
	setfillcolor(YELLOW);
	setlinecolor(YELLOW);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (_map0[i][j] == 2) {  // 地图上的食物标记
				int food_x = 150 + j * 26;  // 食物像素x坐标
				int food_y = 40 + i * 26;   // 食物像素y坐标
				fillcircle(food_x + 13, food_y + 13, 8);  // 填充圆
				circle(food_x + 13, food_y + 13, 8);      // 边框
			}
		}
	}

	// 刷新画面
	FlushBatchDraw();
}



void  _shopView() // 记得改一下背景图的素材名字为shop.png
{
	setbkcolor(WHITE);  // 窗口背景色
	cleardevice();      // 刷新窗口

	// 背景图
	IMAGE shop;
	loadimage(&shop, _T("./项目细节/shop.png"), 800, 600);
	putimage(0, 0, &shop);

	// 右上角显示金币数
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(660, 70, _T("金币数"));

	// 加速药
	IMAGE addSpeed;
	loadimage(&addSpeed, _T("./项目细节/res/红药水.png"), 70, 90);
	putimage(75, 160, &addSpeed);

	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(75, 250, _T("加速药"));
	outtextxy(50, 280, _T("拥有数："));


	// 减速药
	IMAGE minusSpeed;
	loadimage(&minusSpeed, _T("./项目细节/res/蓝药水.png"), 80, 90);
	putimage(215, 160, &minusSpeed);

	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(215, 250, _T("减速药"));
	outtextxy(195, 280, _T("拥有数："));

	// 无敌药
	IMAGE penetrate;
	loadimage(&penetrate, _T("./项目细节/res/紫药水.png"), 90, 90);
	putimage(360, 160, &penetrate);

	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(360, 250, _T("无敌药"));
	outtextxy(340, 280, _T("拥有数："));

	// 皮肤1
	IMAGE head1;
	loadimage(&head1, _T("./项目细节/res/蜜蜂头.png"), 90, 90);
	putimage(500, 160, &head1);

	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(490, 250, _T("小蜜蜂皮肤"));
	outtextxy(480, 280, _T("是否拥有："));

	// 皮肤2
	IMAGE head2;
	loadimage(&head2, _T("./项目细节/res/鱼头.png"), 90, 90);
	putimage(640, 160, &head2);

	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(630, 250, _T("粉色鱼皮肤"));
	outtextxy(620, 280, _T("是否拥有："));

	_getch();
}

