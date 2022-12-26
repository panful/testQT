/*
* 1. QLabel显示图片
* 2. QMenu
* 3. QMenu
* 4. QAction
* 5. QSpacerItem布局弹簧，按钮可以随着窗口大小移动，按钮大小不变
* 6. setGeometry设置部件位置
* 7. 弹簧，部件可以随着窗口大小变化也跟着变化
* 8. QMenu131
* 9. 窗口大小设置 resize     setMinimumSize setMaximumSize setFixedSize
* 10.QToolButton弹出菜单
* 11.QStackedWidget计数
* 12.QMenuBar QToolButton弹出QAction 并设置槽函数
* 13.QPixmap
* 14.事件过滤器 钩子 eventFilter
* 15.安装事件过滤器
* 16.
*/

#define TEST16

#ifdef TEST1

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QThread>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QWidget* w = new QWidget;
    QLabel* label = new QLabel(w);
    QPixmap* p1 = new QPixmap();
    QPixmap* p2 = new QPixmap();
    QPixmap* p3 = new QPixmap();

    w->setMinimumSize(800, 600);

    p3->load("p3.jpg");
    label->setPixmap(*p3);

    w->show();

    return app.exec();
}

#endif // TEST1

#ifdef TEST2

#include<QtWidgets>
int main(int argc, char* argv[]) {
    QApplication aa(argc, argv);
    QMenu pm1("AAA"); //创建菜单，仅需一个字符串即可。
    //向菜单pm1 中添加菜单项
    QMenu* pm11 = pm1.addMenu("ABB"); //pm1 拥有addMenu()函数返回的菜单的所有权。
    QMenu* pm12 = pm1.addMenu("ACC"); 
    QMenu* pm13 = pm1.addMenu("ADD");
    //向菜单pm11 中添加菜单项
    pm11->addMenu("AAB"); 
    pm11->addMenu("AAC");
    pm1.exec(); //使用exec()函数显示菜单pm1
    return aa.exec();
}
#endif // TEST2

#ifdef TEST3

#include<QtWidgets>
int main(int argc, char* argv[]) 
{
    QApplication aa(argc, argv);
    QMenuBar pmb; //创建一个菜单栏
    //向菜单栏中添加顶级菜单
    QMenu* pm1 = pmb.addMenu("AAA");
    pmb.addMenu("BBB");
    pmb.addMenu("CCC");
    //向顶级菜单AAA 中添加菜单项
    QMenu* pm11 = pm1->addMenu("ABB");
    pm1->addMenu("ACC");
    pm1->addMenu("ADD");
    //向菜单ABB 中添加菜单项
    pm11->addMenu("AAB"); pm11->addMenu("AAC");
    /*还可向使用QWidget 一样，向QMenuBar 中添加按钮，同样也可向QMenu 中添加按钮。但这种使用方法不
    推荐。*/
    //该菜单会在屏幕左上角显示，注意：在显示菜单之前
    //    不要点击鼠标和使用键盘，以免使显示的菜单消息
    //    了。
    //    关闭菜单后，程序不会结束，此时请
    //    使用此按钮结束程序
    QPushButton* pb = new QPushButton("XXX", &pmb); 
    pb->move(200, 33);
    //设置菜单栏的大小，并以窗口的形式显示菜单栏
    pmb.resize(333, 222); 
    pmb.show(); 
    return aa.exec();
}

#endif // TEST3

#ifdef TEST4

