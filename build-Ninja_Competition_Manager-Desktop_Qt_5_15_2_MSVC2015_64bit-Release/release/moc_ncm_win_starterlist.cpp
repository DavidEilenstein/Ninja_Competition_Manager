/****************************************************************************
** Meta object code from reading C++ file 'ncm_win_starterlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../code/ncm_win_starterlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ncm_win_starterlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NCM_WIN_StarterList_t {
    QByteArrayData data[11];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NCM_WIN_StarterList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NCM_WIN_StarterList_t qt_meta_stringdata_NCM_WIN_StarterList = {
    {
QT_MOC_LITERAL(0, 0, 19), // "NCM_WIN_StarterList"
QT_MOC_LITERAL(1, 20, 6), // "update"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "update_auto"
QT_MOC_LITERAL(4, 40, 8), // "activate"
QT_MOC_LITERAL(5, 49, 27), // "on_actionget_data_triggered"
QT_MOC_LITERAL(6, 77, 46), // "on_actionreload_competitors_a..."
QT_MOC_LITERAL(7, 124, 25), // "on_actionUpdate_triggered"
QT_MOC_LITERAL(8, 150, 29), // "on_actionAutoupdate_triggered"
QT_MOC_LITERAL(9, 180, 7), // "checked"
QT_MOC_LITERAL(10, 188, 40) // "on_actionChange_Table_Setting..."

    },
    "NCM_WIN_StarterList\0update\0\0update_auto\0"
    "activate\0on_actionget_data_triggered\0"
    "on_actionreload_competitors_and_runs_triggered\0"
    "on_actionUpdate_triggered\0"
    "on_actionAutoupdate_triggered\0checked\0"
    "on_actionChange_Table_Settings_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NCM_WIN_StarterList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    1,   50,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,

       0        // eod
};

void NCM_WIN_StarterList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NCM_WIN_StarterList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->update_auto((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_actionget_data_triggered(); break;
        case 3: _t->on_actionreload_competitors_and_runs_triggered(); break;
        case 4: _t->on_actionUpdate_triggered(); break;
        case 5: _t->on_actionAutoupdate_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_actionChange_Table_Settings_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NCM_WIN_StarterList::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_NCM_WIN_StarterList.data,
    qt_meta_data_NCM_WIN_StarterList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NCM_WIN_StarterList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NCM_WIN_StarterList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NCM_WIN_StarterList.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int NCM_WIN_StarterList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
