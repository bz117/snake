#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>

using namespace std;


//本架构是在基础架构的基础上修改的，
// 基础架构的相关函数、变量有修改的，新增的函数、变量
// 都在名称前加上了  “ _ ”


//---------------------------------数据设计---------------------------------



/*
	默认地图信息（20*20）
	map0[i][j]表示地图上(i,j)坐标点内容：
		0表示空地 
		1表示墙 
		2表示食物 
		3表示障碍物

		拓展:
			2表示普通食物

			21表示加速食物
			22表示减速食物
			23表示穿透食物
*/
int _map0[20][20];


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


//总得分:累计所有游戏的得分						--拓展
int totalScore = 0;


//每局游戏当前的得分，初始化为0，吃食物+10
int currentScore;


//移动间隔，单位(ms)默认200						--拓展
int _moveInterval;


//道具数量.初始化为0							--拓展
//加速、减速、穿透
int _addSpeedProp, _minusSpeedProp, _penetrateProp;


/*//选择的模式									--拓展

	正常模式		0
	限时模式		1
	食物变异模式	2
	挑战模式		3
	对抗模式		4
*/
int _mode;


/*//历史最高分数								--拓展
	正常模式		0
	限时模式		1
	食物变异模式	2
	挑战模式		3
	对抗模式		4
//普通模式、食物变异模式、挑战模式、对抗模式的历史最高分数,
//限时模式的最快通关时间						--拓展
*/
int _charts[5];


/*
		人机蛇									--拓展
		蛇身信息:
		snake[i][0]表示第i节身体的x轴坐标
		snake[i][1]表示第i节身体的y轴坐标
		第0节为蛇头
		蛇的初始长度为3
		初始化从地图左下方空白处从左往右移动
*/
int _AIsnake[20 * 20][2];


/*
	计时器，单位(ms)							--拓展
	限时模式的倒计时
*/
int _timedate;


//道具状态
struct snake_state
{
	bool _addSpeedProp, _minusSpeedProp, _penetrateProp;
};



//---------------------------------数据设计---------------------------------



//---------------------------------Service层---------------------------------


/*
	initGame:
		负责人：danking
		功能：
			初始化各项数据：map0、snake数组，snakeLength、direction、current、moveInterval
			初始化地图、蛇的位置、分数、方向等基本信息

		拓展功能:
			初始化所有模式的相关信息

		参数：		void;
		返回值：	void;
*/
void _initGame();


/*
	moveSnake:
		负责人：
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
			判断蛇头是否是否与蛇身、墙、障碍、食物发生碰撞
			先在snake数组中判断是否撞上蛇身
			再在map0数组中判断是否撞上墙、障碍、食物

			没有撞上，返回				0
			撞上蛇身、墙、障碍，返回	1
			撞上食物,返回				2	

		拓展功能:根据蛇的状态再来判断
			
		参数：		void;
		返回值：	
			0	没有撞上; 
			1	撞上蛇身、墙、障碍; 
			2	撞上食物;
*/
int _checkCollision();


/*
	checkInput:
		负责人：
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
			处理吃食物逻辑，修改snakeLength、current、map0数组中食物坐标和
			snake数组中增加并修改信息：
				蛇头、蛇身沿当前方向移动一格，增加一节蛇身
				实现方式：修改snake数组,从尾到头将每一节身体移到前一节的位置,再根据方向 direction 移动蛇头,在原来蛇尾位置增加一节

		拓展功能:
			判断是哪种食物，给与相应效果，修改相关蛇的数据

		参数：		void;
		返回值：	void;
*/
void _handleEat();


/*
	generateFood：
		负责人：凉水
		功能：
			在地图上随机一个空位置(map0[x][y] = 0)生成一个食物（map0[i][j] = 2）
			可以使用srand()、rand()函数

		拓展功能:
			根据模式，随机生成特殊食物
		参数：		void;
		返回值：	void;
*/
void _generateFood();


