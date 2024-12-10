#ifndef DONK_H
#define DONK_H
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include<sstream>
using namespace std;
#define BUF_SIZE 8192
/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 *
 *
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            佛祖保佑       永不宕机     永无BUG
 */
 /**
/*窗口函数*/
void SIGN();
void admin_GUI();
void user_GUI();
void TELLerror();
/*其他函数*/
void SMemoCL(LPVOID& ShareMemoryPointer);//清空共享内存
void SMemoinfoCY(char* Buffer, LPVOID& ShareMemoryPointer);//将共享内存中的内容拷贝出来
#endif //DONK_H