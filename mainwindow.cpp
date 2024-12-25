#include "mainwindow.h"  // Inclusion du fichier d'en-tête de la classe MainWindow
#include "ui_mainwindow.h"  // Inclusion de l'interface générée par Qt Designer
#include <QString>  // Pour manipuler des chaînes de caractères
#include <QLabel>  // Pour utiliser des étiquettes QLabel
#include <QJsonDocument>  // Pour manipuler des documents JSON
#include <QJsonObject>  // Pour manipuler des objets JSON
#include <QMessageBox>  // Pour afficher des messages dans des boîtes de dialogue
#include <QUrlQuery>  // Pour analyser et manipuler les URL
#include <QSqlDatabase>  // Pour travailler avec des bases de données SQL
#include <QNetworkAccessManager>  // Pour gérer les requêtes réseau
#include <QNetworkRequest>  // Pour définir une requête réseau
#include <QNetworkReply>  // Pour traiter la réponse d'une requête réseau
#include <QUrl>  // Pour manipuler des URL
#include <QSqlError>  // Pour gérer les erreurs SQL

// Constructeur de la classe MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),  // Initialisation de la classe parente QMainWindow
    ui(new Ui::MainWindow),  // Création d'une instance de l'interface utilisateur
    xCoordinate(0), yCoordinate(0), zCoordinate(0),  // Initialisation des coordonnées à 0
    xTranslation(0), yTranslation(0), zTranslation(0),  // Initialisation des translations à 0
    scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f)  // Initialisation des échelles à 1.0 (pas de mise à l'échelle)
{
    ui->setupUi(this);  // Configuration de l'interface utilisateur via Qt Designer

    // Initialisation du QLabel pour afficher les coordonnées
    coordinatesLabel = ui->coordinatesLabel;  // Liaison automatique via Qt Designer

    // Définir le texte initial du QLabel (coordonnées = (0, 0, 0))
    updateCoordinates(0, 0, 0);

    // Initialisation des sliders à leurs valeurs par défaut
    ui->rotationSliderX->setValue(0);  // Rotation X
    ui->rotationSliderY->setValue(0);  // Rotation Y
    ui->rotationSliderZ->setValue(0);  // Rotation Z
    ui->translationSliderX->setValue(0);  // Translation X
    ui->translationSliderY->setValue(0);  // Translation Y
    ui->translationSliderZ->setValue(0);  // Translation Z
    ui->scaleSliderX->setValue(0);  // Échelle X (par défaut 100 %)
    ui->scaleSliderY->setValue(0);  // Échelle Y
    ui->scaleSliderZ->setValue(0);  // Échelle Z

    // Définir les plages des sliders de translation
    ui->translationSliderX->setRange(0, 100);  // Plage de 0 à 100 pour X
    ui->translationSliderY->setRange(0, 100);  // Plage de 0 à 100 pour Y
    ui->translationSliderZ->setRange(0, 100);  // Plage de 0 à 100 pour Z

    // Connexions des signaux des sliders aux slots correspondants
    connect(ui->rotationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderX_actionTriggered);
    connect(ui->rotationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderY_actionTriggered);
    connect(ui->rotationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_rotationSliderZ_actionTriggered);
    connect(ui->translationSliderX, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderX_actionTriggered);
    connect(ui->translationSliderY, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderY_actionTriggered);
    connect(ui->translationSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_translationSliderZ_actionTriggered);
    connect(ui->scaleSliderX, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderX_actionTriggered);
    connect(ui->scaleSliderY, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderY_actionTriggered);
    connect(ui->scaleSliderZ, &QSlider::actionTriggered, this, &MainWindow::on_scaleSliderZ_actionTriggered);

    // Connexions des boutons aux slots correspondants
    connect(ui->loadbtn, &QPushButton::clicked, this, &MainWindow::on_loadbtn_clicked);  // Bouton "Charger"
    connect(ui->savebtn, &QPushButton::clicked, this, &MainWindow::on_savebtn_clicked);  // Bouton "Sauvegarder"
}


MainWindow::~MainWindow()
{
    delete ui;  // Supprime l'interface utilisateur pour libérer la mémoire
}

void MainWindow::updateCoordinates(double x, double y, double z)
{
    // Mettre à jour le QLabel avec les coordonnées X, Y et Z
    QString coordinatesText = QString("X: %1, Y: %2, Z: %3").arg(x).arg(y).arg(z);
    coordinatesLabel->setText(coordinatesText);  // Affiche le texte mis à jour dans le QLabel
}

void MainWindow::on_rotationSliderX_actionTriggered(int action)
{
    // Mise à jour de la rotation sur l'axe X
    xRotation = ui->rotationSliderX->value();  // Récupère la valeur du slider
    ui->widget->setrotationX(xRotation);  // Applique la rotation X au widget
    ui->widget->update();  // Met à jour l'affichage du widget
}

void MainWindow::on_rotationSliderY_actionTriggered(int action)
{
    // Mise à jour de la rotation sur l'axe Y
    yRotation = ui->rotationSliderY->value();  // Récupère la valeur du slider
    ui->widget->setrotationY(yRotation);  // Applique la rotation Y au widget
    ui->widget->update();  // Met à jour l'affichage du widget
}

