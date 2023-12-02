#include <time.h>
#include <cmath>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glut.h>
#include <iostream> // Include necessary headers




//  Methods Signatures
void print(int x, int y, char* string);
void Display();
void main(int argc, char** argr);
void drawCircle(int x, int y, float r);
void drawRedCircle(float r);
void SpecialKeys(int key, int x, int y);
void drawRect(int x, int y, int w, int h);
void drawGradientRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawFrameBorder();
void drawGreenPig(float x, float y);
int  RandomNum(int min, int max);
void drawCoinGold(int x, int y);
void drawAidBox(int x, int y);
void drawFlag(int x, int y);
void writeTime();
void drawBomb(float x, float y, bool isVisible);
void displayGameOver();
void generateRandomCoordinatesCoin(int index);
void generateRandomCoordinatesAidBox(int index);
void generateRandomPigCoordinates(int index);
bool isCollisionWithCenter(float x, float y);
bool isCollisionWithCoin(float x, float y);
bool isCollisionWithBomb(float x, float y);
bool isCollisionWithAidBox(float x, float y);
bool isCollisionWithFlag(float x, float y);
void displayGameWon();
void drawCloud(int x, int y);
void writeTimeCoin();
void writeTimeAidBox();

//gloabl variable init
int charX = 500;//character initial point x
int charY = 300;//character initial point y
//int x = 400;
//int y = 400;
int startTime = 60;
int startTimeCoin = 0;
int startTimeAidBox = 0;
int score = 0;
int healthBarWidth = 250;
bool CoinCollected = false;//checks if coin power up was collected
bool AidBoxCollected = false;//checks if coin power up was collected
bool showFlag = false;
int CollidedCoinX;//x of coin i collided with
int CollidedCoinY;//y of coin i collided with
int CollidedAidBoxX;//x of aidBox i collided with
int CollidedAidBoxY;//y of aidBox i collided with
int  goldCoinTimer = -1; // Timer for gold coin effect, -1 means inactive


float coinCoordinates[1][2]; // Holds the coordinates for two coins
float aidBoxCoordinates[1][2]; // Holds the coordinates for two coins
float pigCoordinates[5][2]; // Holds the coordinates for five pigs

float bombCoordinates[5][2] = {
  {300, 300},
  {500, 30},
  {700, 350},
  {500, 400},
  {100, 200}
};







void displayGameOver() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);//red
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); // white color
	glRasterPos2f(400, 300); // Position for the text

	const char* gameOverText = "YOU LOST! HAHA";
	for (const char* c = gameOverText; *c; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glFlush();
}

void displayGameWon() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);//green
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); // white color
	glRasterPos2f(400, 300); // Position for the text
	const char* gameOverText = "YOU WON! WOW";
	for (const char* c = gameOverText; *c; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glFlush();
}


//this is the method used to print text in OpenGL
//there are three parameters,
//the first two are the coordinates where the text is display,
//the third coordinate is the string containing the text to display
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}



