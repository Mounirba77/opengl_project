#include "miWidget.h"
#include <QOpenGLFunctions>
#include <QPainter>

miWidget::miWidget(QWidget *parent) : QOpenGLWidget(parent), translationX(0), translationY(0), translationZ(0),
    scaleX(1.0), scaleY(1.0), scaleZ(1.0) // Initialiser les valeurs d'échelle par défaut
{
    // Constructeur, initialisation des valeurs par défaut
}

void miWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);  // Activer le test de profondeur
}

void miWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  // Ajuster la vue OpenGL lors du redimensionnement
}

void miWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Effacer l'écran et le buffer de profondeur
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();  // Réinitialiser les transformations

    // Appliquer les transformations de translation
    glTranslatef(translationX, translationY, translationZ);

    // Appliquer les transformations de mise à l'échelle
    glScalef(scaleX, scaleY, scaleZ);

    // Appliquer les transformations de rotation
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    // Dessiner un cube avec des couleurs différentes pour chaque face
    // Front face (multicolored)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.05, -0.05, -0.05);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.05, 0.05, -0.05);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.05, 0.05, -0.05);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.05, -0.05, -0.05);
    glEnd();

    // Back face (white)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); glVertex3f(0.05, -0.05, 0.05);
    glVertex3f(0.05, 0.05, 0.05);
    glVertex3f(-0.05, 0.05, 0.05);
    glVertex3f(-0.05, -0.05, 0.05);
    glEnd();

    // Right face (purple)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(0.05, -0.05, -0.05);
    glVertex3f(0.05, 0.05, -0.05);
    glVertex3f(0.05, 0.05, 0.05);
    glVertex3f(0.05, -0.05, 0.05);
    glEnd();

    // Left face (green)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.05, -0.05, 0.05);
    glVertex3f(-0.05, 0.05, 0.05);
    glVertex3f(-0.05, 0.05, -0.05);
    glVertex3f(-0.05, -0.05, -0.05);
    glEnd();

    // Top face (blue)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.05, 0.05, 0.05);
    glVertex3f(0.05, 0.05, -0.05);
    glVertex3f(-0.05, 0.05, -0.05);
    glVertex3f(-0.05, 0.05, 0.05);
    glEnd();

    // Bottom face (red)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.05, -0.05, -0.05);
    glVertex3f(0.05, -0.05, 0.05);
    glVertex3f(-0.05, -0.05, 0.05);
    glVertex3f(-0.05, -0.05, -0.05);
    glEnd();

    // Dessiner des axes pour visualiser les directions X, Y, Z
    graficarLineas();

    glFlush();  // Exécuter les commandes OpenGL
    this->makeCurrent();
}

void miWidget::graficarLineas()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(20, 0, 0);  // Axe X (rouge)
    glColor3f(1, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 20, 0);  // Axe Y (jaune)
    glColor3f(0, 1, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 20);  // Axe Z (cyan)
    glEnd();
}

void miWidget::setTranslationX(float value)
{
    translationX = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setTranslationY(float value)
{
    translationY = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setTranslationZ(float value)
{
    translationZ = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setScaleX(float value)
{
    scaleX = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setScaleY(float value)
{
    scaleY = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setScaleZ(float value)
{
    scaleZ = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setrotationX(float value)
{
    rotate_x = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setrotationY(float value)
{
    rotate_y = value;
    update();  // Mettre à jour le widget après chaque changement
}

void miWidget::setrotationZ(float value)
{
    rotate_z = value;
    update();  // Mettre à jour le widget après chaque changement
}
