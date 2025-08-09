#include<graphics.h>
#include<iostream>
#include<conio.h>

//---------------------------------数据设计---------------------------------



/*
	默认地图信息（20*20）
	map0[i][j]表示地图上(i,j)坐标点内容：
		0表示空地 
		1表示墙 
		2表示食物 
		3表示障碍物
*/
int map0[20][20];


/*
		蛇身信息:
		snake[i][0]表示第i节身体的x轴坐标
		snake[i][1]表示第i节身体的y轴坐标
		第0节为蛇头
		蛇的初始长度为3
		初始化从地图左上方空白处从左往右移动
*/
int snake[20 * 20][2];


//蛇的当前长度  初始化为3 每吃到食物+1
int snakeLength;


/*蛇头当前的移动方向
	w =  上
	a =  左
	s =  下
	d =	 右
初始化方向为：从左往右 (d)
*/
char direction;


//总得分:累计所有游戏的得分--拓展
int totalScore = 0;


//每局游戏当前的得分，初始化为0，吃食物+10
int currentScore;


//移动时间，单位(ms)，默认为1000ms--拓展
int moveInterval;



//---------------------------------数据设计---------------------------------



//---------------------------------Service层---------------------------------


/*
	initGame:
		负责人：danking
		功能：
			初始化各项数据：map0、snake数组，snakeLength、direction、current、moveInterval
			初始化地图、蛇的位置、分数、方向等基本信息
		参数：		void;
		返回值：	void;
*/
void initGame();


/*
	moveSnake:
		负责人：圣龙战
		功能：
			蛇沿当前方向移动一格
			实现方式：修改snake数组，从尾到头将每一节身体移到前一节的位置，再根据方向 direction 移动蛇头
		参数：		void;		
		返回值：	void;
*/
void moveSnake();


/*
	checkCollision：
		负责人：鸟哥
		功能：
			判断蛇头是否与蛇身、墙、障碍、食物发生碰撞
			先在snake数组中判断是否撞上蛇身
			再在map0数组中判断是否撞上墙、障碍、食物

			没有撞上，返回				0
			撞上蛇身、墙、障碍，返回	1
			撞上食物,返回				2	
			
		参数：		void;
		返回值：	
			0	没有撞上; 
			1	撞上蛇身、墙、障碍; 
			2	撞上食物;
*/
int checkCollision();


/*
	checkInput:
		负责人：小逸
		功能：
			检查用户输入，使用 _kbhit 检测是否有键盘输入；
			若没有输入，则不进行操作
			若输入方向合法（不允许反向），则修改 direction；
			若输入空格，则调用 pauseView() 暂停游戏；

				 _kbhit(); 
					函数作用: 判断用户是否有输入(缓冲区是否有值)
					返回值:
						0: 表示用户没有输入(缓冲区没有值)
						非0: 表示用户有输入内容(缓冲区有值)

				可以在 图灵院小组相关资料->C,C++额外技术相关  中了解相关函数或者向小学长询问

		参数：		void;
		返回值：	void;
*/
void checkInput();


/*
	handleEat：
		负责人：君剑
		功能：
			处理吃食物逻辑，修改snakeLength、currentScore、map0数组中食物坐标和
			snake数组中增加并修改信息：
				蛇头、蛇身沿当前方向移动一格，增加一节蛇身
				实现方式：修改snake数组,从尾到头将每一节身体移到前一节的位置,再根据方向 direction 移动蛇头,在原来蛇尾位置增加一节
		参数：		void;
		返回值：	void;
*/
void handleEat();


/*
	generateFood：
		负责人：凉水
		功能：
			在地图上随机一个空位置(map0[x][y] = 0)生成一个食物（map0[i][j] = 2）
			可以使用srand()、rand()函数
		参数：		void;
		返回值：	void;
*/
void generateFood();



//---------------------------------Service层---------------------------------



//---------------------------------V i e w层---------------------------------



