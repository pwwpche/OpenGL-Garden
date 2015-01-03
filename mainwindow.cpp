#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <gl/glut.h>
#include <stdio.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //updateSwitch = false;
    connect(ui->buttonCreate, SIGNAL(clicked()), this, SLOT(createItem()));
    connect(ui->buttonRead, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(ui->scrollFlakeCount, SIGNAL(valueChanged(int)), this, SLOT(startSnow()));
    connect(ui->scrollSnowArea, SIGNAL(valueChanged(int)), this, SLOT(setSnowArea()));
    connect(ui->scrollMeltSpeed, SIGNAL(valueChanged(int)), this, SLOT(setMeltingSpeed()));
    connect(ui->scrollWindLevel, SIGNAL(valueChanged(int)), this, SLOT(setWindLevel()));
    connect(ui->dialWind, SIGNAL(valueChanged(int)), this, SLOT(setWindLevel()));
    connect(ui->scrollFalSpeed, SIGNAL(valueChanged(int)), this, SLOT(setFallSpeed()));
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), ui->widget, SLOT(updateGL()));
    timer->start(10);

    ui->statusBar->showMessage("前进：↑      后退：↓      左转：←       右转：→      向上:PgUp      向下：PgDn      跳跃：Space      升高地形：鼠标左      降低地形：鼠标右");
}

MainWindow::~MainWindow()
{
    delete ui;    
}

void MainWindow::loadFile(){
    QString filename = QFileDialog::getOpenFileName(this,"Load File",QDir::currentPath());
    if (!filename.isNull()) {        
        ui->widget->loadFile((const char *)(filename.toLocal8Bit()));
    }else{
    }
    return ;
}

void MainWindow::saveFile(){

        QString filename = QFileDialog::getSaveFileName(this, "Load File", QDir::currentPath());
         if (!filename.isNull()) {
            ui->widget->saveFile((const char *)(filename.toLocal8Bit()));
        }

}

void MainWindow::stopSnow(){
    ui->widget->stopSnow();
}

void MainWindow::startSnow(){
    ui->labelFlakeCount->setText(QString::number(ui->scrollFlakeCount->value()));
    ui->widget->startSnow(ui->scrollFlakeCount->value());
}

void MainWindow::setSnowArea(){
    ui->labelSnowArea->setText(QString::number(ui->scrollSnowArea->value()));
    ui->widget->setSnowArea(ui->scrollSnowArea->value());
}

void MainWindow::setWindLevel(){
    float windLevel = ui->scrollWindLevel->value();
    ui->labelWindLevel->setText(QString::number(ui->scrollWindLevel->value()));
    windLevel = windLevel / 100.0 / 2;
    ui->widget->setWindLevel(ui->dialWind->value(),  windLevel);
}

void MainWindow::setMeltingSpeed(){
    ui->labelTemperature->setText(QString::number(ui->scrollMeltSpeed->value()));
    ui->widget->setMeltSpeed(ui->scrollMeltSpeed->value());
}

void MainWindow::setFallSpeed(){
    int val = ui->scrollFalSpeed->value();
    float speed = (float) val / 100.0 * -0.3 - 0.01;
    ui->labelFallSpeed->setText(QString::number(speed));
    ui->widget->setFallSpeed(speed);
}

void MainWindow::createItem(){
    ui->widget->setFocus();
    if(ui->radioFlowers->isChecked())    {
        QString levels = ui->lineFlowerLevels->text();
        int textureType = 0;
        int flowerType = 0;
        if(ui->radioFlowerA->isChecked()){
            flowerType = 0;
        }
        if(ui->radioFlowerB->isChecked()){
            flowerType = 1;
        }
        if(ui->radioFTexture1->isChecked()){
            textureType = 0;
        }
        if(ui->radioFTexture2->isChecked()){
            textureType =1;
        }
        if(ui->radioFTexture3->isChecked()){
            textureType = 2;
        }
        if(ui->radioFTexture4->isChecked()){
            textureType = 3;
        }
        QString flowerCnt = ui->lineFlowerLevenCnt->text();
        setupFlowers(textureType, levels, flowerType, flowerCnt);
    }else if(ui->radioTree->isChecked()){
        QString treeHeight = ui->lineTreeHeight->text();
        QString treeWidth = ui->lineTreeWidth->text();
        QString treeLevels = ui->lineTreeLevel->text();
        setupTrees(treeHeight, treeWidth, treeLevels);
    }
}

void MainWindow::setupTrees(QString heightStr, QString widthStr, QString levelStr){
    QLocale local;
    double height = local.toDouble(heightStr);
    double width =local.toDouble(widthStr);
    int level = local.toInt(levelStr);
    ui->widget->setupTrees(height, width, level);
}

void MainWindow::setupFlowers(int textureType, QString levelStr, int type, QString levelsCnt){
    QLocale local;

    int levels = local.toInt(levelStr);
    QTextStream stream(&levelsCnt);
    int level[20];
    int cnt = 0;
    int num = 0;
    while(1){
        stream >> num;
        cout << "steream_num" << num << endl;
        level[cnt] = num;
        cnt++;
        if(cnt > 18 || cnt > levels){
            break;
        }
        if(stream.atEnd()){
            break;
        }
    }

    ui->widget->setupFlowers(textureType, type, levels, level);
}


void MainWindow::keyPressEvent(QKeyEvent *e){
    //setFocusProxy(this);
    //ui->widget->keyPressEvent(e);
    //std::cout << "MainWindow focus" <<hasFocus() << std::endl;
    ui->widget->keyPressEvent2(e);
    //e->ignore();
}


void MainWindow::keyReleaseEvent(QKeyEvent *e){
    //std::cout << "MainWindow focus" <<hasFocus() << std::endl;
    //e->ignore();
    //setFocusProxy(this);
   ui->widget->keyReleaseEvent2(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        ui->widget->setGroundHeight(1);
    }
    if(e->button() == Qt::RightButton){
        ui->widget->setGroundHeight(-1);
    }
}
