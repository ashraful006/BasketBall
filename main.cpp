#include <iostream>
#include<GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <sstream>


using namespace std;
int is_gameover=0;
int counter1=0;
int counter2=0;
int counter_score=0;
int prev=0;
char Gameover[]="Game over!!!!!!";

char Exit[]="Esc : Exit";
char reset[]="Reset : R";

char score[]="Score:";
char Throw[]="Throw : Space";


float BarSpeed=0.0;
bool a=false;           ///if ball is thrown

float l=1.5;

float getx(int x){return float(x)/float(400);}

float gety(int y){return float(y)/float(400);}

float _move = 0.0f;

float ballRadius=.03;
float ballx;
float rotAngle=0.0;
float bally;
float ballxMax=1.0-.1,ballxMin=-1.0+.1,ballyMax=1.0-.1,ballyMin=-1.0+.1;
float xSpeed=.02;
float ySpeed=.02;



string FloatToString(int f){

    stringstream ss;

    ss << f;

    string s = ss.str();

    return s;

}







void Sprint( float x, float y, char *st)
{
    int l,i;


    l=strlen(st);
    glColor3f(0.0,1.0,0.7);
    glRasterPos2f( x, y);
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }


}







void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 32:
        if(counter1==0){
            a=true;
            ballx=.3*cos(rotAngle*.0175);
            bally=.3*sin(rotAngle*.0175);
            counter1=1;
        }
        break;
      case 114:

        a=false;
        counter1=0;
        xSpeed=.02;
        ySpeed=.02;
        counter_score=0;
        prev=0;
        BarSpeed=0.0;
        counter2=0;
        is_gameover=0;
        _move=0.0;
        break;
      case 27:
        exit(0);
        break;




   }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);



	glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);

    glVertex3f(getx(-400),gety(290),0.0);
    glVertex3f(getx(400),gety(290),0.0);
    glVertex3f(getx(400),gety(295),0.0);
    glVertex3f(getx(-400),gety(295),0.0);
    glEnd();




    glPopMatrix();


    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(getx(-120),gety(-40),0.0);
    glVertex3f(getx(120),gety(-40),0.0);
    glVertex3f(getx(120),gety(-30),0.0);
    glVertex3f(getx(-120),gety(-30),0.0);
    glEnd();
    glPopMatrix();





    glPushMatrix();
    glTranslatef(_move, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(getx(-75),gety(355),0.0);
    glVertex3f(getx(-75),gety(290),0.0);
    glVertex3f(getx(75),gety(290),0.0);
    glVertex3f(getx(75),gety(355),0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(getx(-70),gety(350),0.0);
    glVertex3f(getx(-70),gety(295),0.0);
    glVertex3f(getx(70),gety(295),0.0);
    glVertex3f(getx(70),gety(350),0.0);

    glEnd();


    glPopMatrix();




    glPushMatrix();
    if(a==false){
        glRotated(rotAngle,0.0,0.0,1.0);
    }
    if(a==true){
        glTranslatef(ballx,bally,0.0);

    }
    if(a==false){
        glTranslatef(.2,0.0,0.0);
    }

    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    int seg=200;
    glBegin(GL_POLYGON);
	for(int i=0;i<seg;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/seg;
		float r=0.075;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
    glEnd();
    glPopMatrix();



    glPushMatrix();
        glColor3f(0.0,1.0,0.0);
        Sprint(.5,-.5,score);
    glPopMatrix();



    glPushMatrix();
        glColor3f(0.0,1.0,0.0);

        string s=FloatToString(counter_score);
        char ch[1024];
        strncpy(ch,s.c_str(),sizeof(ch));
        Sprint(.5,-.55,ch);

        Sprint(-.85,-.5,Exit);
        Sprint(-.85,-.55,reset);
        Sprint(-.2,-.7,Throw);
        if(is_gameover==1){
            Sprint(-.2,-.2,Gameover);
        }


    glPopMatrix();




	glutSwapBuffers();





	if(a==true){


        ballx+=xSpeed*cos(rotAngle*0.0175);
        bally+=ySpeed*sin(rotAngle*0.0175);
        if(ballx>ballxMax){
            ballx=ballxMax;
            xSpeed= -xSpeed;
        }
        else if(ballx<ballxMin){
            ballx=ballxMin;
            xSpeed= -xSpeed;
        }
        if(bally>ballyMax){
            bally=ballyMax;
            ySpeed= -ySpeed;
        }
        else if(bally<ballyMin){
            bally=ballyMin;
            ySpeed = -ySpeed;
        }
	}


	_move += BarSpeed;
    if(_move > 1.0-.185)
    {
        BarSpeed=-BarSpeed;
    }
    else if(_move<-1.0+.185){
        BarSpeed=-BarSpeed;
    }


    if(a==false){
        rotAngle+=l;

        if(rotAngle>145){
            rotAngle=145;
            l=-l;
        }
        if(rotAngle<35){
            rotAngle=35;
            l=-l;
        }
    }













}

void update(int value) {




    if(ySpeed<0){
        if(bally*400>290 && bally*400<297){
            prev=counter_score;
            if((ballx*400)>-75+(_move*400) && (ballx*400)<(75+_move*400)  ){

                    counter_score++;
                    counter2++;
            }
        }
    }

    if(bally*400<200 && ySpeed<0){
            if(counter_score<=prev){
                a=false;
                xSpeed=.02;
                ySpeed=.02;
                counter1=1;
                is_gameover=1;

            }
            else{
                a=false;
                counter1=0;
                xSpeed=.02;
                ySpeed=.02;

            }
    }


    if(counter2>=3){
        BarSpeed+=.01;
        counter2=0;
    }

	glutPostRedisplay();

	glutTimerFunc(20, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Transformation");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(20, update, 0);
	glutMainLoop();
	return 0;
}
