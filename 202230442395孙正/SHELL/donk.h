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
 *            ���汣��       ����崻�     ����BUG
 */
 /**
/*���ں���*/
void SIGN();
void admin_GUI();
void user_GUI();
void TELLerror();
/*��������*/
void SMemoCL(LPVOID& ShareMemoryPointer);//��չ����ڴ�
void SMemoinfoCY(char* Buffer, LPVOID& ShareMemoryPointer);//�������ڴ��е����ݿ�������
#endif //DONK_H