/*
	shopView:
		负责人:小卓
		拓展功能:
			"界面上面展示""道具商店""和金币数量
			中间展示所有可购买的道具和每个道具的拥有数量
			下面提示按回车回到主菜单"

			根据道具所需要的金币数量扣除金币并增加道具的数量，若金币不足则显示“金币不足”
			道具：加速、减速、穿透、背景图
		参数:		void;
		返回值:		void;
*/
void  _shopView();


/*
	propUseView:
		负责人:小何
		拓展功能:
			"最上方展示“进行游戏”按钮，
			下方展示玩家所拥有的所有道具，每个道具都有“使用”按钮"	
			三种道具：加速、减速、穿透
			根据道具效果修改相关数据
		参数:		void;
		返回值:		void;
*/
void  _propUseView();


/*
	generateObstacle：
		负责人：danking
		拓展功能：
			在地图上随机一个空位置(map0[x][y] = 0)生成一个障碍物（map0[i][j] = 3）
			可以使用srand()、rand()函数
		参数：		void;
		返回值：	void;
*/
void _generateObstacle();


/*
	modeView:
		负责人:鸟哥
		拓展功能:
			展示所有特殊的模式：限时模式，食物变异模式，挑战模式，对抗模式
			玩家按下ws时，光标会上下移动，按下空格确定进入模式，直接进入各个模式对应的游戏界面
			修改 mode
			正常模式			0，
			限时模式			1，
			食物变异模式		2，
			挑战模式			3，
			对抗模式			4
		参数:		void;
		返回值:		void;
*/
void _modeView();


/*
	AIwork：
		负责人：小白
		拓展功能：
			人机蛇相关逻辑:
				人机蛇初始化、人机蛇移动、吃食物、死亡
				再生成人机蛇
		参数：		void;
		返回值：	void;
*/
void _AIwork();


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

		拓展功能:
			修改totalScore,把本局分数加上
		参数：		void;
		返回值：	void;
*/
void _endView();



//---------------------------------Service层---------------------------------



//---------------------------------V i e w 层---------------------------------



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

			拓展功能:
				展示团队介绍、玩法说明、游戏设置、排行榜
		参数：		void;
		返回值：	void;
*/
void _mainMenuView();


/*
	renderGameView:
		负责人：小卓
		功能：
			展示当前游戏画面
			根据map0、snake数组,currentScore、snakeLength 绘制地图与信息，展示当前游戏的画面

		拓展功能:
			根据mode，展示不同的游戏模式的当前画面
		参数：		void;
		返回值：	void;
*/
void _renderGameView();


/*
	gameLoopView：
		负责人：君剑
		功能：
			整合游戏界面，游戏主逻辑循环：

			1. 检测输入			调用 checkInput()
			2. 判断碰撞			调用 checkCollision()
            - 撞墙/蛇身/障碍：	调用 endView()
            - 吃到食物：		调用 handleEat()、generateFood()
            - 正常移动：		调用 moveSnake()
			3. 渲染画面			调用 renderGameView()
			4. 延时				
				static int waitIndex = 1; // 静态局部变量，初始化时为1
				waitIndex++; // 每一帧+1
				if (waitIndex==10) // 如果等于10才执行，这样小蛇每隔10帧移动一次
				{
					moveSnake(); //  调用小蛇移动函数
					waitIndex = 1; // 再变成1
				}

			拓展功能:
				根据不同的模式，处理不同的游戏主逻辑
		参数：		void;
		返回值：	void;
*/
void _gameLoopView();


/*
	exitView:
		负责人：
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

		拓展功能:
			增加展示 模式选择的按钮
		参数：		void;
		返回值：	void;
*/
void _pauseView();


/*
	instructionView:
		负责人:徐少
		拓展功能:
			展示各模式的玩法说明,提示按回车回到主菜单
			展示道具的功能
			while(1){
				1. 展示内容
				2. 用户输入
				3. 根据输入进行对应处理
					玩家输入回车
					返回菜单：调用主菜单界面函数  mainMenuView();
			}
		参数:		void;
		返回值:		void;
*/
void _instructionView();


