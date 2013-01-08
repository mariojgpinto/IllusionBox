/****************************************************************************
** Meta object code from reading C++ file 'GUI.h'
**
** Created: Sun 1. Jul 17:30:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_expQt[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    7,    6,    6, 0x0a,
      44,    7,    6,    6, 0x0a,
      75,    7,    6,    6, 0x0a,
     106,    6,    6,    6, 0x0a,
     122,    6,    6,    6, 0x0a,
     140,    6,    6,    6, 0x0a,
     158,    6,    6,    6, 0x0a,
     177,    6,    6,    6, 0x0a,
     196,    6,    6,    6, 0x0a,
     221,  215,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_expQt[] = {
    "expQt\0\0value\0on_maxSlider_valueChanged(int)\0"
    "on_minSlider_valueChanged(int)\0"
    "on_ROISlider_valueChanged(int)\0"
    "on_Up_Clicked()\0on_Down_Clicked()\0"
    "on_Left_Clicked()\0on_Right_Clicked()\0"
    "on_Water_Clicked()\0on_Point_Clicked()\0"
    "image\0paintImage(RGBDImage*)\0"
};

const QMetaObject expQt::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_expQt,
      qt_meta_data_expQt, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &expQt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *expQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *expQt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_expQt))
        return static_cast<void*>(const_cast< expQt*>(this));
    return QWidget::qt_metacast(_clname);
}

int expQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_maxSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_minSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_ROISlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_Up_Clicked(); break;
        case 4: on_Down_Clicked(); break;
        case 5: on_Left_Clicked(); break;
        case 6: on_Right_Clicked(); break;
        case 7: on_Water_Clicked(); break;
        case 8: on_Point_Clicked(); break;
        case 9: paintImage((*reinterpret_cast< RGBDImage*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
