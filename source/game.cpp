#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QBrush>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>
#include <QtGlobal>
#include <QTime>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Game.h"
#include "Button.h"
#include "TankButton.h"
#include "playercontroler.h"
#include "setting.h"
#include "wall.h"
#include "state_box.h"

#define RESTART_CODE 1000

extern QApplication * app;

Game::Game(QWidget *parent): QGraphicsView(parent){
    show();
    //showFullScreen();

    // import the images
    tankButtonImages[0] = new QPixmap(":/images/button_tank1.png");
    tankButtonImages[1] = new QPixmap(":/images/button_tank2.png");
    tankButtonImages[2] = new QPixmap(":/images/button_tank3.png");
    tankButtonImages[3] = new QPixmap(":/images/button_tank4.png");
    tankButtonImages[4] = new QPixmap(":/images/button_tank5.png");
    tankButtonImages[5] = new QPixmap(":/images/button_tank6.png");

    tankButtonSelectedImages[0] = new QPixmap(":/images/button_select_tank1.png");
    tankButtonSelectedImages[1] = new QPixmap(":/images/button_select_tank2.png");
    tankButtonSelectedImages[2] = new QPixmap(":/images/button_select_tank3.png");
    tankButtonSelectedImages[3] = new QPixmap(":/images/button_select_tank4.png");
    tankButtonSelectedImages[4] = new QPixmap(":/images/button_select_tank5.png");
    tankButtonSelectedImages[5] = new QPixmap(":/images/button_select_tank6.png");

    mapButtonImages[0] = new QPixmap(":/images/button_map1.png");
    mapButtonImages[1] = new QPixmap(":/images/button_map2.png");
    mapButtonImages[2] = new QPixmap(":/images/button_map3.png");
    mapButtonImages[3] = new QPixmap(":/images/button_map4.png");
    mapButtonImages[4] = new QPixmap(":/images/button_map5.png");
    mapButtonImages[5] = new QPixmap(":/images/button_map6.png");

    mapButtonSelectedImages[0] = new QPixmap(":/images/button_select_map1.png");
    mapButtonSelectedImages[1] = new QPixmap(":/images/button_select_map2.png");
    mapButtonSelectedImages[2] = new QPixmap(":/images/button_select_map3.png");
    mapButtonSelectedImages[3] = new QPixmap(":/images/button_select_map4.png");
    mapButtonSelectedImages[4] = new QPixmap(":/images/button_select_map5.png");
    mapButtonSelectedImages[5] = new QPixmap(":/images/button_select_map6.png");

    tankInformationImages[0] = new QPixmap(":/images/tank_information1.png");
    tankInformationImages[1] = new QPixmap(":/images/tank_information2.png");
    tankInformationImages[2] = new QPixmap(":/images/tank_information3.png");
    tankInformationImages[3] = new QPixmap(":/images/tank_information4.png");
    tankInformationImages[4] = new QPixmap(":/images/tank_information5.png");
    tankInformationImages[5] = new QPixmap(":/images/tank_information6.png");

    //
    isOver = false;

    // 0 for starting scene
    current = 0;

    // create the starting scene
    startScene = new QGraphicsScene(this);
    startScene->setSceneRect(0,0,SCREEN_WIDTH,GAME_SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage(":/images/startScreen.png")));
    setScene(startScene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH,GAME_SCREEN_HEIGHT);

    // create the starting button
    startButton = new Button();
    QPixmap p(":/images/button_start.png");
    startButton->setPixmap(p);

    // the button's position
    startButton->setGeometry(SCREEN_WIDTH/2-410,GAME_SCREEN_HEIGHT-360,p.width(),p.height());
    startScene->addWidget(startButton);
    startButton->setAttribute(Qt::WA_TranslucentBackground);
    //qDebug() << p.width();
    startButton->setFocus();

    // set the tank information box
    tankInformationBox = new QGraphicsPixmapItem();
    tankInformationBox->setPos(670,130);
    tankInformationBox->setPixmap(*tankInformationImages[0]);

    // set the tank button of select scene
    for (int i = 0; i < 6; i++){
        tankButtonP1[i] = new TankButton(i + 1);
        tankButtonP2[i] = new TankButton(i + 1);
        mapButton[i] = new TankButton(i + 1);
    }
    // set image
    for (int i = 0; i < 6; i++){
        tankButtonP1[i]->setPixmap(*tankButtonImages[i]);
        tankButtonP2[i]->setPixmap(*tankButtonImages[i]);
        mapButton[i]->setPixmap(*mapButtonImages[i]);
    }

    // set connect to tank button that let it change when focus changed
    for (int i = 0; i < 6; i++){
        connect(tankButtonP1[i],SIGNAL(focusOut(int)),this,SLOT(setFocusOutP1(int)));
        connect(tankButtonP1[i],SIGNAL(focusIn(int)),this,SLOT(setFocusInP1(int)));
        connect(tankButtonP2[i],SIGNAL(focusOut(int)),this,SLOT(setFocusOutP2(int)));
        connect(tankButtonP2[i],SIGNAL(focusIn(int)),this,SLOT(setFocusInP2(int)));
    }

    // set bgm
    start_bgm_list = new QMediaPlaylist(this);
    start_bgm_list->addMedia(QUrl("qrc:/sounds/Flutey.mp3"));
    start_bgm_list->setPlaybackMode(QMediaPlaylist::Loop);

    start_bgm = new QMediaPlayer(this);
    start_bgm->setPlaylist(start_bgm_list);
    start_bgm->setVolume(30);

    game_bgm = new QMediaPlayer(this);
    game_bgm->setMedia(QUrl("qrc:/sounds/Battlefield.mp3"));
    game_bgm->setVolume(30);

    start_bgm->play();

    // check if the button is pressed
    connect(startButton,SIGNAL(clicked()),this,SLOT(setChooseSceneP1()));
}