/*
	mainMenuview:
		负责人：小白
		功能：
			展示主菜单选项，玩家可以选择  开始游戏、退出游戏(核心)
			玩家通过ws选择选项，默认选项为 开始游戏 ，选中选项高亮，
			玩家按回车确认选择
			while(1){
				1. 展示选项
				2. 用户输入
				3. 根据输入进行对应处理
					开始游戏: 调用初始化游戏函数 initGame() ，调用游戏整合界面函数 gameLoopView() ;
					退出游戏: 调用退出游戏界面函数 exitView();
			}
		参数：		void;
		返回值：	void;
*/
void mainMenuView();


/*
	renderGameView:
		负责人：小卓
		功能：
			展示当前游戏画面
			根据map0、snake数组,currentScore、snakeLength 绘制地图与信息，展示当前游戏的画面
		参数：		void;
		返回值：	void;
*/
void renderGameView();


/*
	gameLoopView：
		负责人：圣龙战
		功能：
			整合游戏界面，游戏主逻辑循环：

			1. 检测输入			调用 checkInput()
			2. 判断碰撞			调用 checkCollision()
            - 撞墙/蛇身/障碍：	调用 endView()
            - 吃到食物：		调用 handleEat()、generateFood()
            - 正常移动：		调用 moveSnake()
			3. 渲染画面			调用 renderGameView()
			4. 延时				Sleep(moveInterval);

		参数：		void;
		返回值：	void;
*/
void gameLoopView();


/*
	exitView:
		负责人：小何
		功能：
			展示内容确认是否退出游戏，提示按空格退出，按回车返回主菜单
			while(1){
				1. 展示内容
				2. 用户输入
				3. 根据输入进行对应处理
					退出游戏: 调用 exit(0);
					返回主菜单：调用主菜单界面函数 mainMenuView();
			}
		参数：		void;
		返回值：	void;
*/
void exitView();


/*
	pauseView：
		负责人：徐少
		功能：
			展示“游戏暂停”，本局目前分数，展示  继续游戏、返回菜单 按钮
			玩家通过ws选择选项，默认选项为 继续游戏 ，选中选项高亮，玩家按空格确认选择
			while(1){
				1. 展示内容
				2. 用户输入
				3. 根据输入进行对应处理
					继续游戏: 不初始化，调用游戏界面函数 gameLoopView();
					返回菜单：调用主菜单界面函数 mainMenuView();
			}
		参数：		void;
		返回值：	void;
*/
void pauseView();


/*
	endView:
		负责人：烟雨
		功能：
			展示“游戏结束”，本局最终分数，展示按回车返回主菜单
			while(1){
				1. 展示内容
				2. 用户输入
				3. 根据输入进行对应处理
					返回菜单：调用主菜单界面函数  mainMenuView();
			}
		参数：		void;
		返回值：	void;
*/
void endView();



//---------------------------------V i e w 层---------------------------------


using namespace std;
int main()
{
	snakeLength = 3;				//测试moveSnake()/gameLoopView()
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
	//初始化地图数据
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			map0[i][j] = 0;
		}
	};
	//初始化围墙数据
	for (int i = 0; i < 20; i++) {
		map0[0][i] = 1;          // 上边界
		map0[19][i] = 1;         // 下边界
		map0[i][0] = 1;          // 左边界
		map0[i][19] = 1;         // 右边界
	}
	// 蛇初始位置设为左上方空白区域
	snake[0][0] = 3;  // 蛇头x坐标（水平方向）
	snake[0][1] = 1;  // 蛇头y坐标（垂直方向）
	snake[1][0] = 2;  // 第一节身体x坐标
	snake[1][1] = 1;  // 第一节身体y坐标
	snake[2][0] = 1;  // 第二节身体x坐标
	snake[2][1] = 1;  // 第二节身体y坐标
	//初始化蛇的长度
	snakeLength = 3;
	// 初始化方向
	direction = 'd';
	//每局游戏当前的得分，初始化为0，吃食物+10
	currentScore = 0;
	//移动时间，单位(ms)，默认为1000ms--拓展
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

	for (int i = 0; i <= snakeLength; i++)	//测试moveSnake()/gameLoopView()
	{
		cout << "蛇的第" << i << "节身体";
		cout << "x坐标为: " << snake[i][0];
		cout << " , y坐标为: " << snake[i][1] << endl;
	}
}

