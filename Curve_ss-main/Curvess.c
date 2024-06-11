# include "iGraphics.h"

double curve[200],y,width=1280,height=720,mid=360,radius=1,balx,dx,dx2,Y=0,dx1,baly[200],paused=0,tracer[200],dobx,cur_y,deg,doby,instruction=280,nn,mm;
int j=3;
double fre[200]={1.1,0.7,2.0};
double amplitude[200]={155,175,100};
double amp[200]={155,175,100};
double amplitude1[200]={155,175,100};
double radx,radx1;
int i,pos=-1,prevmx,prevmy,pressed=0,initial=0,hide=0,rightbutton=0,x,leftshift,rightshift;
double amin=360,amax=0,amin1=4;
double phase;
double maxi(double a , double b)
{
    if(a >= b) return a;
    else return b;
}
double mini(double a , double b)
{
    if(a >= b) return b;
    else return a;
}
double abs(double a, double b){
    return a-b<0?-(a-b):a-b ;
}
void initialise()
{
    iSetColor(255,255,255);
    iRectangle(320,335,640,50);
    iSetColor(250,120,0);
    iFilledRectangle(330,345,620,30);
    iSetColor(0,0,0);
    iText(450,350,"                   START         ",GLUT_BITMAP_TIMES_ROMAN_24);
}
void mouse(int x,int y)
{
    nn=x;
    mm=720-y;
}
void shift()
{
    iSetColor(250,120,0);
    iFilledRectangle(50,10,100,30);
    iSetColor(255,255,255);
    iText(52,20,"  Right shifting",GLUT_BITMAP_HELVETICA_12);
    iSetColor(0,255,0);
    iFilledRectangle(160,10,100,30);
    iSetColor(0,0,0);
    iText(162,20,"  Left Shifting" ,GLUT_BITMAP_HELVETICA_12);
    iSetColor(0,0,255);
    iFilledRectangle(270,10,100,30);
    iSetColor(0,0,0);
    iText(272,20,"  No shift" ,GLUT_BITMAP_HELVETICA_12);
    if(nn>=50&&nn<=150&&mm>=10&&mm<=40)
    {
        iSetColor(250,250,250);
        iFilledRectangle(50,10,100,30);
        iSetColor(0,0,0);
        iText(52,20,"  Right shifting",GLUT_BITMAP_HELVETICA_12);
    }
    if(nn>=160&&nn<=260&&mm>=10&&mm<=40)
    {
        iSetColor(250,250,250);
        iFilledRectangle(160,10,100,30);
        iSetColor(0,0,0);
        iText(162,20,"  Left Shifting" ,GLUT_BITMAP_HELVETICA_12);
    }
    if(nn>=270&&nn<=370&&mm>=10&&mm<=40)
    {
        iSetColor(250,250,1250);
        iFilledRectangle(270,10,100,30);
        iSetColor(0,0,0);
        iText(272,20,"  No shift" ,GLUT_BITMAP_HELVETICA_12);
    }

}
void clicktoresume()
{
    iSetColor(255,180,0);
    iFilledRectangle(330,345,620,30);
    iSetColor(0,0,0);
    iText(450,350,"CLICK HERE TO RESUME",GLUT_BITMAP_TIMES_ROMAN_24);
}
void showinstrction()
{
    iSetColor(20,20,20);
    iFilledRectangle(1000,0,280,720);
    iSetColor(250,250,250);
    iText(1010,680,"Add graph :  Right Button ",GLUT_BITMAP_9_BY_15);
    iText(1010,650, "Hide/show all graph : S/s ",GLUT_BITMAP_9_BY_15);
    iText(1010,620, "Tracer tracking : 0-9 ",GLUT_BITMAP_9_BY_15);
    iText(1010,590, "Tracer speed : +/- ",GLUT_BITMAP_9_BY_15);
    iText(1010,560, "Change direction : l/r ",GLUT_BITMAP_9_BY_15);
    iText(1010,530,"Change Amplitude : A/a ",GLUT_BITMAP_9_BY_15);
    iText(1010,500,"Change frequency : F/f",GLUT_BITMAP_9_BY_15);
    iText(1010,470,"Pause : P",GLUT_BITMAP_9_BY_15);
    iText(1010,440,"Phase shifting: </>",GLUT_BITMAP_9_BY_15);
    iText(1010,410,"Track individual graph :",GLUT_BITMAP_9_BY_15);
    iText(1020,380," Left button&drag",GLUT_BITMAP_9_BY_15);
    iText(1010,350,"Skip the screen: F1",GLUT_BITMAP_9_BY_15);
    iText(1010,320,"End to exit",GLUT_BITMAP_9_BY_15);
}
void show_graph()
{
    if(initial){
        if(paused)
            {
                clicktoresume();
            }
        int sum[1290]={0};
        if(rightshift)
        {
            phase+=(3.1416)/180;
        }
        if(leftshift)
        {
            phase-=(3.1416)/180;
        }
        for(i=0;i<j;i++)
        {
            for(x=0;x<=1000+instruction;x++)
            {
                radx=(x*3.1416)/180;
                if(i%3==0)
                {
                    y=mid+(sin((radx*fre[i])+phase)*amp[i]);
                    sum[x]+=y-mid;
                }
                else if(i%3==1)
                {
                    y=mid+(cos((radx*fre[i])+phase)*amp[i]);
                    sum[x]+=y-mid;
                }
                else if(i%3==2)
                {
                    y=mid+(sin((radx*fre[i])+phase)*amp[i]);
                    sum[x]+=y;
                }
                iSetColor(250,120,0);
                iLine(x-1,Y,x,y);
                Y=y;
            }
        }
        Y=0;
        for(x=0;x<=1000+(int)instruction;x++)
        {
            iSetColor(250,250,250);
            iLine(x-1,Y,x,sum[x]);
            Y=sum[x];
        }
    }
}

