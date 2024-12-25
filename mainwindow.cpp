#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrlQuery>
#include <QSqlDatabase>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    xCoordinate(0), yCoordinate(0), zCoordinate(0),
    xTranslation(0), yTranslation(0), zTranslation(0),
    scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f)  // Initialize scale
{
    ui->setupUi(this);

    // Initialisation du QLabel pour afficher les coordonnées
    coordinatesLabel = ui->coordinatesLabel;  // Automatiquement lié par Qt Designer

    // Définir le texte initial du QLabel (coordonnées = (0, 0, 0))
    updateCoordinates(0, 0, 0);

    // Initialisation des positions des sliders (assumer la valeur 0 initialement)
    ui->rotationSliderX->setValue(0);         // Rotation X
    ui->rotationSliderY->setValue(0);       // Rotation Y
    ui->rotationSliderZ->setValue(0);       // Rotation Z
    ui->translationSliderX->setValue(0);     // Translation X
    ui->translationSliderY->setValue(0);     // Translation Y
    ui->translationSliderZ->setValue(0);     // Translation Z
    ui->scaleSliderX->setValue(0);         // Scale X (100% as default)
    ui->scaleSliderY->setValue(0);         // Scale Y
    ui->scaleSliderZ->setValue(0);         // Scale Z
    ui->translationSliderX->setRange(0,100);           // Slider range
    ui->translationSliderY->setRange(0,100);
    ui->translationSliderZ->setRange(0,100);
    //ui->translationSliderX->setSingleStep(0.01);          // Small increment step (via arrow keys)
    //ui->translationSliderX->setPageStep(0.1);

    // Connexions des signaux et des slots des sliders
    connect(ui->rotationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderX_actionTriggered);
    connect(ui->rotationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderY_actionTriggered);
    connect(ui->rotationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderZ_actionTriggered);
    connect(ui->translationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderX_actionTriggered);
    connect(ui->translationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderY_actionTriggered);
    connect(ui->translationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderZ_actionTriggered);
    connect(ui->scaleSliderX, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderX_actionTriggered);
    connect(ui->scaleSliderY, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderY_actionTriggered);
    connect(ui->scaleSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderZ_actionTriggered);
    // Connect button signals to slots
    connect(ui->loadbtn, &QPushButton::clicked, this, &MainWindow::on_loadbtn_clicked);
    connect(ui->savebtn, &QPushButton::clicked, this, &MainWindow::on_savebtn_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCoordinates(double x, double y, double z)
{
    // Mettre à jour le QLabel avec les coordonnées
    QString coordinatesText = QString("X: %1, Y: %2, Z: %3").arg(x).arg(y).arg(z);
    coordinatesLabel->setText(coordinatesText);  // Mettre à jour les coordonnées affichées
}

void MainWindow::on_rotationSliderX_actionTriggered(int action)
{
    // // Mise à jour de la rotation X selon la valeur du slider
    // ui->widget->rotate_x = ui->rotationSliderX->value();
    // ui->widget->update(); // Mettre à jour le widget

    // Mise à jour de la translation X selon la valeur du slider
    xRotation = ui->rotationSliderX->value();
    ui->widget->setrotationX(xRotation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_rotationSliderY_actionTriggered(int action)
{
    // Mise à jour de la translation X selon la valeur du slider
    yRotation = ui->rotationSliderY->value();
    ui->widget->setrotationY(yRotation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_rotationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la translation X selon la valeur du slider
    zRotation = ui->rotationSliderZ->value();
    ui->widget->setrotationZ(zRotation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_translationSliderX_actionTriggered(int action)
{
    // Mise à jour de la translation X selon la valeur du slider
    xTranslation = ui->translationSliderX->value()/100.0;
    ui->widget->setTranslationX(xTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_translationSliderY_actionTriggered(int action)
{
    // Mise à jour de la translation Y selon la valeur du slider
    yTranslation = ui->translationSliderY->value()/100.0;
    ui->widget->setTranslationY(yTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_translationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la translation Z selon la valeur du slider
    zTranslation = ui->translationSliderZ->value()/100.0;
    ui->widget->setTranslationZ(zTranslation); // Mettre à jour la translation pour le widget
    ui->widget->update(); // Mettre à jour le widget
    updateCoordinates(xTranslation, yTranslation, zTranslation); // Mettre à jour les coordonnées dans le QLabel
}

void MainWindow::on_scaleSliderX_actionTriggered(int action)
{
    // Mise à jour de l'échelle X selon la valeur du slider
    scaleX = ui->scaleSliderX->value()/5.0; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleX(scaleX); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_scaleSliderY_actionTriggered(int action)
{
    // Mise à jour de l'échelle Y selon la valeur du slider
    scaleY = ui->scaleSliderY->value()/5.0; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleY(scaleY); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}

void MainWindow::on_scaleSliderZ_actionTriggered(int action)
{
    // Mise à jour de l'échelle Z selon la valeur du slider
    scaleZ = ui->scaleSliderZ->value()/5.0; // Convertir la valeur en facteur de mise à l'échelle
    ui->widget->setScaleZ(scaleZ); // Appliquer l'échelle au widget
    ui->widget->update(); // Mettre à jour le widget
}




void MainWindow::on_savebtn_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL corrigée du script PHP
    QUrl url("http://localhost/webdb/openglsave.php"); // Assurez-vous que "localhost" pointe vers votre serveur WAMP

    // Préparer les données à envoyer
    QUrlQuery params;
    params.addQueryItem("translationx", QString::number(xTranslation));
    params.addQueryItem("translationy", QString::number(yTranslation));
    params.addQueryItem("translationz", QString::number(zTranslation));
    params.addQueryItem("rotationx", QString::number(xRotation));
    params.addQueryItem("rotationy", QString::number(yRotation));
    params.addQueryItem("rotationz", QString::number(zRotation));
    params.addQueryItem("scalex", QString::number(scaleX));
    params.addQueryItem("scaley", QString::number(scaleY));
    params.addQueryItem("scalez", QString::number(scaleZ));
    // Préparer la requête
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, params.query().toUtf8());

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj["success"].toBool()) {
                QMessageBox::information(nullptr, "Succès", jsonObj["message"].toString());
            } else {
                QMessageBox::critical(nullptr, "Erreur", jsonObj["message"].toString());
            }
        } else {
            // Afficher l'erreur détaillée
            QMessageBox::critical(nullptr, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::on_loadbtn_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL du script PHP
    QUrl url("http://localhost/webdb/openglload.php"); // Remplacez par l'URL correcte

    // Préparer la requête
    QNetworkRequest request(url);

    // Envoyer la requête GET
    QNetworkReply *reply = manager->get(request);

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj["success"].toBool()) {
                // Extraire les données de l'objet JSON
                QJsonObject data = jsonObj["data"].toObject();
                double tx = data["translationx"].toDouble();
                double ty = data["translationy"].toDouble();
                double tz = data["translationz"].toDouble();
                double rx = data["rotationx"].toDouble();
                double ry = data["rotationy"].toDouble();
                double rz = data["rotationz"].toDouble();
                double sx = data["scalex"].toDouble();
                double sy = data["scaley"].toDouble();
                double sz = data["scalez"].toDouble();

                // Mettre à jour les sliders
                ui->translationSliderX->setValue(tx * 100);
                ui->translationSliderY->setValue(ty * 100);
                ui->translationSliderZ->setValue(tz * 100);
                ui->rotationSliderX->setValue(rx);
                ui->rotationSliderY->setValue(ry);
                ui->rotationSliderZ->setValue(rz);
                ui->scaleSliderX->setValue(sx * 5);
                ui->scaleSliderY->setValue(sy * 5);
                ui->scaleSliderZ->setValue(sz * 5);

                // Mettre à jour les valeurs dans le widget
                ui->widget->setTranslationX(tx);
                ui->widget->setTranslationY(ty);
                ui->widget->setTranslationZ(tz);
                ui->widget->setrotationX(rx);
                ui->widget->setrotationY(ry);
                ui->widget->setrotationZ(rz);
                ui->widget->setScaleX(sx);
                ui->widget->setScaleY(sy);
                ui->widget->setScaleZ(sz);
                ui->widget->update();

                // Mettre à jour les coordonnées affichées dans le QLabel
                updateCoordinates(tx, ty, tz);
            } else {
                QMessageBox::critical(this, "Erreur", jsonObj["message"].toString());
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater();
    });

}


void MainWindow::on_readbtn_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL of the PHP script
    QUrl url("http://localhost/webdb/openglread.php"); // Ensure this matches your setup

    // Prepare the request
    QNetworkRequest request(url);

    // Send the GET request
    QNetworkReply *reply = manager->get(request);

    // Handle the response
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj["success"].toBool()) {
                // Extract the data array
                QJsonArray data = jsonObj["data"].toArray();

                // Clear the table before populating it
                ui->table->setRowCount(0);

                // Populate the table
                ui->table->setColumnCount(10); // Number of columns
                ui->table->setHorizontalHeaderLabels({"ID", "TranslationX", "TranslationY", "TranslationZ",
                                                      "RotationX", "RotationY", "RotationZ",
                                                      "ScaleX", "ScaleY", "ScaleZ"});

                for (int i = 0; i < data.size(); ++i) {
                    QJsonObject row = data[i].toObject();

                    // Insert a new row
                    ui->table->insertRow(i);

                    // Populate each column
                    ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(row["id"].toInt())));
                    ui->table->setItem(i, 1, new QTableWidgetItem(QString::number(row["translationx"].toDouble())));
                    ui->table->setItem(i, 2, new QTableWidgetItem(QString::number(row["translationy"].toDouble())));
                    ui->table->setItem(i, 3, new QTableWidgetItem(QString::number(row["translationz"].toDouble())));
                    ui->table->setItem(i, 4, new QTableWidgetItem(QString::number(row["rotationx"].toDouble())));
                    ui->table->setItem(i, 5, new QTableWidgetItem(QString::number(row["rotationy"].toDouble())));
                    ui->table->setItem(i, 6, new QTableWidgetItem(QString::number(row["rotationz"].toDouble())));
                    ui->table->setItem(i, 7, new QTableWidgetItem(QString::number(row["scalex"].toDouble())));
                    ui->table->setItem(i, 8, new QTableWidgetItem(QString::number(row["scaley"].toDouble())));
                    ui->table->setItem(i, 9, new QTableWidgetItem(QString::number(row["scalez"].toDouble())));
                }

                QMessageBox::information(this, "Success", "Data loaded successfully.");
            } else {
                QMessageBox::critical(this, "Error", jsonObj["message"].toString());
            }
        } else {
            QMessageBox::critical(this, "Error", "Cannot contact server: " + reply->errorString());
        }
        reply->deleteLater();
    });
}



void MainWindow::on_deletebtn_clicked()
{
    QString id = ui->ID_text->text();

    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL corrigée du script PHP
    QUrl url("http://localhost/webdb/opengldelete.php"); // Assurez-vous que "localhost" pointe vers votre serveur WAMP

    // Préparer les données à envoyer
    QUrlQuery params;
    params.addQueryItem("id", QString::number(id.toInt()));

    // Préparer la requête
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, params.query().toUtf8());

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj["success"].toBool()) {
                QMessageBox::information(nullptr, "Succès", jsonObj["message"].toString());
            } else {
                QMessageBox::critical(nullptr, "Erreur", jsonObj["message"].toString());
            }
        } else {
            // Afficher l'erreur détaillée
            QMessageBox::critical(nullptr, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater();
    });
}

