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
#include"N1k0.h"
 int main()
{
    std::string FILENAMED = "F:\\ideaoo\\os_linuxmodelafter_filesystem\\db\\diskapp.txt";
    fstream Disk_Pointer(FILENAMED, ios::in | ios::out);
    Init(Disk_Pointer);
    jump2whePTR(Disk_Pointer, 101, 0);

    /*回复信息空间，用于服务器向客户端回复信息*/
    HANDLE ReplyInfoSpace = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // 物理文件句柄
        NULL,   // 默认安全级别
        PAGE_READWRITE,   // 可读可写
        0,   // 高位文件大小
        BUF_SIZE,   // 地位文件大小
        "ReplyInfoSpace"   // 共享内存名称
    );

    LPVOID ReplyInfoSend = MapViewOfFile(
        ReplyInfoSpace,            // 共享内存的句柄
        FILE_MAP_ALL_ACCESS, // 可读写许可
        0,
        0,
        BUF_SIZE
    );

    /*写占用空间，用于高速客户机当前写的状态*/
    HANDLE WSPACE = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // 物理文件句柄
        NULL,   // 默认安全级别
        PAGE_READWRITE,   // 可读可写
        0,   // 高位文件大小
        BUF_SIZE,   // 地位文件大小
        "WSPACE"   // 共享内存名称
    );

    //映射缓存区视图，得到指向共享内存的指针
    LPVOID WriteSend = MapViewOfFile(
        WSPACE,            // 共享内存的句柄
        FILE_MAP_ALL_ACCESS, // 可读写许可
        0,
        0,
        BUF_SIZE
    );
    char WriteSendBuf[BUF_SIZE] = { 0 };

    /*与rd相关的内容*/
    int rdIsNotEmpty = 0;//01标记变量，表示rd的目录是不是空的
    int rdOriSqe = 0;
    int rdTarSqe = 0;
    string rdBuf = "";//用户存储输入内容中的地址部分
    int WriteLock = 0;


    /*开始不断地接受信息*/
    while (1)
    {
        //Sleep(1000);
        // 打开共享的文件对象
        HANDLE SHARED_FILESPACE = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "SHARED_FILESPACE");
        LPVOID InstructionRec = MapViewOfFile(SHARED_FILESPACE, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (!InstructionRec)//判断指针是否为空（共享内存未创建的时候为空）
        {
            printf("Waiting......\n");
            Sleep(1000);
            continue;
        }

        if (strlen((char*)InstructionRec))//判断共享内存中是否有内容
        {
            char UserAccBuf[BUF_SIZE] = { 0 };//用户权限缓存
            HANDLE SHARED_FILEQUL = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "SHARED_FILEQUL");
            LPVOID AccRec = MapViewOfFile(SHARED_FILEQUL, FILE_MAP_ALL_ACCESS, 0, 0, 0);
            SMemoinfoCY(UserAccBuf, AccRec);

            char InstructionRecBuffer[BUF_SIZE] = { 0 };
            SMemoinfoCY(InstructionRecBuffer, InstructionRec);// 将共享内存数据拷贝出来
            istringstream Buf(InstructionRecBuffer);//将内容转换为输入流
            string InstructionBuf;//用于存储输入内容中的指令部分

            Buf >> InstructionBuf;//输入用户输入的指令
            cout << "Get info:" << InstructionRecBuffer << endl;//输出客户端输入的信息
            if (rdIsNotEmpty == 1)
            {
                if (InstructionBuf == "y")
                {
                    rdDir(Disk_Pointer, rdTarSqe);
                    bitmap_engine(Disk_Pointer, rdTarSqe, 0);
                    response("删除完成", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    rdIsNotEmpty = 0;
                    rdOriSqe = 0;
                    rdBuf = "";
                    rdTarSqe = 0;
                    continue;
                }
                else if (InstructionBuf == "n")
                {
                    response("操作取消", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    rdIsNotEmpty = 0;
                    rdOriSqe = 0;
                    rdBuf = "";
                    rdTarSqe = 0;
                    continue;
                }
                else
                {
                    response("指令错误", ReplyInfoSend);
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
                ReplyInfo = ReplyInfo + "文件系统归属:" + DocSysHost + "\n";
                ReplyInfo = ReplyInfo + "文件系统大小:" + DocSysSize + "Mb" + "\n";
                ReplyInfo = ReplyInfo + "磁盘块大小:" + DiskBlockSize + "b" + "\n";
                ReplyInfo = ReplyInfo + "超级块序号:" + SuperBlockSqe + "\n";
                ReplyInfo = ReplyInfo + "位图序号:" + BitMapSqe + "\n";
                ReplyInfo = ReplyInfo + "根结点序号:" + RootSqe + "\n";
                ReplyInfo = ReplyInfo + "I结点区序号:" + INodeSqe + "\n";
                ReplyInfo = ReplyInfo + "I结点区剩余空间:" + to_string(G_InodeLspace(Disk_Pointer)) + "\n";
                ReplyInfo = ReplyInfo + "文件区序号:" + DocSqe + "\n";
                ReplyInfo = ReplyInfo + "文件区剩余空间:" + to_string(G_docLspace(Disk_Pointer));
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                response(ReplyInfo, ReplyInfoSend);
                continue;
            }
            else if (InstructionBuf == "cd")
            {
                string cdBuf;//用户存储输入内容中的地址部分
                Buf >> cdBuf;
                string ReplyInfo = cd_HELP(Disk_Pointer, cdBuf);
                response(ReplyInfo, ReplyInfoSend);
            }
            else if (InstructionBuf == "dir")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string ReplyInfo = "";
                string dirBuf;//用户存储输入内容中的地址部分
                Buf >> dirBuf;
                if (dirBuf == "/s")//如果带/s参数
                {
                    ReplyInfo += "当前目录下的所有文件和子目录为：";
                    ShowAllChildNodeName(Disk_Pointer, getBLOCK(Disk_Pointer), ReplyInfo);
                    response(ReplyInfo, ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                int CurBlockSqe = dir_HELP(Disk_Pointer, dirBuf);//文件指针定位
                if (CurBlockSqe == 0)//如果返回错误信息
                {
                    response("地址有误，创建失败！", ReplyInfoSend);
                    continue;
                }
                ReplyInfo += "当前目录下的信息为：";
                ShowAllInfo(Disk_Pointer, CurBlockSqe, ReplyInfo);
                response(ReplyInfo, ReplyInfoSend);
                continue;

                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "md")//创建新目录
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string mdBuf;//用户存储输入内容中的地址部分
                Buf >> mdBuf;

                string CurDirName = mdAddLocation(Disk_Pointer, mdBuf);
                if (CurDirName == "")
                {
                    response("地址有误，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*判断新建目录的长度*/
                if (CurDirName.length() > 8)//目录名不能大于8位
                {
                    response("目录名过长，创建失败！", ReplyInfoSend);
                    continue;
                }

                int NewINodeBlockSqe = F_spareInode(Disk_Pointer);

                /*判断文件系统是否还有空间*/
                if (!NewINodeBlockSqe)//如果文件系统汇总没有空间，创建失败
                {
                    response("文件系统已无空闲空间，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*判断所创建文件名是否与子结点中文件名重复*/
                if (document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName))
                {
                    response("文件名重复，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*判断子结点是不是满了*/
                int FreeChildSqe = F_sparechildnode(Disk_Pointer, getBLOCK(Disk_Pointer));
                if (FreeChildSqe)//没满，将子结点标记为已经使用，并输入32位地址
                {
                    jump2whePTR(Disk_Pointer, getBLOCK(Disk_Pointer), 112 + 32 * (FreeChildSqe - 1));//跳转到对应的子结点
                    int* INode = blocknum2addr(NewINodeBlockSqe);
                    INode[0] = 1;//将首位置为1，表示该子结点已经被使用
                    inputintaddr(Disk_Pointer, INode, 32);//输入32位子结点
                    jump2whePTR(Disk_Pointer, getBLOCK(Disk_Pointer), 0);//跳回开头
                }
                else
                {
                    response("当前文件的子文件已达上限，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*对新文件进行初始化*/
                InputDocName(Disk_Pointer, NewINodeBlockSqe, CurDirName);
                InputParNode(Disk_Pointer, NewINodeBlockSqe, blocknum2addr(getBLOCK(Disk_Pointer)));
                bitmap_engine(Disk_Pointer, NewINodeBlockSqe, 1);
                response("目录创建成功！", ReplyInfoSend);
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                continue;
            }
            else if (InstructionBuf == "rd")
            {
                rdOriSqe = getBLOCK(Disk_Pointer);
                Buf >> rdBuf;
                rdTarSqe = rd_HELP(Disk_Pointer, rdBuf);//寻找应该删除的目标磁盘块
                if (rdTarSqe == 1)//如果是根目录
                {
                    response("根目录不可删除，删除失败！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    continue;
                }
                if (F_docTy(Disk_Pointer, rdTarSqe) != 0)//如果目标文件不是目录
                {
                    response("目标文件为普通文件，删除失败！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    continue;
                }
                if (rdTarSqe)
                {
                    if (!IsDirEmpty(Disk_Pointer, rdTarSqe))//如果非空
                    {
                        rdIsNotEmpty = 1;
                        response("目标目录非空，是否需要删除？y/n", ReplyInfoSend);
                        continue;
                    }
                    else//如果是空的
                    {
                        rdDir(Disk_Pointer, rdTarSqe);//删除对应结点
                        bitmap_engine(Disk_Pointer, rdTarSqe, 0);
                        response("目标目录删除完成", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                        rdIsNotEmpty = 0;//将所有系数置0
                        rdOriSqe = 0;
                        rdBuf = "";
                        rdTarSqe = 0;
                        continue;
                    }
                }
                else//如果没有找都目标磁盘块，返回错误信息
                {
                    response("地址错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, rdOriSqe, 0);
                    continue;
                }
                jump2whePTR(Disk_Pointer, rdOriSqe, 0);
            }
            else if (InstructionBuf == "newfile")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string newfileNameBuf;//用户存储输入内容中的地址部分
                string newfileAccBuf;
                string newfileContextBuf;
                Buf >> newfileNameBuf;
                Buf >> newfileAccBuf;
                Buf >> newfileContextBuf;

                string CurDirName = newfile_HELP(Disk_Pointer, newfileNameBuf);
                /*文件名格式检测*/
                string ReplyInfo = FileNameTest(CurDirName);
                if (ReplyInfo != "")
                {
                    response(ReplyInfo, ReplyInfoSend);
                    continue;
                }

                /*保护类型格式检测*/
                ReplyInfo = FileAccTest(newfileAccBuf);
                if (ReplyInfo != "")
                {
                    response(ReplyInfo, ReplyInfoSend);
                    continue;
                }

                int NewINodeBlockSqe = F_spareInode(Disk_Pointer);
                int NewDocBlockSqe = F_sparedoc(Disk_Pointer);

                /*判断文件系统是否还有空间*/
                if (!NewINodeBlockSqe)//如果文件系统汇总没有空间，创建失败
                {
                    response("文件系统已无空闲空间，创建失败！", ReplyInfoSend);
                    continue;
                }
                if (!NewDocBlockSqe)//如果文件系统汇总没有空间，创建失败
                {
                    response("文件系统已无空闲空间，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*判断所创建文件名是否与子结点中文件名重复*/
                if (document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName))
                {
                    response("文件名重复，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*判断子结点是不是满了*/
                int FreeChildSqe = F_sparechildnode(Disk_Pointer, getBLOCK(Disk_Pointer));
                if (FreeChildSqe)//没满，将子结点标记为已经使用，并输入32位地址
                {
                    jump2whePTR(Disk_Pointer, getBLOCK(Disk_Pointer), 112 + 32 * (FreeChildSqe - 1));//跳转到对应的子结点
                    int* INode = blocknum2addr(NewINodeBlockSqe);
                    INode[0] = 1;//将首位置为1，表示该子结点已经被使用
                    inputintaddr(Disk_Pointer, INode, 32);//输入32位子结点
                    jump2whePTR(Disk_Pointer, getBLOCK(Disk_Pointer), 0);//跳回开头
                }
                else
                {
                    response("当前文件的子文件已达上限，创建失败！", ReplyInfoSend);
                    continue;
                }

                /*对新文件进行初始化*/
                InputDocName(Disk_Pointer, NewINodeBlockSqe, CurDirName);//输入文件名
                InputParNode(Disk_Pointer, NewINodeBlockSqe, blocknum2addr(getBLOCK(Disk_Pointer)));//输入父结点地址
                InputAcc(Disk_Pointer, NewINodeBlockSqe, newfileAccBuf);//输入文件保护类型
                inputcontT(Disk_Pointer, NewINodeBlockSqe, NewDocBlockSqe, newfileContextBuf);//输入文件内容
                InputFileType(Disk_Pointer, NewINodeBlockSqe, 1);//输入文件类型
                bitmap_engine(Disk_Pointer, NewINodeBlockSqe, 1);
                bitmap_engine(Disk_Pointer, NewDocBlockSqe, 1);
                response("文件创建成功！", ReplyInfoSend);
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                continue;
            }
            else if (InstructionBuf == "cat")
            {
                 int ORZNUM = getBLOCK(Disk_Pointer);
                string mdBuf;//用户存储输入内容中的地址部分
                Buf >> mdBuf;
                int TarSqe = cat_HELP(Disk_Pointer, mdBuf);
                if (F_docTy(Disk_Pointer, TarSqe) != 1)//如果目标文件不是普通文件
                {
                    response("目标文件不是普通文件，指令错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                if (TarSqe)
                {
                    int* ComAcc = F_docUACC(Disk_Pointer, TarSqe);//查询普通用户访问权限
                    int* SysAcc = F_docSACC(Disk_Pointer, TarSqe);//查询系统用户访问权限
                    if (!((ComAcc[0] == 1 && UserAccBuf[0] == '1') || (SysAcc[0] == 1 && UserAccBuf[0] == '0')))//判断有无权限写入该文件
                    {
                        response("无权限读取该文件！", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    response(GetFileContext(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, TarSqe))), ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("地址错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "write")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string writeBuf;//用户存储输入内容中的地址部分
                string InputInfo;//待输入的文件内容
                Buf >> writeBuf;
                Buf >> InputInfo;
                int TarSqe = cat_HELP(Disk_Pointer, writeBuf);
                if (F_docTy(Disk_Pointer, TarSqe) != 1)//如果目标文件不是普通文件
                {
                    response("目标文件不是普通文件，指令错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                if (TarSqe)
                {
                    int* ComAcc = F_docUACC(Disk_Pointer, TarSqe);//查询普通用户访问权限
                    int* SysAcc = F_docSACC(Disk_Pointer, TarSqe);//查询系统用户访问权限
                    if (InputInfo.length() > 128)
                    {
                        response("文件内容过多，无法写入！", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    if (!((ComAcc[1] == 1 && UserAccBuf[0] == '1') || (SysAcc[1] == 1 && UserAccBuf[0] == '0')))//判断有无权限写入该文件
                    {
                        response("无权限写入该文件！", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    /*清空源文件*/
                    jump2whePTR(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, TarSqe)), 0);
                    for (int i = 0; i < 1024; i++)
                    {
                        Disk_Pointer << 0;
                    }
                    jump2whePTR(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, TarSqe)), 0);

                    /*写时延迟*/
                    strcpy_s((char*)WriteSend, writeBuf.length() + 1, const_cast<char*>(writeBuf.c_str()));
                    Sleep(10000);
                    SMemoCL(WriteSend);

                    /*写入*/
                    inputcharaddr(Disk_Pointer, const_cast<char*>(InputInfo.c_str()));
                    response("写入成功！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("地址错误！", ReplyInfoSend);
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

                if (Parameter == "")//如果没有参数
                {
                    /*寻找源文件内容*/
                    int OriAddSqe = cat_HELP(Disk_Pointer, OriAdd);
                    string OriContext;
                    if (OriAddSqe)
                    {
                        OriContext = GetFileContext(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, OriAddSqe)));
                    }
                    else
                    {
                        response("源地址错误！", ReplyInfoSend);
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
                        response("复制成功！", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    else
                    {
                        response("目标地址错误！", ReplyInfoSend);
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

                    /*寻找源文件内容*/
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
                        response("源地址错误！", ReplyInfoSend);
                        jump2whePTR(Disk_Pointer, ORZNUM, 0);
                        continue;
                    }
                    Disk_Pointer2.close();

                    /*拷贝到目标文件夹*/
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
                    response("参数错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }

                jump2whePTR(Disk_Pointer, ORZNUM, 0);
            }
            else if (InstructionBuf == "del")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                string delBuf;//用户存储输入内容中的地址部分
                Buf >> delBuf;
                int TarSqe = cat_HELP(Disk_Pointer, delBuf);
                if (F_docTy(Disk_Pointer, TarSqe) != 1)//如果目标文件不是普通文件
                {
                    response("目标文件不是普通文件，指令错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                if (TarSqe)
                {
                    delDoc(Disk_Pointer, TarSqe);
                    response("删除成功！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
                else
                {
                    response("地址错误！", ReplyInfoSend);
                    jump2whePTR(Disk_Pointer, ORZNUM, 0);
                    continue;
                }
            }
            else if (InstructionBuf == "check")
            {
                int ORZNUM = getBLOCK(Disk_Pointer);
                ConsistencyCheck(Disk_Pointer, 101);
                jump2whePTR(Disk_Pointer, ORZNUM, 0);
                response("文件一致性检查完成！", ReplyInfoSend);
                continue;
            }
            else
            {
                response("指令错误！", ReplyInfoSend);
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

    /*解除回复信息空间文件映射*/
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
 *            佛祖保佑       永不宕机     永无BUG
 */
 /**
/*==============================专用函数==============================*/