Game::~Game(){

    // button

    delete startButton;
    for (int i = 0; i < 6; i++){
        delete tankButtonP1[i];
        delete tankButtonP2[i];
        delete mapButton[i];
    }
    delete restart;
    delete quit;

    delete start_bgm_list;
    delete start_bgm;
    delete game_bgm;

    delete timerB;

    delete startScene;
    delete selectScene;
    delete mapScene;
    delete gameScene;
    delete gameoverScene;

    for (int i = 0; i < 6; i++){
        delete tankButtonImages[i];
        delete tankButtonSelectedImages[i];
        delete mapButtonImages[i];
        delete mapButtonSelectedImages[i];
        delete tankInformationImages[i];
    }
}

void Game::setChooseSceneP1(){
    // 1 for 1P
    current = 1;

    selectScene = new QGraphicsScene(this);
    selectScene->setSceneRect(0,0,SCREEN_WIDTH,GAME_SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage(":/images/selectScreenP1.png")));
    setScene(selectScene);

    // add the information box
    selectScene->addItem(tankInformationBox);

    // set position
    tankButtonP1[0]->setGeometry(110,140,190,190);
    tankButtonP1[1]->setGeometry(360,140,190,190);
    tankButtonP1[2]->setGeometry(110,370,190,190);
    tankButtonP1[3]->setGeometry(360,370,190,190);
    tankButtonP1[4]->setGeometry(110,600,190,190);
    tankButtonP1[5]->setGeometry(360,600,190,190);

    // set focusable
    for (int i = 5; i >= 0; i--){
        selectScene->addWidget(tankButtonP1[i]);
        tankButtonP1[i]->setAttribute(Qt::WA_TranslucentBackground);
        tankButtonP1[i]->setFocus();
    }

    for (int i = 0; i < 6; i++){
        connect(tankButtonP1[i],SIGNAL(clicked(int)),this,SLOT(setChooseSceneP2(int)));
    }
}

