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
/*--------------------------------------------------������-----------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/


class INode
{
public:
    char FileName[8];//�ļ�����
    int type;//��ʾ�ļ����ͣ�0λĿ¼��1λ�ļ�
    int AdAccess[3];//����Ա�ļ��������ͣ��ֱ��ʾֻ��/��д/��ִ��
    int UserAccess[3];//��ͨ�û��ļ��������ͣ��ֱ��ʾֻ��/��д/��ִ��
    char ParNode[32];//��Ÿ����
    char ChildNode[3][32];//����ӽ�㣬�ļ�û���ӽ��
    char DiskAddress[32];//����ļ���Ӧ�����ݣ�Ŀ¼����Ĭ��Ϊ��
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
/*----------------------------------------------������������---------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/




/*==============================��������==============================*/
/*==========���뺯��==========*/
/*8λint����<==>char�ַ�*/
int* char2_8int(char Char);//������ת��Ϊ8λ�������������飬���������ı�
char int_82char(int* tt);//��8λ��������������ת��Ϊ���ţ���������ı�

/*ָ��==>���̿����*/
int ptrnum2blocknum(int PointerSqe);//��ָ�����ת��Ϊ���̿����

/*32λ����int��ַ<==>���̿��ַ*/
int* blocknum2addr(int blocknum);//�����̿����ת��Ϊ32λ��ַ
int addr2blocknum(int* Add);//��32λ��ַת��Ϊ���̿����





/*==========���ܺ���==========*/
void Init(fstream& Disk_Pointer);//��ʼ�����������ڽ�Ӳ�̽��г�ʼ��
int getBLOCK(fstream& Disk_Pointer);//��ȡ��Ӧָ��ĵ�ǰ���̿����
int document_match(fstream& Disk_Pointer, int blocknum, string DocName);//����Ӧ���ļ������ض����̿��е������ӽ����ļ������бȽϣ����ƥ�䣬���ش��̿���ţ������ƥ�䣬����0
void jump2whePTR(fstream& Disk_Pointer, int blocknum, int BlockIn);//��ָ����ת��ָ��λ�á�����blocknumΪ���̿���ţ�BlockInΪ���ڵ�ַ
void response(string ReplyInfo, LPVOID& ShareMemoryPointer);//���ڿ����ظ�����Ϣ
void SMemoCL(LPVOID& ShareMemoryPointer);//��չ����ڴ�
void SMemoinfoCY(char* Buffer, LPVOID& ShareMemoryPointer);//�������ڴ��е����ݿ�������
void bitmap_engine(fstream& Disk_Pointer, int blocknum, int Tag);//��λͼ�����ĳһ��ֵ��1������0

/*���뺯��*/
void inputintaddr(fstream& Disk_Pointer, int* IntArr, int Length);//ֱ�ӽ������������뵽Ӳ����
void InputChar(fstream& Disk_Pointer, char Char);//������ת��Ϊ�������������뵽Ӳ����
void inputcharaddr(fstream& Disk_Pointer, char* CharArr);//�����Ŵ�ת��Ϊ�������������뵽Ӳ����
void InputDocName(fstream& Disk_Pointer, int blocknum, string DocName);//���ļ������뵽Ӳ���У��������ָ��ص�ԭʼ���̿����λ��
void InputParNode(fstream& Disk_Pointer, int blocknum, int* IntArr);//����ָ�����뵽Ӳ���У��������ָ��ص�ԭʼ���̿����λ��
void InputAcc(fstream& Disk_Pointer, int blocknum, string Acc);//�������������뵽Ӳ����
void inputcontT(fstream& Disk_Pointer, int blocknum, int NewDocBlockSqe, string Context);//�ڶ�Ӧ�Ĵ��̿��������ļ����ݴ��̿��Ӧ�ĵ�ַ,���ڶ�Ӧ���ļ����̿��������ļ�����
void InputFileType(fstream& Disk_Pointer, int blocknum, int FileType);//���ļ��������뵽������

/*�������*/
int* OP32b(fstream& Disk_Pointer);//���32λ��������
int* OP8b(fstream& Disk_Pointer);//���8λ��������

