#include <QApplication>
#include "Game.h"
#include "setting.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QSize>

#define RESTART_CODE 1000

Game * game;

int main(int argc, char *argv[]){
    int CURRENT_CODE = 0;
    QApplication* app = new QApplication(argc, argv);
    do{
        //app->desktop()->screen()->resize(1680,1050);
        game = new Game();
        game->move(app->desktop()->screen()->rect().center() - game->rect().center());
        CURRENT_CODE = app->exec();

    }while(CURRENT_CODE == RESTART_CODE);

    return CURRENT_CODE;
}
