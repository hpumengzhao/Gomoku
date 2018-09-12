#include <graphics.h>
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
int visb[MAXN][MAXN];//��¼����
int visw[MAXN][MAXN];//��¼����
int bwin;//��Ǻ����ʤ
int wwin;//��ǰ����ӻ�ʤ
int step;
int steppc;
int flag;
int flag2;//�˳�ģʽ
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

int board[MAXN][MAXN];//1�Ǻ��壬-1�ǰ��壬0����ʾû��

void CreateMenus()//���˵�
{
    wwin=0;
    bwin=0;
    memset(visb,0,sizeof(visb));
    memset(visw,0,sizeof(visw));
    flag=0;
    flag2=0;//�˳�ģʽ

    initgraph(1000,500);

    setbkcolor(EGERGB(0xFF, 0xFF, 0x40));//���ñ�����ɫ
    //Title
	setfillcolor(EGERGB(0x0, 0x80, 0x80));//�߿����
	bar(200, 0, 800,150);
	setcolor(EGERGB(0x0, 0xFF, 0x0));//������ɫ
    setbkmode(TRANSPARENT);//�������͸����
	setfont(100, 60, "����");
	outtextxy(200, 0, "ALPHAGO  X");
	setfillcolor(EGERGB(0x40, 0x0, 0x0));//���ñ�����ɫ
	//�˵���
	bar(300,150,700,500);
    //��һ����Բ
	setfillcolor(EGERGB(0x00, 0x50, 0x0));//��Բ��ɫ
    fillellipse(500,270,150,70);//��Բ��ͼ
    setbkmode(TRANSPARENT);
    setcolor(EGERGB(0x0, 0x00, 0xFF));
    setfont(40, 20, "����");
    outtextxy(370,260,"Fight with PC");
    //�ڶ�����Բ
    setfillcolor(EGERGB(0x00, 0x00, 0x64));
    fillellipse(500,430,150,70);
    setcolor(EGERGB(0xFF, 0x00, 0x00));
    setfont(40, 15, "����");
    outtextxy(370,400,"Fight with Person");
    //Author
    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "����");
    outtextxy(710,400,"Author: Meng Zhao");
}


int jud()//�����ж�
{
    for(int i=60;i<=480;i++)
    {
        for(int j=60;j<=480;j++)
        {
            //�жϺ���
            if(visb[i][j]&&visb[i+30][j]&&visb[i+60][j]&&visb[i-30][j]&&visb[i-60][j]) return 1;//�����ʤ
            else if(visb[i][j]&&visb[i][j+30]&&visb[i][j+60]&&visb[i][j-30]&&visb[i][j-60]) return 1;//�����ʤ
            else if(visb[i][j]&&visb[i+30][j+30]&&visb[i+60][j+60]&&visb[i-30][j-30]&&visb[i-60][j-60]) return 1;//б��Ϊ1
            else if(visb[i][j]&&visb[i-30][j+30]&&visb[i-60][j+60]&&visb[i+30][j-30]&&visb[i+60][j-60]) return 1;//б��Ϊ-1
            //�жϰ���
            if(visw[i][j]&&visw[i+30][j]&&visw[i+60][j]&&visw[i-30][j]&&visw[i-60][j]) return 2;//�����ʤ
            else if(visw[i][j]&&visw[i][j+30]&&visw[i][j+60]&&visw[i][j-30]&&visw[i][j-60]) return 2;//�����ʤ
            else if(visw[i][j]&&visw[i+30][j+30]&&visw[i+60][j+60]&&visw[i-30][j-30]&&visw[i-60][j-60]) return 2;//б��Ϊ1
            else if(visw[i][j]&&visw[i-30][j+30]&&visw[i-60][j+60]&&visw[i+30][j-30]&&visw[i+60][j-60]) return 2;//б��Ϊ-1
        }
    }
}

