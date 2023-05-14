#include "qipan.h"
#include <QGridLayout>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include<QtDebug>
qipan::qipan(QWidget *parent) : QWidget(parent)
{
    setFixedSize(540, 540);
    setWindowTitle("黑子鸡子五子棋");
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            QLabel* cell = new QLabel(this);
            cell->setAlignment(Qt::AlignCenter);
            cell->setFixedSize(36, 36);
            cell->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); border: 1px solid rgb(0, 0, 0); }");
            layout->addWidget(cell, i, j);
        }
    }

    board_.resize(ROW_COUNT);
    for (int i = 0; i < ROW_COUNT; i++) {
        board_[i].resize(COL_COUNT);
    }
}
int check=-1;  //加入判断改哪一方下棋
void qipan::mousePressEvent(QMouseEvent *event)
{
      check*=-1;
    if(check == 1){        //轮到玩家1下棋
    qDebug() << "mouse pressed";
    int x1 = event->x();
    int y1 = event->y();

    // 检查鼠标点击的位置是否在棋盘内
//    if (x < 18 || y < 18 || x > 522 || y > 522) {
//        return;
//    }

    // 获取鼠标点击的单元格的行列坐标
    int row1 = y1 / 36;
    int col1 = x1 / 36;

    // 检查该单元格是否已经有棋子
    if (board_[row1][col1] != pieceColor::NONE) {
        return;
    }

    // 在该位置放置黑色棋子
    piecePress(pieceColor::BLACK,col1*36+18,row1*36+18);

    // 判断玩家1是否胜利
    bool won = winner();
    if (won) {
        QMessageBox::information(this, "Game Over", "小鸡子胜利!");

        return;
    }
    }
    if(-check == 1){     //轮到玩家2下棋
    // 生成玩家2的移动
    int x2 = event->x();
    int y2 = event->y();
     qDebug() << "mouse1 pressed";
    // 获取鼠标点击的单元格的行列坐标
    int row2 = y2 / 36;
    int col2 = x2 / 36;

    // 检查该单元格是否已经有棋子
    if (board_[row2][col2] != pieceColor::NONE) {
        return;
    }


    // 在该位置放置白色棋子
    piecePress(pieceColor::WHITE,col2*36+18,row2*36+18);

    // 判断玩家2是否胜利
  bool  won = winner();
    if (won) {
        QMessageBox::information(this, "Game Over", "小黑子胜利!");
        return;
    }
    }

        }

        void qipan::paintEvent(QPaintEvent *event)
        {
        QWidget::paintEvent(event);
        QPainter painter(this);
        QPixmap board(":/cxk.png"); // 加载棋盘图片
        painter.drawPixmap(0, 0, width(), height(), board); // 将棋盘绘制到窗口上
        }

        bool qipan::piecePress(pieceColor color, int x, int y)
        {
        // 创建一个QLabel用于表示新的棋子
        QLabel* piece = new QLabel(this);
        piece->setFixedSize(36, 36); // 设置棋子大小
        piece->move(x - 18, y - 18); // 设置棋子位置
        piece->setPixmap(QPixmap(color == pieceColor::BLACK ? ":/black.png" : ":/white.png").scaled(36,36)); // 根据颜色设置棋子图片
        piece->show(); // 显示棋子

        // 更新棋盘状态，将该位置标记为已经有棋子
        int row = (y - 18) / 36;
        int col = (x - 18) / 36;
        board_[row][col] = color;

        qDebug() << "added";

        return true; // 返回表示成功落子
        }

        bool qipan::winner()
        {
        // 判断横向是否有五个棋子相连
        for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j <= COL_COUNT - 5; j++) {
        if (board_[i][j] != pieceColor::NONE &&
        board_[i][j] == board_[i][j + 1] &&
        board_[i][j] == board_[i][j + 2] &&
        board_[i][j] == board_[i][j + 3] &&
        board_[i][j] == board_[i][j + 4]) {
        return true;
        }
        }
        }
        // 判断纵向是否有五个棋子相连
        for (int i = 0; i <= ROW_COUNT - 5; i++) {
            for (int j = 0; j < COL_COUNT; j++) {
                if (board_[i][j] != pieceColor::NONE &&
                    board_[i][j] == board_[i + 1][j] &&
                    board_[i][j] == board_[i + 2][j] &&
                    board_[i][j] == board_[i + 3][j] &&
                    board_[i][j] == board_[i + 4][j]) {
                    return true;
                }
            }
        }
        // 判断正斜线是否有五个棋子相连
        for (int i = 0; i <= ROW_COUNT - 5; i++) {
            for (int j = 0; j <= COL_COUNT - 5; j++) {
                if (board_[i][j] != pieceColor::NONE &&
                    board_[i][j] == board_[i + 1][j + 1] &&
                    board_[i][j] == board_[i + 2][j + 2] &&
                    board_[i][j] == board_[i + 3][j + 3] &&
                    board_[i][j] == board_[i + 4][j + 4]) {
                    return true;
                }
            }
        }
        // 判断反斜线是否有五个棋子相连
        for (int i = 0; i <= ROW_COUNT - 5; i++) {
            for (int j = 4; j < COL_COUNT; j++) {
                if (board_[i][j] != pieceColor::NONE &&
                    board_[i][j] == board_[i + 1][j - 1] &&
                    board_[i][j] == board_[i +2][j - 2] &&
                        board_[i][j] == board_[i + 3][j - 3] &&
                        board_[i][j] == board_[i + 4][j - 4]) {
                        return true;
                 }
             }
        }
       return false; // 没有获胜
        }

