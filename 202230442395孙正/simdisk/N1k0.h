#pragma once
#include <iostream>
#include <cmath>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <io.h>
#include <vector>
#define BUF_SIZE 4096
using namespace std;

/*-------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------基础类-----------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/


class INode
{
public:
    char FileName[8];//文件名称
    int type;//表示文件类型，0位目录，1位文件
    int AdAccess[3];//管理员文件保护类型，分别表示只读/可写/可执行
    int UserAccess[3];//普通用户文件保护类型，分别表示只读/可写/可执行
    char ParNode[32];//存放父结点
    char ChildNode[3][32];//存放子结点，文件没有子结点
    char DiskAddress[32];//存放文件对应的内容，目录内容默认为空
    INode()
    {
        for (int i = 0; i < 8; i++)
        {
            FileName[i] = 0;
        }
        type = 0;
        for (int i = 0; i < 3; i++)
        {
            AdAccess[i] = 0;
            UserAccess[i] = 0;
        }
        for (int i = 0; i < 32; i++)
        {
            ParNode[i] = 0;
            DiskAddress[i] = 0;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                ChildNode[i][j] = 0;
            }
        }
    }
    INode(char* FN, int t, int* AdAcc, int* UserAcc, char* PNode, char** CNode, char* DAdd)
    {
        for (int i = 0; i < 8; i++)
        {
            FileName[i] = FN[i];
        }
        type = t;
        for (int i = 0; i < 3; i++)
        {
            AdAccess[i] = AdAcc[i];
            UserAccess[i] = UserAcc[i];
        }
        for (int i = 0; i < 32; i++)
        {
            ParNode[i] = PNode[i];
            DiskAddress[i] = DAdd[i];
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                ChildNode[i][j] = CNode[i][j];
            }
        }
    }
};

/*-------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------其他函数声明---------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/




/*==============================基本函数==============================*/
/*==========翻译函数==========*/
/*8位int数组<==>char字符*/
int* char2_8int(char Char);//将符号转换为8位二进制整数数组，用于输入文本
char int_82char(int* tt);//将8位二进制整数数组转换为符号，用于输出文本

/*指针==>磁盘块序号*/
int ptrnum2blocknum(int PointerSqe);//将指针序号转换为磁盘块序号

/*32位数组int地址<==>磁盘块地址*/
int* blocknum2addr(int blocknum);//将磁盘块序号转换为32位地址
int addr2blocknum(int* Add);//将32位地址转换为磁盘块序号





/*==========功能函数==========*/
void Init(fstream& Disk_Pointer);//初始化函数，用于将硬盘进行初始化
int getBLOCK(fstream& Disk_Pointer);//获取对应指针的当前磁盘块序号
int document_match(fstream& Disk_Pointer, int blocknum, string DocName);//将对应的文件名与特定磁盘块中的所有子结点的文件名进行比较，如果匹配，返回磁盘块序号；如果不匹配，返回0
void jump2whePTR(fstream& Disk_Pointer, int blocknum, int BlockIn);//将指针跳转到指定位置。其中blocknum为磁盘块序号，BlockIn为块内地址
void response(string ReplyInfo, LPVOID& ShareMemoryPointer);//用于拷贝回复的信息
void SMemoCL(LPVOID& ShareMemoryPointer);//清空共享内存
void SMemoinfoCY(char* Buffer, LPVOID& ShareMemoryPointer);//将共享内存中的内容拷贝出来
void bitmap_engine(fstream& Disk_Pointer, int blocknum, int Tag);//将位图区域的某一个值置1或者置0

/*输入函数*/
void inputintaddr(fstream& Disk_Pointer, int* IntArr, int Length);//直接将二进制数输入到硬盘中
void InputChar(fstream& Disk_Pointer, char Char);//将符号转换为二进制数并输入到硬盘中
void inputcharaddr(fstream& Disk_Pointer, char* CharArr);//将符号串转换为二进制数并输入到硬盘中
void InputDocName(fstream& Disk_Pointer, int blocknum, string DocName);//将文件名输入到硬盘中，输入完后，指针回到原始磁盘块的首位。
void InputParNode(fstream& Disk_Pointer, int blocknum, int* IntArr);//将父指针输入到硬盘中，输入完后，指针回到原始磁盘块的首位。
void InputAcc(fstream& Disk_Pointer, int blocknum, string Acc);//将保护类型输入到硬盘中
void inputcontT(fstream& Disk_Pointer, int blocknum, int NewDocBlockSqe, string Context);//在对应的磁盘块中输入文件内容磁盘块对应的地址,并在对应的文件磁盘块中输入文件内容
void InputFileType(fstream& Disk_Pointer, int blocknum, int FileType);//将文件类型输入到磁盘中

