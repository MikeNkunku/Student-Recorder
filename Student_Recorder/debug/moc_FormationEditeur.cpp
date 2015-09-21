/****************************************************************************
** Meta object code from reading C++ file 'FormationEditeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FormationEditeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FormationEditeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormationEditeur_t {
    QByteArrayData data[11];
    char stringdata[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormationEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormationEditeur_t qt_meta_stringdata_FormationEditeur = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 9),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 13),
QT_MOC_LITERAL(4, 42, 11),
QT_MOC_LITERAL(5, 54, 9),
QT_MOC_LITERAL(6, 64, 15),
QT_MOC_LITERAL(7, 80, 13),
QT_MOC_LITERAL(8, 94, 14),
QT_MOC_LITERAL(9, 109, 16),
QT_MOC_LITERAL(10, 126, 15)
    },
    "FormationEditeur\0activSave\0\0cancelChanges\0"
    "supprimerUV\0ajouterUV\0supprimerUVCons\0"
    "ajouterUVCons\0ajouterFiliere\0"
    "supprimerFiliere\0sauverFormation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormationEditeur[] = {

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
       1,    1,   64,    2, 0x0a /* Public */,
       1,    0,   67,    2, 0x2a /* Public | MethodCloned */,
       3,    0,   68,    2, 0x0a /* Public */,
       4,    0,   69,    2, 0x0a /* Public */,
       5,    0,   70,    2, 0x0a /* Public */,
       6,    0,   71,    2, 0x0a /* Public */,
       7,    0,   72,    2, 0x0a /* Public */,
       8,    0,   73,    2, 0x0a /* Public */,
       9,    0,   74,    2, 0x0a /* Public */,
      10,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
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

void FormationEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormationEditeur *_t = static_cast<FormationEditeur *>(_o);
        switch (_id) {
        case 0: _t->activSave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->activSave(); break;
        case 2: _t->cancelChanges(); break;
        case 3: _t->supprimerUV(); break;
        case 4: _t->ajouterUV(); break;
        case 5: _t->supprimerUVCons(); break;
        case 6: _t->ajouterUVCons(); break;
        case 7: _t->ajouterFiliere(); break;
        case 8: _t->supprimerFiliere(); break;
        case 9: _t->sauverFormation(); break;
        default: ;
        }
    }
}

const QMetaObject FormationEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormationEditeur.data,
      qt_meta_data_FormationEditeur,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormationEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormationEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormationEditeur.stringdata))
        return static_cast<void*>(const_cast< FormationEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormationEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_FormationCreateur_t {
    QByteArrayData data[5];
    char stringdata[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormationCreateur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormationCreateur_t qt_meta_stringdata_FormationCreateur = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 9),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 13),
QT_MOC_LITERAL(4, 43, 15)
    },
    "FormationCreateur\0activSave\0\0cancelChanges\0"
    "sauverFormation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormationCreateur[] = {

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
       1,    1,   34,    2, 0x0a /* Public */,
       1,    0,   37,    2, 0x2a /* Public | MethodCloned */,
       3,    0,   38,    2, 0x0a /* Public */,
       4,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FormationCreateur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormationCreateur *_t = static_cast<FormationCreateur *>(_o);
        switch (_id) {
        case 0: _t->activSave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->activSave(); break;
        case 2: _t->cancelChanges(); break;
        case 3: _t->sauverFormation(); break;
        default: ;
        }
    }
}

const QMetaObject FormationCreateur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormationCreateur.data,
      qt_meta_data_FormationCreateur,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormationCreateur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormationCreateur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormationCreateur.stringdata))
        return static_cast<void*>(const_cast< FormationCreateur*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormationCreateur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
