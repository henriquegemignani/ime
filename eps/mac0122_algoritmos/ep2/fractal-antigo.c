/* Compilar com "gcc -lglut -lm" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>  

#define menu_Sair		0x00
#define menu_Executar	0x01
#define menu_Limpar		0x02
#define menu_IlhaKochTriadica 0x21
#define menu_IlhaKochQuadrica 0x22
#define menu_triangulo	0x33
#define menu_quadrado	0x34
#define menu_pentagono	0x35
#define menu_hexagono	0x36
#define menu_aumentarNivel 0x11
#define menu_diminuirNivel 0x12

#define raioFiguraBase 300
#define PI 3.14159265
#define sqrt2 1.414213562373095
#define sqrt3 1.732050807568877
#define sqrt5 2.236067977499789
#define screenWidth 800
#define screenHeight 600

#define NUMPONTOS_IlhaKoch 3



// P1 = (x,angle), em Coordenadas polares, considerando START como (0,0)
// Sendo P2 = (R,angle + PI/6), em Coordenadas polares, considerando START como (0,0)
// Pela Lei dos Cossenos: 
//  R*R = 2*x*x - 2*x*x*cos120
//  R*R = 2*x*x*( 1 - cos120 )     cos120 = -0.5
//  R*R = 3*x*x -> R = x*sqrt(3)
// P3 = (2x,angle), em Coordenadas polares, considerando START como (0,0)
float PONTOS_IlhaKoch[3][2] = {
	{ 1, 0 },
	{ sqrt3, PI/6 },
	{ 2, 0 }
};

static int win;
static int menuPrincipal, menuModelo, menuBase, menuNivel;
static int primitive = menu_Executar;
static short REDRAW = 0x01;
static short modeloFractal = menu_IlhaKochTriadica, nivelRecursao = 1;
void callbackMenu(int value);
void increaseRecursion(void);
void decreaseRecursion(void);

void createMenu(void) {
	/* Criando o submenu de seleção de Modelo. */
	menuModelo = glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Ilha de Koch triadica", menu_IlhaKochTriadica);
	glutAddMenuEntry("Ilha de Koch quadrica", menu_IlhaKochQuadrica);
	
	menuBase = glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Triangulo", menu_triangulo);
	glutAddMenuEntry("Quadrado",  menu_quadrado);
	glutAddMenuEntry("Pentagono", menu_pentagono);
	glutAddMenuEntry("Hexagono",  menu_hexagono);
	
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