/*输出函数*/
int* OP32b(fstream& Disk_Pointer);//输出32位二进制数
int* OP8b(fstream& Disk_Pointer);//输出8位二进制数

/*查找函数*/
int F_spareInode(fstream& Disk_Pointer);//用于寻找位图中对应的i结点的区域的空闲区域，返回i结点的磁盘块序号，查找完后，指针回到原始磁盘块的首位。
int F_sparedoc(fstream& Disk_Pointer);//用于寻找位图中对应的文件区域的空闲区域，返回文件块对应的的磁盘块序号，查找完后，指针回到原始磁盘块的首位
int F_sparechildnode(fstream& Disk_Pointer, int blocknum);//判断特定的磁盘块中是否有空闲的子结点，如果有，返回子结点序号（1/2/3）；如果没有，返回0并定位到磁盘块开头
char* F_docNa(fstream& Disk_Pointer, int blocknum);//寻找某一32位地址对应的文件磁盘块对应的文件名，返回文件名数组，查找完后，指针回到原始磁盘块的首位
int F_docTy(fstream& Disk_Pointer, int blocknum);//寻找某个磁盘块对应的文件类型
int* F_docSACC(fstream& Disk_Pointer, int blocknum);//寻找某个磁盘块对应的系统保护类型
int* F_docUACC(fstream& Disk_Pointer, int blocknum);//寻找某个磁盘块对应的普通用户保护类型
int* F_docFAddr(fstream& Disk_Pointer, int blocknum);//寻找某个磁盘块对应的父结点地址
int** F_docCHILDddr(fstream& Disk_Pointer, int blocknum);//寻找某个磁盘块对应的子结点地址
int* F_doccontnode(fstream& Disk_Pointer, int blocknum);//寻找某个磁盘块对应的内容的地址










/*==============================专用函数==============================*/
/*info*/
int G_InodeLspace(fstream& Disk_Pointer);//获取i结点的剩余空间
int G_docLspace(fstream& Disk_Pointer);//获取文件区的剩余空间

/*cd*/
string cd_HELP(fstream& Disk_Pointer, string AddBuf);//将指针跳转至对应路径的目录，并返回路径；如果路径不正确，返回错误信息

/*dir*/
void ShowAllChildNodeName(fstream& Disk_Pointer, int blocknum, string& ReplyInfo);//用于寻找目标磁盘块的所有子结点的名字，并将相应的信息录入到ReplyInfo中
void ShowAllInfo(fstream& Disk_Pointer, int blocknum, string& ReplyInfo);//将对应磁盘块的所有信息返回到ReplyInfo中
int dir_HELP(fstream& Disk_Pointer, string AddBuf);//将指针跳转至对应路径的目录；如果路径正确，返回对应文件的磁盘块序号；如果路径不正确，返回0

/*md*/
string mdAddLocation(fstream& Disk_Pointer, string AddBuf);//将指针跳转至对应路径的目录，并返回需要创建的文件名；如果路径不正确，返回一个空串

/*rd*/
int IsDirEmpty(fstream& Disk_Pointer, int blocknum);//判断一个目录磁盘块是否为空
int IsFileEmpty(fstream& Disk_Pointer, int blocknum);//盘块一个文件磁盘块是否为空
int rd_HELP(fstream& Disk_Pointer, string AddBuf);//将指针跳转至对应路径的目录，并返回路径；如果路径不正确，返回错误信息
void rdDir(fstream& Disk_Pointer, int blocknum);//删除一个目录，如果有子目录，一起删了

/*newfile*/
string FileNameTest(string FileName);//判断一个文件名的格式是否正确
string FileAccTest(string Acc);//判断保护类型的格式是否正确
string newfile_HELP(fstream& Disk_Pointer, string AddBuf);//将指针跳转至对应路径的目录，并返回需要创建的文件名；如果路径不正确，返回一个空串

/*cat*/
int cat_HELP(fstream& Disk_Pointer, string AddBuf);//将指针跳转至对应路径的目录，并返回路径；如果路径不正确，返回错误信息
string GetFileContext(fstream& Disk_Pointer, int blocknum);//获取对应磁盘块的内容

/*del*/
void delDoc(fstream& Disk_Pointer, int blocknum);//删除一个文件（指定磁盘块）。

/*copy*/
string GetWindowsFileName(string path);//获取windows下一个文件的文件名
string CopyNewFile(fstream& Disk_Pointer, istringstream& Buf);//在Copy指令下新建一个文件

/*check*/
void ConsistencyCheck(fstream& Disk_Pointer, int blocknum);//一致性检查