/*���Һ���*/
int F_spareInode(fstream& Disk_Pointer);//����Ѱ��λͼ�ж�Ӧ��i��������Ŀ������򣬷���i���Ĵ��̿���ţ��������ָ��ص�ԭʼ���̿����λ��
int F_sparedoc(fstream& Disk_Pointer);//����Ѱ��λͼ�ж�Ӧ���ļ�����Ŀ������򣬷����ļ����Ӧ�ĵĴ��̿���ţ��������ָ��ص�ԭʼ���̿����λ
int F_sparechildnode(fstream& Disk_Pointer, int blocknum);//�ж��ض��Ĵ��̿����Ƿ��п��е��ӽ�㣬����У������ӽ����ţ�1/2/3�������û�У�����0����λ�����̿鿪ͷ
char* F_docNa(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳһ32λ��ַ��Ӧ���ļ����̿��Ӧ���ļ����������ļ������飬�������ָ��ص�ԭʼ���̿����λ
int F_docTy(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳ�����̿��Ӧ���ļ�����
int* F_docSACC(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳ�����̿��Ӧ��ϵͳ��������
int* F_docUACC(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳ�����̿��Ӧ����ͨ�û���������
int* F_docFAddr(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳ�����̿��Ӧ�ĸ�����ַ
int** F_docCHILDddr(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳ�����̿��Ӧ���ӽ���ַ
int* F_doccontnode(fstream& Disk_Pointer, int blocknum);//Ѱ��ĳ�����̿��Ӧ�����ݵĵ�ַ










/*==============================ר�ú���==============================*/
/*info*/
int G_InodeLspace(fstream& Disk_Pointer);//��ȡi����ʣ��ռ�
int G_docLspace(fstream& Disk_Pointer);//��ȡ�ļ�����ʣ��ռ�

/*cd*/
string cd_HELP(fstream& Disk_Pointer, string AddBuf);//��ָ����ת����Ӧ·����Ŀ¼��������·�������·������ȷ�����ش�����Ϣ

/*dir*/
void ShowAllChildNodeName(fstream& Disk_Pointer, int blocknum, string& ReplyInfo);//����Ѱ��Ŀ����̿�������ӽ������֣�������Ӧ����Ϣ¼�뵽ReplyInfo��
void ShowAllInfo(fstream& Disk_Pointer, int blocknum, string& ReplyInfo);//����Ӧ���̿��������Ϣ���ص�ReplyInfo��
int dir_HELP(fstream& Disk_Pointer, string AddBuf);//��ָ����ת����Ӧ·����Ŀ¼�����·����ȷ�����ض�Ӧ�ļ��Ĵ��̿���ţ����·������ȷ������0

/*md*/
string mdAddLocation(fstream& Disk_Pointer, string AddBuf);//��ָ����ת����Ӧ·����Ŀ¼����������Ҫ�������ļ��������·������ȷ������һ���մ�

/*rd*/
int IsDirEmpty(fstream& Disk_Pointer, int blocknum);//�ж�һ��Ŀ¼���̿��Ƿ�Ϊ��
int IsFileEmpty(fstream& Disk_Pointer, int blocknum);//�̿�һ���ļ����̿��Ƿ�Ϊ��
int rd_HELP(fstream& Disk_Pointer, string AddBuf);//��ָ����ת����Ӧ·����Ŀ¼��������·�������·������ȷ�����ش�����Ϣ
void rdDir(fstream& Disk_Pointer, int blocknum);//ɾ��һ��Ŀ¼���������Ŀ¼��һ��ɾ��

/*newfile*/
string FileNameTest(string FileName);//�ж�һ���ļ����ĸ�ʽ�Ƿ���ȷ
string FileAccTest(string Acc);//�жϱ������͵ĸ�ʽ�Ƿ���ȷ
string newfile_HELP(fstream& Disk_Pointer, string AddBuf);//��ָ����ת����Ӧ·����Ŀ¼����������Ҫ�������ļ��������·������ȷ������һ���մ�

/*cat*/
int cat_HELP(fstream& Disk_Pointer, string AddBuf);//��ָ����ת����Ӧ·����Ŀ¼��������·�������·������ȷ�����ش�����Ϣ
string GetFileContext(fstream& Disk_Pointer, int blocknum);//��ȡ��Ӧ���̿������

/*del*/
void delDoc(fstream& Disk_Pointer, int blocknum);//ɾ��һ���ļ���ָ�����̿飩��

/*copy*/
string GetWindowsFileName(string path);//��ȡwindows��һ���ļ����ļ���
string CopyNewFile(fstream& Disk_Pointer, istringstream& Buf);//��Copyָ�����½�һ���ļ�

/*check*/
void ConsistencyCheck(fstream& Disk_Pointer, int blocknum);//һ���Լ��





