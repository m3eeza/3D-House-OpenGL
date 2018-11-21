#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <time.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

double r, g, b;
double MonsterX, MonsterY, MonsterZ = 0;
bool color;
void drawMonster();

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};


//front float eyeX = .5159011, float eyeY = .35505, float eyeZ = 2.731610,
//float centerX = .4992011, float centerY = .195151, float centerZ = .74462, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f)

//side .456471  .291530  .5189291  .48141   .086950   .604859

//top .4672312  .782390  .5102610  .4667321  .784150 .450984

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) 
		{
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void eyeright()
{
	//function for the right eye
	glPushMatrix();
	glTranslatef(.17, 1.1, .75);     //Specify the coordinates for the right eye
	glRotatef(-45, 0, 0, 1);
	glScalef(.9, .7, .7);            //Specify the size of the right eye
	glColor3f(1.0, 1.0, 1.0);       //Specify the color of the eye
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}
void eyeleft()
{
	glPushMatrix();
	glTranslatef(-.17, 1.1, .75);     //Specify the position for the left eye
	glRotatef(45, 0, 0, 1);
	glScalef(.9, .7, .7);
	glColor3f(1.0, 1.0, 1.0);
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}

void legleft()
{
	glPushMatrix();
	glTranslatef(.3, -.5, 0);     //Specify the position for the left leg
	glRotatef(-90.0, 1, 0, 0);
	glScalef(.8, .8, .8);
	gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
	glPopMatrix();
}

void legright()
{
	glPushMatrix();
	glTranslatef(-.3, -.5, 0);     //Specify the position for the right leg
	glRotatef(-90.0, 1, 0, 0);
	glScalef(.8, .8, .8);
	gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
	glPopMatrix();
}




void armleft()
{
	glPushMatrix();
	glTranslatef(-.82, 0, .1);     //Specify the position for the left arm
	glRotatef(90, 0, 1, 0);
	glRotatef(-50, 1, 0, 0);
	gluCylinder(gluNewQuadric(), .15, .15, .48, 30, 6);
	glPopMatrix();
}

void armright()
{
	glPushMatrix();
	glTranslatef(.82, 0, .1);      //Specify the position for the right arm
	glRotatef(90, 0, 1, 0);
	glRotatef(-130, 1, 0, 0);
	gluCylinder(gluNewQuadric(), .15, .15, .48, 30, 6);
	glPopMatrix();
}

void handleft()
{
	glPushMatrix();
	glTranslatef(.82, 0, .1);     //Specify the position for the left hand
	glScalef(.4, .3, .3);
	gluSphere(gluNewQuadric(), .4, 100, 100);
	glPopMatrix();
}






void handright()
{
	glPushMatrix();
	glTranslatef(-.82, 0, .1);    //Specify the position for the right hand
	glScalef(.4, .3, .3);
	gluSphere(gluNewQuadric(), .4, 100, 100);
	glPopMatrix();
}

void mouth()
{
	glPushMatrix();
	glTranslatef(0, .78, .74);
	glScalef(.4, .4, .1);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .4, 100, 100);
	glPopMatrix();
}

void teeth()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-.08, .72, .76);
	glTranslatef(.055, 0, .005);
	glutSolidCube(.035);
	glTranslatef(.055, 0, 0);
	glutSolidCube(.035);
	glPopMatrix();
}




