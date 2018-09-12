#include <graphics.h>
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
int visb[MAXN][MAXN];//记录黑棋
int visw[MAXN][MAXN];//记录白棋
int bwin;//标记黑棋获胜
int wwin;//标记白棋子获胜
int step;
int steppc;
int flag;
int flag2;//退出模式
int px,py;
int player;
static int MAN=1;
static int COM=-1;
mouse_msg msg = {0};

struct point
{
    int x;
    int y;
};

int board[MAXN][MAXN];//1是黑棋，-1是白棋，0，表示没有

void CreateMenus()//主菜单
{
    wwin=0;
    bwin=0;
    memset(visb,0,sizeof(visb));
    memset(visw,0,sizeof(visw));
    flag=0;
    flag2=0;//退出模式

    initgraph(1000,500);

    setbkcolor(EGERGB(0xFF, 0xFF, 0x40));//设置背景颜色
    //Title
	setfillcolor(EGERGB(0x0, 0x80, 0x80));//边框矩形
	bar(200, 0, 800,150);
	setcolor(EGERGB(0x0, 0xFF, 0x0));//文字颜色
    setbkmode(TRANSPARENT);//文字填充透明化
	setfont(100, 60, "楷体");
	outtextxy(200, 0, "ALPHAGO  X");
	setfillcolor(EGERGB(0x40, 0x0, 0x0));//设置背景颜色
	//菜单栏
	bar(300,150,700,500);
    //第一个椭圆
	setfillcolor(EGERGB(0x00, 0x50, 0x0));//椭圆颜色
    fillellipse(500,270,150,70);//椭圆构图
    setbkmode(TRANSPARENT);
    setcolor(EGERGB(0x0, 0x00, 0xFF));
    setfont(40, 20, "楷体");
    outtextxy(370,260,"Fight with PC");
    //第二个椭圆
    setfillcolor(EGERGB(0x00, 0x00, 0x64));
    fillellipse(500,430,150,70);
    setcolor(EGERGB(0xFF, 0x00, 0x00));
    setfont(40, 15, "楷体");
    outtextxy(370,400,"Fight with Person");
    //Author
    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    outtextxy(710,400,"Author: Meng Zhao");
}


int jud()//人人判断
{
    for(int i=60;i<=480;i++)
    {
        for(int j=60;j<=480;j++)
        {
            //判断黑棋
            if(visb[i][j]&&visb[i+30][j]&&visb[i+60][j]&&visb[i-30][j]&&visb[i-60][j]) return 1;//横向获胜
            else if(visb[i][j]&&visb[i][j+30]&&visb[i][j+60]&&visb[i][j-30]&&visb[i][j-60]) return 1;//纵向获胜
            else if(visb[i][j]&&visb[i+30][j+30]&&visb[i+60][j+60]&&visb[i-30][j-30]&&visb[i-60][j-60]) return 1;//斜率为1
            else if(visb[i][j]&&visb[i-30][j+30]&&visb[i-60][j+60]&&visb[i+30][j-30]&&visb[i+60][j-60]) return 1;//斜率为-1
            //判断白棋
            if(visw[i][j]&&visw[i+30][j]&&visw[i+60][j]&&visw[i-30][j]&&visw[i-60][j]) return 2;//横向获胜
            else if(visw[i][j]&&visw[i][j+30]&&visw[i][j+60]&&visw[i][j-30]&&visw[i][j-60]) return 2;//纵向获胜
            else if(visw[i][j]&&visw[i+30][j+30]&&visw[i+60][j+60]&&visw[i-30][j-30]&&visw[i-60][j-60]) return 2;//斜率为1
            else if(visw[i][j]&&visw[i-30][j+30]&&visw[i-60][j+60]&&visw[i+30][j-30]&&visw[i+60][j-60]) return 2;//斜率为-1
        }
    }
}