void MainWindow::on_rotationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la rotation sur l'axe Z
    zRotation = ui->rotationSliderZ->value();  // Récupère la valeur du slider
    ui->widget->setrotationZ(zRotation);  // Applique la rotation Z au widget
    ui->widget->update();  // Met à jour l'affichage du widget
}

void MainWindow::on_translationSliderX_actionTriggered(int action)
{
    // Mise à jour de la translation sur l'axe X
    xTranslation = ui->translationSliderX->value() / 100.0;  // Normalise la valeur
    ui->widget->setTranslationX(xTranslation);  // Applique la translation X au widget
    ui->widget->update();  // Met à jour l'affichage du widget
    updateCoordinates(xTranslation, yTranslation, zTranslation);  // Met à jour le QLabel avec les nouvelles coordonnées
}

void MainWindow::on_translationSliderY_actionTriggered(int action)
{
    // Mise à jour de la translation sur l'axe Y
    yTranslation = ui->translationSliderY->value() / 100.0;  // Normalise la valeur
    ui->widget->setTranslationY(yTranslation);  // Applique la translation Y au widget
    ui->widget->update();  // Met à jour l'affichage du widget
    updateCoordinates(xTranslation, yTranslation, zTranslation);  // Met à jour le QLabel avec les nouvelles coordonnées
}

void MainWindow::on_translationSliderZ_actionTriggered(int action)
{
    // Mise à jour de la translation sur l'axe Z
    zTranslation = ui->translationSliderZ->value() / 100.0;  // Normalise la valeur
    ui->widget->setTranslationZ(zTranslation);  // Applique la translation Z au widget
    ui->widget->update();  // Met à jour l'affichage du widget
    updateCoordinates(xTranslation, yTranslation, zTranslation);  // Met à jour le QLabel avec les nouvelles coordonnées
}

void MainWindow::on_scaleSliderX_actionTriggered(int action)
{
    // Mise à jour de l'échelle sur l'axe X
    scaleX = ui->scaleSliderX->value() / 5.0;  // Convertit la valeur en facteur d'échelle
    ui->widget->setScaleX(scaleX);  // Applique l'échelle X au widget
    ui->widget->update();  // Met à jour l'affichage du widget
}

void MainWindow::on_scaleSliderY_actionTriggered(int action)
{
    // Mise à jour de l'échelle sur l'axe Y
    scaleY = ui->scaleSliderY->value() / 5.0;  // Convertit la valeur en facteur d'échelle
    ui->widget->setScaleY(scaleY);  // Applique l'échelle Y au widget
    ui->widget->update();  // Met à jour l'affichage du widget
}

void MainWindow::on_scaleSliderZ_actionTriggered(int action)
{
    // Mise à jour de l'échelle sur l'axe Z
    scaleZ = ui->scaleSliderZ->value() / 5.0;  // Convertit la valeur en facteur d'échelle
    ui->widget->setScaleZ(scaleZ);  // Applique l'échelle Z au widget
    ui->widget->update();  // Met à jour l'affichage du widget
}


void MainWindow::on_savebtn_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL corrigée du script PHP
    QUrl url("http://dengtech.systems/data/mysqlopengl/opengl_save_api.php"); // Assurez-vous que "localhost" pointe vers votre serveur WAMP
    // Préparer les données à envoyer
    QUrlQuery params;
    params.addQueryItem("translationx", QString::number(xTranslation)); // Ajouter la translation X
    params.addQueryItem("translationy", QString::number(yTranslation)); // Ajouter la translation Y
    params.addQueryItem("translationz", QString::number(zTranslation)); // Ajouter la translation Z
    params.addQueryItem("rotationx", QString::number(xRotation)); // Ajouter la rotation X
    params.addQueryItem("rotationy", QString::number(yRotation)); // Ajouter la rotation Y
    params.addQueryItem("rotationz", QString::number(zRotation)); // Ajouter la rotation Z
    params.addQueryItem("scalex", QString::number(scaleX)); // Ajouter l'échelle X
    params.addQueryItem("scaley", QString::number(scaleY)); // Ajouter l'échelle Y
    params.addQueryItem("scalez", QString::number(scaleZ)); // Ajouter l'échelle Z

    // Préparer la requête
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"); // Définir le type de contenu

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, params.query().toUtf8());

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll(); // Lire la réponse brute
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response); // Convertir en document JSON
            QJsonObject jsonObj = jsonDoc.object(); // Extraire l'objet JSON

            if (jsonObj["success"].toBool()) {
                // Si l'opération a réussi
                QMessageBox::information(nullptr, "Succès", jsonObj["message"].toString());
            } else {
                // En cas d'échec
                QMessageBox::critical(nullptr, "Erreur", jsonObj["message"].toString());
            }
        } else {
            // Afficher un message d'erreur si le serveur est inaccessible
            QMessageBox::critical(nullptr, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater(); // Libérer la mémoire du reply
    });
}

