/*******************************************************************/
/** MAC 122 - Principios de Desenvolvimento de Algoritmos         **/
/** IME-USP - Segundo Semestre de 2009                            **/
/**                                                               **/
/** Segundo Exercocio-Programa -- Fractais                        **/
/** Arquivo: fractal.c                                            **/                                             
/**                                                               **/
/** Henrique Gemignani Passos Lima    nº USP: ???????             **/
/**                                                               **/
/** 22/08/2009                                                    **/
/*******************************************************************/
/* Compilar com "gcc -lglut -lm" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>  

#define menu_Sair			0x00
#define menu_Executar		0x01
#define menu_Limpar			0x02
#define menu_aumentarNivel	0x03
#define menu_diminuirNivel	0x04

#define MODELO_ILHATRIADICA	0x20
#define MODELO_ILHAQUAD1	0x21
#define MODELO_ILHAQUAD2	0x22
#define MODELO_NEVE1		0x23
#define MODELO_NEVE2		0x24
#define MODELO_NEVE3		0x25
#define MODELO_NEVE4		0x26

#define NUM_MODELO	7
#define MAX_POINT	32

#define raioFiguraBase 120
#define PI		3.141592653589793
#define screenWidth 800
#define screenHeight 600
int FRACTAL_DATA[NUM_MODELO][2] = {
	{ 3, 3 }, // Ilha de Koch Triadica
	{ 7, 4 }, // Ilha de Koch Quadrica
	{ 31, 8 }, // Ilha de Koch Quadrica 2
	{ 6, 3 }, // Floco de Neve 1
	{ 6, 3 }, // Floco de Neve 2
	{ 6, 3 }, // Floco de Neve 3
	{ 6, 3 }, // Floco de Neve 4
};
float FRACTAL_PONTOS[NUM_MODELO][MAX_POINT][3] = {
	// Ilha de Koch Triadica
	/*=======================================================\
	 P1 = (x,angle), em Coordenadas polares, considerando START como (0,0)
	 Sendo P2 = (R,angle + PI/6), em Coordenadas polares, considerando START como (0,0)
	  Pela Lei dos Cossenos: 
	   R*R = 2*x*x - 2*x*x*cos120
	   R*R = 2*x*x*( 1 - cos120 )     cos120 = -0.5
	   R*R = 3*x*x -> R = x*sqrt(3)
	 P3 = (2x,angle), em Coordenadas polares, considerando START como (0,0)
	\========================================================*/
	{
		{ 1               , 0     , 0 },
		{ 1.73205080756887, PI / 6, 0 },
		{ 2               , 0     , 0 }
	},
	
	// Ilha de Koch Quadrica
	/*=======================================================\
	 P1 = (x,angle), em Coordenadas polares, considerando START como (0,0)
	 P2 = (x*sqrt(2),angle + PI/4), em Coordenadas polares, considerando START como (0,0)
	 O triangulo retangulo (START,P3,P4) tem catetos x e 2x. Logo, pelo Teorema de Pitágoras, a hipotenusa vale x*sqrt5
	  O angulo no verticie START é igual a arctg(0.5) = 0.463647609 rad.
	  Portanto P3 = (x*sqrt5,angle + 0.463647609), em Coordenadas polares, considerando START como (0,0)
	 P4 = (2x,angle), em Coordenadas polares, considerando START como (0,0)
	 De maneira análoga à feita no P3, descobrimos que P5 = (x*sqrta5,angle - 0.463647609), em Coordenadas polares, considerando START como (0,0)
	 O triangulo retangulo (START,P7,P6) tem catetos 3x e x. Logo, pelo Teorema de Pitágoras, a hipotenusa vale x * sqrt2 * sqrt5
	  O angulo no verticie START é igual a arctg(1/3) = 0.321750554 rad.
	  Portanto P6 = (x*sqrt2*sqrt5,angle - 0.321750554), em Coordenadas polares, considerando START como (0,0)
	 P7 = (3x,angle), em Coordenadas polares, considerando START como (0,0)
	\========================================================*/
	{
		{ 1                , 0           , 0 },
		{ 1.414213562373095, PI / 4      , 0 },
		{ 2.236067977499789, 0.463647609 , 0 },
		{ 2                , 0           , 0 },
		{ 2.236067977499789, -0.463647609, 0 },
		{ 3.162277660168379, -0.321750554, 0 },
		{ 3                , 0           , 0 }
	},
	/*=======================================================\
	// Ilha de Koch Quadrica 2
	\========================================================*/
	{
		{ 1                ,  PI/2             , 0 }, // P 1
		{ 1.414213562373095,  PI/4             , 0 }, // P 2 = (sqrt[ 2], PI/4)
		{ 2.236067977499789,  1.107148717794090, 0 }, // P 3 = (sqrt[ 5], arctg[ 2 ])
		{ 2                ,  PI/2             , 0 }, // P 4
		{ 3                ,  PI/2             , 0 }, // P 5
		{ 3.162277660168379,  1.249045772398254, 0 }, // P 6 = (sqrt[10], arctg[ 3 ])
		{ 3.605551275463989,  0.982793723247329, 0 }, // P 7 = (sqrt[13], arctg[3/2])
		{ 4.472135954999579,  1.107148717794090, 0 }, // P 8 = (sqrt[20], arctg[ 2 ])
		{ 5                ,  0.927295218001612, 0 }, // P 9 = ( 5      , arctg[4/3])
		{ 4.242640687119285,  PI/4             , 0 }, // P10 = (sqrt[18], PI/4 )
		{ 3.605551275463989,  0.588002603547567, 0 }, // P11 = (sqrt[13], arctg[2/3])
		{ 2.828427124746190,  PI/4             , 0 }, // P12 = (sqrt[ 8], PI/4 )
		{ 2.236067977499789,  0.463647609000806, 0 }, // P13 = (sqrt[ 5], arctg[1/2])
		{ 3.162277660168379,  0.321750554396642, 0 }, // P14 = (sqrt[10], arctg[1/3])
		{ 4.123105625617660,  0.244978663126864, 0 }, // P15 = (sqrt[17], arctg[1/4])
		{ 4                ,  0                , 0 }, // P16 = MEIO
		{ 4.123105625617660, -0.244978663126864, 0 }, // P17 = (sqrt[17], -arctg[1/4])
		{ 5.099019513592784, -0.197395559849880, 0 }, // P18 = (sqrt[26], -arctg[1/5])
		{ 6.082762530298219, -0.165148677414626, 0 }, // P19 = (sqrt[37], -arctg[1/6])
		{ 6.324555320336758, -0.321750554396642, 0 }, // P20 = (sqrt[40], -arctg[1/3])
		{ 5.385164807134504, -0.380506377112364, 0 }, // P21 = (sqrt[29], -arctg[2/5])
		{ 5.830951894845300, -0.540419500270584, 0 }, // P22 = (sqrt[34], -arctg[3/5])
		{ 6.403124237432848, -0.674740942223552, 0 }, // P23 = (sqrt[41], -arctg[4/5])
		{ 7.211102550927978, -0.588002603547567, 0 }, // P24 = (sqrt[52], -arctg[2/3])
		{ 6.708203932499369, -0.463647609000806, 0 }, // P25 = (sqrt[45], -arctg[1/2])
		{ 7.615773105863908, -0.404891786285083, 0 }, // P26 = (sqrt[58], -arctg[3/7])
		{ 8.544003745317531, -0.358770670270572, 0 }, // P27 = (sqrt[73], -arctg[3/8])
		{ 8.246211251235321, -0.244978663126864, 0 }, // P28 = (sqrt[68], -arctg[1/4])
		{ 7.280109889280518, -0.278299659005111, 0 }, // P29 = (sqrt[53], -arctg[2/7])
		{ 7.071067811865475, -0.141897054604163, 0 }, // P30 = (sqrt[50], -arctg[1/7])
		{ 8.062257748298549, -0.124354994546761, 0 }  // P31 = (sqrt[65], -arctg[1/8])
	},
	/*=======================================================\
	// Floco de Neve (Modelo 1) - Original
	\========================================================*/
	{
		{ 1                ,  PI / 3           , MODELO_NEVE3 }, // P1 = ( 1     , PI/3)
		{ 2                ,  PI / 3           , MODELO_NEVE4 }, // P2 = ( 2     , PI/3)
		{ 2.645751311064590,  0.713724378944765, MODELO_NEVE4 }, // P3 = (sqrt[7], arctg[sqrt[3]/2])
		{ 2.692582403567252,  0.380506377112364, MODELO_NEVE4 }, // P4 = (sqrt[7.25], arctg[7/2.5])
		{ 1                ,  0                , MODELO_NEVE2 }, // P5 = ( 1     , 0 )
		{ 2                ,  0                , MODELO_NEVE3 }, // P6 = ( 2     , 0 )
		{ 0                ,  0                , MODELO_NEVE4 }
	},
	/*=======================================================\
	// Floco de Neve (Modelo 2) - UpsideDown/Inverted
	\========================================================*/
	{
		{ 1                ,  0                , MODELO_NEVE2 }, // P1 = ( 1     , 0)
		{ 2                ,  0                , MODELO_NEVE4 }, // P2 = ( 2     , 0)
		{ 1                , -PI / 3           , MODELO_NEVE1 }, // P3 = ( 1     , -PI/3)
		{ 2                , -PI / 3           , MODELO_NEVE3 }, // P4 = ( 1     , -PI/3)
		{ 2.645751311064590, -0.713724378944765, MODELO_NEVE2 }, // P5 = (sqrt[7], -arctg[sqrt[3]/2])
		{ 2.692582403567252, -0.380506377112364, MODELO_NEVE3 }, // P6 = (sqrt[7.25], -arctg[7/2.5])
		{ 0                ,  0                , MODELO_NEVE4 }
	},
	/*=======================================================\
	// Floco de Neve (Modelo 3) - UpsideDown
	\========================================================*/
	{
		{ 1                , -PI / 3           , MODELO_NEVE1 }, // P1 = ( 1     , -PI/3)
		{ 2                , -PI / 3           , MODELO_NEVE2 }, // P2 = ( 2     , -PI/3)
		{ 2.645751311064590, -0.713724378944765, MODELO_NEVE2 }, // P3 = (sqrt[7], -arctg[sqrt[3]/2])
		{ 2.692582403567252, -0.380506377112364, MODELO_NEVE3 }, // P4 = (sqrt[7.25], -arctg[7/2.5])
		{ 1                ,  0                , MODELO_NEVE4 }, // P5 = ( 1     , 0 )
		{ 2                ,  0                , MODELO_NEVE4 }, // P6 = ( 2     , 0 )
		{ 0                ,  0                , MODELO_NEVE1 }
	},
	/*=======================================================\
	// Floco de Neve (Modelo 4) - Inverted
	\========================================================*/
	{
		{ 1                ,  0                , MODELO_NEVE4 }, // P1 = ( 1     , 0)
		{ 2                ,  0                , MODELO_NEVE2 }, // P2 = ( 2     , 0)
		{ 1                ,  PI / 3           , MODELO_NEVE3 }, // P3 = ( 1     , PI/3)
		{ 2                ,  PI / 3           , MODELO_NEVE4 }, // P4 = ( 1     , PI/3)
		{ 2.645751311064590,  0.713724378944765, MODELO_NEVE1 }, // P5 = (sqrt[7], arctg[sqrt[3]/2])
		{ 2.692582403567252,  0.380506377112364, MODELO_NEVE4 }, // P6 = (sqrt[7.25], arctg[7/2.5])
		{ 0                ,  0                , MODELO_NEVE1 }
	}
};

