#ifndef QIPAN_H
#define QIPAN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class qipan : public QWidget
{
    Q_OBJECT

public:
    explicit qipan(QWidget *parent = nullptr);
    enum  pieceColor { NONE, BLACK, WHITE }; // 枚举类型，表示棋子颜色

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    static const int ROW_COUNT = 15; // 棋盘行数
    static const int COL_COUNT = 15; // 棋盘列数



    QVector<QVector<pieceColor>> board_; // 二维向量，表示棋盘上各个位置的棋子颜色
    QLabel* piece_ = nullptr; // 表示当前玩家所下的棋子

    bool piecePress(pieceColor color, int x, int y); // 在(x,y)位置放置颜色为color的棋子，返回是否能落子
    bool winner(); // 判断是否已经有一方获胜
};

#endif // qipan_H