/********************************************/
/* Estrutura da lista ligada				*/
/*  e funcoes relacionadas a esta.			*/
typedef struct PointData {
    float x;
	float y;
	short nivel;
    struct PointData *next;
} pointStruct;
typedef pointStruct* point;
point startPoint;
/*float distanceBetweenPoints( point a, point b ) {
	float dX = b->x - a->x, dY = b->y - a->y;
	return sqrt( dX*dX + dY*dY );
}
float angleBetweenPoints( point a, point b ) {
	float dX = b->x - a->x, dY = b->y - a->y;
	return atan2( dY, dX );
}*/
float distanceBetweenPoints( float x1, float y1, float x2, float y2 ) {
	float dX = x2 - x1, dY = y2 - y1;
	return sqrt( dX*dX + dY*dY );
}
float angleBetweenPoints( float x1, float y1, float x2, float y2 ) {
	float dX = x2 - x1, dY = y2 - y1;
	return atan2( dY, dX );
}
void freePointList( point *root ) {
	if( *root == NULL ) return;
	point p, aux;
	for( p = *root; p != NULL; p = aux ) {
		aux = p->next;
		if( p ) free(p);
	}
	*root = NULL;
}
point allocatePoint( short nivel, float x, float y ) {
	point p = malloc(sizeof(pointStruct));
	if( p == NULL ) {
		printf("Erro: Memoria insuficiente.\n");
		exit(1);
		return NULL;
	}
	p->x = x;
	p->y = y;
	p->nivel = nivel;
	p->next = NULL;
	return p;
}
point newPointAfter( short nivel, point* root, float x, float y ) {
	point new = allocatePoint( nivel, x, y );
	if( *root == NULL ) {
		*root = new;
	} else {
		new->next = (*root)->next;
		(*root)->next = new;
	}
	return new;
}
point newPointAtEnd( short nivel, point* root, float x, float y ) {
	point new = allocatePoint( nivel, x, y );
	if( *root == NULL ) {
		*root = new;
	} else {
        point aux = *root;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new;
	}
	return new;
}
void removePoint( point *root, point *target ) {
	if( *root == NULL || *target == NULL ) return;
	point p;
	for( p = *root; p != NULL; p = p->next ) {
		if( p->next != *target ) continue;
		p->next = (*target)->next;
		free(*target);
		return;
	}
}
/*  Fim das funcoes da lista ligada			*/
/********************************************/
point createPolygon( short lados, short raio, point* root ) {
	int i;
	for( i = 0; i < lados; i++ ) {
		newPointAtEnd( 1, root, 
			raioFiguraBase * cos( (-i) * (2 * PI / lados) ), 
			raioFiguraBase * sin( (-i) * (2 * PI / lados) )
		);
	}
	return *root;
}
void callbackMenu(int value) {
	/*Aqui são tratadas as chamadas ao menu
	value é o ID do item no menu*/
	if( 0x20 <= value && value < 0x30 ) {
		freePointList( &startPoint );
		modeloFractal = value;
		nivelRecursao = 1;
		
	} else if( 0x30 <= value && value < 0x40 ) {
		freePointList( &startPoint );
		createPolygon( value - 0x30, raioFiguraBase, &startPoint );
		nivelRecursao = 1;
		
	} else switch( value ) {
	case menu_aumentarNivel:
		increaseRecursion();
		break;
	case menu_diminuirNivel:
		decreaseRecursion();
		break;
	case menu_Executar:
		REDRAW = 0x01;
		break;
	case menu_Sair:
		glutDestroyWindow(win);
		freePointList( &startPoint );
		exit(0);
		break;
	case menu_Limpar:
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	default:
		primitive = value;
	}
	/*redesenhando*/
	glutPostRedisplay();
}
void setColorFromNivel( short nivel ) {
	switch( nivel ) {
		case 1:
			glColor3f( 1.0, 0.0, 0.0);
			return;
		case 2:
			glColor3f( 0.0, 0.0, 1.0);
			return;
		case 3:
			glColor3f( 0.0, 1.0, 0.0);
			return;
		case 4:
			glColor3f( 1.0, 0.0, 1.0);
			return;
		default:
			glColor3f( 1.0 - nivel / 5, 0.0, 1.0 - nivel / 5);
			return;
	}
}