void Display() {
	//glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);

	if (score >= 50) {
		drawFlag(850, 100);
		showFlag = true;
	}
	//check if they lost
	if (healthBarWidth <= 0) {
		displayGameOver();
	}
	else if (isCollisionWithFlag(charX, charY) && showFlag) {
		displayGameWon();


	}
	else {
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", score);
		print(450, 550, (char*)p0s);

		drawRedCircle(20);

		drawFrameBorder();
		drawCloud(300, 400);
		//drawGreenPig(500, 500);
		//drawCoinGold(300, 500);
		//drawAidBox(400, 400);

		// Draw bombs
		for (int i = 0; i < 5; i++) {
			float x = bombCoordinates[i][0];
			float y = bombCoordinates[i][1];
			drawBomb(x, y, true);
		}
		// Draw coins randomlyy
		for (int i = 0; i < 1; i++) {
			float coinX = coinCoordinates[i][0];
			float coinY = coinCoordinates[i][1];
			drawCoinGold(coinX, coinY);
		}
		// Draw aid boxes randomlyy
		for (int i = 0; i < 1; i++) {
			float aidBoxX = aidBoxCoordinates[i][0];
			float aidBoxY = aidBoxCoordinates[i][1];
			drawAidBox(aidBoxX, aidBoxY);
		}
		// Draw pigs
		for (int i = 0; i < 5; i++) {
			float pigX = pigCoordinates[i][0];
			float pigY = pigCoordinates[i][1];
			drawGreenPig(pigX, pigY);
		}



		// Draw two rectangles on top of the page
		glColor3f(1.0f, 1.0f, 1.0f);
		drawGradientRect(28, 550, healthBarWidth, 30);//First rectangle

		glColor3f(1.0f, 1.0f, 1.0f);
		drawRect(720, 550, 270, 30);//Second rectangle

		// Display time in Second rectangle
		glColor3f(1.0f, 1.0f, 1.0f);

		glColor3f(0.00, 0.00, 0.00);

		writeTime();
		if (CoinCollected) {
			writeTimeCoin();
		}
		if (AidBoxCollected) {
			writeTimeAidBox();
		}
	}



	glFlush();
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);
	srand(time(0)); // Seed the random number generator with the current time

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	generateRandomCoordinatesCoin(0);
	generateRandomCoordinatesCoin(1);
	generateRandomCoordinatesAidBox(0);
	generateRandomCoordinatesAidBox(1);
	for (int i = 0; i < 5; i++) {
		generateRandomPigCoordinates(i);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1000, 0.0, 600);
	// Get  start time
	startTime = glutGet(GLUT_ELAPSED_TIME);
	// Generate the pigs once at the start of the game
	//RandomPigs();
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();
}

void drawFrameBorder() {
	glColor3f(0.5f, 0.5f, 0.5f); // Set color to grey

	// Set line width to make it thicker
	glLineWidth(5.0f); // Adjust the line width as needed

	// Draw the rectangle using GL_LINE_LOOP
	glBegin(GL_LINE_LOOP);
	glVertex2f(5, 5); // Bottom-left corner
	glVertex2f(995, 5); // Bottom-right corner
	glVertex2f(995, 530); // Top-right corner
	glVertex2f(5, 530); // Top-left corner
	glEnd();

	// Reset line width to default
	glLineWidth(1.0f);

	// Draw circles at the corners using your drawCircle function
	float circleRadius = 5.0f; // Adjust the radius as needed
	drawCircle(5, 5, circleRadius);
	drawCircle(995, 5, circleRadius);
	drawCircle(995, 530, circleRadius);
	drawCircle(5, 530, circleRadius);
}