void MainWindow::on_loadbtn_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL du script PHP
    QUrl url("http://dengtech.systems/data/mysqlopengl/opengl_load_api.php"); // Remplacez par l'URL correcte
    // Préparer la requête
    QNetworkRequest request(url);

    // Envoyer la requête GET
    QNetworkReply *reply = manager->get(request);

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray response = reply->readAll(); // Lire la réponse brute
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response); // Convertir en document JSON
            QJsonObject jsonObj = jsonDoc.object(); // Extraire l'objet JSON

            if (jsonObj["success"].toBool()) {
                // Si l'opération a réussi, extraire les données
                QJsonObject data = jsonObj["data"].toObject();
                double tx = data["translationx"].toDouble(); // Translation X
                double ty = data["translationy"].toDouble(); // Translation Y
                double tz = data["translationz"].toDouble(); // Translation Z
                double rx = data["rotationx"].toDouble(); // Rotation X
                double ry = data["rotationy"].toDouble(); // Rotation Y
                double rz = data["rotationz"].toDouble(); // Rotation Z
                double sx = data["scalex"].toDouble(); // Échelle X
                double sy = data["scaley"].toDouble(); // Échelle Y
                double sz = data["scalez"].toDouble(); // Échelle Z

                // Mettre à jour les sliders
                ui->translationSliderX->setValue(tx * 100); // Normalisation pour le slider
                ui->translationSliderY->setValue(ty * 100);
                ui->translationSliderZ->setValue(tz * 100);
                ui->rotationSliderX->setValue(rx);
                ui->rotationSliderY->setValue(ry);
                ui->rotationSliderZ->setValue(rz);
                ui->scaleSliderX->setValue(sx * 5); // Normalisation pour le slider
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
                ui->widget->update(); // Mettre à jour l'affichage

                // Mettre à jour les coordonnées affichées dans le QLabel
                updateCoordinates(tx, ty, tz);
            } else {
                // En cas d'erreur
                QMessageBox::critical(this, "Erreur", jsonObj["message"].toString());
            }
        } else {
            // Afficher un message d'erreur si le serveur est inaccessible
            QMessageBox::critical(this, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater(); // Libérer la mémoire du reply
    });
}


void MainWindow::on_readbtn_clicked()
{
    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL du script PHP
    QUrl url("http://dengtech.systems/data/mysqlopengl/opengl_read_api.php"); // Assurez-vous que cette URL correspond à votre configuration
    // Préparer la requête
    QNetworkRequest request(url);

    // Envoyer la requête GET
    QNetworkReply *reply = manager->get(request);

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll(); // Lire la réponse brute du serveur
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response); // Convertir la réponse en document JSON
            QJsonObject jsonObj = jsonDoc.object(); // Extraire l'objet JSON

            if (jsonObj["success"].toBool()) {
                // Extraire le tableau de données
                QJsonArray data = jsonObj["data"].toArray();

                // Vider la table avant de la remplir
                ui->table->setRowCount(0);

                // Configurer les colonnes de la table
                ui->table->setColumnCount(10); // Nombre de colonnes
                ui->table->setHorizontalHeaderLabels({"ID", "TranslationX", "TranslationY", "TranslationZ",
                                                      "RotationX", "RotationY", "RotationZ",
                                                      "ScaleX", "ScaleY", "ScaleZ"});

                // Remplir la table avec les données
                for (int i = 0; i < data.size(); ++i) {
                    QJsonObject row = data[i].toObject(); // Chaque élément est un objet JSON représentant une ligne

                    // Insérer une nouvelle ligne
                    ui->table->insertRow(i);

                    // Remplir chaque colonne avec les données correspondantes
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

                QMessageBox::information(this, "Succès", "Données chargées avec succès.");
            } else {
                QMessageBox::critical(this, "Erreur", jsonObj["message"].toString());
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater(); // Libérer la mémoire associée au reply
    });
}

void MainWindow::on_deletebtn_clicked()
{
    // Récupérer l'ID saisi par l'utilisateur
    QString id = ui->ID_text->text();

    // Créer un gestionnaire réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // URL du script PHP pour la suppression
    QUrl url("http://dengtech.systems/data/mysqlopengl/opengl_delete_api.php"); // Assurez-vous que cette URL correspond à votre configuration
    // Préparer les données à envoyer
    QUrlQuery params;
    params.addQueryItem("id", QString::number(id.toInt())); // Ajouter l'ID comme paramètre

    // Préparer la requête
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded"); // Type de contenu

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, params.query().toUtf8());

    // Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll(); // Lire la réponse brute du serveur
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response); // Convertir en document JSON
            QJsonObject jsonObj = jsonDoc.object(); // Extraire l'objet JSON

            if (jsonObj["success"].toBool()) {
                // En cas de succès
                QMessageBox::information(nullptr, "Succès", jsonObj["message"].toString());
            } else {
                // En cas d'erreur côté serveur
                QMessageBox::critical(nullptr, "Erreur", jsonObj["message"].toString());
            }
        } else {
            // Afficher un message d'erreur si le serveur est inaccessible
            QMessageBox::critical(nullptr, "Erreur", "Impossible de contacter le serveur : " + reply->errorString());
        }
        reply->deleteLater(); // Libérer la mémoire associée au reply
    });
}