void change_individiual_graph(int mx,int my)
{
        pos=-1;
        prevmx=mx;
        prevmy=my;
        doby=prevmy*1.0;
        dobx=prevmx*1.0;
        for(i=0;i<j;i++)
        {
                deg=(dobx*3.1416)/180;
                if(i%3==0)
                {
                    cur_y=mid+(sin((deg*fre[i])+phase)*amp[i]);
                    if(abs(doby-cur_y)<=20.0)
                    {
                        pos=i;
                        break;

                    }
                }
                else if(i%3==1)
                {
                    cur_y=mid+(cos((deg*fre[i])+phase)*amp[i]);
                    if(abs(doby-cur_y)<=20.0)
                    {
                        pos=i;
                        break;

                    }
                }
                else if(i%3==2)
                {
                    cur_y=mid+(sin((deg*fre[i])+phase)*amp[i]);
                    if(abs(doby-cur_y)<=20.0)
                    {
                        pos=i;
                        break;

                    }
                }

        }
        rightbutton=0;

}

void addgraph()
{
    if(!hide){
        fre[j]=fre[j-1]+1;
        amplitude[j]=amplitude[j-1]+35;
        if(amplitude[j]>0) amplitude[j]=mini(amin,amplitude[j]);
        else if (amplitude[j]<0) amplitude[j]=maxi(-amin,amplitude[j]);
        amp[j]=amplitude[j];
        amplitude1[j]=amplitude[j];
        j++;
    }
}

