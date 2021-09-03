/****************************************************************************
** Meta object code from reading C++ file 'AudioPlayer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Desktop/src/AudioPlayer.hpp"
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
    QByteArrayData data[24];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioPlayer_t qt_meta_stringdata_AudioPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioPlayer"
QT_MOC_LITERAL(1, 12, 11), // "togglePause"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "dummyparam"
QT_MOC_LITERAL(4, 36, 9), // "setVolume"
QT_MOC_LITERAL(5, 46, 2), // "to"
QT_MOC_LITERAL(6, 49, 8), // "setSpeed"
QT_MOC_LITERAL(7, 58, 8), // "setPitch"
QT_MOC_LITERAL(8, 67, 7), // "setRate"
QT_MOC_LITERAL(9, 75, 20), // "setEmulateChordPitch"
QT_MOC_LITERAL(10, 96, 14), // "setHighQuality"
QT_MOC_LITERAL(11, 111, 25), // "setEnableNonlinearSpeedup"
QT_MOC_LITERAL(12, 137, 4), // "skip"
QT_MOC_LITERAL(13, 142, 6), // "amount"
QT_MOC_LITERAL(14, 149, 4), // "jump"
QT_MOC_LITERAL(15, 154, 8), // "chapters"
QT_MOC_LITERAL(16, 163, 14), // "incrementSpeed"
QT_MOC_LITERAL(17, 178, 15), // "incrementVolume"
QT_MOC_LITERAL(18, 194, 14), // "decrementSpeed"
QT_MOC_LITERAL(19, 209, 15), // "decrementVolume"
QT_MOC_LITERAL(20, 225, 11), // "skipForward"
QT_MOC_LITERAL(21, 237, 12), // "skipBackward"
QT_MOC_LITERAL(22, 250, 11), // "jumpForward"
QT_MOC_LITERAL(23, 262, 12) // "jumpBackward"

    },
    "AudioPlayer\0togglePause\0\0dummyparam\0"
    "setVolume\0to\0setSpeed\0setPitch\0setRate\0"
    "setEmulateChordPitch\0setHighQuality\0"
    "setEnableNonlinearSpeedup\0skip\0amount\0"
    "jump\0chapters\0incrementSpeed\0"
    "incrementVolume\0decrementSpeed\0"
    "decrementVolume\0skipForward\0skipBackward\0"
    "jumpForward\0jumpBackward"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x0a /* Public */,
       1,    0,  112,    2, 0x2a /* Public | MethodCloned */,
       4,    1,  113,    2, 0x0a /* Public */,
       6,    1,  116,    2, 0x0a /* Public */,
       7,    1,  119,    2, 0x0a /* Public */,
       8,    1,  122,    2, 0x0a /* Public */,
       9,    1,  125,    2, 0x0a /* Public */,
      10,    1,  128,    2, 0x0a /* Public */,
      11,    1,  131,    2, 0x0a /* Public */,
      12,    1,  134,    2, 0x0a /* Public */,
      14,    1,  137,    2, 0x0a /* Public */,
      16,    0,  140,    2, 0x0a /* Public */,
      17,    0,  141,    2, 0x0a /* Public */,
      18,    0,  142,    2, 0x0a /* Public */,
      19,    0,  143,    2, 0x0a /* Public */,
      20,    0,  144,    2, 0x0a /* Public */,
      21,    0,  145,    2, 0x0a /* Public */,
      22,    0,  146,    2, 0x0a /* Public */,
      23,    0,  147,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AudioPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->togglePause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->togglePause(); break;
        case 2: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setPitch((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setEmulateChordPitch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setHighQuality((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setEnableNonlinearSpeedup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->skip((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->jump((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->incrementSpeed(); break;
        case 12: _t->incrementVolume(); break;
        case 13: _t->decrementSpeed(); break;
        case 14: _t->decrementVolume(); break;
        case 15: _t->skipForward(); break;
        case 16: _t->skipBackward(); break;
        case 17: _t->jumpForward(); break;
        case 18: _t->jumpBackward(); break;
        default: ;
        }
    }
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
