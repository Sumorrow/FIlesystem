#include"donk.h"
/*指令空间，用于客户端向服务器传输指令*/
//创建共享文件句柄
HANDLE SHARED_FILESPACE = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "SHARED_FILESPACE");
//映射缓存区视图，得到指向共享内存的指针
LPVOID SHARED_FILEPTR = MapViewOfFile(SHARED_FILESPACE, FILE_MAP_ALL_ACCESS, 0,0,BUF_SIZE);
/*权限空间，用于告知服务器用户的身份*/
HANDLE SHARED_FILEQUL = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE,"SHARED_FILEQUL" );
//映射缓存区视图，得到指向共享内存的指针
LPVOID SHARED_FILEQULPTR = MapViewOfFile(SHARED_FILEQUL, FILE_MAP_ALL_ACCESS,0,0,BUF_SIZE);


void SIGN()
{
begin:
	ExMessage m;//定义鼠标变量
		
	/*初始化*/
	initgraph(640, 360); //定义画布大小，宽度，长度
	setbkcolor(BLACK);//设置背景颜色
	cleardevice();//刷新
	// 加载图像
	IMAGE img;
	loadimage(&img, _T("F:\\ideaoo\\os_linuxmodelafter_filesystem\\srcReference\\background.png"));  
	// 设置图像显示的位置
	int x = 0; 
	int y = 0; 
	putimage(x, y, &img);
	/*设置框和框中的信息*/
	char account[20] = {};
	char password[15] = {};
	fstream f;
	setlinecolor(WHITE);
	rectangle(160, 100, 480, 140);//账号框
	rectangle(160, 190, 480, 230);//密码框
	rectangle(160, 280, 480, 320);//登录框
	RECT r1 = { 160,280,480,320 };
	settextcolor(WHITE);
	drawtext(("SIGN IN"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//登录文本
	RECT r2 = {160, 100, 480, 140};
	settextcolor(WHITE);
	drawtext(("ACCOUNT"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//账号输入
	RECT r3 = { 160, 190, 480, 230 };
	settextcolor(WHITE);
	drawtext(("PASSWORD"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//密码输入
	/*设置文本*/
	settextstyle(16, 0, ("宋体"));//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextcolor(WHITE);
	settextstyle(12, 0, ("宋体"));
	settextstyle(20, 0, ("楷体"));
	outtextxy(200, 50, ("IT'S MY GO"));


	/*按钮设定*/

	while (1) {
		m = getmessage(EM_MOUSE | EM_KEY);
		if (m.x >= 160 && m.y >= 280 && m.x <= 480 && m.y <= 320) {
			if (m.message == WM_LBUTTONUP) {//左键弹起时			
				if (std::string(account) == "cmd" && std::string(password) == "0000") {//系统用户
					admin_GUI();
					goto begin;
				}			
				else if (std::string(account) == "usr" && std::string(password) == "1234") {//普通用户
					user_GUI();
					goto begin;
				}
				else {
					TELLerror();
					goto begin;
				}
			}	
		}	
		else if (m.x >= 160 && m.y >= 100 && m.x <= 480 && m.y <= 140) {
			if (m.message == WM_LBUTTONUP)
			{
				InputBox(account, 20, "ACCOUNT");
			}
		}
		else if (m.x >= 160 && m.y >= 190 && m.x <= 480 && m.y <= 230) 		
		{
			if (m.message == WM_LBUTTONUP)				
			{
				InputBox(password, 15, "PASSWORD");
			}
		}
	}
	// 关闭图形窗口
	closegraph();
	return;
}
void TELLerror()
{
	settextstyle(12, 0, "宋体");
	settextcolor(WHITE);
	outtextxy(200, 157, "ERROR");
	settextcolor(BLACK);
	Sleep(300);
	clearrectangle(200, 157, 300, 170);
}
void admin_GUI()
{
begin:
	ExMessage m;//定义鼠标变量
	char INS_T[BUF_SIZE] = {};
	char password[15] = {};
	fstream f;
	/*初始化*/
	initgraph(550, 350); //定义画布大小，宽度，长度
	setbkcolor(BLACK);//设置背景颜色
	cleardevice();//刷新
	// 加载图像
	IMAGE img;
	loadimage(&img, _T("F:\\ideaoo\\os_linuxmodelafter_filesystem\\srcReference\\background.png"));
	// 设置图像显示的位置
	int x = 0; // 图像的 x 坐标
	int y = 0; // 图像的 y 坐标
	// 显示图像
	putimage(x, y, &img);
	/*设置框和框中的信息*/
	setlinecolor(BLACK);
	rectangle(15, 40, 535, 270);//信息框
	rectangle(15, 310, 450, 330);//输入文本框
	rectangle(465, 15, 535, 35);//返回框	
	rectangle(465, 280, 535, 300);//输入框
	rectangle(465, 310, 535, 330);//确认框	
	/*设置文本*/
	RECT r1 = { 465,280, 535, 300 };
	settextcolor(WHITE);
	drawtext(_T(""), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//输入指令	
	RECT r2 = { 465, 310, 535, 330 };
	settextcolor(WHITE);
	drawtext(_T("确认"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//确认指令	
	RECT r3 = { 465, 15, 535, 35 };
	settextcolor(WHITE);
	drawtext(_T("返回"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回上一层
	settextstyle(16, 0, "宋体");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextcolor(WHITE);
	settextstyle(16, 0, "楷体");//设置文字大小 格式 
	outtextxy(15, 15, "当前目录:");
	outtextxy(90, 15, ("/cmd"));
	outtextxy(195, 285, "请输入指令");
	
	

	/*按钮设定*/
begin2:
	while (1) {

		m = getmessage(EM_MOUSE | EM_KEY);
		if (m.x >= 15 && m.y >= 310 && m.x <= 450 && m.y <= 330) {//指令输入
			if (m.message == WM_LBUTTONUP) {//左键弹起时
				if (m.message == WM_LBUTTONUP) {//左键弹起时
					InputBox(INS_T, BUF_SIZE, "请输入指令");
					clearrectangle(17, 312, 448, 328);
					outtextxy(17, 312, INS_T);
				}
			}
		}
		else if (m.x >= 465 && m.y >= 310 && m.x <= 535 && m.y <= 330) {			
			//确认
			if (m.message == WM_LBUTTONUP) {//左键弹起时
				clearrectangle(16, 41, 534, 269);//清空信息栏
				char RYInfrec[BUF_SIZE] = { 0 };//接受回复信息的数组
				//将数据拷贝到共享内存
				strcpy_s((char*)SHARED_FILEPTR, strlen(INS_T) + 1, INS_T);
				strcpy_s((char*)SHARED_FILEQULPTR, strlen("0") + 1, "0");
				/*对于write是否占用的判断*/
				HANDLE WSPACE = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "WSPACE");//不断地从回复信息空间中获取数据
				LPVOID WREC= MapViewOfFile(WSPACE, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				istringstream input_s(INS_T);
				string WFILE;
				if (WREC)WFILE = string((char*)WREC);
				else WFILE = "";

				string input_INS;
				string InputFile;
				input_s >> input_INS;
				input_s >> InputFile;
				if (InputFile == WFILE && input_INS == "write")
				{
					clearrectangle(90, 15, 200, 30);
					outtextxy(90, 15, RYInfrec);
					outtextxy(16, 41, "当前文件正在被其他用户写入，请稍后再试！");
					char NULLChar[] = "";//清空输入
					strcpy_s((char*)SHARED_FILEPTR, strlen(NULLChar) + 1, NULLChar);
					goto begin2;
				}

				while (1)
				{
					HANDLE ReplyInfoSpace = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "ReplyInfoSpace");//不断地从回复信息空间中获取数据
					LPVOID ReplyInfoRec = MapViewOfFile(ReplyInfoSpace, FILE_MAP_ALL_ACCESS, 0, 0, 0);
					if (!ReplyInfoRec)continue;
					if (strlen((char*)ReplyInfoRec))
					{
						SMemoinfoCY(RYInfrec, ReplyInfoRec);
						break;//如果获取到的数据，break
					}
				}

				clearrectangle(17, 42, 533, 268);//清空输入文本框

				/*输出返回的信息到信息框*/
				if (RYInfrec[0] == '/')
				{
					clearrectangle(90, 15, 200, 30);
					outtextxy(90, 15, RYInfrec);
					outtextxy(16, 41, "跳转成功！");
					continue;
				}
				int CountChangeLine = 1;
				string input_str(RYInfrec);
				for (int i = 0; i < input_str.length(); i++)
				{
					if (input_str[i] == '\n')
					{
						input_str[i] = ' ';
						CountChangeLine++;
					}
				}
				istringstream input_Sstr(input_str);
				for (int i = 0; i < CountChangeLine; i++)
				{
					input_Sstr >> input_str;
					outtextxy(16, 41 + 18 * i, input_str.c_str());
				}
			}
		}
		else if (m.x >= 465 && m.y >= 15 && m.x <= 535 && m.y <= 35) if (m.message == WM_LBUTTONUP)return;
	}


	/*解除指令空间文件映射*/
	UnmapViewOfFile(SHARED_FILEPTR);
	CloseHandle(SHARED_FILESPACE);

	return;
}
void user_GUI()
{
begin:
	ExMessage m;//定义鼠标变量
	char INS_T[BUF_SIZE] = {};
	char password[15] = {};
	fstream f;

	/*初始化*/
	initgraph(550, 350); //定义画布大小，宽度，长度
	setbkcolor(BLACK);//设置背景颜色
	cleardevice();//刷新	
	// 加载图像
	IMAGE img;
	loadimage(&img, _T("F:\\ideaoo\\os_linuxmodelafter_filesystem\\srcReference\\background2.png"));
	// 设置图像显示的位置
	int x = 0; // 图像的 x 坐标
	int y = 0; // 图像的 y 坐标
	// 显示图像
	putimage(x, y, &img);
	/*设置框和框中的信息*/
	setlinecolor(BLACK);
	rectangle(15, 40, 535, 270);//信息框
	rectangle(15, 310, 450, 330);//输入文本框
	rectangle(465, 15, 535, 35);//返回框
	rectangle(465, 280, 535, 300);//输入框
	rectangle(465, 310, 535, 330);//确认框
	/*设置文本*/
	RECT r1 = { 465,280, 535, 300 };
	settextcolor(WHITE);
	drawtext(_T(""), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//输入指令
	RECT r2 = { 465, 310, 535, 330 };
	settextcolor(WHITE);
	drawtext(_T("确认"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//确认指令
	RECT r3 = { 465, 15, 535, 35 };
	settextcolor(WHITE);
	drawtext(_T("返回"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//返回上一层
	settextstyle(16, 0, "宋体");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	//下面是输出字体 参数：（起始位置x 起始位置y “带输出的字符串”）
	settextcolor(WHITE);
	settextstyle(16, 0, "楷体");//设置文字大小 格式 
	outtextxy(15, 15, "当前目录:");
	outtextxy(90, 15, ("/cmd"));
	outtextxy(195, 285, "请输入指令");
	
	
	/*按钮设定*/
begin2:
	while (1) {
		m = getmessage(EM_MOUSE | EM_KEY);
		if (m.x >= 15 && m.y >= 310 && m.x <= 450 && m.y <= 330) {//指令输入
			if (m.message == WM_LBUTTONUP) {//左键弹起时
				if (m.message == WM_LBUTTONUP) {//左键弹起时
					InputBox(INS_T, BUF_SIZE, "请输入指令");
					clearrectangle(17, 312, 448, 328);
					outtextxy(17, 312, INS_T);
				}
			}
		}
		else if (m.x >= 465 && m.y >= 310 && m.x <= 535 && m.y <= 330) {//确认
			if (m.message == WM_LBUTTONUP) {//左键弹起时
				clearrectangle(16, 41, 534, 269);//清空信息栏
				char RYInfrec[BUF_SIZE] = { 0 };//接受回复信息的数组


				//将数据拷贝到共享内存
				strcpy_s((char*)SHARED_FILEPTR, strlen(INS_T) + 1, INS_T);
				strcpy_s((char*)SHARED_FILEQULPTR, strlen("1") + 1, "1");

				/*对于write是否占用的判断*/
				HANDLE WSPACE = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "WSPACE");//不断地从回复信息空间中获取数据
				LPVOID WREC= MapViewOfFile(WSPACE, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				istringstream input_s(INS_T);
				string WFILE;
				if (WREC)
				{
					WFILE = string((char*)WREC);
				}
				else
				{
					WFILE = "";
				}

				string input_INS;
				string InputFile;
				input_s >> input_INS;
				input_s >> InputFile;
				if (InputFile == WFILE && input_INS == "write")
				{
					clearrectangle(90, 15, 200, 30);
					outtextxy(90, 15, RYInfrec);
					outtextxy(16, 41, "当前文件正在被其他用户写入，请稍后再试！");
					char NULLChar[] = "";//清空输入
					strcpy_s((char*)SHARED_FILEPTR, strlen(NULLChar) + 1, NULLChar);
					goto begin2;
				}

				while (1)
				{
					HANDLE ReplyInfoSpace = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "ReplyInfoSpace");//不断地从回复信息空间中获取数据
					LPVOID ReplyInfoRec = MapViewOfFile(ReplyInfoSpace, FILE_MAP_ALL_ACCESS, 0, 0, 0);



					if (!ReplyInfoRec)continue;
					if (strlen((char*)ReplyInfoRec))
					{
						SMemoinfoCY(RYInfrec, ReplyInfoRec);
						break;//如果获取到的数据，break
					}
				}

				clearrectangle(17, 42, 533, 268);//清空输入文本框

				/*输出返回的信息到信息框*/
				if (RYInfrec[0] == '/')
				{
					clearrectangle(90, 15, 200, 30);
					outtextxy(90, 15, RYInfrec);
					outtextxy(16, 41, "跳转成功！");
					continue;
				}
				int CountChangeLine = 1;
				string input_str(RYInfrec);
				for (int i = 0; i < input_str.length(); i++)
				{
					if (input_str[i] == '\n')
					{
						input_str[i] = ' ';
						CountChangeLine++;
					}
				}
				istringstream input_Sstr(input_str);
				for (int i = 0; i < CountChangeLine; i++)
				{
					input_Sstr >> input_str;
					outtextxy(16, 41 + 18 * i, input_str.c_str());
				}
			}
		}
		else if (m.x >= 465 && m.y >= 15 && m.x <= 535 && m.y <= 35) {//返回
			if (m.message == WM_LBUTTONUP) {//左键弹起时
				return;
			}
		}
	}

	/*解除指令空间文件映射*/
	UnmapViewOfFile(SHARED_FILEPTR);
	CloseHandle(SHARED_FILESPACE);

	return;
}

