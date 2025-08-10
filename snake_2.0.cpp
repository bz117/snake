#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>

using namespace std;


//���ܹ����ڻ����ܹ��Ļ������޸ĵģ�
// �����ܹ�����غ������������޸ĵģ������ĺ���������
// ��������ǰ������  �� _ ��


//---------------------------------�������---------------------------------



/*
	Ĭ�ϵ�ͼ��Ϣ��20*20��
	map0[i][j]��ʾ��ͼ��(i,j)��������ݣ�
		0��ʾ�յ� 
		1��ʾǽ 
		2��ʾʳ�� 
		3��ʾ�ϰ���

		��չ:
			2��ʾ��ͨʳ��

			21��ʾ����ʳ��
			22��ʾ����ʳ��
			23��ʾ��͸ʳ��
*/
int _map0[20][20];


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


//�ܵ÷�:�ۼ�������Ϸ�ĵ÷�						--��չ
int totalScore = 0;


//ÿ����Ϸ��ǰ�ĵ÷֣���ʼ��Ϊ0����ʳ��+10
int currentScore;


//�ƶ��������λ(ms)Ĭ��200						--��չ
int _moveInterval;


//��������.��ʼ��Ϊ0							--��չ
//���١����١���͸
int _addSpeedProp, _minusSpeedProp, _penetrateProp;


/*//ѡ���ģʽ									--��չ

	����ģʽ		0
	��ʱģʽ		1
	ʳ�����ģʽ	2
	��սģʽ		3
	�Կ�ģʽ		4
*/
int _mode;


/*//��ʷ��߷���								--��չ
	����ģʽ		0
	��ʱģʽ		1
	ʳ�����ģʽ	2
	��սģʽ		3
	�Կ�ģʽ		4
//��ͨģʽ��ʳ�����ģʽ����սģʽ���Կ�ģʽ����ʷ��߷���,
//��ʱģʽ�����ͨ��ʱ��						--��չ
*/
int _charts[5];


/*
		�˻���									--��չ
		������Ϣ:
		snake[i][0]��ʾ��i�������x������
		snake[i][1]��ʾ��i�������y������
		��0��Ϊ��ͷ
		�ߵĳ�ʼ����Ϊ3
		��ʼ���ӵ�ͼ���·��հ״����������ƶ�
*/
int _AIsnake[20 * 20][2];


/*
	��ʱ������λ(ms)							--��չ
	��ʱģʽ�ĵ���ʱ
*/
int _timedate;


//����״̬
struct snake_state
{
	bool _addSpeedProp, _minusSpeedProp, _penetrateProp;
};



//---------------------------------�������---------------------------------



//---------------------------------Service��---------------------------------


/*
	initGame:
		�����ˣ�danking
		���ܣ�
			��ʼ���������ݣ�map0��snake���飬snakeLength��direction��current��moveInterval
			��ʼ����ͼ���ߵ�λ�á�����������Ȼ�����Ϣ

		��չ����:
			��ʼ������ģʽ�������Ϣ

		������		void;
		����ֵ��	void;
*/
void _initGame();


/*
	moveSnake:
		�����ˣ�
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
			�ж���ͷ�Ƿ��Ƿ�������ǽ���ϰ���ʳ�﷢����ײ
			����snake�������ж��Ƿ�ײ������
			����map0�������ж��Ƿ�ײ��ǽ���ϰ���ʳ��

			û��ײ�ϣ�����				0
			ײ������ǽ���ϰ�������	1
			ײ��ʳ��,����				2	

		��չ����:�����ߵ�״̬�����ж�
			
		������		void;
		����ֵ��	
			0	û��ײ��; 
			1	ײ������ǽ���ϰ�; 
			2	ײ��ʳ��;
*/
int _checkCollision();