void writeTime() {
	char* p0s[20];
	// Calculate remaining time in seconds
	int remainingTime = 60 - (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000;

	// Check if time has run out
	if (remainingTime <= 0) {
		remainingTime = 0; // stop the remaining time at 0 seconds
		displayGameOver();
	}

	// Convert remaining time to a string
	char remainingTimeStr[10];
	sprintf(remainingTimeStr, "%02d:%02d", remainingTime / 60, remainingTime % 60);

	// Display the time in the second rectangle
	glColor3f(0.0f, 0.0f, 0.0f);
	print(810, 555, remainingTimeStr);
	sprintf((char*)p0s, "Time:");
	print(750, 555, (char*)p0s);
}

void writeTimeCoin() {
	char* p0s[20];
	// Calculate remaining time in seconds only when CoinCollected is true
	int remainingTime = 0;
	if (CoinCollected) {
		remainingTime = 15 - (glutGet(GLUT_ELAPSED_TIME) - startTimeCoin) / 1000;
		// Check if time has run out
		if (remainingTime <= 0) {
			remainingTime = 0; // Stop the remaining time at 0 seconds
			CoinCollected = false;
		}
	}

	// Convert remaining time to a string
	char remainingTimeStr[10];
	sprintf(remainingTimeStr, "%02d:%02d", remainingTime / 60, remainingTime % 60);

	// Display the time in the second rectangle
	glColor3f(0.0f, 1.0f, 0.0f);
	print(870, 555, remainingTimeStr);
	sprintf((char*)p0s, "Time:");
	glColor3f(0.0f, 0.0f, 0.0f);
	print(750, 555, (char*)p0s);
}

void writeTimeAidBox() {
	char* p0s[20];
	// Calculate remaining time in seconds only when AidBoxCollected is true
	int remainingTime = 0;
	if (AidBoxCollected) {
		remainingTime = 15 - (glutGet(GLUT_ELAPSED_TIME) - startTimeAidBox) / 1000;
		// Check if time has run out
		if (remainingTime <= 0) {
			remainingTime = 0; // Stop the remaining time at 0 seconds
			AidBoxCollected = false;
			//return bombs as they were
			bombCoordinates[0][0] = 300;
			bombCoordinates[0][1] = 300;
			bombCoordinates[1][0] = 500;
			bombCoordinates[1][1] = 30;
			bombCoordinates[2][0] = 700;
			bombCoordinates[2][1] = 350;
			bombCoordinates[3][0] = 500;
			bombCoordinates[3][1] = 400;
			bombCoordinates[4][0] = 100;
			bombCoordinates[4][1] = 200;



		}
	}

	// Convert remaining time to a string
	char remainingTimeStr[10];
	sprintf(remainingTimeStr, "%02d:%02d", remainingTime / 60, remainingTime % 60);

	// Display the time in the second rectangle
	glColor3f(0.0f, 0.0f, 1.0f);
	print(930, 555, remainingTimeStr);
	sprintf((char*)p0s, "Time:");
	glColor3f(0.0f, 0.0f, 0.0f);
	print(750, 555, (char*)p0s);
}

//void writeTimeCoin() {
//	char* p0s[20];
//
//	if (CoinCollected) {
//		startTimeCoin = glutGet(GLUT_ELAPSED_TIME);
//	}
//
//	// Calculate remaining time in seconds
//	int remainingTime = 15 - (CoinCollected ? (glutGet(GLUT_ELAPSED_TIME) - startTimeCoin) : 0) / 1000;
//
//	// Check if time has run out
//	if (remainingTime <= 0) {
//		remainingTime = 0; // stop the remaining time at 0 seconds
//		CoinCollected = false;
//	}
//
//	// Convert remaining time to a string
//	char remainingTimeStr[10];
//	sprintf(remainingTimeStr, "%02d:%02d", remainingTime / 60, remainingTime % 60);
//
//	// Display the time in the second rectangle
//	glColor3f(0.0f, 1.0f, 0.0f);
//	print(880, 555, remainingTimeStr);
//	sprintf((char*)p0s, "Time:");
//	glColor3f(0.0f, 0.0f, 0.0f);
//	print(750, 555, (char*)p0s);
//}



void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}