int judpc()//�˻��ж�
{
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            //�жϺ���
            if(board[i][j]==1&&board[i+30][j]==1&&board[i+60][j]==1&&board[i-30][j]==1&&board[i-60][j]==1) return 1;//�����ʤ
            else if(board[i][j]==1&&board[i][j+30]==1&&board[i][j+60]==1&&board[i][j-30]==1&&board[i][j-60]==1) return 1;//�����ʤ
            else if(board[i][j]==1&&board[i+30][j+30]==1&&board[i+60][j+60]==1&&board[i-30][j-30]==1&&board[i-60][j-60]==1) return 1;//б��Ϊ1
            else if(board[i][j]==1&&board[i-30][j+30]==1&&board[i-60][j+60]==1&&board[i+30][j-30]==1&&board[i+60][j-60]==1) return 1;//б��Ϊ-1
            //�жϰ�����
            if(board[i][j]==-1&&board[i+30][j]==-1&&board[i+60][j]==-1&&board[i-30][j]==-1&&board[i-60][j]==-1) return 2;//�����ʤ
            else if(board[i][j]==-1&&board[i][j+30]==-1&&board[i][j+60]==-1&&board[i][j-30]==-1&&board[i][j-60]==-1) return 2;//�����ʤ
            else if(board[i][j]==-1&&board[i+30][j+30]==-1&&board[i+60][j+60]==-1&&board[i-30][j-30]==-1&&board[i-60][j-60]==-1) return 2;//б��Ϊ1
            else if(board[i][j]==-1&&board[i-30][j+30]==-1&&board[i-60][j+60]==-1&&board[i+30][j-30]==-1&&board[i+60][j-60]==-1) return 2;//б��Ϊ-1
        }
    }
}

void CreatePCBoard()//�˻�����
{
    setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ
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
    setfont(40, 15, "����");
    outtextxy(750,100,"PVP");
    setfillcolor(EGERGB(0xFF,0x0,0x0));
    setcolor(EGERGB(0xFF, 0xFF, 0x0));
    xyprintf(650, 40, "��ǰ��������0��");
    //P1��Ϣ
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "����");
    xyprintf(700,150,"PC(��):0");
    //P2��Ϣ
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "����");
    xyprintf(700,200,"Player(��):0");

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"�˳�");
}

void CreatePVPboard()//��������
{
    setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ
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
    setfont(40, 15, "����");
    outtextxy(750,100,"PVP");
    setfillcolor(EGERGB(0xFF,0x0,0x0));
    setcolor(EGERGB(0xFF, 0xFF, 0x0));
    xyprintf(650, 40, "��ǰ��������0��");
    //P1��Ϣ
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "����");
    xyprintf(700,150,"P1(��):0");
    //P2��Ϣ
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "����");
    xyprintf(700,200,"P2(��):0");

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"�˳�");
}