/*
	checkInput:
		�����ˣ�
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
			�����ʳ���߼����޸�snakeLength��current��map0������ʳ�������
			snake���������Ӳ��޸���Ϣ��
				��ͷ�������ص�ǰ�����ƶ�һ������һ������
				ʵ�ַ�ʽ���޸�snake����,��β��ͷ��ÿһ�������Ƶ�ǰһ�ڵ�λ��,�ٸ��ݷ��� direction �ƶ���ͷ,��ԭ����βλ������һ��

		��չ����:
			�ж�������ʳ�������ӦЧ�����޸�����ߵ�����

		������		void;
		����ֵ��	void;
*/
void _handleEat();


/*
	generateFood��
		�����ˣ���ˮ
		���ܣ�
			�ڵ�ͼ�����һ����λ��(map0[x][y] = 0)����һ��ʳ�map0[i][j] = 2��
			����ʹ��srand()��rand()����

		��չ����:
			����ģʽ�������������ʳ��
		������		void;
		����ֵ��	void;
*/
void _generateFood();


/*
	shopView:
		������:С׿
		��չ����:
			"��������չʾ""�����̵�""�ͽ������
			�м�չʾ���пɹ���ĵ��ߺ�ÿ�����ߵ�ӵ������
			������ʾ���س��ص����˵�"

			���ݵ�������Ҫ�Ľ�������۳���Ҳ����ӵ��ߵ�����������Ҳ�������ʾ����Ҳ��㡱
			���ߣ����١����١���͸������ͼ
		����:		void;
		����ֵ:		void;
*/
void  _shopView();


/*
	propUseView:
		������:С��
		��չ����:
			"���Ϸ�չʾ��������Ϸ����ť��
			�·�չʾ�����ӵ�е����е��ߣ�ÿ�����߶��С�ʹ�á���ť"	
			���ֵ��ߣ����١����١���͸
			���ݵ���Ч���޸��������
		����:		void;
		����ֵ:		void;
*/
void  _propUseView();


/*
	generateObstacle��
		�����ˣ�danking
		��չ���ܣ�
			�ڵ�ͼ�����һ����λ��(map0[x][y] = 0)����һ���ϰ��map0[i][j] = 3��
			����ʹ��srand()��rand()����
		������		void;
		����ֵ��	void;
*/
void _generateObstacle();


/*
	modeView:
		������:���
		��չ����:
			չʾ���������ģʽ����ʱģʽ��ʳ�����ģʽ����սģʽ���Կ�ģʽ
			��Ұ���wsʱ�����������ƶ������¿ո�ȷ������ģʽ��ֱ�ӽ������ģʽ��Ӧ����Ϸ����
			�޸� mode
			����ģʽ			0��
			��ʱģʽ			1��
			ʳ�����ģʽ		2��
			��սģʽ			3��
			�Կ�ģʽ			4
		����:		void;
		����ֵ:		void;
*/
void _modeView();


/*
	AIwork��
		�����ˣ�С��
		��չ���ܣ�
			�˻�������߼�:
				�˻��߳�ʼ�����˻����ƶ�����ʳ�����
				�������˻���
		������		void;
		����ֵ��	void;
*/
void _AIwork();


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

		��չ����:
			�޸�totalScore,�ѱ��ַ�������
		������		void;
		����ֵ��	void;
*/
void _endView();



//---------------------------------Service��---------------------------------



//---------------------------------V i e w ��---------------------------------



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

			��չ����:
				չʾ�Ŷӽ��ܡ��淨˵������Ϸ���á����а�
		������		void;
		����ֵ��	void;
*/
void _mainMenuView();


/*
	renderGameView:
		�����ˣ�С׿
		���ܣ�
			չʾ��ǰ��Ϸ����
			����map0��snake����,currentScore��snakeLength ���Ƶ�ͼ����Ϣ��չʾ��ǰ��Ϸ�Ļ���

		��չ����:
			����mode��չʾ��ͬ����Ϸģʽ�ĵ�ǰ����
		������		void;
		����ֵ��	void;
*/
void _renderGameView();


