#ifndef QMLWIDGET_H

#define QMLWIDGET_H

#include <QQuickWidget>
#include <QQmlEngine>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>

class QmlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QmlWidget(QWidget* parent = 0)
    {
        quickWidget = new QQuickWidget();
        quickWidget->setSource(QUrl("qrc:///main.qml"));

        layout = new QVBoxLayout(this);

        QPushButton* btn1 = new QPushButton(this);
        btn1->setText("widget btn");
        layout->addWidget(btn1);

        connect(btn1, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));

        QObject* obj = (QObject*)quickWidget->rootObject();

        connect(obj, SIGNAL(qmlClicked()), this, SLOT(slotWidget()));
        connect(this, SIGNAL(sigWidget()), obj, SIGNAL(widgetClicked()));

        quickWidget->setLayout(layout);
        quickWidget->show();
    }

private:

    QVBoxLayout* layout;
    QQuickWidget* quickWidget;

signals:
    void sigWidget();

public slots:
    void slotWidget()
    {
        qDebug() << "qml sig to widget slot";

        emit sigWidget();
    }
    void btnClicked()
    {
        qDebug() << "widget btn clicked";
    }
};

#endif // QMLWIDGET_H
