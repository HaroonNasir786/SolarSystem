#include "SolarSystem.h"
#include "Texture.h"

SolarSystem::SolarSystem(int argc, char* argv[])
{
	InitGL(argc, argv);

	Setup();

	glutMainLoop();
}

void SolarSystem::InitGL(int argc, char* argv[])
{
	
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Solar System");

	glutDisplayFunc(GLUTCallbacks::Render);
	glutReshapeFunc(GLUTCallbacks::ResizePlanets);
	glutIdleFunc(GLUTCallbacks::Idle);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMouseWheelFunc(GLUTCallbacks::MouseWheel);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 1, 1000);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

SolarSystem::~SolarSystem()
{

}

void SolarSystem::Menu(const char* str, float size)
{
	glPushMatrix();
	glScalef(size, size, size);

	for (int i = 0; i < strlen(str); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();

}

void SolarSystem::Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														 // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(0, 0, -100);

	if (!animation) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glColor3f(1, 1, 1);
		glTranslatef(-45, 50, 0.0);
	    Menu("Press Space Bar to START/PAUSE", 0.04f);
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLUquadricObj* quadric; //Loading Planet Object
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	gluQuadricTexture(quadric, GL_TRUE);

	glScalef(scaleFactor, scaleFactor, scaleFactor);

	glRotatef(worldX, 1, 0, 0);
	glRotatef(worldY, 0, 1, 0);

	glDisable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, sunTex->GetID());
	glPushMatrix(); //Sun
	gluSphere(quadric, 15, 36, 18);
	glEnable(GL_BLEND);
	glBlendFunc(first, second);
	gluSphere(quadric, 20, 36, 18);
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0, 0.0, 0.0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);

	LoadPlanets();

	DrawStars();


	glutSwapBuffers();             // All drawing commands applied to the 
								   // hidden buffer, so now, bring forward
								   // the hidden buffer and hide the visible one
}

void SolarSystem::LoadPlanets() // loading planets
{
	GLUquadricObj* quadric; //Loading Planet Object
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	gluQuadricTexture(quadric, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D, marsTex->GetID());
	glPushMatrix(); // Mars planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(40, 0, -10.0);
	glRotatef(rotation, 1, 0, 0);
	gluSphere(quadric, 5, 36, 18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, mercuryTex->GetID());
	glPushMatrix(); // mercury planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(10, 0, -30.0);
	glRotatef(rotation, 1, 0, 0);
	gluSphere(quadric, 5, 36, 18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, plutoTex->GetID());
	glPushMatrix(); // pluto planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(20, 0, -100.0);
	glRotatef(rotation, 1, 0, 0);
	gluSphere(quadric, 5, 36, 18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, earthTex->GetID());
	glPushMatrix();// earth planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(-20, 0.0, -70);
	glRotatef(rotation, 0, 0, 1);
	gluSphere(quadric, 10, 36, 18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, jupitarTex->GetID());
	glPushMatrix();// jupitar planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(-60, 0, 0.0);
	glRotatef(rotation, 1, 0, 0);
	gluSphere(quadric, 17, 36, 18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, uranusTex->GetID());
	glPushMatrix();// Uranus planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(20, 0, 44.0);
	glRotatef(rotation, 1, 0, 0);
	gluSphere(quadric, 11, 36, 18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, neptuneTex->GetID());
	glPushMatrix();// neptune planet
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(60, 0, 10.0);
	glRotatef(rotation, 1, 0, 0);
	gluSphere(quadric, 11, 36, 18);
	glPopMatrix();

}

void SolarSystem::ResizePlanets(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	globalH = h;
	globalW = w;

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 1000.0);
}

void SolarSystem::Setup()
{
	LoadTexture(); 

	//get random cordinates for the stars
	for (int i = 0; i < 500; i++)
		StarCoordinates(&stars[i]);
	srand(time(0));
	//Parameter handling
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SolarSystem::LoadTexture() // loading textures
{
	sunTex = new Texture();
	sunTex->Load((char*)"sun.raw", 128, 128);

	earthTex = new Texture();
	earthTex->Load((char*)"earth.raw", 128, 128);

	jupitarTex = new Texture();
	jupitarTex->Load((char*)"jupiter.raw", 128, 128);

	marsTex = new Texture();
	marsTex->Load((char*)"mars.raw", 1000, 500);

	uranusTex = new Texture();
	uranusTex->Load((char*)"uranus.raw", 128, 128);

	neptuneTex = new Texture();
	neptuneTex->Load((char*)"neptune.raw", 128, 128);

	plutoTex = new Texture();
	plutoTex->Load((char*)"pluto.raw", 128, 128);

	mercuryTex = new Texture();
	mercuryTex->Load((char*)"mercury.raw", 128, 128);
}

void SolarSystem::Idle()
{
	if (animation)
		rotation += 1.1;

	glutPostRedisplay();
}


void SolarSystem::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': exit(0);
		break;
	case 'w': if (key = animation) worldX -= 1.0f;
		break;
	case 's': if (key = animation) worldX += 1.0f;
		break;
	case 'a': if (key = animation) worldY -= 1.0f;
		break;
	case 'd': if (key = animation)  worldY += 1.0f;
		break;
	case 'Q': exit(0);
		break;
	case 'W': if (key = animation) worldX -= 1.0f;
		break;
	case 'S': if (key = animation) worldX += 1.0f;
		break;
	case 'A': if (key = animation) worldY -= 1.0f;
		break;
	case 'D': if (key = animation)  worldY += 1.0f;
		break;
	case ' ': animation = !animation;;
		break;
	default: break;
	}
	glutPostRedisplay();
}

void SolarSystem::MouseWheel(int button, int dir, int x, int y)
{

	if (animation) {
		if (dir > 0) {
			scaleFactor += 0.01;
			glutPostRedisplay();
		}
		else {
			if (scaleFactor > 0.08) {
				scaleFactor -= 0.01;
				glutPostRedisplay();
			}
		}
	}
}

void SolarSystem::StarCoordinates(point *star)
{
	int lowest = -1000, highest = 1000;
	int range = (highest - lowest) + 1;
	star->x = lowest + int(range * rand() / (RAND_MAX + 1.0));
	star->y = lowest + int(range * rand() / (RAND_MAX + 1.0));
	star->z = lowest + int(range * rand() / (RAND_MAX + 1.0));
}

void SolarSystem::DrawStars()
{
	GLUquadricObj* quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	for (int i = 0; i < 500; i++) {
		glPushMatrix();
		glTranslatef(stars[i].x, stars[i].y, stars[i].z);
		glColor3f(1, 1, 1);
		gluSphere(quadric, 1, 36, 18);
		glPopMatrix();
	}
}
