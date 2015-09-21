/****************************************************************************
** Meta object code from reading C++ file 'WindowLoadStudent.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WindowLoadStudent.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WindowLoadStudent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WindowLoadStudent_t {
    QByteArrayData data[7];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowLoadStudent_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowLoadStudent_t qt_meta_stringdata_WindowLoadStudent = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 17),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 16),
QT_MOC_LITERAL(4, 54, 4),
QT_MOC_LITERAL(5, 59, 13),
QT_MOC_LITERAL(6, 73, 20)
    },
    "WindowLoadStudent\0itemDoubleClicked\0"
    "\0QListWidgetItem*\0item\0selectStudent\0"
    "openWindowNewStudent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowLoadStudent[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void WindowLoadStudent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WindowLoadStudent *_t = static_cast<WindowLoadStudent *>(_o);
        switch (_id) {
        case 0: _t->itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->selectStudent((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->openWindowNewStudent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WindowLoadStudent::*_t)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WindowLoadStudent::itemDoubleClicked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WindowLoadStudent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WindowLoadStudent.data,
      qt_meta_data_WindowLoadStudent,  qt_static_metacall, 0, 0}
};


const QMetaObject *WindowLoadStudent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowLoadStudent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WindowLoadStudent.stringdata))
        return static_cast<void*>(const_cast< WindowLoadStudent*>(this));
    return QWidget::qt_metacast(_clname);
}

int WindowLoadStudent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WindowLoadStudent::itemDoubleClicked(QListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