void SpecialKeys(int key, int x, int y) {

	// Check if character collides with any pig
	for (int i = 0; i < 5; i++) {
		float pigX = pigCoordinates[i][0];
		float pigY = pigCoordinates[i][1];
		float pigRadius = 20; // Adjust as needed
		float characterRadius = 20;

		float dx = charX - pigX;
		float dy = charY - pigY;
		float distance = sqrt(dx * dx + dy * dy);

		if (distance < (pigRadius + characterRadius)) {
			// Collision detected with a pig
			if (CoinCollected) {
				score += 20; // Increase the score by double becuz of coin powerup
			}
			else {
				score += 10; // Increase the score

			}

			pigCoordinates[i][0] = -1000; // Make the pig's position invalid
			break; // No need to check for other pigs
		}
	}

	switch (key) {
	case GLUT_KEY_LEFT:
		if (charX >= 40) {
			charX -= 10;
		}
		else {
			healthBarWidth = healthBarWidth - 50;

		}
		break;
	case GLUT_KEY_RIGHT:
		if (charX <= 960) {
			charX += 10;

		}
		else {
			healthBarWidth = healthBarWidth - 50;
		}
		break;
	case GLUT_KEY_UP:
		if (charY <= 500) {
			charY += 10;

		}
		else {
			healthBarWidth = healthBarWidth - 50;
		}
		break;

	case GLUT_KEY_DOWN:
		if (charY >= 40) {
			charY -= 10;

		}
		else {
			healthBarWidth = healthBarWidth - 50;
		}
		break;
	}


	if (isCollisionWithBomb(charX, charY)) {
		//bombCoordinates[i][0] = -1000;
		healthBarWidth = healthBarWidth - 50;
		charX = 500;
		charY = 300;
	}
	if (isCollisionWithCoin(charX, charY)) {
		CoinCollected = true;
		startTimeCoin = glutGet(GLUT_ELAPSED_TIME);

		for (int i = 0; i < 2; i++) {
			float coinsX = coinCoordinates[i][0];
			float coinsY = coinCoordinates[i][1];
			if (coinsX == CollidedCoinX && coinsY == CollidedCoinY) {
				coinCoordinates[i][0] = -1000;
				break;
			}


		}
	}
	if (isCollisionWithAidBox(charX, charY)) {
		AidBoxCollected = true;

		startTimeAidBox = glutGet(GLUT_ELAPSED_TIME);

		for (int i = 0; i < 2; i++) {
			float aidBoxX = aidBoxCoordinates[i][0];
			float aidBoxY = aidBoxCoordinates[i][1];
			if (aidBoxX == CollidedAidBoxX && aidBoxY == CollidedAidBoxY) {
				aidBoxCoordinates[i][0] = -1000;
				// Set all bomb x-coordinates to -1000
				for (int j = 0; j < 5; j++) {
					bombCoordinates[j][0] = -1000;
				}
				break;
			}


		}
	}

	glutPostRedisplay();
}


// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x1 / 2.0f, y1 / 2.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x2 / 2.0f, y2 / 2.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x3 / 2.0f, y3 / 2.0f, 0.0f);
	glEnd();
}


// draws health bar rectangle using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawGradientRect(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(x, y);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x + w, y);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x + w, y + h);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(x, y + h);
	glEnd();
}

void drawGreenPig(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f); // Translate to the specified position
	glScalef(0.25f, 0.25f, 0.25f);


	// Calculate the rotation angle based on time (slower rotation)
	float rotationAngle = glutGet(GLUT_ELAPSED_TIME) / 5000.0f * 360.0f;

	// Apply rotation around the z-axis (out of screen)
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

	// Draw body
	glColor3f(0.0f, 1.0f, 0.1647f);
	drawCircle(0, 0, 75);

	// Draw ears
	glColor3f(0.0f, 1.0f, 0.0f); // Green color for the ears
	drawCircle(-25, 75, 15); // Left ear
	drawCircle(25, 75, 15); // Right ear

	// Draw eyes
	glTranslatef(25.0f, 18.0f, 0.0f); // move the eyes to the right and up
	glColor3f(1.0f, 1.0f, 1.0f); // White color for the eyes
	drawCircle(-60, 19, 13);
	drawCircle(25, 19, 13);
	glColor3f(0.0f, 0.0f, 0.0f); // Black color for the pupils
	drawCircle(-60, 19, 6);
	drawCircle(25, 19, 6);

	// Draw snout
	glTranslatef(5.0f, 10.0f, 0.0f); // move the snout to the right and up
	glColor3f(0.0f, 0.6f, 0.0f);
	drawCircle(-20, -25, 25);

	// Draw nostrils
	glTranslatef(-5.0f, 0.0f, 0.0f); // move to the nostrils' position
	glColor3f(0.0f, 0.0f, 0.0f); // Black color for the nostrils
	drawCircle(-26, -30, 6.5);
	drawCircle(3, -30, 6.5);

	glPopMatrix();
}