int judpc()//人机判断
{
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            //判断黑棋
            if(board[i][j]==1&&board[i+30][j]==1&&board[i+60][j]==1&&board[i-30][j]==1&&board[i-60][j]==1) return 1;//横向获胜
            else if(board[i][j]==1&&board[i][j+30]==1&&board[i][j+60]==1&&board[i][j-30]==1&&board[i][j-60]==1) return 1;//纵向获胜
            else if(board[i][j]==1&&board[i+30][j+30]==1&&board[i+60][j+60]==1&&board[i-30][j-30]==1&&board[i-60][j-60]==1) return 1;//斜率为1
            else if(board[i][j]==1&&board[i-30][j+30]==1&&board[i-60][j+60]==1&&board[i+30][j-30]==1&&board[i+60][j-60]==1) return 1;//斜率为-1
            //判断白棋子
            if(board[i][j]==-1&&board[i+30][j]==-1&&board[i+60][j]==-1&&board[i-30][j]==-1&&board[i-60][j]==-1) return 2;//横向获胜
            else if(board[i][j]==-1&&board[i][j+30]==-1&&board[i][j+60]==-1&&board[i][j-30]==-1&&board[i][j-60]==-1) return 2;//纵向获胜
            else if(board[i][j]==-1&&board[i+30][j+30]==-1&&board[i+60][j+60]==-1&&board[i-30][j-30]==-1&&board[i-60][j-60]==-1) return 2;//斜率为1
            else if(board[i][j]==-1&&board[i-30][j+30]==-1&&board[i-60][j+60]==-1&&board[i+30][j-30]==-1&&board[i+60][j-60]==-1) return 2;//斜率为-1
        }
    }
}

void CreatePCBoard()//人机棋盘
{
    setbkcolor(EGERGB(173, 92, 45));//设置背景颜色
    setcolor(BLACK);
    for(int i=60;i<510;i+=30)
    {
        line(i,60,i,480);
    }
    for(int j=60;j<510;j+=30)
    {
        line(60,j,480,j);
    }
    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    outtextxy(750,100,"PVP");
    setfillcolor(EGERGB(0xFF,0x0,0x0));
    setcolor(EGERGB(0xFF, 0xFF, 0x0));
    xyprintf(650, 40, "当前共计下了0棋");
    //P1信息
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "楷体");
    xyprintf(700,150,"PC(白):0");
    //P2信息
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "楷体");
    xyprintf(700,200,"Player(黑):0");

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"退出");
}

void CreatePVPboard()//人人棋盘
{
    setbkcolor(EGERGB(173, 92, 45));//设置背景颜色
    setcolor(BLACK);
    for(int i=60;i<510;i+=30)
    {
        line(i,60,i,480);
    }
    for(int j=60;j<510;j+=30)
    {
        line(60,j,480,j);
    }
    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    outtextxy(750,100,"PVP");
    setfillcolor(EGERGB(0xFF,0x0,0x0));
    setcolor(EGERGB(0xFF, 0xFF, 0x0));
    xyprintf(650, 40, "当前共计下了0棋");
    //P1信息
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "楷体");
    xyprintf(700,150,"P1(白):0");
    //P2信息
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "楷体");
    xyprintf(700,200,"P2(黑):0");

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"退出");
}

