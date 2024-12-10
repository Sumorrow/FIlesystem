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
    string CurDirName;//用于暂时存储当前位置
    if (AddBuf.length() == 0)//如果地址为空，返回错误信息
    {
        return "跳转地址缺失！";
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//从根结点开始检索
        /*输入指令的分隔符/进行预处理*/
        for (int i = 0; i < AddBuf.length(); i++)//先处理地址中的/符号
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//将/替换为空格，便于输入
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*判断根地址是否有问题*/
        if (CurDirName != "cmd")//如果根地址有误
        {
            jump2whePTR(Disk_Pointer, ORZNUM, 0);//跳转回原来的位置
            return "地址错误！";
        }
        if (AddStr.eof())
        {
            jump2whePTR(Disk_Pointer, 101, 0);
            return "/cmd";
        }
        /*通过子结点不断进行定位*/
        while (1)//当输入字符串AddressBuf中还有内容
        {
            AddStr >> CurDirName;//输入下一个目录

            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//如果找到了对应的子文件
            {
                if (F_docTy(Disk_Pointer, getBLOCK(Disk_Pointer)) != 0)
                {
                    return "地址错误！";
                }
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//跳转到对应的位置
            }
            else//如果没有知道对应的子文件
            {
                jump2whePTR(Disk_Pointer, ORZNUM, 0);//跳转回原来的位置
                return "地址错误！";
            }
            if (AddStr.eof())//当输入完一个目录之后到底输入底部，结束
            {
                return OriAddBuf;
            }
        }
    }
    else
    {
        return "地址错误！";
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
    if (ChildNodeAdd[0] == 1)//如果这个子结点被占用了
    {
        int ChildNodeSqe = addr2blocknum(ChildNodeAdd);
        ChildNodeName = F_docNa(Disk_Pointer, ChildNodeSqe);
        ReplyInfo = ReplyInfo + "\n" + string(ChildNodeName);
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32);
    ChildNodeAdd = OP32b(Disk_Pointer);
    FileType = F_docTy(Disk_Pointer, addr2blocknum(ChildNodeAdd));
    if (ChildNodeAdd[0] == 1)//如果这个子结点被占用了
    {
        int ChildNodeSqe = addr2blocknum(ChildNodeAdd);
        ChildNodeName = F_docNa(Disk_Pointer, ChildNodeSqe);
        ReplyInfo = ReplyInfo + "\n" + string(ChildNodeName);
    }

    jump2whePTR(Disk_Pointer, blocknum, 112 + 32 + 32);
    ChildNodeAdd = OP32b(Disk_Pointer);
    FileType = F_docTy(Disk_Pointer, addr2blocknum(ChildNodeAdd));
    if (ChildNodeAdd[0] == 1)//如果这个子结点被占用了
    {
        int ChildNodeSqe = addr2blocknum(ChildNodeAdd);
        ChildNodeName = F_docNa(Disk_Pointer, ChildNodeSqe);
        ReplyInfo = ReplyInfo + "\n" + string(ChildNodeName);
    }

    jump2whePTR(Disk_Pointer, ORZNUM, 0);
}
int dir_HELP(fstream& Disk_Pointer, string AddBuf)
{
    string CurDirName;//用于暂时存储当前位置
    if (AddBuf.length() == 0)//如果地址为空，返回当前磁盘块序号
    {
        return getBLOCK(Disk_Pointer);
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//从根结点开始检索
        /*输入指令的分隔符/进行预处理*/
        for (int i = 0; i < AddBuf.length(); i++)//先处理地址中的/符号
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//将/替换为空格，便于输入
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*判断根地址是否有问题*/
        if (CurDirName != "cmd")//如果根地址有误
        {
            return 0;
        }
        /*通过子结点不断进行定位*/
        while (1)//当输入字符串AddressBuf中还有内容
        {
            AddStr >> CurDirName;//输入下一个目录
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//如果找到了对应的子文件
            {
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//跳转到对应的位置
            }
            else//如果没有知道对应的子文件
            {
                return 0;
            }
            if (AddStr.eof())//当输入完一个目录之后到底输入底部，结束
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
    ReplyInfo = ReplyInfo + "\n" + "目录名：" + string(F_docNa(Disk_Pointer, blocknum));

    jump2whePTR(Disk_Pointer, blocknum, 73);//跳转到管理员保护类型位置
    ReplyInfo = ReplyInfo + "\n" + "管理员保护类型：";
    for (int i = 0; i < 3; i++)//读取管理员保护类型
    {
        Disk_Pointer >> chartpt_buf;
        ReplyInfo += chartpt_buf;
    }

    jump2whePTR(Disk_Pointer, blocknum, 77);//跳转到普通用户保护类型位置
    ReplyInfo = ReplyInfo + "\n" + "普通用户保护类型：";
    for (int i = 0; i < 3; i++)//读取普通用户保护类型
    {
        Disk_Pointer >> chartpt_buf;
        ReplyInfo += chartpt_buf;
    }

    jump2whePTR(Disk_Pointer, blocknum, 80);//跳转到父结点位置
    ReplyInfo = ReplyInfo + "\n" + "父结点地址：";
    for (int i = 0; i < 32; i++)//读取父结点地址
    {
        Disk_Pointer >> chartpt_buf;
        ReplyInfo += chartpt_buf;
    }

    jump2whePTR(Disk_Pointer, blocknum, 112);//跳转到子结点位置
    ReplyInfo = ReplyInfo + "\n" + "子结点地址：";
    for (int i = 0; i < 3; i++)//读取子结点地址
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
    string CurDirName;//用于暂时存储当前位置
    if (AddBuf.length() == 0)//如果地址为空，错误
    {
        return ErrorReturn;
    }

    /*判断所给地址是否为绝对地址，如果是，跳转到相应位置并返回需要创建的文件名，如果不是，直接返回需要创建的文件名*/
    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//从根结点开始检索
        /*输入指令的分隔符/进行预处理*/
        for (int i = 0; i < AddBuf.length(); i++)//先处理地址中的/符号
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//将/替换为空格，便于输入
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*判断根地址是否有问题*/
        if (CurDirName != "cmd")//如果根地址有误
        {
            return ErrorReturn;
        }

        /*通过子结点不断进行定位*/
        while (1)//当输入字符串AddressBuf中还有内容
        {
            AddStr >> CurDirName;//输入下一个目录
            if (AddStr.eof())//当输入完一个目录之后到底输入底部，那么这时候这个名字就是对应的文件名
            {
                break;
            }
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//如果找到了对应的子文件
            {
                if (F_docTy(Disk_Pointer, ChildBlockSqe) != 0)//如果子文件不是目录
                {
                    return ErrorReturn;
                }
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//跳转到对应的位置
            }
            else//如果没有知道对应的子文件
            {
                return ErrorReturn;
            }
        }
    }
    else
    {
        for (int i = 1; i < AddBuf.length(); i++)//判断文件名中有没有/符号
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
    string CurDirName;//用于暂时存储当前位置
    if (AddBuf.length() == 0)//如果地址为空，返回当前磁盘块序号
    {
        return getBLOCK(Disk_Pointer);
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//从根结点开始检索
        /*输入指令的分隔符/进行预处理*/
        for (int i = 0; i < AddBuf.length(); i++)//先处理地址中的/符号
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//将/替换为空格，便于输入
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*判断根地址是否有问题*/
        if (CurDirName != "cmd")//如果根地址有误
        {
            return 0;
        }
        /*通过子结点不断进行定位*/
        while (1)//当输入字符串AddressBuf中还有内容
        {
            AddStr >> CurDirName;//输入下一个目录
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//如果找到了对应的子文件
            {
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//跳转到对应的位置
            }
            else//如果没有找到对应的子文件
            {
                return 0;
            }
            if (AddStr.eof())//当输入完一个目录之后到底输入底部，结束
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
    if (FileType == 0)//如果对应的是目录
    {
        if (IsDirEmpty(Disk_Pointer, blocknum))
        {
            /*将父结点的对应子结点地址清除*/
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

            /*将目录i结点中内容删除*/
            jump2whePTR(Disk_Pointer, blocknum, 0);
            bitmap_engine(Disk_Pointer, getBLOCK(Disk_Pointer), 0);//将位图中对应i结点的位置清除
            for (int i = 0; i < 1024; i++)
            {
                Disk_Pointer << 0;
            }
            return;
        }
        else
        {
            int** INIttpt_buf = F_docCHILDddr(Disk_Pointer, blocknum);
            /*删子结点*/
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

            /*删自己*/
            if (IsDirEmpty(Disk_Pointer, blocknum))
            {
                rdDir(Disk_Pointer, blocknum);
            }
        }
    }
    else//如果对应的是文件
    {
        int* DocContextAdd = F_doccontnode(Disk_Pointer, blocknum);

        /*将文件结点的内容清除*/
        bitmap_engine(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
        jump2whePTR(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
        for (int i = 0; i < 1024; i++)
        {
            Disk_Pointer << 0;
        }

        /*将父结点的对应子结点地址清除*/
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

        /*将文件i结点的内容清除*/
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
        return "地址有误，创建失败!";
    }
    if (FileName.length() > 8)
    {
        return "文件名过长，创建失败！";
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
            return "文件名格式错误，创建失败！";
        }
    }
    if (CountPoint != 1)
    {
        return "文件名格式错误，创建失败！";
    }
    return Right;
}
string FileAccTest(string Acc)
{
    string Right = "";
    if (Acc.length() != 6)
    {
        return "保护类型长度错误，创建失败!";
    }
    for (int i = 0; i < Acc.length(); i++)
    {
        if (Acc[i] != '0' && Acc[i] != '1')
        {
            return "保护类型格式错误，创建失败!";
        }
    }
    return Right;
}
string newfile_HELP(fstream& Disk_Pointer, string AddBuf)
{
    string ErrorReturn = "";
    string CurDirName;//用于暂时存储当前位置
    if (AddBuf.length() == 0)//如果地址为空，错误
    {
        return ErrorReturn;
    }

    /*判断所给地址是否为绝对地址，如果是，跳转到相应位置并返回需要创建的文件名，如果不是，直接返回需要创建的文件名*/
    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//从根结点开始检索
        /*输入指令的分隔符/进行预处理*/
        for (int i = 0; i < AddBuf.length(); i++)//先处理地址中的/符号
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//将/替换为空格，便于输入
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*判断根地址是否有问题*/
        if (CurDirName != "cmd")//如果根地址有误
        {
            return ErrorReturn;
        }

        /*通过子结点不断进行定位*/
        while (1)//当输入字符串AddressBuf中还有内容
        {
            AddStr >> CurDirName;//输入下一个目录
            if (AddStr.eof())//当输入完一个目录之后到底输入底部，那么这时候这个名字就是对应的文件名
            {
                break;
            }
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//如果找到了对应的子文件
            {
                if (F_docTy(Disk_Pointer, ChildBlockSqe) != 0)//如果子文件不是目录
                {
                    return ErrorReturn;
                }
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//跳转到对应的位置
            }
            else//如果没有知道对应的子文件
            {
                return ErrorReturn;
            }
        }
    }
    else
    {
        for (int i = 1; i < AddBuf.length(); i++)//判断文件名中有没有/符号
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
    string CurDirName;//用于暂时存储当前位置
    if (AddBuf.length() == 0)//如果地址为空，返回当前磁盘块序号
    {
        return 0;
    }

    if (AddBuf[0] == '/')
    {
        jump2whePTR(Disk_Pointer, 101, 0);//从根结点开始检索
        /*输入指令的分隔符/进行预处理*/
        for (int i = 0; i < AddBuf.length(); i++)//先处理地址中的/符号
        {
            if (AddBuf[i] == '/')AddBuf[i] = ' ';//将/替换为空格，便于输入
        }

        istringstream AddStr(AddBuf);
        AddStr >> CurDirName;

        /*判断根地址是否有问题*/
        if (CurDirName != "cmd")//如果根地址有误
        {
            return 0;
        }
        /*通过子结点不断进行定位*/
        while (1)//当输入字符串AddressBuf中还有内容
        {
            AddStr >> CurDirName;//输入下一个目录
            int ChildBlockSqe = document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName);
            if (ChildBlockSqe)//如果找到了对应的子文件
            {
                jump2whePTR(Disk_Pointer, ChildBlockSqe, 0);//跳转到对应的位置
            }
            else//如果没有知道对应的子文件
            {
                return 0;
            }
            if (AddStr.eof())//当输入完一个目录之后到底输入底部，结束
            {
                if (F_docTy(Disk_Pointer, getBLOCK(Disk_Pointer)) != 1)//如果该文件是一个目录
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

    /*将文件结点的内容清除*/
    bitmap_engine(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
    jump2whePTR(Disk_Pointer, addr2blocknum(DocContextAdd), 0);
    for (int i = 0; i < 1024; i++)
    {
        Disk_Pointer << 0;
    }

    /*将父结点的对应子结点地址清除*/
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

    /*将文件i结点的内容清除*/
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
    string newfileNameBuf;//用户存储输入内容中的地址部分
    string newfileAccBuf;
    string newfileContextBuf;
    Buf >> newfileNameBuf;
    Buf >> newfileAccBuf;
    Buf >> newfileContextBuf;

    string CurDirName = mdAddLocation(Disk_Pointer, newfileNameBuf);
    /*文件名格式检测*/
    string ReplyInfo = FileNameTest(CurDirName);
    if (ReplyInfo != "")
    {
        return ReplyInfo;
    }

    /*保护类型格式检测*/
    ReplyInfo = FileAccTest(newfileAccBuf);
    if (ReplyInfo != "")
    {
        return ReplyInfo;
    }

    int NewINodeBlockSqe = F_spareInode(Disk_Pointer);
    int NewDocBlockSqe = F_sparedoc(Disk_Pointer);

    /*判断文件系统是否还有空间*/
    if (!NewINodeBlockSqe)//如果文件系统汇总没有空间，创建失败
    {
        return "文件系统已无空闲空间，创建失败！";
    }
    if (!NewDocBlockSqe)//如果文件系统汇总没有空间，创建失败
    {
        return "文件系统已无空闲空间，创建失败！";
    }

    /*判断所创建文件名是否与子结点中文件名重复*/
    if (document_match(Disk_Pointer, getBLOCK(Disk_Pointer), CurDirName))
    {
        return "文件名重复，创建失败！";
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
        return "当前文件的子文件已达上限，创建失败！";
    }

    /*对新文件进行初始化*/
    InputDocName(Disk_Pointer, NewINodeBlockSqe, CurDirName);//输入文件名
    InputParNode(Disk_Pointer, NewINodeBlockSqe, blocknum2addr(getBLOCK(Disk_Pointer)));//输入父结点地址
    InputAcc(Disk_Pointer, NewINodeBlockSqe, newfileAccBuf);//输入文件保护类型
    inputcontT(Disk_Pointer, NewINodeBlockSqe, NewDocBlockSqe, newfileContextBuf);//输入文件内容
    InputFileType(Disk_Pointer, NewINodeBlockSqe, 1);//输入文件类型
    bitmap_engine(Disk_Pointer, NewINodeBlockSqe, 1);
    bitmap_engine(Disk_Pointer, NewDocBlockSqe, 1);
    jump2whePTR(Disk_Pointer, ORZNUM, 0);
    return "文件创建成功！";
}
void ConsistencyCheck(fstream& Disk_Pointer, int blocknum)
{
    jump2whePTR(Disk_Pointer, blocknum, 0);
    int FileType = F_docTy(Disk_Pointer, blocknum);
    bitmap_engine(Disk_Pointer, blocknum, 1);//把该文件对应的位图比特置为1
    if (FileType == 1)//如果是一个文件
    {
        bitmap_engine(Disk_Pointer, addr2blocknum(F_doccontnode(Disk_Pointer, blocknum)), 1);//把文件内容对应的位图比特置为1
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
 *            佛祖保佑       永不宕机     永无BUG
 */
 /**
/*==============================专用函数==============================*/