/* void fractalRecursion( point start, point target ) {
	if( target == NULL ) target = startPoint;
	float dist = distanceBetweenPoints( start, target );
	float angle = angleBetweenPoints( start, target );
	float x;
	short nivel = nivelRecursao;
	point aux;
	switch( modeloFractal ) {
	case menu_IlhaKochTriadica:
		// Ilha de Koch triadica
		x = dist / 3;
		// P1 = (x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &start, start->x + x * cos( angle ), start->y + x * sin( angle ) );
		
		// Sendo P2 = (R,angle + PI/6), em Coordenadas polares, considerando START como (0,0)
		// Pela Lei dos Cossenos: 
		//  R*R = 2*x*x - 2*x*x*cos120
		//  R*R = 2*x*x*( 1 - cos120 )     cos120 = -0.5
		//  R*R = 3*x*x -> R = x*sqrt(3)
		aux = newPointAfter( nivel, &aux, 
			start->x + (x * sqrt3) * cos( angle + PI/6 ),
			start->y + (x * sqrt3) * sin( angle + PI/6 ) );
			
		// P3 = (2x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * 2) * cos( angle ), start->y + (x * 2) * sin( angle ) );
		break;
	case menu_IlhaKochQuadrica:
		// Ilha de Koch quadrica
		x = dist / 4;
		// P1 = (x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &start, start->x + x * cos( angle ), start->y + x * sin( angle ) );
		
		// P2 = (x*sqrt(2),angle + PI/4), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt2) * cos( angle + PI/4), start->y + (x * sqrt2) * sin( angle + PI/4) );
		
		// O triangulo retangulo (START,P3,P4) tem catetos x e 2x. Logo, pelo Teorema de Pitágoras, a hipotenusa vale x*sqrt5
		// O angulo no verticie START é igual a arctg(0.5) = 0.463647609 rad.
		// Portanto P3 = (x*sqrt5,angle + 0.463647609), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt5) * cos( angle + 0.463647609 ), start->y + (x * sqrt5) * sin( angle + 0.463647609 ) );
		
		// P4 = (2x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * 2) * cos( angle ), start->y + (x * 2) * sin( angle ) );
		
		// De maneira análoga à feita no P3, descobrimos que P5 = (x*sqrta5,angle - 0.463647609), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt5) * cos( angle - 0.463647609 ), start->y + (x * sqrt5) * sin( angle - 0.463647609 ) );
		
		// O triangulo retangulo (START,P7,P6) tem catetos 3x e x. Logo, pelo Teorema de Pitágoras, a hipotenusa vale x * sqrt2 * sqrt5
		// O angulo no verticie START é igual a arctg(1/3) = 0.321750554 rad.
		// Portanto P6 = (x*sqrt2*sqrt5,angle - 0.321750554), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt2 * sqrt5) * cos( angle - 0.321750554 ), start->y + (x * sqrt2 * sqrt5) * sin( angle - 0.321750554 ) );
		
		// P7 = (3x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * 3) * cos( angle ), start->y + (x * 3) * sin( angle ) );
		break;
	}
} */

void fractalRecursion( int nivel, float x1, float y1, float x2, float y2 ) {
	if( nivel <= 1 ) {
		glVertex2f( x1 + screenWidth / 2, y1 + screenHeight / 2);
		return;
	}
	float dist = distanceBetweenPoints( x1, y1, x2, y2 );
	float angle = angleBetweenPoints( x1, y1, x2, y2 );
	float d, p1x, p1y, p2x, p2y;
	int i;
	point aux;
	switch( modeloFractal ) {
	case menu_IlhaKochTriadica:
		// Ilha de Koch triadica
		d = dist / 3;
		p1x = x1; p1y = y1;
		for( i = 0; i < NUMPONTOS_IlhaKoch; i++ ) {
			p2x = x1 + (d * PONTOS_IlhaKoch[i][0]) * cos( angle + PONTOS_IlhaKoch[i][1] );
			p2y = y1 + (d * PONTOS_IlhaKoch[i][0]) * sin( angle + PONTOS_IlhaKoch[i][1] );
			fractalRecursion( nivel - 1, p1x, p1y, p2x, p2y );
			p1x = p2x; p1y = p2y;
		}
		fractalRecursion( nivel - 1, p1x, p1y, x2, y2 );
		break;
	case menu_IlhaKochQuadrica: /*
		// Ilha de Koch quadrica
		float x = dist / 4;
		// P1 = (x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &start, start->x + x * cos( angle ), start->y + x * sin( angle ) );
		
		// P2 = (x*sqrt(2),angle + PI/4), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt2) * cos( angle + PI/4), start->y + (x * sqrt2) * sin( angle + PI/4) );
		
		// O triangulo retangulo (START,P3,P4) tem catetos x e 2x. Logo, pelo Teorema de Pitágoras, a hipotenusa vale x*sqrt5
		// O angulo no verticie START é igual a arctg(0.5) = 0.463647609 rad.
		// Portanto P3 = (x*sqrt5,angle + 0.463647609), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt5) * cos( angle + 0.463647609 ), start->y + (x * sqrt5) * sin( angle + 0.463647609 ) );
		
		// P4 = (2x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * 2) * cos( angle ), start->y + (x * 2) * sin( angle ) );
		
		// De maneira análoga à feita no P3, descobrimos que P5 = (x*sqrta5,angle - 0.463647609), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt5) * cos( angle - 0.463647609 ), start->y + (x * sqrt5) * sin( angle - 0.463647609 ) );
		
		// O triangulo retangulo (START,P7,P6) tem catetos 3x e x. Logo, pelo Teorema de Pitágoras, a hipotenusa vale x * sqrt2 * sqrt5
		// O angulo no verticie START é igual a arctg(1/3) = 0.321750554 rad.
		// Portanto P6 = (x*sqrt2*sqrt5,angle - 0.321750554), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * sqrt2 * sqrt5) * cos( angle - 0.321750554 ), start->y + (x * sqrt2 * sqrt5) * sin( angle - 0.321750554 ) );
		
		// P7 = (3x,angle), em Coordenadas polares, considerando START como (0,0)
		aux = newPointAfter( nivel, &aux, start->x + (x * 3) * cos( angle ), start->y + (x * 3) * sin( angle ) ); */
		break;
	}
}
void drawFractal( int nivel, int lados ) {
	glClear( GL_COLOR_BUFFER_BIT );
	glBegin( GL_LINE_STRIP );
	float x1 = raioFiguraBase, y1 = 0, x2, y2;
	int i;
	for( i = 1; i < lados; i++ ) {
		x2 = raioFiguraBase * cos( (-i) * (2 * PI / lados) );
		y2 = raioFiguraBase * sin( (-i) * (2 * PI / lados) );
		fractalRecursion( nivel - 1, x1, y1, x2, y2 );
		x1 = x2;
		y1 = y2;
	}
}

