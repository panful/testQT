#ifndef QDATAMGR_H
#define QDATAMGR_H

#include <QObject>

class QDataMgr : public QObject
{
    Q_OBJECT
        //Q_PROPERTY(QString _txt READ rtxt WRITE settxt NOTIFY txtchanged)
public:
    explicit QDataMgr(QObject* parent = nullptr);
    //QString rtxt() const { return _txt; }
    //void settxt(QString s) { _txt = s; emit txtchanged(); }

//signals:
    //void txtchanged();

public slots:
public:
    Q_INVOKABLE void info();
//private:
   // QString _txt;
};

#endif // QDATAMGR_H