void PVPshow()//显示当前棋盘状况
{
    setbkcolor(EGERGB(173, 92, 45));//设置背景颜色
    setcolor(BLACK);
    for(int i=60;i<510;i+=30)
    {
        line(i,60,i,480);
    }
    for(int j=60;j<510;j+=30)
    {
        line(60,j,480,j);
    }

    for(int i=60;i<=480;i++)
    {
        for(int j=60;j<=480;j++)
        {
            if(visw[i][j])
            {
                setcolor(EGERGB(255, 255, 255));
                setfillcolor(EGERGB(255,255,255));
                fillellipse(i,j,15,15);
            }
            if(visb[i][j])
            {
                setcolor(EGERGB(0, 0, 0));
                setfillcolor(EGERGB(0,0,0));
                fillellipse(i,j,15,15);
            }
        }
    }
    setcolor(EGERGB(0xFF, 0xFF, 0x0));

    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    xyprintf(650, 40, "当前共计下了%d棋",step-1);

    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    outtextxy(750,100,"PVP");

    //p1:
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "楷体");
    xyprintf(700,150,"P1(白):%d",(step-1)/2+(step-1)%2);

    //p2
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "楷体");
    xyprintf(700,200,"P2(黑):%d",(step-1)/2);

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"退出");
    if(bwin)
    {
        setcolor(EGERGB(0, 0, 0));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "楷体");
        outtextxy(630,350,"黑棋获胜，点击下方回到主菜单");
    }
    else if(wwin)
    {
        setcolor(EGERGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "楷体");
        outtextxy(650,350,"白棋获胜,点击下方退出键回到主菜单");
    }
}
void PVEshow()//显示当前人机棋盘状况
{
    setbkcolor(EGERGB(173, 92, 45));//设置背景颜色
    setcolor(BLACK);
    for(int i=60;i<510;i+=30)
    {
        line(i,60,i,480);
    }
    for(int j=60;j<510;j+=30)
    {
        line(60,j,480,j);
    }

    for(int i=60;i<=480;i++)
    {
        for(int j=60;j<=480;j++)
        {
            if(board[i][j]==-1)
            {
                setcolor(EGERGB(255, 255, 255));
                setfillcolor(EGERGB(255,255,255));
                fillellipse(i,j,15,15);
            }
            if(board[i][j]==1)
            {
                setcolor(EGERGB(0, 0, 0));
                setfillcolor(EGERGB(0,0,0));
                fillellipse(i,j,15,15);
            }
        }
    }
    setcolor(EGERGB(0xFF, 0xFF, 0x0));

    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    xyprintf(650, 40, "当前共计下了%d棋",step+steppc);

    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "楷体");
    outtextxy(750,100,"PVP");

    //p1:
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "楷体");
    xyprintf(700,150,"PC(白):%d",steppc);

    //p2
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "楷体");
    xyprintf(700,200,"Player(黑):%d",step);

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"退出");
    if(bwin)
    {
        setcolor(EGERGB(0, 0, 0));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "楷体");
        outtextxy(630,350,"玩家(黑)获胜，点击下方回到主菜单");
    }
    else if(wwin)
    {
        setcolor(EGERGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "楷体");
        outtextxy(650,350,"电脑(白)获胜,点击下方退出键回到主菜单");
    }
}
void pvp()//人人对战
{
    bwin=0;
    wwin=0;
    CreatePVPboard();
    step=1;//步数初始化
        for ( ; is_run(); )
        {
            msg = getmouse();
            //边界条件
            if((int)msg.is_down()&&(int)msg.x&&(int)msg.y&&visw[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]==0&&visb[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]==0&&msg.x>=50&&msg.x<=485&&msg.y>=55&&msg.y<=485)
            {
                step++;//每走一步，步数+1
                if((step)&1)
                {
                    visb[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//奇数下黑棋//取余是为了精确计算
                }
                if((step)%2==0)
                {
                    visw[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//偶数下白棋;
                }
                if(jud()==1) bwin=1;
                else if(jud()==2) wwin=1;
                cleardevice();
                PVPshow();
                if(bwin||wwin) break;
            }
        }
}

void pcposition()
{
    int dx,dy;
    srand((int)time(NULL));
    px=rand()%421+60;
    py=rand()%421+60;
    while(board[px-px%30][py-py%30]==1||board[px-px%30][py-py%30]==-1)
    {
        px=rand()%421+60;
        py=rand()%421+60;
    }
}
int qiju[480][480][8][2];
int oldp[480][480];
int newp[480][480];
int a1[1000][1000];
int a2[1000][1000];
int win;



int caculate(int oldp[480][480],int qiuju[480][480][8][2])//棋局评估
{
    int k;
    int cnt;
    int tx,ty;
    int dirx[8]={0,30,30,30,0,-30,-30,-30};//八个方向
    int diry[8]={30,30,0,-30,-30,-30,0,30};//八个方向
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            if(oldp[i][j]==0)//此处为空
            {
                for(int k=0;k<8;k++)
                {
                    tx=i;
                    ty=j;
                    cnt=0;
                    for(int t=0;t<5;t++)
                    {
                        tx+=dirx[k];
                        ty+=diry[k];
                        if(tx<60||tx>480||ty<60||ty>480)
                        {
                            break;
                        }
                        if(oldp[tx][ty]==1)//黑棋
                        {
                            cnt++;
                        }
                        else break;
                    }
                    qiju[i][j][k][0]=cnt;
                    //白棋
                    cnt=0;
                    tx=i;
                    ty=j;
                    for(int t=0;t<5;t++)
                    {
                        tx+=dirx[k];
                        ty+=diry[k];
                        if(tx<60||tx>480||ty<60||ty>480)
                        {
                            break;
                        }
                        if(oldp[tx][ty]==-1)
                        {
                            cnt++;
                        }
                        else break;
                    }
                    qiju[i][j][k][1]=cnt;
                }
            }
        }
    }
}

