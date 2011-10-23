/* * * * * * * * * * * * * * * * * * * * * * * * * 
 * EP2 - Simulador de Voo                       *
 *                                               *
 * Henrique Geminiani Passos - NUSP: 6879634     * 
 * Luciana dos Santos Kayo - NUSP: 6430992       * 
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */ 



#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include "island.h"
#include "ocean.h"
#include "airplane.h"

Ocean *ocean;
Island *island;
Airplane **airplanes; // Vetor com todos os avioes do programa
int num_planes;
int active_plane = 0; // Aviao a partir do qual vemos o resto da cena
int view_mode = 0;
GLfloat ratio, camx = 30.0f, camz = 8.0f;
float dx, dy;
float off = 0;
bool paused = false;

// Define brilho, fontes de luz e reflectancia
void DefineLuz(void) {
    GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
    GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat LuzEspecular[] = {0.626281f, 0.555802f, 0.366065f, 1.0f };
    GLfloat PosicaoLuz0[]  = {-40.0f,-40.0f, 100.0f, 1.0f };
    GLfloat PosicaoLuz1[]  = { 40.0f, 40.0f, 100.0f, 1.0f };
    GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f };

    // Fonte de Luz 0
	glEnable ( GL_COLOR_MATERIAL );
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,51);

  // Fonte de Luz 1
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,20);
}

void init(void) {
    glClearColor(0.5f, 1.0f, 0.83f, 1.0f); // Fundo de tela preto

    glShadeModel(GL_SMOOTH);
    glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_DEPTH_TEST);
    glEnable ( GL_CULL_FACE );

}

// Define a posicao atual como a do aviao ativo
void PosicUser() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,ratio,0.01,1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    airplanes[active_plane]->Camera(view_mode);
    // gluLookAt( -50, -50, 50,
		       // 0, 0, 0,
		       // 0, 0, 1 );

}

void reshape( int w, int h ) {
    if(h == 0) h = 1;
    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h);
    PosicUser();
}

// Mostra cena e avioes na tela
void display( void ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
    DefineLuz();

    PosicUser();

    glMatrixMode(GL_MODELVIEW);
    ocean->Render();
    island->Render();
    for(int i = 0; i < num_planes; i++)
	    airplanes[i]->Render();
    glutSwapBuffers();
}

// Atualiza pposicao e rotacao do aviao ativo
void update( int a ) {
    glutTimerFunc( 16, update, 1 );
    if(paused) return;
    airplanes[active_plane]->UpdateRot(Vector3D(dy,dx,0));
    airplanes[active_plane]->Update();
    display();
}

void keyboard ( unsigned char key, int x, int y ) {
    switch ( key )
    {
    case 'q':
    case 27:        // Termina o programa qdo
	    delete ocean;
	    delete island;
	    for(int i = 0; i < num_planes; i++)
		    delete airplanes[i];
	    delete airplanes;
	    exit ( 0 );   // a tecla ESC for pressionada
	    break;
    case 'a':
	    airplanes[active_plane]->UpdateVelocity(+0.25f);
	    break;
    case 's':
	    airplanes[active_plane]->UpdateVelocity(-0.25f);
	    break;
    case 'v':
	    active_plane = (active_plane + 1) % num_planes;
	    break;
    case 'z':
	    airplanes[active_plane]->UpdateRotVelocity(Vector3D(0,0,-.2));
	    break;
    case 'c':
	    airplanes[active_plane]->UpdateRotVelocity(Vector3D(0,0,.2));
	    break;
    case 'x':
	    airplanes[active_plane]->StopRotVelocity();
	    break;
    case 'd':
	    airplanes[active_plane]->Dump();
	    break;
    case 'b':
	    view_mode = (view_mode + 1) % 3;
	    break;
    case 'p':
	    paused = !paused;
	    break;
    default:
	    break;
  }
}

void arrow_keys ( int a_keys, int x, int y ) {
    switch ( a_keys )
    {
    case GLUT_KEY_PAGE_UP:
	    airplanes[active_plane]->UpdateRot(Vector3D(0,0,+1));
	    break;
    case GLUT_KEY_PAGE_DOWN:
	    airplanes[active_plane]->UpdateRot(Vector3D(0,0,-1));
	    break;
    default:
	    break;
    }
}

static void mouse(int x, int y) {
    dx = (x - 350) / 350.0f;
    dy = (y - 250) / 250.0f;
}

int main ( int argc, char** argv ) {
    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );// | GLUT_STEREO);// | GLUT_DOUBLE | GLUT_RGBA );

    glutInitWindowPosition (0,0);
    glutInitWindowSize  ( 700, 500 );
    glutCreateWindow    ( "Computação Gráfica - EP Básico 3D" );

    FILE *input = fopen("input.txt", "r");
    int ocean_minx, ocean_miny, ocean_maxx, ocean_maxy;
    int island_minx, island_miny, island_maxx, island_maxy;
    char buffer[1024];

    fscanf(input, "%d %d %d %d", &ocean_minx, &ocean_maxx, &ocean_miny, &ocean_maxy);
    fscanf(input, "%d %d %d %d", &island_minx, &island_maxx, &island_miny, &island_maxy);
    fscanf(input, "%s", buffer);

    ocean = new Ocean(ocean_minx, ocean_miny, ocean_maxx, ocean_maxy);
    island = new Island(island_minx, island_miny, island_maxx, island_maxy, buffer);

    fscanf(input, "%d", &num_planes);
    airplanes = new Airplane*[num_planes];
    for(int i = 0; i < num_planes; i++) {
	    int x, y, z, rotx, roty, rotz, vel;
	    fscanf(input, "%d %d %d", &x, &y, &z);
	    fscanf(input, "%d %d %d %d", &rotx, &roty, &rotz, &vel);
	    airplanes[i] = new Airplane(Vector3D(x,y,z), Vector3D(-rotx,-roty,-rotz), vel);
    }

    fclose(input);

    fprintf(stdout, "ocean: (minx %d, miny %d, maxx %d, maxy %d)\n", ocean_minx, ocean_miny, ocean_maxx, ocean_maxy);
    fprintf(stdout, "island: (minx %d, miny %d, maxx %d, maxy %d)\n%s\n", island_minx, island_miny, island_maxx, island_maxy, buffer);

    init ();

    glutDisplayFunc ( display );
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutSpecialFunc ( arrow_keys );
    glutTimerFunc( 16, update, 1 );
    glutPassiveMotionFunc (mouse);
    //glutIdleFunc ( display );

    glutMainLoop ( );
    return 0;
}




