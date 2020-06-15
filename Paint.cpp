#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int phyWidth= 700;
int phyHeight= 700;
int logWidth=100;
int logHeight=100;
int centerX=logWidth/2; int centerY=logHeight/2;
int mx=centerX, my = centerY;
int mouseX=centerX, mouseY=centerY;
int mouseXX=centerX, mouseYY=centerY;
int status8 = 0;
int shade8 =0;
int color8 =0;
int click = 0;
int xr = 0;
int yr=0;
int xr1=0;
int yr1=0;

void setPixel(int x, int y)
{
    glColor3f(0.0, 0.0, 0.0); //Set pixel to black
    glBegin(GL_POINTS);
    glVertex2i(x, y); //Set pixel coordinates
    glEnd();
    glFlush(); //Render pixel
}

GLint linePoints[100] = {}; //ARRAY FOR LINE POINTS
int j =-1;
GLint rectPoints[100] = {}; // ARRAY FOR REC POINTS
int r =-1;
GLint penPoints[1000] ={};
int p = -1;

int undomem[50] = {}; //STORE HISTORY OF DRAWINGS
int u = -1;  // 1 -> LINE, 2-> RECT, 3 -> FillRect, 4 -> CIRCLE, 5-> FillCircle, 6 -> Text, 7 ->Pen

void mouse(int x,int y){
    mx = x;
    mx=0.5+1.0*mx*logWidth/phyWidth;
    my = phyHeight - y;
    my=0.5+1.0*my*logHeight/phyHeight;

}

void passiveMouse (int x,int y){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
    mouseY = phyHeight - y;
    mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
    
    //SHADE ASSIGNED AS MOUSE HOVERS OVER BUTTON
    if(mouseX>=3&&mouseX<=10&&mouseY>=94&&mouseY<=97&&status8!=1)
        shade8=1;
    else if(mouseX>=3&&mouseX<=10&&mouseY>=90&&mouseY<=93&&status8!=2)
        shade8=2;
    else if(mouseX>=12&&mouseX<=19&&mouseY>=94&&mouseY<=97&&status8!=3)
        shade8=3;
    else if(mouseX>=12&&mouseX<=19&&mouseY>=90&&mouseY<=93&&status8!=4)
        shade8=4;
    else if(mouseX>=21&&mouseX<=28&&mouseY>=94&&mouseY<=97&&status8!=5)
        shade8=5;
    else if(mouseX>=21&&mouseX<=28&&mouseY>=90&&mouseY<=93&&status8!=6)
        shade8=6;
    else if(mouseX>=30&&mouseX<=37&&mouseY>=94&&mouseY<=97&&status8!=7)
        shade8=7;
    else if(mouseX>=30&&mouseX<=37&&mouseY>=90&&mouseY<=93&&status8!=8)
        shade8=8;
    else
        shade8=0;

    //printf("%d %d %d\n",shade8, mouseX, mouseY);
    glutPostRedisplay();
    
}

bool inCanvas(int x, int y){
if(x>3 && x<97 && y>3 && y<85)
    return true;
else
    return false;
}

