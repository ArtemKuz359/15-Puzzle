#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include "gamewindow.h"
#include <QTabBar>
#include <QStyleOption>
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);

    gameWindow = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    gameboard.start();
    gameWindow = new GameWindow(&gameboard, this);
    this->setCentralWidget(gameWindow);
}

void MainWindow::on_pushButton_4_clicked()
{

    QDialog *settingsDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(settingsDialog);


    QRadioButton *radioButton3x3 = new QRadioButton("3x3", settingsDialog);
    QRadioButton *radioButton4x4 = new QRadioButton("4x4", settingsDialog);
    QRadioButton *radioButton5x5 = new QRadioButton("5x5", settingsDialog);


    if (gameboard.dimension() == 3) {
        radioButton3x3->setChecked(true);
    } else if (gameboard.dimension() == 5) {
        radioButton5x5->setChecked(true);
    } else {
        radioButton4x4->setChecked(true);
    }


    layout->addWidget(radioButton3x3);
    layout->addWidget(radioButton4x4);
    layout->addWidget(radioButton5x5);


    QPushButton *applyButton = new QPushButton("Apply", settingsDialog);
    layout->addWidget(applyButton);


    connect(applyButton, &QPushButton::clicked, this, [&, settingsDialog, radioButton3x3, radioButton4x4, radioButton5x5]() {
        if (radioButton3x3->isChecked()) {
            gameboard.setBoardSize(3);
        } else if (radioButton5x5->isChecked()) {
            gameboard.setBoardSize(5);
        } else {
            gameboard.setBoardSize(4);
        }

        if (gameWindow != nullptr) {
            gameWindow->updateGameBoard();
        }
    });

    settingsDialog->open();
}





void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}