/*
	gameLoopView��
		�����ˣ�����
		���ܣ�
			������Ϸ���棬��Ϸ���߼�ѭ����

			1. �������			���� checkInput()
			2. �ж���ײ			���� checkCollision()
            - ײǽ/����/�ϰ���	���� endView()
            - �Ե�ʳ�		���� handleEat()��generateFood()
            - �����ƶ���		���� moveSnake()
			3. ��Ⱦ����			���� renderGameView()
			4. ��ʱ				
				static int waitIndex = 1; // ��̬�ֲ���������ʼ��ʱΪ1
				waitIndex++; // ÿһ֡+1
				if (waitIndex==10) // �������10��ִ�У�����С��ÿ��10֡�ƶ�һ��
				{
					moveSnake(); //  ����С���ƶ�����
					waitIndex = 1; // �ٱ��1
				}

			��չ����:
				���ݲ�ͬ��ģʽ������ͬ����Ϸ���߼�
		������		void;
		����ֵ��	void;
*/
void _gameLoopView();


/*
	exitView:
		�����ˣ�
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

		��չ����:
			����չʾ ģʽѡ��İ�ť
		������		void;
		����ֵ��	void;
*/
void _pauseView();


/*
	instructionView:
		������:����
		��չ����:
			չʾ��ģʽ���淨˵��,��ʾ���س��ص����˵�
			չʾ���ߵĹ���
			while(1){
				1. չʾ����
				2. �û�����
				3. ����������ж�Ӧ����
					�������س�
					���ز˵����������˵����溯��  mainMenuView();
			}
		����:		void;
		����ֵ:		void;
*/
void _instructionView();


/*	
	introductionView:
		������:С��
		��չ����:
			չʾ�����������Ͷ�Ӧ��������,��ʾ���س��ص����˵�
			�������س�,���ز˵����������˵����溯��  mainMenuView();
		����:		void;
		����ֵ:		void;
*/
void _introductionView();


/*
	settingView:
		������:����
		��չ����:
			չʾ�����޸ĵ�ѡ��:
				��Ч: <��>
				����: <50>
				�·�չʾ������ʾ:
				���س����ص����˵�
				ws�ƶ����, ad�޸ĵ�ǰѡ��
		����:		void;
		����ֵ:		void;
*/
void  _settingView();


/*
	chartsView:
		������:��ˮ
		��չ����:
			"�ֱ�չʾ��ͨģʽ��ʳ�����ģʽ����սģʽ���Կ�ģʽ����ʷ��߷���
			չʾ��ʱģʽ�����ͨ��ʱ��
			�·���ʾ���س��ص����˵�"	
		����:		void;
		����ֵ:		void;
*/
void  _chartsView();



//---------------------------------V i e w ��---------------------------------


int main()
{
	//snakeLength = 3;				//����moveSnake()/gameLoopView()
	//moveInterval = 1000;
	//for (int i = 0; i < 20; i++)
	//{
	//	snake[i][0] = 9;
	//	snake[i][1] = 10;
	//}
	//for (int i = 0; i < snakeLength; i++)
	//{
	//	snake[i][0] = 3 - i;
	//	snake[i][1] = 1;
	//}
	//direction = 'd';
	//moveSnake();
	//gameLoopView();
	//��ʼ��ͼ�δ��ڣ���800����600����ʾ����̨��
	initgraph(800, 600, EX_SHOWCONSOLE);
	//�������˵�
	_mainMenuView();
	return 0;
}

void _initGame() {
	//��ʼ����ͼ���ݣ����и�����Ϊ�յأ�
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			_map0[i][j] = 0;
		}
	};
	//��ʼ��Χǽ���ݣ����ܱ߽���Ϊǽ��
	for (int i = 0; i < 20; i++) {
		_map0[0][i] = 1;          // �ϱ߽�
		_map0[19][i] = 1;         // �±߽�
		_map0[i][0] = 1;          // ��߽�
		_map0[i][19] = 1;         // �ұ߽�
	}
	// �߳�ʼλ����Ϊ��ͼ�м����򣬱������ײǽ
	snake[0][0] = 10;  // ��ͷx���꣨ˮƽ����- ��ͼ�м�
	snake[0][1] = 10;  // ��ͷy���꣨��ֱ����- ��ͼ�м�
	snake[1][0] = 9;   // ��һ������x����
	snake[1][1] = 10;  // ��һ������y����
	snake[2][0] = 8;   // �ڶ�������x����
	snake[2][1] = 10;  // �ڶ�������y����
	//��ʼ���ߵĳ���
	snakeLength = 3;
	// ��ʼ���������ң�
	direction = 'd';
	//��ʼ����ǰ����
	currentScore = 0;
	//��ʼ���ƶ������200ms���������ƶ��ٶȣ�
	_moveInterval = 200;

	// ���ɳ�ʼʳ��
	_generateFood();
}

