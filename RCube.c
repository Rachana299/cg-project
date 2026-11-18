#include<string.h> 
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h> 
#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#include<time.h>
 
void *font = GLUT_BITMAP_HELVETICA_18; 
static char historyFullMessage[] = "History full";
static char *statusMessage=NULL;
 
void output(int x, int y, char *string) 
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

static int top[3][3]={{0,0,0},{0,0,0},{0,0,0}}, 
right[3][3]={{1,1,1},{1,1,1},{1,1,1}}, 
front[3][3]={{2,2,2},{2,2,2},{2,2,2}}, 
back[3][3]={{3,3,3},{3,3,3},{3,3,3}}, 
bottom[3][3]={{4,4,4},{4,4,4},{4,4,4}}, 
left[3][3]={{5,5,5},{5,5,5},{5,5,5}}, 
temp[3][3]; 
 
int solve[300]; 
int count=0; 
int solve1=0; 
static int rotation=0; 
int rotationcomplete=0; 
static GLfloat theta=0.0; 
#define CUBE_TURN_SPEED 2.5f
static GLint axis=0; 
static GLfloat p=0.0,q=0.0,r=0.0; 
static GLint inverse=0; 
static GLfloat angle=0.0; 
int beginx=0,beginy=0; 
int moving=0; 
static int controlsVisible=0;
static int windowWidth=500,windowHeight=500;
static int cubeRendering=0;
enum {CHALLENGE_IDLE,CHALLENGE_COUNTDOWN,CHALLENGE_RUNNING,CHALLENGE_PAUSED,CHALLENGE_SOLVED,CHALLENGE_EXPIRED,CHALLENGE_STOPPED,CHALLENGE_ERROR};
static int challengeState=CHALLENGE_IDLE;
static int challengeMenuVisible=0;
static int practiceMenuVisible=0;
static int challengeCountdown=3;
static int challengeDurationMilliseconds=0;
static int challengeRemainingMilliseconds=0;
static int challengeStartTime=0;
static int challengeElapsedMilliseconds=0;
static int challengeGeneration=0;
static int challengeGoVisible=0;
static int practiceActive=0;
static int practiceAutoPlaying=0;
static int practiceMovePending=0;
static int practiceMoveCount=0;
static int practiceMoveIndex=0;
static int practiceMoves[30];
GLfloat vertices[][3]={{-1.0,-1.0,-1.0}, 
 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, //center 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                        
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0},  //bottom center 
                       {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                        
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0},  //left center 
                       {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0}, 

                       {1.0,-1.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, // right center 
                       {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, // top center 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, 
 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, //front center 

                       {-1.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
 
                       {-1.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, //back center 
                       {-1.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, // top left center 
                       {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0},  
                             
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 

                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, // top right  center 
                       {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, 
 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, // top front center 
                       {-1.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {1.0,3.0,3.0}, 
                       {-1.0,3.0,3.0}, 
 
                       {-1.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {1.0,3.0,-3.0}, 
                       {-1.0,3.0,-3.0}, // top back center 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 

        {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0},  //bottom left center 
                       {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-3.0,-1.0,1.0}, 
 
        {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0},  //bottom  right center 
                       {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
            
        {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0},  //bottom front center 

                       {-1.0,-3.0,3.0}, 
                       {1.0,-3.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
 
                       {-1.0,-3.0,-3.0}, 
                       {1.0,-3.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0},  //bottom back center 
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
 
        {-3.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-1.0,3.0,-3.0}, 
                       {-3.0,3.0,-3.0}, // top left back 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, 
 
        {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0}, // top left front 
                       {-3.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-1.0,3.0,3.0}, 
                       {-3.0,3.0,3.0}, 
 
        {1.0,1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {3.0,3.0,-3.0}, 
                       {1.0,3.0,-3.0}, // top right  back 
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
 
        {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, // top right  front 
                       {1.0,1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {3.0,3.0,3.0}, 

                       {1.0,3.0,3.0}, 
 
        {-3.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-3.0,1.0,-3.0},  //ceneter left back 
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0}, 
 
        {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0},  //center left front 
                       {-3.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-3.0,1.0,3.0}, 
 
        {1.0,-1.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, // center right back 
                       {1.0,-1.0,-1.0}, 

                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
 
        {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, // center right front 
                       {1.0,-1.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
 
        {-3.0,-3.0,-3.0}, 
                       {-1.0,-3.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-3.0,-1.0,-3.0},  //bottom left back 
                       {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0}, 
 
        {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 

                       {-3.0,-1.0,1.0},  //bottom left front 
                       {-3.0,-3.0,3.0}, 
                       {-1.0,-3.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-3.0,-1.0,3.0}, 
 
        {1.0,-3.0,-3.0}, 
                       {3.0,-3.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0},  //bottom  right back 
                       {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
            
        {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0},  //bottom  right front 
                       {1.0,-3.0,3.0}, 
                       {3.0,-3.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
        
}; 
                      
GLfloat color[][3]={{0.94,0.94,0.91},  //white 
                    {0.96,0.34,0.06},  //orange 
                    {0.04,0.22,0.78},  //blue 
                    {0.04,0.58,0.22},  //green 
                    {0.98,0.82,0.04},  //yellow 
                    {0.82,0.035,0.035}, //red 
		{0.055,0.065,0.08} //dark plastic body
};


void polygon(int a,int b,int c,int d,int e) 
{
	if(cubeRendering)
	{
		GLfloat face[4][3];
		GLfloat center[3]={0.0f,0.0f,0.0f};
		GLfloat normal[3];
		GLfloat edge1[3],edge2[3],normalLength;
		int indices[4]={b,c,d,e};
		int i,j;

		for(i=0;i<4;i++)
		{
			face[i][0]=vertices[indices[i]][0];
			face[i][1]=vertices[indices[i]][1];
			face[i][2]=vertices[indices[i]][2];
			center[0]+=face[i][0]*0.25f;
			center[1]+=face[i][1]*0.25f;
			center[2]+=face[i][2]*0.25f;
		}

		edge1[0]=face[1][0]-face[0][0];
		edge1[1]=face[1][1]-face[0][1];
		edge1[2]=face[1][2]-face[0][2];
		edge2[0]=face[2][0]-face[0][0];
		edge2[1]=face[2][1]-face[0][1];
		edge2[2]=face[2][2]-face[0][2];
		normal[0]=edge1[1]*edge2[2]-edge1[2]*edge2[1];
		normal[1]=edge1[2]*edge2[0]-edge1[0]*edge2[2];
		normal[2]=edge1[0]*edge2[1]-edge1[1]*edge2[0];
		normalLength=sqrtf(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);
		if(normalLength>0.0f)
		{
			normal[0]/=normalLength;
			normal[1]/=normalLength;
			normal[2]/=normalLength;
		}

		glNormal3fv(normal);
		glColor3fv(color[6]);
		glBegin(GL_QUADS);
		for(i=0;i<4;i++)
			glVertex3fv(face[i]);
		glEnd();

		if(a!=6)
		{
			GLfloat insetFace[4][3];
			const GLfloat insetScale=0.84f;
			const GLfloat cornerCut=0.12f;
			const GLfloat stickerOffset=0.012f;

			for(i=0;i<4;i++)
			{
				insetFace[i][0]=center[0]+(face[i][0]-center[0])*insetScale;
				insetFace[i][1]=center[1]+(face[i][1]-center[1])*insetScale;
				insetFace[i][2]=center[2]+(face[i][2]-center[2])*insetScale;
			}

			glColor3fv(color[a]);
			glBegin(GL_POLYGON);
			for(i=0;i<4;i++)
			{
				int previous=(i+3)%4;
				int next=(i+1)%4;
				for(j=0;j<2;j++)
				{
					int neighbor=(j==0) ? previous : next;
					GLfloat stickerPoint[3];
					stickerPoint[0]=insetFace[i][0]+(insetFace[neighbor][0]-insetFace[i][0])*cornerCut+normal[0]*stickerOffset;
					stickerPoint[1]=insetFace[i][1]+(insetFace[neighbor][1]-insetFace[i][1])*cornerCut+normal[1]*stickerOffset;
					stickerPoint[2]=insetFace[i][2]+(insetFace[neighbor][2]-insetFace[i][2])*cornerCut+normal[2]*stickerOffset;
					glVertex3fv(stickerPoint);
				}
			}
			glEnd();
		}
		return;
	}

	glColor3f(0,0,0); 
	glLineWidth(3.0); 
	glBegin(GL_LINE_LOOP); 
	glVertex3fv(vertices[b]); 
	glVertex3fv(vertices[c]); 
	glVertex3fv(vertices[d]); 
	glVertex3fv(vertices[e]); 
	glEnd(); 

	glColor3fv(color[a]); 
	glBegin(GL_POLYGON); 
	glVertex3fv(vertices[b]); 
	glVertex3fv(vertices[c]); 
	glVertex3fv(vertices[d]); 
	glVertex3fv(vertices[e]); 
	glEnd(); 
} 

 
void colorcube1() 
{ 
	polygon(6,0,3,2,1);  
	polygon(6,2,3,7,6);  
	polygon(6,0,4,7,3);    // center piece 
	polygon(6,1,2,6,5);            
	polygon(6,4,5,6,7); 
	polygon(6,0,1,5,4);  
}
 
void colorcube2() 
{ 
	polygon(6,8,11,10,9);  
	polygon(6,10,11,15,14);  
	polygon(6,8,12,15,11);    // bottom center 
	polygon(6,9,10,14,13);            
	polygon(6,12,13,14,15); 
	polygon(bottom[1][1],8,9,13,12);  
} 
 
void colorcube3() 
{ 
	polygon(6,16,19,18,17);  
	polygon(6,18,19,23,22);  
	polygon(left[1][1],16,20,23,19);    // left center 
	polygon(6,17,18,22,21);            
	polygon(6,20,21,22,23); 
	polygon(6,16,17,21,20);  
} 
 
void colorcube4() 
{ 
	polygon(6,24,27,26,25);  
	polygon(6,26,27,31,30);  
	polygon(6,24,28,31,27);    // right center 
	polygon(right[1][1],25,26,30,29);            
	polygon(6,28,29,30,31); 
	polygon(6,24,25,29,28);  
} 
 
void colorcube5() 
{ 
	polygon(6,32,35,34,33);  
	polygon(top[1][1],34,35,39,38);  
	polygon(6,32,36,39,35);    // top center 
	polygon(6,33,34,38,37);            
	polygon(6,36,37,38,39); 
	polygon(6,32,33,37,36);  
} 
 
void colorcube6() 
{ 
	polygon(6,40,43,42,41);  
	polygon(6,42,43,47,46);  
	polygon(6,40,44,47,43);    // front center 
	polygon(6,41,42,46,45);            
	polygon(front[1][1],44,45,46,47); 
	polygon(6,40,41,45,44);  
} 
 
void colorcube7() 
{ 
	polygon(back[1][1],48,51,50,49);  
	polygon(6,50,51,55,54);  
	polygon(6,48,52,55,51);    //back center 
	polygon(6,49,50,54,53);            
	polygon(6,52,53,54,55); 
	polygon(6,48,49,53,52);  
} 

void colorcube8() 
{ 
	polygon(6,56,59,58,57);  
	polygon(top[1][0],58,59,63,62);  
	polygon(left[0][1],56,60,63,59);    // top left center 
	polygon(6,57,58,62,61);            
	polygon(6,60,61,62,63); 
	polygon(6,56,57,61,60);  
} 

void colorcube9() 
{ 
	polygon(6,64,67,66,65);  
	polygon(top[1][2],66,67,71,70);  
	polygon(6,64,68,71,67);    // top right center 
	polygon(right[0][1],65,66,70,69);            
	polygon(6,68,69,70,71); 
	polygon(6,64,65,69,68);  
} 
 
void colorcube10() 
{ 
	polygon(6,72,75,74,73);  
	polygon(top[2][1],74,75,79,78);  
	polygon(6,72,76,79,75);    // top front center 
	polygon(6,73,74,78,77);            
	polygon(front[0][1],76,77,78,79); 
	polygon(6,72,73,77,76);  
} 
 
void colorcube11() 
{ 
	polygon(back[0][1],80,83,82,81);  
	polygon(top[0][1],82,83,87,86);  
	polygon(6,80,84,87,83);    // top back center 
	polygon(6,81,82,86,85);            
	polygon(6,84,85,86,87); 
	polygon(6,80,81,85,84);  
} 
 
void colorcube12() 
{ 
	polygon(6,80+8,83+8,82+8,81+8);  
	polygon(6,82+8,83+8,87+8,86+8);  
	polygon(left[2][1],80+8,84+8,87+8,83+8);    // bottom left center 
	polygon(6,81+8,82+8,86+8,85+8);            
	polygon(6,84+8,85+8,86+8,87+8); 
	polygon(bottom[1][0],80+8,81+8,85+8,84+8);  
} 
 
void colorcube13() 
{ 
	polygon(6,80+16,83+16,82+16,81+16);  
	polygon(6,82+16,83+16,87+16,86+16);  
	polygon(6,80+16,84+16,87+16,83+16);    // bottom right center 
	polygon(right[2][1],81+16,82+16,86+16,85+16);            
	polygon(6,84+16,85+16,86+16,87+16); 
	polygon(bottom[1][2],80+16,81+16,85+16,84+16);  
} 
 
void colorcube14() 
{ 
	polygon(6,80+24,83+24,82+24,81+24);  
	polygon(6,82+24,83+24,87+24,86+24);  
	polygon(6,80+24,84+24,87+24,83+24);    // bottom front center 
	polygon(6,81+24,82+24,86+24,85+24);            
	polygon(front[2][1],84+24,85+24,86+24,87+24); 
	polygon(bottom[0][1],80+24,81+24,85+24,84+24);  
} 

void colorcube15() 
{ 
	polygon(back[2][1],112,115,114,113);  
	polygon(6,114,115,119,118);  
	polygon(6,112,116,119,115);    // bottom back center 
	polygon(6,113,114,118,117);            
	polygon(6,116,117,118,119); 
	polygon(bottom[2][1],112,113,117,116);  
} 
 
void colorcube16() 
{ 
	polygon(back[0][2],120,123,122,121);  
	polygon(top[0][0],122,123,127,126);  
	polygon(left[0][0],120,124,127,123);    // top left back 
	polygon(6,121,122,126,125);            
	polygon(6,124,125,126,127); 
	polygon(6,120,121,125,124);  
} 

void colorcube17() 
{ 
	polygon(6,128,131,130,129);  
	polygon(top[2][0],130,131,135,134);  
	polygon(left[0][2],128,132,135,131);    // top left front 
	polygon(6,129,130,134,133);            
	polygon(front[0][0],132,133,134,135); 
	polygon(6,128,129,133,132);  
} 
 
void colorcube18() 
{ 
	polygon(back[0][0],136,139,138,137);  
	polygon(top[0][2],138,139,143,142);  
	polygon(6,136,140,143,139);    // top right back 
	polygon(right[0][2],137,138,142,141);            
	polygon(6,140,141,142,143); 
	polygon(6,136,137,141,140);  
} 
 
void colorcube19() 
{ 
	polygon(6,144,147,146,145);  
	polygon(top[2][2],146,147,151,150);  
	polygon(6,144,148,151,147);    // top right front 
	polygon(right[0][0],145,146,150,149);            
	polygon(front[0][2],148,149,150,151); 
	polygon(6,144,145,149,148);  
} 
 
void colorcube20() 
{ 
polygon(back[1][2],152,155,154,153);  
polygon(6,154,155,159,158);  
polygon(left[1][0],152,156,159,155);    //center left back 
polygon(6,153,154,158,157);            
polygon(6,156,157,158,159); 
polygon(6,152,153,157,156);  
} 
 
void colorcube21() 
{ 
	polygon(6,160,163,162,161);  
	polygon(6,162,163,167,166);  
	polygon(left[1][2],160,164,167,163);    // center left front 
	polygon(6,161,162,166,165);            
	polygon(front[1][0],164,165,166,167); 
	polygon(6,160,161,165,164);  
} 

void colorcube22() 
{ 
	polygon(back[1][0],168,171,170,169);  
	polygon(6,170,171,175,174);  
	polygon(6,168,172,175,171);    // center right back 
	polygon(right[1][2],169,170,174,173);            
	polygon(6,172,173,174,175); 
	polygon(6,168,169,173,172);  
} 

void colorcube23() 
{ 
	polygon(6,176,179,178,177);  
	polygon(6,178,179,183,182);  
	polygon(6,176,180,183,179);    //center right front 
	polygon(right[1][0],177,178,182,181);            
	polygon(front[1][2],180,181,182,183); 
	polygon(6,176,177,181,180);  
} 
 
void colorcube24() 
{ 
	polygon(back[2][2],184,187,186,185);  
	polygon(6,186,187,191,190);  
	polygon(left[2][0],184,188,191,187);    // bottom left back 
	polygon(6,185,186,190,189);            
	polygon(6,188,189,190,191); 
	polygon(bottom[2][0],184,185,189,188);  
} 

void colorcube25() 
{ 
	polygon(6,192,195,194,193);  
	polygon(6,194,195,199,198);  
	polygon(left[2][2],192,196,199,195);    // bottom left front 
	polygon(6,193,194,198,197);            
	polygon(front[2][0],196,197,198,199); 
	polygon(bottom[0][0],192,193,197,196);  
} 
 
void colorcube26() 
{ 
	polygon(back[2][0],200,203,202,201);  
	polygon(6,202,203,207,206);  
	polygon(6,200,204,207,203);    // bottom right back 
	polygon(right[2][2],201,202,206,205);            
	polygon(6,204,205,206,207); 
	polygon(bottom[2][2],200,201,205,204);  
}

void colorcube27() 
{ 
	polygon(6,208,211,210,209);  
	polygon(6,210,211,215,214);  
	polygon(6,208,212,215,211);    // bottom right front 
	polygon(right[2][0],209,210,214,213);            
	polygon(front[2][2],212,213,214,215); 
	polygon(bottom[0][2],208,209,213,212);  
} 
 
#define CONTROL_PANEL_LEFT 10
#define CONTROL_PANEL_TOP 10
#define CONTROL_PANEL_WIDTH 270
#define CONTROL_PANEL_HEIGHT 430
#define CONTROL_PANEL_FIRST_ROW 44
#define CONTROL_PANEL_ROW_HEIGHT 22

static void drawScreenRect(GLfloat x,GLfloat y,GLfloat width,GLfloat height,
	GLfloat red,GLfloat green,GLfloat blue)
{
	glColor3f(red,green,blue);
	glBegin(GL_QUADS);
	glVertex2f(x,y);
	glVertex2f(x+width,y);
	glVertex2f(x+width,y+height);
	glVertex2f(x,y+height);
	glEnd();
}

static void drawScreenOutline(GLfloat x,GLfloat y,GLfloat width,GLfloat height,
	GLfloat red,GLfloat green,GLfloat blue)
{
	glColor3f(red,green,blue);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x,y);
	glVertex2f(x+width,y);
	glVertex2f(x+width,y+height);
	glVertex2f(x,y+height);
	glEnd();
}

void drawControlsPanel()
{
	GLboolean depthTestEnabled;
	int rowY,i;
	void *previousFont;
	static char *moveLabels[13]={
		"TOP","TOP INVERSE","RIGHT","RIGHT INVERSE","FRONT","FRONT INVERSE",
		"LEFT","LEFT INVERSE","BACK","BACK INVERSE","BOTTOM","BOTTOM INVERSE",
		"UNDO LAST MOVE"
	};
	static char *moveKeys[13]={"A","Q","S","W","D","E","F","R","G","T","H","Y","O"};

	if(!controlsVisible)
		return;

	previousFont=font;
	font=GLUT_BITMAP_HELVETICA_12;
	depthTestEnabled=glIsEnabled(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)windowWidth,(GLdouble)windowHeight,0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawScreenRect(CONTROL_PANEL_LEFT,CONTROL_PANEL_TOP,CONTROL_PANEL_WIDTH,
		CONTROL_PANEL_HEIGHT,0.045f,0.06f,0.095f);
	drawScreenOutline(CONTROL_PANEL_LEFT,CONTROL_PANEL_TOP,CONTROL_PANEL_WIDTH,
		CONTROL_PANEL_HEIGHT,0.15f,0.23f,0.32f);
	drawScreenRect(CONTROL_PANEL_LEFT,CONTROL_PANEL_TOP,CONTROL_PANEL_WIDTH,
		3,0.12f,0.78f,0.88f);

	font=GLUT_BITMAP_HELVETICA_18;
	glColor3f(0.94f,0.97f,1.0f);
	output(CONTROL_PANEL_LEFT+12,CONTROL_PANEL_TOP+24,"MOVE CONTROLS");
	font=GLUT_BITMAP_HELVETICA_12;
	glColor3f(0.47f,0.68f,0.78f);
	output(CONTROL_PANEL_LEFT+12,CONTROL_PANEL_TOP+39,"CLICK A ROW OR PRESS ITS KEY");

	glBegin(GL_QUADS);
	for(i=0;i<13;i++)
	{
		GLfloat rowTop=CONTROL_PANEL_FIRST_ROW+i*CONTROL_PANEL_ROW_HEIGHT;
		if(i==12)
			glColor3f(0.10f,0.16f,0.21f);
		else if(i%2==0)
			glColor3f(0.075f,0.105f,0.15f);
		else
			glColor3f(0.06f,0.085f,0.125f);
		glVertex2f(CONTROL_PANEL_LEFT+10,rowTop);
		glVertex2f(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-10,rowTop);
		glVertex2f(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-10,rowTop+20);
		glVertex2f(CONTROL_PANEL_LEFT+10,rowTop+20);
	}
	glEnd();
	glBegin(GL_QUADS);
	for(i=0;i<13;i++)
	{
		GLfloat rowTop=CONTROL_PANEL_FIRST_ROW+i*CONTROL_PANEL_ROW_HEIGHT;
		if(i==12)
			glColor3f(0.45f,0.31f,0.12f);
		else
			glColor3f(0.13f,0.24f,0.31f);
		glVertex2f(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-48,rowTop+3);
		glVertex2f(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-16,rowTop+3);
		glVertex2f(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-16,rowTop+17);
		glVertex2f(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-48,rowTop+17);
	}
	glEnd();

	for(i=0;i<13;i++)
	{
		rowY=CONTROL_PANEL_FIRST_ROW+i*CONTROL_PANEL_ROW_HEIGHT;
		glColor3f(i==12 ? 1.0f : 0.83f,i==12 ? 0.84f : 0.88f,0.92f);
		output(CONTROL_PANEL_LEFT+18,rowY+15,moveLabels[i]);
		glColor3f(0.68f,0.9f,0.96f);
		output(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-39,rowY+14,moveKeys[i]);
	}

	glColor3f(0.45f,0.5f,0.6f);
	glBegin(GL_LINES);
	glVertex2i(CONTROL_PANEL_LEFT+10,CONTROL_PANEL_TOP+330);
	glVertex2i(CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH-10,CONTROL_PANEL_TOP+330);
	glEnd();

	glColor3f(0.82f,0.87f,0.94f);
	output(CONTROL_PANEL_LEFT+12,CONTROL_PANEL_TOP+354,"DRAG OUTSIDE TO ORBIT");
	output(CONTROL_PANEL_LEFT+12,CONTROL_PANEL_TOP+376,"VIEW: 4/6  2/8  1/9  |  RESET: 5");
	drawScreenRect(CONTROL_PANEL_LEFT+10,CONTROL_PANEL_TOP+400,
		CONTROL_PANEL_WIDTH-20,24,0.34f,0.10f,0.12f);
	glColor3f(1.0f,0.78f,0.75f);
	output(CONTROL_PANEL_LEFT+20,CONTROL_PANEL_TOP+417,"EXIT GAME");

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	if(depthTestEnabled)
		glEnable(GL_DEPTH_TEST);
	font=previousFont;
}

#define CHALLENGE_BASE_TOP 12
#define CHALLENGE_BASE_WIDTH 200
#define CHALLENGE_BASE_HEIGHT 42
#define CHALLENGE_BASE_MARGIN 12
#define CHALLENGE_BASE_MENU_ROW_HEIGHT 34
#define CHALLENGE_BASE_STATUS_HEIGHT 50

static GLfloat challengeUIScale(void)
{
	GLfloat scaleX=(GLfloat)windowWidth/500.0f;
	GLfloat scaleY=(GLfloat)windowHeight/500.0f;
	GLfloat scale=(scaleX<scaleY) ? scaleX : scaleY;

	if(scale<0.65f)
		scale=0.65f;
	if(scale>3.0f)
		scale=3.0f;
	return scale;
}

static void outputChallengeText(GLfloat x,GLfloat y,const char *text,GLfloat height)
{
	GLfloat textScale=height/119.05f;
	int i;

	glPushMatrix();
	glTranslatef(x,y,0.0f);
	glScalef(textScale,-textScale,1.0f);
	for(i=0;text[i]!='\0';i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,(int)(unsigned char)text[i]);
	glPopMatrix();
}

static void drawGameHUD(void)
{
	GLboolean depthTestEnabled;
	GLfloat scale=challengeUIScale();
	GLfloat left=12.0f*scale;
	GLfloat top=12.0f*scale;
	GLfloat width=240.0f*scale;
	GLfloat height=56.0f*scale;
	GLfloat accentRed=0.12f,accentGreen=0.78f,accentBlue=0.88f;
	char detail[48];
	static const char *moveNames[7]={"","U","R","F","L","B","D"};

	if(controlsVisible)
		return;

	if(statusMessage!=NULL)
		snprintf(detail,sizeof(detail),"%s",statusMessage);
	else if(rotation>0)
		snprintf(detail,sizeof(detail),"TURN: %s%s",
			moveNames[rotation],inverse ? "'" : "");
	else if(practiceActive)
	{
		snprintf(detail,sizeof(detail),"PRACTICE MODE  |  STEP OR PLAY");
		accentRed=0.25f;
		accentGreen=0.82f;
		accentBlue=0.62f;
	}
	else if(challengeState==CHALLENGE_COUNTDOWN ||
	        challengeState==CHALLENGE_RUNNING ||
	        challengeState==CHALLENGE_PAUSED)
	{
		snprintf(detail,sizeof(detail),"CHALLENGE MODE  |  RACE THE CLOCK");
		accentRed=0.96f;
		accentGreen=0.66f;
		accentBlue=0.24f;
	}
	else
		snprintf(detail,sizeof(detail),"DRAG TO ORBIT  |  RIGHT-CLICK FOR MOVES");

	depthTestEnabled=glIsEnabled(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)windowWidth,(GLdouble)windowHeight,0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawScreenRect(left,top,width,height,0.035f,0.05f,0.08f);
	drawScreenOutline(left,top,width,height,0.14f,0.21f,0.29f);
	drawScreenRect(left,top,3.0f*scale,height,accentRed,accentGreen,accentBlue);
	outputChallengeText(left+13.0f*scale,top+23.0f*scale,"CUBE ARENA",17.0f*scale);
	outputChallengeText(left+13.0f*scale,top+43.0f*scale,detail,9.0f*scale);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	if(depthTestEnabled)
		glEnable(GL_DEPTH_TEST);
}

static void drawCubeMapFace(const int face[3][3],int reverseColumns,
	GLfloat x,GLfloat y,GLfloat cellSize,GLfloat gap)
{
	int row,column;

	glBegin(GL_QUADS);
	for(row=0;row<3;row++)
	{
		for(column=0;column<3;column++)
		{
			int faceColumn=reverseColumns ? 2-column : column;
			GLfloat cellX=x+column*(cellSize+gap);
			GLfloat cellY=y+row*(cellSize+gap);

			glColor3f(0.02f,0.025f,0.035f);
			glVertex2f(cellX,cellY);
			glVertex2f(cellX+cellSize,cellY);
			glVertex2f(cellX+cellSize,cellY+cellSize);
			glVertex2f(cellX,cellY+cellSize);

			glColor3fv(color[face[row][faceColumn]]);
			glVertex2f(cellX+gap,cellY+gap);
			glVertex2f(cellX+cellSize-gap,cellY+gap);
			glVertex2f(cellX+cellSize-gap,cellY+cellSize-gap);
			glVertex2f(cellX+gap,cellY+cellSize-gap);
		}
	}
	glEnd();
}

static void drawCubeMap(void)
{
	GLboolean depthTestEnabled;
	GLfloat scaleX=(GLfloat)windowWidth/500.0f;
	GLfloat scaleY=(GLfloat)windowHeight/500.0f;
	GLfloat scale=scaleX<scaleY ? scaleX : scaleY;
	GLfloat cellSize,gap,padding,titleHeight,faceSize,panelWidth,panelHeight;
	GLfloat panelLeft,panelTop,faceLeft,faceTop;
	void *previousFont;

	if(scale<0.45f)
		scale=0.45f;
	if(scale>2.5f)
		scale=2.5f;

	cellSize=14.0f*scale;
	gap=1.0f*scale;
	padding=8.0f*scale;
	titleHeight=18.0f*scale;
	faceSize=3.0f*cellSize+2.0f*gap;
	panelWidth=4.0f*faceSize+2.0f*padding;
	panelHeight=3.0f*faceSize+titleHeight+2.0f*padding;
	panelLeft=windowWidth-panelWidth-12.0f*scale;
	panelTop=windowHeight-panelHeight-12.0f*scale;
	faceLeft=panelLeft+padding;
	faceTop=panelTop+padding+titleHeight;

	previousFont=font;
	font=GLUT_BITMAP_HELVETICA_12;
	depthTestEnabled=glIsEnabled(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)windowWidth,(GLdouble)windowHeight,0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	drawScreenRect(panelLeft,panelTop,panelWidth,panelHeight,0.035f,0.05f,0.08f);
	drawScreenOutline(panelLeft,panelTop,panelWidth,panelHeight,0.14f,0.21f,0.29f);
	drawScreenRect(panelLeft,panelTop,panelWidth,2.0f*scale,
		0.12f,0.78f,0.88f);

	font=GLUT_BITMAP_HELVETICA_12;
	glColor3f(0.65f,0.82f,0.9f);
	output((int)(panelLeft+padding),(int)(panelTop+16.0f*scale),"CUBE STATE");

	drawCubeMapFace(top,0,faceLeft+faceSize,faceTop,cellSize,gap);
	drawCubeMapFace(left,0,faceLeft,faceTop+faceSize,cellSize,gap);
	drawCubeMapFace(front,0,faceLeft+faceSize,faceTop+faceSize,cellSize,gap);
	drawCubeMapFace(right,0,faceLeft+2.0f*faceSize,faceTop+faceSize,cellSize,gap);
	drawCubeMapFace(back,1,faceLeft+3.0f*faceSize,faceTop+faceSize,cellSize,gap);
	drawCubeMapFace(bottom,0,faceLeft+faceSize,faceTop+2.0f*faceSize,cellSize,gap);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	if(depthTestEnabled)
		glEnable(GL_DEPTH_TEST);
	font=previousFont;
}

static void drawChallengeUI(void)
{
	GLboolean depthTestEnabled;
	GLfloat scale;
	GLfloat left,top,buttonWidth,buttonHeight,menuTop,rowHeight,statusTop,statusHeight,lineWidth;
	GLfloat mainButtonGap,mainButtonWidth,challengeButtonLeft;
	GLfloat statusWidth;
	GLfloat controlsTop,controlsHeight,controlGap,controlWidth;
	GLfloat panelBottom,panelHeight,accentRed,accentGreen,accentBlue;
	int timerSeconds;
	int scrambleMove,hintMove,hintInverse;
	int menuVisible,statusVisible,showControls;
	const char *moveNames[7]={"","U","R","F","L","B","D"};
	char statusText[40];

	scale=challengeUIScale();
	buttonWidth=CHALLENGE_BASE_WIDTH*scale;
	mainButtonGap=6.0f*scale;
	mainButtonWidth=(buttonWidth-mainButtonGap)*0.5f;
	challengeButtonLeft=windowWidth-(CHALLENGE_BASE_WIDTH+CHALLENGE_BASE_MARGIN)*scale+
		mainButtonWidth+mainButtonGap;
	buttonHeight=CHALLENGE_BASE_HEIGHT*scale;
	left=windowWidth-(CHALLENGE_BASE_WIDTH+CHALLENGE_BASE_MARGIN)*scale;
	top=CHALLENGE_BASE_TOP*scale;
	menuTop=top+buttonHeight+2.0f*scale;
	rowHeight=CHALLENGE_BASE_MENU_ROW_HEIGHT*scale;
	menuVisible=challengeMenuVisible || practiceMenuVisible;
	statusVisible=challengeState!=CHALLENGE_IDLE || practiceActive;
	showControls=practiceActive || challengeState==CHALLENGE_RUNNING ||
		challengeState==CHALLENGE_PAUSED;
	statusTop=menuTop+(menuVisible ? 3.0f*rowHeight : 0.0f)+10.0f*scale;
	statusWidth=buttonWidth;
	statusHeight=CHALLENGE_BASE_STATUS_HEIGHT*scale;
	controlsTop=statusTop+statusHeight+6.0f*scale;
	controlsHeight=34.0f*scale;
	controlGap=4.0f*scale;
	controlWidth=(buttonWidth-2.0f*controlGap)/3.0f;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);
	glLineWidth(1.2f*scale<1.0f ? 1.0f : (1.2f*scale>4.0f ? 4.0f : 1.2f*scale));
	depthTestEnabled=glIsEnabled(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)windowWidth,(GLdouble)windowHeight,0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	panelBottom=top+buttonHeight+6.0f*scale;
	if(menuVisible)
		panelBottom=menuTop+3.0f*rowHeight+6.0f*scale;
	if(statusVisible)
		panelBottom=(showControls ? controlsTop+controlsHeight : statusTop+statusHeight)+
			6.0f*scale;
	panelHeight=panelBottom-(top-6.0f*scale);
	accentRed=0.12f;
	accentGreen=0.78f;
	accentBlue=0.88f;
	if(practiceActive || challengeState==CHALLENGE_SOLVED)
	{
		accentRed=0.24f;
		accentGreen=0.78f;
		accentBlue=0.48f;
	}
	else if(challengeState==CHALLENGE_PAUSED)
	{
		accentRed=0.92f;
		accentGreen=0.62f;
		accentBlue=0.2f;
	}
	else if(challengeState==CHALLENGE_EXPIRED || challengeState==CHALLENGE_ERROR)
	{
		accentRed=0.9f;
		accentGreen=0.25f;
		accentBlue=0.22f;
	}
	drawScreenRect(left-6.0f*scale,top-6.0f*scale,
		buttonWidth+12.0f*scale,panelHeight,0.035f,0.05f,0.08f);
	drawScreenOutline(left-6.0f*scale,top-6.0f*scale,
		buttonWidth+12.0f*scale,panelHeight,0.14f,0.21f,0.29f);
	drawScreenRect(left-6.0f*scale,top-6.0f*scale,
		buttonWidth+12.0f*scale,2.0f*scale,accentRed,accentGreen,accentBlue);

	glColor3f(0.25f,0.42f,0.32f);
	glBegin(GL_QUADS);
	glVertex2f(left,top);
	glVertex2f(left+mainButtonWidth,top);
	glVertex2f(left+mainButtonWidth,top+buttonHeight);
	glVertex2f(left,top+buttonHeight);
	glColor3f(0.16f,0.36f,0.52f);
	glVertex2f(challengeButtonLeft,top);
	glVertex2f(left+buttonWidth,top);
	glVertex2f(left+buttonWidth,top+buttonHeight);
	glVertex2f(challengeButtonLeft,top+buttonHeight);
	glEnd();
	glColor3f(0.85f,0.9f,1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(left,top);
	glVertex2f(left+mainButtonWidth,top);
	glVertex2f(left+mainButtonWidth,top+buttonHeight);
	glVertex2f(left,top+buttonHeight);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(challengeButtonLeft,top);
	glVertex2f(left+buttonWidth,top);
	glVertex2f(left+buttonWidth,top+buttonHeight);
	glVertex2f(challengeButtonLeft,top+buttonHeight);
	glEnd();
	glColor3f(1.0f,1.0f,1.0f);
	outputChallengeText(left+8.0f*scale,top+28.0f*scale,"Practice",15.0f*scale);
	outputChallengeText(challengeButtonLeft+5.0f*scale,top+28.0f*scale,"Challenge",15.0f*scale);

	if(menuVisible)
	{
		glColor3f(0.08f,0.09f,0.12f);
		glBegin(GL_QUADS);
		glVertex2f(left,menuTop);
		glVertex2f(left+buttonWidth,menuTop);
		glVertex2f(left+buttonWidth,menuTop+3.0f*rowHeight);
		glVertex2f(left,menuTop+3.0f*rowHeight);
		glEnd();

		glColor3f(0.25f,0.52f,0.32f);
		glBegin(GL_QUADS);
		glVertex2f(left+2.0f*scale,menuTop+2.0f*scale);
		glVertex2f(left+buttonWidth-2.0f*scale,menuTop+2.0f*scale);
		glVertex2f(left+buttonWidth-2.0f*scale,menuTop+rowHeight-2.0f*scale);
		glVertex2f(left+2.0f*scale,menuTop+rowHeight-2.0f*scale);
		glEnd();
		glColor3f(0.56f,0.43f,0.2f);
		glBegin(GL_QUADS);
		glVertex2f(left+2.0f*scale,menuTop+rowHeight+2.0f*scale);
		glVertex2f(left+buttonWidth-2.0f*scale,menuTop+rowHeight+2.0f*scale);
		glVertex2f(left+buttonWidth-2.0f*scale,menuTop+2.0f*rowHeight-2.0f*scale);
		glVertex2f(left+2.0f*scale,menuTop+2.0f*rowHeight-2.0f*scale);
		glEnd();
		glColor3f(0.58f,0.24f,0.2f);
		glBegin(GL_QUADS);
		glVertex2f(left+2.0f*scale,menuTop+2.0f*rowHeight+2.0f*scale);
		glVertex2f(left+buttonWidth-2.0f*scale,menuTop+2.0f*rowHeight+2.0f*scale);
		glVertex2f(left+buttonWidth-2.0f*scale,menuTop+3.0f*rowHeight-2.0f*scale);
		glVertex2f(left+2.0f*scale,menuTop+3.0f*rowHeight-2.0f*scale);
		glEnd();
		glColor3f(1.0f,1.0f,1.0f);
		if(practiceMenuVisible)
		{
			outputChallengeText(left+12.0f*scale,menuTop+26.0f*scale,"Easy - 10 moves",18.0f*scale);
			outputChallengeText(left+12.0f*scale,menuTop+rowHeight+26.0f*scale,"Medium - 20 moves",18.0f*scale);
			outputChallengeText(left+12.0f*scale,menuTop+2.0f*rowHeight+26.0f*scale,"Hard - 30 moves",18.0f*scale);
		}
		else
		{
			outputChallengeText(left+12.0f*scale,menuTop+26.0f*scale,"Easy - 1 min",18.0f*scale);
			outputChallengeText(left+12.0f*scale,menuTop+rowHeight+26.0f*scale,"Medium - 3 min",18.0f*scale);
			outputChallengeText(left+12.0f*scale,menuTop+2.0f*rowHeight+26.0f*scale,"Hard - 5 min",18.0f*scale);
		}
	}

	if(statusVisible)
	{
		if(practiceActive)
		{
			if(practiceMoveIndex>=practiceMoveCount)
				snprintf(statusText,sizeof(statusText),"Practice complete");
			else
			{
				scrambleMove=practiceMoves[practiceMoveCount-1-practiceMoveIndex];
				hintMove=scrambleMove<0 ? -scrambleMove : scrambleMove;
				hintInverse=scrambleMove>0;
				snprintf(statusText,sizeof(statusText),"%s %d/%d: %s%s",
					practiceAutoPlaying ? "Playing" :
					(practiceMovePending ? "Step" : "Next"),
					practiceMoveIndex+1,practiceMoveCount,moveNames[hintMove],
					hintInverse ? "'" : "");
			}
		}
		else if(challengeState==CHALLENGE_COUNTDOWN)
			snprintf(statusText,sizeof(statusText),"Starting in %d",challengeCountdown);
		else if(challengeState==CHALLENGE_RUNNING && challengeGoVisible)
			snprintf(statusText,sizeof(statusText),"GO!");
		else if(challengeState==CHALLENGE_RUNNING)
		{
			timerSeconds=(challengeRemainingMilliseconds+999)/1000;
			snprintf(statusText,sizeof(statusText),"Time left %d:%02d",
				timerSeconds/60,timerSeconds%60);
		}
		else if(challengeState==CHALLENGE_PAUSED)
		{
			timerSeconds=(challengeRemainingMilliseconds+999)/1000;
			snprintf(statusText,sizeof(statusText),"Paused %d:%02d",
				timerSeconds/60,timerSeconds%60);
		}
		else if(challengeState==CHALLENGE_SOLVED)
		{
			timerSeconds=challengeElapsedMilliseconds/1000;
			snprintf(statusText,sizeof(statusText),"Solved in %d:%02d",
				timerSeconds/60,timerSeconds%60);
		}
		else if(challengeState==CHALLENGE_EXPIRED)
			snprintf(statusText,sizeof(statusText),"Time's up!");
		else if(challengeState==CHALLENGE_STOPPED)
			snprintf(statusText,sizeof(statusText),"Challenge stopped");
		else
			snprintf(statusText,sizeof(statusText),"History is full");

		drawScreenRect(left,statusTop,statusWidth,statusHeight,
			0.055f,0.075f,0.11f);
		drawScreenRect(left,statusTop,4.0f*scale,statusHeight,
			accentRed,accentGreen,accentBlue);
		glColor3f(1.0f,1.0f,1.0f);
		outputChallengeText(left+12.0f*scale,statusTop+34.0f*scale,statusText,18.0f*scale);
		if(practiceActive)
		{
			glColor3f(rotationcomplete && !practiceAutoPlaying &&
				practiceMoveIndex<practiceMoveCount ? 0.16f : 0.24f,0.36f,0.42f);
			glBegin(GL_QUADS);
			glVertex2f(left,controlsTop);
			glVertex2f(left+controlWidth,controlsTop);
			glVertex2f(left+controlWidth,controlsTop+controlsHeight);
			glVertex2f(left,controlsTop+controlsHeight);
			glEnd();

			glColor3f(0.16f,practiceAutoPlaying ? 0.48f : 0.3f,0.42f);
			glBegin(GL_QUADS);
			glVertex2f(left+controlWidth+controlGap,controlsTop);
			glVertex2f(left+2.0f*controlWidth+controlGap,controlsTop);
			glVertex2f(left+2.0f*controlWidth+controlGap,controlsTop+controlsHeight);
			glVertex2f(left+controlWidth+controlGap,controlsTop+controlsHeight);
			glEnd();

			glColor3f(0.55f,0.2f,0.18f);
			glBegin(GL_QUADS);
			glVertex2f(left+2.0f*(controlWidth+controlGap),controlsTop);
			glVertex2f(left+3.0f*controlWidth+2.0f*controlGap,controlsTop);
			glVertex2f(left+3.0f*controlWidth+2.0f*controlGap,controlsTop+controlsHeight);
			glVertex2f(left+2.0f*(controlWidth+controlGap),controlsTop+controlsHeight);
			glEnd();

			glColor3f(1.0f,1.0f,1.0f);
			outputChallengeText(left+8.0f*scale,controlsTop+23.0f*scale,"Step",13.0f*scale);
			outputChallengeText(left+controlWidth+controlGap+8.0f*scale,
				controlsTop+23.0f*scale,practiceAutoPlaying ? "Pause" : "Play",13.0f*scale);
			outputChallengeText(left+2.0f*(controlWidth+controlGap)+8.0f*scale,
				controlsTop+23.0f*scale,"Exit",13.0f*scale);
		}
		else if(challengeState==CHALLENGE_RUNNING || challengeState==CHALLENGE_PAUSED)
		{
			glColor3f(challengeState==CHALLENGE_RUNNING && rotationcomplete==1 ? 0.16f : 0.24f,
				challengeState==CHALLENGE_RUNNING && rotationcomplete==1 ? 0.36f : 0.25f,0.42f);
			glBegin(GL_QUADS);
			glVertex2f(left,controlsTop);
			glVertex2f(left+controlWidth,controlsTop);
			glVertex2f(left+controlWidth,controlsTop+controlsHeight);
			glVertex2f(left,controlsTop+controlsHeight);
			glEnd();

			glColor3f(challengeState==CHALLENGE_PAUSED ? 0.2f : 0.24f,
				challengeState==CHALLENGE_PAUSED ? 0.48f : 0.25f,
				challengeState==CHALLENGE_PAUSED ? 0.28f : 0.28f);
			glBegin(GL_QUADS);
			glVertex2f(left+controlWidth+controlGap,controlsTop);
			glVertex2f(left+2.0f*controlWidth+controlGap,controlsTop);
			glVertex2f(left+2.0f*controlWidth+controlGap,controlsTop+controlsHeight);
			glVertex2f(left+controlWidth+controlGap,controlsTop+controlsHeight);
			glEnd();

			glColor3f(0.55f,0.2f,0.18f);
			glBegin(GL_QUADS);
			glVertex2f(left+2.0f*(controlWidth+controlGap),controlsTop);
			glVertex2f(left+3.0f*controlWidth+2.0f*controlGap,controlsTop);
			glVertex2f(left+3.0f*controlWidth+2.0f*controlGap,controlsTop+controlsHeight);
			glVertex2f(left+2.0f*(controlWidth+controlGap),controlsTop+controlsHeight);
			glEnd();

			glColor3f(1.0f,1.0f,1.0f);
			outputChallengeText(left+7.0f*scale,controlsTop+23.0f*scale,"Pause",13.0f*scale);
			outputChallengeText(left+controlWidth+controlGap+3.0f*scale,
				controlsTop+23.0f*scale,"Resume",13.0f*scale);
			outputChallengeText(left+2.0f*(controlWidth+controlGap)+15.0f*scale,
				controlsTop+23.0f*scale,"Stop",13.0f*scale);
		}
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	if(depthTestEnabled)
		glEnable(GL_DEPTH_TEST);
	glLineWidth(lineWidth);
}

void display() 
{ 
	GLfloat lightPosition[4]={-0.45f,0.75f,1.0f,0.0f};
	GLfloat lightAmbient[4]={0.18f,0.18f,0.18f,1.0f};
	GLfloat lightDiffuse[4]={0.9f,0.9f,0.9f,1.0f};
	GLfloat lightSpecular[4]={0.55f,0.55f,0.55f,1.0f};
	GLfloat materialSpecular[4]={0.24f,0.24f,0.24f,1.0f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	 
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpecular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lightAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,materialSpecular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,36.0f);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	cubeRendering=1;
	 
	glPushMatrix(); 
	glRotatef(25.0+p,1.0,0.0,0.0); 
	glRotatef(-30.0+q,0.0,1.0,0.0); 
	glRotatef(0.0+r,0.0,0.0,1.0);  
	 
	if(rotation==0) 
	{  
		colorcube1(); 
		colorcube2(); 
		colorcube3(); 
		colorcube4(); 
		colorcube5(); 
		colorcube6(); 
		colorcube7(); 
		colorcube8();  
		colorcube9(); 
		colorcube10(); 
		colorcube11(); 
		colorcube12(); 
		colorcube13(); 
		colorcube14(); 
		colorcube15(); 
		colorcube16(); 
		colorcube17(); 
		colorcube18(); 
		colorcube19(); 
		colorcube20(); 
		colorcube21(); 
		colorcube22(); 
		colorcube23(); 
		colorcube24(); 
		colorcube25(); 
		colorcube26(); 
		colorcube27(); 
	} 
	if(rotation==1) 
	{ 
		colorcube1(); 
		colorcube2(); 
		colorcube3(); 
		colorcube4(); 
		colorcube6(); 
		colorcube7(); 
		colorcube12(); 
		colorcube13(); 
		colorcube14(); 
		colorcube15(); 
		colorcube20(); 
		colorcube21(); 
		colorcube22(); 
		colorcube23(); 
		colorcube24(); 
		colorcube25(); 
		colorcube26(); 
		colorcube27(); 
		if(inverse==0) 
		{
			glRotatef(-theta,0.0,1.0,0.0); 
		} 
		else 
		{
			glRotatef(theta,0.0,1.0,0.0); 
		} 
		colorcube5(); 
		colorcube8();  
		colorcube9(); 
		colorcube10(); 
		colorcube11(); 
		colorcube16(); 
		colorcube17(); 
		colorcube18(); 
		colorcube19(); 
	} 
	if(rotation==2) 
	{  
		colorcube1(); 
		colorcube2(); 
		colorcube3(); 
		colorcube5(); 
		colorcube6(); 
		colorcube7(); 
		colorcube8();  
		colorcube10(); 
		colorcube11(); 
		colorcube12(); 
		colorcube14(); 
		colorcube15(); 
		colorcube16(); 
		colorcube17(); 
		colorcube20(); 
		colorcube21(); 
		colorcube24(); 
		colorcube25(); 
		if(inverse==0) 
		{ 
			glRotatef(-theta,1.0,0.0,0.0); 
		} 
		else 
		{ 
			glRotatef(theta,1.0,0.0,0.0); 
		} 
		colorcube4(); 
		colorcube9(); 
		colorcube13(); 
		colorcube18(); 
		colorcube19(); 
		colorcube22(); 
		colorcube23(); 
		colorcube26(); 
		colorcube27(); 
	} 
	if(rotation==3) 
	{ 
		colorcube1(); 
		colorcube2(); 
		colorcube3(); 
		colorcube4(); 
		colorcube5(); 
		colorcube7(); 
		colorcube8();  
		colorcube9(); 
		colorcube11(); 
		colorcube12(); 
		colorcube13(); 
		colorcube15(); 
		colorcube16(); 
		colorcube18(); 
		colorcube20(); 
		colorcube22(); 
		colorcube24(); 
		colorcube26(); 
		if(inverse==0) 
		{ 
			glRotatef(-theta,0.0,0.0,1.0); 
		} 
		else 
		{ 
			glRotatef(theta,0.0,0.0,1.0); 
		} 
		colorcube6(); 
		colorcube10(); 
		colorcube14(); 
		colorcube17(); 
		colorcube19(); 
		colorcube21(); 
		colorcube23(); 
		colorcube25(); 
		colorcube27(); 
	} 
	if(rotation==4) 
	{  
		colorcube1(); 
		colorcube2(); 
		colorcube4(); 
		colorcube5(); 
		colorcube6(); 
		colorcube7(); 
		colorcube9(); 
		colorcube10(); 
		colorcube11(); 
		colorcube13(); 
		colorcube14(); 
		colorcube15(); 
		colorcube18(); 
		colorcube19(); 
		colorcube22(); 
		colorcube23(); 
		colorcube26(); 
		colorcube27(); 
		if(inverse==0) 
		{
			glRotatef(theta,1.0,0.0,0.0); 
		} 
		else 
		{
			glRotatef(-theta,1.0,0.0,0.0); 
		} 
		colorcube3(); 
		colorcube8();  
		colorcube12(); 
		colorcube16(); 
		colorcube17(); 
		colorcube20(); 
		colorcube21(); 
		colorcube24(); 
		colorcube25(); 
	} 
	if(rotation==5) 
	{  
		colorcube1(); 
		colorcube2(); 
		colorcube3(); 
		colorcube4(); 
		colorcube5(); 
		colorcube6(); 
		colorcube8();  
		colorcube9(); 
		colorcube10(); 
		colorcube12(); 
		colorcube13(); 
		colorcube14(); 
		colorcube17(); 
		colorcube19(); 
		colorcube21(); 
		colorcube23(); 
		colorcube25(); 
		colorcube27(); 
		if(inverse==0) 
		{
			glRotatef(theta,0.0,0.0,1.0); 
		} 
		else 
		{ 
			glRotatef(-theta,0.0,0.0,1.0); 
		} 
		colorcube7(); 
		colorcube11(); 
		colorcube15(); 
		colorcube16(); 
		colorcube18(); 
		colorcube20(); 
		colorcube22(); 
		colorcube24(); 
		colorcube26(); 
	} 
	if(rotation==6) 
	{  
		colorcube1(); 
		colorcube3(); 
		colorcube4(); 
		colorcube5(); 
		colorcube6(); 
		colorcube7(); 
		colorcube8();  
		colorcube9(); 
		colorcube10(); 
		colorcube11(); 
		colorcube16(); 
		colorcube17(); 
		colorcube18(); 
		colorcube19(); 
		colorcube20(); 
		colorcube21(); 
		colorcube22(); 
		colorcube23(); 
		if(inverse==0) 
		{
			glRotatef(theta,0.0,1.0,0.0); 
		} 
		else 
		{
			glRotatef(-theta,0.0,1.0,0.0); 
		} 
		colorcube2(); 
		colorcube12(); 
		colorcube13(); 
		colorcube14(); 
		colorcube15(); 
		colorcube24(); 
		colorcube25(); 
		colorcube26(); 
		colorcube27(); 
	}
	 
	glPopMatrix(); 
	cubeRendering=0;
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	drawGameHUD();
	drawCubeMap();
	drawControlsPanel();
	drawChallengeUI();
	glFlush(); 
	glutSwapBuffers(); 
} 


void transpose(char a) 
{  
	if(a=='r') 
	{ 
		int temp; 
		temp=right[0][0]; 
		right[0][0]=right[2][0]; 
		right[2][0]=right[2][2]; 
		right[2][2]=right[0][2]; 
		right[0][2]=temp; 
		temp=right[1][0]; 
		right[1][0]=right[2][1]; 
		right[2][1]=right[1][2]; 
		right[1][2]=right[0][1]; 
		right[0][1]=temp; 
	} 
	if(a=='t') 
	{ 
		int temp; 
		temp=top[0][0]; 
		top[0][0]=top[2][0]; 
		top[2][0]=top[2][2]; 
		top[2][2]=top[0][2]; 
		top[0][2]=temp; 
		temp=top[1][0]; 
		top[1][0]=top[2][1]; 
		top[2][1]=top[1][2]; 
		top[1][2]=top[0][1]; 
		top[0][1]=temp; 
	} 
	if(a=='f') 
	{ 
		int temp; 
		temp=front[0][0]; 
		front[0][0]=front[2][0]; 
		front[2][0]=front[2][2]; 
		front[2][2]=front[0][2]; 
		front[0][2]=temp; 
		temp=front[1][0]; 
		front[1][0]=front[2][1]; 
		front[2][1]=front[1][2]; 
		front[1][2]=front[0][1]; 
		front[0][1]=temp; 
	} 
	if(a=='l') 
	{ 
		int temp; 
		temp=left[0][0]; 
		left[0][0]=left[2][0]; 
		left[2][0]=left[2][2]; 
		left[2][2]=left[0][2]; 
		left[0][2]=temp; 
		temp=left[1][0]; 
		left[1][0]=left[2][1]; 
		left[2][1]=left[1][2]; 
		left[1][2]=left[0][1]; 
		left[0][1]=temp; 
	} 
	if(a=='k') 
	{ 
		int temp; 
		temp=back[0][0]; 
		back[0][0]=back[2][0]; 
		back[2][0]=back[2][2]; 
		back[2][2]=back[0][2]; 
		back[0][2]=temp; 
		temp=back[1][0]; 
		back[1][0]=back[2][1]; 
		back[2][1]=back[1][2]; 
		back[1][2]=back[0][1]; 
		back[0][1]=temp; 
	} 
	if(a=='b') 
	{ 
		int temp; 
		temp=bottom[0][0]; 
		bottom[0][0]=bottom[2][0]; 
		bottom[2][0]=bottom[2][2]; 
		bottom[2][2]=bottom[0][2]; 
		bottom[0][2]=temp; 
		temp=bottom[1][0]; 
		bottom[1][0]=bottom[2][1]; 
		bottom[2][1]=bottom[1][2]; 
		bottom[1][2]=bottom[0][1]; 
		bottom[0][1]=temp; 
	} 
} 
 
  
void topc() 
{ 
	transpose('t'); 
	int temp1=front[0][0]; 
	int temp2=front[0][1]; 
	int temp3=front[0][2]; 

	front[0][0]=right[0][0]; 
	front[0][1]=right[0][1]; 
	front[0][2]=right[0][2]; 
	 
	right[0][0]=back[0][0]; 
	right[0][1]=back[0][1]; 
	right[0][2]=back[0][2]; 
	 
	back[0][0]=left[0][0]; 
	back[0][1]=left[0][1]; 
	back[0][2]=left[0][2]; 
	 
	left[0][0]=temp1; 
	left[0][1]=temp2; 
	left[0][2]=temp3; 
} 
 
void frontc() 
{ 
	transpose('f'); 
	int temp1=left[0][2]; 
	int temp2=left[1][2]; 
	int temp3=left[2][2]; 
	 
	left[0][2]=bottom[0][0]; 
	left[1][2]=bottom[0][1]; 
	left[2][2]=bottom[0][2]; 
	 
	bottom[0][0]=right[2][0]; 
	bottom[0][1]=right[1][0]; 
	bottom[0][2]=right[0][0]; 
	 
	right[2][0]=top[2][2]; 
	right[1][0]=top[2][1]; 
	right[0][0]=top[2][0]; 
	 
	top[2][2]=temp1; 
	top[2][1]=temp2; 
	top[2][0]=temp3; 
} 
 
void rightc() 
{ 
	transpose('r'); 
	int temp1=top[0][2]; 
	int temp2=top[1][2]; 
	int temp3=top[2][2]; 
	 
	top[0][2]=front[0][2]; 
	top[1][2]=front[1][2]; 
	top[2][2]=front[2][2]; 
	 
	front[0][2]=bottom[0][2]; 
	front[1][2]=bottom[1][2]; 
	front[2][2]=bottom[2][2]; 
	 
	bottom[0][2]=back[2][0]; 
	bottom[1][2]=back[1][0]; 
	bottom[2][2]=back[0][0]; 
	 
	back[2][0]=temp1; 
	back[1][0]=temp2; 
	back[0][0]=temp3; 
} 
 
void leftc() 
{ 
	transpose('l'); 
	int temp1=front[0][0]; 
	int temp2=front[1][0]; 
	int temp3=front[2][0]; 
	 
	front[0][0]=top[0][0]; 
	front[1][0]=top[1][0]; 
	front[2][0]=top[2][0]; 

	top[0][0]=back[2][2]; 
	top[1][0]=back[1][2]; 
	top[2][0]=back[0][2]; 
	 
	back[2][2]=bottom[0][0]; 
	back[1][2]=bottom[1][0]; 
	back[0][2]=bottom[2][0]; 

	bottom[0][0]=temp1; 
	bottom[1][0]=temp2; 
	bottom[2][0]=temp3;  
} 
 
void backc() 
{ 
	transpose('k'); 
	int temp1=top[0][0]; 
	int temp2=top[0][1]; 
	int temp3=top[0][2]; 
	 
	top[0][0]=right[0][2]; 
	top[0][1]=right[1][2]; 
	top[0][2]=right[2][2]; 
	 
	right[0][2]=bottom[2][2]; 
	right[1][2]=bottom[2][1]; 
	right[2][2]=bottom[2][0]; 

	bottom[2][2]=left[2][0]; 
	bottom[2][1]=left[1][0]; 
	bottom[2][0]=left[0][0]; 

	left[2][0]=temp1; 
	left[1][0]=temp2; 
	left[0][0]=temp3; 
} 
 
void bottomc() 
{ 
	transpose('b'); 
	int temp1=front[2][0]; 
	int temp2=front[2][1]; 
	int temp3=front[2][2]; 

	front[2][0]=left[2][0]; 
	front[2][1]=left[2][1]; 
	front[2][2]=left[2][2]; 

	left[2][0]=back[2][0]; 
	left[2][1]=back[2][1]; 
	left[2][2]=back[2][2]; 

	back[2][0]=right[2][0]; 
	back[2][1]=right[2][1]; 
	back[2][2]=right[2][2]; 

	right[2][0]=temp1; 
	right[2][1]=temp2; 
	right[2][2]=temp3; 
} 
 
 
void spincube(void);
static int startPracticeReverseMove(void);

static int beginCubeMove(int move,int moveInverse,int practiceMove)
{
	if(rotationcomplete!=1 || (practiceMove && !practiceActive))
		return 0;

	if(practiceActive && !practiceMove)
	{
		practiceActive=0;
		practiceAutoPlaying=0;
	}

	if(count<0 || count+1>=(int)(sizeof(solve)/sizeof(solve[0])))
	{
		statusMessage=historyFullMessage;
		glutPostRedisplay();
		return 0;
	}

	rotationcomplete=0;
	rotation=move;
	inverse=moveInverse;
	solve[++count]=moveInverse ? -move : move;
	statusMessage=NULL;
	glutIdleFunc(spincube);
	return 1;
}

static void startCubeMove(int move,int moveInverse)
{
	beginCubeMove(move,moveInverse,0);
}

static void undoLastCubeMove(void)
{
	int previousMove;

	if(rotationcomplete!=1 || count<=0)
		return;

	practiceActive=0;
	practiceAutoPlaying=0;
	previousMove=solve[count--];
	rotation=previousMove<0 ? -previousMove : previousMove;
	inverse=previousMove>0;
	rotationcomplete=0;
	statusMessage=NULL;
	glutIdleFunc(spincube);
}

static int cubeIsSolved(void)
{
	int row,column;

	for(row=0;row<3;row++)
		for(column=0;column<3;column++)
			if(top[row][column]!=top[1][1] ||
			   right[row][column]!=right[1][1] ||
			   front[row][column]!=front[1][1] ||
			   back[row][column]!=back[1][1] ||
			   bottom[row][column]!=bottom[1][1] ||
			   left[row][column]!=left[1][1])
				return 0;
	return 1;
}

static void applyCubeMove(int move,int moveInverse)
{
	int turns=moveInverse ? 3 : 1;
	int i;

	for(i=0;i<turns;i++)
	{
		switch(move)
		{
			case 1: topc(); break;
			case 2: rightc(); break;
			case 3: frontc(); break;
			case 4: leftc(); break;
			case 5: backc(); break;
			case 6: bottomc(); break;
		}
	}
}

static void scrambleCube(int moveCount,int *moveHistory)
{
	int face;
	int lastFace=-1;
	int move;
	int moveInverse;
	int signedMove;
	int i;

	for(i=0;i<moveCount;i++)
	{
		face=rand()%6;
		while(face==lastFace)
			face=rand()%6;
		lastFace=face;
		move=face+1;
		moveInverse=rand()%2;
		signedMove=moveInverse ? -move : move;
		solve[++count]=signedMove;
		if(moveHistory!=NULL)
			moveHistory[i]=signedMove;
		applyCubeMove(move,moveInverse);
	}
}

static int startPracticeReverseMove(void)
{
	int scrambleMove;
	int move;
	int moveInverse;

	if(!practiceActive || !rotationcomplete || practiceMovePending ||
	   practiceMoveIndex>=practiceMoveCount)
		return 0;

	scrambleMove=practiceMoves[practiceMoveCount-1-practiceMoveIndex];
	move=scrambleMove<0 ? -scrambleMove : scrambleMove;
	moveInverse=scrambleMove>0;
	if(!beginCubeMove(move,moveInverse,1))
		return 0;

	practiceMovePending=1;
	return 1;
}

static void startPractice(int moveCount)
{
	if(rotationcomplete!=1)
		return;

	practiceActive=0;
	practiceAutoPlaying=0;
	practiceMovePending=0;
	challengeGeneration++;
	challengeState=CHALLENGE_IDLE;
	challengeGoVisible=0;
	if(count<0 || count+2*moveCount>=(int)(sizeof(solve)/sizeof(solve[0])))
	{
		challengeState=CHALLENGE_ERROR;
		glutPostRedisplay();
		return;
	}

	scrambleCube(moveCount,practiceMoves);
	practiceMoveCount=moveCount;
	practiceMoveIndex=0;
	practiceActive=1;
	rotation=0;
	theta=0.0f;
	statusMessage=NULL;
	glutIdleFunc(NULL);
	glutPostRedisplay();
}

static void challengeTimerTick(int generation);

static void startChallenge(int moveCount,int durationSeconds)
{
	if(rotationcomplete!=1)
		return;

	practiceActive=0;
	practiceAutoPlaying=0;
	practiceMovePending=0;
	if(count<0 || count+moveCount>=(int)(sizeof(solve)/sizeof(solve[0])))
	{
		challengeState=CHALLENGE_ERROR;
		challengeGeneration++;
		glutPostRedisplay();
		return;
	}

	scrambleCube(moveCount,NULL);

	rotation=0;
	theta=0.0f;
	challengeDurationMilliseconds=durationSeconds*1000;
	challengeRemainingMilliseconds=challengeDurationMilliseconds;
	challengeElapsedMilliseconds=0;
	challengeCountdown=3;
	challengeGoVisible=0;
	challengeState=CHALLENGE_COUNTDOWN;
	rotationcomplete=0;
	glutIdleFunc(NULL);
	challengeGeneration++;
	glutTimerFunc(1000,challengeTimerTick,challengeGeneration);
	glutPostRedisplay();
}

void spincube(void) 
{
	theta+=CUBE_TURN_SPEED;
	if(theta==360.0) 
		theta-=360.0; 
	if(theta>=90.0) 
	{ 
		applyCubeMove(rotation,inverse);
		rotation=0; 
		theta=0;
		rotationcomplete=(challengeState==CHALLENGE_PAUSED) ? 0 : 1;
		glutIdleFunc(NULL);
		if(challengeState==CHALLENGE_RUNNING && cubeIsSolved())
		{
			int elapsed=glutGet(GLUT_ELAPSED_TIME)-challengeStartTime;
			challengeElapsedMilliseconds+=elapsed;
			challengeRemainingMilliseconds=challengeDurationMilliseconds-elapsed;
			if(challengeRemainingMilliseconds<0)
				challengeRemainingMilliseconds=0;
			challengeState=CHALLENGE_SOLVED;
			challengeGeneration++;
		}
		if(practiceMovePending)
		{
			practiceMovePending=0;
			practiceMoveIndex++;
			if(practiceActive && practiceAutoPlaying &&
			   practiceMoveIndex<practiceMoveCount)
			{
				if(!startPracticeReverseMove())
					practiceAutoPlaying=0;
			}
			else if(practiceMoveIndex>=practiceMoveCount)
				practiceAutoPlaying=0;
		}
	}  
	glutPostRedisplay(); 
} 
 
static void challengeTimerTick(int generation)
{
	int elapsed;
	int now;

	if(generation!=challengeGeneration)
		return;

	if(challengeState==CHALLENGE_COUNTDOWN)
	{
		if(challengeCountdown>1)
			challengeCountdown--;
		else
		{
			challengeCountdown=0;
			challengeState=CHALLENGE_RUNNING;
			challengeGoVisible=1;
			challengeStartTime=glutGet(GLUT_ELAPSED_TIME);
			challengeRemainingMilliseconds=challengeDurationMilliseconds;
			rotationcomplete=1;
		}
		glutPostRedisplay();
		glutTimerFunc(1000,challengeTimerTick,generation);
		return;
	}

	if(challengeState!=CHALLENGE_RUNNING)
		return;

	challengeGoVisible=0;
	now=glutGet(GLUT_ELAPSED_TIME);
	elapsed=now-challengeStartTime;
	if(cubeIsSolved())
	{
		challengeElapsedMilliseconds+=elapsed;
		challengeRemainingMilliseconds=challengeDurationMilliseconds-elapsed;
		if(challengeRemainingMilliseconds<0)
			challengeRemainingMilliseconds=0;
		challengeState=CHALLENGE_SOLVED;
		challengeGeneration++;
	}
	else
	{
		challengeRemainingMilliseconds=challengeDurationMilliseconds-elapsed;
		if(challengeRemainingMilliseconds<=0)
		{
			challengeRemainingMilliseconds=0;
			challengeElapsedMilliseconds+=challengeDurationMilliseconds;
			challengeState=CHALLENGE_EXPIRED;
			challengeGeneration++;
		}
		else
			glutTimerFunc(250,challengeTimerTick,generation);
	}
	glutPostRedisplay();
}

static void pauseChallenge(void)
{
	int elapsed;

	if(challengeState!=CHALLENGE_RUNNING || rotationcomplete!=1)
		return;

	elapsed=glutGet(GLUT_ELAPSED_TIME)-challengeStartTime;
	challengeElapsedMilliseconds+=elapsed;
	challengeRemainingMilliseconds=challengeDurationMilliseconds-elapsed;
	if(challengeRemainingMilliseconds<=0)
	{
		challengeRemainingMilliseconds=0;
		challengeState=CHALLENGE_EXPIRED;
		challengeGeneration++;
		glutPostRedisplay();
		return;
	}
	else
		challengeState=CHALLENGE_PAUSED;

	challengeGeneration++;
	challengeGoVisible=0;
	rotationcomplete=0;
	glutIdleFunc(NULL);
	glutPostRedisplay();
}

static void resumeChallenge(void)
{
	if(challengeState!=CHALLENGE_PAUSED)
		return;

	challengeDurationMilliseconds=challengeRemainingMilliseconds;
	challengeStartTime=glutGet(GLUT_ELAPSED_TIME);
	challengeState=CHALLENGE_RUNNING;
	challengeGeneration++;
	rotationcomplete=1;
	glutTimerFunc(250,challengeTimerTick,challengeGeneration);
	glutPostRedisplay();
}

static void stopChallenge(void)
{
	int elapsed;

	if(challengeState!=CHALLENGE_RUNNING && challengeState!=CHALLENGE_PAUSED)
		return;

	if(challengeState==CHALLENGE_RUNNING)
	{
		elapsed=glutGet(GLUT_ELAPSED_TIME)-challengeStartTime;
		challengeElapsedMilliseconds+=elapsed;
		challengeRemainingMilliseconds=challengeDurationMilliseconds-elapsed;
		if(challengeRemainingMilliseconds<0)
			challengeRemainingMilliseconds=0;
	}

	challengeState=CHALLENGE_STOPPED;
	challengeGeneration++;
	if(rotationcomplete==1)
		glutIdleFunc(NULL);
	else if(rotation==0 && theta==0.0f)
		rotationcomplete=1;
	glutPostRedisplay();
}

 
void motion(int x, int y) 
{
	if(moving)
	{ 
		q=q + (x - beginx); 
		beginx = x; 
		p=p + (y - beginy); 
		beginy=y; 
		glutPostRedisplay(); 
	} 
} 
 
void mymenu(int id);
 
void mouse(int btn,int state,int x,int y) 
{ 
	int row;
	int selectingPractice;
	GLfloat scale;
	GLfloat challengeLeft;
	GLfloat challengeTop;
	GLfloat challengeWidth;
	GLfloat challengeHeight;
	GLfloat practiceButtonWidth;
	GLfloat challengeButtonLeft;
	GLfloat challengeMenuTop;
	GLfloat challengeRowHeight;
	GLfloat challengeStatusTop;
	GLfloat challengeStatusHeight;
	GLfloat challengeControlsTop;
	GLfloat challengeControlsHeight;
	GLfloat challengeControlGap;
	GLfloat challengeControlWidth;

	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		controlsVisible=!controlsVisible;
		challengeMenuVisible=0;
		practiceMenuVisible=0;
		moving=0;
		glutPostRedisplay();
		return;
	}

	if(btn!=GLUT_LEFT_BUTTON)
		return;

	if(state==GLUT_UP)
	{
		moving=0;
		return;
	}

	if(state!=GLUT_DOWN)
		return;

	scale=challengeUIScale();
	challengeWidth=CHALLENGE_BASE_WIDTH*scale;
	challengeHeight=CHALLENGE_BASE_HEIGHT*scale;
	challengeLeft=windowWidth-(CHALLENGE_BASE_WIDTH+CHALLENGE_BASE_MARGIN)*scale;
	practiceButtonWidth=(challengeWidth-6.0f*scale)*0.5f;
	challengeButtonLeft=challengeLeft+practiceButtonWidth+6.0f*scale;
	challengeTop=CHALLENGE_BASE_TOP*scale;
	challengeMenuTop=challengeTop+challengeHeight+2.0f*scale;
	challengeRowHeight=CHALLENGE_BASE_MENU_ROW_HEIGHT*scale;
	challengeStatusTop=challengeMenuTop+
		((challengeMenuVisible || practiceMenuVisible) ?
			3.0f*challengeRowHeight : 0.0f)+10.0f*scale;
	challengeStatusHeight=CHALLENGE_BASE_STATUS_HEIGHT*scale;
	challengeControlsTop=challengeStatusTop+challengeStatusHeight+6.0f*scale;
	challengeControlsHeight=34.0f*scale;
	challengeControlGap=4.0f*scale;
	challengeControlWidth=(challengeWidth-2.0f*challengeControlGap)/3.0f;
	if(x>=challengeLeft && x<challengeLeft+challengeWidth &&
	   y>=challengeTop && y<challengeTop+challengeHeight)
	{
		if(x<challengeLeft+practiceButtonWidth)
		{
			practiceMenuVisible=!practiceMenuVisible;
			challengeMenuVisible=0;
		}
		else if(x>=challengeButtonLeft)
		{
			challengeMenuVisible=!challengeMenuVisible;
			practiceMenuVisible=0;
		}
		moving=0;
		glutPostRedisplay();
		return;
	}

	if(challengeMenuVisible || practiceMenuVisible)
	{
		if(x>=challengeLeft && x<challengeLeft+challengeWidth &&
		   y>=challengeMenuTop && y<challengeMenuTop+3.0f*challengeRowHeight)
		{
			row=(int)((y-challengeMenuTop)/challengeRowHeight);
			selectingPractice=practiceMenuVisible;
			challengeMenuVisible=0;
			practiceMenuVisible=0;
			if(rotationcomplete==1)
			{
				if(selectingPractice)
				{
					if(row==0)
						startPractice(10);
					else if(row==1)
						startPractice(20);
					else
						startPractice(30);
				}
				else if(row==0)
					startChallenge(10,60);
				else if(row==1)
					startChallenge(20,180);
				else
					startChallenge(30,300);
			}
			glutPostRedisplay();
			return;
		}
		challengeMenuVisible=0;
		practiceMenuVisible=0;
	}

	if(practiceActive &&
	   x>=challengeLeft && x<challengeLeft+challengeWidth &&
	   y>=challengeControlsTop && y<challengeControlsTop+challengeControlsHeight)
	{
		if(x-challengeLeft<challengeControlWidth)
		{
			if(rotationcomplete==1 && !practiceAutoPlaying &&
			   practiceMoveIndex<practiceMoveCount)
				startPracticeReverseMove();
		}
		else if(x-challengeLeft>=challengeControlWidth+challengeControlGap &&
		        x-challengeLeft<2.0f*challengeControlWidth+challengeControlGap)
		{
			if(practiceAutoPlaying)
				practiceAutoPlaying=0;
			else if(practiceMoveIndex<practiceMoveCount)
			{
				practiceAutoPlaying=1;
				if(rotationcomplete==1 && !startPracticeReverseMove())
					practiceAutoPlaying=0;
			}
		}
		else if(x-challengeLeft>=2.0f*(challengeControlWidth+challengeControlGap))
		{
			practiceActive=0;
			practiceAutoPlaying=0;
		}
		glutPostRedisplay();
		return;
	}

	if((challengeState==CHALLENGE_RUNNING || challengeState==CHALLENGE_PAUSED) &&
	   x>=challengeLeft && x<challengeLeft+challengeWidth &&
	   y>=challengeControlsTop && y<challengeControlsTop+challengeControlsHeight)
	{
		if(x-challengeLeft<challengeControlWidth)
			pauseChallenge();
		else if(x-challengeLeft>=challengeControlWidth+challengeControlGap &&
		        x-challengeLeft<2.0f*challengeControlWidth+challengeControlGap)
			resumeChallenge();
		else if(x-challengeLeft>=2.0f*(challengeControlWidth+challengeControlGap))
			stopChallenge();
		glutPostRedisplay();
		return;
	}

	if(controlsVisible)
	{
		if(x>=CONTROL_PANEL_LEFT && x<CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH &&
		   y>=CONTROL_PANEL_FIRST_ROW &&
		   y<CONTROL_PANEL_FIRST_ROW+13*CONTROL_PANEL_ROW_HEIGHT)
		{
			row=(y-CONTROL_PANEL_FIRST_ROW)/CONTROL_PANEL_ROW_HEIGHT;
			if(rotationcomplete==1)
				mymenu(row<12 ? row+1 : 0);
			glutPostRedisplay();
			return;
		}

		if(x>=CONTROL_PANEL_LEFT && x<CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH &&
		   y>=CONTROL_PANEL_TOP+400 &&
		   y<CONTROL_PANEL_TOP+CONTROL_PANEL_HEIGHT)
		{
			if(rotationcomplete==1)
				mymenu(13);
			glutPostRedisplay();
			return;
		}

		if(x>=CONTROL_PANEL_LEFT && x<CONTROL_PANEL_LEFT+CONTROL_PANEL_WIDTH &&
		   y>=CONTROL_PANEL_TOP && y<CONTROL_PANEL_TOP+CONTROL_PANEL_HEIGHT)
			return;
	}

	moving=1;
	beginx=x;
	beginy=y;
	glutPostRedisplay();
} 
 
 
static void keyboard(unsigned char key,int x,int y) 
{ 
	int move=0;
	int moveInverse=0;

	(void)x;
	(void)y;
	switch(key)
	{
		case 'a': move=1; break;
		case 'q': move=1; moveInverse=1; break;
		case 's': move=2; break;
		case 'w': move=2; moveInverse=1; break;
		case 'd': move=3; break;
		case 'e': move=3; moveInverse=1; break;
		case 'f': move=4; break;
		case 'r': move=4; moveInverse=1; break;
		case 'g': move=5; break;
		case 't': move=5; moveInverse=1; break;
		case 'h': move=6; break;
		case 'y': move=6; moveInverse=1; break;
	}
	if(move!=0)
	{
		startCubeMove(move,moveInverse);
		return;
	}

	if(key=='2'&&rotationcomplete==1) 
	{ 
		p=p+2.0;
		glutPostRedisplay();
	} 
	if(key=='8'&&rotationcomplete==1) 
	{ 
		p=p-2.0; 
		glutPostRedisplay();
	} 
	if(key=='6'&&rotationcomplete==1) 
	{ 
		q=q+2.0; 
		glutPostRedisplay();
	} 
	if(key=='4'&&rotationcomplete==1) 
	{ 
		q=q-2.0; 
		glutPostRedisplay();
	} 
	if(key=='9'&&rotationcomplete==1) 
	{ 
		r=r+2.0; 
		glutPostRedisplay();
	} 
	if(key=='1'&&rotationcomplete==1) 
	{ 
		r=r-2.0; 
		glutPostRedisplay();
	} 
	if(key=='5'&&rotationcomplete==1) 
	{ 
		p=0.0; 
		q=0.0; 
		r=0.0; 
		glutPostRedisplay();
	} 
	if(key=='o'&&rotationcomplete==1) 
		undoLastCubeMove();
} 
 

void myreshape(int w,int h) 
{ 
	windowWidth=w;
	windowHeight=h;
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if (w <= h) 
		glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0); 
	else 
		glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0); 
	glMatrixMode(GL_MODELVIEW); 
}
 

void mymenu(int id) 
{ 
	if(id==0)
	{
		undoLastCubeMove();
		return;
	}
	if(id==13)
	{
		exit(0);
		return;
	}
	if(id>=1 && id<=12)
	{
		int move=(id+1)/2;
		int moveInverse=id%2==0;
		startCubeMove(move,moveInverse);
	} 
}

 
int main(int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("RUBIK'S CUBE"); 
	glutReshapeFunc(myreshape); 
	glutIdleFunc(spincube); 
	glutMouseFunc(mouse); 
	glutMotionFunc(motion); 
	glutKeyboardFunc(keyboard); 
	glutDisplayFunc(display); 
	glClearColor(0.1f,0.12f,0.15f,1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); 
	glutMainLoop(); 
	//return 0; 
}

