/****************************************************************************
** Meta object code from reading C++ file 'Book.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/Book.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Book.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Book_t {
    QByteArrayData data[21];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Book_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Book_t qt_meta_stringdata_Book = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Book"
QT_MOC_LITERAL(1, 5, 11), // "QML.Element"
QT_MOC_LITERAL(2, 17, 4), // "auto"
QT_MOC_LITERAL(3, 22, 15), // "onAuthorChanged"
QT_MOC_LITERAL(4, 38, 0), // ""
QT_MOC_LITERAL(5, 39, 14), // "onTitleChanged"
QT_MOC_LITERAL(6, 54, 14), // "onCoverChanged"
QT_MOC_LITERAL(7, 69, 17), // "onPositionChanged"
QT_MOC_LITERAL(8, 87, 16), // "_onAuthorChanged"
QT_MOC_LITERAL(9, 104, 15), // "_onTitleChanged"
QT_MOC_LITERAL(10, 120, 15), // "_onCoverChanged"
QT_MOC_LITERAL(11, 136, 18), // "_onPositionChanged"
QT_MOC_LITERAL(12, 155, 6), // "author"
QT_MOC_LITERAL(13, 162, 5), // "title"
QT_MOC_LITERAL(14, 168, 5), // "cover"
QT_MOC_LITERAL(15, 174, 8), // "position"
QT_MOC_LITERAL(16, 183, 9), // "setAuthor"
QT_MOC_LITERAL(17, 193, 3), // "tmp"
QT_MOC_LITERAL(18, 197, 8), // "setTitle"
QT_MOC_LITERAL(19, 206, 8), // "setCover"
QT_MOC_LITERAL(20, 215, 11) // "setPosition"

    },
    "Book\0QML.Element\0auto\0onAuthorChanged\0"
    "\0onTitleChanged\0onCoverChanged\0"
    "onPositionChanged\0_onAuthorChanged\0"
    "_onTitleChanged\0_onCoverChanged\0"
    "_onPositionChanged\0author\0title\0cover\0"
    "position\0setAuthor\0tmp\0setTitle\0"
    "setCover\0setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Book[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      16,   16, // methods
       4,  120, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   96,    4, 0x06 /* Public */,
       5,    0,   97,    4, 0x06 /* Public */,
       6,    0,   98,    4, 0x06 /* Public */,
       7,    0,   99,    4, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    0,  100,    4, 0x02 /* Public */,
       9,    0,  101,    4, 0x02 /* Public */,
      10,    0,  102,    4, 0x02 /* Public */,
      11,    0,  103,    4, 0x02 /* Public */,
      12,    0,  104,    4, 0x02 /* Public */,
      13,    0,  105,    4, 0x02 /* Public */,
      14,    0,  106,    4, 0x02 /* Public */,
      15,    0,  107,    4, 0x02 /* Public */,
      16,    1,  108,    4, 0x02 /* Public */,
      18,    1,  111,    4, 0x02 /* Public */,
      19,    1,  114,    4, 0x02 /* Public */,
      20,    1,  117,    4, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QUrl,
    QMetaType::Double,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QUrl,   17,
    QMetaType::Void, QMetaType::Double,   17,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00495103,
      13, QMetaType::QString, 0x00495103,
      14, QMetaType::QUrl, 0x00495103,
      15, QMetaType::Double, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void Book::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Book *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onAuthorChanged(); break;
        case 1: _t->onTitleChanged(); break;
        case 2: _t->onCoverChanged(); break;
        case 3: _t->onPositionChanged(); break;
        case 4: _t->_onAuthorChanged(); break;
        case 5: _t->_onTitleChanged(); break;
        case 6: _t->_onCoverChanged(); break;
        case 7: _t->_onPositionChanged(); break;
        case 8: { QString _r = _t->author();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { QString _r = _t->title();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QUrl _r = _t->cover();
            if (_a[0]) *reinterpret_cast< QUrl*>(_a[0]) = std::move(_r); }  break;
        case 11: { double _r = _t->position();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setAuthor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->setCover((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 15: _t->setPosition((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Book::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Book::onAuthorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Book::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Book::onTitleChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Book::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Book::onCoverChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Book::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Book::onPositionChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Book *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->author(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->title(); break;
        case 2: *reinterpret_cast< QUrl*>(_v) = _t->cover(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->position(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Book *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAuthor(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setTitle(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setCover(*reinterpret_cast< QUrl*>(_v)); break;
        case 3: _t->setPosition(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Book::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Book.data,
    qt_meta_data_Book,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Book::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Book::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Book.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Book::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Book::onAuthorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Book::onTitleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Book::onCoverChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Book::onPositionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
