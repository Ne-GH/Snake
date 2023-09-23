#include"head.h"
int main(){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    
	snake sn = snakeinit();
	printfsnake(console, sn);


	Handleinit(console);//初始化控制窗口
    printfborder(console);
	printfhint(console);


	pfood fo = (pfood)malloc(sizeof(food));
	*fo = foodinit();

    int key;
	while (1) {
			fflush(stdin);
			body temp;
			body first = *sn.head;
			body second = *(sn.head->next);
			randfood(console, fo);
			printffood(console, *fo);
			//key = getch();
		if (_kbhit()) {
			switch (key = getch()) {
			case 27:
				over(console,sn);
				break;
				//0左, 1下, 2上, 3右
			case 32:
				printfspace(console,sn);
				break;
			case 72://上
				if (second.y < first.y)
					break;
				sn.direction = 2;
				break;
			case 75://左
				if (second.x < first.x)
					break;
				sn.direction = 0;
				break;
			case 77://右
				if (second.x > first.x)
					break;
				sn.direction = 3;
				break;
			case 80://下
				if (second.y > first.y)
					break;
				sn.direction = 1;
				break;

			case 9://Tab
				
				break;


			default:
				continue;
			}
			movesnake(console, &sn, sn.direction, fo);
			collision(console,sn);
		}
		else {
			movesnake(console, &sn, sn.direction, fo);
			collision(console,sn);
		}
		fflush(stdin);
		Sleep(200);
	
	}
    return 0;
}