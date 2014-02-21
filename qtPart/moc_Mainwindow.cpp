/****************************************************************************
** Meta object code from reading C++ file 'Mainwindow.h'
**
** Created: Mon Feb 17 14:05:34 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mainwindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      30,   11,   11,   11, 0x0a,
      49,   11,   11,   11, 0x0a,
      69,   11,   11,   11, 0x0a,
      83,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     114,   11,   11,   11, 0x0a,
     134,   11,   11,   11, 0x0a,
     153,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Mainwindow[] = {
    "Mainwindow\0\0newProjectPopup()\0"
    "openProjectPopup()\0closeProjectPopup()\0"
    "exportPopup()\0saveProjectPopup()\0"
    "exitPopup()\0addClassroomOnMap()\0"
    "addCorridorOnMap()\0addRestroomOnMap()\0"
};

void Mainwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mainwindow *_t = static_cast<Mainwindow *>(_o);
        switch (_id) {
        case 0: _t->newProjectPopup(); break;
        case 1: _t->openProjectPopup(); break;
        case 2: _t->closeProjectPopup(); break;
        case 3: _t->exportPopup(); break;
        case 4: _t->saveProjectPopup(); break;
        case 5: _t->exitPopup(); break;
        case 6: _t->addClassroomOnMap(); break;
        case 7: _t->addCorridorOnMap(); break;
        case 8: _t->addRestroomOnMap(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Mainwindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Mainwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Mainwindow,
      qt_meta_data_Mainwindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mainwindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mainwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mainwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mainwindow))
        return static_cast<void*>(const_cast< Mainwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Mainwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