void iDraw()
{
    iClear();
    glutPassiveMotionFunc(mouse);
    if(!initial)
    {
        initialise();
    }
    else if(initial)
    {
        shift();
        if(pressed)
        {
            showinstrction();
            instruction=0;

        }
        else
        {
            iSetColor(255,255,255);
            iText(1010,20,"press F1 to show instructions",GLUT_BITMAP_HELVETICA_18);
            instruction=280;
        }
        for(i=0;i<=1000+instruction;i++)
        {
            iSetColor(255,255,255);
            iFilledCircle(i,mid,1);
        }
        for(i=0;i<=j;i++)
        {
            if(tracer[i])
            {
                iSetColor(0,0,0);
                iFilledCircle(balx,baly[i],0);
            }
            else if(i%3==0&&j-i>0)
            {
                iSetColor(255,0,0);
                iFilledCircle(balx,baly[i],5);
            }
            else if(i%3==1&&j-i>0)
            {
                iSetColor(0,0,255);
                iFilledCircle(balx,baly[i],5);
            }
            else if(i%3==2&&j-i>0)
            {
                iSetColor(0,255,0);
                iFilledCircle(balx,baly[i],5);
            }
            else if(j-i==0)
            {
                iSetColor(255,255,255);
                iFilledCircle(balx,baly[i],5);
            }
        }
        show_graph();
    }

}

void iMouseMove(int buttonx, int buttony)
{
    if(pos!=-1&&rightbutton==0){
        amplitude[pos]=((buttony*1.0-mid)/(prevmy-mid))*amplitude[pos];
        amplitude1[pos]=amplitude[pos];
        amp[pos]=amplitude[pos];
        if(buttonx==0) buttonx++;
        fre[pos]=fre[pos]*(prevmx*1.0/buttonx);
        if(fre[pos]<0) fre[pos]*=-1;
        prevmx=buttonx;
        prevmy=buttony;
        if(prevmy*1.0-mid==0) prevmy+=1;
    }
}

void iMouse(int button, int state, int mx1, int my1){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(initial)
        {
            if(paused)
            {
                if(mx1>=320&&mx1<=960&&my1>=340&&my1<=380)
                {
                    paused=0;
                    dx=dx1;
                }
            }
            if(!paused)
            {
                if(mx1>=50&&mx1<=150&&my1>=10&&my1<=40)
                {
                    rightshift=1;
                    leftshift=0;
                }
                else if(mx1>=160&&mx1<=260&&my1>=10&&my1<=40)
                {
                    leftshift=1;
                    rightshift=0;
                }
                else if(mx1>=270&&mx1<=370&&my1>=10&&my1<=40)
                {
                    rightshift=0;
                    leftshift=0;
                }
            }
            change_individiual_graph(mx1,my1);
        }
        else
        {
            if(mx1>=320&&mx1<=960&&my1>=340&&my1<=380)
            {
                initial=1;
            }
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        rightbutton=1;
        if(initial) addgraph();
    }
}