int naiveline()
{
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            if(board[i][j]==0)
            {
                int win=0;
                for(int k=0;k<4;k++)
                {
                    if(qiju[i][j][k][0]+qiju[i][j][k+4][0]>=4)
                    {
                        win+=10000;
                    }
                    else if(qiju[i][j][k][0]+qiju[i][j][k+4][0]==3)
                    {
                        win+=1000;
                    }
                    else if(qiju[i][j][k][0]+qiju[i][j][k+4][0]==2)
                    {
                        win+=100;
                    }
                    else if(qiju[i][j][k][0]+qiju[i][j][k+4][0]==1)
                    {
                        win+=10;
                    }
                }
                a1[i][j]=win;//黑棋
                win=0;
                for(int k=0;k<4;k++)
                {
                    if(qiju[i][j][k][1]+qiju[i][j][k+4][1]>=4)
                    {
                        win+=10000;
                    }
                    else if(qiju[i][j][k][1]+qiju[i][j][k+4][1]==3)
                    {
                        win+=1000;
                    }
                    else if(qiju[i][j][k][1]+qiju[i][j][k+4][1]==2)
                    {
                        win+=100;
                    }
                    else if(qiju[i][j][k][1]+qiju[i][j][k+4][1]==1)
                    {
                        win+=10;
                    }
                }
                a2[i][j]=win;//白棋子
            }
        }
    }
}

void AIprotect()//防守型AI
{
    int x,y;
    int k=0;
    int x1=270,y1=270;
    int x2=270,y2=270;

    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            oldp[i][j]=board[i][j];
            newp[i][j]=board[i][j];
        }
    }
    memset(qiju,0,sizeof(qiju));
    memset(a1,0,sizeof(a1));
    memset(a2,0,sizeof(a2));
    caculate(oldp,qiju);
    naiveline();
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            if(a2[x2][y2]<a2[i][j])
            {
                x2=i;
                y2=j;
            }
        }
    }
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            if(a1[x1][y1]<a1[i][j])
            {
                x1=i;
                y1=j;
            }
        }
    }
    if(a2[x2][y2]>a1[x1][y1])
    {
        px=x2;
        py=y2;
    }
    else
    {
        px=x1;
        py=y1;
    }
}