void Game::setChooseSceneP2(int ty1){
    // 2 for 2P
    current = 2;
    tankTypeP1 = ty1;
    setBackgroundBrush(QBrush(QImage(":/images/selectScreenP2.png")));
    setScene(selectScene);

    // set position
    tankButtonP2[0]->setGeometry(110,140,190,190);
    tankButtonP2[1]->setGeometry(360,140,190,190);
    tankButtonP2[2]->setGeometry(110,370,190,190);
    tankButtonP2[3]->setGeometry(360,370,190,190);
    tankButtonP2[4]->setGeometry(110,600,190,190);
    tankButtonP2[5]->setGeometry(360,600,190,190);

    // set focusable
    for (int i = 5; i >= 0; i--){
        selectScene->addWidget(tankButtonP2[i]);
        tankButtonP2[i]->setAttribute(Qt::WA_TranslucentBackground);
        tankButtonP2[i]->setFocus();
    }

    for (int i = 0; i < 6; i++){
        connect(tankButtonP2[i],SIGNAL(clicked(int)),this,SLOT(setMapScene(int)));
    }
}

void Game::setMapScene(int ty2){
    // 3 for map
    current = 3;
    tankTypeP2 = ty2;
    mapScene = new QGraphicsScene(this);
    mapScene->setSceneRect(0,0,SCREEN_WIDTH,GAME_SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage(":/images/mapScreen.png")));
    setScene(mapScene);

    // set position
    mapButton[0]->setGeometry(110,220,350,210);
    mapButton[1]->setGeometry(480,220,350,210);
    mapButton[2]->setGeometry(850,220,350,210);
    mapButton[3]->setGeometry(90,500,350,210);
    mapButton[4]->setGeometry(460,500,350,210);
    mapButton[5]->setGeometry(830,500,350,210);

    // set focusable
    for (int i = 5; i >= 0; i--){
        mapScene->addWidget(mapButton[i]);
        mapButton[i]->setAttribute(Qt::WA_TranslucentBackground);
        mapButton[i]->setFocus();
    }
    mapButton[0]->setPixmap(QPixmap(":/images/button_select_map1.png"));

    // set connect
    for (int i = 0; i < 6; i++){
        connect(mapButton[i],SIGNAL(focusOut(int)),this,SLOT(setFocusOutMap(int)));
        connect(mapButton[i],SIGNAL(focusIn(int)),this,SLOT(setFocusInMap(int)));

        // to game scene
        connect(mapButton[i],SIGNAL(clicked(int)),this,SLOT(setNewGame(int)));
    }
}

void Game::setNewGame(int map){
    // 4 for game scene
    current = 4;

    start_bgm->stop();
    game_bgm->play();

    mapType = map;
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,SCREEN_WIDTH,GAME_SCREEN_HEIGHT); // make the scene 1280 X 720 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(gameScene);

    // create the player
    player1 = new Player(1,tankTypeP1,270);
    player2 = new Player(2,tankTypeP2,90);
    controler = new PlayerControler();
    box1 = new State_Box(1,tankTypeP1);
    box2 = new State_Box(2,tankTypeP2);

    // initialize the start positions of two players
    player1->setPos(1160,600);
    player2->setPos(60,60);
    player1->setRotation(270);
    player2->setRotation(90);

    // make the controler focusable and set it to be the current focus
    controler->setFlag(QGraphicsItem::ItemIsFocusable);
    controler->setFocus();

    // add the players to the scene
    gameScene->addItem(player1);
    gameScene->addItem(player2);
    gameScene->addItem(controler);
    gameScene->addItem(box1);
    gameScene->addItem(box2);

    timerB = new QTimer(this);
    connect(timerB,SIGNAL(timeout()),player1,SLOT(addBullet()));
    connect(timerB,SIGNAL(timeout()),player2,SLOT(addBullet()));
    connect(timerB,SIGNAL(timeout()),box1,SLOT(AddBullet()));
    connect(timerB,SIGNAL(timeout()),box2,SLOT(AddBullet()));
    timerB->start(1000/TANK_ADD_BULLET_RATE);

    //draw the wall
    setWall(mapType);

    connect(player1,SIGNAL(dead(int)),this,SLOT(pause(int)));
    connect(player2,SIGNAL(dead(int)),this,SLOT(pause(int)));
}