void Timer(int value){
    glutTimerFunc(5, Timer, value);
    glutPostRedisplay();
}
int fill = 0;
void mouseClick(int btn,int state, int x, int y){
    
    
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        mouseXX = x;
        mouseXX=0.5+1.0*mouseXX*logWidth/phyWidth;
        mouseYY = phyHeight - y;
        mouseYY=0.5+1.0*mouseYY*logHeight/phyHeight;
        
        // CLICK = 1 WHEN MOUSE CLICKED IN CANVAS
        if(inCanvas(mouseXX, mouseYY)&&status8>0){
            click = 1;
                    }
        
        //STATUS ASSIGNED PER BUTTON CLICK MODE
        if(mouseXX>=3&&mouseXX<=10&&mouseYY>=94&&mouseYY<=97)
            status8=1;
        if(mouseXX>=3&&mouseXX<=10&&mouseYY>=90&&mouseYY<=93)
            status8=2;
        if(mouseXX>=12&&mouseXX<=19&&mouseYY>=94&&mouseYY<=97)
            status8=3;
        if(mouseXX>=12&&mouseXX<=19&&mouseYY>=90&&mouseYY<=93)
            status8=4;
        if(mouseXX>=21&&mouseXX<=28&&mouseYY>=94&&mouseYY<=97)
            status8=5;
        if(mouseXX>=21&&mouseXX<=28&&mouseYY>=90&&mouseYY<=93)
            status8=6;
        if(mouseXX>=30&&mouseXX<=37&&mouseYY>=94&&mouseYY<=97){
            status8=7;
            fill = 1;}
        if(mouseXX>=30&&mouseXX<=37&&mouseYY>=90&&mouseYY<=93){
            status8=8;
            fill =2 ;}
        
        // COLOR ASSIGNED PER COLOR MODE
        if(mouseXX>=94&&mouseXX<=97&&mouseYY>=92&&mouseYY<=95)
            color8 =1;
        if(mouseXX>=89&&mouseXX<=92&&mouseYY>=92&&mouseYY<=95)
            color8 =2;
        if(mouseXX>=84&&mouseXX<=87&&mouseYY>=92&&mouseYY<=95)
            color8 =3;
        if(mouseXX>=79&&mouseXX<=82&&mouseYY>=92&&mouseYY<=95)
            color8 =4;
        if(mouseXX>=74&&mouseXX<=77&&mouseYY>=92&&mouseYY<=95)
            color8 =5;
        if(mouseXX>=69&&mouseXX<=72&&mouseYY>=92&&mouseYY<=95)
            color8 =6;
        if(mouseXX>=64&&mouseXX<=67&&mouseYY>=92&&mouseYY<=95)
            color8 =7;
        if(mouseXX>=59&&mouseXX<=62&&mouseYY>=92&&mouseYY<=95)
            color8 =8;
    }
    
    // XR1, YR1 ASSIGNED TO MOUSE RELEASE POINT
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP&&inCanvas(mouseXX, mouseYY)){
        xr1 = x;
        xr1=0.5+1.0*xr1*logWidth/phyWidth;
        yr1 = phyHeight - y;
        yr1=0.5+1.0*yr1*logHeight/phyHeight;
        click = 2;
        
        printf("2 %d %d\n", xr1, yr1);
    }
    glutPostRedisplay();
    printf("%d    %d \n",click , status8);
    
}


void init2D() {
    glClearColor( 1.0, 1.0, 1.0 , 1.0); // COLOR BACKGROUND
    glMatrixMode( GL_PROJECTION); gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}
void printSome(char *str,int x,int y) {
    glColor3f (0.0, 0.0, 0.0);
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
    glFlush();
}

