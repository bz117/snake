#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>

using namespace std;


// Ƥ��
int _skin = 0;


void _renderGameView(int _mode = 0) {
	setbkcolor(WHITE);  // ���ڱ���ɫ
	cleardevice();      // ˢ�´���

	// ������Ϸ����߿�20x20����ÿ��26���أ�
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(150, 40, 150 + 20 * 26, 40 + 20 * 26);  // ��Ϸ����߿�520x520����

	// ����ģʽչʾ��ͬ�ĵ�ͼ
	if (_mode == 1)
	{
		IMAGE map1;
		loadimage(&map1, _T("map.png"));
		putimage(150, 40, &map1);
	}
	else if (_mode == 2)
	{
		IMAGE map2;
		loadimage(&map2, _T("./��Ŀϸ��/res/����.png"));
		putimage(150, 40, &map2);
	}
	else if (_mode == 3)
	{
		IMAGE map3;
		loadimage(&map3, _T("./��Ŀϸ��/res/�۷��ͼ.png"));
		putimage(150, 40, &map3);
	}
	else if (_mode == 4)
	{
		IMAGE map4;
		loadimage(&map4, _T("./��Ŀϸ��/res/�ҽ���ͼ.png"));
		putimage(150, 40, &map4);
	}


	// ����������
	setlinecolor(LIGHTGRAY);
	setlinestyle(PS_SOLID, 1);
	for (int i = 1; i < 20; i++) {
		// ��ֱ��
		line(150 + i * 26, 40, 150 + i * 26, 40 + 20 * 26);
		// ˮƽ��
		line(150, 40 + i * 26, 150 + 20 * 26, 40 + i * 26);
	}

	// ������ʾ�����ȡ�����
	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(75, 5, _T("ʱ��"));    // Ԥ��ʱ����ʾλ��
	outtextxy(300, 5, _T("����"));
	outtextxy(500, 5, _T("����"));

	// ��ʾʵ����ֵ�����Ⱥͷ�����
	char lengthStr[20], scoreStr[20];
	sprintf_s(lengthStr, "%d", snakeLength);
	sprintf_s(scoreStr, "%d", currentScore);

	outtextxy(350, 5, lengthStr);  // ��ʾ����
	outtextxy(550, 5, scoreStr);   // ��ʾ����

	// �ײ���ʾ����Ϸ������ʾ
	settextstyle(20, 0, _T("΢���ź�"));
	outtextxy(250, 580, _T("WASD���Ʒ��򣬿ո���ͣ��Ϸ"));

	// ��ʾǽ�� - ��ɫ����
	setfillcolor(BROWN);
	setlinecolor(BLACK);
	int wall_pixel_x = 150;  // ǽ������x����
	int wall_pixel_y = 40;   // ǽ������y����
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (_map0[i][j] == 1)
			{
				wall_pixel_x = 150 + j * 26;
				wall_pixel_y = 40 + i * 26;
				fillrectangle(wall_pixel_x + 2, wall_pixel_y + 2, wall_pixel_x + 24, wall_pixel_y + 24);  // ��䷽��
				rectangle(wall_pixel_x + 2, wall_pixel_y + 2, wall_pixel_x + 24, wall_pixel_y + 24);      // �߿�
			}
		}
	}

	// ����Ƥ����ʾ��ͷ����
	if (_skin == 0) // Ĭ�Ϻ�ͷ����
	{
		// ��ʾ��ͷ - ��ɫ����
		setfillcolor(RED);
		setlinecolor(BLACK);
		int head_pixel_x = 150 + snake[0][0] * 26;  // ��ͷ����x����
		int head_pixel_y = 40 + snake[0][1] * 26;   // ��ͷ����y����
		fillrectangle(head_pixel_x + 2, head_pixel_y + 2, head_pixel_x + 24, head_pixel_y + 24);  // ��䷽��
		rectangle(head_pixel_x + 2, head_pixel_y + 2, head_pixel_x + 24, head_pixel_y + 24);      // �߿�

		// ��ʾ���� - ��ɫ����
		setfillcolor(GREEN);
		setlinecolor(BLACK);
		for (int i = 1; i < snakeLength; i++)
		{
			int body_pixel_x = 150 + snake[i][0] * 26;  // ��������x����
			int body_pixel_y = 40 + snake[i][1] * 26;   // ��������y����
			fillrectangle(body_pixel_x + 2, body_pixel_y + 2, body_pixel_x + 24, body_pixel_y + 24);
			rectangle(body_pixel_x + 2, body_pixel_y + 2, body_pixel_x + 24, body_pixel_y + 24);
		}
	}
	else if (_skin == 1) // �۷�Ƥ��
	{
		// ��ʾ��ͷ 
		IMAGE head1;
		loadimage(&head1, _T("./��Ŀϸ��/res/�۷�ͷ.png", 26, 26));
		int head_pixel_x = 150 + snake[0][0] * 26;  // ��ͷ����x����
		int head_pixel_y = 40 + snake[0][1] * 26;   // ��ͷ����y����
		putimage(head_pixel_x, head_pixel_y, &head1);

		// ��ʾ���� 
		IMAGE body1;
		loadimage(&body1, _T("./��Ŀϸ��/res/�۷�����.png", 26, 26));
		for (int i = 1; i < snakeLength; i++)
		{
			int body_pixel_x = 150 + snake[i][0] * 26;  // ��������x����
			int body_pixel_y = 40 + snake[i][1] * 26;   // ��������y����
			putimage(body_pixel_x, body_pixel_y, &body1);
		}
	}
	else if (_skin == 2) // ��Ƥ��
	{
		// ��ʾ��ͷ
		IMAGE head2;
		loadimage(&head2, _T("./��Ŀϸ��/res/��ͷ.png", 26, 26));
		int head_pixel_x = 150 + snake[0][0] * 26;  // ��ͷ����x����
		int head_pixel_y = 40 + snake[0][1] * 26;   // ��ͷ����y����
		putimage(head_pixel_x, head_pixel_y, &head2);

		// ��ʾ����
		IMAGE body2;
		loadimage(&body2, _T("./��Ŀϸ��/res/������.png", 26, 26));
		for (int i = 1; i < snakeLength; i++)
		{
			int body_pixel_x = 150 + snake[i][0] * 26;  // ��������x����
			int body_pixel_y = 40 + snake[i][1] * 26;   // ��������y����
			putimage(body_pixel_x, body_pixel_y, &body2);
		}
	}

	// ��ʾʳ�� - ��ɫԲȦ
	setfillcolor(YELLOW);
	setlinecolor(YELLOW);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (_map0[i][j] == 2) {  // ��ͼ�ϵ�ʳ����
				int food_x = 150 + j * 26;  // ʳ������x����
				int food_y = 40 + i * 26;   // ʳ������y����
				fillcircle(food_x + 13, food_y + 13, 8);  // ���Բ
				circle(food_x + 13, food_y + 13, 8);      // �߿�
			}
		}
	}

	// ˢ�»���
	FlushBatchDraw();
}