void Game::setGameoverScene(){
    timerB->stop();
    gameScene->clear();
    // 5 for gameover scene
    current = 5;

    gameoverScene = new QGraphicsScene(this);
    gameoverScene->setSceneRect(0,0,SCREEN_WIDTH,GAME_SCREEN_HEIGHT);
    if (this->loser == 1){
        setBackgroundBrush(QBrush(QImage(":/images/gameoverScreenP2.png")));
        //qDebug() << "p2 win";
    }
    else if (this->loser == 2){
        setBackgroundBrush(QBrush(QImage(":/images/gameoverScreenP1.png")));
        //qDebug() << "p1 win";
    }
    setScene(gameoverScene);

    // create button
    restart = new TankButton(1);
    quit = new TankButton(2);
    restart->setPixmap(QPixmap(":/images/button_select_restart.png"));
    quit->setPixmap(QPixmap(":/images/button_quit.png"));

    // set button
    restart->setGeometry(97,755,446,110);
    quit->setGeometry(750,755,420,110);

    // set focusable
    gameoverScene->addWidget(restart);
    gameoverScene->addWidget(quit);
    restart->setAttribute(Qt::WA_TranslucentBackground);
    quit->setAttribute(Qt::WA_TranslucentBackground);
    quit->setFocus();
    restart->setFocus();

    connect(restart,SIGNAL(focusOut(int)),this,SLOT(setFocusOutRe(int)));
    connect(restart,SIGNAL(focusIn(int)),this,SLOT(setFocusInRe(int)));
    connect(restart,SIGNAL(clicked(int)),this,SLOT(gameover(int)));

    connect(quit,SIGNAL(focusOut(int)),this,SLOT(setFocusOutQu(int)));
    connect(quit,SIGNAL(focusIn(int)),this,SLOT(setFocusInQu(int)));
    connect(quit,SIGNAL(clicked(int)),this,SLOT(gameover(int)));
}

void Game::setFocusOutP1(int index){
    this->tankButtonP1[index]->setPixmap(*this->tankButtonImages[index]);
}

void Game::setFocusOutP2(int index){
    this->tankButtonP2[index]->setPixmap(*this->tankButtonImages[index]);
}

void Game::setFocusInP1(int index){
    this->tankButtonP1[index]->setPixmap(*this->tankButtonSelectedImages[index]);
    this->tankInformationBox->setPixmap(*this->tankInformationImages[index]);
}

void Game::setFocusInP2(int index){
    this->tankButtonP2[index]->setPixmap(*this->tankButtonSelectedImages[index]);
    this->tankInformationBox->setPixmap(*this->tankInformationImages[index]);
}

void Game::setFocusOutMap(int index){
    this->mapButton[index]->setPixmap(*this->mapButtonImages[index]);
}

void Game::setFocusInMap(int index){
    this->mapButton[index]->setPixmap(*this->mapButtonSelectedImages[index]);
}

void Game::setFocusOutRe(int){
    this->restart->setPixmap(QPixmap(":/images/button_restart.png"));
}

void Game::setFocusInRe(int){
    this->restart->setPixmap(QPixmap(":/images/button_select_restart.png"));
}

void Game::setFocusOutQu(int){
    this->quit->setPixmap(QPixmap(":/images/button_quit.png"));
}

void Game::setFocusInQu(int){
    this->quit->setPixmap(QPixmap(":/images/button_select_quit.png"));
}

