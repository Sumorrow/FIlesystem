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
/*info*/
int G_InodeLspace(fstream& Disk_Pointer)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    int CountRemain = 0;
    jump2whePTR(Disk_Pointer, 1, 102);
    char chartpt_buf;
    for (int i = 102; i < 50102; i++)
    {
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '0')
        {
            CountRemain++;
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return CountRemain;
}
int G_docLspace(fstream& Disk_Pointer)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    int CountRemain = 0;
    jump2whePTR(Disk_Pointer, 1, 50102);
    char chartpt_buf;
    for (int i = 50102; i < 102400; i++)
    {
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '0')
        {
            CountRemain++;
        }
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return CountRemain;
}

/*cd*/
string cd_HELP(fstream& Disk_Pointer, string AddBuf)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    string OriAddBuf = AddBuf;
    string CurDirName;//������ʱ�洢��ǰλ��
    if (AddBuf.length() == 0)//�����ַΪ�գ����ش�����Ϣ
    {
        return "��ת��ַȱʧ��";
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//�Ӹ���㿪ʼ����
        /*����ָ��ķָ���/����Ԥ����*/
        for (int i = 0; i < AddBuf.length(); i++)//�ȴ����ַ�е�/����
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//��/�滻Ϊ�ո񣬱�������
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*�жϸ���ַ�Ƿ�������*/
        if (CurDirName != "cmd")//�������ַ����
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);//��ת��ԭ����λ��
            return "��ַ����";
        }
        if (AddStr.eof())
        {
            jump2whePTR(Disk_Pointer, 101, 0);
            return "/cmd";
        }
        /*ͨ���ӽ�㲻�Ͻ��ж�λ*/
        while (1)//�������ַ���AddressBuf�л�������
        {
            AddStr >> CurDirName;//������һ��Ŀ¼

            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//����ҵ��˶�Ӧ�����ļ�
            {
                if (F_docTy(Disk_Pointer, getBLOCK(Disk_Pointer)) != 0)
                {
                    return "��ַ����";
                }
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//��ת����Ӧ��λ��
            }
            else//���û��֪����Ӧ�����ļ�
            {
                jump2whePTR(Disk_Pointer, ORZNUM, 0);//��ת��ԭ����λ��
                return "��ַ����";
            }
            if (AddStr.eof())//��������һ��Ŀ¼֮�󵽵�����ײ�������
            {
                return OriAddBuf;
            }
        }
    }
    else
    {
        return "��ַ����";
    }
}
/*dir*/
void ShowAllChildNodeName(fstream& Disk_Pointer, int blocknum, string& ReplyInfo)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char* ChildNodeName;
    int* ChildNodeAdd;
    int FileType;

    jump2whePTR(Disk_Pointer, blocknum, 112);
    ChildNodeAdd = OP32b(Disk_Pointer);
    FileType = F_docTy(Disk_Pointer, addr2blocknum(ChildNodeAdd));
    if (ChildNodeAdd[0] == 1)//�������ӽ�㱻ռ����
    {
        int ChildNodeSqe = addr2blocknum(ChildNodeAdd);
        ChildNodeName = F_docNa(Disk_Pointer, ChildNodeSqe);
        ReplyInfo = ReplyInfo + "\n" + string(ChildNodeName);
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32);
    ChildNodeAdd = OP32b(Disk_Pointer);
    FileType = F_docTy(Disk_Pointer, addr2blocknum(ChildNodeAdd));
    if (ChildNodeAdd[0] == 1)//�������ӽ�㱻ռ����
    {
        int ChildNodeSqe = addr2blocknum(ChildNodeAdd);
        ChildNodeName = F_docNa(Disk_Pointer, ChildNodeSqe);
        ReplyInfo = ReplyInfo + "\n" + string(ChildNodeName);
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32 + 32);
    ChildNodeAdd = OP32b(Disk_Pointer);
    FileType = F_docTy(Disk_Pointer, addr2blocknum(ChildNodeAdd));
    if (ChildNodeAdd[0] == 1)//�������ӽ�㱻ռ����
    {
        int ChildNodeSqe = addr2blocknum(ChildNodeAdd);
        ChildNodeName = F_docNa(Disk_Pointer, ChildNodeSqe);
        ReplyInfo = ReplyInfo + "\n" + string(ChildNodeName);
    }

    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