void moveSnake() {
	//��β����ͷ����ÿ�������ƶ���ǰһ�ڵ�λ��
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}
	//���ݵ�ǰ�����ƶ���ͷ
	switch (direction)
	{
	case 'w':  // ���ƣ�y���1��
		snake[0][1] = snake[0][1] - 1;
		break;
	case 'a':  // ���ƣ�x���1��
		snake[0][0] = snake[0][0] - 1;
		break;
	case 's':  // ���ƣ�y���1��
		snake[0][1] = snake[0][1] + 1;
		break;
	case 'd':  // ���ƣ�x���1��
		snake[0][0] = snake[0][0] + 1;
		break;
	}
	//for (int i = 0; i <= snakeLength; i++)	//����moveSnake()/gameLoopView()
	//{
	//	cout << "�ߵĵ�" << i << "������";
	//	cout << "x����Ϊ: " << snake[i][0];
	//	cout << " , y����Ϊ: " << snake[i][1] << endl;
	//}
}

int _checkCollision() {
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

	//������ͷ��һ������
	int next_x = snake[0][0];
	int next_y = snake[0][1];

	switch (direction) {
	case'w':  // ����
		next_y -= 1;
		break;
	case's':  // ����
		next_y += 1;
		break;
	case'a':  // ����
		next_x -= 1;
		break;
	case'd':  // ����
		next_x += 1;
		break;
	}

	// �߽��� - ������ͼ��Χ��0~19������ײ
	if (next_x < 0 || next_x >= 20 || next_y < 0 || next_y >= 20) {
		return 1;
	}

	// ���������ײ�����ͷ����������غϣ�
	for (int i = 1; i < snakeLength; i++) {
		if (snake[i][0] == next_x && snake[i][1] == next_y)
			return 1;  // ������ײ
	}

	// ����ͼ���ݣ�ǽ/�յ�/ʳ�
	if (_map0[next_y][next_x] == 1)			// ײǽ
		return 1;
	if (_map0[next_y][next_x] == 0)			// �յأ�����ײ��
		return 0;
	if (_map0[next_y][next_x] == 2)			// �Ե�ʳ��
		return 2;

	return 0; // Ĭ������ײ
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
		case 'w':   // �ϣ����Դ�Сд��
		case 'W':
			if (direction != 's') direction = 'w';  // ����ֱ������ת��
			break;
		case 'a':   // �󣨺��Դ�Сд��
		case 'A':
			if (direction != 'd') direction = 'a';  // ����ֱ������ת��
			break;
		case 's':   // �£����Դ�Сд��
		case 'S':
			if (direction != 'w') direction = 's';  // ����ֱ������ת��
			break;
		case 'd':   // �ң����Դ�Сд��
		case 'D':
			if (direction != 'a') direction = 'd';  // ����ֱ������ת��
			break;
		case ' ':   // �ո� -> ��ͣ��Ϸ
			_pauseView();
			break;
		default:    // ������������
			break;
		}
	}
}

void _handleEat() {
	// ������������β����ʼ��ÿ���ƶ���ǰһ��λ�ã�����һ����β����
	for (int i = snakeLength; i > 0; --i) {
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}

	// ���ݷ����ƶ���ͷ��ʳ��λ��
	switch (direction) {
	case 'w':
		snake[0][1] -= 1;
		break;
	case 's':
		snake[0][1] += 1;
		break;
	case 'a':
		snake[0][0] -= 1;
		break;
	case 'd':
		snake[0][0] += 1;
		break;
	}

	// �������ݣ�����+1������+10�����ʳ����
	++snakeLength;
	currentScore += 10;
	_map0[snake[0][1]][snake[0][0]] = 0;  // ԭʳ��λ����Ϊ�յ�
}