void Game::setWall(int ty){

    if (ty == 1){
        w[0] = new Wall(0,0,1280,30);
        w[1] = new Wall(0,30,30,660);
        w[2] = new Wall(0,690,1280,30);
        w[3] = new Wall(1250,30,30,660);
        h[0] = new River(30,210,196,60);
        w[4] = new Wall(226,210,30,60);
        w[5] = new Wall(843,210,30,60);
        h[1] = new River(873,210,167,60);
        w[6] = new Wall(1040,210,30,60);
        w[7] = new Wall(210,450,30,60);
        h[2] = new River(240,450,167,60);
        w[8] = new Wall(407,450,30,60);
        h[3] = new River(1054,450,196,60);
        w[9] = new Wall(1024,450,30,60);
        h[4] = new River(567,287,146,146);
        w[10] = new Wall(537,257,206,30);
        w[11] = new Wall(537,287,30,176);
        w[12] = new Wall(713,287,30,176);
        w[13] = new Wall(567,433,146,30);
    }
    else if (ty == 2){
        w[0] = new Wall(0,0,1280,30);
        w[1] = new Wall(0,30,30,660);
        w[2] = new Wall(0,690,1280,30);
        w[3] = new Wall(1250,30,30,660);
        w[4] = new Wall(360,140,40,100);
        w[5] = new Wall(400,140,60,40);
        w[6] = new Wall(820,140,100,40);
        w[7] = new Wall(880,180,40,60);
        w[8] = new Wall(360,480,40,100);
        w[9] = new Wall(400,540,60,40);
        w[10] = new Wall(820,540,100,40);
        w[11] = new Wall(880,480,40,60);
        h[0] = new River(400,180,180,360);
        h[1] = new River(580,180,300,120);
        h[2] = new River(580,420,300,120);
        h[3] = new River(700,300,180,120);
        turret1 = new Turret();
        gameScene->addItem(turret1);
        turret1->setPos(590,310);
    }
    else if (ty == 3){
        w[0] = new Wall(0,0,1280,30);
        w[1] = new Wall(0,30,30,660);
        w[2] = new Wall(0,690,1280,30);
        w[3] = new Wall(1250,30,30,660);
        w[4] = new Wall(610,150,60,60);
        w[5] = new Wall(550,210,180,60);
        w[6] = new Wall(490,270,300,60);
        w[7] = new Wall(430,330,420,60);
        w[8] = new Wall(490,390,300,60);
        w[9] = new Wall(550,450,180,60);
        w[10] = new Wall(610,510,60,60);
        w[11] = new Wall(150,150,120,60);
        w[12] = new Wall(150,210,60,60);
        w[13] = new Wall(150,450,60,120);
        w[14] = new Wall(210,510,60,60);
        w[15] = new Wall(1010,150,120,60);
        w[16] = new Wall(1070,210,60,60);
        w[17] = new Wall(1010,510,120,60);
        w[18] = new Wall(1070,450,60,60);
    }
    else if (ty == 4){
        w[0] = new Wall(0,0,1280,30);
        w[1] = new Wall(0,30,30,660);
        w[2] = new Wall(0,690,1280,30);
        w[3] = new Wall(1250,30,30,660);
        w[4] = new Wall(30,210,246,60);
        h[0] = new River(276,210,60,60);
        h[1] = new River(336,210,60,60);
        w[5] = new Wall(396,210,245,60);
        h[2] = new River(641,210,60,60);
        h[3] = new River(701,210,60,60);
        w[6] = new Wall(761,210,245,60);
        w[7] = new Wall(1004,440,246,60);
        h[4] = new River(944,440,60,60);
        h[5] = new River(884,440,60,60);
        w[8] = new Wall(639,440,245,60);
        h[6] = new River(579,440,60,60);
        h[7] = new River(519,440,60,60);
        w[9] = new Wall(274,440,245,60);
    }
    else if (ty == 5){
        w[0] = new Wall(0,0,1280,30);
        w[1] = new Wall(0,30,30,660);
        w[2] = new Wall(0,690,1280,30);
        w[3] = new Wall(1250,30,30,660);
        w[4] = new Wall(286,360,240,30);
        w[5] = new Wall(286,510,240,30);
        w[6] = new Wall(784,180,240,30);
        w[7] = new Wall(784,330,240,30);
        h[0] = new River(286,30,240,330);
        h[1] = new River(286,540,240,150);
        h[2] = new River(784,30,240,150);
        h[3] = new River(784,360,240,330);

    }
    else if (ty == 6){ // random
        qsrand(QTime::currentTime().msec());
        int t = (qrand() % 5) + 1;
        mapType = t;
        setWall(mapType);
    }
}

void Game::pause(int loser){
    this->isOver = true;
    this->loser = loser;
    QTimer::singleShot(3000,this,SLOT(setGameoverScene()));
}

void Game::gameover(int CODE){
    if (CODE == RESTART_CODE){
        this->setVisible(false);
    }
    //delete game_bgm;
    delete this;
    app->exit(CODE);
}
