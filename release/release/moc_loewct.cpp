/****************************************************************************
** Meta object code from reading C++ file 'loewct.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LoEWCT/loewct.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loewct.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoEWCT_t {
    QByteArrayData data[6];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_LoEWCT_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_LoEWCT_t qt_meta_stringdata_LoEWCT = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 17),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 16),
QT_MOC_LITERAL(4, 43, 19),
QT_MOC_LITERAL(5, 63, 25)
    },
    "LoEWCT\0checkPingTimeouts\0\0tcpConnectClient\0"
    "tcpDisconnectClient\0tcpProcessPendingDatagram\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoEWCT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a,
       3,    0,   35,    2, 0x0a,
       4,    0,   36,    2, 0x0a,
       5,    0,   37,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LoEWCT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoEWCT *_t = static_cast<LoEWCT *>(_o);
        switch (_id) {
        case 0: _t->checkPingTimeouts(); break;
        case 1: _t->tcpConnectClient(); break;
        case 2: _t->tcpDisconnectClient(); break;
        case 3: _t->tcpProcessPendingDatagram(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject LoEWCT::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LoEWCT.data,
      qt_meta_data_LoEWCT,  qt_static_metacall, 0, 0}
};


const QMetaObject *LoEWCT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoEWCT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoEWCT.stringdata))
        return static_cast<void*>(const_cast< LoEWCT*>(this));
    return QObject::qt_metacast(_clname);
}

int LoEWCT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_LoEWCTThread_t {
    QByteArrayData data[1];
    char stringdata[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_LoEWCTThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_LoEWCTThread_t qt_meta_stringdata_LoEWCTThread = {
    {
QT_MOC_LITERAL(0, 0, 12)
    },
    "LoEWCTThread\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoEWCTThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void LoEWCTThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject LoEWCTThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LoEWCTThread.data,
      qt_meta_data_LoEWCTThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *LoEWCTThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoEWCTThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoEWCTThread.stringdata))
        return static_cast<void*>(const_cast< LoEWCTThread*>(this));
    return QObject::qt_metacast(_clname);
}

int LoEWCTThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
