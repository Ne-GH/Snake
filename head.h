#ifndef _HEAD_H
#define _HEAD_H
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct pos{
    int x;
    int y;
}pos,*ppos;

typedef struct body {
    int x;
    int y;
    struct body* next;
}*pbody,body;

typedef struct snake {
    int count;//蛇身体数量
    int direction;//控制方向,0左,1下,2上,3右
    pbody head;
}snake,*psnake;

typedef struct food {
    int statu;
    int x;
    int y;
}food,*pfood;
void Handleinit(HANDLE);//初始化控制台

void coloer(HANDLE,int);//改变之后的文本颜色

void movecursor(HANDLE,pos);//移动光标

void printfborder(HANDLE);//打印边界

snake snakeinit();//初始化蛇

void printfsnake(HANDLE, snake);//打印蛇

void clearsnake(HANDLE, snake);//清除蛇

body resnake(snake sn);//移动蛇的数据

void movesnake(HANDLE, psnake,int,pfood);//移动蛇

food foodinit();//食物初始化

void randfood(HANDLE, pfood);//随机食物

void printffood(HANDLE, food);

void collision(HANDLE,snake);//碰撞检测

void delect(snake);//释放蛇的内存

void over(HANDLE,snake);

void printfother(HANDLE, snake);

void printfhint(HANDLE);

void printfspace(HANDLE,snake);


            //蛇,食物,key
void AutoEat(snake,food,int*);

#endif