/*	
	introductionView:
		负责人:小逸
		拓展功能:
			展示开发者名单和对应负责内容,提示按回车回到主菜单
			玩家输入回车,返回菜单：调用主菜单界面函数  mainMenuView();
		参数:		void;
		返回值:		void;
*/
void _introductionView();


/*
	settingView:
		负责人:烟雨
		拓展功能:
			展示可以修改的选项:
				音效: <开>
				音量: <50>
				下方展示操作提示:
				按回车键回到主菜单
				ws移动光标, ad修改当前选项
		参数:		void;
		返回值:		void;
*/
void  _settingView();


/*
	chartsView:
		负责人:凉水
		拓展功能:
			"分别展示普通模式、食物变异模式、挑战模式、对抗模式的历史最高分数
			展示限时模式的最快通关时间
			下方提示按回车回到主菜单"	
		参数:		void;
		返回值:		void;
*/
void  _chartsView();



//---------------------------------V i e w 层---------------------------------


int main()
{
	//snakeLength = 3;				//测试moveSnake()/gameLoopView()
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
	//初始化图形窗口（宽800，高600，显示控制台）
	initgraph(800, 600, EX_SHOWCONSOLE);
	//进入主菜单
	_mainMenuView();
	return 0;
}

void _initGame() {
	//初始化地图数据（所有格子设为空地）
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			_map0[i][j] = 0;
		}
	};
	//初始化围墙数据（四周边界设为墙）
	for (int i = 0; i < 20; i++) {
		_map0[0][i] = 1;          // 上边界
		_map0[19][i] = 1;         // 下边界
		_map0[i][0] = 1;          // 左边界
		_map0[i][19] = 1;         // 右边界
	}
	// 蛇初始位置设为地图中间区域，避免快速撞墙
	snake[0][0] = 10;  // 蛇头x坐标（水平方向）- 地图中间
	snake[0][1] = 10;  // 蛇头y坐标（垂直方向）- 地图中间
	snake[1][0] = 9;   // 第一节身体x坐标
	snake[1][1] = 10;  // 第一节身体y坐标
	snake[2][0] = 8;   // 第二节身体x坐标
	snake[2][1] = 10;  // 第二节身体y坐标
	//初始化蛇的长度
	snakeLength = 3;
	// 初始化方向（向右）
	direction = 'd';
	//初始化当前分数
	currentScore = 0;
	//初始化移动间隔（200ms，控制蛇移动速度）
	_moveInterval = 200;

	// 生成初始食物
	_generateFood();
}

void moveSnake() {
	//从尾部到头部，每节身体移动到前一节的位置
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}
	//根据当前方向移动蛇头
	switch (direction)
	{
	case 'w':  // 上移（y轴减1）
		snake[0][1] = snake[0][1] - 1;
		break;
	case 'a':  // 左移（x轴减1）
		snake[0][0] = snake[0][0] - 1;
		break;
	case 's':  // 下移（y轴加1）
		snake[0][1] = snake[0][1] + 1;
		break;
	case 'd':  // 右移（x轴加1）
		snake[0][0] = snake[0][0] + 1;
		break;
	}
	//for (int i = 0; i <= snakeLength; i++)	//测试moveSnake()/gameLoopView()
	//{
	//	cout << "蛇的第" << i << "节身体";
	//	cout << "x坐标为: " << snake[i][0];
	//	cout << " , y坐标为: " << snake[i][1] << endl;
	//}
}