void _generateFood() {

	//cout << "generateFood works!\n";		//����gameLoopView()
	srand((unsigned int)time(NULL));  // ��ʼ�����������
	int n = 0;  // ����Ƿ�����ʳ��
	int attempts = 0;  // ���Դ�����������ѭ����
	while (n == 0 && attempts < 1000) {
		int x1 = rand() % 20;  // ���x���꣨0~19��
		int y1 = rand() % 20;  // ���y���꣨0~19��
		// ���λ���Ƿ�Ϊ�յ��Ҳ���������
		if (_map0[y1][x1] == 0)
		{
			bool isOnSnake = false;
			// ����Ƿ��������غ�
			for (int i = 0; i < snakeLength; i++)
			{
				if (snake[i][0] == x1 && snake[i][1] == y1)
				{
					isOnSnake = true;
					break;
				}
			}
			if (!isOnSnake) {  // �Ϸ�λ�ã�����ʳ��
				_map0[y1][x1] = 2;
				n++;  // ���������
			}
		}
		attempts++;  // �ۼƳ��Դ���
	}
	// �������ʧ�ܣ���ͼ��������ʲôҲ����
}

void _mainMenuView()
{
	int cur = 1;  // ��ǰѡ�еİ�ť������1~8��
	BeginBatchDraw();
	//����ͼƬ����
	IMAGE img_mm[4];
	IMAGE img_mn[4];
	IMAGE img_bk;
	setbkmode(TRANSPARENT);

	//����ͼƬ
	int w = 300;   // ����ť���
	int h = w / 4; // ����ť�߶�

	loadimage(&img_bk, "./assets/���˵�.jpg", 800, 600);  // ����ͼ
	loadimage(img_mm, "./assets/��ť.png", w, h);         // ����ť����
	loadimage(img_mm + 1, "./assets/��ťm.png", w, h);    // ����ť��������
	loadimage(img_mm + 2, "./assets/��ť1.png", w, h);    // ����ťѡ��
	loadimage(img_mm + 3, "./assets/��ť1m.png", w, h);   // ����ťѡ������

	loadimage(img_mn, "./assets/��ť.png", w / 2, h / 2);  // ����ť����
	loadimage(img_mn + 1, "./assets/��ťm.png", w / 2, h / 2); // ����ť��������
	loadimage(img_mn + 2, "./assets/��ť1.png", w / 2, h / 2); // ����ťѡ��
	loadimage(img_mn + 3, "./assets/��ť1m.png", w / 2, h / 2); // ����ťѡ������

	// ���˵�ѭ��
	while (1) {
		setbkcolor(WHITE);
		cleardevice();  // ��ջ���

		//���Ʊ���
		putimage(0, 0, &img_bk);

		//���ư�ť�ı�
		string ch[10] = { "���˵�","��ʼ��Ϸ","ģʽѡ��","�����̵�","�˳���Ϸ","�淨˵��","��ʷ��߷�","�Ŷ�˵��","��Ϸ����" };
		settextstyle(60, 0, "΢���ź�");  // ��������
		settextcolor(BLACK);

		// ��������ť����ʼ��Ϸ��ģʽѡ�񡢵����̵ꡢ�˳���Ϸ��
		for (int i = 0; i < 4; i++)
		{
			int px = 250, py = 150 + i * 100;  // ��ťλ��
			if (i + 1 == cur)  // ѡ��״̬
			{
				putimage(px, py, img_mm + 3, NOTSRCERASE);
				putimage(px, py, img_mm + 2, SRCINVERT);
			}
			else  // δѡ��״̬
			{
				putimage(px, py, img_mm + 1, NOTSRCERASE);
				putimage(px, py, img_mm, SRCINVERT);
			}
			// ��ť�ı�����
			outtextxy((w - textwidth(ch[i + 1].c_str())) / 2 + px,
				(h - textheight(ch[i + 1].c_str())) / 2 + py,
				ch[i + 1].c_str());
		}

		// ���Ƹ���ť���淨˵������ʷ��߷֡��Ŷ�˵������Ϸ���ã�
		settextstyle(30, 0, "΢���ź�");
		for (int i = 0; i < 4; i++)
		{
			int px = 0, py = 300 + i * 50;  // ��ťλ��
			if (i + 5 == cur)  // ѡ��״̬
			{
				putimage(px, py, img_mn + 3, NOTSRCERASE);
				putimage(px, py, img_mn + 2, SRCINVERT);
			}
			else  // δѡ��״̬
			{
				putimage(px, py, img_mn + 1, NOTSRCERASE);
				putimage(px, py, img_mn, SRCINVERT);
			}
			// ��ť�ı�����
			outtextxy((w / 2 - textwidth(ch[i + 5].c_str())) / 2 + px,
				(h / 2 - textheight(ch[i + 5].c_str())) / 2 + py,
				ch[i + 5].c_str());
		}

		// ���Ʊ���
		settextstyle(80, 0, "΢���ź�");
		outtextxy(310, 40, ch[0].c_str());
		FlushBatchDraw();  // ˢ�»���


		// �����û����루ѡ��ť��
		ExMessage msg;
		if (peekmessage(&msg, EX_KEY))  // ��������Ϣ
		{
			if (msg.message == WM_KEYDOWN)  // ��������
			{
				int key = msg.vkcode;
				if (key == 'W') {  // ����ѡ��
					if (cur > 1) cur--;
				}
				if (key == 'S') {  // ����ѡ��
					if (cur < 8) cur++;
				}
				if (key == 'A') {  // �л�������ť
					if (cur < 5) cur = 5;
				}
				if (key == 'D') {  // �л�������ť
					if (cur > 4) cur = 1;
				}
				// �س�ȷ��
				if (key == VK_RETURN) {
					switch (cur)
					{
					case 1:  // ��ʼ��Ϸ
						EndBatchDraw();  // �����˵���������
						flushmessage();
						_initGame();      // ��ʼ����Ϸ
						_gameLoopView();  // ������Ϸѭ��
						BeginBatchDraw();  // ���¿����˵���������
						break;
					case 4:  // �˳���Ϸ
						flushmessage();
						EndBatchDraw();
						exitView();
						break;
					case 5:
						flushmessage();
						EndBatchDraw();
						_instructionView();
						break;
					case 7:
						flushmessage();
						EndBatchDraw();
						_introductionView();
						break;
					default:  // ��������δʵ��
						break;
					}
				}
			}
		}
	}
	EndBatchDraw();  // ������������
}

