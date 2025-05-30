#include "MyFunctions.h"
#include <QDebug>

void MyFunctions::myFunc()
{
    static int index {};
    qDebug() << index++ << "Invoke myFunc()";
}
