#include<graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

void renderGameView() {
	initgraph(800, 600); //���ڴ�С
	setbkcolor(WHITE); //���ڱ���ɫ
	cleardevice(); //ˢ�´���
	IMAGE map;
	loadimage(&map, _T("map.png"), 520, 520); //�����ͼͼƬ��������С���޸ĳ�ɫ��ͼƬ��ַ����
	putimage(150, 40, &map); //��ʾͼƬ

	//������ʾ��ʱ�䡢���ȡ�����
	settextstyle(40, 0, _T("Consolas")); //��������Ϊ��40���صġ�Consolas��
	settextcolor(BLACK); //������ɫ
	setbkmode(TRANSPARENT); //���ֱ���ɫ͸��
	outtextxy(75, 0, _T("time"));
	outtextxy(345, 0, _T("length"));
	outtextxy(645, 0, _T("score"));

	//�ײ���ʾ����Ϸ������ʾ
	settextstyle(40, 0, _T("Consolas")); //��������Ϊ��40���صġ�Consolas��
	settextcolor(BLACK); //������ɫ
	outtextxy(155, 560, _T("wasd�޸ķ��򣬿ո���ͣ��Ϸ"));

	//��ʾ��ͷ
	IMAGE head;
	loadimage(&head, _T("head.png"), 26, 26); //����ͼƬ��������С���޸ĳ�ɫ��ͼƬ��ַ����
	putimage(snake[0][0], snake[0][1], &head); //��ʾͼƬ

	//��ʾ����
	IMAGE body;
	loadimage(&body, _T("body.png"), 26, 26); //����ͼƬ��������С���޸ĳ�ɫ��ͼƬ��ַ����
	for (int i = 1; i < snakeLength; i++)
	{
		putimage(snake[i][0], snake[i][1], &body); //��ʾͼƬ
	}

	cout << "renderGameView works!\n";		//����gameLoopView()
}