void _renderGameView() {
	setbkcolor(WHITE);  // ���ڱ���ɫ
	cleardevice();      // ˢ�´���

	// ������Ϸ����߿�20x20����ÿ��26���أ�
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(150, 40, 150 + 20 * 26, 40 + 20 * 26);  // ��Ϸ����߿�520x520����

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

void _gameLoopView() {
	BeginBatchDraw();

	// ������Ⱦһ�Σ�ȷ����Ϸ��ʼʱ��ʾ����
	_renderGameView();

	// ��Ϸ��ѭ��
	while (1)
	{
		checkInput();  // ����û�����
		int collision = _checkCollision();  // �ж���ײ����

		switch (collision) {
		case 0:  // ����ײ���ƶ���
			moveSnake();
			break;
		case 1:  // ��ײ�߽�/����/ǽ����Ϸ����
			EndBatchDraw();  // ������������
			_endView();
			return;
		case 2:  // �Ե�ʳ������ʳ�ﲢ������ʳ��
			_handleEat();
			_generateFood();
			break;
		}
		_renderGameView();  // ��Ⱦ��ǰ����
		Sleep(_moveInterval);  // �������ʱ�������ٶȣ�
	}
	EndBatchDraw();  // �����������ƣ�ѭ���˳�ʱִ�У�
}

void exitView() {
	//while (1) {
	//	std::cout << "�Ƿ��˳���Ϸ?(�ո��˳�,�س����ز˵�)\n";  // չʾѡ��
	//	int choice = _getch();  // �����û����루�����ԣ�
	//	if (choice == 32)  // �ո�ASCII 32�����˳�����
	//		exit(0);
	//	else if (choice == 13)  // �س���ASCII 13�����������˵�
	//		mainMenuView();
	//	else  // �������룺����ѯ��
	//		continue;
	//}

	setbkcolor(RGB(133, 194, 77));
	cleardevice();
	settextstyle(28, 0, "����");
	settextcolor(WHITE);

	//���Լ���ͼƬ
	IMAGE exitbg;
	loadimage(&exitbg, "./exitView.png", 800, 600);

	// ��Ϸ��������ѭ��
	while (true)
	{
		/* չʾ���� */
		string str1 = "�Ƿ��˳���Ϸ?";
		string str2 = "�ո��˳�,�س����ز˵�";
		cleardevice();
		putimage(0, 0, &exitbg);
		outtextxy(350, 175, str1.c_str());  // ������ʾ����

		// ��ʾ���ַ���
		outtextxy(350, 215, str2.c_str());

		// ��ʾ������ʾ
		/*settextstyle(20, 0, "����");
		outtextxy(400 - textwidth("���س��������˵�") / 2, 400, "���س��������˵�");*/

		/* �ȴ��س� */
		if (_getch() == 13)  // �س���
		{
			flushmessage();
			_mainMenuView();
		}
		else if (_getch() == 32)
		{
			closegraph();
			exit(0);
		}
		else
		{
			continue;
		}
	}
}

void _pauseView()
{
	int xs_flag = 0;  // ѡ�а�ť������0:������Ϸ, 1:ʹ�õ���, 2:ģʽѡ��, 3:���ز˵���

	// ���Լ�����ͣ���汳����ʧ�ܲ�Ӱ�칦�ܣ�
	IMAGE pausebg;
	loadimage(&pausebg, "./pauseView.png");

	// ��ͣ����ѭ��
	while (1) {
		// ���Ʊ���
		cleardevice();
		if (pausebg.getwidth() > 0)
			putimage(0, 0, &pausebg);

		// ���Ʊ�������Ϣ
		settextstyle(40, 0, "����");
		outtextxy(340, 40, "��Ϸ����ͣ");

		settextstyle(40, 0, "����");
		char buf[64];
		sprintf_s(buf, "��ǰ������%d", currentScore);
		outtextxy(320, 100, buf);

		// ���ư�ť��δѡ��״̬��
		button(256, 224, 308, 76, "������Ϸ", 40, RGB(171, 171, 171));
		button(256, 321, 308, 76, "ʹ�õ���", 40, RGB(171, 171, 171));
		button(256, 418, 308, 76, "ģʽѡ��", 40, RGB(171, 171, 171));
		button(256, 515, 308, 76, "���ز˵�", 40, RGB(171, 171, 171));

		// ������ʾѡ�еİ�ť
		switch (xs_flag) {
		case 0:
			button(256, 224, 308, 76, "������Ϸ", 40, WHITE);
			break;
		case 1:
			button(256, 321, 308, 76, "ʹ�õ���", 40, WHITE);
			break;
		case 2:
			button(256, 418, 308, 76, "ģʽѡ��", 40, WHITE);
			break;
		case 3:
			button(256, 515, 308, 76, "���ز˵�", 40, WHITE);
			break;
		}

		FlushBatchDraw();


		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w' || ch == 'W') {  // ��ѡ
				xs_flag = (xs_flag - 1 + 4) % 4;
			}
			else if (ch == 's' || ch == 'S') {  // ��ѡ
				xs_flag = (xs_flag + 1) % 4;
			}
			else if (ch == 32 || ch == 13) {  // �ո�/�س�ȷ��
				if (xs_flag == 0) {  // ������Ϸ
					flushmessage();
					return;
				}
				else if (xs_flag == 3) {  // ���ز˵�
					flushmessage();
					EndBatchDraw();
					_mainMenuView();
					BeginBatchDraw();
					return;
				}
				// ��������δʵ��
			}
		}

		Sleep(50);  // ��ʱ
	}
}

