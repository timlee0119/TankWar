/****************************************************************************
** Meta object code from reading C++ file 'Game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[19];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 16), // "setChooseSceneP1"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "setChooseSceneP2"
QT_MOC_LITERAL(4, 40, 11), // "setMapScene"
QT_MOC_LITERAL(5, 52, 10), // "setNewGame"
QT_MOC_LITERAL(6, 63, 16), // "setGameoverScene"
QT_MOC_LITERAL(7, 80, 13), // "setFocusOutP1"
QT_MOC_LITERAL(8, 94, 13), // "setFocusOutP2"
QT_MOC_LITERAL(9, 108, 12), // "setFocusInP1"
QT_MOC_LITERAL(10, 121, 12), // "setFocusInP2"
QT_MOC_LITERAL(11, 134, 14), // "setFocusOutMap"
QT_MOC_LITERAL(12, 149, 13), // "setFocusInMap"
QT_MOC_LITERAL(13, 163, 13), // "setFocusOutRe"
QT_MOC_LITERAL(14, 177, 12), // "setFocusInRe"
QT_MOC_LITERAL(15, 190, 13), // "setFocusOutQu"
QT_MOC_LITERAL(16, 204, 12), // "setFocusInQu"
QT_MOC_LITERAL(17, 217, 7), // "setWall"
QT_MOC_LITERAL(18, 225, 8) // "gameover"

    },
    "Game\0setChooseSceneP1\0\0setChooseSceneP2\0"
    "setMapScene\0setNewGame\0setGameoverScene\0"
    "setFocusOutP1\0setFocusOutP2\0setFocusInP1\0"
    "setFocusInP2\0setFocusOutMap\0setFocusInMap\0"
    "setFocusOutRe\0setFocusInRe\0setFocusOutQu\0"
    "setFocusInQu\0setWall\0gameover"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x0a /* Public */,
       3,    1,  100,    2, 0x0a /* Public */,
       4,    1,  103,    2, 0x0a /* Public */,
       5,    1,  106,    2, 0x0a /* Public */,
       6,    1,  109,    2, 0x0a /* Public */,
       7,    1,  112,    2, 0x0a /* Public */,
       8,    1,  115,    2, 0x0a /* Public */,
       9,    1,  118,    2, 0x0a /* Public */,
      10,    1,  121,    2, 0x0a /* Public */,
      11,    1,  124,    2, 0x0a /* Public */,
      12,    1,  127,    2, 0x0a /* Public */,
      13,    1,  130,    2, 0x0a /* Public */,
      14,    1,  133,    2, 0x0a /* Public */,
      15,    1,  136,    2, 0x0a /* Public */,
      16,    1,  139,    2, 0x0a /* Public */,
      17,    1,  142,    2, 0x0a /* Public */,
      18,    1,  145,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Game *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setChooseSceneP1(); break;
        case 1: _t->setChooseSceneP2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setMapScene((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setNewGame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setGameoverScene((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setFocusOutP1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setFocusOutP2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setFocusInP1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setFocusInP2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setFocusOutMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setFocusInMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setFocusOutRe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setFocusInRe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setFocusOutQu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setFocusInQu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setWall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->gameover((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Game::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Game.data,
      qt_meta_data_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(const_cast< Game*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