/* void drawFractal(void) {
	if( REDRAW == 0x00 ) return;
	glClear(GL_COLOR_BUFFER_BIT);
	if( startPoint == NULL ) return;
	glBegin( GL_LINE_STRIP );
	point p;
	for( p = startPoint; p != NULL; p = p->next ) {
		setColorFromNivel( p->nivel );
		glVertex2f( p->x + screenWidth / 2, p->y + screenHeight / 2);
	}
	setColorFromNivel( 1 );
	glVertex2f( startPoint->x + screenWidth / 2, startPoint->y + screenHeight / 2);
	glEnd();
	glFlush(); // Força desenhar a janela (Não apagar) 
	REDRAW = 0x00;
} */
void increaseRecursion(void) {
	nivelRecursao++; /*
	point cur = startPoint, next;
	while( cur != NULL ) {
		next = cur->next;
		fractalRecursion( cur, next );
		cur = next;
	}
	REDRAW = 0x01; */
}
void decreaseRecursion(void) {
	if( nivelRecursao <= 1 ) return;
	nivelRecursao--;
	point p, prev, aux;
	for( p = startPoint; p != NULL; p = aux ) {
		aux = p->next;
		if( nivelRecursao < p->nivel ) {
			free( p );
			if( prev == NULL ) { // p == startPoint
				startPoint = aux;
			} else {
				prev->next = aux;
			}
		} else prev = p;
	}
	REDRAW = 0x01;
}

void clearScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char ** argv) {
	// inicializa o ponto inicial
	startPoint = malloc(sizeof(pointStruct));
	if( startPoint == NULL ) {
		printf("Erro: Memoria insuficiente.\n");
		exit(1);
		return 1;
	}
	free(startPoint);
	startPoint = NULL;	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth,screenHeight);
	glutCreateWindow("EP2");
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE); 
	glLineWidth(1.5);
	glPointSize(1.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	createMenu();
	glutDisplayFunc(clearScreen);
	glutReshapeFunc(reshape);
	glutMainLoop(); /*O OpenGL passa a tomar controle total do programa*/
	return 0;
}