void _endView() {
	//cout << "endView works!\n";				//����gameLoopView()
	//cout << "���������������!\n";
	//_getch();
	//exit(0);

	setbkcolor(RGB(49, 124, 74));
	cleardevice();
	settextstyle(28, 0, "����");
	settextcolor(WHITE);

	//���Լ���ͼƬ
	IMAGE endbg;
	loadimage(&endbg, "./endView1.png", 800, 600);

	// ��Ϸ��������ѭ��
	while (true)
	{
		/* չʾ���� */
		string str = to_string(currentScore);
		cleardevice();
		putimage(0, 0, &endbg);
		outtextxy(450, 175, str.c_str());  // ������ʾ����

		// ��ʾ���ַ���
		outtextxy(450, 215, str.c_str());

		// ��ʾ������ʾ
		/*settextstyle(20, 0, "����");
		outtextxy(400 - textwidth("���س��������˵�") / 2, 400, "���س��������˵�");*/

		/* �ȴ��س� */
		if (_getch() == 13)  // �س���
		{
			flushmessage();
			_mainMenuView();
			return;
		}
	}
}

void button(int x, int y, int w, int h, const char* text, int texth, COLORREF color) {
	setbkmode(TRANSPARENT);
	setfillcolor(color);       // ��ť���ɫ
	setlinecolor(BLACK);       // �߿�ɫ
	setlinestyle(PS_SOLID, 5); // �߿���ʽ
	fillroundrect(x, y, x + w, y + h, 10, 10);  // ����Բ�Ǿ��ΰ�ť

	// ���ư�ť�ı�
	settextstyle(texth, 0, "����");
	settextcolor(BLACK);
	int tw = textwidth(text);  // �ı����
	int th = textheight(text); // �ı��߶�
	int tx = x + w / 2 - tw / 2;  // �ı�x���꣨���У�
	int ty = y + h / 2 - th / 2;  // �ı�y���꣨���У�
	outtextxy(tx, ty, text);      // �����ı�
}


