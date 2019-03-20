#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <tchar.h>

typedef struct postion {
	int x;
	int y;
}Foodpostion;
typedef struct Snakemessage {
	int x;
	int y;
}Snakepostion;
#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000)//按下1，不按0
Foodpostion food;                         //当前食物位置
Snakepostion snakeArr[100];               //当前小蛇每个点的信息
int length;                              //当前小蛇长度

void init();                             //初始化界面
void gamebegin();                        //游戏启动
void gameplay();                         //玩游戏具体过程
void close();                            //释放资源
void drawsnake(Snakepostion *snp);        //画蛇
void drawfood();                      //画食物
void clearfood();                     //吃掉食物
void clearsnake(Snakepostion snp[]);  //清除小蛇，准备画新
void drawscore(int score);                   //分数
void drawwindows();                         //绘制边框
void drawtime(int sec);                            //绘制时间
void main() {
	init();                             //初始化界面
	gamebegin();                        //游戏启动
	gameplay();                         //玩游戏具体过程
	close();                            //释放资源
}
void init() {
	initgraph(700, 605);
}
void gamebegin() {
	//绘制边框
	drawwindows();
	/*setlinecolor(RGB(50, 50, 50));//边框颜色
	setlinestyle(PS_SOLID, 10);  //边框为实线，粗细为10像素，此函数后两个参数有默认值，不传
	fillrectangle(0, 0, 475, 600);//左上角和右下角（x,y），此坐标是线宽的中轴线的坐标，外坐标-5 内+5*/
	//绘制初始小蛇
	setlinestyle(PS_SOLID, 1);//改线条粗细
	//setlinecolor(RGB(0, 0, 0));//改线条颜色
	
	length = 5;
	for (int i = 0; i < 5; i++) {
		snakeArr[i].x = 200;
		snakeArr[i].y = 200+i*10;
	}
	drawsnake(snakeArr);
	//绘制初始食物
	drawfood();
	//绘制分数
	drawscore(0);
	//绘制时间
	drawtime(30);
	
}
void gameplay() {
	for (int j = 299; j >= 0; j--) {//监听键盘
		if (j % 10 == 0) {
			drawtime(j / 10);
		}
		if (KEY_DOWN(VK_UP) && snakeArr[0].y > 10) {//上边界
			clearsnake(snakeArr);
			for (int i = length - 1; i > 0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x;
			snakeArr[0].y = snakeArr[0].y - 10;
			drawsnake(snakeArr);
		}
		if (KEY_DOWN(VK_DOWN) && snakeArr[length -1].y<590) {//下边界
			clearsnake(snakeArr);
			for (int i = length - 1; i >0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x;
			snakeArr[0].y = snakeArr[0].y + 10;
			drawsnake(snakeArr);
			
		}
		if (KEY_DOWN(VK_LEFT) && snakeArr[0].x>10) {//左边界
			clearsnake(snakeArr);
			for (int i = length - 1; i > 0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x-10;
			snakeArr[0].y = snakeArr[0].y;
			drawsnake(snakeArr);
		}
		if (KEY_DOWN(VK_RIGHT) && snakeArr[0].x<470) {//右边界
			clearsnake(snakeArr);
			for (int i = length - 1; i > 0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x + 10;
			snakeArr[0].y = snakeArr[0].y;
			drawsnake(snakeArr);
		}
		
		if ((food.x == snakeArr[0].x) && (food.y == snakeArr[0].y)) {
			snakeArr[length].x = snakeArr[length - 1].x;
			snakeArr[length].y = snakeArr[length - 1].y+10;
			length++;
			clearfood();
			drawfood();
			
			
			clearsnake(snakeArr);
			drawsnake(snakeArr);
		}
		
		Sleep(100);
		drawscore(length * 10 - 50);
	}
	cleardevice();
	TCHAR str[30];
	settextcolor(RGB(255, 0, 0));//设置文字颜色
	settextstyle(50, 0, _T("黑体"));//设置文字大小，粗细，字体
	_stprintf(str, _T("GAME OVER"));
	outtextxy(300, 250, str);
	drawscore(length * 10 - 50);
	Sleep(2000);
}
void close() {
	_getch();
	closegraph();
}
void drawsnake(Snakepostion snp[]){
	setlinecolor(RGB(0,0,0));
	setfillcolor(RGB(255, 50, 50));
	fillrectangle(snp[0].x, snp[0].y, snp[0].x + 10, snp[0].y + 10);
	setfillcolor(RGB(0, 0, 0));
	for (int i =1; i <length; i++) {
		fillrectangle(snp[i].x, snp[i].y, snp[i].x + 10, snp[i].y + 10);
	}
}
void drawfood() {
	srand((unsigned)time(NULL));//随机数初始化
	food.x = (rand() % 40) * 10 + 10;//防止食物出现在边框上，+10
	food.y = (rand() % 40) * 10 + 10;
	setlinestyle(PS_SOLID, 1);//改线条粗细
	setfillcolor(RGB(0,0,0));
	fillrectangle(food.x, food.y, food.x + 10, food.y + 10);
}
void clearfood(){
	setfillcolor(RGB(255,255,255));
	fillrectangle(food.x, food.y, food.x + 10, food.y + 10);
}
void clearsnake(Snakepostion snp[]) {
	setlinecolor(RGB(255,255,255));
	setfillcolor(RGB(255, 255, 255));
	for (int i = 0; i <length; i++) {
		fillrectangle(snp[i].x, snp[i].y, snp[i].x + 10, snp[i].y + 10);
	}
}
void drawscore(int score) {
	TCHAR str[30];
	TCHAR s[30];
	TCHAR st[30];
	settextcolor(RGB(255, 0, 0));//设置文字颜色
	settextstyle(25, 0, _T("黑体"));//设置文字大小，粗细，字体							
	_stprintf(str, _T("Your score:"));
	outtextxy(500, 50, str);
	_stprintf(s, _T("%3d"),score);
	outtextxy(530, 80, s);
	_stprintf(st, _T("WECLOME!"));
	outtextxy(520,450, st);
}
void drawwindows() {
	setlinecolor(RGB(50, 50, 50));//边框颜色
	setlinestyle(PS_SOLID, 10);  //边框为实线，粗细为10像素，此函数后两个参数有默认值，不传
	fillrectangle(0, 0, 475, 600);//左上角和右下角（x,y），此坐标是线宽的中轴线的坐标，外坐标-5 内+5
}
void drawtime(int sec) {
	TCHAR str[30];
	settextcolor(RGB(255, 255, 0));//设置文字颜色
	settextstyle(25, 0, _T("黑体"));//设置文字大小，粗细，字体
	_stprintf(str, _T("剩余时间： %2ds"), sec);
	outtextxy(500, 250, str);
}