int checkCollision() {
	//int rk = 0;								//测试gameLoopView()
	//cout << "返回值:\n0 没有撞上\n";
	//cout << "1 撞上蛇身、墙、障碍\n2 撞上食物\n";
	//cout << "请输入返回值(0/1/2):";
	//cin >> rk;
	//if (rk > 2||rk < 0)
	//{
	//	rk = 0;
	//}
	//return rk;

	int next_x = snake[0][0];
	int next_y = snake[0][1];
	int result = 1;
	switch (direction) {					//蛇头沿当前方向再走一格的坐标
	case'w':
		next_y -= 1;
	case's':
		next_y += 1;
	case'a':
		next_x -= 1;
	case'd':
		next_x += 1;
	}
	for (int i = 0; i < 20 * 20; i++) {		//判断蛇身与蛇头是否发生碰撞
		if (snake[i][0] == next_x && snake[i][1] == next_y)
			result = 1;
	}
	if (map0[next_y][next_x] == 1)			//判断蛇头在地图中的坐标点的内容
		result = 1;
	if (map0[next_y][next_x] == 0)
		result = 0;
	if (map0[next_y][next_x] == 2)
		result =  2;
	return result;
}

void checkInput() {
	//cout << "checkInput works!\n";			//测试gameLoopView()


	if (!_kbhit())          // 无输入直接返回
		return;
	else
	{
		int ch = _getch();      // 读取按键（不回显）

			switch (ch)
			{
			case 'w':   // 上
				if (direction != 's') direction = 'w';
				break;
			case 'a':   // 左
				if (direction != 'd') direction = 'a';
				break;
			case 's':   // 下
				if (direction != 'w') direction = 's';
				break;
			case 'd':   // 右
				if (direction != 'a') direction = 'd';
				break;
			case ' ':   // 空格 -> 暂停
				pauseView();
				break;
			default:
				break;
			}
	}
	
}

void handleEat() {
	//cout << "handleEat works!\n";			//测试gameLoopView()

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
	//cout << "generateFood works!\n";		//测试gameLoopView()

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
	cout << "renderGameView works!\n";		//测试gameLoopView()
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
		std::cout << "是否退出游戏?(空格退出,回车返回菜单)\n";//展示选项
		int choice = _getch();//接受用户输入单个字符,_getch()包含在conio.h里
		if (choice == 32)//空格的ASCII码为32
			exit(0);//按空格退出程序
		else if (choice == 13)//回车的ASCII码为13
			mainMenuView();//按回车进入主菜单
		else
			continue;//输入其他的字符继续询问
	}
}

void pauseView();

void endView() {
	//cout << "endView works!\n";				//测试gameLoopView()
	//cout << "按任意键结束程序!\n";
	//_getch();
	//exit(0);

	setbkcolor(GREEN);
	cleardevice();
	settextstyle(40, 0, L"宋体");
	settextcolor(BLACK);

	while (true)
	{
		/* 展示内容 */
		cleardevice();
		outtextxy(400 - textwidth(L"游戏结束") / 2, 220, L"游戏结束");

		wchar_t buf[32];
		swprintf_s(buf, L"本局最终分数：%d", currentScore);
		outtextxy(400 - textwidth(buf) / 2, 280, buf);

		settextstyle(20, 0, L"宋体");
		outtextxy(400 - textwidth(L"按回车返回主菜单") / 2, 400, L"按回车返回主菜单");

		/* 等待回车 */
		if (_getch() == 13)        // 回车键
		{
			closegraph();
			mainMenuView();
			return;
		}
	}
}