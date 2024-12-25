#include "miWidget.h"  // Inclusion du fichier d'en-tête de la classe miWidget
#include <QOpenGLFunctions>  // Inclusion des fonctions OpenGL
#include <QPainter>  // Inclusion pour l'utilisation de QPainter

// Constructeur de la classe miWidget
miWidget::miWidget(QWidget *parent) : QOpenGLWidget(parent), translationX(0), translationY(0), translationZ(0),
    scaleX(1.0), scaleY(1.0), scaleZ(1.0) // Initialiser les valeurs d'échelle par défaut
{
    // Constructeur, initialisation des valeurs par défaut
}

void miWidget::initializeGL()
{
    initializeOpenGLFunctions();  // Initialiser les fonctions OpenGL
    glEnable(GL_DEPTH_TEST);  // Activer le test de profondeur pour gérer le rendu 3D correctement
}

void miWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  // Ajuster la fenêtre d'affichage OpenGL lors du redimensionnement
}

void miWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Effacer l'écran et le buffer de profondeur
    glDepthFunc(GL_LESS);  // Utiliser la fonction de test de profondeur par défaut
    glEnable(GL_DEPTH_TEST);  // Assurer que le test de profondeur est activé
    glShadeModel(GL_SMOOTH);  // Utiliser un modèle d'éclairage lisse pour un rendu plus fluide

    glLoadIdentity();  // Réinitialiser la matrice de transformation

    // Appliquer les transformations de translation
    glTranslatef(translationX, translationY, translationZ);

    // Appliquer les transformations de mise à l'échelle
    glScalef(scaleX, scaleY, scaleZ);

    // Appliquer les transformations de rotation
    glRotatef(rotate_x, 1.0, 0.0, 0.0);  // Rotation autour de l'axe X
    glRotatef(rotate_y, 0.0, 1.0, 0.0);  // Rotation autour de l'axe Y
    glRotatef(rotate_z, 0.0, 0.0, 1.0);  // Rotation autour de l'axe Z

    // Dessiner un cube avec des couleurs différentes pour chaque face

    // Face avant (multicolore)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.05, -0.05, -0.05);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.05, 0.05, -0.05);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.05, 0.05, -0.05);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.05, -0.05, -0.05);
    glEnd();

    // Face arrière (blanche)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); glVertex3f(0.05, -0.05, 0.05);
    glVertex3f(0.05, 0.05, 0.05);
    glVertex3f(-0.05, 0.05, 0.05);
    glVertex3f(-0.05, -0.05, 0.05);
    glEnd();

    // Face droite (violette)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(0.05, -0.05, -0.05);
    glVertex3f(0.05, 0.05, -0.05);
    glVertex3f(0.05, 0.05, 0.05);
    glVertex3f(0.05, -0.05, 0.05);
    glEnd();

    // Face gauche (verte)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.05, -0.05, 0.05);
    glVertex3f(-0.05, 0.05, 0.05);
    glVertex3f(-0.05, 0.05, -0.05);
    glVertex3f(-0.05, -0.05, -0.05);
    glEnd();

    // Face supérieure (bleue)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.05, 0.05, 0.05);
    glVertex3f(0.05, 0.05, -0.05);
    glVertex3f(-0.05, 0.05, -0.05);
    glVertex3f(-0.05, 0.05, 0.05);
    glEnd();

    // Face inférieure (rouge)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.05, -0.05, -0.05);
    glVertex3f(0.05, -0.05, 0.05);
    glVertex3f(-0.05, -0.05, 0.05);
    glVertex3f(-0.05, -0.05, -0.05);
    glEnd();

    // Dessiner des axes pour visualiser les directions X, Y, Z
    graficarLineas();

    glFlush();  // Exécuter les commandes OpenGL
    this->makeCurrent();  // S'assurer que le contexte est actif
}

void miWidget::graficarLineas()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(20, 0, 0);  // Axe X (rouge)
    glColor3f(1, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 20, 0);  // Axe Y (jaune)
    glColor3f(0, 1, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 20);  // Axe Z (cyan)
    glEnd();
}

// Méthodes pour définir les translations et mettre à jour le widget
void miWidget::setTranslationX(float value)
{
    translationX = value;
    update();  // Redessiner le widget
}

void miWidget::setTranslationY(float value)
{
    translationY = value;
    update();  // Redessiner le widget
}

void miWidget::setTranslationZ(float value)
{
    translationZ = value;
    update();  // Redessiner le widget
}

// Méthodes pour définir l'échelle et mettre à jour le widget
void miWidget::setScaleX(float value)
{
    scaleX = value;
    update();  // Redessiner le widget
}

void miWidget::setScaleY(float value)
{
    scaleY = value;
    update();  // Redessiner le widget
}

void miWidget::setScaleZ(float value)
{
    scaleZ = value;
    update();  // Redessiner le widget
}

// Méthodes pour définir les rotations et mettre à jour le widget
void miWidget::setrotationX(float value)
{
    rotate_x = value;
    update();  // Redessiner le widget
}

void miWidget::setrotationY(float value)
{
    rotate_y = value;
    update();  // Redessiner le widget
}

void miWidget::setrotationZ(float value)
{
    rotate_z = value;
    update();  // Redessiner le widget
}
