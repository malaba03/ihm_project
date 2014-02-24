/****************************************************************************
** Meta object code from reading C++ file 'Mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Mainwindow_t {
    QByteArrayData data[15];
    char stringdata[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Mainwindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Mainwindow_t qt_meta_stringdata_Mainwindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 16),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 17),
QT_MOC_LITERAL(4, 47, 16),
QT_MOC_LITERAL(5, 64, 17),
QT_MOC_LITERAL(6, 82, 16),
QT_MOC_LITERAL(7, 99, 9),
QT_MOC_LITERAL(8, 109, 24),
QT_MOC_LITERAL(9, 134, 4),
QT_MOC_LITERAL(10, 139, 17),
QT_MOC_LITERAL(11, 157, 20),
QT_MOC_LITERAL(12, 178, 13),
QT_MOC_LITERAL(13, 192, 7),
QT_MOC_LITERAL(14, 200, 9)
    },
    "Mainwindow\0newProjectDialog\0\0"
    "exportAsXmlDialog\0openProjectPopup\0"
    "closeProjectPopup\0saveProjectPopup\0"
    "exitPopup\0receiveCurrentProjectDir\0"
    "QDir\0currentProjectDir\0receiveLayerFilePath\0"
    "layerFilePath\0message\0loadLayer\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mainwindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a,
       3,    0,   65,    2, 0x0a,
       4,    0,   66,    2, 0x0a,
       5,    0,   67,    2, 0x0a,
       6,    0,   68,    2, 0x0a,
       7,    0,   69,    2, 0x0a,
       8,    1,   70,    2, 0x0a,
      11,    1,   73,    2, 0x0a,
      13,    0,   76,    2, 0x0a,
      14,    0,   77,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Mainwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Mainwindow *_t = static_cast<Mainwindow *>(_o);
        switch (_id) {
        case 0: _t->newProjectDialog(); break;
        case 1: _t->exportAsXmlDialog(); break;
        case 2: _t->openProjectPopup(); break;
        case 3: _t->closeProjectPopup(); break;
        case 4: _t->saveProjectPopup(); break;
        case 5: _t->exitPopup(); break;
        case 6: _t->receiveCurrentProjectDir((*reinterpret_cast< QDir(*)>(_a[1]))); break;
        case 7: _t->receiveLayerFilePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->message(); break;
        case 9: _t->loadLayer(); break;
        default: ;
        }
    }
}

const QMetaObject Mainwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Mainwindow.data,
      qt_meta_data_Mainwindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *Mainwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mainwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mainwindow.stringdata))
        return static_cast<void*>(const_cast< Mainwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Mainwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