void eyebrowleft()
{
	glPushMatrix();
	glTranslatef(-.3, 1.5, .97);;
	glRotatef(90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
	glPopMatrix();
}

void eyebrowright()
{
	glPushMatrix();
	glTranslatef(.3, 1.5, .97);
	glRotatef(270, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
	glPopMatrix();
}

void neckring()
{
	glPushMatrix();
	glTranslatef(0, .5, 0);
	glScalef(.59, .59, .59);
	glRotatef(90.0, 1, 0, 0);
	glutSolidTorus(.1, 1.0, 20, 20);
	glPopMatrix();
}




void head()
{
	glPushMatrix();
	glTranslatef(0, 1.2, 0);
	glScalef(.9, .9, .9);
	glColor3f(1.0, 0.8, 0.6);
	gluSphere(gluNewQuadric(), 1, 100, 100);
	glPopMatrix();
}

void hatmain()
{
	glPushMatrix();
	glTranslatef(0, 1.3, 0);
	glScalef(.98, .98, .98);
	gluSphere(gluNewQuadric(), .9, 100, 100);
	glPopMatrix();
}

void maintopball()
{
	glPushMatrix();
	glTranslatef(0, 2.2, 0);
	glScalef(.9, .9, .9);
	gluSphere(gluNewQuadric(), .18, 100, 100);
	glPopMatrix();
}







void hatring()
{
	glPushMatrix();
	glTranslatef(0, 1.4, 0);
	glScalef(.84, .84, .84);
	glRotatef(90.0, 1, 0, 0);
	glutSolidTorus(.1, 1.0, 20, 20);
	glPopMatrix();
}

void footleft()
{
	glPushMatrix();
	glTranslatef(-.3, -.5, 0);
	glScalef(1.5, .3, 1.5);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}

void footright()
{
	glPushMatrix();
	glTranslatef(.3, -.5, 0);
	glScalef(1.5, .3, 1.5);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}





void coatline()
{
	glPushMatrix();
	glTranslatef(0, .12, .67);
	glRotatef(-17.0, 1, 0, 0);
	glScalef(.05, .7, .1);
	glutSolidCube(1);
	glPopMatrix();
}

void bellyCoatbottom()
{
	glPushMatrix();
	glTranslatef(0, -.2, 0);
	glScalef(1, .7, 1);
	glRotatef(90.0, 1, 0, 0);
	gluDisk(gluNewQuadric(), 0, .8, 30, 30);
	glPopMatrix();
}

void BellyCoat()
{
	glPushMatrix();
	glTranslatef(0, .5, 0);
	glScalef(1, .7, 1);
	glRotatef(90.0, 1, 0, 0);
	gluCylinder(gluNewQuadric(), .6, .8, 1, 100, 100);
	glPopMatrix();
}





void pupilleft()
{
	glPushMatrix();
	glTranslatef(-.17, 1.1, .88);
	glScalef(.9, .9, .9);
	gluSphere(gluNewQuadric(), .1, 100, 100);
	glPopMatrix();
}

void pupilright()
{
	glPushMatrix();
	glTranslatef(.17, 1.1, .88);
	glScalef(.9, .9, .9);
	gluSphere(gluNewQuadric(), .1, 100, 100);
	glPopMatrix();
}

void topbutton()
{
	glPushMatrix();
	glTranslatef(-.1, .4, .85);
	glScalef(1.9, 1.9, 1.9);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}
void middlebutton()
{
	glPushMatrix();
	glTranslatef(-.1, .15, .98);
	glScalef(1.9, 1.9, 1.9);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}
void bottombutton()
{
	glPushMatrix();
	glTranslatef(-.1, -.1, .92);
	glScalef(1.9, 1.9, 1.9);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}
void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawJackPart() {
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}
void drawJack() {
	glPushMatrix();
	drawJackPart();
	glRotated(90.0, 0, 1, 0);
	drawJackPart();
	glRotated(90.0, 1, 0, 0);
	drawJackPart();
	glPopMatrix();
}
void drawTable(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void drawBed() {
	//bed base
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(1-r, g, b);
	glTranslated(0.25, 1.05, 0.25);
	glScaled(0.5, 0.1, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//matress
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.26, 1.11, 0.25);
	glScaled(0.42, 0.03, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//upper part
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, g, b);
	glTranslated(0.025, 1.1, 0.25);
	glScaled(0.05, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//lower part
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(1-r, g, b);
	glTranslated(0.5, 1.1, 0.25);
	glScaled(0.05, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawCommode() {

	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, 1-g, b);
	glTranslated(0.025, 1.1, 0.62);
	glScaled(0.1, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, 1-g, b);
	glTranslatef(0.08, 1.16, 0.62);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.075, 1.11, 0.62);
	glScaled(0.002, 0.002, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, 1-g, b);
	glTranslatef(0.08, 1.06, 0.62);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}
void drawVanity() {

	//base
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslated(0.75, 1.12, 0.035);
	glScaled(0.4, 0.2, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	//frame
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, g,1- b);
	glTranslated(0.75, 1.3, 0.035);
	glScaled(0.38, 0.5, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();

	//screen/mirror
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.75, 1.3, 0.036);
	glScaled(0.36, 0.48, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslatef(0.75, 1.2, 0.09);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.75, 1.175, 0.09);
	glScaled(0.38, 0.002, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.75, 1.125, 0.09);
	glScaled(0.38, 0.002, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.75, 1.075, 0.09);
	glScaled(0.38, 0.002, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslatef(0.75, 1.15, 0.09);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslatef(0.75, 1.1, 0.09);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslatef(0.75, 1.05, 0.09);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}

void drawCupboard() {

	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslated(0.025, 1.3, 0.85);
	glScaled(0.1, 0.6, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslatef(0.08, 1.30, 0.88);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.08, 1.3, 0.85);
	glScaled(0.002, 0.6, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.25, 0.1, 0);
	if (color)
		glColor3d(r, g, 1-b);
	glTranslatef(0.08, 1.30, 0.82);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();


}

void drawLowerKitchen() {
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, 1-g, 1-b);
	glTranslated(0.125, 0.3, 0.7);
	glScaled(0.25, 0.5, 0.6);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.25, 0.3, 0.85);
	glScaled(0.002, 0.5, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.25, 0.3, 0.70);
	glScaled(0.002, 0.5, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.25, 0.3, 0.55);
	glScaled(0.002, 0.5, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();




}

void drawFridge() {

	glPushMatrix();
	glColor3f(0.75, 0.75, 75);
	if (color)
		glColor3d(1-r,1- g, b);
	glTranslated(0.125, 0.3, 0.1);
	glScaled(0.3, 0.7, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.125, 0.42, 0.2);
	glScaled(.3, 0.002, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.125, 0.4, 0.2);
	glScaled(.3, 0.002, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();




}

void drawLamp() {

	//upper
	glPushMatrix();
	glColor3f(1, 0, 0);
	if (color)
		glColor3d(1-r, g, 1-b);
	glTranslatef(0.025, 1.3, 0.62);
	glRotated(-90, 1, 0, 0);
	glScalef(0.3, .5, .5);
	gluCylinder(gluNewQuadric(), 0.1, .04, 0.1, 100, 100);
	glPopMatrix();

	//middle
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.025, 1.25, 0.62);
	glScaled(0.002, 0.15, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

}

void drawChair() {

	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, g, b);
	glTranslated(0.8, 0.0, 0.6);
	drawTable(0.15, 0.02, 0.02, 0.22);
	glPopMatrix();

}

void drawStoove() {

	glPushMatrix();
	glColor3f(0.75, 0.75, 0.75);
	if (color)
		glColor3d(r, g, b);
	glTranslated(0.6, 0.3, 0.125);
	glScaled(0.4, 0.5, 0.25);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.6, 0.3, 0.25);
	glScaled(0.3, 0.3, 0.002);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.7, .5, 0.25);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.65, .5, 0.25);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.6, .5, 0.25);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.55, .5, 0.25);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.5, .5, 0.25);
	glScalef(0.3, .3, .3);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.5, .55, 0.075);
	glScalef(0.75, .01, .75);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.5, .55, 0.175);
	glScalef(0.75, .01, .75);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.7, .55, 0.075);
	glScalef(0.75, .01, .75);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.7, .55, 0.175);
	glScalef(0.75, .01, .75);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.1, 0.1);
	if (color)
		glColor3d(r, g, b);
	glTranslated(0.7, 0.58, 0.175);
	glRotated(30, 0, 1, 0);
	glutSolidTeapot(0.04);
	glPopMatrix();
}
void Display() {
	setupCamera();
	setupLights();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Monster
	glPushMatrix();
	glTranslated(MonsterX, MonsterY, MonsterZ);
	drawMonster();
	glPopMatrix();


	
	glPushMatrix();
	glColor3d(r, g, b);

	drawChair();
	glPushMatrix();
	glColor3f(0.3, 0.1, 0);
	if (color)
		glColor3d(r, g, b);
	glTranslated(0.5, 0.0, 0.6);
	drawTable(0.4, 0.02, 0.02, 0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	if (color)
		glColor3d(r, g, b);
	drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.1, 0);
	if (color)
		glColor3d(r, g, b);
	glRotated(90, 0, 0, 1.0);
	drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.1, 0);
	if (color)
		glColor3d(r, g, b);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.1);
	if (color)
		glColor3d(r, g, b);
	//glRotated(180, 0.0, 1.0, 0.0);
	glTranslated(0, 1, 0);
	drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
	if (color)
		glColor3d(r, g, b);
	glColor3f(0, 0, 0.1);
	glTranslated(0, 1, 0);
	glRotated(90, 0, 0, 1.0);
	drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
	if (color)
		glColor3d(r, g, b);
	glColor3f(0, 0, 0.1);
	glTranslated(0, 1, 0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();

	drawBed();
	drawCommode();
	drawVanity();
	drawCupboard();
	drawLowerKitchen();
	drawStoove();
	drawLamp();
	drawFridge();

	glColor3d(r, g, b);

	glPopMatrix();


	glFlush();
}