int dir_HELP(fstream& Disk_Pointer, string AddBuf)
{
    string CurDirName;//������ʱ�洢��ǰλ��
    if (AddBuf.length() == 0)//�����ַΪ�գ����ص�ǰ���̿����
    {
        return getBLOCK(Disk_Pointer);
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//�Ӹ���㿪ʼ����
        /*����ָ��ķָ���/����Ԥ����*/
        for (int i = 0; i < AddBuf.length(); i++)//�ȴ����ַ�е�/����
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//��/�滻Ϊ�ո񣬱�������
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*�жϸ���ַ�Ƿ�������*/
        if (CurDirName != "cmd")//�������ַ����
        {
            return 0;
        }
        /*ͨ���ӽ�㲻�Ͻ��ж�λ*/
        while (1)//�������ַ���AddressBuf�л�������
        {
            AddStr >> CurDirName;//������һ��Ŀ¼
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//����ҵ��˶�Ӧ�����ļ�
            {
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//��ת����Ӧ��λ��
            }
            else//���û��֪����Ӧ�����ļ�
            {
                return 0;
            }
            if (AddStr.eof())//��������һ��Ŀ¼֮�󵽵�����ײ�������
            {
                return getBLOCK(Disk_Pointer);
            }
        }
    }
    else
    {
        return 0;
    }
}
void ShowAllInfo(fstream& Disk_Pointer, int blocknum, string& ReplyInfo)
{
    char chartpt_buf;
    int ORZNUM = getBLOCK(Disk_Pointer);
    ReplyInfo = ReplyInfo + "\n" + "Ŀ¼����" + string(F_docNa(Disk_Pointer, blocknum));

    jump2whePTR(Disk_Pointer, blocknum, 73);//��ת������Ա��������λ��
    ReplyInfo = ReplyInfo + "\n" + "����Ա�������ͣ�";
    for (int i = 0; i < 3; i++)//��ȡ����Ա��������
    {
        Disk_Pointer >> chartpt_buf;
        ReplyInfo += chartpt_buf;
    }

    jump2whePTR(Disk_Pointer, blocknum, 77);//��ת����ͨ�û���������λ��
    ReplyInfo = ReplyInfo + "\n" + "��ͨ�û��������ͣ�";
    for (int i = 0; i < 3; i++)//��ȡ��ͨ�û���������
    {
        Disk_Pointer >> chartpt_buf;
        ReplyInfo += chartpt_buf;
    }

    jump2whePTR(Disk_Pointer, blocknum, 80);//��ת�������λ��
    ReplyInfo = ReplyInfo + "\n" + "������ַ��";
    for (int i = 0; i < 32; i++)//��ȡ������ַ
    {
        Disk_Pointer >> chartpt_buf;
        ReplyInfo += chartpt_buf;
    }

    jump2whePTR(Disk_Pointer, blocknum, 112);//��ת���ӽ��λ��
    ReplyInfo = ReplyInfo + "\n" + "�ӽ���ַ��";
    for (int i = 0; i < 3; i++)//��ȡ�ӽ���ַ
    {
        ReplyInfo += "\n";
        for (int j = 0; j < 32; j++)
        {
            Disk_Pointer >> chartpt_buf;
            ReplyInfo += chartpt_buf;
        }
    }

    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
/*md*/
string mdAddLocation(fstream& Disk_Pointer, string AddBuf)
{
    string ErrorReturn = "";
    string CurDirName;//������ʱ�洢��ǰλ��
    if (AddBuf.length() == 0)//�����ַΪ�գ�����
    {
        return ErrorReturn;
    }

    /*�ж�������ַ�Ƿ�Ϊ���Ե�ַ������ǣ���ת����Ӧλ�ò�������Ҫ�������ļ�����������ǣ�ֱ�ӷ�����Ҫ�������ļ���*/
    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//�Ӹ���㿪ʼ����
        /*����ָ��ķָ���/����Ԥ����*/
        for (int i = 0; i < AddBuf.length(); i++)//�ȴ����ַ�е�/����
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//��/�滻Ϊ�ո񣬱�������
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*�жϸ���ַ�Ƿ�������*/
        if (CurDirName != "cmd")//�������ַ����
        {
            return ErrorReturn;
        }

        /*ͨ���ӽ�㲻�Ͻ��ж�λ*/
        while (1)//�������ַ���AddressBuf�л�������
        {
            AddStr >> CurDirName;//������һ��Ŀ¼
            if (AddStr.eof())//��������һ��Ŀ¼֮�󵽵�����ײ�����ô��ʱ��������־��Ƕ�Ӧ���ļ���
            {
                break;
            }
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//����ҵ��˶�Ӧ�����ļ�
            {
                if (F_docTy(Disk_Pointer, ChildBlockSqe) != 0)//������ļ�����Ŀ¼
                {
                    return ErrorReturn;
                }
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//��ת����Ӧ��λ��
            }
            else//���û��֪����Ӧ�����ļ�
            {
                return ErrorReturn;
            }
        }
    }
    else
    {
        for (int i = 1; i < AddBuf.length(); i++)//�ж��ļ�������û��/����
        {
            if (AddBuf[i] == '/')
            {
                return ErrorReturn;
            }
        }
        CurDirName = AddBuf;
    }
    for (int i = 0; i < CurDirName.length(); i++)
    {
        if (CurDirName[i] == '.')
        {
          //  return ErrorReturn;
        }
    }
    return CurDirName;
}
/*rd*/
int IsDirEmpty(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    char chartpt_buf;
    for (int i = 0; i < 3; i++)
    {
        jump2whePTR(Disk_Pointer, blocknum, 112 + 32 * i);
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '1')
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);
            return 0;
        }
    }
    return 1;
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
int IsFileEmpty(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 0);
    char chartpt_buf;
    for (int i = 0; i < 1024; i++)
    {
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '1')return 1;
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return 0;
}
int rd_HELP(fstream& Disk_Pointer, string AddBuf)
{
    string CurDirName;//������ʱ�洢��ǰλ��
    if (AddBuf.length() == 0)//�����ַΪ�գ����ص�ǰ���̿����
    {
        return getBLOCK(Disk_Pointer);
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//�Ӹ���㿪ʼ����
        /*����ָ��ķָ���/����Ԥ����*/
        for (int i = 0; i < AddBuf.length(); i++)//�ȴ����ַ�е�/����
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//��/�滻Ϊ�ո񣬱�������
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*�жϸ���ַ�Ƿ�������*/
        if (CurDirName != "cmd")//�������ַ����
        {
            return 0;
        }
        /*ͨ���ӽ�㲻�Ͻ��ж�λ*/
        while (1)//�������ַ���AddressBuf�л�������
        {
            AddStr >> CurDirName;//������һ��Ŀ¼
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//����ҵ��˶�Ӧ�����ļ�
            {
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//��ת����Ӧ��λ��
            }
            else//���û���ҵ���Ӧ�����ļ�
            {
                return 0;
            }
            if (AddStr.eof())//��������һ��Ŀ¼֮�󵽵�����ײ�������
            {
                if (F_docTy(Disk_Pointer, getBLOCK(Disk_Pointer)) != 0)
                {
                    return 0;
                }
                return getBLOCK(Disk_Pointer);
            }
        }
    }
    else
    {
        return 0;
    }
}
void rdDir(fstream& Disk_Pointer, int blocknum)
{
    int FileType = F_docTy(Disk_Pointer, blocknum);
    if (FileType == 0)//�����Ӧ����Ŀ¼
    {
        if (IsDirEmpty(Disk_Pointer, blocknum))
        {
            /*�������Ķ�Ӧ�ӽ���ַ���*/
            int* ParNode = F_docFAddr(Disk_Pointer, blocknum);
            char* DocName = F_docNa(Disk_Pointer, blocknum);
            int** ParChildNode = F_docCHILDddr(Disk_Pointer, addr2blocknum(ParNode));

            if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[0]))))
            {
                jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112);
                for (int i = 0; i < 32; i++)
                {
                    Disk_Pointer << 0;
                }
            }
            else if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[1]))))
            {
                jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112 + 32);
                for (int i = 0; i < 32; i++)
                {
                    Disk_Pointer << 0;
                }
            }
            else if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[2]))))
            {
                jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112 + 64);
                for (int i = 0; i < 32; i++)
                {
                    Disk_Pointer << 0;
                }
            }

            /*��Ŀ¼i���������ɾ��*/
            jump2whePTR(Disk_Pointer, blocknum, 0);
            bitmap_engine(Disk_Pointer, getBLOCK(Disk_Pointer), 0);//��λͼ�ж�Ӧi����λ�����
            for (int i = 0; i < 1024; i++)
            {
                Disk_Pointer << 0;
            }
            return;
        }
        else
        {
            int** INIttpt_buf = F_docCHILDddr(Disk_Pointer, blocknum);
            /*ɾ�ӽ��*/
            if (INIttpt_buf[0][0] == 1)
            {
                rdDir(Disk_Pointer, addr2blocknum(INIttpt_buf[0]));
            }
            if (INIttpt_buf[1][0] == 1)
            {
                rdDir(Disk_Pointer, addr2blocknum(INIttpt_buf[1]));
            }
            if (INIttpt_buf[2][0] == 1)
            {
                rdDir(Disk_Pointer, addr2blocknum(INIttpt_buf[2]));
            }

            /*ɾ�Լ�*/
            if (IsDirEmpty(Disk_Pointer, blocknum))
            {
                rdDir(Disk_Pointer, blocknum);
            }
        }
    }
    else//�����Ӧ�����ļ�
    {
        int* DocContextAdd = F_doccontnode(Disk_Pointer, blocknum);

        /*���ļ������������*/
        bitmap_engine(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
        jump2whePTR(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
        for (int i = 0; i < 1024; i++)
        {
            Disk_Pointer << 0;
        }

        /*�������Ķ�Ӧ�ӽ���ַ���*/
        int* ParNode = F_docFAddr(Disk_Pointer, blocknum);
        char* DocName = F_docNa(Disk_Pointer, blocknum);
        int** ParChildNode = F_docCHILDddr(Disk_Pointer, addr2blocknum(ParNode));

        if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[0]))))
        {
            jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112);
            for (int i = 0; i < 32; i++)
            {
                Disk_Pointer << 0;
            }
        }
        else if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[1]))))
        {
            jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112 + 32);
            for (int i = 0; i < 32; i++)
            {
                Disk_Pointer << 0;
            }
        }
        else if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[2]))))
        {
            jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112 + 64);
            for (int i = 0; i < 32; i++)
            {
                Disk_Pointer << 0;
            }
        }

        /*���ļ�i�����������*/
        bitmap_engine(Disk_Pointer, blocknum, 0);
        jump2whePTR(Disk_Pointer, blocknum, 0);
        for (int i = 0; i < 240; i++)
        {
            Disk_Pointer << 0;
        }
        return;
    }
}
/*newfile*/
string FileNameTest(string FileName)
{
    string Right = "";
    if (FileName.length() == 0)
    {
        return "��ַ���󣬴���ʧ��!";
    }
    if (FileName.length() > 8)
    {
        return "�ļ�������������ʧ�ܣ�";
    }
    int CountPoint = 0;
    for (int i = 0; i < FileName.length(); i++)
    {
        if (FileName[i] == '.')
        {
            CountPoint++;
        }
        if (FileName[i] == '*' || FileName[i] == '/')
        {
            return "�ļ�����ʽ���󣬴���ʧ�ܣ�";
        }
    }
    if (CountPoint != 1)
    {
        return "�ļ�����ʽ���󣬴���ʧ�ܣ�";
    }
    return Right;
}
string FileAccTest(string Acc)
{
    string Right = "";
    if (Acc.length() != 6)
    {
        return "�������ͳ��ȴ��󣬴���ʧ��!";
    }
    for (int i = 0; i < Acc.length(); i++)
    {
        if (Acc[i] != '0' && Acc[i] != '1')
        {
            return "�������͸�ʽ���󣬴���ʧ��!";
        }
    }
    return Right;
}
string newfile_HELP(fstream& Disk_Pointer, string AddBuf)
{
    string ErrorReturn = "";
    string CurDirName;//������ʱ�洢��ǰλ��
    if (AddBuf.length() == 0)//�����ַΪ�գ�����
    {
        return ErrorReturn;
    }

    /*�ж�������ַ�Ƿ�Ϊ���Ե�ַ������ǣ���ת����Ӧλ�ò�������Ҫ�������ļ�����������ǣ�ֱ�ӷ�����Ҫ�������ļ���*/
    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//�Ӹ���㿪ʼ����
        /*����ָ��ķָ���/����Ԥ����*/
        for (int i = 0; i < AddBuf.length(); i++)//�ȴ����ַ�е�/����
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//��/�滻Ϊ�ո񣬱�������
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*�жϸ���ַ�Ƿ�������*/
        if (CurDirName != "cmd")//�������ַ����
        {
            return ErrorReturn;
        }

        /*ͨ���ӽ�㲻�Ͻ��ж�λ*/
        while (1)//�������ַ���AddressBuf�л�������
        {
            AddStr >> CurDirName;//������һ��Ŀ¼
            if (AddStr.eof())//��������һ��Ŀ¼֮�󵽵�����ײ�����ô��ʱ��������־��Ƕ�Ӧ���ļ���
            {
                break;
            }
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//����ҵ��˶�Ӧ�����ļ�
            {
                if (F_docTy(Disk_Pointer, ChildBlockSqe) != 0)//������ļ�����Ŀ¼
                {
                    return ErrorReturn;
                }
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//��ת����Ӧ��λ��
            }
            else//���û��֪����Ӧ�����ļ�
            {
                return ErrorReturn;
            }
        }
    }
    else
    {
        for (int i = 1; i < AddBuf.length(); i++)//�ж��ļ�������û��/����
        {
            if (AddBuf[i] == '/')
            {
                return ErrorReturn;
            }
        }
        CurDirName = AddBuf;
    }
    return CurDirName;
}
/*cat*/
int cat_HELP(fstream& Disk_Pointer, string AddBuf)
{
    string CurDirName;//������ʱ�洢��ǰλ��
    if (AddBuf.length() == 0)//�����ַΪ�գ����ص�ǰ���̿����
    {
        return 0;
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//�Ӹ���㿪ʼ����
        /*����ָ��ķָ���/����Ԥ����*/
        for (int i = 0; i < AddBuf.length(); i++)//�ȴ����ַ�е�/����
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//��/�滻Ϊ�ո񣬱�������
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*�жϸ���ַ�Ƿ�������*/
        if (CurDirName != "cmd")//�������ַ����
        {
            return 0;
        }
        /*ͨ���ӽ�㲻�Ͻ��ж�λ*/
        while (1)//�������ַ���AddressBuf�л�������
        {
            AddStr >> CurDirName;//������һ��Ŀ¼
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//����ҵ��˶�Ӧ�����ļ�
            {
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//��ת����Ӧ��λ��
            }
            else//���û��֪����Ӧ�����ļ�
            {
                return 0;
            }
            if (AddStr.eof())//��������һ��Ŀ¼֮�󵽵�����ײ�������
            {
                if (F_docTy(Disk_Pointer, getBLOCK(Disk_Pointer)) != 1)//������ļ���һ��Ŀ¼
                {
                    return 0;
                }
                return getBLOCK(Disk_Pointer);
            }
        }
    }
    else
    {
        return 0;
    }
}
string GetFileContext(fstream& Disk_Pointer, int blocknum)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    jump2whePTR(Disk_Pointer, blocknum, 0);
    string FileContext = "";
    char chartpt_buf;
    int* TempOutputIntArr;
    for (int i = 0; i < 128; i++)
    {
        TempOutputIntArr = OP8b(Disk_Pointer);
        chartpt_buf = int_82char(TempOutputIntArr);
        FileContext += chartpt_buf;
    }
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return FileContext;
}
/*del*/
void delDoc(fstream& Disk_Pointer, int blocknum)
{
    int* DocContextAdd = F_doccontnode(Disk_Pointer, blocknum);

    /*���ļ������������*/
    bitmap_engine(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
    jump2whePTR(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
    for (int i = 0; i < 1024; i++)
    {
        Disk_Pointer << 0;
    }

    /*�������Ķ�Ӧ�ӽ���ַ���*/
    int* ParNode = F_docFAddr(Disk_Pointer, blocknum);
    char* DocName = F_docNa(Disk_Pointer, blocknum);
    int** ParChildNode = F_docCHILDddr(Disk_Pointer, addr2blocknum(ParNode));

    if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[0]))))
    {
        jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112);
        for (int i = 0; i < 32; i++)
        {
            Disk_Pointer << 0;
        }
    }
    else if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[1]))))
    {
        jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112 + 32);
        for (int i = 0; i < 32; i++)
        {
            Disk_Pointer << 0;
        }
    }
    else if (string(DocName) == string(F_docNa(Disk_Pointer, addr2blocknum(ParChildNode[2]))))
    {
        jump2whePTR(Disk_Pointer, addr2blocknum(ParNode), 112 + 64);
        for (int i = 0; i < 32; i++)
        {
            Disk_Pointer << 0;
        }
    }

    /*���ļ�i�����������*/
    bitmap_engine(Disk_Pointer, blocknum, 0);
    jump2whePTR(Disk_Pointer, blocknum, 0);
    for (int i = 0; i < 240; i++)
    {
        Disk_Pointer << 0;
    }
    return;
}
string GetWindowsFileName(string path)
{
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '\\')
        {
            path[i] = ' ';
        }
    }
    istringstream TempInputStr(path);
    string TempStr;
    while (!TempInputStr.eof())
    {
        TempInputStr >> TempStr;
    }
    return TempStr;
}
string CopyNewFile(fstream& Disk_Pointer, istringstream& Buf)
{
    int ORZNUM = getBLOCK(Disk_Pointer);
    string newfileNameBuf;//�û��洢���������еĵ�ַ����
    string newfileAccBuf;
    string newfileContextBuf;
    Buf >> newfileNameBuf;
    Buf >> newfileAccBuf;
    Buf >> newfileContextBuf;

    string CurDirName = mdAddLocation(Disk_Pointer, newfileNameBuf);
    /*�ļ�����ʽ���*/
    string ReplyInfo = FileNameTest(CurDirName);
    if (ReplyInfo != "")
    {
        return ReplyInfo;
    }

    /*�������͸�ʽ���*/
    ReplyInfo = FileAccTest(newfileAccBuf);
    if (ReplyInfo != "")
    {
        return ReplyInfo;
    }

    int NewINodeBlockSqe = F_spareInode(Disk_Pointer);
    int NewDocBlockSqe = F_sparedoc(Disk_Pointer);

    /*�ж��ļ�ϵͳ�Ƿ��пռ�*/
    if (!NewINodeBlockSqe)//����ļ�ϵͳ����û�пռ䣬����ʧ��
    {
        return "�ļ�ϵͳ���޿��пռ䣬����ʧ�ܣ�";
    }
    if (!NewDocBlockSqe)//����ļ�ϵͳ����û�пռ䣬����ʧ��
    {
        return "�ļ�ϵͳ���޿��пռ䣬����ʧ�ܣ�";
    }

    /*�ж��������ļ����Ƿ����ӽ�����ļ����ظ�*/
    if (document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName))
    {
        return "�ļ����ظ�������ʧ�ܣ�";
    }

    /*�ж��ӽ���ǲ�������*/
    int FreeChildSqe = F_sparechildnode(Disk_Pointer, getBLOCK(Disk_Pointer));
    if (FreeChildSqe)//û�������ӽ����Ϊ�Ѿ�ʹ�ã�������32λ��ַ
    {
        jump2whePTR(Disk_Pointer, getBLOCK(Disk_Pointer), 112 + 32 * (FreeChildSqe - 1));//��ת����Ӧ���ӽ��
        int* INode = blocknum2addr(NewINodeBlockSqe);
        INode[0] = 1;//����λ��Ϊ1����ʾ���ӽ���Ѿ���ʹ��
        inputintaddr(Disk_Pointer, INode, 32);//����32λ�ӽ��
        jump2whePTR(Disk_Pointer, getBLOCK(Disk_Pointer), 0);//���ؿ�ͷ
    }
    else
    {
        return "��ǰ�ļ������ļ��Ѵ����ޣ�����ʧ�ܣ�";
    }

    /*�����ļ����г�ʼ��*/
    InputDocName(Disk_Pointer, NewINodeBlockSqe, CurDirName);//�����ļ���
    InputParNode(Disk_Pointer, NewINodeBlockSqe, blocknum2addr(getBLOCK(Disk_Pointer)));//���븸����ַ
    InputAcc(Disk_Pointer, NewINodeBlockSqe, newfileAccBuf);//�����ļ���������
    inputcontT(Disk_Pointer, NewINodeBlockSqe, NewDocBlockSqe, newfileContextBuf);//�����ļ�����
    InputFileType(Disk_Pointer, NewINodeBlockSqe, 1);//�����ļ�����
    bitmap_engine(Disk_Pointer, NewINodeBlockSqe, 1);
    bitmap_engine(Disk_Pointer, NewDocBlockSqe, 1);
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return "�ļ������ɹ���";
}
void ConsistencyCheck(fstream& Disk_Pointer, int blocknum)
{
    jump2whePTR(Disk_Pointer, blocknum, 0);
    int FileType = F_docTy(Disk_Pointer, blocknum);
    bitmap_engine(Disk_Pointer, blocknum, 1);//�Ѹ��ļ���Ӧ��λͼ������Ϊ1
    if (FileType == 1)//�����һ���ļ�
    {
        bitmap_engine(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, blocknum)), 1);//���ļ����ݶ�Ӧ��λͼ������Ϊ1
        return;
    }
    else
    {
        char chartpt_buf;
        jump2whePTR(Disk_Pointer, blocknum, 112);
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '1')
        {
            jump2whePTR(Disk_Pointer, blocknum, 112);
            int* ChildNodeAdd = OP32b(Disk_Pointer);
            ConsistencyCheck(Disk_Pointer, addr2blocknum(ChildNodeAdd));
        }

        jump2whePTR(Disk_Pointer, blocknum, 144);
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '1')
        {
            jump2whePTR(Disk_Pointer, blocknum, 144);
            int* ChildNodeAdd = OP32b(Disk_Pointer);
            ConsistencyCheck(Disk_Pointer, addr2blocknum(ChildNodeAdd));
        }

        jump2whePTR(Disk_Pointer, blocknum, 176);
        Disk_Pointer >> chartpt_buf;
        if (chartpt_buf == '1')
        {
            jump2whePTR(Disk_Pointer, blocknum, 176);
            int* ChildNodeAdd = OP32b(Disk_Pointer);
            ConsistencyCheck(Disk_Pointer, addr2blocknum(ChildNodeAdd));
        }
        return;
    }
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