int _checkCollision() {
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

	//计算蛇头下一步坐标
	int next_x = snake[0][0];
	int next_y = snake[0][1];

	switch (direction) {
	case'w':  // 上移
		next_y -= 1;
		break;
	case's':  // 下移
		next_y += 1;
		break;
	case'a':  // 左移
		next_x -= 1;
		break;
	case'd':  // 右移
		next_x += 1;
		break;
	}

	// 边界检查 - 超出地图范围（0~19）则碰撞
	if (next_x < 0 || next_x >= 20 || next_y < 0 || next_y >= 20) {
		return 1;
	}

	// 检查蛇身碰撞（与除头部外的身体重合）
	for (int i = 1; i < snakeLength; i++) {
		if (snake[i][0] == next_x && snake[i][1] == next_y)
			return 1;  // 蛇身碰撞
	}

	// 检查地图内容（墙/空地/食物）
	if (_map0[next_y][next_x] == 1)			// 撞墙
		return 1;
	if (_map0[next_y][next_x] == 0)			// 空地（无碰撞）
		return 0;
	if (_map0[next_y][next_x] == 2)			// 吃到食物
		return 2;

	return 0; // 默认无碰撞
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
		case 'w':   // 上（忽略大小写）
		case 'W':
			if (direction != 's') direction = 'w';  // 不能直接向下转上
			break;
		case 'a':   // 左（忽略大小写）
		case 'A':
			if (direction != 'd') direction = 'a';  // 不能直接向右转左
			break;
		case 's':   // 下（忽略大小写）
		case 'S':
			if (direction != 'w') direction = 's';  // 不能直接向上转下
			break;
		case 'd':   // 右（忽略大小写）
		case 'D':
			if (direction != 'a') direction = 'd';  // 不能直接向左转右
			break;
		case ' ':   // 空格 -> 暂停游戏
			_pauseView();
			break;
		default:    // 其他按键忽略
			break;
		}
	}
}

void _handleEat() {
	// 蛇身增长：从尾部开始，每节移动到前一节位置（新增一节在尾部）
	for (int i = snakeLength; i > 0; --i) {
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}

	// 根据方向移动蛇头到食物位置
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

	// 更新数据：长度+1，分数+10，清除食物标记
	++snakeLength;
	currentScore += 10;
	_map0[snake[0][1]][snake[0][0]] = 0;  // 原食物位置设为空地
}

void _generateFood() {

	//cout << "generateFood works!\n";		//测试gameLoopView()
	srand((unsigned int)time(NULL));  // 初始化随机数种子
	int n = 0;  // 标记是否生成食物
	int attempts = 0;  // 尝试次数（避免死循环）
	while (n == 0 && attempts < 1000) {
		int x1 = rand() % 20;  // 随机x坐标（0~19）
		int y1 = rand() % 20;  // 随机y坐标（0~19）
		// 检查位置是否为空地且不在蛇身上
		if (_map0[y1][x1] == 0)
		{
			bool isOnSnake = false;
			// 检查是否与蛇身重合
			for (int i = 0; i < snakeLength; i++)
			{
				if (snake[i][0] == x1 && snake[i][1] == y1)
				{
					isOnSnake = true;
					break;
				}
			}
			if (!isOnSnake) {  // 合法位置：生成食物
				_map0[y1][x1] = 2;
				n++;  // 标记已生成
			}
		}
		attempts++;  // 累计尝试次数
	}
	// 如果生成失败（地图快满），什么也不做
}

void _mainMenuView()
{
	int cur = 1;  // 当前选中的按钮索引（1~8）
	BeginBatchDraw();
	//定义图片变量
	IMAGE img_mm[4];
	IMAGE img_mn[4];
	IMAGE img_bk;
	setbkmode(TRANSPARENT);

	//加载图片
	int w = 300;   // 主按钮宽度
	int h = w / 4; // 主按钮高度

	loadimage(&img_bk, "./assets/主菜单.jpg", 800, 600);  // 背景图
	loadimage(img_mm, "./assets/按钮.png", w, h);         // 主按钮正常
	loadimage(img_mm + 1, "./assets/按钮m.png", w, h);    // 主按钮高亮遮罩
	loadimage(img_mm + 2, "./assets/按钮1.png", w, h);    // 主按钮选中
	loadimage(img_mm + 3, "./assets/按钮1m.png", w, h);   // 主按钮选中遮罩

	loadimage(img_mn, "./assets/按钮.png", w / 2, h / 2);  // 副按钮正常
	loadimage(img_mn + 1, "./assets/按钮m.png", w / 2, h / 2); // 副按钮高亮遮罩
	loadimage(img_mn + 2, "./assets/按钮1.png", w / 2, h / 2); // 副按钮选中
	loadimage(img_mn + 3, "./assets/按钮1m.png", w / 2, h / 2); // 副按钮选中遮罩

	// 主菜单循环
	while (1) {
		setbkcolor(WHITE);
		cleardevice();  // 清空画面

		//绘制背景
		putimage(0, 0, &img_bk);

		//绘制按钮文本
		string ch[10] = { "主菜单","开始游戏","模式选择","道具商店","退出游戏","玩法说明","历史最高分","团队说明","游戏设置" };
		settextstyle(60, 0, "微软雅黑");  // 设置字体
		settextcolor(BLACK);

		// 绘制主按钮（开始游戏、模式选择、道具商店、退出游戏）
		for (int i = 0; i < 4; i++)
		{
			int px = 250, py = 150 + i * 100;  // 按钮位置
			if (i + 1 == cur)  // 选中状态
			{
				putimage(px, py, img_mm + 3, NOTSRCERASE);
				putimage(px, py, img_mm + 2, SRCINVERT);
			}
			else  // 未选中状态
			{
				putimage(px, py, img_mm + 1, NOTSRCERASE);
				putimage(px, py, img_mm, SRCINVERT);
			}
			// 按钮文本居中
			outtextxy((w - textwidth(ch[i + 1].c_str())) / 2 + px,
				(h - textheight(ch[i + 1].c_str())) / 2 + py,
				ch[i + 1].c_str());
		}

		// 绘制副按钮（玩法说明、历史最高分、团队说明、游戏设置）
		settextstyle(30, 0, "微软雅黑");
		for (int i = 0; i < 4; i++)
		{
			int px = 0, py = 300 + i * 50;  // 按钮位置
			if (i + 5 == cur)  // 选中状态
			{
				putimage(px, py, img_mn + 3, NOTSRCERASE);
				putimage(px, py, img_mn + 2, SRCINVERT);
			}
			else  // 未选中状态
			{
				putimage(px, py, img_mn + 1, NOTSRCERASE);
				putimage(px, py, img_mn, SRCINVERT);
			}
			// 按钮文本居中
			outtextxy((w / 2 - textwidth(ch[i + 5].c_str())) / 2 + px,
				(h / 2 - textheight(ch[i + 5].c_str())) / 2 + py,
				ch[i + 5].c_str());
		}

		// 绘制标题
		settextstyle(80, 0, "微软雅黑");
		outtextxy(310, 40, ch[0].c_str());
		FlushBatchDraw();  // 刷新画面


		// 处理用户输入（选择按钮）
		ExMessage msg;
		if (peekmessage(&msg, EX_KEY))  // 检测键盘消息
		{
			if (msg.message == WM_KEYDOWN)  // 按键按下
			{
				int key = msg.vkcode;
				if (key == 'W') {  // 上移选择
					if (cur > 1) cur--;
				}
				if (key == 'S') {  // 下移选择
					if (cur < 8) cur++;
				}
				if (key == 'A') {  // 切换到副按钮
					if (cur < 5) cur = 5;
				}
				if (key == 'D') {  // 切换到主按钮
					if (cur > 4) cur = 1;
				}
				// 回车确认
				if (key == VK_RETURN) {
					switch (cur)
					{
					case 1:  // 开始游戏
						EndBatchDraw();  // 结束菜单批量绘制
						flushmessage();
						_initGame();      // 初始化游戏
						_gameLoopView();  // 进入游戏循环
						BeginBatchDraw();  // 重新开启菜单批量绘制
						break;
					case 4:  // 退出游戏
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
					default:  // 其他功能未实现
						break;
					}
				}
			}
		}
	}
	EndBatchDraw();  // 结束批量绘制
}

