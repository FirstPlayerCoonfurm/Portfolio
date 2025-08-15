#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Размеры окна
int windowWidth = 800;
int windowHeight = 600;

// Параметры волн
float waveHeight = 30.0f;
float waveLength = 0.02f;
float waveSpeed = 0.05f;
float waveOffset = 0.0f;

// Параметры корабля
float shipX = 400.0f;
float shipY = 300.0f;
float shipWidth = 100.0f;
float shipHeight = 50.0f;
float shipSpeed = 2.0f;
float shipAngle = 0.0f;

// Цвета
GLfloat waterColor[] = {0.0f, 0.3f, 0.7f, 1.0f};
GLfloat shipColor[] = {0.5f, 0.3f, 0.1f, 1.0f};
GLfloat sailColor[] = {0.9f, 0.9f, 0.9f, 1.0f};

// Функция для отрисовки волны
void drawWave() {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 1.0f);
    for (int x = 0; x <= windowWidth; x += 5) {
        float y = waveHeight * sin(waveLength * x + waveOffset) + windowHeight / 2;
        glVertex2f(x, y);
    }
    glEnd();
}

// Функция для отрисовки корабля
void drawShip() {
    // Корпус корабля
    glBegin(GL_POLYGON);
    glColor3fv(shipColor);
    glVertex2f(shipX - shipWidth/2, shipY);
    glVertex2f(shipX + shipWidth/2, shipY);
    glVertex2f(shipX + shipWidth/3, shipY - shipHeight/2);
    glVertex2f(shipX - shipWidth/3, shipY - shipHeight/2);
    glEnd();

    // Мачта
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.3f, 0.2f, 0.1f);
    glVertex2f(shipX, shipY);
    glVertex2f(shipX, shipY + shipHeight);
    glEnd();

    // Парус
    glBegin(GL_TRIANGLES);
    glColor3fv(sailColor);
    glVertex2f(shipX, shipY + shipHeight/3);
    glVertex2f(shipX, shipY + shipHeight);
    glVertex2f(shipX + shipWidth/2, shipY + shipHeight/2);
    glEnd();
}

// Функция отрисовки сцены
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Рисуем море (заполненная волна)
    glBegin(GL_POLYGON);
    glColor3fv(waterColor);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    for (int x = windowWidth; x >= 0; x -= 5) {
        float y = waveHeight * sin(waveLength * x + waveOffset) + windowHeight / 2;
        glVertex2f(x, y);
    }
    glEnd();

    // Рисуем волну (контур)
    drawWave();

    // Рисуем корабль
    drawShip();

    glutSwapBuffers();
}

// Функция обновления анимации
void update(int value) {
    // Обновляем смещение волны для анимации
    waveOffset += waveSpeed;

    // Двигаем корабль
    shipX += shipSpeed;
    if (shipX > windowWidth + shipWidth) {
        shipX = -shipWidth;
    }

    // Качаем корабль на волнах
    float waveAtShip = waveHeight * sin(waveLength * shipX + waveOffset);
    shipY = windowHeight / 2 + waveAtShip;
    shipAngle = waveHeight * waveLength * cos(waveLength * shipX + waveOffset) * 5.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

// Функция обработки изменения размеров окна
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

// Функция обработки клавиатуры
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
            break;
        case 'a':
            shipSpeed -= 0.5f;
            break;
        case 'd':
            shipSpeed += 0.5f;
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Корабль на волнах");

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Цвет неба

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
