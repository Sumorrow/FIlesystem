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
#include"N1k0.h"
 int main()
{
    std::string FILENAMED = "F:\\ideaoo\\os_linuxmodelafter_filesystem\\db\\diskapp.txt";
    fstream Disk_Pointer(FILENAMED, ios::in | ios::out);
    Init(Disk_Pointer);
    jump2whePTR(Disk_Pointer, 101, 0);

    /*�ظ���Ϣ�ռ䣬���ڷ�������ͻ��˻ظ���Ϣ*/
    HANDLE ReplyInfoSpace = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // �����ļ����
        NULL,   // Ĭ�ϰ�ȫ����
        PAGE_READWRITE,   // �ɶ���д
        0,   // ��λ�ļ���С
        BUF_SIZE,   // ��λ�ļ���С
        "ReplyInfoSpace"   // �����ڴ�����
    );

    LPVOID ReplyInfoSend = MapViewOfFile(
        ReplyInfoSpace,            // �����ڴ�ľ��
        FILE_MAP_ALL_ACCESS, // �ɶ�д���
        0,
        0,
        BUF_SIZE
    );

    /*дռ�ÿռ䣬���ڸ��ٿͻ�����ǰд��״̬*/
    HANDLE WSPACE = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // �����ļ����
        NULL,   // Ĭ�ϰ�ȫ����
        PAGE_READWRITE,   // �ɶ���д
        0,   // ��λ�ļ���С
        BUF_SIZE,   // ��λ�ļ���С
        "WSPACE"   // �����ڴ�����
    );

    //ӳ�仺������ͼ���õ�ָ�����ڴ��ָ��
    LPVOID WriteSend = MapViewOfFile(
        WSPACE,            // �����ڴ�ľ��
        FILE_MAP_ALL_ACCESS, // �ɶ�д���
        0,
        0,
        BUF_SIZE
    );
    char WriteSendBuf[BUF_SIZE] = { 0 };

    /*��rd��ص�����*/
    int rdIsNotEmpty = 0;//01��Ǳ�������ʾrd��Ŀ¼�ǲ��ǿյ�
    int rdOriSqe = 0;
    int rdTarSqe = 0;
    string rdBuf = "";//�û��洢���������еĵ�ַ����
    int WriteLock = 0;


    /*��ʼ���ϵؽ�����Ϣ*/
    while (1)
    {
        //Sleep(1000);
        // �򿪹�����ļ�����
        HANDLE SHARED_FILESPACE = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "SHARED_FILESPACE");
        LPVOID InstructionRec = MapViewOfFile(SHARED_FILESPACE, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (!InstructionRec)//�ж�ָ���Ƿ�Ϊ�գ������ڴ�δ������ʱ��Ϊ�գ�
        {
            printf("Waiting......\n");
            Sleep(1000);
            continue;
        }

        if (strlen((char*)InstructionRec))//�жϹ����ڴ����Ƿ�������
        {
            char UserAccBuf[BUF_SIZE] = { 0 };//�û�Ȩ�޻���
            HANDLE SHARED_FILEQUL = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "SHARED_FILEQUL");
            LPVOID AccRec = MapViewOfFile(SHARED_FILEQUL, FILE_MAP_ALL_ACCESS, 0, 0, 0);
            SMemoinfoCY(UserAccBuf, AccRec);

            char InstructionRecBuffer[BUF_SIZE] = { 0 };
            SMemoinfoCY(InstructionRecBuffer, InstructionRec);// �������ڴ����ݿ�������
            istringstream Buf(InstructionRecBuffer);//������ת��Ϊ������
            string InstructionBuf;//���ڴ洢���������е�ָ���

            Buf >> InstructionBuf;//�����û������ָ��
            cout << "Get info:" << InstructionRecBuffer << endl;//����ͻ����������Ϣ
            if (rdIsNotEmpty == 1)
            {
                if (InstructionBuf == "y")
                {
                    rdDir(Disk_Pointer, rdTarSqe);
                    bitmap_engine(Disk_Pointer, rdTarSqe, 0);
                    response("ɾ�����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    rdIsNotEmpty = 0;
                    rdOriSqe = 0;
                    rdBuf = "";
                    rdTarSqe = 0;
                    continue;
                }
                else if (InstructionBuf == "n")
                {
                    response("����ȡ��", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    rdIsNotEmpty = 0;
                    rdOriSqe = 0;
                    rdBuf = "";
                    rdTarSqe = 0;
                    continue;
                }
                else
                {
                    response("ָ�����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    rdIsNotEmpty = 0;
                    rdOriSqe = 0;
                    rdBuf = "";
                    rdTarSqe = 0;
                    continue;
                }
            }
            else if (InstructionBuf == "info")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string ReplyInfo = "";
                string DocSysHost;
                string DocSysSize;
                string DiskBlockSize;
                string SuperBlockSqe;
                string BitMapSqe;
                string RootSqe;
                string INodeSqe;
                string DocSqe;
                DocSysHost = F_docNa(Disk_Pointer, 0);
                jump2whePTR(Disk_Pointer, 0, 64);
                DocSysSize = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                jump2whePTR(Disk_Pointer, 0, 96);
                DiskBlockSize = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                jump2whePTR(Disk_Pointer, 0, 128);
                SuperBlockSqe = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                jump2whePTR(Disk_Pointer, 0, 160);
                BitMapSqe = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                jump2whePTR(Disk_Pointer, 0, 192);
                RootSqe = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                jump2whePTR(Disk_Pointer, 0, 224);
                INodeSqe = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                jump2whePTR(Disk_Pointer, 0, 256);
                DocSqe = to_string(addr2blocknum(OP32b(Disk_Pointer)));
                ReplyInfo = ReplyInfo + "�ļ�ϵͳ����:" + DocSysHost + "\n";
                ReplyInfo = ReplyInfo + "�ļ�ϵͳ��С:" + DocSysSize + "Mb" + "\n";
                ReplyInfo = ReplyInfo + "���̿��С:" + DiskBlockSize + "b" + "\n";
                ReplyInfo = ReplyInfo + "���������:" + SuperBlockSqe + "\n";
                ReplyInfo = ReplyInfo + "λͼ���:" + BitMapSqe + "\n";
                ReplyInfo = ReplyInfo + "��������:" + RootSqe + "\n";
                ReplyInfo = ReplyInfo + "I��������:" + INodeSqe + "\n";
                ReplyInfo = ReplyInfo + "I�����ʣ��ռ�:" + to_string(G_InodeLspace(Disk_Pointer)) + "\n";
                ReplyInfo = ReplyInfo + "�ļ������:" + DocSqe + "\n";
                ReplyInfo = ReplyInfo + "�ļ���ʣ��ռ�:" + to_string(G_docLspace(Disk_Pointer));
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                response(ReplyInfo, ReplyInfoSend);
                continue;
            }
            else if (InstructionBuf == "cd")
            {
                string cdBuf;//�û��洢���������еĵ�ַ����
                Buf >> cdBuf;
                string ReplyInfo = cd_HELP(Disk_Pointer, cdBuf);
                response(ReplyInfo, ReplyInfoSend);
            }
            else if (InstructionBuf == "dir")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string ReplyInfo = "";
                string dirBuf;//�û��洢���������еĵ�ַ����
                Buf >> dirBuf;
                if (dirBuf == "/s")//�����/s����
                {
                    ReplyInfo += "��ǰĿ¼�µ������ļ�����Ŀ¼Ϊ��";
                    ShowAllChildNodeName(Disk_Pointer, getBLOCK(Disk_Pointer), ReplyInfo);
                    response(ReplyInfo, ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                int CurBlockSqe = dir_HELP(Disk_Pointer, dirBuf);//�ļ�ָ�붨λ
                if (CurBlockSqe == 0)//������ش�����Ϣ
                {
                    response("��ַ���󣬴���ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }
                ReplyInfo += "��ǰĿ¼�µ���ϢΪ��";
                ShowAllInfo(Disk_Pointer, CurBlockSqe, ReplyInfo);
                response(ReplyInfo, ReplyInfoSend);
                continue;

                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "md")//������Ŀ¼
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string mdBuf;//�û��洢���������еĵ�ַ����
                Buf >> mdBuf;

                string CurDirName = mdAddLocation(Disk_Pointer, mdBuf);
                if (CurDirName == "")
                {
                    response("��ַ���󣬴���ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }

                /*�ж��½�Ŀ¼�ĳ���*/
                if (CurDirName.length() > 8)//Ŀ¼�����ܴ���8λ
                {
                    response("Ŀ¼������������ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }

                int NewINodeBlockSqe = F_spareInode(Disk_Pointer);

                /*�ж��ļ�ϵͳ�Ƿ��пռ�*/
                if (!NewINodeBlockSqe)//����ļ�ϵͳ����û�пռ䣬����ʧ��
                {
                    response("�ļ�ϵͳ���޿��пռ䣬����ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }

                /*�ж��������ļ����Ƿ����ӽ�����ļ����ظ�*/
                if (document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName))
                {
                    response("�ļ����ظ�������ʧ�ܣ�", ReplyInfoSend);
                    continue;
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
                    response("��ǰ�ļ������ļ��Ѵ����ޣ�����ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }

                /*�����ļ����г�ʼ��*/
                InputDocName(Disk_Pointer, NewINodeBlockSqe, CurDirName);
                InputParNode(Disk_Pointer, NewINodeBlockSqe, blocknum2addr(getBLOCK(Disk_Pointer)));
                bitmap_engine(Disk_Pointer, NewINodeBlockSqe, 1);
                response("Ŀ¼�����ɹ���", ReplyInfoSend);
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                continue;
            }
            else if (InstructionBuf == "rd")
            {
                rdOriSqe = getBLOCK(Disk_Pointer);
                Buf >> rdBuf;
                rdTarSqe = rd_HELP(Disk_Pointer, rdBuf);//Ѱ��Ӧ��ɾ����Ŀ����̿�
                if (rdTarSqe == 1)//����Ǹ�Ŀ¼
                {
                    response("��Ŀ¼����ɾ����ɾ��ʧ�ܣ�", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    continue;
                }
                if (F_docTy(Disk_Pointer, rdTarSqe) != 0)//���Ŀ���ļ�����Ŀ¼
                {
                    response("Ŀ���ļ�Ϊ��ͨ�ļ���ɾ��ʧ�ܣ�", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    continue;
                }
                if (rdTarSqe)
                {
                    if (!IsDirEmpty(Disk_Pointer, rdTarSqe))//����ǿ�
                    {
                        rdIsNotEmpty = 1;
                        response("Ŀ��Ŀ¼�ǿգ��Ƿ���Ҫɾ����y/n", ReplyInfoSend);
                        continue;
                    }
                    else//����ǿյ�
                    {
                        rdDir(Disk_Pointer, rdTarSqe);//ɾ����Ӧ���
                        bitmap_engine(Disk_Pointer, rdTarSqe, 0);
                        response("Ŀ��Ŀ¼ɾ�����", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                        rdIsNotEmpty = 0;//������ϵ����0
                        rdOriSqe = 0;
                        rdBuf = "";
                        rdTarSqe = 0;
                        continue;
                    }
                }
                else//���û���Ҷ�Ŀ����̿飬���ش�����Ϣ
                {
                    response("��ַ����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    continue;
                }
                jump2whePTR(Disk_Pointer, rdOriSqe, 0);
            }
            else if (InstructionBuf == "newfile")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string newfileNameBuf;//�û��洢���������еĵ�ַ����
                string newfileAccBuf;
                string newfileContextBuf;
                Buf >> newfileNameBuf;
                Buf >> newfileAccBuf;
                Buf >> newfileContextBuf;

                string CurDirName = newfile_HELP(Disk_Pointer, newfileNameBuf);
                /*�ļ�����ʽ���*/
                string ReplyInfo = FileNameTest(CurDirName);
                if (ReplyInfo != "")
                {
                    response(ReplyInfo, ReplyInfoSend);
                    continue;
                }

                /*�������͸�ʽ���*/
                ReplyInfo = FileAccTest(newfileAccBuf);
                if (ReplyInfo != "")
                {
                    response(ReplyInfo, ReplyInfoSend);
                    continue;
                }

                int NewINodeBlockSqe = F_spareInode(Disk_Pointer);
                int NewDocBlockSqe = F_sparedoc(Disk_Pointer);

                /*�ж��ļ�ϵͳ�Ƿ��пռ�*/
                if (!NewINodeBlockSqe)//����ļ�ϵͳ����û�пռ䣬����ʧ��
                {
                    response("�ļ�ϵͳ���޿��пռ䣬����ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }
                if (!NewDocBlockSqe)//����ļ�ϵͳ����û�пռ䣬����ʧ��
                {
                    response("�ļ�ϵͳ���޿��пռ䣬����ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }

                /*�ж��������ļ����Ƿ����ӽ�����ļ����ظ�*/
                if (document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName))
                {
                    response("�ļ����ظ�������ʧ�ܣ�", ReplyInfoSend);
                    continue;
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
                    response("��ǰ�ļ������ļ��Ѵ����ޣ�����ʧ�ܣ�", ReplyInfoSend);
                    continue;
                }

                /*�����ļ����г�ʼ��*/
                InputDocName(Disk_Pointer, NewINodeBlockSqe, CurDirName);//�����ļ���
                InputParNode(Disk_Pointer, NewINodeBlockSqe, blocknum2addr(getBLOCK(Disk_Pointer)));//���븸����ַ
                InputAcc(Disk_Pointer, NewINodeBlockSqe, newfileAccBuf);//�����ļ���������
                inputcontT(Disk_Pointer, NewINodeBlockSqe, NewDocBlockSqe, newfileContextBuf);//�����ļ�����
                InputFileType(Disk_Pointer, NewINodeBlockSqe, 1);//�����ļ�����
                bitmap_engine(Disk_Pointer, NewINodeBlockSqe, 1);
                bitmap_engine(Disk_Pointer, NewDocBlockSqe, 1);
                response("�ļ������ɹ���", ReplyInfoSend);
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                continue;
            }
            else if (InstructionBuf == "cat")
            {
                 int ORZNUM = getBLOCK(Disk_Pointer);
                string mdBuf;//�û��洢���������еĵ�ַ����
                Buf >> mdBuf;
                int TarSqe = cat_HELP(Disk_Pointer, mdBuf);
                if (F_docTy(Disk_Pointer, TarSqe) != 1)//���Ŀ���ļ�������ͨ�ļ�
                {
                    response("Ŀ���ļ�������ͨ�ļ���ָ�����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                if (TarSqe)
                {
                    int* ComAcc = F_docUACC(Disk_Pointer, TarSqe);//��ѯ��ͨ�û�����Ȩ��
                    int* SysAcc = F_docSACC(Disk_Pointer, TarSqe);//��ѯϵͳ�û�����Ȩ��
                    if (!((ComAcc[0] == 1 && UserAccBuf[0] == '1') || (SysAcc[0] == 1 && UserAccBuf[0] == '0')))//�ж�����Ȩ��д����ļ�
                    {
                        response("��Ȩ�޶�ȡ���ļ���", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    response(GetFileContext(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, TarSqe))), ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("��ַ����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "write")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string writeBuf;//�û��洢���������еĵ�ַ����
                string InputInfo;//��������ļ�����
                Buf >> writeBuf;
                Buf >> InputInfo;
                int TarSqe = cat_HELP(Disk_Pointer, writeBuf);
                if (F_docTy(Disk_Pointer, TarSqe) != 1)//���Ŀ���ļ�������ͨ�ļ�
                {
                    response("Ŀ���ļ�������ͨ�ļ���ָ�����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                if (TarSqe)
                {
                    int* ComAcc = F_docUACC(Disk_Pointer, TarSqe);//��ѯ��ͨ�û�����Ȩ��
                    int* SysAcc = F_docSACC(Disk_Pointer, TarSqe);//��ѯϵͳ�û�����Ȩ��
                    if (InputInfo.length() > 128)
                    {
                        response("�ļ����ݹ��࣬�޷�д�룡", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    if (!((ComAcc[1] == 1 && UserAccBuf[0] == '1') || (SysAcc[1] == 1 && UserAccBuf[0] == '0')))//�ж�����Ȩ��д����ļ�
                    {
                        response("��Ȩ��д����ļ���", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    /*���Դ�ļ�*/
                    jump2whePTR(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, TarSqe)), 0);
                    for (int i = 0; i < 1024; i++)
                    {
                        Disk_Pointer << 0;
                    }
                    jump2whePTR(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, TarSqe)), 0);

                    /*дʱ�ӳ�*/
                    strcpy_s((char*)WriteSend, writeBuf.length() + 1, const_cast<char*>(writeBuf.c_str()));
                    Sleep(10000);
                    SMemoCL(WriteSend);

                    /*д��*/
                    inputcharaddr(Disk_Pointer, const_cast<char*>(InputInfo.c_str()));
                    response("д��ɹ���", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("��ַ����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "copy")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string OriAdd;
                string TarAdd;
                string Parameter;

                Buf >> OriAdd;
                Buf >> TarAdd;
                Buf >> Parameter;

                if (Parameter == "")//���û�в���
                {
                    /*Ѱ��Դ�ļ�����*/
                    int OriAddSqe = cat_HELP(Disk_Pointer, OriAdd);
                    string OriContext;
                    if (OriAddSqe)
                    {
                        OriContext = GetFileContext(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, OriAddSqe)));
                    }
                    else
                    {
                        response("Դ��ַ����", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }

                    int TarAddSqe = cat_HELP(Disk_Pointer, TarAdd);
                    if (TarAddSqe)
                    {
                        int* TarAddDocAdd = F_doccontnode(Disk_Pointer, TarAddSqe);
                        jump2whePTR(Disk_Pointer, addr2blocknum(TarAddDocAdd), 0);
                        for (int i = 0; i < 1024; i++)
                        {
                            Disk_Pointer << 0;
                        }
                        jump2whePTR(Disk_Pointer, addr2blocknum(TarAddDocAdd), 0);
                        inputcharaddr(Disk_Pointer, const_cast<char*>(OriContext.c_str()));
                        response("���Ƴɹ���", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    else
                    {
                        response("Ŀ���ַ����", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                }
                else if (Parameter == "host")
                {
                    string TempOriContext;
                    string OriContext;
                    string OriFileName = GetWindowsFileName(OriAdd);
                    fstream Disk_Pointer2(OriAdd, ios::in || ios::out);

                    /*Ѱ��Դ�ļ�����*/
                    if (Disk_Pointer2)
                    {
                        while (!Disk_Pointer2.eof())
                        {
                            Disk_Pointer2 >> TempOriContext;
                            OriContext += TempOriContext;
                        }
                       
                    }
                    else
                    {
                        response("Դ��ַ����", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    Disk_Pointer2.close();

                    /*������Ŀ���ļ���*/
                    string InputInstruciton = "";
                    InputInstruciton += OriFileName;
                    InputInstruciton += " 111111 ";
                    InputInstruciton += OriContext;
                    istringstream Inputsstr(InputInstruciton);
                    response(CopyNewFile(Disk_Pointer, Inputsstr), ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("��������", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }

                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "del")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string delBuf;//�û��洢���������еĵ�ַ����
                Buf >> delBuf;
                int TarSqe = cat_HELP(Disk_Pointer, delBuf);
                if (F_docTy(Disk_Pointer, TarSqe) != 1)//���Ŀ���ļ�������ͨ�ļ�
                {
                    response("Ŀ���ļ�������ͨ�ļ���ָ�����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                if (TarSqe)
                {
                    delDoc(Disk_Pointer, TarSqe);
                    response("ɾ���ɹ���", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("��ַ����", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
            }
            else if (InstructionBuf == "check")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                ConsistencyCheck(Disk_Pointer, 101);
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                response("�ļ�һ���Լ����ɣ�", ReplyInfoSend);
                continue;
            }
            else
            {
                response("ָ�����", ReplyInfoSend);
                continue;
            }
        }
        else
        {
            printf(".....\t.....\t.....\n");
            Sleep(1000);
        }
    }
    return 0;

    /*����ظ���Ϣ�ռ��ļ�ӳ��*/
    UnmapViewOfFile(ReplyInfoSend);
    CloseHandle(ReplyInfoSpace);
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
