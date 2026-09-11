//player 1,ID:41230301538 Name:Mahbub ALAm
//player 2,ID:41230301453 Name:Samia Tasnim
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

float p1=150,p2=350,e1=150,e2=350;
float y1=550,y2=700,s1=4,s2=4;
int score1=0,score2=0,life1=3,life2=3;
int high1=0,high2=0,level=1;
int start=0,pause=0,over=0,road=0;
float er1=1,eg1=.7,eb1=0;
float er2=1,eg2=.7,eb2=0;
void box(float a,float b,float c,float d)
{
    glBegin(GL_QUADS);
    glVertex2f(a,b); glVertex2f(c,b);
    glVertex2f(c,d); glVertex2f(a,d);
    glEnd();
}
void text(float x,float y,char *s)
{
    glRasterPos2f(x,y);
    for(int i=0;s[i];i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}
void car(float x,float y,float r,float g,float b)
{
    // Body
    glColor3f(r,g,b);
    box(x-22,y-45,x+22,y+45);
    // Roof
    glColor3f(r*.7,g*.7,b*.7);
    glBegin(GL_QUADS);
    glVertex2f(x-15,y-15); glVertex2f(x+15,y-15);
    glVertex2f(x+12,y+30); glVertex2f(x-12,y+30);
    glEnd();
    // Glass
    glColor3f(.6,.9,1);
    box(x-10,y-8,x+10,y+24);
    // Lights
    glColor3f(1,1,0);
    box(x-16,y+36,x-8,y+42);
    box(x+8,y+36,x+16,y+42);
    // Wheels
    glColor3f(.05,.05,.05);
    box(x-27,y-38,x-20,y-15);
    box(x-27,y+15,x-20,y+38);
    box(x+20,y-38,x+27,y-15);
    box(x+20,y+15,x+27,y+38);
}
void resetGame()
{
    p1=150; p2=350;
    e1=150; e2=350;
    y1=550; y2=700;
    s1=s2=4;
    score1=score2=0;
    life1=life2=3;
    level=1;
    road=0;
    pause=0;
    over=0;
    er1=er2=1;
    eg1=eg2=.7;
    eb1=eb2=0;
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Background
    glColor3f(.1,.5,.1);
    box(0,0,500,500);
    // Road
    glColor3f(.2,.2,.2);
    box(80,0,420,500);
   //Road Divider
    glColor3f(1,1,1);
    for(int i=-60;i<560;i+=60)
        box(245,i+road,255,i+30+road);
    // Players
    if(life1) car(p1,60,0,.3,1);
    if(life2) car(p2,60,1,0,0);
    // Enemies
    if(life1) car(e1,y1,er1,eg1,eb1);
    if(life2) car(e2,y2,er2,eg2,eb2);
    char t[60];
    // Score and life
    glColor3f(1,1,1);
    sprintf(t,"P1:%d Life:%d Speed:%.1f",
            score1,life1,s1);
    text(5,480,t);
    sprintf(t,"P2:%d Life:%d Speed:%.1f",
            score2,life2,s2);
    text(300,480,t);
    sprintf(t,"Level: %d",level);
    text(220,460,t);
    sprintf(t,"High:%d",high1);
    text(5,445,t);
    sprintf(t,"High:%d",high2);
    text(440,445,t);
    // Start Screen
    if(!start)
    {
        glColor3f(1,1,0);
        glRasterPos2f(165,300);
        sprintf(t,"2 PLAYER CAR RACING");
        for(int i=0;t[i];i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,t[i]);
        text(175,260,(char*)"Press SPACE to Start");
        text(150,230,(char*)"P1: A/D   P2: LEFT/RIGHT");
    }
    // Pause
    if(pause && !over && start)
    {
        glColor3f(1,1,0);
        text(220,280,(char*)"PAUSED");
        text(185,250,(char*)"Press P to Resume");
    }
    // Game Over
    if(over)
    {
        glColor3f(1,1,0);
        if(score1>score2)
            sprintf(t,"PLAYER 1 WINS!");
        else if(score2>score1)
            sprintf(t,"PLAYER 2 WINS!");
        else
            sprintf(t,"DRAW!");
        glRasterPos2f(180,290);
        for(int i=0;t[i];i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,t[i]);
        text(175,250,(char*)"Press R to Restart");
    }
   glutSwapBuffers();
}
void keyboard(unsigned char key,int x,int y)
{
   // Start
    if(key==' ')
    {
        if(!start)
        {
            start=1;
            resetGame();
        }
    }

    // Player 1
    if(start && !pause && !over)
    {
        if((key=='a'||key=='A')&&p1>105&&life1)
            p1-=15;

        if((key=='d'||key=='D')&&p1<395&&life1)
            p1+=15;
    }
   // Pause
    if(key=='p'||key=='P')
    {
        if(start && !over)
            pause=!pause;
    }
   // Restart
    if(key=='r'||key=='R')
    {
        start=1;
        resetGame();
    }

    glutPostRedisplay();
}
void specialKeys(int key,int x,int y)
{
    if(start&&!pause&&!over&&life2)
    {
        if(key==GLUT_KEY_LEFT&&p2>105)
            p2-=15;
        if(key==GLUT_KEY_RIGHT&&p2<395)
            p2+=15;
    }
  glutPostRedisplay();
}
void newEnemy(int n)
{
    if(n==1)
    {
        y1=550;
        e1=105+rand()%290;

        // Different enemy colors
        int c=rand()%3;
        if(c==0){er1=1;eg1=.7;eb1=0;}
        if(c==1){er1=.7;eg1=.2;eb1=1;}
        if(c==2){er1=0;eg1=.9;eb1=.3;}
    }
    else
    {
        y2=700;
        e2=105+rand()%290;
        int c=rand()%3;
        if(c==0){er2=1;eg2=.7;eb2=0;}
        if(c==1){er2=.7;eg2=.2;eb2=1;}
        if(c==2){er2=0;eg2=.9;eb2=.3;}
    }
}
void update(int v)
{
    if(start&&!pause&&!over)
    {
 // Road movement
        road-=5;
        if(road<-60) road=0;
 // Level
        level=1+(score1+score2)/5;
        if(level>10) level=10;
   // Player 1
        if(life1)
        {
            y1-=s1;

            if(y1<-45)
            {
                score1++;
                if(score1>high1) high1=score1;

                s1=4+level*.5;
                if(s1>9)s1=9;

                newEnemy(1);
            }
         if(y1<105&&y1>15&&
               abs((int)e1-(int)p1)<35)
            {
                life1--;
                newEnemy(1);
            }
        }

        // Player 2
        if(life2)
        {
            y2-=s2;

            if(y2<-45)
            {
                score2++;
                if(score2>high2) high2=score2;

                s2=4+level*.5;
                if(s2>9)s2=9;

                newEnemy(2);
            }
          if(y2<105&&y2>15&&
               abs((int)e2-(int)p2)<35)
            {
                life2--;
                newEnemy(2);
            }
        }
      // Game Over
        if(!life1&&!life2)
            over=1;
    }
    glutPostRedisplay();
    glutTimerFunc(30,update,0);
}
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char** argv)
{
    srand(time(0));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("2 Player Car Racing");
    glClearColor(.1,.5,.1,1);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(30,update,0);
    glutMainLoop();
    return 0;
}