void drawMain(){

    glClear( GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0, 0.0, 0.0);
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(3,3);
    glVertex2i(3,85);
    glVertex2i(97,85);
    glVertex2i(97,3);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(3,97);
    glVertex2i(3,94);
    glVertex2i(10,94);
    glVertex2i(10,97);
    glEnd();
    printSome("Line", 4, 95);
    
    if(status8 == 1){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(3,97);
        glVertex2i(3,94);
        glVertex2i(10,94);
        glVertex2i(10,97);
        glEnd();
        printSome("Line", 4, 95);
    }
    if(shade8 == 1){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(3,97);
        glVertex2i(3,94);
        glVertex2i(10,94);
        glVertex2i(10,97);
        glEnd();
        printSome("Line", 4, 95);
    }
    
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(3,93);
    glVertex2i(3,90);
    glVertex2i(10,90);
    glVertex2i(10,93);
    glEnd();
    printSome("Pen", 4, 91);
    
    if(status8 == 2){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(3,93);
        glVertex2i(3,90);
        glVertex2i(10,90);
        glVertex2i(10,93);
        glEnd();
        printSome("Pen", 4, 91);
    }
    if(shade8 == 2){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(3,93);
        glVertex2i(3,90);
        glVertex2i(10,90);
        glVertex2i(10,93);
        glEnd();
        printSome("Pen", 4, 91);
    }
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(12,97);
    glVertex2i(12,94);
    glVertex2i(19,94);
    glVertex2i(19,97);
    glEnd();
    printSome("Rect", 13, 95);
    
    if(status8 == 3){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(12,97);
        glVertex2i(12,94);
        glVertex2i(19,94);
        glVertex2i(19,97);
        glEnd();
        printSome("Rect", 13, 95);
    }
    if(shade8 == 3){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(12,97);
        glVertex2i(12,94);
        glVertex2i(19,94);
        glVertex2i(19,97);
        glEnd();
        printSome("Rect", 13, 95);
    }
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(12,93);
    glVertex2i(12,90);
    glVertex2i(19,90);
    glVertex2i(19,93);
    glEnd();
    printSome("Text", 13, 91);
    
    if(status8 == 4){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(12,93);
        glVertex2i(12,90);
        glVertex2i(19,90);
        glVertex2i(19,93);
        glEnd();
        printSome("Text", 13, 91);
    }
    if(shade8 == 4){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(12,93);
        glVertex2i(12,90);
        glVertex2i(19,90);
        glVertex2i(19,93);
        glEnd();
        printSome("Text", 13, 91);
    }
    
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(21,97);
    glVertex2i(21,94);
    glVertex2i(28,94);
    glVertex2i(28,97);
    glEnd();
    printSome("Cirlce", 22, 95);
    
    if(status8 == 5){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(21,97);
        glVertex2i(21,94);
        glVertex2i(28,94);
        glVertex2i(28,97);
        glEnd();
        printSome("Cirlce", 22, 95);
        
    }
    if(shade8 == 5){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(21,97);
        glVertex2i(21,94);
        glVertex2i(28,94);
        glVertex2i(28,97);
        glEnd();
        printSome("Cirlce", 22, 95);
        
    }
    
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(21,93);
    glVertex2i(21,90);
    glVertex2i(28,90);
    glVertex2i(28,93);
    glEnd();
    printSome("Undo", 22, 91);
    
    if(status8 == 6){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(21,93);
        glVertex2i(21,90);
        glVertex2i(28,90);
        glVertex2i(28,93);
        glEnd();
        printSome("Undo", 22, 91);
        
    }
    if(shade8 == 6){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(21,93);
        glVertex2i(21,90);
        glVertex2i(28,90);
        glVertex2i(28,93);
        glEnd();
        printSome("Undo", 22, 91);
        
    }
    
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(30,97);
    glVertex2i(30,94);
    glVertex2i(37,94);
    glVertex2i(37,97);
    glEnd();
    printSome("Fill", 31, 95);
    
    if(status8 == 7){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(30,97);
        glVertex2i(30,94);
        glVertex2i(37,94);
        glVertex2i(37,97);
        glEnd();
        printSome("Fill", 31, 95);
    }
    if(shade8 == 7){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(30,97);
        glVertex2i(30,94);
        glVertex2i(37,94);
        glVertex2i(37,97);
        glEnd();
        printSome("Fill", 31, 95);
    }
    
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(30,93);
    glVertex2i(30,90);
    glVertex2i(37,90);
    glVertex2i(37,93);
    glEnd();
    printSome("No Fill", 31, 91);
    
    if(status8 == 8){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex2i(30,93);
        glVertex2i(30,90);
        glVertex2i(37,90);
        glVertex2i(37,93);
        glEnd();
        printSome("No Fill", 31, 91);
    }
    if(shade8 == 8){
        
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2i(30,93);
        glVertex2i(30,90);
        glVertex2i(37,90);
        glVertex2i(37,93);
        glEnd();
        printSome("No Fill", 31, 91);
    }
    
    
    glBegin(GL_POLYGON);// color 1 black
    glVertex2i(97,95);
    glVertex2i(94,95);
    glVertex2i(94,92);
    glVertex2i(97,92);
    glEnd();
    
    glColor3f(1,0,0);// color 2 red
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2i(92,95);
    glVertex2i(89,95);
    glVertex2i(89,92);
    glVertex2i(92,92);
    glEnd();
    
    glBegin(GL_POLYGON);// color 3 green
    glColor3f(0,1,0);
    glVertex2i(87,95);
    glVertex2i(84,95);
    glVertex2i(84,92);
    glVertex2i(87,92);
    glEnd();
    
    glBegin(GL_POLYGON);// color 4 blue
    glColor3f(0,0,1);
    glVertex2i(82,95);
    glVertex2i(79,95);
    glVertex2i(79,92);
    glVertex2i(82,92);
    glEnd();
    
    glBegin(GL_LINE_LOOP);// color 5 white
    glColor3f(0,0,0);
    glVertex2i(77,95);
    glVertex2i(74,95);
    glVertex2i(74,92);
    glVertex2i(77,92);
    glEnd();
    
    glBegin(GL_POLYGON);// color 6 yellow
    glColor3f(1,1,0);
    glVertex2i(72,95);
    glVertex2i(69,95);
    glVertex2i(69,92);
    glVertex2i(72,92);
    glEnd();
    
    glBegin(GL_POLYGON);// color 7 sky
    glColor3f(0,1,1);
    glVertex2i(67,95);
    glVertex2i(64,95);
    glVertex2i(64,92);
    glVertex2i(67,92);
    glEnd();
    
    glBegin(GL_POLYGON);// color 8 pink
    glColor3f(1,0,1);
    glVertex2i(62,95);
    glVertex2i(59,95);
    glVertex2i(59,92);
    glVertex2i(62,92);
    glEnd();

}

