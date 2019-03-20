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
#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000)//����1������0
Foodpostion food;                         //��ǰʳ��λ��
Snakepostion snakeArr[100];               //��ǰС��ÿ�������Ϣ
int length;                              //��ǰС�߳���

void init();                             //��ʼ������
void gamebegin();                        //��Ϸ����
void gameplay();                         //����Ϸ�������
void close();                            //�ͷ���Դ
void drawsnake(Snakepostion *snp);        //����
void drawfood();                      //��ʳ��
void clearfood();                     //�Ե�ʳ��
void clearsnake(Snakepostion snp[]);  //���С�ߣ�׼������
void drawscore(int score);                   //����
void drawwindows();                         //���Ʊ߿�
void drawtime(int sec);                            //����ʱ��
void main() {
	init();                             //��ʼ������
	gamebegin();                        //��Ϸ����
	gameplay();                         //����Ϸ�������
	close();                            //�ͷ���Դ
}
void init() {
	initgraph(700, 605);
}
void gamebegin() {
	//���Ʊ߿�
	drawwindows();
	/*setlinecolor(RGB(50, 50, 50));//�߿���ɫ
	setlinestyle(PS_SOLID, 10);  //�߿�Ϊʵ�ߣ���ϸΪ10���أ��˺���������������Ĭ��ֵ������
	fillrectangle(0, 0, 475, 600);//���ϽǺ����½ǣ�x,y�������������߿�������ߵ����꣬������-5 ��+5*/
	//���Ƴ�ʼС��
	setlinestyle(PS_SOLID, 1);//��������ϸ
	//setlinecolor(RGB(0, 0, 0));//��������ɫ
	
	length = 5;
	for (int i = 0; i < 5; i++) {
		snakeArr[i].x = 200;
		snakeArr[i].y = 200+i*10;
	}
	drawsnake(snakeArr);
	//���Ƴ�ʼʳ��
	drawfood();
	//���Ʒ���
	drawscore(0);
	//����ʱ��
	drawtime(30);
	
}
void gameplay() {
	for (int j = 299; j >= 0; j--) {//��������
		if (j % 10 == 0) {
			drawtime(j / 10);
		}
		if (KEY_DOWN(VK_UP) && snakeArr[0].y > 10) {//�ϱ߽�
			clearsnake(snakeArr);
			for (int i = length - 1; i > 0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x;
			snakeArr[0].y = snakeArr[0].y - 10;
			drawsnake(snakeArr);
		}
		if (KEY_DOWN(VK_DOWN) && snakeArr[length -1].y<590) {//�±߽�
			clearsnake(snakeArr);
			for (int i = length - 1; i >0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x;
			snakeArr[0].y = snakeArr[0].y + 10;
			drawsnake(snakeArr);
			
		}
		if (KEY_DOWN(VK_LEFT) && snakeArr[0].x>10) {//��߽�
			clearsnake(snakeArr);
			for (int i = length - 1; i > 0; i--) {
				snakeArr[i].x = snakeArr[i - 1].x;
				snakeArr[i].y = snakeArr[i - 1].y;
			}
			snakeArr[0].x = snakeArr[0].x-10;
			snakeArr[0].y = snakeArr[0].y;
			drawsnake(snakeArr);
		}
		if (KEY_DOWN(VK_RIGHT) && snakeArr[0].x<470) {//�ұ߽�
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
	settextcolor(RGB(255, 0, 0));//����������ɫ
	settextstyle(50, 0, _T("����"));//�������ִ�С����ϸ������
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
	srand((unsigned)time(NULL));//�������ʼ��
	food.x = (rand() % 40) * 10 + 10;//��ֹʳ������ڱ߿��ϣ�+10
	food.y = (rand() % 40) * 10 + 10;
	setlinestyle(PS_SOLID, 1);//��������ϸ
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
	settextcolor(RGB(255, 0, 0));//����������ɫ
	settextstyle(25, 0, _T("����"));//�������ִ�С����ϸ������							
	_stprintf(str, _T("Your score:"));
	outtextxy(500, 50, str);
	_stprintf(s, _T("%3d"),score);
	outtextxy(530, 80, s);
	_stprintf(st, _T("WECLOME!"));
	outtextxy(520,450, st);
}
void drawwindows() {
	setlinecolor(RGB(50, 50, 50));//�߿���ɫ
	setlinestyle(PS_SOLID, 10);  //�߿�Ϊʵ�ߣ���ϸΪ10���أ��˺���������������Ĭ��ֵ������
	fillrectangle(0, 0, 475, 600);//���ϽǺ����½ǣ�x,y�������������߿�������ߵ����꣬������-5 ��+5
}
void drawtime(int sec) {
	TCHAR str[30];
	settextcolor(RGB(255, 255, 0));//����������ɫ
	settextstyle(25, 0, _T("����"));//�������ִ�С����ϸ������
	_stprintf(str, _T("ʣ��ʱ�䣺 %2ds"), sec);
	outtextxy(500, 250, str);
}