#pragma once

#include <string>
using namespace std;

class Setting{
public:
    virtual int order;
    virtual string name;

    virtual void* setting;

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
};


class AutoSpeedMin: public Setting{
public:
    AutoSpeedMin(float* value): order(1), name("Auto Speed Start"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
};

class AutoSpeedMax: public Setting{
public:
    AutoSpeedMax(float* value): order(2), name("Auto Speed End"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}

class AutoSpeedDuration: public Setting{
public:
    AutoSpeedDuration(int* value): order(3), name("Auto Speed Duration"), setting(value) { } // int in hours

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}

class SonicQuality: public Setting{
public:
    SonicQuality(int* value): order(4), name("Sonic Quality"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}

class SonicRate: public Setting{
public:
    SonicRate(float* value): order(5), name("Sonic Rate"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}

class SonicPitch: public Setting{
public:
    SonicRate(float* value): order(6), name("Sonic Rate"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}

class SonicEmulateChoord: public Setting{
public:
    SonicEmulateChoord(bool* value): order(7), name("Emulate Choord Pitch"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}

class NonLinearSpeedup: public Setting{
public:
    NonLinearSpeedup(bool* value): order(8), name("Non-Linear Speedup"), setting(value) { }

    virtual void Key1Pressed();
    virtual void Key2Pressed();
    virtual void Key3Pressed();

    virtual void show();
private:
}
