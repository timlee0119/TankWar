#ifndef TANKBUTTON_H
#define TANKBUTTON_H
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QObject>
#include <QMediaPlayer>

class TankButton: public QLabel{
    Q_OBJECT
private:
    int type;
    QMediaPlayer * choose;
    QMediaPlayer * select;
public:
    TankButton(int type);
    ~TankButton();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
signals:
    void clicked(int type);
    void focusIn(int index);
    void focusOut(int index);
};

#endif // TANKBUTTON_H
