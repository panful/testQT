/* qss设置常见整理 https://blog.csdn.net/liunanya/article/details/111303629
* 1.QSS入门 https://blog.csdn.net/zyhse/article/details/105907181/
* 2.QSS属性 https://www.cnblogs.com/bclshuai/p/9809679.html
* 3.加载*.qss文件
* 4.子元素选择器，包含选择器，父子部件
* 5.伪类选择器，部件各种状态有不同属性
*/

// QSS注释需要用"/**/"不能用"//"


#define TEST5

#ifdef TEST1

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

int main(int argc,char** argv)
{
    QApplication app(argc, argv);

    qApp->setStyleSheet("QPushButton { background-color: red; }"); // 将QPushButton及其子类的背景色设置为红色
    //qApp->setStyleSheet("QWidget { background-color: red; }"); // 将QWidget及其子类的背景颜色设置为红色
    //qApp->setStyleSheet("QWidget { background-color: yellow; } QPushButton { background-color: red; } QLineEdit { background-color: green; }"); // 对不同组件设置不同的属性
    //qApp->setStyleSheet("QPushButton { background-color: red; } QWidget { background-color: yellow; }"); // 全都是黄色，后面的如果是父类会把前面的所有子类都覆盖掉
    //qApp->setStyleSheet("* { background-color: yellow; }"); // 所有控件的背景色设置为黄色
    //qApp->setStyleSheet("* { background-color: yellow; } QPushButton { background-color: red; }"); // QPushButton是红色，其他都是黄色
    //qApp->setStyleSheet(".QWidget { background-color: yellow; }"); // 只设置QWidget的背景色，QWidget的子类不会被设置 如果要派生类不受影响，调用一下setProperty()
    //qApp->setStyleSheet("#widget1 {background-color: red}"); // 设置ObjectName为widget1的背景色为红色
    //qApp->setStyleSheet("QWidget#widget1 {background-color: red}"); // 和上面的效果一样，控件的类名可加可不加
    //qApp->setStyleSheet("#widget1 {background-color: red} #lineEdit1 {background-color: green}"); // 设置多个指定控件的背景色
    //qApp->setStyleSheet("#widget1,#lineEdit1 {background-color: red}"); // 多个指定控件设置相同背景色
    //qApp->setStyleSheet("QWidget[myBkColor='myRed']{background-color:red} QWidget[myBkColor = 'myGreen']{background-color:green}"); // 属性选择器，后面需要使用setProperty选择某个属性
    //qApp->setStyleSheet("QPushButton:pressed{color:red} QPushButton:!pressed{color:green}");// 伪类选择器，按下和没按下颜色不同

    QWidget* w1 = new QWidget();
    w1->setMinimumSize(600, 400);
    w1->setWindowTitle("widget 1");
    w1->setObjectName("widget1");
    QPushButton* btn1 = new QPushButton("Button 1", w1);
    btn1->setObjectName("btn1");
    //w1->setProperty("myBkColor", "myRed"); // 属性选择
    w1->show();

    QWidget* w2 = new QWidget();
    w2->setMinimumSize(600, 400);
    w2->setWindowTitle("widget 2");
    w2->setObjectName("widget2");
    QLineEdit* lineEdit1 = new QLineEdit("text", w2);
    lineEdit1->setObjectName("lineEdit1");
    //w2->setProperty("myBkColor", "myGreen"); // 属性选择
    w2->show();

    return app.exec();
}
#endif // TEST1

