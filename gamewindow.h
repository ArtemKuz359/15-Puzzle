#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTimer>

class GameBoard;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(GameBoard* gameboard, QWidget* parent = nullptr);
    void updateGameBoard();
    void onTileButtonClicked();
    void onTimerTimeout();
    void onExitButtonClicked();
    void resizeEvent(QResizeEvent* event) override;
private:

    GameBoard* m_gameboard;
    QGridLayout* m_gameBoardLayout;
    QVBoxLayout* m_layout;
    QLabel* m_timeLabel;
    QTime m_elapsedTime;
    QTimer* m_timer;
};

#endif // GAMEWINDOW_H
