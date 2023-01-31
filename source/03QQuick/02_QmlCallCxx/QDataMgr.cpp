
#include "QDataMgr.h"
#include <QDebug>
QDataMgr::QDataMgr(QObject* parent) : QObject(parent)
{
   // _txt = "top color is red";
}

void QDataMgr::info() {
    //qDebug() << "_txt: " << _txt;
    qDebug() << "============ test =================\n";
}