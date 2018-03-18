#ifndef BUTTON_H
#define BUTTON_H
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QObject>
#include <QMediaPlayer>

class Button: public QLabel{
    Q_OBJECT
public:
    Button();
    ~Button();
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QMediaPlayer * press;
signals:
    void clicked();
};

#endif // BUTTON_H
