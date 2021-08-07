#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include "sndfile.h"
#include "sonic.h"
#include "portaudio.h"
#include "cope.cpp"
#include "Book.h"
#include "Player.h"
#include "Menu.h"
// #include "PlayerMenu.cpp"
// #include "SettingsMenu.cpp"
// #include "BluetoothMenu.cpp"
// #include "FileMenu.cpp"
#include "DEV_Config.h"
// #include "DEV_Config.c"
#include "LCD_1in3.h"
// #include "LCD_1in3.c"
#include "GUI_Paint.h"
// #include "GUI_Paint.c"
// #include "GUI_BMP.h"
// #include "GUI_BMP.h"
// #include <curses.h>
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

using namespace std;


uint16_t* image;
Menu* currentMenu;


void initDisplay(){
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in3_LCD);

	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }

	LCD_1in3_Init(HORIZONTAL);
	LCD_1in3_Clear(WHITE);

    image = (uint16_t*)malloc(LCD_HEIGHT * LCD_WIDTH * 2);

    Paint_NewImage(image, LCD_WIDTH, LCD_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);
}


void refreshDisplay(){
    LCD_1in3_Display(image);
}

//* This is just to resolve scope so I don't have to put the menu instances in a global scope
#define switchMenu(menu) _switchMenu(menu, &playerMenu, &fileMenu, &settingsMenu, &bluetoothMenu)
void _switchMenu(int menu, PlayerMenu* playerMenu, FileMenu* fileMenu, SettingsMenu* settingsMenu, BluetoothMenu* bluetoothMenu){
    if (menu == PLAYER_MENU)
        currentMenu = playerMenu;
    // if (menu == BLUETOOTH_MENU)
    //     currentMenu = bluetoothMenu;
    // if (menu == SETTINGS_MENU)
    //     currentMenu = settingsMenu;
    // if (menu == FILE_MENU)
    //     currentMenu = fileMenu;

}


int main(int argc, char** argv) {
    // string inFileName = "/home/marvin/Snapshot.wav";
    string inFileName = "/home/pi/Snapshot.wav";

    Book* book = new Book(inFileName);
    Player* player = new Player(book);

    PlayerMenu    playerMenu(player);
    FileMenu      fileMenu;
    SettingsMenu  settingsMenu;
    BluetoothMenu bluetoothMenu;

    currentMenu = &playerMenu;

    player->setSpeed(2.0);

    while(1){
        if(GET_KEY_UP == 0){
            switchMenu(currentMenu->JoyUpPressed());
            while (GET_KEY_UP == 0) { }
        }
        if(GET_KEY_DOWN == 0){
            switchMenu(currentMenu->JoyDownPressed());
            while (GET_KEY_DOWN == 0) { }
        }
        if(GET_KEY_LEFT == 0){
            switchMenu(currentMenu->JoyLeftPressed());
            while (GET_KEY_LEFT == 0) { }
        }
        if(GET_KEY_RIGHT == 0){
            switchMenu(currentMenu->JoyRightPressed());
            while (GET_KEY_RIGHT == 0) { }
        }
        if(GET_KEY_PRESS == 0){
            switchMenu(currentMenu->JoyCenterPressed());
            while (GET_KEY_PRESS == 0) { }
        }
        if(GET_KEY1 == 0){
            switchMenu(currentMenu->Key1Pressed());
            while (GET_KEY1 == 0) { }
        }
        if(GET_KEY2 == 0){
            switchMenu(currentMenu->Key2Pressed());
            while (GET_KEY2 == 0) { }
        }
        if(GET_KEY3 == 0){
            switchMenu(currentMenu->Key3Pressed());
            while (GET_KEY3 == 0) { }
        }

        usleep(20);
    };

    delete book;
    delete player;

    free(image);
    image = NULL;
	DEV_ModuleExit();

    return 0;
}

// GetTermSize(&rows, &cols);
// alias build="cd ./build; make -j17; cd .."; alias run="build; ./sap /home/marvin/Media/Audiobooks/Snapshot.wav"

// static_cast<double>(frames())/samplerate() = duration

// #define KEY_UP_PIN      6
// #define KEY_DOWN_PIN    19
// #define KEY_LEFT_PIN    5
// #define KEY_RIGHT_PIN   26
// #define KEY_PRESS_PIN   13
// #define KEY1_PIN        21
// #define KEY2_PIN        20
// #define KEY3_PIN        16

// #define GET_KEY_UP       DEV_Digital_Read(KEY_UP_PIN)
// #define GET_KEY_DOWN     DEV_Digital_Read(KEY_DOWN_PIN)
// #define GET_KEY_LEFT     DEV_Digital_Read(KEY_LEFT_PIN)
// #define GET_KEY_RIGHT    DEV_Digital_Read(KEY_RIGHT_PIN)
// #define GET_KEY_PRESS    DEV_Digital_Read(KEY_PRESS_PIN)
// #define GET_KEY1         DEV_Digital_Read(KEY1_PIN)
// #define GET_KEY2         DEV_Digital_Read(KEY2_PIN)
// #define GET_KEY3         DEV_Digital_Read(KEY3_PIN)