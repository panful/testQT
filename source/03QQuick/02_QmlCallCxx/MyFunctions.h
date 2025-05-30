#pragma once

#include <QObject>

class MyFunctions : public QObject
{
    Q_OBJECT;

public:
    Q_INVOKABLE void myFunc();
};