#include<QtWidgets>
int main(int argc, char* argv[]) {
    QApplication aa(argc, argv);
    QWidget w;
    //以下是创建QAction 的方法
    QAction* pa = new QAction(QIcon("C:\\Users\\yangpan\\Pictures\\Saved Pictures\\test.jpg"), "", &w); //含一图标、文本
    QAction* pa1 = new QAction("disable", &w); //仅有文本
    QAction* pa2 = new QAction(&w); //既无图标也无文本
    QAction* pa3 = new QAction("xxx", &w);
    //为QAction 添加快捷键
    //pa->setShortcut(QKeySequence("Ctrl+G")); 
    pa1->setShortcut(QKeySequence("Ctrl+D"));
    pa2->setShortcut(QKeySequence("Ctrl+E"));
    pa3->setShortcut(QKeySequence("Ctrl+H"));
    //创建菜单和菜单栏
    auto layout = new QHBoxLayout();
    QMenuBar* pmb = new QMenuBar(&w);
    QMenu* pm1 = pmb->addMenu("AAA");
    pm1->addAction(pa); //动作pa 的文本和图标会作为菜单项被添加到pm1 之中。
    //创建按钮部件
    QPushButton* pb = new QPushButton("Disable", &w); pb->move(0, 66);
    QPushButton* pb1 = new QPushButton("Enable", &w); pb1->move(99, 66);
    QCheckBox* pc = new QCheckBox("FFF", &w); pc->move(22, 99);
    //把QAction 添加到按钮中
    pb->addAction(pa1); pb1->addAction(pa2);
    //把QAction 的triggered 信号连接到相应的槽函数
    //动作pa 用于切换pc 的选中状态
    QObject::connect(pa, &QAction::triggered, pc, &QCheckBox::toggle);
    //动作pa1 用于禁用pc，注意：triggered 信号会传递一个默认为false 的bool 参数。
    QObject::connect(pa1, &QAction::triggered, pc, &QCheckBox::setEnabled);
    //动作pa2 用于启用pc
    QObject::connect(pa2, &QAction::triggered, pc, &QCheckBox::setDisabled);
    /*把pb 的clicked 信号关联到动作pa1，这样点击pb 将激活动作pa1。注意：clicked 信号也会传递一个默
    认为false 的bool 参数。*/
    QObject::connect(pb, &QPushButton::clicked, pa1, &QAction::triggered);
    //使动作pa3 切换pc 的选中状态，但是该动作在本例不会有任何反应，因为未把该动作添加到任何部件。
    QObject::connect(pa3, &QAction::triggered, pc, &QCheckBox::toggle);
    //auto pbxx = new QPushButton();
    //pbxx->setMaximumHeight(50);
    //layout->addWidget(pmb);
    //layout->addWidget(pbxx);
    //w.setLayout(layout);
    w.resize(333, 222);
    w.show();
    return aa.exec();
}
#endif // TEST4

#ifdef TEST5

#include<QtWidgets>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) 
{
    QApplication a(argc, argv);
    QWidget w;
    QPushButton* pb = new QPushButton("AAA");
    QPushButton* pb1 = new QPushButton("BBB");
    QPushButton* pb2 = new QPushButton("CCC");
    QPushButton* pb3 = new QPushButton("DDD");
    pb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    pb1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pb2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* pg = new QHBoxLayout;
    pg->addWidget(pb);
    pg->addStretch(1); //添加一个拉伸因子为1 的间距(QSpacerItem)
    pg->addWidget(pb1);
    pg->addStretch(2);//添加一个拉伸因子为2 的间距
    pg->addWidget(pb2);
    w.setLayout(pg);
    w.resize(300, 100); 
    w.show(); 
    return a.exec();
}
#endif // TEST5

#ifdef TEST6

#include<QtWidgets>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    // 1
    //auto layout = new QHBoxLayout();
    //QPushButton* pb = new QPushButton("AAA");
    //layout->addWidget(pb);
    //pb->setGeometry(0, 0, 40, 50);
    //w.setLayout(layout);

    // 2
    QPushButton* pb = new QPushButton("test", &w);
    pb->setGeometry(10, 10, 50, 50);

    w.resize(300, 100);
    w.show();
    return a.exec();
}

#endif // TEST6

#ifdef TEST7

#include<QtWidgets>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QMenuBar* pmb = new QMenuBar();
    pmb->setMaximumHeight(50);

    QPushButton* pb = new QPushButton("AAA");
    QPushButton* pb1 = new QPushButton("BBB");
    QPushButton* pb2 = new QPushButton("CCC");

    QHBoxLayout* pg = new QHBoxLayout;
    pg->addWidget(pb);
    pg->addWidget(pb1);
    pg->addWidget(pb2);
    pg->addWidget(pmb);
    pg->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    w.setLayout(pg);
    w.resize(800, 600);
    w.show(); return a.exec();
}
#endif // TEST7

#ifdef TEST8

#include<QtWidgets>
int main(int argc, char* argv[])
{
    QApplication aa(argc, argv);
    QWidget* w = new QWidget();
    QMenu* menu = new QMenu(w);
    auto ret1 = menu->addMenu("test");
    ret1->addMenu("aa");
    ret1->addMenu("bb");
    ret1->addMenu("cc");
    menu->exec();
    w->resize(400, 300);
    w->show();

    return aa.exec();
}

