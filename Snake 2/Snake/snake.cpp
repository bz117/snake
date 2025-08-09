#include<graphics.h>
#include<iostream>
#include<conio.h>

//---------------------------------�������---------------------------------



/*
	Ĭ�ϵ�ͼ��Ϣ��20*20��
	map0[i][j]��ʾ��ͼ��(i,j)��������ݣ�
		0��ʾ�յ� 
		1��ʾǽ 
		2��ʾʳ�� 
		3��ʾ�ϰ���
*/
int map0[20][20];


/*
		������Ϣ:
		snake[i][0]��ʾ��i�������x������
		snake[i][1]��ʾ��i�������y������
		��0��Ϊ��ͷ
		�ߵĳ�ʼ����Ϊ3
		��ʼ���ӵ�ͼ���Ϸ��հ״����������ƶ�
*/
int snake[20 * 20][2];


//�ߵĵ�ǰ����  ��ʼ��Ϊ3 ÿ�Ե�ʳ��+1
int snakeLength;


/*��ͷ��ǰ���ƶ�����
	w =  ��
	a =  ��
	s =  ��
	d =	 ��
��ʼ������Ϊ���������� (d)
*/
char direction;


//�ܵ÷�:�ۼ�������Ϸ�ĵ÷�--��չ
int totalScore = 0;


//ÿ����Ϸ��ǰ�ĵ÷֣���ʼ��Ϊ0����ʳ��+10
int currentScore;


//�ƶ�ʱ�䣬��λ(ms)��Ĭ��Ϊ1000ms--��չ
int moveInterval;



//---------------------------------�������---------------------------------



//---------------------------------Service��---------------------------------


/*
	initGame:
		�����ˣ�danking
		���ܣ�
			��ʼ���������ݣ�map0��snake���飬snakeLength��direction��current��moveInterval
			��ʼ����ͼ���ߵ�λ�á�����������Ȼ�����Ϣ
		������		void;
		����ֵ��	void;
*/
void initGame();


/*
	moveSnake:
		�����ˣ�ʥ��ս
		���ܣ�
			���ص�ǰ�����ƶ�һ��
			ʵ�ַ�ʽ���޸�snake���飬��β��ͷ��ÿһ�������Ƶ�ǰһ�ڵ�λ�ã��ٸ��ݷ��� direction �ƶ���ͷ
		������		void;		
		����ֵ��	void;
*/
void moveSnake();


/*
	checkCollision��
		�����ˣ����
		���ܣ�
			�ж���ͷ�Ƿ�������ǽ���ϰ���ʳ�﷢����ײ
			����snake�������ж��Ƿ�ײ������
			����map0�������ж��Ƿ�ײ��ǽ���ϰ���ʳ��

			û��ײ�ϣ�����				0
			ײ������ǽ���ϰ�������	1
			ײ��ʳ��,����				2	
			
		������		void;
		����ֵ��	
			0	û��ײ��; 
			1	ײ������ǽ���ϰ�; 
			2	ײ��ʳ��;
*/
int checkCollision();


/*
	checkInput:
		�����ˣ�С��
		���ܣ�
			����û����룬ʹ�� _kbhit ����Ƿ��м������룻
			��û�����룬�򲻽��в���
			�����뷽��Ϸ����������򣩣����޸� direction��
			������ո������ pauseView() ��ͣ��Ϸ��

				 _kbhit(); 
					��������: �ж��û��Ƿ�������(�������Ƿ���ֵ)
					����ֵ:
						0: ��ʾ�û�û������(������û��ֵ)
						��0: ��ʾ�û�����������(��������ֵ)

				������ ͼ��ԺС���������->C,C++���⼼�����  ���˽���غ���������Сѧ��ѯ��

		������		void;
		����ֵ��	void;
*/
void checkInput();


/*
	handleEat��
		�����ˣ�����
		���ܣ�
			�����ʳ���߼����޸�snakeLength��currentScore��map0������ʳ�������
			snake���������Ӳ��޸���Ϣ��
				��ͷ�������ص�ǰ�����ƶ�һ������һ������
				ʵ�ַ�ʽ���޸�snake����,��β��ͷ��ÿһ�������Ƶ�ǰһ�ڵ�λ��,�ٸ��ݷ��� direction �ƶ���ͷ,��ԭ����βλ������һ��
		������		void;
		����ֵ��	void;
*/
void handleEat();


/*
	generateFood��
		�����ˣ���ˮ
		���ܣ�
			�ڵ�ͼ�����һ����λ��(map0[x][y] = 0)����һ��ʳ�map0[i][j] = 2��
			����ʹ��srand()��rand()����
		������		void;
		����ֵ��	void;
*/
void generateFood();



//---------------------------------Service��---------------------------------



//---------------------------------V i e w��---------------------------------



