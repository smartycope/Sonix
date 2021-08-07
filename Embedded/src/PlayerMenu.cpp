#include "Menu.h"


void PlayerMenu::start(){
    printDisplay(PLAYER_TITLE_COORD, player->book->title.c_str());
    printDisplay(PLAYER_PAUSE_COORD, "||");
    printDisplay(PLAYER_SKIP_FORWARD_COORD, ">|");
    printDisplay(PLAYER_SKIP_BACKWARD_COORD, "|<");
    refresh();
}


int PlayerMenu::Key1Pressed(){
    player->skipForward();
    return PLAYER_MENU;
}

int PlayerMenu::Key2Pressed(){
    player->togglePaused();
    return PLAYER_MENU;
}

int PlayerMenu::Key3Pressed(){
    player->skipBackward();
    return PLAYER_MENU;
}

int PlayerMenu::JoyUpPressed(){
    if (speedChangeMode)
        player->incrementSpeed();
    else
        player->incrementVolume();
    return PLAYER_MENU;
}

int PlayerMenu::JoyDownPressed(){
    if (speedChangeMode)
        player->decrementSpeed();
    else
        player->decrementVolume();
    return PLAYER_MENU;
}

int PlayerMenu::JoyLeftPressed(){
    return FILE_MENU;
}

int PlayerMenu::JoyRightPressed(){
    return PLAYER_MENU;
}

int PlayerMenu::JoyCenterPressed(){
    speedChangeMode = not speedChangeMode;
    if (speedChangeMode)
        printDisplay(PLAYER_SPEED_VOLUME_COORD, fmt("Speed: %d", player->getSpeed()).c_str());
    else
        printDisplay(PLAYER_SPEED_VOLUME_COORD, fmt("Volume: %d", player->getVolume()).c_str());

    GUI_Partial_Refresh(PLAYER_SPEED_VOLUME_COORD, BOTTOM_RIGHT);
    // GUI_Partial_Refresh(5, 200, 240, 240);
    return PLAYER_MENU;
}
