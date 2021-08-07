#pragma once

#include <string>
#include "Player.h"
#include "GUI_Paint.h"
#include "DEV_Config.h"
#include "GUI_BMP.h"
#include "fonts.h"

#define TOP_LEFT     0, 0
#define TOP_RIGHT    240, 0
#define BOTTOM_LEFT  0, 240
#define BOTTOM_RIGHT 240, 240
#define CENTER       120, 120

// #define FONT &Font16
// #define BACKGROUND_COLOR WHITE
// #define TEXT_COLOR       BLACK


#define PLAYER_SPEED_VOLUME_COORD 5, 200
#define PLAYER_TITLE_COORD 5, 5
#define PLAYER_PAUSE_COORD 230, 120
#define PLAYER_SKIP_FORWARD_COORD 230, 10
#define PLAYER_SKIP_BACKWARD_COORD 230, 230

using namespace std;

enum{
    PLAYER_MENU,
    // PLAYER = PLAYER_MENU,
    FILE_MENU,
    // FILE = FILE_MENU,
    SETTINGS_MENU,
    // SETTINGS = SETTINGS_MENU,
    BLUETOOTH_MENU,
    // BLUETOOTH = BLUETOOTH_MENU
};

class Menu{
public:
    int type;

    virtual void start();

    // They return what menu to switch to (it's own, if it does't switch)
    virtual int Key1Pressed();
    virtual int Key2Pressed();
    virtual int Key3Pressed();

    virtual int JoyUpPressed();
    virtual int JoyDownPressed();
    virtual int JoyLeftPressed();
    virtual int JoyRightPressed();
    virtual int JoyCenterPressed();

protected:
    sFONT* font = &Font16;
    const UWORD textColor = BLACK;
    const UWORD backgroundColor = WHITE;
    void printDisplay(UWORD x, UWORD y, const char* str) { Paint_DrawString_EN(x, y, str, font, textColor, backgroundColor); }
    void refresh() { GUI_Partial_Refresh(TOP_LEFT, BOTTOM_RIGHT); }
};

class PlayerMenu: public Menu{
public:
    int type;

    virtual void start();

    virtual int Key1Pressed();
    virtual int Key2Pressed();
    virtual int Key3Pressed();

    virtual int JoyUpPressed();
    virtual int JoyDownPressed();
    virtual int JoyLeftPressed();
    virtual int JoyRightPressed();
    virtual int JoyCenterPressed();

    PlayerMenu(Player* player): type(PLAYER_MENU), player(player), speedChangeMode(false){ }

private:
    Player* player;
    bool speedChangeMode;
};


class FileMenu: Menu{
public:
    int type;

    virtual void start();

    virtual int Key1Pressed();
    virtual int Key2Pressed();
    virtual int Key3Pressed();

    virtual int JoyUpPressed();
    virtual int JoyDownPressed();
    virtual int JoyLeftPressed();
    virtual int JoyRightPressed();
    virtual int JoyCenterPressed();

    // FileMenu();

private:
};


class BluetoothMenu: Menu{
public:
    int type;

    virtual void start();

    virtual int Key1Pressed();
    virtual int Key2Pressed();
    virtual int Key3Pressed();

    virtual int JoyUpPressed();
    virtual int JoyDownPressed();
    virtual int JoyLeftPressed();
    virtual int JoyRightPressed();
    virtual int JoyCenterPressed();

    // BluetoothMenu();

private:
};


class SettingsMenu: Menu{
public:
    int type;

    virtual void start();

    virtual int Key1Pressed();
    virtual int Key2Pressed();
    virtual int Key3Pressed();

    virtual int JoyUpPressed();
    virtual int JoyDownPressed();
    virtual int JoyLeftPressed();
    virtual int JoyRightPressed();
    virtual int JoyCenterPressed();

    // SettingsMenu();

private:
};