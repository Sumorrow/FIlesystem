#include"N1k0.h"

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
/*==============================专用函数==============================*/
int* char2_8int(char Char)
{
    int IntNum = int(Char);//将字符转换为ASCII码
    int* bit_int0;//输出数组
    bit_int0 = new int[8];
    for (int i = 0; i < 8; i++)//用除n取余法转换为二进制数
    {
        bit_int0[7 - i] = IntNum % 2;
        IntNum = IntNum / 2;
    }
    return bit_int0;
}
char int_82char(int* tt)
{
    int IntNum = 0;
    for (int i = 7; i >= 0; i--)//将二进制数进行累加
    {
        IntNum += tt[i] * pow(2, 7 - i);
    }
    return char(IntNum);//返回ASCII码值
}
int ptrnum2blocknum(int PointerSqe)
{
    return PointerSqe / 1024;
}
int addr2blocknum(int* Add)
{
    int blocknum = 0;
    for (int i = 21; i >= 5; i--)//将17位二进制数翻译为磁盘块地址
    {
        blocknum += Add[i] * pow(2, 21 - i);
    }
    return blocknum;
}
int* blocknum2addr(int blocknum)
{
    int* Add;
    Add = new int[32];
    for (int i = 0; i < 32; i++)
    {
        Add[i] = 0;
    }
    for (int i = 21; i >= 5; i--)//用除n取余法转换为二进制数
    {
        Add[i] = blocknum % 2;
        blocknum = blocknum / 2;
    }
    return Add;
}
/*==========功能函数==========*/
void Init(fstream& Disk_Pointer)
{
    /*初始化根目录*/
    Disk_Pointer.seekg(1024 * 101, ios::beg);
    char RootDirName[] = "cmd\0\0\0\0\0";//根目录名
    inputcharaddr(Disk_Pointer, RootDirName);
    int FileType[] = { 0,0,0,0,0,0,0,0 };//表示文件类型为目录
    inputintaddr(Disk_Pointer, FileType, 8);
    int Access[] = { 0,0,0,0,0,0,0,0 };//目录不讨论访问权限问题，全部置为0
    inputintaddr(Disk_Pointer, Access, 8);
    int ParNode[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
    //根目录没有父结点
    inputintaddr(Disk_Pointer, ParNode, 32);
    int ChildNode[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
    //根目录初始时没有子结点
    inputintaddr(Disk_Pointer, ChildNode, 96);
    //目录没有文件内容
    int DiskAddress[] = { 0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 };
    inputintaddr(Disk_Pointer, DiskAddress, 32);

    /*初始化超级块区*/
    jump2whePTR(Disk_Pointer, 0, 0);
    inputcharaddr(Disk_Pointer, const_cast<char*>("cmd"));
    jump2whePTR(Disk_Pointer, 0, 64);
    inputintaddr(Disk_Pointer, blocknum2addr(100), 32);
    jump2whePTR(Disk_Pointer, 0, 96);
    inputintaddr(Disk_Pointer, blocknum2addr(1024), 32);
    jump2whePTR(Disk_Pointer, 0, 124);
    inputintaddr(Disk_Pointer, blocknum2addr(0), 32);
    jump2whePTR(Disk_Pointer, 0, 160);
    inputintaddr(Disk_Pointer, blocknum2addr(1), 32);
    jump2whePTR(Disk_Pointer, 0, 192);
    inputintaddr(Disk_Pointer, blocknum2addr(101), 32);
    jump2whePTR(Disk_Pointer, 0, 224);
    inputintaddr(Disk_Pointer, blocknum2addr(102), 32);
    jump2whePTR(Disk_Pointer, 0, 256);
    inputintaddr(Disk_Pointer, blocknum2addr(50102), 32);

    /*初始化位图区*/
    jump2whePTR(Disk_Pointer, 1, 0);//跳转到位图区
    for (int i = 0; i < 102; i++)//将前101个磁盘块置为已使用
    {
        Disk_Pointer << 1;
    }
    for (int i = 0; i < 1024 * 100 - 102; i++)//将后面的所有磁盘块置为未使用
    {
        Disk_Pointer << 0;
    }
}
int getBLOCK(fstream& Disk_Pointer)
{
    int PointerSqe = Disk_Pointer.tellg();
    return ptrnum2blocknum(PointerSqe);
}
int document_match(fstream& Disk_Pointer, int blocknum, string DocName)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    for (int i = 0; i < 3; i++)//循环3次判断子结点文件名
    {
        jump2whePTR(Disk_Pointer, blocknum, 112 + 32 * i);//跳转到子结点部分
        int* BitDocName = OP32b(Disk_Pointer);//读入32位子结点地址
        char* CharDocName = F_docNa(Disk_Pointer, addr2blocknum(BitDocName));//寻找子结点文件名
        if (string(CharDocName) == DocName)//判断子结点文件名是不是要找的东西
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);
            return addr2blocknum(BitDocName);//如果是，返回子结点对应的磁盘块号
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;//如果不是，返回0
}
void jump2whePTR(fstream& Disk_Pointer, int blocknum, int BlockIn)
{
    Disk_Pointer.seekg(1024 * blocknum + BlockIn, ios::beg);
}
void response(string ReplyInfo, LPVOID& ShareMemoryPointer)
{
    strcpy_s((char*)ShareMemoryPointer, strlen(ReplyInfo.c_str()) + 1, ReplyInfo.c_str());//发送错误信息
    cout << "Return Info:" << ReplyInfo << endl;
}
void SMemoCL(LPVOID& ShareMemoryPointer)
{
    char NULLChar[] = "";
    strcpy_s((char*)ShareMemoryPointer, strlen(NULLChar) + 1, NULLChar);
}
void SMemoinfoCY(char* Buffer, LPVOID& ShareMemoryPointer)
{
    strcpy_s(Buffer, strlen((char*)ShareMemoryPointer) + 1, (char*)ShareMemoryPointer);
    SMemoCL(ShareMemoryPointer);
}
void bitmap_engine(fstream& Disk_Pointer, int blocknum, int Tag)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, 1, blocknum);
    Disk_Pointer << Tag;
    jump2whePTR(Disk_Pointer, blocknum, 0);
}
/*输入函数*/
void inputcharaddr(fstream& Disk_Pointer, char* CharArr)
{
    for (int i = 0; i < strlen(CharArr); i++)
    {
        InputChar(Disk_Pointer, CharArr[i]);
    }
}
void InputChar(fstream& Disk_Pointer, char Char)
{
    int* InputInt;
    InputInt = new int[8];
    InputInt = char2_8int(Char);
    inputintaddr(Disk_Pointer, InputInt, 8);
}
void inputintaddr(fstream& Disk_Pointer, int* IntArr, int Length)
{
    for (int i = 0; i < Length; i++)
    {
        Disk_Pointer << IntArr[i];
    }
}
void InputDocName(fstream& Disk_Pointer, int blocknum, string DocName)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 0);
    int DocNameLength = DocName.length();//获取文件名的长度
    char* CharDocName;
    CharDocName = new char[DocNameLength];//申请一个临时数组存放文件名
    strcpy_s(CharDocName, DocNameLength + 1, DocName.c_str());//将文件名汇总内容拷贝到临时数组
    inputcharaddr(Disk_Pointer, CharDocName);//输入文件名
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
void InputParNode(fstream& Disk_Pointer, int blocknum, int* IntArr)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 80);
    inputintaddr(Disk_Pointer, IntArr, 32);
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
void InputAcc(fstream& Disk_Pointer, int blocknum, string Acc)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 72);
    int* TempInputIntArr;
    TempInputIntArr = new int[8];
    for (int i = 0; i < 8; i++)
    {
        TempInputIntArr[i] = 0;
    }
    for (int i = 1; i < 4; i++)
    {
        TempInputIntArr[i] = Acc[i - 1] - 48;
    }
    for (int i = 5; i < 8; i++)
    {
        TempInputIntArr[i] = Acc[i - 2] - 48;
    }
    inputintaddr(Disk_Pointer, TempInputIntArr, 8);
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
void inputcontT(fstream& Disk_Pointer, int blocknum, int NewDocBlockSqe, string Context)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 208);
    inputintaddr(Disk_Pointer, blocknum2addr(NewDocBlockSqe), 32);
    jump2whePTR(Disk_Pointer, NewDocBlockSqe, 0);
    inputcharaddr(Disk_Pointer, const_cast<char*>(Context.c_str()));
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
void InputFileType(fstream& Disk_Pointer, int blocknum, int FileType)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 71);
    Disk_Pointer << FileType;
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
/*输出函数*/
int* OP32b(fstream& Disk_Pointer)
{
    int* OP32b;
    OP32b = new int[32];
    char chartpt_buf;
    for (int i = 0; i < 32; i++)
    {
        Disk_Pointer >> chartpt_buf;
        OP32b[i] = int(chartpt_buf) - 48;
    }
    return OP32b;
}
int* OP8b(fstream& Disk_Pointer)
{
    int* OP8b;
    OP8b = new int[8];
    char chartpt_buf;
    for (int i = 0; i < 8; i++)
    {
        Disk_Pointer >> chartpt_buf;
        OP8b[i] = int(chartpt_buf) - 48;
    }
    return OP8b;
}
/*查找函数*/
int F_sparedoc(fstream& Disk_Pointer)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, 1, 0);//遍历位图区中文件的部分
    int i = 50102;
    char chartpt_buf;
    for (i; i < 100102; i++)
    {
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '0')
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);
            return i;
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;//如果没找到，返回0

}
int F_spareInode(fstream& Disk_Pointer)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    int i = 102;
    jump2whePTR(Disk_Pointer, 1, i);
    char chartpt_buf;
    for (i; i < 50102; i++)//遍历位图区中i结点的部分
    {
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '0')
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);
            return i;
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;//如果没找到，返回0
}
char* F_docNa(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char* DocName;//应该返回的文件名
    DocName = new char[8];
    int* INIttpt_buf;//用于装载用于翻译的数字
    jump2whePTR(Disk_Pointer, blocknum, 0);//跳转到对应位置
    for (int i = 0; i < 8; i++)
    {
        INIttpt_buf = OP8b(Disk_Pointer);
        DocName[i] = int_82char(INIttpt_buf);//将对应的二进制数组转换为符号
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return DocName;//返回文件名
}
int F_sparechildnode(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char IsFree;

    jump2whePTR(Disk_Pointer, blocknum, 112);//跳转到第一个子结点的位置
    Disk_Pointer >> IsFree;
    if (IsFree == '0')//如果子结点没有被使用
    {
        Disk_Pointer.seekg(-1, ios::cur);//退一位
        jump2whePTR(Disk_Pointer, ORZNUM, 0);
        return 1;//返回子结点序号
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32);//跳转到第二个子结点的位置
    Disk_Pointer >> IsFree;
    if (IsFree == '0')//如果子结点没有被使用
    {
        Disk_Pointer.seekg(-1, ios::cur);//退一位
        jump2whePTR(Disk_Pointer, ORZNUM, 0);
        return 2;//返回子结点序号
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32 + 32);//跳转到第三个子结点的位置
    Disk_Pointer >> IsFree;
    if (IsFree == '0')//如果子结点没有被使用
    {
        Disk_Pointer.seekg(-1, ios::cur);//退一位
        jump2whePTR(Disk_Pointer, ORZNUM, 0);
        return 3;//返回子结点序号
    }

    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;
}
int F_docTy(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    jump2whePTR(Disk_Pointer, blocknum, 71);
    Disk_Pointer >> chartpt_buf;
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return int(chartpt_buf) - 48;
}
int* F_docSACC(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    int* SysAcc;
    SysAcc = new int[3];
    jump2whePTR(Disk_Pointer, blocknum, 73);
    for (int i = 0; i < 3; i++)
    {
        Disk_Pointer >> chartpt_buf;
        SysAcc[i] = chartpt_buf - 48;
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return SysAcc;
}
int* F_docUACC(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    int* ComAcc;
    ComAcc = new int[3];
    jump2whePTR(Disk_Pointer, blocknum, 77);
    for (int i = 0; i < 3; i++)
    {
        Disk_Pointer >> chartpt_buf;
        ComAcc[i] = chartpt_buf - 48;
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return ComAcc;
}
int* F_docFAddr(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    int* ParNodeAdd;
    ParNodeAdd = new int[32];
    jump2whePTR(Disk_Pointer, blocknum, 80);
    for (int i = 0; i < 32; i++)
    {
        Disk_Pointer >> chartpt_buf;
        ParNodeAdd[i] = chartpt_buf - 48;
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return ParNodeAdd;
}
int** F_docCHILDddr(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    int** ChildNodeAdd;
    ChildNodeAdd = new int* [3];
    for (int i = 0; i < 32; i++)
    {
        ChildNodeAdd[i] = new int[32];
    }
    jump2whePTR(Disk_Pointer, blocknum, 112);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            Disk_Pointer >> chartpt_buf;
            ChildNodeAdd[i][j] = chartpt_buf - 48;
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return ChildNodeAdd;
}
int* F_doccontnode(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    int* ParNodeAdd;
    ParNodeAdd = new int[32];
    jump2whePTR(Disk_Pointer, blocknum, 208);
    for (int i = 0; i < 32; i++)
    {
        Disk_Pointer >> chartpt_buf;
        ParNodeAdd[i] = chartpt_buf - 48;
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return ParNodeAdd;
}
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
/*==============================专用函数==============================*/