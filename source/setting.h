#ifndef SETTING_H
#define SETTING_H

// screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int GAME_SCREEN_HEIGHT = 900;

// tank
const int TANK_AMOUNT = 6;
const int TANK_WIDTH = 60;
const int TANK_HEIGHT = 60;
const double TANK_REFRESH_RATE = 60; // it will impact the speed & angle change rate of the tank
const double ANGLE_PER_REFRESH = 3.3;
const double TANK_ADD_BULLET_RATE = 1;

// based on tank type
const double TANK_SPEED[TANK_AMOUNT] = {3,4,4.5,3,2,3};
const double TANK_MAX_HEALTH[TANK_AMOUNT] = {2000,1400,1600,2200,2600,1600};
const double TANK_MAX_POWER[TANK_AMOUNT] = {1000,1000,1000,1000,1000,1000};
const double TANK_POWER_RECOVER_RATE[TANK_AMOUNT] = {1,1,1,1,1,1};
const double TANK_POWER_CONSUME[TANK_AMOUNT] = {100,300,300,500,500,600};
const int MAX_MAGAZINE[TANK_AMOUNT] = {5,4,7,4,5,3};
const double BULLET_DAMAGE[TANK_AMOUNT] = {100,130,80,120,80,180};
const double BULLET_SPEED[TANK_AMOUNT]= {6,6,6,6,6,6};

// bullet
const double BULLET_REFRESH_RATE = 100; // it will impact the speed of the bullet
const double BULLET_CREATE_RATE = 4; // the number of shot bullets per second

// sound effect
const int EFFECT_VOLUME[6] = {80,80,100,50,50,50};
#endif // SETTING_H

/*
灰色坦克：       1000                     500      500          傷害高子彈
紅色坦克：稍快    700     稍高     少1     520      416          穿牆彈
黃色坦克： 快     800      低      多2     490      343          dash(或刺針)
綠色坦克：        1200    稍高     少1     480      576         大顆子彈
藍色坦克：稍慢    1500     稍低            450      675          荊棘甲
紫色坦克：        800      高      少2     540      432         盾

         跑速 || 血量 || 傷害 || 彈夾 || 傷害力 // 血量*傷害力 // 特殊技能
*/
