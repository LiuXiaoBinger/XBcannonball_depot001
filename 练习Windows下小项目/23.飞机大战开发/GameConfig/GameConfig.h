#pragma once


#define PATH_PIC(PIC_NAME) "./res/"#PIC_NAME


//背景图的高度、宽度
#define IMG_BACKGROUND_WIDTH    600
#define IMG_BACKGROUND_HEIGHT   800

#define IMG_PLAYER_WIDHT      60
#define IMG_PLAYER_HEIGHT     60

#define IMG_GUNNER_WIDHT      6
#define IMG_GUNNER_HEIGHT     20

#define IMG_FOEBIG_WIDHT      150
#define IMG_FOEBIG_HEIGHT     100

#define IMG_FOEMID_WIDHT     80  
#define IMG_FOEMID_HEIGHT    60

#define IMG_FOESMA_WIDHT     60
#define IMG_FOESMA_HEIGHT    40




#define WINDOW_X   200
#define WINDOW_Y   20
//窗口的大小
#define WINDOW_WIDTH    IMG_BACKGROUND_WIDTH+16
#define WINDOW_HEIGHT   IMG_BACKGROUND_HEIGHT+39
#define WINDOW_TITLE    "飞机大战"








//------------------------------------------------------

#define TIMER_BACKGROUND_MOVE_ID           1
#define TIMER_BACKGROUND_MOVE_INTERVAL     60
#define TIMER_BACKGROUND_MOVE_STEP         3


#define TIMER_PLAYER_MOVE_ID              2
#define TIMER_PLAYER_MOVE_INTERVAL        30
#define TIMER_PLAYER_MOVE_STEP            3

//炮弹移动定时器
#define TIMER_GUNNER_MOVE_ID              3
#define TIMER_GUNNER_MOVE_INTERVAL        80
#define TIMER_GUNNER_MOVE_STEP            8


#define TIMER_GUNNER_SEND_ID              4
#define TIMER_GUNNER_SEND_INTERVAL        800


#define TIMER_FOEBIG_MOVE_ID              5
#define TIMER_FOEBIG_MOVE_INTERVAL        200
#define TIMER_FOEBIG_MOVE_STEP            5
#define TIMER_FOEMID_MOVE_STEP            8
#define TIMER_FOESMA_MOVE_STEP            12

#define TIMER_FOEBIG_CREATE_ID              6
#define TIMER_FOEBIG_CREATE_INTERVAL        12000

#define TIMER_FOEMID_CREATE_ID              7
#define TIMER_FOEMID_CREATE_INTERVAL        9000

#define TIMER_FOESMA_CREATE_ID              8
#define TIMER_FOESMA_CREATE_INTERVAL        6000


#define TIMER_IS_HIT_ID                     9
#define TIMER_IS_HIT_INTERVAL               1


#define TIMER_CHANGE_SHOWID_ID                     10
#define TIMER_CHANGE_SHOWID_INTERVAL               300



//----BLOOD-----------------------------------
#define DEF_FOEBIG_BLOOD    5
#define DEF_FOEMID_BLOOD    3
#define DEF_FOESMA_BLOOD    1

#define DEF_GUNNER_HURT     1