/*
	mainMenuview:
		�����ˣ�С��
		���ܣ�
			չʾ���˵�ѡ���ҿ���ѡ��  ��ʼ��Ϸ���˳���Ϸ(����)
			���ͨ��wsѡ��ѡ�Ĭ��ѡ��Ϊ ��ʼ��Ϸ ��ѡ��ѡ�������
			��Ұ��س�ȷ��ѡ��
			while(1){
				1. չʾѡ��
				2. �û�����
				3. ����������ж�Ӧ����
					��ʼ��Ϸ: ���ó�ʼ����Ϸ���� initGame() ��������Ϸ���Ͻ��溯�� gameLoopView() ;
					�˳���Ϸ: �����˳���Ϸ���溯�� exitView();
			}
		������		void;
		����ֵ��	void;
*/
void mainMenuView();


/*
	renderGameView:
		�����ˣ�С׿
		���ܣ�
			չʾ��ǰ��Ϸ����
			����map0��snake����,currentScore��snakeLength ���Ƶ�ͼ����Ϣ��չʾ��ǰ��Ϸ�Ļ���
		������		void;
		����ֵ��	void;
*/
void renderGameView();


/*
	gameLoopView��
		�����ˣ�ʥ��ս
		���ܣ�
			������Ϸ���棬��Ϸ���߼�ѭ����

			1. �������			���� checkInput()
			2. �ж���ײ			���� checkCollision()
            - ײǽ/����/�ϰ���	���� endView()
            - �Ե�ʳ�		���� handleEat()��generateFood()
            - �����ƶ���		���� moveSnake()
			3. ��Ⱦ����			���� renderGameView()
			4. ��ʱ				Sleep(moveInterval);

		������		void;
		����ֵ��	void;
*/
void gameLoopView();


/*
	exitView:
		�����ˣ�С��
		���ܣ�
			չʾ����ȷ���Ƿ��˳���Ϸ����ʾ���ո��˳������س��������˵�
			while(1){
				1. չʾ����
				2. �û�����
				3. ����������ж�Ӧ����
					�˳���Ϸ: ���� exit(0);
					�������˵����������˵����溯�� mainMenuView();
			}
		������		void;
		����ֵ��	void;
*/
void exitView();


/*
	pauseView��
		�����ˣ�����
		���ܣ�
			չʾ����Ϸ��ͣ��������Ŀǰ������չʾ  ������Ϸ�����ز˵� ��ť
			���ͨ��wsѡ��ѡ�Ĭ��ѡ��Ϊ ������Ϸ ��ѡ��ѡ���������Ұ��ո�ȷ��ѡ��
			while(1){
				1. չʾ����
				2. �û�����
				3. ����������ж�Ӧ����
					������Ϸ: ����ʼ����������Ϸ���溯�� gameLoopView();
					���ز˵����������˵����溯�� mainMenuView();
			}
		������		void;
		����ֵ��	void;
*/
void pauseView();


/*
	endView:
		�����ˣ�����
		���ܣ�
			չʾ����Ϸ���������������շ�����չʾ���س��������˵�
			while(1){
				1. չʾ����
				2. �û�����
				3. ����������ж�Ӧ����
					���ز˵����������˵����溯��  mainMenuView();
			}
		������		void;
		����ֵ��	void;
*/
void endView();



//---------------------------------V i e w ��---------------------------------


using namespace std;
int main()
{
	snakeLength = 3;				//����moveSnake()/gameLoopView()
	moveInterval = 1000;
	for (int i = 0; i < 20; i++)
	{
		snake[i][0] = 9;
		snake[i][1] = 10;
	}
	for (int i = 0; i < snakeLength; i++)
	{
		snake[i][0] = 3 - i;
		snake[i][1] = 1;
	}
	direction = 'd';
	moveSnake();
	gameLoopView();
	return 0;
}

void initGame() {
	//��ʼ����ͼ����
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			map0[i][j] = 0;
		}
	};
	//��ʼ��Χǽ����
	for (int i = 0; i < 20; i++) {
		map0[0][i] = 1;          // �ϱ߽�
		map0[19][i] = 1;         // �±߽�
		map0[i][0] = 1;          // ��߽�
		map0[i][19] = 1;         // �ұ߽�
	}
	// �߳�ʼλ����Ϊ���Ϸ��հ�����
	snake[0][0] = 3;  // ��ͷx���꣨ˮƽ����
	snake[0][1] = 1;  // ��ͷy���꣨��ֱ����
	snake[1][0] = 2;  // ��һ������x����
	snake[1][1] = 1;  // ��һ������y����
	snake[2][0] = 1;  // �ڶ�������x����
	snake[2][1] = 1;  // �ڶ�������y����
	//��ʼ���ߵĳ���
	snakeLength = 3;
	// ��ʼ������
	direction = 'd';
	//ÿ����Ϸ��ǰ�ĵ÷֣���ʼ��Ϊ0����ʳ��+10
	currentScore = 0;
	//�ƶ�ʱ�䣬��λ(ms)��Ĭ��Ϊ1000ms--��չ
	moveInterval = 1000;

}

void moveSnake() {
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}
	switch (direction)
	{
		case 'w':
			snake[0][1] = snake[0][1] - 1;
			break;
		case 'a':
			snake[0][0] = snake[0][0] - 1;
			break;
		case 's':
			snake[0][1] = snake[0][1] + 1;
			break;
		case 'd':
			snake[0][0] = snake[0][0] + 1;
			break;
	}

	for (int i = 0; i <= snakeLength; i++)	//����moveSnake()/gameLoopView()
	{
		cout << "�ߵĵ�" << i << "������";
		cout << "x����Ϊ: " << snake[i][0];
		cout << " , y����Ϊ: " << snake[i][1] << endl;
	}
}