void PVPshow()//��ʾ��ǰ����״��
{
    setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ
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
    setfont(40, 15, "����");
    xyprintf(650, 40, "��ǰ��������%d��",step-1);

    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "����");
    outtextxy(750,100,"PVP");

    //p1:
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "����");
    xyprintf(700,150,"P1(��):%d",(step-1)/2+(step-1)%2);

    //p2
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "����");
    xyprintf(700,200,"P2(��):%d",(step-1)/2);

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"�˳�");
    if(bwin)
    {
        setcolor(EGERGB(0, 0, 0));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "����");
        outtextxy(630,350,"�����ʤ������·��ص����˵�");
    }
    else if(wwin)
    {
        setcolor(EGERGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "����");
        outtextxy(650,350,"�����ʤ,����·��˳����ص����˵�");
    }
}
void PVEshow()//��ʾ��ǰ�˻�����״��
{
    setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ
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
    setfont(40, 15, "����");
    xyprintf(650, 40, "��ǰ��������%d��",step+steppc);

    setcolor(EGERGB(0xFF, 0x0, 0x0));
    setbkmode(TRANSPARENT);
    setfont(40, 15, "����");
    outtextxy(750,100,"PVP");

    //p1:
    setcolor(EGERGB(255, 255, 255));
    setfont(40, 15, "����");
    xyprintf(700,150,"PC(��):%d",steppc);

    //p2
    setcolor(EGERGB(0,0,0));
    setfont(40, 15, "����");
    xyprintf(700,200,"Player(��):%d",step);

    setfillcolor(EGERGB(0xFF,0x0,0x0));
    bar(700,400,850,450);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    outtextxy(750,400,"�˳�");
    if(bwin)
    {
        setcolor(EGERGB(0, 0, 0));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "����");
        outtextxy(630,350,"���(��)��ʤ������·��ص����˵�");
    }
    else if(wwin)
    {
        setcolor(EGERGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        setfont(20, 10, "����");
        outtextxy(650,350,"����(��)��ʤ,����·��˳����ص����˵�");
    }
}
void pvp()//���˶�ս
{
    bwin=0;
    wwin=0;
    CreatePVPboard();
    step=1;//������ʼ��
        for ( ; is_run(); )
        {
            msg = getmouse();
            //�߽�����
            if((int)msg.is_down()&&(int)msg.x&&(int)msg.y&&visw[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]==0&&visb[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]==0&&msg.x>=50&&msg.x<=485&&msg.y>=55&&msg.y<=485)
            {
                step++;//ÿ��һ��������+1
                if((step)&1)
                {
                    visb[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//�����º���//ȡ����Ϊ�˾�ȷ����
                }
                if((step)%2==0)
                {
                    visw[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//ż���°���;
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



int caculate(int oldp[480][480],int qiuju[480][480][8][2])//�������
{
    int k;
    int cnt;
    int tx,ty;
    int dirx[8]={0,30,30,30,0,-30,-30,-30};//�˸�����
    int diry[8]={30,30,0,-30,-30,-30,0,30};//�˸�����
    for(int i=60;i<=480;i+=30)
    {
        for(int j=60;j<=480;j+=30)
        {
            if(oldp[i][j]==0)//�˴�Ϊ��
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
                        if(oldp[tx][ty]==1)//����
                        {
                            cnt++;
                        }
                        else break;
                    }
                    qiju[i][j][k][0]=cnt;
                    //����
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
                a1[i][j]=win;//����
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
                a2[i][j]=win;//������
            }
        }
    }
}

void AIprotect()//������AI
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



void pveeasy()//�˹�����
{
    memset(board,0,sizeof(board));//�������
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
            board[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//�����º���//ȡ����Ϊ�˾�ȷ����
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



void pve()//�е��Ѷ�
{
    memset(board,0,sizeof(board));//�������
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
            board[(int)msg.x-(int)msg.x%30][(int)msg.y-(int)msg.y%30]=1;//�����º���//ȡ����Ϊ�˾�ȷ����
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
    setbkcolor(EGERGB(255,255, 255));//���ñ�����ɫ
    setfillcolor(EGERGB(0,139,139));
    bar(200,100,800,200);

    setfillcolor(EGERGB(0,139,139));
    bar(200,300,800,400);

    setbkmode(TRANSPARENT);//�������͸����

    setcolor(EGERGB(160,32,240));
    setfont(70,30,"΢���ź�");
    outtextxy(380,100,"�˹�����");

    setcolor(EGERGB(160,32,240));
    setfont(70,30,"΢���ź�");
    outtextxy(350,300,"�����˹�����");
    for ( ; is_run(); delay_fps(60))//������
	{
		//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
		//���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ
		while (mousemsg())
		{
			msg = getmouse();
		}

		//��ʽ�����Ϊ�ַ��������ں������
		//msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������
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
    for ( ; is_run(); delay_fps(60))//������
	{
		//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
		//���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ
		while (mousemsg())
		{
			msg = getmouse();
		}

		//��ʽ�����Ϊ�ַ��������ں������
		//msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������
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
    if(flag==1)//�����˻���ս
	{
	    cleardevice();
	    createPC2();

	}
	//���˶Կ�
	else if(flag==2)
    {
        pvp();
    }
}
void exitt()//�˳������˵�
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
	CreateMenus();//���˵�
	choose();//�˵���ѡ��
	exitt();
	getch();
	return 0;
}
