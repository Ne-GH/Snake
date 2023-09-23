#include"head.h"

void coloer(HANDLE console,int n) {
	SetConsoleTextAttribute(console,n);
	return;
}

//窗口初始化
void Handleinit(HANDLE console){
	SetConsoleTitle("贪吃蛇");
	CONSOLE_CURSOR_INFO cci = { 1 ,FALSE};
	SetConsoleCursorInfo(console, &cci);
  
	COORD buf = {121 ,36};
	SetConsoleScreenBufferSize(console, buf);//改变缓冲区
	SMALL_RECT sr = { 0, 0, 120, 35};
	SetConsoleWindowInfo(console,TRUE, &sr);//改变窗口大小
	return;
}
//移动光标
void movecursor(HANDLE console,pos pos){
	COORD p;
	p.X = pos.x;
	p.Y = pos.y;
	SetConsoleCursorPosition(console, p);
	return ;
}
//打印边框
void printfborder(HANDLE console){
	coloer(console, 0x9);
	for(int i = 0;i < 35; ++ i){
		movecursor(console,(pos){0,i});
		printf("■");



		movecursor(console,(pos){80,i});
		printf("■┃");
		movecursor(console,(pos){119,i});
		printf("┃");
	}
	movecursor(console,(pos){82,0});
	printf("  ");
	movecursor(console,(pos){118,0});
	printf("  ");
	for(int i = 0;i <= 80 ; i += 2){
		movecursor(console ,(pos){i,0});
		printf("■");
		movecursor(console,(pos){i,35});
		printf("■");
	}

	return;
}
//初始化蛇
snake snakeinit() {
	snake sn;
	sn.count = 3;
	sn.head = (pbody)malloc(sizeof(body));
	pbody temp = sn.head;
	temp->x = 30;
	temp->y = 20;
	sn.direction = 3;
	for (int i = 1; i <= 2; ++ i) {
		temp->next = (pbody)malloc(sizeof(body));
		temp = temp->next;
		temp->x = 30 - i * 2;
		temp->y = 20;
	}
	temp ->next = NULL;
	return sn;
}
//打印蛇
void printfsnake(HANDLE console, snake sn) {
	coloer(console,14);
	pbody temp = sn.head;
	pos te;
	while (temp != NULL) {
		te.x = temp->x;
		te.y = temp->y;
		movecursor(console, te);
		temp = temp->next;
		printf("■");
	}
	return;
}
//清除蛇
void clearsnake(HANDLE console, snake sn) {
	pbody temp = sn.head;
	pos te;
	while(temp){
		te.x = temp->x;
		te.y = temp->y;
		movecursor(console, te);
		printf("  ");
		temp = temp->next;
	}
	return;
}
//蛇中各节点坐标后移
body resnake(snake sn) {//链表内除head其余数据后移
	pbody temp = sn.head;
	while (temp->next->next){
		temp = temp->next;
	}
	body end;
	end.x = temp->next->x;
	end.y = temp->next->y;
	free(temp->next);
	temp->next = NULL;
	pbody te = (pbody)malloc(sizeof(body));
	te->x = sn.head->x;
	te->y = sn.head->y;
	te->next = sn.head->next;
	sn.head->next = te;
	return end;
}
//移动蛇,并打印
void movesnake(HANDLE console, psnake sn, int n ,pfood fo) {
	clearsnake(console, *sn);
	body temp;
	temp = resnake(*sn);
	//0左, 1下, 2上, 3右
	switch (n) {
	case 0:
		sn->head->x -= 2;
		break;
	case 1:
		sn->head->y += 1;
		break;
	case 2:
		sn->head->y -= 1;
		break;
	case 3:
		sn->head->x += 2;
		break;
	}
	if ((sn->head->x == fo->x) && (sn->head->y == fo->y)) {
		pbody t;
		t = sn->head;
		while (t->next) {
			t = t->next;
		}
		t->next= (pbody)malloc(sizeof(body));
		t->next->next = NULL;
		t->next->x = temp.x;
		t->next->y = temp.y;
		fo->statu = 0;
		sn->count++;
	}
	printfsnake(console, *sn);
	printfother(console, *sn);
	return ;
}

food foodinit() {
	food temp;
	temp.x = 0;
	temp.y = 0;
	temp.statu = 0;//没有存在的食物
	return temp;
}

void randfood(HANDLE console, pfood fo) {
	if (fo->statu == 0) {
		srand((time(NULL)));
		fo->x = (rand() % 39 + 1)*2;
		fo->y = rand() % 34 + 1;
		coloer(console, 0xc);
		printffood(console, *fo);
		fo->statu = 1;
	}
	else if (fo->statu == 1)
		return;
	//x  2->78
	//   1->39
	//y  1->34
	return;
}
void printffood(HANDLE console, food fo) {
	coloer(console, 0xc);
	movecursor(console, (pos) { fo.x, fo.y });
	printf("■");
	return;
}

void collision(HANDLE console,snake sn) {//碰撞检测
	pbody temp = sn.head ->next;
	if (sn.head->y <= 0 ||
		sn.head->y >= 35 ||
		sn.head->x >= 80 ||
		sn.head->x <= 0)
		over(console, sn);
	while (temp) {//自身碰撞
		if (sn.head->x == temp->x && sn.head->y == temp->y) {
			over(console,sn);
		}
		temp = temp->next;
	}
	return;
}

void delectsnake(snake sn) {
	pbody temp = sn.head;
	pbody te = sn.head->next;
	while (temp->next) {
		free(temp);
		temp = te;
		te = te->next;
	}
	free(temp);

	return;
}
void over(HANDLE console,snake sn) {
	delectsnake(sn);
	movecursor(console, (pos) {30,15});
	coloer(console, 0xd);
	printf("游戏结束,按任意键退出");
	getchar();
	exit(1);

	return;
}

void printfother(HANDLE console, snake sn) {
	coloer(console, 0xd);
	movecursor(console, (pos) { 95, 3 });
	printf("蛇的长度:");
	printf("%d", sn.count);
	return;
}

void printfhint(HANDLE console) {
	coloer(console, 0xb);
	movecursor(console, (pos) { 84, 9 });
	printf("﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌");
	movecursor(console, (pos) { 85, 11 });
	printf("使用方向键控制蛇移动的方向");
	movecursor(console, (pos) { 85, 12 });
	printf("↑:上");
	movecursor(console, (pos) { 85, 13 });
	printf("↓:下");
	movecursor(console, (pos) { 85, 14 });
	printf("←:左");
	movecursor(console, (pos) { 85, 15 });
	printf("→:右");
	movecursor(console, (pos) { 85, 17 });
	printf("ESC:退出游戏");
	movecursor(console, (pos) { 85, 18 });
	printf("Space:暂停游戏");
	movecursor(console, (pos) { 85, 19 });
	printf("Tab:自动觅食");
	return;
}


void printfspace(HANDLE console,snake sn) {
	coloer(console, 0x5);
	movecursor(console, (pos) { 30, 15 });
	printf("游戏暂停,按任意键继续");
	char temp;
	temp = getch();
	movecursor(console, (pos) { 30, 15 });
	printf("                     ");
	printfsnake(console, sn);
	return;
}

void AutoEat(snake snake,food food,int *pkey){
	
}