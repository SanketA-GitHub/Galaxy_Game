#include<stdlib.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

GLint sx=50,sy=50,bx,by,ex=50,ey=400,ebx,eby,ebx1,eby1,ebx2,eby2;
GLfloat maxx=640,maxy=480;
#define maxr 3
#define maxc 10
int flag=0,flag1=0,flag2=0,score=0,flag3=0,flag4=0,flag5=0,enemymat[maxr][maxc],i,j,c=0;
void myinit(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,maxx,0.0,maxy);
}


void drawText(char* text,float x,float y)
{
	int i;
	GLvoid *fontstyle=GLUT_BITMAP_TIMES_ROMAN_24;
	glRasterPos2f(x,y);
	glColor3f(1.0,1.0,1.0);
	for(i=0;text[i]!='\0';i++)
	{
		
		glutBitmapCharacter(fontstyle,text[i]);
	}
}

void myTimer(int value)
{
	switch(value)
	{
		case 0://ship bullet
			by=by+10;
			if(by>ey+70)
			{
				flag=0;
				break;
			}
			
			if(by>ey-20) {
			for(i=0;i<maxr;i++)
			{
				for(j=0;j<maxc;j++)
				{
					if(enemymat[i][j]==0)
						if(bx>ex+(30*j)-6&&bx<ex+(30*j)+12&&by<ey+(30*i)&&by>ey+(30*i)-18)//check if enemy is hit
						{
							by=maxy;
							//flag=0;
							enemymat[i][j]=1;
							j=i=11;
							score++;
						}
				}				
			}
			}
			glutTimerFunc(150,myTimer,0);
			break;
		case 1://enemy movement
			if(flag1==0)
			{
				ex+=5;
				if(c%2==0) //enemy downward movement
				{
					c++;
					ey-=20;
				}
				if(ex>330)
				{
					c++;
					flag1=1;
				}
			}
			if(flag1==1)
			{
				ex-=5;
				if(ex<50)
					flag1=0;
			}
			glutTimerFunc(150,myTimer,1);
			break;
		case 2://enemy bullet1 movement
			if(eby<sy+25&&eby>sy&&ebx<sx+18&&ebx>sx-3)//check if ship is hit
			{
				eby=0;
				flag5++;
			}
			if(eby<0)
			{
				flag2=0;
				break;
			}
			eby-=5;
			glutTimerFunc(100,myTimer,2);
			break;
		case 3://enemy bullet1 generation
			{
			int r=(rand()%(10));
			if(flag2==0)
			{
				
				flag2=1;
				ebx=ex+(r*30);
				eby=ey-5;
				glutTimerFunc(200,myTimer,2);
			}
			glutTimerFunc(1000,myTimer,3);
			break;
			}
		case 4://enemy bullet2 movement
			if(eby1<sy+25&&eby1>sy&&ebx1<sx+18&&ebx1>sx-3)//check if ship is hit
			{
				eby1=0;
				flag5++;
			}
			if(eby1<0)
			{
				flag3=0;
				break;
			}
			eby1-=5;
			glutTimerFunc(100,myTimer,4);
			break;
		case 5://enemy bullet2 generation
			if(flag3==0)
			{
				int r=(rand()%(10));
				flag3=1;
				ebx1=ex+(r*30);
				eby1=ey-5;
				glutTimerFunc(200,myTimer,4);
			}
			glutTimerFunc(1000,myTimer,5);
			break;
		case 6://enemy bullet3 movement
			if(eby2<sy+25&&eby2>sy&&ebx2<sx+18&&ebx2>sx-3)//check if ship is hit
			{
				eby2=0;
				flag5++;
			}
			if(eby2<0)
			{
				flag4=0;
				break;
			}
			eby2-=5;
			glutTimerFunc(100,myTimer,6);
			break;
		case 7://enemy bullet3 generation
			if(flag4==0)
			{
				int r=(rand()%(10));
				flag4=1;
				ebx2=ex+(r*30);
				eby2=ey-5;
				glutTimerFunc(200,myTimer,6);
			}
			glutTimerFunc(1000,myTimer,7);
			break;
	}
	glutPostRedisplay();
}
void myKeyboard(int key,int x, int y)
{
	switch(key)//ship movement
	{
		case GLUT_KEY_RIGHT:
				if(sx>maxx-50)
					break;
				sx=sx+5;
				break;
		case GLUT_KEY_LEFT:
				if(sx<50)
					break;
				sx=sx-5;
				break;
	}
	glutPostRedisplay();
}
void myKeyboard1(unsigned char key,int x, int y)
{
	switch(key)//ship bullet control
	{
		case ' ':
			if(flag==0)
			{
				flag=1;
				glutTimerFunc(100,myTimer,0);//start ship bullet movement
			}
			break;
	}
	glutPostRedisplay();
}