void drawMonster() {
	glPushMatrix();
	//glTranslatef(0.5, 1.5, 0.5);
	glScaled(0.1, 0.1, 0.1);
	eyeright();
	eyeleft();
	glColor3f(0.0, 0.0, 1.0);
	legleft();
	legright();
	hatmain();
	glColor3ub(160, 82, 45);
	armleft();
	armright();
	mouth();
	teeth();
	eyebrowleft();
	eyebrowright();
	head();
	glColor3f(1.0, 0.0, 0.0);
	maintopball();
	hatring();
	neckring();
	handleft();
	handright();
	glColor3f(0.0, 0.0, 0.0);
	footleft();
	footright();
	coatline();
	pupilleft();
	pupilright();
	glColor3ub(160, 82, 45);
	BellyCoat();
	bellyCoatbottom();
	glPopMatrix();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 't':
		camera.eye.x = .4672312;
		camera.eye.y = .782390;
		camera.eye.z = .5102610;
		camera.center.x = .4667321;
		camera.center.y = .784150;
		camera.center.z = .450984;
		break;
	case 'x':
		camera.eye.x = .456471;
		camera.eye.y = .291530;
		camera.eye.z = .5189291;
		camera.center.x = .48141;
		camera.center.y = .086950;
		camera.center.z = .604859;
		break;
	case 'f':
		camera.eye.x = 0.4840711;
		camera.eye.y = .00852;
		camera.eye.z = .47914;
		camera.center.x = 0.4755790;
		camera.center.y = .9334561;
		camera.center.z = .482;
		camera.up.x = 0.0002824910;
		camera.up.y = .99718;
		camera.up.z = -0.0750472;
		break;
	case 'c':
		color = !color;
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);

	}

	/*std::cout << camera.up.x << camera.up.y << camera.up.z << "up\n";
	std::cout << camera.eye.x << camera.eye.y << camera.eye.z << "eye\n";
	std::cout << camera.center.x << camera.center.y << camera.center.z << "center\n"*/;

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void anim() {
	/*MonsterX = (rand() % 10)/10;
	MonsterY = (rand() % 20)/10;
	MonsterZ = (rand() % 10)/10;

	std::cout << MonsterX << MonsterY << MonsterZ;
	glutPostRedisplay();*/						// redraw 		
}
void timer(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	MonsterX = (rand() % 10 + 1) / 10.0;
	MonsterY = (rand() % 20 + 1) / 10.0;
	MonsterZ = (rand() % 10 + 1) / 10.0;
	if (color) {
		r = (rand() % 10 + 1) / 10.0;
		g = (rand() % 10 + 1) / 10.0;
		b = (rand() % 10 + 1) / 10.0;
		std::cout << r << g << b;
	}
	glutPostRedisplay();						// redraw 		
	glutTimerFunc(1000, timer, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	srand(time(NULL));
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutIdleFunc(anim);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glutTimerFunc(0, timer, 0);		//call the timer function
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