void  _shopView() // �ǵø�һ�±���ͼ���ز�����Ϊshop.png
{
	setbkcolor(WHITE);  // ���ڱ���ɫ
	cleardevice();      // ˢ�´���

	// ����ͼ
	IMAGE shop;
	loadimage(&shop, _T("./��Ŀϸ��/shop.png"), 800, 600);
	putimage(0, 0, &shop);

	// ���Ͻ���ʾ�����
	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(660, 70, _T("�����"));

	// ����ҩ
	IMAGE addSpeed;
	loadimage(&addSpeed, _T("./��Ŀϸ��/res/��ҩˮ.png"), 70, 90);
	putimage(75, 160, &addSpeed);

	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(75, 250, _T("����ҩ"));
	outtextxy(50, 280, _T("ӵ������"));


	// ����ҩ
	IMAGE minusSpeed;
	loadimage(&minusSpeed, _T("./��Ŀϸ��/res/��ҩˮ.png"), 80, 90);
	putimage(215, 160, &minusSpeed);

	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(215, 250, _T("����ҩ"));
	outtextxy(195, 280, _T("ӵ������"));

	// �޵�ҩ
	IMAGE penetrate;
	loadimage(&penetrate, _T("./��Ŀϸ��/res/��ҩˮ.png"), 90, 90);
	putimage(360, 160, &penetrate);

	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(360, 250, _T("�޵�ҩ"));
	outtextxy(340, 280, _T("ӵ������"));

	// Ƥ��1
	IMAGE head1;
	loadimage(&head1, _T("./��Ŀϸ��/res/�۷�ͷ.png"), 90, 90);
	putimage(500, 160, &head1);

	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(490, 250, _T("С�۷�Ƥ��"));
	outtextxy(480, 280, _T("�Ƿ�ӵ�У�"));

	// Ƥ��2
	IMAGE head2;
	loadimage(&head2, _T("./��Ŀϸ��/res/��ͷ.png"), 90, 90);
	putimage(640, 160, &head2);

	settextstyle(30, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	outtextxy(630, 250, _T("��ɫ��Ƥ��"));
	outtextxy(620, 280, _T("�Ƿ�ӵ�У�"));

	_getch();
}

