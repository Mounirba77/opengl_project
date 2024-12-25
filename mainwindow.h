#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// Directives de préprocesseur pour éviter les inclusions multiples.
// Elles garantissent que le fichier d'en-tête n'est inclus qu'une seule fois.

#include <QMainWindow>
// Inclure la classe QMainWindow, qui est la base d'une fenêtre principale dans Qt.

#include <QString>  // Inclure QString pour gérer les chaînes de caractères.
#include <QLabel>   // Inclure QLabel pour afficher du texte ou des coordonnées.
#include <QSlider>  // Inclure QSlider pour permettre des contrôles interactifs avec des sliders.
#include <QtNetwork>
// Inclure le module QtNetwork pour les fonctionnalités réseau.
#include <QtSql>
// Inclure le module QtSql pour gérer les bases de données.
#include <QSqlDatabase>
// Inclure la classe QSqlDatabase pour se connecter et gérer des bases de données.
#include <QNetworkAccessManager>
// Inclure QNetworkAccessManager pour gérer les requêtes réseau.
#include <QNetworkReply>
// Inclure QNetworkReply pour traiter les réponses réseau.

namespace Ui {
class MainWindow;
// Déclaration d'un espace de noms "Ui" contenant la classe MainWindow,
// généralement générée automatiquement par l'outil Qt Designer.
}

class MainWindow : public QMainWindow
// Définition de la classe MainWindow, qui hérite de QMainWindow.
{
    Q_OBJECT // Ajout de cette macro obligatoire pour utiliser les signaux et slots dans Qt.

public:
    explicit MainWindow(QWidget *parent = nullptr);
    // Constructeur explicite pour initialiser MainWindow avec un parent optionnel.
    ~MainWindow();
    // Destructeur de la classe MainWindow.

private:
    // Début de la section des membres et fonctions privées.

public slots:
    void updateCoordinates(double x, double y, double z);
    // Slot public pour mettre à jour les coordonnées (X, Y, Z).

    // Déclaration des slots pour gérer les actions des sliders (rotation).
    void on_rotationSliderX_actionTriggered(int action);       // Rotation autour de l'axe X.
    void on_rotationSliderY_actionTriggered(int action);       // Rotation autour de l'axe Y.
    void on_rotationSliderZ_actionTriggered(int action);       // Rotation autour de l'axe Z.
    void on_translationSliderX_actionTriggered(int action);    // Translation sur l'axe X.
    void on_translationSliderY_actionTriggered(int action);    // Translation sur l'axe Y.
    void on_translationSliderZ_actionTriggered(int action);    // Translation sur l'axe Z.

    // Slots pour gérer la mise à l'échelle.
    void on_scaleSliderX_actionTriggered(int action);  // Mise à l'échelle sur l'axe X.
    void on_scaleSliderY_actionTriggered(int action);  // Mise à l'échelle sur l'axe Y.
    void on_scaleSliderZ_actionTriggered(int action);  // Mise à l'échelle sur l'axe Z.

private slots:
    void on_savebtn_clicked();
    // Slot pour gérer l'événement du bouton "Enregistrer".

    void on_loadbtn_clicked();
    // Slot pour gérer l'événement du bouton "Charger".

    void on_readbtn_clicked();
    // Slot pour gérer l'événement du bouton "Lire".

    void on_deletebtn_clicked();
    // Slot pour gérer l'événement du bouton "Supprimer".

private:
    Ui::MainWindow *ui;
    // Pointeur vers l'interface utilisateur associée à cette classe.

    QLabel *coordinatesLabel;
    // QLabel pour afficher les coordonnées à l'utilisateur.

    // Variables pour stocker les coordonnées des sliders (rotation).
    double xCoordinate, yCoordinate, zCoordinate;

    // Variables pour stocker les valeurs de mise à l'échelle.
    double scaleX, scaleY, scaleZ;

    // Variables pour stocker les coordonnées de translation.
    double xTranslation, yTranslation, zTranslation;

    // Variables pour stocker les coordonnées de rotation.
    double xRotation, yRotation, zRotation;

    // Position initiale des sliders.
    int initialSliderValue;

    QNetworkAccessManager *networkManager;
    // Gestionnaire pour effectuer des requêtes réseau.
};

#endif // MAINWINDOW_H
// Fin de la directive de préprocesseur pour éviter les inclusions multiples.