#endif // TEST8

#ifdef TEST9

#include <QtWidgets>
#include <iostream>

/*
在窗口resize(w,h)时如果w或者h的值小于窗口内某个控件的w,h
那么resize就在这个方向上无效
此时Qt会自动生成一个合适的值

setFixedSize(w,h)其实就是等同于setMinimumSize(w,h)和setMaximumSize(w,h)
在 setFixedSize(w,h)之后重新设置一下窗体的最小值和最大值就好了,如下:
setMinimumSize(0,0);
setMaximumSize(QSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX)
*/

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    //w.setMinimumSize(80,60);
    //w.setMaximumSize(80,60);
    //w.setFixedSize(80,60);
    w.resize(80, 60);
    std::cout << w.size().width() << '\t' << w.size().height() << '\n';
    w.show();

    return a.exec();
}


#endif // TEST9

#ifdef TEST10

#include<QtWidgets>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) 
{
    QApplication a(argc, argv);
    //创建部件
    QWidget w;

    QPushButton* btn = new QPushButton("pushbutton");
    QToolButton* pb1 = new QToolButton(); 
    pb1->setPopupMode(QToolButton::InstantPopup);  // 设置菜单弹出模式

    QMenu* menu = new QMenu("AAA"); //创建菜单，仅需一个字符串即可。
    //向菜单pm1 中添加菜单项
    QMenu* pm11 = menu->addMenu("ABB"); //pm1 拥有addMenu()函数返回的菜单的所有权。
    pm11->setIcon(QIcon("resource/captureScreen.svg"));
    QMenu* pm12 = menu->addMenu("ACC");
    QMenu* pm13 = menu->addMenu("ADD");
    //向菜单pm11 中添加菜单项
    pm11->addMenu("AAB");
    pm11->addMenu("AAC");

    pb1->setMenu(menu);
    //pb1->setGeometry(100, 100, 50, 50);

    QHBoxLayout* layout = new QHBoxLayout();
    w.setLayout(layout);
    layout->addWidget(pb1);
    layout->addWidget(btn);

    w.resize(300, 200); 
    w.show(); 
    return a.exec();
}

#endif // TEST10

#ifdef TEST11

#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <memory>

int main(int argc,char** argv)
{
    QApplication app(argc, argv);
    auto s = std::make_unique<QStackedWidget>();
    auto w1 = std::make_unique<QWidget>();
    auto w2 = std::make_unique<QWidget>();

    s->addWidget(w1.get());
    auto num1 = s->count();
    s->addWidget(w2.get());
    auto num2 = s->count();
    w1.reset(std::make_unique<QWidget>().release());
    s->addWidget(w1.get());
    auto num3 = s->count();

    s->removeWidget(w1.get());
    auto num4 = s->count();

    return app.exec();
}

#endif // TEST11

#ifdef TEST12

#include<QtWidgets>
int main(int argc, char* argv[]) 
{
    QApplication aa(argc, argv);
    QWidget w;

    // 1
    //QMenuBar* menuBar = new QMenuBar();
    //QPushButton* pushButton = new QPushButton();
    //QHBoxLayout* layout = new QHBoxLayout();
    //QMenu* menu1 = menuBar->addMenu("menu");
    //QAction* action = new QAction("test Action");
    //QCheckBox* checkBox = new QCheckBox("checkbox");
    //menu1->addAction(action);

    //layout->addWidget(checkBox);
    //layout->addWidget(menuBar);
    //layout->addWidget(pushButton);
    //w.setLayout(layout);

    //QObject::connect(action, &QAction::triggered, checkBox, &QCheckBox::toggle);

    // 2
    QToolButton* toolButton = new QToolButton();
    toolButton->setText("tool button  ");
    toolButton->setPopupMode(QToolButton::InstantPopup);
    QPushButton* pushButton = new QPushButton();
    QHBoxLayout* layout = new QHBoxLayout();
    //QMenu* menu1 = menuBar->addMenu("menu");
    QAction* action = new QAction("test Action");
    QCheckBox* checkBox = new QCheckBox("checkbox");
    toolButton->addAction(action);

    layout->addWidget(checkBox);
    layout->addWidget(toolButton);
    layout->addWidget(pushButton);
    w.setLayout(layout);

    QObject::connect(action, &QAction::triggered, checkBox, &QCheckBox::toggle);



    w.resize(333, 222);
    w.show();
    return aa.exec();
}
#endif // TEST12

