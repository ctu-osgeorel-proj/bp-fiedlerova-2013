/****************************************************************************
** Meta object code from reading C++ file 'qgsconflateplugin.h'
**
** Created: Thu Jan 31 10:05:19 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qgsconflateplugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgsconflateplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QgsConflatePlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QgsConflatePlugin[] = {
    "QgsConflatePlugin\0\0showDialog()\0"
};

void QgsConflatePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QgsConflatePlugin *_t = static_cast<QgsConflatePlugin *>(_o);
        switch (_id) {
        case 0: _t->showDialog(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QgsConflatePlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QgsConflatePlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QgsConflatePlugin,
      qt_meta_data_QgsConflatePlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QgsConflatePlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QgsConflatePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QgsConflatePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgsConflatePlugin))
        return static_cast<void*>(const_cast< QgsConflatePlugin*>(this));
    if (!strcmp(_clname, "QgisPlugin"))
        return static_cast< QgisPlugin*>(const_cast< QgsConflatePlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int QgsConflatePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
