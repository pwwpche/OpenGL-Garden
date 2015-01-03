#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QString>
#include <iostream>
#include <QLocale>
#include <QTimer>
#include <QFileDialog>
#include <QByteArray>
#include <QMessageBox>
#include "gltest.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
public slots:
    void createItem();
    void loadFile();
    void saveFile();
    void stopSnow();
    void startSnow();
    void setSnowArea();
    void setWindLevel();
    void setMeltingSpeed();
    void setFallSpeed();
private:
    QTimer *timer;
    void setupFlowers(int textureType, QString levels, int type, QString levelsCnt);
    void setupTrees(QString heightStr, QString widthStr, QString levelStr);
    Ui::MainWindow *ui;
    bool updateSwitch;
};

#endif // MAINWINDOW_H