#ifdef TEST2

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QWidget* w1 = new QWidget();
    w1->setMinimumSize(600, 400);
    w1->setWindowTitle("widget 1");
    w1->setObjectName("widget1");
    QPushButton* btn1 = new QPushButton(w1);
    btn1->setObjectName("btn1");
    //btn1->setStyleSheet("QPushButton#btn1{image:url(resource/undo.svg);}"); //给按钮设置图片
    btn1->setStyleSheet("QPushButton#btn1{image:url(resource/undo.svg);min-height:60px;min-width:60px;padding:0px;margin:0px;}");// 设置图片并设置大小
    //btn1->setStyleSheet("QPushButton#btn1{image:url(resource/posX.svg);min-height:26px;min-width:26px;padding:0px;margin:0px;}"); // 替换之前设置的属性
    //btn1->setStyleSheet("QPushButton#btn1{min-height:26px;min-width:26px;padding:0px;margin:0px;}"); // 替换之前设置的属性
    //btn1->setStyleSheet("QPushButton#btn1{image:url(resource/posX.svg);}"); // 替换之前设置的属性，大小也会重置
    
    qDebug() << btn1->styleSheet();
    w1->show();

    QWidget* w2 = new QWidget();
    w2->setMinimumSize(600, 400);
    w2->setWindowTitle("widget 2");
    w2->setObjectName("widget2");
    QLineEdit* lineEdit1 = new QLineEdit("text", w2);
    lineEdit1->setObjectName("lineEdit1");
    w2->show();

    return app.exec();
}
#endif // TEST2

#ifdef TEST3

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QBoxLayout>
#include <QFile>