// Function to generate a random num in the range [min, max]
int RandomNum(int min, int max) {
	return min + rand() % (max - min + 1);
}




void drawCoinGold(int x, int y) {
	int r = 10;
	// Draw the slightly bigger gold circle
	glColor3f(1.0f, 0.84f, 0.0f); // Gold color
	drawCircle(x, y, 15); // Slightly bigger radius
	// Draw the smaller circle
	glColor3f(0.9f, 0.7f, 0.0f); // Slightly darker gold color
	drawCircle(x, y, 10); // Slightly bigger radius

	// Calculate the rotation angle based on time (slower rotation)
	float rotationAngle = glutGet(GLUT_ELAPSED_TIME) / 5000.0f * 360.0f;

	// Save the current transformation matrix
	glPushMatrix();

	// Translate to the center of the coin
	glTranslatef(x, y, 0.0f);

	// Rotate the coin around itself at the specified angle
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

	// Draw the dark plus sign
	glColor3f(0.2f, 0.2f, 0.2f); // Dark gray color
	glBegin(GL_LINES);
	glVertex2f(-r / 2, 0.0f);
	glVertex2f(r / 2, 0.0f);
	glVertex2f(0.0f, -r / 2);
	glVertex2f(0.0f, r / 2);
	glEnd();

	// Restore the previous transformation matrix
	glPopMatrix();
	glutPostRedisplay(); // redraw of the window at each frame
}

void drawAidBox(int x, int y) {
	int w = 20; // Width of the rectangles
	int h = 40; // Height of the rectangles

	// Draw the outer dark green rectangle
	glColor3f(0.0f, 0.5f, 0.0f); // Dark green color
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	float rotationAngle = glutGet(GLUT_ELAPSED_TIME) / 2000.0f * 360.0f;
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate in place
	drawRect(-w / 2, -h / 2, w, h);
	glPopMatrix();

	// Draw the inner light green rectangle (rotating together)
	glColor3f(0.5f, 1.0f, 0.5f); // Light green color
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate in the same direction
	drawRect(-h / 2, -w / 2, h, w);
	glPopMatrix();

	// Draw the plus sign
	glColor3f(1.0f, 1.0f, 1.0f); // White color
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(x - w / 2 + w / 4, y);
	glVertex2i(x + w / 2 - w / 4, y);
	glVertex2i(x, y - h * 0.15);
	glVertex2i(x, y + h * 0.15);
	glEnd();
}




void drawFlag(int x, int y) {
	int w = 20; // Width of the rectangles
	int h = 40; // Height of the rectangles

	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(0.15f, 0.15f, 0.15f);
	float rotationAngle = glutGet(GLUT_ELAPSED_TIME) / 2000.0f * 360.0f;
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate in place

	// Draw black pole
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRect(0, -300, 20, 600);

	// Draw rectangles
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRect(20, 200, 400, 100);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawRect(20, 100, 400, 100);
	glColor3f(0.0f, 0.5f, 0.0f); // dark green color
	drawRect(20, 0, 400, 100);

	// Draw triangle
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2i(20, 300);
	glVertex2i(120, 150); // adjust y coordinate to match height of rectangles
	glVertex2i(20, 0); // adjust y coordinate to match height of rectangles
	glEnd();

	glPopMatrix();
}

void drawBomb(float x, float y, bool isVisible) {
	int bodyRadius = 15;
	int highlightRadius = 3;
	int tipWidth = 8;
	int tipHeight = 6;
	int stringLength = 10;

	// Draw bomb body
	glColor3f(0.0f, 0.0f, 0.0f);
	drawCircle(x, y, bodyRadius);

	// Draw highlight
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(x - 7 + highlightRadius, y + 6 - highlightRadius, highlightRadius);

	// Draw bomb tip
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRect(x - tipWidth / 2, y + bodyRadius, tipWidth, tipHeight);

	// Draw bomb string
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(x, y + bodyRadius + tipHeight);
	glVertex2f(x, y + bodyRadius + tipHeight + stringLength);
	glEnd();


}

