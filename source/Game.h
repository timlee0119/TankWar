#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QPixmap>
#include <QWidget>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "playercontroler.h"
#include "Player.h"
#include "turret.h"
#include "Button.h"
#include "TankButton.h"
#include "wall.h"
#include "river.h"
#include "state_box.h"

class Game: public QGraphicsView{
    Q_OBJECT
    friend class Button;
    friend class TankButton;
public:
    Game(QWidget * parent=0);
    ~Game();
    // scene
    QGraphicsScene * startScene;
    QGraphicsScene * selectScene;
    QGraphicsScene * mapScene;
    QGraphicsScene * gameScene;
    QGraphicsScene * gameoverScene;

    // buttons
    // current 0
    Button * startButton;
    // curremt 1
    TankButton * tankButtonP1[6];
    QGraphicsPixmapItem * tankInformationBox;
    // current 2
    TankButton * tankButtonP2[6];
    // current 3
    TankButton * mapButton[6]; // 我懶得重寫一個class了XD
    // current 5
    TankButton * restart;
    TankButton * quit;

    // game
    PlayerControler * controler;
    Player * player1;
    Player * player2;
    State_Box * box1;
    State_Box * box2;
    QTimer * timerB; // for creating bullet

    //turret for game 2
    Turret * turret1;

    // store the player information
    int tankTypeP1;
    int tankTypeP2;
    int mapType;
    int current; // store the current window
    int loser;

    // maps' information
    int Wall_Number[5] = {14,12,19,10,8};
    int Hole_Number[5] = {5,4,0,8,4};
    Wall* w[20];
    River* h[20];

    // dont reduce health
    bool isOver;

    // bgm
    QMediaPlaylist * start_bgm_list;
    QMediaPlayer * start_bgm;
    QMediaPlayer * game_bgm;

    // store the images
    QPixmap * tankButtonImages[6];
    QPixmap * tankButtonSelectedImages[6];
    QPixmap * mapButtonImages[6];
    QPixmap * mapButtonSelectedImages[6];
    QPixmap * tankInformationImages[6];

public slots:
    // select
    void setChooseSceneP1();
    void setChooseSceneP2(int);
    void setMapScene(int);

    // game
    void setNewGame(int);

    // gameover
    void setGameoverScene();

    // when buttons are selected
    void setFocusOutP1(int);
    void setFocusOutP2(int);
    void setFocusInP1(int);
    void setFocusInP2(int);
    void setFocusOutMap(int);
    void setFocusInMap(int);
    void setFocusOutRe(int);
    void setFocusInRe(int);
    void setFocusOutQu(int);
    void setFocusInQu(int);

    // draw thw map
    void setWall(int);

    // pause
    void pause(int);

    // restart or quit
    void gameover(int);
};

#endif // GAME_H