void _renderGameView() {
	setbkcolor(WHITE);  // 窗口背景色
	cleardevice();      // 刷新窗口

	// 绘制游戏区域边框（20x20网格，每格26像素）
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(150, 40, 150 + 20 * 26, 40 + 20 * 26);  // 游戏区域边框：520x520像素

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

void _gameLoopView() {
	BeginBatchDraw();

	// 立即渲染一次，确保游戏开始时显示画面
	_renderGameView();

	// 游戏主循环
	while (1)
	{
		checkInput();  // 检测用户输入
		int collision = _checkCollision();  // 判断碰撞类型

		switch (collision) {
		case 0:  // 无碰撞：移动蛇
			moveSnake();
			break;
		case 1:  // 碰撞边界/蛇身/墙：游戏结束
			EndBatchDraw();  // 结束批量绘制
			_endView();
			return;
		case 2:  // 吃到食物：处理吃食物并生成新食物
			_handleEat();
			_generateFood();
			break;
		}
		_renderGameView();  // 渲染当前画面
		Sleep(_moveInterval);  // 按间隔延时（控制速度）
	}
	EndBatchDraw();  // 结束批量绘制（循环退出时执行）
}

void exitView() {
	//while (1) {
	//	std::cout << "是否退出游戏?(空格退出,回车返回菜单)\n";  // 展示选项
	//	int choice = _getch();  // 接受用户输入（不回显）
	//	if (choice == 32)  // 空格（ASCII 32）：退出程序
	//		exit(0);
	//	else if (choice == 13)  // 回车（ASCII 13）：返回主菜单
	//		mainMenuView();
	//	else  // 其他输入：重新询问
	//		continue;
	//}

	setbkcolor(RGB(133, 194, 77));
	cleardevice();
	settextstyle(28, 0, "黑体");
	settextcolor(WHITE);

	//尝试加载图片
	IMAGE exitbg;
	loadimage(&exitbg, "./exitView.png", 800, 600);

	// 游戏结束界面循环
	while (true)
	{
		/* 展示内容 */
		string str1 = "是否退出游戏?";
		string str2 = "空格退出,回车返回菜单";
		cleardevice();
		putimage(0, 0, &exitbg);
		outtextxy(350, 175, str1.c_str());  // 居中显示标题

		// 显示本局分数
		outtextxy(350, 215, str2.c_str());

		// 显示操作提示
		/*settextstyle(20, 0, "宋体");
		outtextxy(400 - textwidth("按回车返回主菜单") / 2, 400, "按回车返回主菜单");*/

		/* 等待回车 */
		if (_getch() == 13)  // 回车键
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
	int xs_flag = 0;  // 选中按钮索引（0:继续游戏, 1:使用道具, 2:模式选择, 3:返回菜单）

	// 尝试加载暂停界面背景（失败不影响功能）
	IMAGE pausebg;
	loadimage(&pausebg, "./pauseView.png");

	// 暂停界面循环
	while (1) {
		// 绘制背景
		cleardevice();
		if (pausebg.getwidth() > 0)
			putimage(0, 0, &pausebg);

		// 绘制标题与信息
		settextstyle(40, 0, "黑体");
		outtextxy(340, 40, "游戏已暂停");

		settextstyle(40, 0, "宋体");
		char buf[64];
		sprintf_s(buf, "当前分数：%d", currentScore);
		outtextxy(320, 100, buf);

		// 绘制按钮（未选中状态）
		button(256, 224, 308, 76, "继续游戏", 40, RGB(171, 171, 171));
		button(256, 321, 308, 76, "使用道具", 40, RGB(171, 171, 171));
		button(256, 418, 308, 76, "模式选择", 40, RGB(171, 171, 171));
		button(256, 515, 308, 76, "返回菜单", 40, RGB(171, 171, 171));

		// 高亮显示选中的按钮
		switch (xs_flag) {
		case 0:
			button(256, 224, 308, 76, "继续游戏", 40, WHITE);
			break;
		case 1:
			button(256, 321, 308, 76, "使用道具", 40, WHITE);
			break;
		case 2:
			button(256, 418, 308, 76, "模式选择", 40, WHITE);
			break;
		case 3:
			button(256, 515, 308, 76, "返回菜单", 40, WHITE);
			break;
		}

		FlushBatchDraw();


		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w' || ch == 'W') {  // 上选
				xs_flag = (xs_flag - 1 + 4) % 4;
			}
			else if (ch == 's' || ch == 'S') {  // 下选
				xs_flag = (xs_flag + 1) % 4;
			}
			else if (ch == 32 || ch == 13) {  // 空格/回车确认
				if (xs_flag == 0) {  // 继续游戏
					flushmessage();
					return;
				}
				else if (xs_flag == 3) {  // 返回菜单
					flushmessage();
					EndBatchDraw();
					_mainMenuView();
					BeginBatchDraw();
					return;
				}
				// 其他功能未实现
			}
		}

		Sleep(50);  // 延时
	}
}