#ifdef TEST13

#include <QApplication>
#include <QtWidgets>
#include <memory>
#include <iostream>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QPixmap p1;
    if (p1.isNull())
    {
        std::cout << "is null\n";

        QPixmap p2;
        p2.load("C:\\Users\\yangpan\\Desktop\\test.bmp");
        //p1 = p2.copy();
        p1 = p2;
    }
    else
    {
        std::cout << "does not null\n";
    }
    
    p1 = QPixmap(); // 清空QPixmap

    if (p1.isNull())
    {
        std::cout << "failed\n";
    }
    else
    {
        std::cout << "save\n";
        p1.save("C:\\Users\\yangpan\\Desktop\\save.bmp");
    }

    return app.exec();
}

#endif // TEST13

#ifdef TEST14

#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QObject>
#include <iostream>

using namespace std;

class A :public QObject {
public:  //该类的对象用作过滤器对象，使用事件过滤器需继承QObject
    bool eventFilter(QObject* w, QEvent* e) {
        if (e->type() == QEvent::MouseButtonPress)
        {
            cout << w->objectName().toStdString(); //验证w为事件本应到达的目标对象
            cout << "=Ak" << endl;
            return 1;  //返回1表示该事件不再进一步处理
        }
        return 0;
    }
};  /*返回0表示其余事件交还给目标对象处理，本例应返回0，否则添加了该过滤器的安钮会无法显示。*/
class B :public A {
public:   //继承自类A
    bool eventFilter(QObject* w, QEvent* e) {
        if (e->type() == QEvent::MouseButtonPress) {
            cout << w->objectName().toStdString() << "=Bk" << endl;
            return 0;
        }
        return 0;
    }
};

class C :public QWidget 
{ 
public: 
    void mousePressEvent(QMouseEvent* e) {
        cout << "Ck" << endl; 
    } 
};

class D :public QPushButton 
{ 
public:
    void mousePressEvent(QMouseEvent* e) {
        cout << "DK" << endl; 
    } 
};

int main(int argc, char* argv[]) {
    
    QApplication a(argc, argv);
    //创建对象，注意：本例父对象应先创建，以避免生命期过早结束
    A ma;       
    B mb;        
    C mc;        
    D* pd = new D;        
    D* pd1 = new D;

    pd->setText("AAA");    
    pd->move(22, 22);      
    pd1->setText("BBB");    
    pd1->move(99, 22);
    //设置对象名
    ma.setObjectName("ma");       
    mb.setObjectName("mb");       
    mc.setObjectName("mc");
    pd->setObjectName("pd");       
    pd1->setObjectName("pd1");
    //设置父对象
    pd->setParent(&mc);    
    pd1->setParent(&mc);
    mb.setParent(&ma);    //①
     //注册过滤器对象
    pd->installEventFilter(&mb);  //②
    pd1->installEventFilter(&ma); //③

    mc.resize(333, 222);    
    mc.show();    
    a.exec();

    return 0;
}

#endif // TEST14

#ifdef TEST15

#include <QApplication>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QtWidgets>

class KeyPressEater : public QObject
{
protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            qDebug("Ate key press %d", keyEvent->key());
            return true;
        }
        else {
            // standard event processing
            return QObject::eventFilter(obj, event);
        }
    }
};

class Widget :public QWidget
{
public:
    Widget()
    {
        KeyPressEater* keyPressEater = new KeyPressEater();

        QPushButton* pushButton = new QPushButton(this);
        pushButton->setGeometry(0, 0, 50, 50);
        pushButton->installEventFilter(keyPressEater);

        QListView* listView = new QListView(this);
        listView->setGeometry(200, 200, 100, 100);
        listView->installEventFilter(keyPressEater);
    }
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    auto w = new Widget();
    w->setMinimumSize(800, 600);
    w->show();

    return app.exec();
}

#endif // TEST15

#ifdef TEST16

#include <QApplication>

int main()
{}

#endif // TEST16