void drawline(){
    if(status8 == 1 && click == 1){
        j++;
        linePoints[j]=mouseXX;
        j++;
        linePoints[j]=mouseYY;
        printf("%d %d\n", mouseXX, mouseYY);
        click = 0;
    }
    if(status8 == 1 && click == 2){
        if(inCanvas(xr1, yr1)){
        j++;
        linePoints[j] = xr1;
        j++;
            linePoints[j] = yr1;}
        else{
            j++;
            linePoints[j] = linePoints[j-2];
            j++;
            linePoints[j] = linePoints[j-2];}
        click = 0;
        u++;
        undomem[u] = 1;
        for( int i = 0; i < j+1; i++){
            printf("%d ", linePoints[i]);
            
        }
        printf("\n ");
    }
    
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    for( int i = 0; i <= j; i++){
        
        glVertex2i(linePoints[i], linePoints[i+1]);
        
        i++;
    }
    glEnd();
    glFlush();


}

GLint rectnfPoints[100] = {};
int nf = -1;
void drawRect(){
    if(fill == 1){
    if(status8 == 3 && click == 1){
        r++;
        rectPoints[r]=mouseXX;
        r++;
        rectPoints[r]=mouseYY;
        printf("%d %d\n", mouseXX, mouseYY);
        click = 0;
    }
    if(status8 == 3 && click == 2){
        if(inCanvas(xr1, yr1)){
            r++;
            rectPoints[r] = xr1;
            r++;
            rectPoints[r] = yr1;}
        else{
            r-=2;}
        click = 0;
        u++;
        undomem[u] = 3;
        for( int i = 0; i < r+1; i++){
            printf("%d ", rectPoints[i]);
            
        }
        printf("\n ");
    }
        
    }
    
    else{
        if(status8 == 3 && click == 1){
            nf++;
            rectnfPoints[nf]=mouseXX;
            nf++;
            rectnfPoints[nf]=mouseYY;
            printf("%d %d\n", mouseXX, mouseYY);
            click = 0;
        }
        if(status8 == 3 && click == 2){
            if(inCanvas(xr1, yr1)){
                nf++;
                rectnfPoints[nf] = xr1;
                nf++;
                rectnfPoints[nf] = yr1;}
            else{
                nf-=2;}
            click = 0;
            u++;
            undomem[u] = 2;
            for( int i = 0; i < nf+1; i++){
                printf("%d ", rectnfPoints[i]);
                
            }
            printf("\n ");
        }
    }
    
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    if(color8 == 1)
        glColor3f(0,0,0);
    if(color8 == 2)
        glColor3f(1,0,0);
    if(color8 == 3)
        glColor3f(0,1,0);
    if(color8 == 4)
        glColor3f(0,0,1);
    if(color8 == 5)
        glColor3f(0,0,0);
    if(color8 == 6)
        glColor3f(1,1,0);
    if(color8 == 7)
        glColor3f(0,1,1);
    if(color8 == 8)
        glColor3f(1,0,1);
    for( int i = 0; i <= r; i+=4){
        if(rectPoints[i+2] == 0)
            break;
        glVertex2i(rectPoints[i], rectPoints[i+1]);
        
        
        glVertex2i(rectPoints[i+2], rectPoints[i+1]);
        
        
        glVertex2i(rectPoints[i+2], rectPoints[i+3]);
        
      
        glVertex2i(rectPoints[i], rectPoints[i+3]);
        
    }
        glEnd();
    
        glBegin(GL_LINES);
        glColor3f(0,0,0);
        for( int i = 0; i <= nf; i+=4){
            if(rectnfPoints[i+2] == 0)
                break;
            glVertex2i(rectnfPoints[i], rectnfPoints[i+1]);
            glVertex2i(rectnfPoints[i+2], rectnfPoints[i+1]);
            
            glVertex2i(rectnfPoints[i+2], rectnfPoints[i+1]);
            glVertex2i(rectnfPoints[i+2], rectnfPoints[i+3]);
            
            glVertex2i(rectnfPoints[i], rectnfPoints[i+1]);
            glVertex2i(rectnfPoints[i], rectnfPoints[i+3]);
            
            
            glVertex2i(rectnfPoints[i], rectnfPoints[i+3]);
            glVertex2i(rectnfPoints[i+2], rectnfPoints[i+3]);
            
        }
        glEnd();
    
    
    
    glFlush();
}
int penstart =0;
int penend = 0;
void drawPen(){

    if(status8 == 2 && click == 1){
        if(penstart == 0)
            penstart = p;
        p++;
        penPoints[p]=mx;
        p++;
        penPoints[p]=my;
        
    }
    if(status8 == 2 && click ==2){
        u++;
        undomem[u] = 7;
        penend = p;
        penstart = penend;
        click = 0;
    }
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    for( int i = 0; i <= p; i+=2){
        glVertex2i(penPoints[i], penPoints[i+1]);
    }
    glEnd();
    glFlush();

}
float circleCentx =0;
float circleCenty =0;
float radius =0;
GLfloat plainCircle[2000] ={};