void generateRandomCoordinatesCoin(int index) {
	float x, y;
	do {
		x = RandomNum(50, 950);
		y = RandomNum(100, 500);
	} while (isCollisionWithBomb(x, y) || isCollisionWithCoin(x, y) || isCollisionWithAidBox(x, y) || isCollisionWithCenter(x, y) || isCollisionWithFlag(x, y));

	coinCoordinates[index][0] = x;
	coinCoordinates[index][1] = y;
}

void generateRandomCoordinatesAidBox(int index) {
	float x, y;
	do {
		x = RandomNum(50, 950);
		y = RandomNum(100, 500);
	} while (isCollisionWithBomb(x, y) || isCollisionWithCoin(x, y) || isCollisionWithAidBox(x, y) || isCollisionWithCenter(x, y) || isCollisionWithFlag(x, y));

	aidBoxCoordinates[index][0] = x;
	aidBoxCoordinates[index][1] = y;
}

void generateRandomPigCoordinates(int index) {
	float x, y;
	do {
		x = RandomNum(50, 950);
		y = RandomNum(100, 500);
	} while (isCollisionWithBomb(x, y) || isCollisionWithCoin(x, y) || isCollisionWithAidBox(x, y) || isCollisionWithCenter(x, y) || isCollisionWithFlag(x, y));

	pigCoordinates[index][0] = x;
	pigCoordinates[index][1] = y;
}

bool isCollisionWithBomb(float x, float y) {
	for (int j = 0; j < 5; j++) {
		float bombX = bombCoordinates[j][0];
		float bombY = bombCoordinates[j][1];
		float bombRadius = 25;

		float dx = x - bombX;
		float dy = y - bombY;
		float distanceSquared = dx * dx + dy * dy;

		if (distanceSquared < bombRadius * bombRadius) {
			return true;
		}
	}
	return false; // No collision
}

bool isCollisionWithCoin(float x, float y) {
	for (int k = 0; k < 2; k++) {
		float coinX = coinCoordinates[k][0];
		float coinY = coinCoordinates[k][1];
		float coinRadius = 15;

		float dx = x - coinX;
		float dy = y - coinY;
		float distanceSquared = dx * dx + dy * dy;

		if (distanceSquared < coinRadius * coinRadius) {
			CollidedCoinX = coinX;
			CollidedCoinY = coinY;
			return true; // Collision 

		}
	}
	return false; // No collision
}

bool isCollisionWithAidBox(float x, float y) {
	for (int l = 0; l < 2; l++) {
		float aidBoxX = aidBoxCoordinates[l][0];
		float aidBoxY = aidBoxCoordinates[l][1];
		float aidBoxRadius = 20;

		float dx = x - aidBoxX;
		float dy = y - aidBoxY;
		float distanceSquared = dx * dx + dy * dy;

		if (distanceSquared < aidBoxRadius * aidBoxRadius) {
			CollidedAidBoxX = aidBoxX;
			CollidedAidBoxY = aidBoxY;
			return true; // Collision 
		}
	}
	return false; // No collision
}

bool isCollisionWithCenter(float x, float y) {
	float centerX = 500;
	float centerY = 300;
	float centerRadius = 20;

	float dx = x - centerX;
	float dy = y - centerY;
	float distanceSquared = dx * dx + dy * dy;

	if (distanceSquared < centerRadius * centerRadius) {
		return true; // Collision 
	}

	return false; // No collision
}

bool isCollisionWithFlag(float x, float y) {
	float flagX = 800; // X-coordinate of the flag
	float flagY = 100; // Y-coordinate of the flag
	float flagWidth = 50; // Width of the flag
	float flagHeight = 100; // Height of the flag

	if (x >= flagX && x <= flagX + flagWidth && y >= flagY && y <= flagY + flagHeight) {
		return true; // Collision with the flag
	}
	return false; // No collision
}