int main(int c, char** v)
{
    QApplication app(c, v);

    QFile file("resource/test.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }

    QWidget* w1 = new QWidget();
    w1->setMinimumSize(600, 400);
    w1->setWindowTitle("widget 1");
    w1->setObjectName("widget1");

    QHBoxLayout* hBoxLayout = new QHBoxLayout();

    QPushButton* btn1 = new QPushButton("Button 1");
    btn1->setObjectName("btn1");
    QPushButton* btn2 = new QPushButton();
    btn2->setObjectName("btn2");
    // QToolButton需要设置一个背景色才能显示图标，可以设置背景色为透明
    QToolButton* btn3 = new QToolButton();
    btn3->setObjectName("btn3");

    hBoxLayout->addWidget(btn1);
    hBoxLayout->addWidget(btn2);
    hBoxLayout->addWidget(btn3);

    qDebug() << btn1->styleSheet();  // 返回为空
    qDebug() << btn2->styleSheet();  // 返回为空
    qDebug() << qApp->styleSheet();  // 返回qApp->setStyleSheet设置的样式
    //btn1->setStyleSheet("QPushButton#btn1{background-color:yellow;}");
    //btn2->setStyleSheet("QPushButton#btn2{image:url(./resource/expand.svg);}"); // 因为btn2的样式为空所以这样设置不会覆盖test.qss文件里面对btn2大小的限制
    //btn3->setStyleSheet(".QToolButton{image:url(./resource/posX.svg);}");
    //btn3->setStyleSheet("QToolButton#btn3{background-color:red;}");
    qDebug() << btn1->styleSheet();
    qDebug() << btn3->styleSheet();

    w1->setLayout(hBoxLayout);
    w1->show();

    QWidget* w2 = new QWidget();
    w2->setMinimumSize(600, 400);
    w2->setWindowTitle("widget 2");
    w2->setObjectName("widget2");
    QLineEdit* lineEdit1 = new QLineEdit("text", w2);
    lineEdit1->setObjectName("lineEdit1");
    w2->show();

    // qApp->setStyleSheet()和 obj->setStyleSheet()对同一个部件设置不同的样式
    // 优先使用obj->setStyleSheet的样式，无论这两条语句的前后

    //QFile file2("resource/test2.qss");
    //if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
    //{
    //    qApp->setStyleSheet(file2.readAll());
    //    file2.close();
    //}

    return app.exec();
}

#endif // TEST3

#ifdef TEST4

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>

int main(int c, char** v)
{
    QApplication app(c, v);

    QWidget* mainW = new QWidget();
    QWidget* w1 = new QWidget();
    QWidget* w2 = new QWidget();
    QWidget* w3 = new QWidget();
    w1->setObjectName("w1");
    w2->setObjectName("w2");
    w3->setObjectName("w3");

    QHBoxLayout* hMainLayout = new QHBoxLayout();
    QVBoxLayout* vW1Layout = new QVBoxLayout();
    QVBoxLayout* vW2Layout = new QVBoxLayout();
    QVBoxLayout* vW3Layout = new QVBoxLayout();

    QPushButton* btn1 = new QPushButton("111");
    QPushButton* btn2 = new QPushButton("222");
    QPushButton* btn3 = new QPushButton("333");
    QPushButton* btn4 = new QPushButton("444");
    QPushButton* btn5 = new QPushButton("555");
    QPushButton* btn6 = new QPushButton("666");
    QPushButton* btn7 = new QPushButton("777");
    QPushButton* btn8 = new QPushButton("888");

    btn1->setObjectName("btn1");
    btn2->setObjectName("btn2");
    btn3->setObjectName("btn3");
    btn4->setObjectName("btn4");
    btn5->setObjectName("btn5");
    btn6->setObjectName("btn6");

    vW1Layout->addWidget(btn1);
    vW1Layout->addWidget(btn2);
    vW1Layout->addWidget(btn3);
    vW2Layout->addWidget(btn4);
    vW2Layout->addWidget(btn5);
    vW2Layout->addWidget(btn6);
    vW2Layout->addWidget(w3);
    vW3Layout->addWidget(btn7);
    vW3Layout->addWidget(btn8);

    w1->setLayout(vW1Layout);
    w2->setLayout(vW2Layout);
    w3->setLayout(vW3Layout);

    hMainLayout->addWidget(w1);
    hMainLayout->addWidget(w2);

    mainW->setLayout(hMainLayout);
    mainW->setMinimumSize(800, 600);
    mainW->show();

    //qApp->setStyleSheet("QWidget#w1{ background-color: red; }");               // 只对w1设置背景色
    //qApp->setStyleSheet("QWidget#w2 > QPushButton{ background-color: red; }"); // 只对w2中的子QPushButton设置背景色（孙子QPushButton不设置）
    qApp->setStyleSheet("QWidget#w2  QPushButton{ background-color: red; }");      // 对w2中的所有QPushButton设置背景色，包括子控件，孙子控件等
    //qApp->setStyleSheet("QPushButton{ background-color: red; }");              // 对所有QPushButton都设置背景色

    return app.exec();
}

#endif // TEST4

#ifdef TEST5

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QBoxLayout>

int main(int c, char** v)
{
    QApplication app(c, v);

    QWidget* w = new QWidget();
    w->setObjectName("myWidget");

    QHBoxLayout* hMainLayout = new QHBoxLayout();

    QPushButton* btn1 = new QPushButton("MyPushButton");
    btn1->setObjectName("btn1");
    QToolButton* btn2 = new QToolButton();
    btn2->setObjectName("btn2");
    QCheckBox* checkBox = new QCheckBox("MyCheckBox");
    checkBox->setObjectName("checkBox");

    hMainLayout->addWidget(btn1);
    hMainLayout->addWidget(btn2);
    hMainLayout->addWidget(checkBox);

    w->setLayout(hMainLayout);
    w->setMinimumSize(800, 600);
    w->show();
    
    // 按下和没有按下是两个不同的图标
    //qApp->setStyleSheet("QPushButton:pressed{image:url(./resource/posX.svg);}QPushButton:!pressed{image:url(./resource/negY.svg);}");

    // 鼠标悬浮到按钮上，按钮显示红色
    qApp->setStyleSheet("QPushButton:hover{color:red;}");

    // 按下且鼠标在按钮上悬浮显示图标（状态之间是【与】的关系）
    //qApp->setStyleSheet("QPushButton:pressed:hover{image:url(./resource/posX.svg);}");

    // checkbox选择和不选择是两种图标
    //qApp->setStyleSheet("QCheckBox::indicator:checked{image:url(./resource/posX.svg);}QCheckBox::indicator:unchecked{image:url(./resource/negY.svg);}");

    return app.exec();
}

#endif // TEST5
