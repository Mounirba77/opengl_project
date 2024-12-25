#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>  // Inclure QString pour gérer les chaînes de caractères
#include <QLabel>   // Inclure QLabel pour afficher les coordonnées
#include <QSlider>  // Inclure QSlider pour les sliders
#include <QtNetwork>
#include <QtSql>
#include <QSqlDatabase>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT // Ajout de cette macro pour les signaux/slots

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:


public slots:
    void updateCoordinates(double x, double y, double z); // Slot pour mettre à jour les coordonnées

    // Déclaration des autres slots pour les sliders
    void on_rotationSliderX_actionTriggered(int action);       // Rotation X
    void on_rotationSliderY_actionTriggered(int action);     // Rotation Y
    void on_rotationSliderZ_actionTriggered(int action);     // Rotation Z
    void on_translationSliderX_actionTriggered(int action);   // Translation X
    void on_translationSliderY_actionTriggered(int action);   // Translation Y
    void on_translationSliderZ_actionTriggered(int action);   // Translation Z

    // Slots pour la mise à l'échelle
    void on_scaleSliderX_actionTriggered(int action);  // Ajout de ce slot
    void on_scaleSliderY_actionTriggered(int action);  // Ajout de ce slot
    void on_scaleSliderZ_actionTriggered(int action);  // Ajout de ce slot


private slots:
    void on_savebtn_clicked();

    void on_loadbtn_clicked();


    void on_readbtn_clicked();

    void on_deletebtn_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *coordinatesLabel; // Un QLabel pour afficher les coordonnées

    // Variables pour stocker les coordonnées des sliders (rotation)
    double xCoordinate, yCoordinate, zCoordinate;

    // Variables pour stocker les coordonnées de changement de du taille
    double scaleX, scaleY, scaleZ;

    // Variables pour stocker les coordonnées de translation
    double xTranslation, yTranslation, zTranslation;

    // Variables pour stocker les coordonnées de rotation
    double xRotation, yRotation, zRotation;

    // Position initiale des sliders
    int initialSliderValue;

    QNetworkAccessManager *networkManager;
};

#endif // MAINWINDOW_H
