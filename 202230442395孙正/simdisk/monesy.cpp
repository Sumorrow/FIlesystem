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
 *            ���汣��       ����崻�     ����BUG
 */
 /**
/*==============================ר�ú���==============================*/
int* char2_8int(char Char)
{
    int IntNum = int(Char);//���ַ�ת��ΪASCII��
    int* bit_int0;//�������
    bit_int0 = new int[8];
    for (int i = 0; i < 8; i++)//�ó�nȡ�෨ת��Ϊ��������
    {
        bit_int0[7 - i] = IntNum % 2;
        IntNum = IntNum / 2;
    }
    return bit_int0;
}
char int_82char(int* tt)
{
    int IntNum = 0;
    for (int i = 7; i >= 0; i--)//���������������ۼ�
    {
        IntNum += tt[i] * pow(2, 7 - i);
    }
    return char(IntNum);//����ASCII��ֵ
}
int ptrnum2blocknum(int PointerSqe)
{
    return PointerSqe / 1024;
}
int addr2blocknum(int* Add)
{
    int blocknum = 0;
    for (int i = 21; i >= 5; i--)//��17λ������������Ϊ���̿��ַ
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
    for (int i = 21; i >= 5; i--)//�ó�nȡ�෨ת��Ϊ��������
    {
        Add[i] = blocknum % 2;
        blocknum = blocknum / 2;
    }
    return Add;
}
/*==========���ܺ���==========*/
void Init(fstream& Disk_Pointer)
{
    /*��ʼ����Ŀ¼*/
    Disk_Pointer.seekg(1024 * 101, ios::beg);
    char RootDirName[] = "cmd\0\0\0\0\0";//��Ŀ¼��
    inputcharaddr(Disk_Pointer, RootDirName);
    int FileType[] = { 0,0,0,0,0,0,0,0 };//��ʾ�ļ�����ΪĿ¼
    inputintaddr(Disk_Pointer, FileType, 8);
    int Access[] = { 0,0,0,0,0,0,0,0 };//Ŀ¼�����۷���Ȩ�����⣬ȫ����Ϊ0
    inputintaddr(Disk_Pointer, Access, 8);
    int ParNode[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
    //��Ŀ¼û�и����
    inputintaddr(Disk_Pointer, ParNode, 32);
    int ChildNode[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };
    //��Ŀ¼��ʼʱû���ӽ��
    inputintaddr(Disk_Pointer, ChildNode, 96);
    //Ŀ¼û���ļ�����
    int DiskAddress[] = { 0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 };
    inputintaddr(Disk_Pointer, DiskAddress, 32);

    /*��ʼ����������*/
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

    /*��ʼ��λͼ��*/
    jump2whePTR(Disk_Pointer, 1, 0);//��ת��λͼ��
    for (int i = 0; i < 102; i++)//��ǰ101�����̿���Ϊ��ʹ��
    {
        Disk_Pointer << 1;
    }
    for (int i = 0; i < 1024 * 100 - 102; i++)//����������д��̿���Ϊδʹ��
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
    for (int i = 0; i < 3; i++)//ѭ��3���ж��ӽ���ļ���
    {
        jump2whePTR(Disk_Pointer, blocknum, 112 + 32 * i);//��ת���ӽ�㲿��
        int* BitDocName = OP32b(Disk_Pointer);//����32λ�ӽ���ַ
        char* CharDocName = F_docNa(Disk_Pointer, addr2blocknum(BitDocName));//Ѱ���ӽ���ļ���
        if (string(CharDocName) == DocName)//�ж��ӽ���ļ����ǲ���Ҫ�ҵĶ���
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);
            return addr2blocknum(BitDocName);//����ǣ������ӽ���Ӧ�Ĵ��̿��
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;//������ǣ�����0
}
void jump2whePTR(fstream& Disk_Pointer, int blocknum, int BlockIn)
{
    Disk_Pointer.seekg(1024 * blocknum + BlockIn, ios::beg);
}
void response(string ReplyInfo, LPVOID& ShareMemoryPointer)
{
    strcpy_s((char*)ShareMemoryPointer, strlen(ReplyInfo.c_str()) + 1, ReplyInfo.c_str());//���ʹ�����Ϣ
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
/*���뺯��*/
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
    int DocNameLength = DocName.length();//��ȡ�ļ����ĳ���
    char* CharDocName;
    CharDocName = new char[DocNameLength];//����һ����ʱ�������ļ���
    strcpy_s(CharDocName, DocNameLength + 1, DocName.c_str());//���ļ����������ݿ�������ʱ����
    inputcharaddr(Disk_Pointer, CharDocName);//�����ļ���
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
/*�������*/
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
/*���Һ���*/
int F_sparedoc(fstream& Disk_Pointer)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, 1, 0);//����λͼ�����ļ��Ĳ���
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
    return 0;//���û�ҵ�������0

}
int F_spareInode(fstream& Disk_Pointer)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    int i = 102;
    jump2whePTR(Disk_Pointer, 1, i);
    char chartpt_buf;
    for (i; i < 50102; i++)//����λͼ����i���Ĳ���
    {
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '0')
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);
            return i;
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;//���û�ҵ�������0
}
char* F_docNa(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char* DocName;//Ӧ�÷��ص��ļ���
    DocName = new char[8];
    int* INIttpt_buf;//����װ�����ڷ��������
    jump2whePTR(Disk_Pointer, blocknum, 0);//��ת����Ӧλ��
    for (int i = 0; i < 8; i++)
    {
        INIttpt_buf = OP8b(Disk_Pointer);
        DocName[i] = int_82char(INIttpt_buf);//����Ӧ�Ķ���������ת��Ϊ����
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return DocName;//�����ļ���
}
int F_sparechildnode(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char IsFree;

    jump2whePTR(Disk_Pointer, blocknum, 112);//��ת����һ���ӽ���λ��
    Disk_Pointer >> IsFree;
    if (IsFree == '0')//����ӽ��û�б�ʹ��
    {
        Disk_Pointer.seekg(-1, ios::cur);//��һλ
        jump2whePTR(Disk_Pointer, ORZNUM, 0);
        return 1;//�����ӽ�����
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32);//��ת���ڶ����ӽ���λ��
    Disk_Pointer >> IsFree;
    if (IsFree == '0')//����ӽ��û�б�ʹ��
    {
        Disk_Pointer.seekg(-1, ios::cur);//��һλ
        jump2whePTR(Disk_Pointer, ORZNUM, 0);
        return 2;//�����ӽ�����
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32 + 32);//��ת���������ӽ���λ��
    Disk_Pointer >> IsFree;
    if (IsFree == '0')//����ӽ��û�б�ʹ��
    {
        Disk_Pointer.seekg(-1, ios::cur);//��һλ
        jump2whePTR(Disk_Pointer, ORZNUM, 0);
        return 3;//�����ӽ�����
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
 *            ���汣��       ����崻�     ����BUG
 */
 /**
/*==============================ר�ú���==============================*/