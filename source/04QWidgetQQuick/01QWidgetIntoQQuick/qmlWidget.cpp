//#include "qmlWidget.h"
//
//#include <QDebug>
//#include <QPushButton>
//
//QmlWidget::QmlWidget(QWidget* parent) : QWidget(parent) {
//
//    quickWidget = new QQuickWidget();
//
//    quickWidget->setSource(QUrl("qrc:///main.qml"));
//
//    layout = new QVBoxLayout(this);
//
//    QPushButton* btn1 = new QPushButton(this);
//
//    btn1->setText("widget btn");
//
//    layout->addWidget(btn1);
//
//    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
//
//    QObject* obj = (QObject*)quickWidget->rootObject();
//
//    connect(obj, SIGNAL(qmlClicked()), this, SLOT(slotWidget()));
//
//    connect(this, SIGNAL(sigWidget()), obj, SIGNAL(widgetClicked()));
//
//    quickWidget->setLayout(layout);
//
//    quickWidget->show();
//
//}
//
//void QmlWidget::slotWidget() {
//
//    qDebug() << "qml sig to widget slot";
//
//    emit sigWidget();
//
//}
//
//void QmlWidget::btnClicked() {
//
//    qDebug() << "widget btn clicked";
//
//}