void iKeyboard(unsigned char key)
{
    if(key=='S')
    {
        for(i=0;i<=j;i++)
        {
            hide=1;
            amp[i]=0;
        }

    }
    if(key=='s')
    {
        for(i=0;i<=j;i++)
        {
            amp[i]=amplitude[i];
            hide=0;
        }
    }
    if(key=='F')
    {
        for(i=0;i<=j;i++)
        {
            fre[i]+=0.1;
            fre[i]=mini(amin1,fre[i]);
        }
    }
    if(key=='f')
    {
        for(i=0;i<=j;i++)
        {
            fre[i]-=0.1;
            fre[i]=maxi(amax,fre[i]);
        }
    }
    if(key=='A')
    {
        for(i=0;i<j;i++)
        {
            if(amplitude[i]<0)
            {
                amplitude[i]-=1;
                amplitude[i]=maxi(amplitude[i],-amin);
                if(!hide) amp[i]=amplitude[i];
                amplitude1[i]=amplitude[i];
            }
            else
            {
                amplitude[i]+=1;
                amplitude[i]=mini(amplitude[i],amin);
                if(!hide) amp[i]=amplitude[i];
                amplitude1[i]=amplitude[i];
            }

        }
    }
    if(key=='a')
    {
        for(i=0;i<=j;i++)
        {
                if(amplitude[i]==-1)
                {
                    amplitude[i]=0;
                    amp[i]=amplitude[i];
                    amplitude[i]=amplitude[i];
                }
                else if(amplitude[i]<-1)
                {
                    amplitude[i]+=1;
                    if(!hide) amp[i]=amplitude[i];
                    amplitude1[i]=amplitude[i];
                }
                else
                {
                    amplitude[i]-=1;
                    amplitude[i]=maxi(amax,amplitude[i]);
                    if(!hide) amp[i]=amplitude[i];
                    amplitude1[i]=amplitude[i];
                }
        }
    }
    if(key =='+')
    {
        if(dx>=0&&dx2>=0) dx++;
        else if(dx<=0) dx--;
    }
    else if(key =='-')
    {
        if(dx>0)
        {
            dx2=dx;
            dx--;
        }
        else if(dx<0)
        {
            dx2=dx;
            dx++;
        }
    }
    if(key=='P')
    {
        if(!paused){
            dx1=dx;
            dx=0;
            paused=1;
            rightshift=0;
            leftshift=0;
        }
    }
    if(key=='r')
    {
        if(dx<0) dx=-dx;
    }
    if(key=='l')
    {
        if(dx>0) dx=-dx;
    }
    if(key=='0')
    {
        if(!tracer[0]) tracer[0]=1;
        else if(tracer[0]) tracer[0]=0;
    }
    if(key=='1')
    {
        if(!tracer[1]) tracer[1]=1;
        else if(tracer[1]) tracer[1]=0;
    }
    if(key=='2')
    {
        if(!tracer[2]) tracer[2]=1;
        else if(tracer[2]) tracer[2]=0;
    }
    if(key=='3')
    {
        if(!tracer[3]) tracer[3]=1;
        else if(tracer[3]) tracer[3]=0;
    }
    if(key=='4')
    {
        if(!tracer[4]) tracer[4]=1;
        else if(tracer[4]) tracer[4]=0;
    }
    if(key=='5')
    {
        if(!tracer[5]) tracer[5]=1;
        else if(tracer[5]) tracer[5]=0;
    }
    if(key=='6')
    {
        if(!tracer[6]) tracer[6]=1;
        else if(tracer[6]) tracer[6]=0;
    }
    if(key=='7')
    {
        if(!tracer[7]) tracer[7]=1;
        else if(tracer[7]) tracer[7]=0;
    }
    if(key=='8')
    {
        if(!tracer[8]) tracer[8]=1;
        else if(tracer[8]) tracer[8]=0;
    }
    if(key=='9')
    {
        if(!tracer[9]) tracer[9]=1;
        else if(tracer[9]) tracer[9]=0;
    }
    if(key=='>')
    {
        phase=phase+((2*3.1416)/180*1.0);
    }
    if(key=='<')
    {
        phase=phase-((2*3.1416)/180*1.0);
    }


}

void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_F1)
    {
        pressed=(pressed+1)%2;
    }

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
}
void change()
{
    if(initial){
        balx+=dx;
        if(balx<0||balx>1000+instruction)
        {
            dx=-dx;
        }
        radx1=(balx*3.1416)/180;
        for(i=0;i<=j;i++){
            if(i%3==0&&j-i>0)
            {
                baly[i]=mid+(sin((radx1*fre[i])+phase)*amplitude1[i]);
            }
            if(i%3==1&&j-i>0)
            {
                baly[i]=mid+(cos((radx1*fre[i])+phase)*amplitude1[i]);
            }
            if(i%3==2&&j-i>0)
            {
                baly[i]=mid+sin((radx1*fre[i])+phase)*amplitude1[i];
            }
            if(j-i==0)
            {
                baly[j]=0;
                for(int k=0;k<i;k++)
                {
                    baly[j]+=baly[k]-mid;
                }
                baly[j]+=mid;
            }


        }
    }
}