void _endView() {
	//cout << "endView works!\n";				//测试gameLoopView()
	//cout << "按任意键结束程序!\n";
	//_getch();
	//exit(0);

	setbkcolor(RGB(49, 124, 74));
	cleardevice();
	settextstyle(28, 0, "黑体");
	settextcolor(WHITE);

	//尝试加载图片
	IMAGE endbg;
	loadimage(&endbg, "./endView1.png", 800, 600);

	// 游戏结束界面循环
	while (true)
	{
		/* 展示内容 */
		string str = to_string(currentScore);
		cleardevice();
		putimage(0, 0, &endbg);
		outtextxy(450, 175, str.c_str());  // 居中显示标题

		// 显示本局分数
		outtextxy(450, 215, str.c_str());

		// 显示操作提示
		/*settextstyle(20, 0, "宋体");
		outtextxy(400 - textwidth("按回车返回主菜单") / 2, 400, "按回车返回主菜单");*/

		/* 等待回车 */
		if (_getch() == 13)  // 回车键
		{
			flushmessage();
			_mainMenuView();
			return;
		}
	}
}

void button(int x, int y, int w, int h, const char* text, int texth, COLORREF color) {
	setbkmode(TRANSPARENT);
	setfillcolor(color);       // 按钮填充色
	setlinecolor(BLACK);       // 边框色
	setlinestyle(PS_SOLID, 5); // 边框样式
	fillroundrect(x, y, x + w, y + h, 10, 10);  // 绘制圆角矩形按钮

	// 绘制按钮文本
	settextstyle(texth, 0, "黑体");
	settextcolor(BLACK);
	int tw = textwidth(text);  // 文本宽度
	int th = textheight(text); // 文本高度
	int tx = x + w / 2 - tw / 2;  // 文本x坐标（居中）
	int ty = y + h / 2 - th / 2;  // 文本y坐标（居中）
	outtextxy(tx, ty, text);      // 绘制文本
}


void _introductionView()
{
	flushmessage();
	setbkcolor(WHITE);
	cleardevice();

	//尝试加载图片
	IMAGE introductionbg;
	loadimage(&introductionbg, "./introduction.png", 800, 600);

	// 团队介绍界面循环
	while (true)
	{
		/* 展示内容 */
		cleardevice();
		putimage(0, 0, &introductionbg);
		/*Sleep(1000);*/

		// 显示操作提示
		/*settextstyle(20, 0, "宋体");
		outtextxy(400 - textwidth("按回车返回主菜单") / 2, 400, "按回车返回主菜单");*/

		/* 等待回车 */
		if (_getch() == 13)  // 回车键
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
	settextstyle(28, 0, "黑体");
	settextcolor(BLACK);

	//尝试加载图片
	IMAGE insbg;
	loadimage(&insbg, "./instruction.jpg", 800, 600);

	// 游戏结束界面循环
	while (true)
	{
		/* 展示内容 */
		string str = "按回车返回主菜单";
		cleardevice();
		putimage(0, 0, &insbg);

		outtextxy(350, 500, str.c_str());
		// 显示操作提示

		/* 等待回车 */
		if (_kbhit())  // 回车键
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