void pveeasy()//人工智障
{
    memset(board,0,sizeof(board));//清空棋盘
    int flag3=0;
    bwin=0;
    wwin=0;
    CreatePCBoard();
    step=0;
    steppc=0;
    AIprotect();
    flag3=0;
    steppc++;
    board[px-px%30][py-py%30]=-1;
    cleardevice();
    PVEshow();
    for(;is_run();)
    {
        msg=getmouse();
        if((int)msg.is_down()&&(int)msg.x&&(int)msg.y&&board[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]==0&&msg.x>=50&&msg.x<=485&&msg.y>=55&&msg.y<=485)
        {
            flag3=1;
            step++;
            board[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//奇数下黑棋//取余是为了精确计算
            cleardevice();
            PVEshow();
            if(judpc()==1)
            {
                 bwin=1;
                 break;
            }
        }
        if(flag3)
        {
            pcposition();
            flag3=0;
            steppc++;
            board[px-px%30][py-py%30]=-1;
            cleardevice();
            PVEshow();
            if(judpc()==2)
            {
                wwin=1;
                break;
            }
        }
    }
    cleardevice();
    PVEshow();
}



void pve()//中等难度
{
    memset(board,0,sizeof(board));//清空棋盘
    int flag3=0;
    bwin=0;
    wwin=0;
    CreatePCBoard();
    step=0;
    steppc=0;
    AIprotect();
    flag3=0;
    steppc++;
    board[px-px%30][py-py%30]=-1;
    cleardevice();
    PVEshow();
    for(;is_run();)
    {
        msg=getmouse();
        if((int)msg.is_down()&&(int)msg.x&&(int)msg.y&&board[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]==0&&msg.x>=50&&msg.x<=485&&msg.y>=55&&msg.y<=485)
        {
            flag3=1;
            step++;
            board[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//奇数下黑棋//取余是为了精确计算
            cleardevice();
            PVEshow();
            if(judpc()==1)
            {
                 bwin=1;
                 break;
            }
        }
        if(flag3)
        {
            AIprotect();
            flag3=0;
            steppc++;
            board[px-px%30][py-py%30]=-1;
            cleardevice();
            PVEshow();
            if(judpc()==2)
            {
                wwin=1;
                break;
            }
        }
    }
    cleardevice();
    PVEshow();
}



void createPC2()
{
    int flag=0;
    setbkcolor(EGERGB(255,255, 255));//设置背景颜色
    setfillcolor(EGERGB(0,139,139));
    bar(200,100,800,200);

    setfillcolor(EGERGB(0,139,139));
    bar(200,300,800,400);

    setbkmode(TRANSPARENT);//文字填充透明化

    setcolor(EGERGB(160,32,240));
    setfont(70,30,"微软雅黑");
    outtextxy(380,100,"人工智障");

    setcolor(EGERGB(160,32,240));
    setfont(70,30,"微软雅黑");
    outtextxy(350,300,"初级人工智能");
    for ( ; is_run(); delay_fps(60))//鼠标操作
	{
		//获取鼠标消息，这个函数会等待，等待到有消息为止
		//类似地，有和kbhit功能相近的函数MouseHit，用于检测有没有鼠标消息
		while (mousemsg())
		{
			msg = getmouse();
		}

		//格式化输出为字符串，用于后面输出
		//msg和flag常数请参考文档或者mouse_msg_e, mouse_flag_e的声明
        if(msg.is_left()&&msg.x>=200&&msg.x<=800&&msg.y>=100&&msg.y<=200)
        {
            cleardevice();
            flag=1;
            break;
        }
        if(msg.is_left()&&msg.x>=200&&msg.x<=800&&msg.y>=300&&msg.y<=400)
        {
            cleardevice();
            flag=2;
            break;
        }
	}
	if(flag==1)
    {
        pveeasy();
    }
    else if(flag==2)
    {
        pve();
    }

}


void choose()
{
    for ( ; is_run(); delay_fps(60))//鼠标操作
	{
		//获取鼠标消息，这个函数会等待，等待到有消息为止
		//类似地，有和kbhit功能相近的函数MouseHit，用于检测有没有鼠标消息
		while (mousemsg())
		{
			msg = getmouse();
		}

		//格式化输出为字符串，用于后面输出
		//msg和flag常数请参考文档或者mouse_msg_e, mouse_flag_e的声明
        if(msg.is_left()&&msg.x>=350&&msg.x<=650&&msg.y<=340&&msg.y>=200)
        {
            cleardevice();
            flag=1;
            break;
        }
        if(msg.is_left()&&msg.x>=350&&msg.x<=650&&msg.y>=350&&msg.y<=500)
        {
            cleardevice();
            flag=2;
            break;
        }
	}
    if(flag==1)//进行人机大战
	{
	    cleardevice();
	    createPC2();

	}
	//人人对抗
	else if(flag==2)
    {
        pvp();
    }
}
void exitt()//退出到主菜单
{
    for(; is_run(); )
    {
        msg = getmouse();
        if((int)msg.is_down()&&(int)msg.x>=700&&msg.x<=850&&msg.y>=400&&msg.y<=450)
        {
            cleardevice();
            CreateMenus();
            choose();
        }
    }
}
int main()
{
	CreateMenus();//主菜单
	choose();//菜单栏选择
	exitt();
	getch();
	return 0;
}