void _introductionView()
{
	flushmessage();
	setbkcolor(WHITE);
	cleardevice();

	//���Լ���ͼƬ
	IMAGE introductionbg;
	loadimage(&introductionbg, "./introduction.png", 800, 600);

	// �Ŷӽ��ܽ���ѭ��
	while (true)
	{
		/* չʾ���� */
		cleardevice();
		putimage(0, 0, &introductionbg);
		/*Sleep(1000);*/

		// ��ʾ������ʾ
		/*settextstyle(20, 0, "����");
		outtextxy(400 - textwidth("���س��������˵�") / 2, 400, "���س��������˵�");*/

		/* �ȴ��س� */
		if (_getch() == 13)  // �س���
		{
			flushmessage();
			//mainMenuView();
		}
		else
		{
			continue;
		}
	}
}


void _instructionView()
{
	flushmessage();
	BeginBatchDraw();
	setbkcolor(RGB(212, 245, 254));
	cleardevice();
	settextstyle(28, 0, "����");
	settextcolor(BLACK);

	//���Լ���ͼƬ
	IMAGE insbg;
	loadimage(&insbg, "./instruction.jpg", 800, 600);

	// ��Ϸ��������ѭ��
	while (true)
	{
		/* չʾ���� */
		string str = "���س��������˵�";
		cleardevice();
		putimage(0, 0, &insbg);

		outtextxy(350, 500, str.c_str());
		// ��ʾ������ʾ

		/* �ȴ��س� */
		if (_kbhit())  // �س���
		{
			char ch = _getch();
			if (ch == 13)
			{
				flushmessage();
				FlushBatchDraw();
				//mainMenuView();
			}

		}
		else
		{
			continue;
		}
	}
}