int checkCollision() {
	//int rk = 0;								//����gameLoopView()
	//cout << "����ֵ:\n0 û��ײ��\n";
	//cout << "1 ײ������ǽ���ϰ�\n2 ײ��ʳ��\n";
	//cout << "�����뷵��ֵ(0/1/2):";
	//cin >> rk;
	//if (rk > 2||rk < 0)
	//{
	//	rk = 0;
	//}
	//return rk;

	int next_x = snake[0][0];
	int next_y = snake[0][1];
	int result = 1;
	switch (direction) {					//��ͷ�ص�ǰ��������һ�������
	case'w':
		next_y -= 1;
	case's':
		next_y += 1;
	case'a':
		next_x -= 1;
	case'd':
		next_x += 1;
	}
	for (int i = 0; i < 20 * 20; i++) {		//�ж���������ͷ�Ƿ�����ײ
		if (snake[i][0] == next_x && snake[i][1] == next_y)
			result = 1;
	}
	if (map0[next_y][next_x] == 1)			//�ж���ͷ�ڵ�ͼ�е�����������
		result = 1;
	if (map0[next_y][next_x] == 0)
		result = 0;
	if (map0[next_y][next_x] == 2)
		result =  2;
	return result;
}

void checkInput() {
	//cout << "checkInput works!\n";			//����gameLoopView()


	if (!_kbhit())          // ������ֱ�ӷ���
		return;
	else
	{
		int ch = _getch();      // ��ȡ�����������ԣ�

			switch (ch)
			{
			case 'w':   // ��
				if (direction != 's') direction = 'w';
				break;
			case 'a':   // ��
				if (direction != 'd') direction = 'a';
				break;
			case 's':   // ��
				if (direction != 'w') direction = 's';
				break;
			case 'd':   // ��
				if (direction != 'a') direction = 'd';
				break;
			case ' ':   // �ո� -> ��ͣ
				pauseView();
				break;
			default:
				break;
			}
	}
	
}

void handleEat() {
	//cout << "handleEat works!\n";			//����gameLoopView()

	int hx = snake[0][0];
	int hy = snake[0][1];
	
		for (int i = snakeLength; i > 0; --i) {
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
		}
		++snakeLength;
		currentScore += 10;
		map0[hy][hx] = 0;
}

void generateFood() {
	//cout << "generateFood works!\n";		//����gameLoopView()

	srand((unsigned int)time(NULL));
	int n = 0;
	while (1) {
		int x1 = rand() % 20;
		int y1 = rand() % 20;
		if (map0[x1][y1] == 0 && n == 0) 
		{
			for (int i = 0; i < snakeLength; i++)
			{
				if (snake[i][0] = y1 && snake[i][1] == x1)
				{
					continue;
				}
			}
			map0[x1][y1] = 2;
			n++;
		}
		else	if (n >= 1) {
			break;
		}
		else {
			continue;
		}
	}
}

void mainMenuView();

void renderGameView() {
	cout << "renderGameView works!\n";		//����gameLoopView()
}

void gameLoopView() {
	while (1)
	{
		checkInput();
		switch (checkCollision()) {
			case 0:
				moveSnake();
				break;
			case 1:
				endView();
				break;
			case 2:
				handleEat();
				generateFood();
				break;
		}
		renderGameView();
		Sleep(moveInterval);
	}
}

void exitView() {
	while (1) {
		std::cout << "�Ƿ��˳���Ϸ?(�ո��˳�,�س����ز˵�)\n";//չʾѡ��
		int choice = _getch();//�����û����뵥���ַ�,_getch()������conio.h��
		if (choice == 32)//�ո��ASCII��Ϊ32
			exit(0);//���ո��˳�����
		else if (choice == 13)//�س���ASCII��Ϊ13
			mainMenuView();//���س��������˵�
		else
			continue;//�����������ַ�����ѯ��
	}
}

void pauseView();

void endView() {
	//cout << "endView works!\n";				//����gameLoopView()
	//cout << "���������������!\n";
	//_getch();
	//exit(0);

	setbkcolor(GREEN);
	cleardevice();
	settextstyle(40, 0, L"����");
	settextcolor(BLACK);

	while (true)
	{
		/* չʾ���� */
		cleardevice();
		outtextxy(400 - textwidth(L"��Ϸ����") / 2, 220, L"��Ϸ����");

		wchar_t buf[32];
		swprintf_s(buf, L"�������շ�����%d", currentScore);
		outtextxy(400 - textwidth(buf) / 2, 280, buf);

		settextstyle(20, 0, L"����");
		outtextxy(400 - textwidth(L"���س��������˵�") / 2, 400, L"���س��������˵�");

		/* �ȴ��س� */
		if (_getch() == 13)        // �س���
		{
			closegraph();
			mainMenuView();
			return;
		}
	}
}