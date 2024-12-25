#ifndef MIWIDGET_H
#define MIWIDGET_H
// Directives de préprocesseur pour éviter les inclusions multiples de ce fichier d'en-tête.

#include <QOpenGLFramebufferObject>
// Inclure QOpenGLFramebufferObject pour gérer des objets de tampon image OpenGL.

#include <QOpenGLWidget>
// Inclure QOpenGLWidget pour créer un widget utilisant OpenGL pour le rendu.

#include <QOpenGLFunctions>
// Inclure QOpenGLFunctions pour accéder aux fonctions OpenGL.

class miWidget : public QOpenGLWidget, protected QOpenGLFunctions
// Définition de la classe miWidget, qui hérite de QOpenGLWidget
// et utilise QOpenGLFunctions pour accéder aux fonctionnalités OpenGL.
{
    Q_OBJECT
    // Macro Qt nécessaire pour la gestion des signaux et des slots.

public:
    explicit miWidget(QWidget *parent = nullptr);
    // Constructeur explicite avec un parent facultatif pour initialiser le widget.

    // Méthodes pour gérer les translations.
    void setTranslationX(float value); // Définir la translation sur l'axe X.
    void setTranslationY(float value); // Définir la translation sur l'axe Y.
    void setTranslationZ(float value); // Définir la translation sur l'axe Z.

    // Méthodes pour gérer l'échelle.
    void setScaleX(float value); // Définir l'échelle sur l'axe X.
    void setScaleY(float value); // Définir l'échelle sur l'axe Y.
    void setScaleZ(float value); // Définir l'échelle sur l'axe Z.

    // Méthodes pour gérer la rotation.
    void setrotationX(float value); // Définir la rotation autour de l'axe X.
    void setrotationY(float value); // Définir la rotation autour de l'axe Y.
    void setrotationZ(float value); // Définir la rotation autour de l'axe Z.

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    // Méthode pour initialiser les ressources et l'état OpenGL. Surcharge de QOpenGLWidget.

    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    // Méthode appelée lorsque le widget est redimensionné pour ajuster le rendu OpenGL.

    void paintGL() Q_DECL_OVERRIDE;
    // Méthode appelée pour dessiner le contenu OpenGL dans le widget.

    void graficarLineas();
    // Méthode pour dessiner des lignes.

public:
    // Variables publiques pour gérer la rotation.
    double rotate_x = 0; // Rotation autour de l'axe X (initialisée à 0).
    double rotate_y = 0; // Rotation autour de l'axe Y (initialisée à 0).
    double rotate_z = 0; // Rotation autour de l'axe Z (initialisée à 0).

private:
    // Variables privées pour gérer la translation.
    float translationX = 0; // Translation sur l'axe X (initialisée à 0).
    float translationY = 0; // Translation sur l'axe Y (initialisée à 0).
    float translationZ = 0; // Translation sur l'axe Z (initialisée à 0).

    // Variables privées pour gérer l'échelle.
    float scaleX = 1.0; // Échelle sur l'axe X (valeur initiale : 1.0, pas de mise à l'échelle).
    float scaleY = 1.0; // Échelle sur l'axe Y (valeur initiale : 1.0).
    float scaleZ = 1.0; // Échelle sur l'axe Z (valeur initiale : 1.0).
};

#endif // MIWIDGET_H
// Fin de la directive de préprocesseur pour éviter les inclusions multiples.