void drawShip(int x,int y)//space ship
{
	
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x,y);
		glVertex2i(x,y+12);
		glVertex2i(x+4,y+5);
		glVertex2i(x+7,y+8);
		glVertex2i(x+9,y+22);
		glVertex2i(x+11,y+8);
		glVertex2i(x+14,y+5);
		glVertex2i(x+18,y+12);
		glVertex2i(x+18,y);
		glVertex2i(x+11,y+3);
		glVertex2i(x+11,y);
		glVertex2i(x+7,y);
		glVertex2i(x+7,y+3);
	glEnd();
	
	glBegin(GL_TRIANGLES);
		glVertex2i(x,y);
		glVertex2i(x,y+12);
		glVertex2i(x+4,y+5);
		glVertex2i(x+7,y+8);
		glVertex2i(x+9,y+22);
		glVertex2i(x+11,y+8);
		glVertex2i(x+14,y+5);
		glVertex2i(x+18,y+12);
		glVertex2i(x+18,y);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2i(x+7,y+8);
		glVertex2i(x+11,y+8);
		glVertex2i(x+11,y);
		glVertex2i(x+7,y);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	if(flag==0)//set bullet at front of ship if not fired
	{
		bx=sx+8;
		by=sy+26;
	}
}
void drawBullet(int x,int y)//bullet
{
	glBegin(GL_QUADS);
		glVertex2i(x,y);
		glVertex2i(x,y+5);
		glVertex2i(x+2,y+5);
		glVertex2i(x+2,y);
	glEnd();
}
void drawEnemy(int x,int y)//enemy
{
	glBegin(GL_QUADS);
		glVertex2i(x,y);
		glVertex2i(x+6,y);
		glVertex2i(x+6,y-3);
		glVertex2i(x,y-3);
		glVertex2i(x-3,y-3);
		glVertex2i(x+9,y-3);
		glVertex2i(x+9,y-6);
		glVertex2i(x-3,y-6);
		glVertex2i(x-6,y-6);
		glVertex2i(x+12,y-6);
		glVertex2i(x+12,y-12);
		glVertex2i(x-6,y-12);
		glVertex2i(x-6,y-12);
		glVertex2i(x-3,y-12);
		glVertex2i(x-3,y-15);
		glVertex2i(x-6,y-15);
		glVertex2i(x+12,y-12);
		glVertex2i(x+9,y-12);
		glVertex2i(x+9,y-15);
		glVertex2i(x+12,y-15);
		glVertex2i(x-3,y-15);
		glVertex2i(x,y-15);
		glVertex2i(x,y-18);
		glVertex2i(x-3,y-18);
		glVertex2i(x+9,y-15);
		glVertex2i(x+6,y-15);
		glVertex2i(x+6,y-18);
		glVertex2i(x+9,y-18);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(x-3,y-6);
		glVertex2i(x,y-6);
		glVertex2i(x,y-9);
		glVertex2i(x-3,y-9);
		glVertex2i(x+9,y-6);
		glVertex2i(x+6,y-6);
		glVertex2i(x+6,y-9);
		glVertex2i(x+9,y-9);
		//glColor3f(1.0,1.0,1.0);
	glEnd();
}
void myDisplay(void)
{
	char str[20]="";
	glClear(GL_COLOR_BUFFER_BIT);
	if(flag5<3&&ey>60&&score<30)//check life,enemy y coordinate and score
	{
		drawShip(sx,sy);
		if(flag==1)//check if bullet is fired
			drawBullet(bx,by);
		if(flag2==1)//check if enemy bullet1 is fired
			drawBullet(ebx,eby);
		if(flag3==1)//check if enemy bullet2 is fired
			drawBullet(ebx1,eby1);
		if(flag4==1)//check if enemy bullet3 is fired
			drawBullet(ebx2,eby2);
		for(i=0;i<maxr;i++)//generate 30 enemy
		{
			for(j=0;j<maxc;j++)
			{
				if(j%2==0)//for alternate red
					glColor3f(1.0,0.0,0.0);
				else//for alternate green
					glColor3f(0.0,1.0,0.0);
				if(enemymat[i][j]==0)//check if enemy is hit
					drawEnemy(ex+(30*j),ey+(30*i));
			}	
		}
		glColor3f(1.0,1.0,1.0);
		sprintf(str,"Score : %d",score);
		drawText(str,10,maxy-24);
		sprintf(str,"Lives : %d",3-flag5);
		drawText(str,150,maxy-24);
		
	}
	else if(score>=30)
	{
		drawText("YOU WIN",200,maxy-100);
		sprintf(str,"Score : %d",score);
		drawText(str,200,maxy/2);
	}
	else
	{
		drawText("GAME OVER",200,maxy-100);
		sprintf(str,"Score : %d",score);
		drawText(str,200,maxy/2);
	}
	glFlush();
}
int main(int argc, char **argv)
{	
	for(i=0;i<maxr;i++)
		for(j=0;j<maxc;j++)
			enemymat[i][j]=0;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(maxx,maxy);
	glutInitWindowPosition(250,350);
	glutCreateWindow("Galaxy");
	glutDisplayFunc(myDisplay);
	glutTimerFunc(300,myTimer,1);//start enemy movement
	glutTimerFunc(900,myTimer,3);//enemy bullet1 initial call
	glutTimerFunc(2500,myTimer,5);//enemy bullet2 initial call
	glutTimerFunc(4500,myTimer,7);//enemy bullet3 initial call
	glutSpecialFunc(myKeyboard);
	glutKeyboardFunc(myKeyboard1);
	myinit();
	glutMainLoop();
}