void drawCloud(int x, int y) {
	static int offset = 0;

	// Move the cloud to the right
	x += offset;
	offset += 1;
	if (x > 1500) {
		x = -300;
		offset = 0;
	}

	//cloud 1
	glColor3f(1, 1, 1);
	drawCircle(x, y, 50);
	drawCircle(x + 50, y, 40);
	drawCircle(x + 90, y, 30);
	//drawCircle(x + 120, y, 20);
	//drawCircle(x + 140, y, 10);
	drawCircle(x - 50, y, 40);
	drawCircle(x - 90, y, 30);
	drawCircle(x - 120, y, 20);
	drawCircle(x - 140, y, 10);

	//cloud 2

	drawCircle(x + 300, y - 200, 50);
	drawCircle(x + 350, y - 200, 40);
	drawCircle(x + 390, y - 200, 30);
	//drawCircle(x + 120, y, 20);
	//drawCircle(x + 140, y, 10);
	drawCircle(x + 250, y - 200, 40);
	drawCircle(x + 210, y - 200, 30);
	drawCircle(x + 180, y - 200, 20);
	drawCircle(x + 160, y - 200, 10);

	//cloud 3

	drawCircle(x - 300, y - 200, 50);
	drawCircle(x - 350, y - 200, 40);
	drawCircle(x - 390, y - 200, 30);
	//drawCircle(x + 120, y, 20);
	//drawCircle(x + 140, y, 10);
	drawCircle(x - 250, y - 200, 40);
	drawCircle(x - 210, y - 200, 30);
	drawCircle(x - 180, y - 200, 20);
	drawCircle(x - 160, y - 200, 10);
}


void drawRedCircle(float r) {

	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	drawCircle(charX, charY, r); // Draw the red circle

	glColor3f(1.0f, 1.0f, 1.0f); // White color
	// Draw eyes
	drawCircle(charX + 3, charY + 3, r / 4);
	drawCircle(charX + 15, charY + 3, r / 4);

	glColor3f(0.0f, 0.0f, 0.0f); // Black color
	// Draw pupils
	drawCircle(charX + 15, charY + 3, r / 8);
	drawCircle(charX + 1, charY + 3, r / 8);

	glColor3f(1.0f, 1.0f, 1.0f); // White color
	// Add highlights to pupils
	drawCircle(charX + 15, charY + 3, r / 20);
	drawCircle(charX + 1, charY + 3, r / 20);

	// Draw eyebrows
	glColor3f(0.0f, 0.0f, 0.0f); // Black color
	drawRect(charX - 2, charY + 5, 10, 3); // Left eyebrow
	drawRect(charX + 10, charY + 5, 10, 3); // Right eyebrow

	// Add thick red lines on top of the circle as hair (tilted)
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glLineWidth(8);
	glBegin(GL_LINES);
	glVertex2f(charX + 5, charY + 18);
	glVertex2f(charX + 15, charY + 25);
	glEnd();
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(charX + 5, charY + 18);
	glVertex2f(charX + 5, charY + 30);
	glEnd();

	// Draw beak

	glColor3f(1.0f, 1.f, .5);
	glBegin(GL_POLYGON);
	glVertex2i(charX + 3, charY - 5);

	glVertex2i(charX + 8, charY - 3);
	glVertex2i(charX + 1 + r + 10, charY - 3);
	//glVertex2i(charX + 1 + r + 15, charY - 3 - 20);
	//glVertex2i(charX + 1 + r + 15, charY - 3 - 20);
	glVertex2i(charX + 5, charY - 3 - 10);
	glEnd();

	//brown line going thru beak

	glColor3f(0.54f, 0.27f, 0.07f); // dark brown color
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(charX + 3, charY - 7);
	glVertex2i(charX + r, charY - 7);
	glEnd();


}