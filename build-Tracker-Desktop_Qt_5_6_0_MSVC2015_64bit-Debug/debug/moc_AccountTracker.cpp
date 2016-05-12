/****************************************************************************
** Meta object code from reading C++ file 'AccountTracker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Tracker/AccountTracker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AccountTracker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AccountTracker_t {
    QByteArrayData data[13];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccountTracker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccountTracker_t qt_meta_stringdata_AccountTracker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AccountTracker"
QT_MOC_LITERAL(1, 15, 13), // "TrackStarting"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 22), // "AccountTrackerSetting*"
QT_MOC_LITERAL(4, 53, 22), // "pAccountTrackerSetting"
QT_MOC_LITERAL(5, 76, 12), // "TrackStarted"
QT_MOC_LITERAL(6, 89, 9), // "TrackOpen"
QT_MOC_LITERAL(7, 99, 9), // "Position*"
QT_MOC_LITERAL(8, 109, 9), // "pPosition"
QT_MOC_LITERAL(9, 119, 10), // "TrackClose"
QT_MOC_LITERAL(10, 130, 12), // "Transaction*"
QT_MOC_LITERAL(11, 143, 12), // "pTransaction"
QT_MOC_LITERAL(12, 156, 20) // "TrackPositionUpdated"

    },
    "AccountTracker\0TrackStarting\0\0"
    "AccountTrackerSetting*\0pAccountTrackerSetting\0"
    "TrackStarted\0TrackOpen\0Position*\0"
    "pPosition\0TrackClose\0Transaction*\0"
    "pTransaction\0TrackPositionUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccountTracker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       6,    2,   45,    2, 0x06 /* Public */,
       9,    2,   50,    2, 0x06 /* Public */,
      12,    2,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 7,    4,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 10,    4,   11,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 7,    4,    8,

       0        // eod
};

void AccountTracker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AccountTracker *_t = static_cast<AccountTracker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->TrackStarting((*reinterpret_cast< AccountTrackerSetting*(*)>(_a[1]))); break;
        case 1: _t->TrackStarted((*reinterpret_cast< AccountTrackerSetting*(*)>(_a[1]))); break;
        case 2: _t->TrackOpen((*reinterpret_cast< AccountTrackerSetting*(*)>(_a[1])),(*reinterpret_cast< Position*(*)>(_a[2]))); break;
        case 3: _t->TrackClose((*reinterpret_cast< AccountTrackerSetting*(*)>(_a[1])),(*reinterpret_cast< Transaction*(*)>(_a[2]))); break;
        case 4: _t->TrackPositionUpdated((*reinterpret_cast< AccountTrackerSetting*(*)>(_a[1])),(*reinterpret_cast< Position*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AccountTracker::*_t)(AccountTrackerSetting * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountTracker::TrackStarting)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AccountTracker::*_t)(AccountTrackerSetting * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountTracker::TrackStarted)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AccountTracker::*_t)(AccountTrackerSetting * , Position * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountTracker::TrackOpen)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AccountTracker::*_t)(AccountTrackerSetting * , Transaction * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountTracker::TrackClose)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AccountTracker::*_t)(AccountTrackerSetting * , Position * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountTracker::TrackPositionUpdated)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject AccountTracker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AccountTracker.data,
      qt_meta_data_AccountTracker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AccountTracker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccountTracker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AccountTracker.stringdata0))
        return static_cast<void*>(const_cast< AccountTracker*>(this));
    return QObject::qt_metacast(_clname);
}

int AccountTracker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AccountTracker::TrackStarting(AccountTrackerSetting * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AccountTracker::TrackStarted(AccountTrackerSetting * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AccountTracker::TrackOpen(AccountTrackerSetting * _t1, Position * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AccountTracker::TrackClose(AccountTrackerSetting * _t1, Transaction * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AccountTracker::TrackPositionUpdated(AccountTrackerSetting * _t1, Position * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