static int win;
static int menuPrincipal, menuModelo, menuBase, menuNivel;
static short MAY_CLEAR = 0x01;
static short modeloFractal = MODELO_ILHATRIADICA, baseFractal = 3, nivelRecursao = 1;
void callbackMenu(int value);
void drawFractal( int nivel, int modelo, int raio, int lados );

/* Funções para a interface grafica do OpenGL */
void createMenu(void) {
	/* Criando o submenu de seleção de Modelo. */
	menuModelo = glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Ilha de Koch Triadica",	MODELO_ILHATRIADICA);
	glutAddMenuEntry("Ilha de Koch Quadrica",	MODELO_ILHAQUAD1);
	glutAddMenuEntry("Ilha de Koch Quadrica 2",	MODELO_ILHAQUAD2);
	glutAddMenuEntry("Floco de Neve",			MODELO_NEVE1);
	
	menuBase = glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Linha",		0x32);
	glutAddMenuEntry("Triangulo",	0x33);
	glutAddMenuEntry("Quadrado",	0x34);
	glutAddMenuEntry("Pentagono",	0x35);
	glutAddMenuEntry("Hexagono",	0x36);
	glutAddMenuEntry("Heptagono",	0x37);
	glutAddMenuEntry("Octogono ",	0x38);
	glutAddMenuEntry("Eneagono",	0x39);
	glutAddMenuEntry("Decagono",	0x40);
	glutAddMenuEntry("Hendecagono",	0x41);
	glutAddMenuEntry("Dodecagono",	0x42);
	glutAddMenuEntry("Triscaidecagono",	0x43);
	
	/* Criando o submenu de seleção do nivel de recursao. */
	menuNivel = glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Aumentar", menu_aumentarNivel);
	glutAddMenuEntry("Diminuir", menu_diminuirNivel);
	
	/* Criando menu principal. */
	menuPrincipal = glutCreateMenu(callbackMenu);
	
	glutAddSubMenu("Modelo", menuModelo);
	glutAddSubMenu("Figura Base", menuBase);
	glutAddSubMenu("Nivel de Recursao", menuNivel);
	glutAddMenuEntry("Desenhar", menu_Executar);
	glutAddMenuEntry("Limpar", menu_Limpar);
	glutAddMenuEntry("Sair", menu_Sair);
	
	/*Faz com que o menu seja chamado quando apertamos o botão direito*/
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void reshape(int w,int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
}
void callbackMenu(int value) {
	// Aqui são tratadas as chamadas ao menu
	// value é o ID do item no menu
	MAY_CLEAR = 0x01;
	// Mudando modelo
	if( 0x20 <= value && value < 0x30 ) {
		modeloFractal = value;
		nivelRecursao = 1;

	// Mudando base
	} else if( 0x30 <= value && value < 0x50 ) {
		baseFractal = value - 0x30;
		nivelRecursao = 1;
		
	} else switch( value ) {
	case menu_aumentarNivel:
		nivelRecursao++;
		break;
	case menu_diminuirNivel:
		if( nivelRecursao > 1 ) nivelRecursao--;
		break;
	case menu_Executar:
		MAY_CLEAR = 0x02;
		break;
	case menu_Sair:
		glutDestroyWindow(win);
		exit(0);
		break;
	case menu_Limpar:
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	default:
		break;
	}
	/*redesenhando*/
	glutPostRedisplay();
}
void keyboardEvents(unsigned char key, int x, int y) {
	if( key == 27 ) // ESCAPE == close
		exit(0);
	else if( key == '+' )
		nivelRecursao++;
	else if( key == '-' ) {
		if( nivelRecursao > 1 )
			nivelRecursao--;
	} else if( key == 13 )
		MAY_CLEAR = 0x02;
	glutPostRedisplay();
}


/* Funções auxiliares */
float distanceBetweenPoints( float x1, float y1, float x2, float y2 ) {
	float dX = x2 - x1, dY = y2 - y1;
	return sqrt( dX*dX + dY*dY );
}
float angleBetweenPoints( float x1, float y1, float x2, float y2 ) {
	return atan2( y2 - y1, x2 - x1 );
}

/*	Funcao recursiva para desenhar fractais.
	nivel <= 1 (Base)
		Nesse caso, simplesmente desenha.
	nivel > 1
		Cria os pontos do modelo atual, e utiliza-se da recursao para cada segmento gerado. */
void fractalRecursion( int nivel, float x1, float y1, float x2, float y2, int modelo ) {
	if( nivel < 1 ) {
		glVertex2f( x1 + screenWidth / 2, y1 + screenHeight / 2);
		return;
	}
	float dist = distanceBetweenPoints( x1, y1, x2, y2 ) / FRACTAL_DATA[modelo - 0x20][1];
	float angle = angleBetweenPoints( x1, y1, x2, y2 );
	float p1x, p1y, p2x, p2y;
	int i;
	p1x = x1; p1y = y1;
	for( i = 0; i < FRACTAL_DATA[modelo - 0x20][0]; i++ ) {
		p2x = x1 + (dist * FRACTAL_PONTOS[modelo - 0x20][i][0]) * cos( angle + FRACTAL_PONTOS[modelo - 0x20][i][1] );
		p2y = y1 + (dist * FRACTAL_PONTOS[modelo - 0x20][i][0]) * sin( angle + FRACTAL_PONTOS[modelo - 0x20][i][1] );
		fractalRecursion( nivel - 1, p1x, p1y, p2x, p2y, 
			((int) FRACTAL_PONTOS[modelo - 0x20][i][2]) ? (int) FRACTAL_PONTOS[modelo - 0x20][i][2] : modelo );
		p1x = p2x; p1y = p2y;
	}
	i = (int) FRACTAL_PONTOS[modelo - 0x20][ FRACTAL_DATA[modelo - 0x20][0] ][2];
	fractalRecursion( nivel - 1, p1x, p1y, x2, y2, i ? i : modelo );
}

/* Gera a imagem base e inicia a recursão para essa imagem */
void drawFractal( int nivel, int modelo, int raio, int lados ) {
	glClear( GL_COLOR_BUFFER_BIT );
	glBegin( GL_LINE_STRIP );
	glColor3f( 0.5, 0.5, 0.5 );
	float angleOffset = 0;
	int i;
	float x1 = raio * cos( angleOffset ),
		y1 = raio * sin( angleOffset ), 
		x2, y2;
	for( i = 0; i < lados; i++ ) {
		x2 = raio * cos( angleOffset + (-i - 1) * (2 * PI / lados) );
		y2 = raio * sin( angleOffset + (-i - 1) * (2 * PI / lados) );
		fractalRecursion( nivel - 1, x1, y1, x2, y2, modelo );
		x1 = x2; y1 = y2;
	}
	//fractalRecursion( nivel - 1, x1, y1, raio, 0, modelo );
	glVertex2f( raio + screenWidth / 2, screenHeight / 2 );
	glEnd();
	glutSwapBuffers();
	glFlush(); // Força desenhar a janela (Não apagar) 
}

/* Limpa a tela. Se necessario, chama "drawFractal" para iniciar o fractal. */
void clearScreen(void) {
	if( MAY_CLEAR == 0x02 ) {
		MAY_CLEAR = 0x00;
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();
		drawFractal( nivelRecursao, modeloFractal, raioFiguraBase, baseFractal );
	} else if( MAY_CLEAR ) {
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
	}
}
int main(int argc, char ** argv) {
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize( screenWidth, screenHeight );
	glutCreateWindow("EP2 - Fractal");
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );
	glLineWidth( 1.5 );
	glPointSize( 1.0 );
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	createMenu();
	glutKeyboardFunc( keyboardEvents );
	glutDisplayFunc( clearScreen );
	glutReshapeFunc( reshape );
	glutMainLoop();
	return 0;
}