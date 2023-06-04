#include "gamewindow.h"
#include "gameboard.h"
#include "qapplication.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTime>
#include <QTimer>

GameWindow::GameWindow(GameBoard* gameboard, QWidget* parent)
    : QWidget(parent), m_gameboard(gameboard),
      m_gameBoardLayout(new QGridLayout()), m_layout(new QVBoxLayout(this)),
      m_timeLabel(new QLabel(this)), m_elapsedTime(0, 0, 0),
      m_timer(new QTimer(this))
{

    QPushButton* exitButton = new QPushButton("EXIT", this);
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::onExitButtonClicked);
    exitButton->setMinimumSize(100,50);
    exitButton->setMaximumSize(10000,50);


    QWidget* gameBoardWidget = new QWidget(this);
    gameBoardWidget->setLayout(m_gameBoardLayout);
    layout()->addWidget(gameBoardWidget);

    QHBoxLayout* timerLayout = new QHBoxLayout();
      timerLayout->addStretch();
      timerLayout->addWidget(m_timeLabel);
      timerLayout->addStretch();


    layout()->addWidget(exitButton);

    const int dimension = gameboard->dimension();
    for (int row = 0; row < dimension; ++row) {
        for (int col = 0; col < dimension; ++col) {
            QPushButton* button = new QPushButton();
            button->setStyleSheet("background-color: white; border: 2px solid black; border-radius: 10px; font-weight: bold; font-size: 24px; color: black;");
            button->setMaximumSize(100, 100);

            connect(button, &QPushButton::clicked, this, &GameWindow::onTileButtonClicked);
            m_gameBoardLayout->addWidget(button, row, col);
        }
    }

    updateGameBoard();



    m_timeLabel = new QLabel("0:00", this);
    m_timeLabel->setStyleSheet("font-size: 24px; background-color: transparent; border: none;");

    m_timeLabel->setAttribute(Qt::WA_TranslucentBackground);






    m_elapsedTime = QTime(0, 0);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameWindow::onTimerTimeout);
    m_timer->start(1000);
}

void GameWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}
void GameWindow::onTileButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        int index = m_gameBoardLayout->indexOf(button);
        m_gameboard->move(index);
        updateGameBoard();
    }
}


void GameWindow::onTimerTimeout()
{
    m_elapsedTime = m_elapsedTime.addSecs(1);
    m_timeLabel->setText(m_elapsedTime.toString("mm:ss"));
}
void GameWindow::onExitButtonClicked()
{
    QApplication::quit();
}


void GameWindow::updateGameBoard()
{
    const int dimension = m_gameboard->dimension();
    bool isWinningState = true;

    for (int row = 0; row < dimension; ++row)
    {
        for (int col = 0; col < dimension; ++col)
        {
            int index = row * dimension + col;
            QPushButton* button = qobject_cast<QPushButton*>(m_gameBoardLayout->itemAtPosition(row, col)->widget());
            if (button)
            {
                int value = m_gameboard->data(m_gameboard->index(index), Qt::DisplayRole).toInt();
                if (value == (int)m_gameboard->boardSize())
                {
                    button->setText("");
                    button->setStyleSheet("background-color: #F0F0F0; border: 1px solid black; border-radius: 10px;");
                }
                else
                {
                    button->setText(QString::number(value));
                    button->setStyleSheet("background-color: #F0F0F0; border: 2px solid white; border-radius: 10px; font-weight: bold; font-size: 24px; color: black;");


                    if (value != index + 1)
                    {
                        isWinningState = false;
                    }
                }
            }
        }
    }


    if (isWinningState)
    {
        m_timer->stop();
        m_timeLabel->setText("YOU WON!");

        // Adjust the width of the time label to fit the "YOU WON" text
        QFontMetrics fontMetrics(m_timeLabel->font());
        QRect boundingRect = fontMetrics.boundingRect("YOU WON!");
        int textWidth = boundingRect.width();
        m_timeLabel->setFixedWidth(textWidth);
    }
}
