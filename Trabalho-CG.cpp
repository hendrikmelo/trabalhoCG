#include <GL\glut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
 
using namespace std;
 
float lado = 40;
float centro_piramide = 80;
GLuint texID[2];

void piramide(float SIZE, GLuint texid){	
	glBindTexture(GL_TEXTURE_2D, texid);
	// Now the roof
	glBegin(GL_TRIANGLES);
	// Front
	  glColor3f( 1, 1, 0 );		// yellow
	  glTexCoord2f(0,0);	glVertex3f(  -lado,  lado,  lado );
	  glTexCoord2f(1,0);	glVertex3f( lado,  lado,  lado );
	  glTexCoord2f(0.5f,1);	glVertex3f(  0,  80,  0 );
	// Right side
	  glColor3f( 0.9, 0.9, 0 );	// darker yellow
	  glTexCoord2f(0,0);	glVertex3f(  lado,  lado,  lado );
	  glTexCoord2f(1,0);	glVertex3f(  lado,  lado, -lado );
	  glTexCoord2f(0.5f,1);	glVertex3f(  0,  80,  0 );
	// Back
	  glColor3f( 0.8, 0.8, 0 );	// even darker yellow
	  glTexCoord2f(0,0);	glVertex3f(  lado,  lado, -lado );
	  glTexCoord2f(1,0);	glVertex3f( -lado,  lado, -lado );
	  glTexCoord2f(0.5f,1);	glVertex3f(  0,  80,  0 );
	// Left side
	  glColor3f( 0.7, 0.7, 0 );	// a bit darker, but still yellow
	  glTexCoord2f(0,0);	glVertex3f( -lado,  lado,  -lado );
	  glTexCoord2f(1,0);	glVertex3f(  -lado,  lado,  lado );
	  glTexCoord2f(0.5f,1);	glVertex3f(  0,  80,  0 );
	glEnd();

	glutSwapBuffers();
}
void cubo(float SIZE, GLuint texid){
		glBindTexture(GL_TEXTURE_2D, texid);
        //glLineWidth(10);
        glColor3f(1,1,0);
        glBegin(GL_QUADS);//FACE FRONTAL
        glTexCoord2f(0,0);        glVertex3f(lado,lado,lado);// +++
        glTexCoord2f(1,0);        glVertex3f(-lado,lado,lado);// -++
        glTexCoord2f(1,1);        glVertex3f(-lado,-lado,lado);// --+
        glTexCoord2f(0,1);       glVertex3f(lado,-lado,lado);// +-+
        glEnd();
       
        glColor3f(1,1,0);
        glBegin(GL_QUADS);//FACE POSTERIOR
        glTexCoord2f(0,0);        glVertex3f(lado,lado,-lado);// ++-
        glTexCoord2f(1,0);        glVertex3f(-lado,lado,-lado);// -+-
        glTexCoord2f(1,1);        glVertex3f(-lado,-lado,-lado);// ---
        glTexCoord2f(0,1);        glVertex3f(lado,-lado,-lado);// +--
        
        glEnd();
       
        glColor3f(1,0.8f,0);
        glBegin(GL_QUADS);//FACE ESQUERDA
        glTexCoord2f(0,0);        glVertex3f(-lado,lado,lado);// -++
        glTexCoord2f(1,0);        glVertex3f(-lado,lado,-lado);// -+-
        glTexCoord2f(1,1);        glVertex3f(-lado,-lado,-lado);// ---
        glTexCoord2f(0,1);        glVertex3f(-lado,-lado,lado);// --+
        glEnd();
       
        glColor3f(1,0.8f,0);
        glBegin(GL_QUADS);//FACE DIREITA
        glTexCoord2f(0,0);        glVertex3f(lado,lado,lado);// +++
        glTexCoord2f(0,1);        glVertex3f(lado,-lado,lado);// +-+
        glTexCoord2f(1,1);        glVertex3f(lado,-lado,-lado);// +--
        glTexCoord2f(1,0);        glVertex3f(lado,lado,-lado);// ++-
        glEnd();
       
        glColor3f(1,0.9f,0);
        glBegin(GL_QUADS);//FACE SUPERIOR
                glVertex3f(-lado,lado,-lado);//-+-
                glVertex3f(-lado,lado,lado);//-++
                glVertex3f(lado,lado,lado);//+++
                glVertex3f(lado,lado,-lado);//++-
        glEnd();
        glColor3f(0.5f,0.5f,0);
        glBegin(GL_QUADS);//FACE INFERIOR
                glVertex3f(-lado,-lado,-lado);//---
                glVertex3f(lado,-lado,-lado);//+--
                glVertex3f(lado,-lado,lado);//+-+
                glVertex3f(-lado,-lado,lado);//--+
        glEnd();
}
 
void desenho(){
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        piramide(lado, texID[1]);
        
		cubo(lado, texID[0]);
        
        glRotatef(2,0,1,0);    
        glColor3f(0,0,1);
        glFlush();
}
 
void ajuste(int w, int h){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
       
        gluPerspective(45,w/h, 0.4, 500);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
       
        gluLookAt(0,50,200,
                        0,0,0,
                        0,1,0);
}
 
void anima(int value){
        glutPostRedisplay();
        glutTimerFunc(30,anima,1);
}
 
void initializeLight(){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
 
        //glEnable(GL_COLOR_MATERIAL);
       
        float luzAmbiente[4] = {0.3,0.3,0.3,1};
        float luzDifusa[4] = {0.7,0.7,0.7,1};
        float luzEspecular[4] = {1,1,1,1};
        float posicaoLuz0[4] = {0,20,0,1};
        float especularidade[4] = {1,1,1,1};
        int especMaterial = 128;
       
        glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
        glMaterialf(GL_FRONT, GL_SHININESS, especMaterial);
       
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
       
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
       
}
void carregarTextura(GLuint tex_id, string filepath){
        unsigned char* imgData;
        int largura, altura, canais;
       
        stbi_set_flip_vertically_on_load(true);
       
        imgData = stbi_load(filepath.c_str(), &largura, &altura,&canais, 4);
       
        if(imgData){
                glBindTexture(GL_TEXTURE_2D, tex_id);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura,
                altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
               
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
               
                stbi_image_free(imgData);
        }else{
                cout<<"ERRO!Não foi possível carregar a imagem "<<filepath.c_str()<<endl;
        }
}
 
void initializeTexture(){
        glGenTextures(2, texID);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        carregarTextura(texID[0], "images/brick.png");
        carregarTextura(texID[1], "images/wood.png");
       
        glEnable(GL_DEPTH_TEST);
}

int main(){
       glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
        glutInitWindowPosition(200,100);
        glutInitWindowSize(800,800);
        glutCreateWindow("Iluminacao");
        glutDisplayFunc(desenho);
        glutReshapeFunc(ajuste);
        glutTimerFunc(30,anima,1);
        initializeTexture();
        initializeLight();
        glutMainLoop();
}
