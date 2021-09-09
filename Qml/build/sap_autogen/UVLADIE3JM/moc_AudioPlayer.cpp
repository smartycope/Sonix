/****************************************************************************
** Meta object code from reading C++ file 'AudioPlayer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/AudioPlayer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioPlayer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioPlayer_t {
    QByteArrayData data[62];
    char stringdata0[808];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioPlayer_t qt_meta_stringdata_AudioPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioPlayer"
QT_MOC_LITERAL(1, 12, 11), // "QML.Element"
QT_MOC_LITERAL(2, 24, 4), // "auto"
QT_MOC_LITERAL(3, 29, 17), // "samplerateChanged"
QT_MOC_LITERAL(4, 47, 0), // ""
QT_MOC_LITERAL(5, 48, 15), // "channelsChanged"
QT_MOC_LITERAL(6, 64, 12), // "speedChanged"
QT_MOC_LITERAL(7, 77, 12), // "pitchChanged"
QT_MOC_LITERAL(8, 90, 11), // "rateChanged"
QT_MOC_LITERAL(9, 102, 24), // "emulateChordPitchChanged"
QT_MOC_LITERAL(10, 127, 29), // "enableNonlinearSpeedupChanged"
QT_MOC_LITERAL(11, 157, 18), // "highQualityChanged"
QT_MOC_LITERAL(12, 176, 21), // "speedIncrementChanged"
QT_MOC_LITERAL(13, 198, 22), // "volumeIncrementChanged"
QT_MOC_LITERAL(14, 221, 18), // "skipSecondsChanged"
QT_MOC_LITERAL(15, 240, 10), // "samplerate"
QT_MOC_LITERAL(16, 251, 8), // "channels"
QT_MOC_LITERAL(17, 260, 5), // "speed"
QT_MOC_LITERAL(18, 266, 5), // "pitch"
QT_MOC_LITERAL(19, 272, 4), // "rate"
QT_MOC_LITERAL(20, 277, 17), // "emulateChordPitch"
QT_MOC_LITERAL(21, 295, 22), // "enableNonlinearSpeedup"
QT_MOC_LITERAL(22, 318, 11), // "highQuality"
QT_MOC_LITERAL(23, 330, 14), // "speedIncrement"
QT_MOC_LITERAL(24, 345, 15), // "volumeIncrement"
QT_MOC_LITERAL(25, 361, 11), // "skipSeconds"
QT_MOC_LITERAL(26, 373, 10), // "updateBook"
QT_MOC_LITERAL(27, 384, 5), // "Book*"
QT_MOC_LITERAL(28, 390, 4), // "book"
QT_MOC_LITERAL(29, 395, 9), // "getVolume"
QT_MOC_LITERAL(30, 405, 13), // "setSamplerate"
QT_MOC_LITERAL(31, 419, 2), // "to"
QT_MOC_LITERAL(32, 422, 11), // "setChannels"
QT_MOC_LITERAL(33, 434, 17), // "setSpeedIncrement"
QT_MOC_LITERAL(34, 452, 18), // "setVolumeIncrement"
QT_MOC_LITERAL(35, 471, 14), // "setSkipSeconds"
QT_MOC_LITERAL(36, 486, 11), // "togglePause"
QT_MOC_LITERAL(37, 498, 10), // "dummyparam"
QT_MOC_LITERAL(38, 509, 8), // "setSpeed"
QT_MOC_LITERAL(39, 518, 8), // "setPitch"
QT_MOC_LITERAL(40, 527, 7), // "setRate"
QT_MOC_LITERAL(41, 535, 20), // "setEmulateChordPitch"
QT_MOC_LITERAL(42, 556, 14), // "setHighQuality"
QT_MOC_LITERAL(43, 571, 25), // "setEnableNonlinearSpeedup"
QT_MOC_LITERAL(44, 597, 9), // "setVolume"
QT_MOC_LITERAL(45, 607, 4), // "skip"
QT_MOC_LITERAL(46, 612, 6), // "amount"
QT_MOC_LITERAL(47, 619, 4), // "jump"
QT_MOC_LITERAL(48, 624, 7), // "Chapter"
QT_MOC_LITERAL(49, 632, 13), // "updateChapter"
QT_MOC_LITERAL(50, 646, 11), // "updateSpeed"
QT_MOC_LITERAL(51, 658, 14), // "incrementSpeed"
QT_MOC_LITERAL(52, 673, 15), // "incrementVolume"
QT_MOC_LITERAL(53, 689, 14), // "decrementSpeed"
QT_MOC_LITERAL(54, 704, 15), // "decrementVolume"
QT_MOC_LITERAL(55, 720, 11), // "skipForward"
QT_MOC_LITERAL(56, 732, 12), // "skipBackward"
QT_MOC_LITERAL(57, 745, 11), // "jumpForward"
QT_MOC_LITERAL(58, 757, 12), // "jumpBackward"
QT_MOC_LITERAL(59, 770, 17), // "audioStateChanged"
QT_MOC_LITERAL(60, 788, 13), // "QAudio::State"
QT_MOC_LITERAL(61, 802, 5) // "state"

    },
    "AudioPlayer\0QML.Element\0auto\0"
    "samplerateChanged\0\0channelsChanged\0"
    "speedChanged\0pitchChanged\0rateChanged\0"
    "emulateChordPitchChanged\0"
    "enableNonlinearSpeedupChanged\0"
    "highQualityChanged\0speedIncrementChanged\0"
    "volumeIncrementChanged\0skipSecondsChanged\0"
    "samplerate\0channels\0speed\0pitch\0rate\0"
    "emulateChordPitch\0enableNonlinearSpeedup\0"
    "highQuality\0speedIncrement\0volumeIncrement\0"
    "skipSeconds\0updateBook\0Book*\0book\0"
    "getVolume\0setSamplerate\0to\0setChannels\0"
    "setSpeedIncrement\0setVolumeIncrement\0"
    "setSkipSeconds\0togglePause\0dummyparam\0"
    "setSpeed\0setPitch\0setRate\0"
    "setEmulateChordPitch\0setHighQuality\0"
    "setEnableNonlinearSpeedup\0setVolume\0"
    "skip\0amount\0jump\0Chapter\0updateChapter\0"
    "updateSpeed\0incrementSpeed\0incrementVolume\0"
    "decrementSpeed\0decrementVolume\0"
    "skipForward\0skipBackward\0jumpForward\0"
    "jumpBackward\0audioStateChanged\0"
    "QAudio::State\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      51,   16, // methods
      11,  356, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,  271,    4, 0x06 /* Public */,
       5,    0,  272,    4, 0x06 /* Public */,
       6,    0,  273,    4, 0x06 /* Public */,
       7,    0,  274,    4, 0x06 /* Public */,
       8,    0,  275,    4, 0x06 /* Public */,
       9,    0,  276,    4, 0x06 /* Public */,
      10,    0,  277,    4, 0x06 /* Public */,
      11,    0,  278,    4, 0x06 /* Public */,
      12,    0,  279,    4, 0x06 /* Public */,
      13,    0,  280,    4, 0x06 /* Public */,
      14,    0,  281,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,  282,    4, 0x0a /* Public */,
      16,    0,  283,    4, 0x0a /* Public */,
      17,    0,  284,    4, 0x0a /* Public */,
      18,    0,  285,    4, 0x0a /* Public */,
      19,    0,  286,    4, 0x0a /* Public */,
      20,    0,  287,    4, 0x0a /* Public */,
      21,    0,  288,    4, 0x0a /* Public */,
      22,    0,  289,    4, 0x0a /* Public */,
      23,    0,  290,    4, 0x0a /* Public */,
      24,    0,  291,    4, 0x0a /* Public */,
      25,    0,  292,    4, 0x0a /* Public */,
      26,    1,  293,    4, 0x0a /* Public */,
      29,    0,  296,    4, 0x0a /* Public */,
      30,    1,  297,    4, 0x0a /* Public */,
      32,    1,  300,    4, 0x0a /* Public */,
      33,    1,  303,    4, 0x0a /* Public */,
      34,    1,  306,    4, 0x0a /* Public */,
      35,    1,  309,    4, 0x0a /* Public */,
      36,    1,  312,    4, 0x0a /* Public */,
      36,    0,  315,    4, 0x2a /* Public | MethodCloned */,
      38,    1,  316,    4, 0x0a /* Public */,
      39,    1,  319,    4, 0x0a /* Public */,
      40,    1,  322,    4, 0x0a /* Public */,
      41,    1,  325,    4, 0x0a /* Public */,
      42,    1,  328,    4, 0x0a /* Public */,
      43,    1,  331,    4, 0x0a /* Public */,
      44,    1,  334,    4, 0x0a /* Public */,
      45,    1,  337,    4, 0x0a /* Public */,
      47,    1,  340,    4, 0x0a /* Public */,
      49,    0,  343,    4, 0x0a /* Public */,
      50,    0,  344,    4, 0x0a /* Public */,
      51,    0,  345,    4, 0x0a /* Public */,
      52,    0,  346,    4, 0x0a /* Public */,
      53,    0,  347,    4, 0x0a /* Public */,
      54,    0,  348,    4, 0x0a /* Public */,
      55,    0,  349,    4, 0x0a /* Public */,
      56,    0,  350,    4, 0x0a /* Public */,
      57,    0,  351,    4, 0x0a /* Public */,
      58,    0,  352,    4, 0x0a /* Public */,
      59,    1,  353,    4, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Double,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Float,   31,
    QMetaType::Void, QMetaType::Float,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Bool,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   31,
    QMetaType::Void, QMetaType::Float,   31,
    QMetaType::Void, QMetaType::Float,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   46,
    QMetaType::Void, 0x80000000 | 48,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 60,   61,

 // properties: name, type, flags
      15, QMetaType::Int, 0x00495103,
      16, QMetaType::Int, 0x00495103,
      17, QMetaType::Double, 0x00495103,
      18, QMetaType::Float, 0x00495103,
      19, QMetaType::Float, 0x00495103,
      20, QMetaType::Bool, 0x00495103,
      21, QMetaType::Bool, 0x00495103,
      22, QMetaType::Bool, 0x00495103,
      23, QMetaType::Float, 0x00495103,
      24, QMetaType::Float, 0x00495103,
      25, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,

       0        // eod
};

void AudioPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->samplerateChanged(); break;
        case 1: _t->channelsChanged(); break;
        case 2: _t->speedChanged(); break;
        case 3: _t->pitchChanged(); break;
        case 4: _t->rateChanged(); break;
        case 5: _t->emulateChordPitchChanged(); break;
        case 6: _t->enableNonlinearSpeedupChanged(); break;
        case 7: _t->highQualityChanged(); break;
        case 8: _t->speedIncrementChanged(); break;
        case 9: _t->volumeIncrementChanged(); break;
        case 10: _t->skipSecondsChanged(); break;
        case 11: { int _r = _t->samplerate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->channels();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: { double _r = _t->speed();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 14: { float _r = _t->pitch();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 15: { float _r = _t->rate();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->emulateChordPitch();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->enableNonlinearSpeedup();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->highQuality();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { float _r = _t->speedIncrement();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 20: { float _r = _t->volumeIncrement();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 21: { int _r = _t->skipSeconds();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->updateBook((*reinterpret_cast< Book*(*)>(_a[1]))); break;
        case 23: { int _r = _t->getVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->setSamplerate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->setChannels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->setSpeedIncrement((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->setVolumeIncrement((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->setSkipSeconds((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->togglePause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->togglePause(); break;
        case 31: _t->setSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 32: _t->setPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 33: _t->setRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 34: _t->setEmulateChordPitch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->setHighQuality((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->setEnableNonlinearSpeedup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->skip((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->jump((*reinterpret_cast< Chapter(*)>(_a[1]))); break;
        case 40: _t->updateChapter(); break;
        case 41: _t->updateSpeed(); break;
        case 42: _t->incrementSpeed(); break;
        case 43: _t->incrementVolume(); break;
        case 44: _t->decrementSpeed(); break;
        case 45: _t->decrementVolume(); break;
        case 46: _t->skipForward(); break;
        case 47: _t->skipBackward(); break;
        case 48: _t->jumpForward(); break;
        case 49: _t->jumpBackward(); break;
        case 50: _t->audioStateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Book* >(); break;
            }
            break;
        case 50:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::samplerateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::channelsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::speedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::pitchChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::rateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::emulateChordPitchChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::enableNonlinearSpeedupChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::highQualityChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::speedIncrementChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::volumeIncrementChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::skipSecondsChanged)) {
                *result = 10;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AudioPlayer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->samplerate(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->channels(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->speed(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->pitch(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->rate(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->emulateChordPitch(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->enableNonlinearSpeedup(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->highQuality(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->speedIncrement(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->volumeIncrement(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->skipSeconds(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AudioPlayer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSamplerate(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setChannels(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setSpeed(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setPitch(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setRate(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setEmulateChordPitch(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setEnableNonlinearSpeedup(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->setHighQuality(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setSpeedIncrement(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setVolumeIncrement(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setSkipSeconds(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AudioPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AudioPlayer.data,
    qt_meta_data_AudioPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AudioPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioPlayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AudioPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AudioPlayer::samplerateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AudioPlayer::channelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AudioPlayer::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AudioPlayer::pitchChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AudioPlayer::rateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AudioPlayer::emulateChordPitchChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void AudioPlayer::enableNonlinearSpeedupChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AudioPlayer::highQualityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AudioPlayer::speedIncrementChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AudioPlayer::volumeIncrementChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void AudioPlayer::skipSecondsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