GLfloat nfCircle[2000] = {};

int pcno = 0;
int nfcno = 0;

int cons = 400;

void drawCircle(){
    if(fill ==1){
    if(status8 == 5 && click == 1){
        circleCentx = mouseXX;
        circleCenty = mouseYY;
        printf("%f, %f\n", circleCentx, circleCenty);
        
    }
    if(status8 == 5 && click == 2){
      //  radius =20;
        float mxx = xr1;
        float myy = yr1;
        float rm = ((circleCentx-mxx));
    radius = sqrtf((((circleCentx-mxx)*(circleCentx-mxx))+((circleCenty-myy)*(circleCenty-myy))));
        printf("|%f| ", radius);
        for (int i = 0; i <= 400; i+=2) {
        float theta = 2.0f * 3.1415926f * float(i) / float(400); //get the current angle in
            float x = radius * cosf(theta);//calculate the x component
            float y = radius * sinf(theta);//calculate the y component
            nfCircle[i+(cons*nfcno)] = x+circleCentx;
            nfCircle[i+1+(cons*nfcno)] = y+circleCenty;
            //glVertex2f(x + cx, y + cy);//output vertex
        }
        click =0;
        u++;
        undomem[u] = 5;
        nfcno++;
    }}
    
    else{
        if(status8 == 5 && click == 1){
            circleCentx = mouseXX;
            circleCenty = mouseYY;
            printf("%f, %f\n", circleCentx, circleCenty);
            
        }
        if(status8 == 5 && click == 2){
            //  radius =20;
            float mxx = xr1;
            float myy = yr1;
            float rm = ((circleCentx-mxx));
            radius = sqrtf((((circleCentx-mxx)*(circleCentx-mxx))+((circleCenty-myy)*(circleCenty-myy))));
            printf("|%f| ", radius);
            for (int i = 0; i <= 400; i+=2) {
                float theta = 2.0f * 3.1415926f * float(i) / float(400); //get the current angle in
                float x = radius * cosf(theta);//calculate the x component
                float y = radius * sinf(theta);//calculate the y component
                plainCircle[i+(cons*pcno)] = x+circleCentx;
                plainCircle[i+1+(cons*pcno)] = y+circleCenty;
                //glVertex2f(x + cx, y + cy);//output vertex
            }
            click =0;
            u++;
            undomem[u] = 4;
            pcno++;
        }
    }
    
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    for( int i = 0; i <= 2000 ; i+=2){
        if(inCanvas(plainCircle[i], plainCircle[i+1])){
            glVertex2i(plainCircle[i], plainCircle[i+1]);}
        
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    if(color8 == 1)
        glColor3f(0,0,0);
    if(color8 == 2)
        glColor3f(1,0,0);
    if(color8 == 3)
        glColor3f(0,1,0);
    if(color8 == 4)
        glColor3f(0,0,1);
    if(color8 == 5)
        glColor3f(0,0,0);
    if(color8 == 6)
        glColor3f(1,1,0);
    if(color8 == 7)
        glColor3f(0,1,1);
    if(color8 == 8)
        glColor3f(1,0,1);
    for( int i = 0; i <= 2000 ; i+=2){
        if(inCanvas(nfCircle[i], nfCircle[i+1])){
            glVertex2i(nfCircle[i], nfCircle[i+1]);}
        
    }
    glEnd();
    glFlush();


}
int writex =0;
int writey =0;
char text[500];
int c = -1;

void keyboard(unsigned char key,int x, int y){
    if(status8 ==4 && click ==2){
        c++;
        text[c] = key;
    }
    if(key == 127){
        c--;
        text[c] = NULL;
    }
    

}
void textEditor(){
    if(status8 ==4 && click ==2){
        writex = mouseXX;
        writey = mouseYY;
        u++;
        undomem[u] = 6;
    }
    
    printSome(text, writex, writey);
    glFlush();
   
    
}

void undo(){
    
    if(status8 == 6){
        for(int i =0; i<=u ; i++){
            printf("%d ",undomem[u]);
        }
        printf("\n");
        
        if(undomem[u] == 1){
            if(j >= 3){
            j-=4;
                u--;}
            else
                j = -1;
        }
        else if(undomem[u] == 2){
            if(nf >= 3){
                nf-=4;
                u--;}
            else
                nf = -1;
        }
        else if(undomem[u] == 3){
            if(r >= 3){
                r-=4;
                u--;}
            else
                r = -1;
        }
        else if(undomem[u] == 7){
            if(p > -1){
                p-= penend;
                u--;}
            else
                p = -1;
        }
        else if(undomem[u] == 4){
            u--;
            for(int i = 0; i <= 400; i++)
                plainCircle[i] = 0;
        }
        else if(undomem[u] == 5){
            u--;
            for(int i = 0; i <= 400; i++)
                nfCircle[i] = 0;
        }
        else if(undomem[u] == 6){
            u--;
            for(int i =0; i <= c; i++)
                text[i] = NULL;
            c = -1;
            
        }

        status8 = 0;
    }
   

}
void Display() {
   
    drawMain();
    drawline();
    drawRect();
    drawPen();
    drawCircle();
    textEditor();
    undo();
    
glFlush();
glutSwapBuffers();

}

int main( int argc, char ** argv) {
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow( "Paint");
    init2D();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(Display);
    glutPassiveMotionFunc(passiveMouse);
    glutMotionFunc(mouse);
    glutMouseFunc(mouseClick);
    Timer(0);
    glutMainLoop();
}
