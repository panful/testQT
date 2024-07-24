/*
1. 重写QWidget测试
2. QMdiArea 多文档窗口，注意和QStackedWidget的区别
3. 黄勇 QDockWidget的使用及自定义标题栏部件
4. QDockWidget的大小以及显示隐藏 https://blog.csdn.net/weixin_40293570/article/details/111314196
5. QToolBar(可以拖动的按钮，一般用作菜单栏）
6. QDockWidget多窗口，标题栏添加全屏显示，自定义标题栏
7. 各种QMessageBox
8. Qt子对象自动释放
9. Qt释放Layout不会自动释放layout中的部件，但是会释放QSpacerItem等item，详细看TEST10
10.使用智能指针析构函数报错 "can't delete an incomplete type" 因为声明顺序错误，QSpacerItem不能使用智能指针
11.Qt中信号槽连接六种方式
12.树控件 QTreeWidget
13.TEST6 打印Qt事件，QDockWidget鼠标事件，焦点事件 focus
14.Qt枚举打印字符串QMetaEnum 自定义枚举使用QMetaEnum
15.自定义QWidget的标题栏
16.QTabWidget // https://blog.csdn.net/i2program/article/details/126863980
17.自定义部件置灰后事件的响应
18.QDialog
*/

#define TEST18

#ifdef TEST1

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
};

#endif // TEST1

#ifdef TEST2

#include <QDebug>
#include <QDockwidget>
#include <QMainWindow>
#include <QMdiArea>
#include <QPushButton>
#include <QVBoxLayout>

class Widget : public QMainWindow
{
    Q_OBJECT;

public:
    explicit Widget(QWidget* parent = nullptr)
    {
        m_btnAdd = new QPushButton("Add");
        m_btnAdd->setMaximumSize(50, 30);
        m_mdiArea = new QMdiArea();

        QDockWidget* dockWidget1 = new QDockWidget();
        QDockWidget* dockWidget2 = new QDockWidget();
        dockWidget1->setWindowTitle("dock1");
        dockWidget2->setWindowTitle("dock2");
        m_mdiArea->addSubWindow(dockWidget1);
        m_mdiArea->addSubWindow(dockWidget2);

        QWidget* centerWindow = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout;
        this->setCentralWidget(centerWindow);
        centerWindow->setLayout(mainLayout);

        mainLayout->addWidget(m_btnAdd);
        mainLayout->addWidget(m_mdiArea);

        connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(OnBtnAdd()));
    }
    ~Widget() = default;

private slots:
    void OnBtnAdd()
    {
    }

private:
    QPushButton* m_btnAdd { nullptr };
    QMdiArea* m_mdiArea { nullptr };
};
#endif // TEST2

#ifdef TEST3

#include <QDebug>
#include <QtOpenGLWidgets>
#include <QtWidgets>

class Widget : public QWidget
{
    Q_OBJECT // 最好继承QMainWindow 类
        public : QDockWidget* pd1,
                 *pd2,
                 *pd3;
    QMainWindow* pw;
    QPushButton *pb, *pb1, *pb2, *pb3, *pb4, *pb5, *pb6;

    Widget(QWidget* p = 0)
        : QWidget(p)
    {
        pw = new QMainWindow(this);

        QWidget* pw1 = new QWidget;
        QWidget* pw2 = new QWidget;
        QWidget* pw3 = new QWidget;
        QWidget* pw4 = new QWidget;

        QOpenGLWidget* pogw = new QOpenGLWidget;
        pogw->setMinimumSize(50, 50);

        QMenuBar* menuBar = new QMenuBar();
        menuBar->setMinimumSize(50, 20);
        QMenu* menu = menuBar->addMenu("Menu");
        menu->addAction("111");
        menu->addAction("222");

        pd1 = new QDockWidget;
        pd2 = new QDockWidget;
        pd3 = new QDockWidget;

        // 布局中心部件
        pb = new QPushButton("XXX", pw1);
        pw->setCentralWidget(pw1);
        pw1->setStyleSheet("background-color: rgb(127,127,0);"); // 设置中心部件的背景色
        // 布局可停靠窗口pd1
        pw->addDockWidget(Qt::LeftDockWidgetArea, pd1); // 把pd1 添加到主窗口的左侧
        pb1 = new QPushButton("Dock1", pw2);
        pb2 = new QPushButton("CCC", pw2);
        pb2->move(0, 33);
        pd1->setWidget(pw2);        // 设置pd1 中的内容
        pd1->setWindowTitle("AAA"); // 设置pd1 的标题
        // 获取QDoctWidget 布局的大小约束(默认为SetMinAndMAxSize)，实际使用时有可能会更改此约束
        // qDebug() << pd1->layout()->sizeConstraint();
        // 布局可停靠窗口pd2
        pw->addDockWidget(Qt::RightDockWidgetArea, pd2);
        pb3 = new QPushButton("Float", pw3);
        pb4 = new QPushButton("Hide", pw3);
        pb4->move(77, 0);
        pb5 = new QPushButton("Dock2");
        pw3->setStyleSheet("background-color: rgb(0,127,0);"); // 设置pw3 的背景色
        // pd2->setTitleBarWidget(pw3); //把pw3 设置为pd2 的标题栏(设置自定义标题栏)
        pd2->setTitleBarWidget(menuBar);
        // 设置可停靠窗口和标题栏部件的最小大小，若设置不合适，会使可停靠窗口无法显示某些部件。
        pd2->setMinimumSize(155, 144);
        pw3->setMinimumSize(155, 55);
        // pw3->resize(111,111); //此函数设置的大小不起作用。
        // 设置pd2 的标题及其内容
        pd2->setWindowTitle("BBB");
        pd2->setWidget(pogw);
        // pd2->setWidget(pb5);
        // 布局可停靠窗口pd3
        pw->addDockWidget(Qt::TopDockWidgetArea, pd3);
        pb6 = new QPushButton("Dock3");
        pd3->setWidget(pb6);
        // pd3->setWidget(pogw);
        pd3->setTitleBarWidget(pw4);
        /*因为pw4 的最小大小默认为0，因此设置pw4 为pd3 的标
        题栏，会使pd3 的标题栏不可见(因为大小为0)。*/

        // 点击pb 使pd3 处于悬浮状态，主要用于验证pd3 是一个可停靠窗口
        QObject::connect(pb, &QPushButton::clicked, this, &Widget::f);
        QObject::connect(pb3, &QPushButton::clicked, this, &Widget::f3); // 点击pb3 使pd2 处于悬浮状态
        QObject::connect(pb4, &QPushButton::clicked, this, &Widget::f4); // 点击pb3 使pd2 停靠在主窗口

        pw->resize(333, 222);
        pw->show();
    }
public slots:
    void f() { pd3->setFloating(1); }

    void f3() { pd2->setFloating(1); }

    void f4() { pd2->setFloating(0); }
};

#endif // TEST3

#ifdef TEST4

#include <QtWidgets>

class WidgetTest : public QWidget
{
public:
    QSize sizeHint() const override
    {
        return m_size;
    }
    QSize minimumSizeHint() const override
    {
        return m_minimumSize;
    }

    QSize m_size { -1, -1 };
    QSize m_minimumSize { 50, 30 }; // widget最小的大小
};

class Widget : public QMainWindow
{
public:
    explicit Widget(QWidget* parent = nullptr)
    {
        auto dock1 = new QDockWidget();
        dock1->setWidget(new WidgetTest());
        dock1->setWindowTitle("dock1");

        auto dock2 = new QDockWidget();
        dock2->setWidget(new WidgetTest());
        dock1->setWindowTitle("dock2");

        this->addDockWidget(Qt::LeftDockWidgetArea, dock1);
        this->addDockWidget(Qt::RightDockWidgetArea, dock2);

        // 设置dockwidget的显示与隐藏
        dock1->show();
        dock2->hide();
    }
};

#endif // TEST4

#ifdef TEST5

#include <QtWidgets>
using namespace std;
class Widget : public QWidget
{
    Q_OBJECT
public:
    QToolBar *pt1, *pt2, *pt3, *pt4;
    QPushButton* pb1;
    QMainWindow* pw;

    Widget(QWidget* p = 0)
        : QWidget(p)
    {
        pw = new QMainWindow; // 主窗口
        pb1 = new QPushButton("AAA", this);
        pw->setCentralWidget(this); // 设置主窗口的中心部件
        // 初始化工具栏
        pt1 = new QToolBar("TTT", pw); // 标题TTT 不会显示为工具栏中的工具按钮文本
        pt2 = new QToolBar("TTT", pw);
        pt3 = new QToolBar("TTT", pw);
        pt4 = new QToolBar("TTT", pw);
        // 把工具栏添加到主窗口pw 中
        pw->addToolBar(pt1);
        pw->addToolBar(pt2);
        pw->addToolBar(pt3);
        pw->addToolBar(Qt::RightToolBarArea, pt4); // 把工具栏pt4 添加到右侧的工具栏区域
        // 向各工具栏中添加动作
        pt1->addAction(QIcon("resource/expand.svg"), "111");
        pt1->addAction(QIcon("resource/expand.svg"), "112");
        pt2->addAction(QIcon("resource/expand.svg"), "221");
        pt2->addAction(QIcon("resource/expand.svg"), "222");
        pt3->addAction(QIcon("resource/expand.svg"), "331");
        pt3->addAction(QIcon("resource/expand.svg"), "332");
        pt4->addAction(QIcon("resource/expand.svg"), "441");
        pt4->addAction(QIcon("resource/expand.svg"), "442");
        // 设置各工具栏的属性
        pt2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); // 把文字显示在图标的侧面
        pt3->setToolButtonStyle(Qt::ToolButtonTextOnly);       // 仅显示文字
        pt4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);  // 文字显示在图标的下面
        pt2->setFloatable(0);                                  // pt2 不能成为独立窗口
        pt3->setMovable(0);                                    // pt3 不可移动
        // pt4 只可在上、左、右三个区域放置，但不能放置在底部
        pt4->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea | Qt::RightToolBarArea);
        pw->resize(333, 222);
        pw->show();
        // 点击按钮pb1 可把工具栏放置在右侧
        QObject::connect(pb1, &QPushButton::clicked, this, &Widget::f1);
    }
public slots:
    void f1()
    {
        // 使用QMainWindow::addToolBar()以编程的方式设置工具栏的位置，QToolBar 类中没有相应的函数
        pw->addToolBar(Qt::RightToolBarArea, pt1);
    }
};

#endif // TEST5

#ifdef TEST6

#include <QColor>
#include <QtOpenGLWidgets>
#include <QtWidgets>

#include <array>
#include <iostream>

class MyOGL : public QOpenGLWidget
{
};

class CustomDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit CustomDockWidget(QWidget* parent = nullptr)
        : QDockWidget(parent)
    {
        // 等价于事件 QEvent::ZOrderChange
        // connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(OnTopLevelChanged(bool)));

        // 报错：QWidget::setMinimumSize: (/CustomDockWidget) Negative sizes (0,-1) are not possible
        // 设置一下Layout即可

        // 自定义QDockWidget标题栏
        //-------------------------------------------
        auto combobox = new QComboBox();
        combobox->addItem("111");
        combobox->addItem("222");
        combobox->addItem("333");
        combobox->addItem("444");

        auto w = new QWidget();
        auto layout = new QHBoxLayout();
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(combobox);
        layout->addWidget(new QPushButton("aaa"));
        layout->addWidget(new QPushButton("bbb"));
        layout->addSpacerItem(new QSpacerItem(100, 30));
        w->setLayout(layout);
        w->setMinimumSize(50, 30);

        this->setTitleBarWidget(w);
        // this->setTitleBarWidget(new QPushButton("Button"));
        //--------------------------------------------------

        this->layout()->setContentsMargins(0, 0, 0, 0);
        this->layout()->setSpacing(0);
    }

    ~CustomDockWidget()
    {
        std::cout << "destroy\n";
    }

private slots:
    void OnTopLevelChanged(bool topLevel)
    {
        std::cout << this->parentWidget()->width() << ',' << this->parentWidget()->height() << std::endl;
        if (topLevel)
        {
            // resize的参数不能大于父窗口
            this->resize(this->parentWidget()->width() / 2, this->parentWidget()->height() / 2); // 修复从选项卡切换到多窗口显示报错:unable to set geometry
        }

        // std::cout << "floating changed\t" << topLevel << std::endl;
    }
    void OnVisibitityChanged(bool visible)
    {
    }
    void OnAllowedAreasChanged(Qt::DockWidgetArea allowedAreas)
    {
    }
    void OnDockLoacationChanged(Qt::DockWidgetArea area)
    {
    }
    void OnFeaturesChanged(QDockWidget::DockWidgetFeature fetatures)
    {
    }

protected:
    // 为QDockWidget添加最大化、最小化、关闭按钮
    bool event(QEvent* event) override
    {
        // 构造函数中修改了标题栏之后，不要在此处再设置WindowFlag

        // if (this->windowFlags() & (Qt::WindowCloseButtonHint
        //     | Qt::WindowMaximizeButtonHint
        //     | Qt::WindowMinimizeButtonHint))
        //{
        //     return QDockWidget::event(event);
        // }

        //// QDockWidget被拖出或者拖入都会触发该事件
        // if (QEvent::ZOrderChange == event->type())
        //{
        //     if (this->isFloating()) // 判断是否为浮动窗口
        //     {
        //         QWidget w;
        //         this->setMaximumSize(w.maximumSize()); // 最大化按钮
        //         this->setWindowFlags(Qt::Dialog
        //             | Qt::WindowCloseButtonHint
        //             | Qt::WindowMaximizeButtonHint
        //             | Qt::WindowMinimizeButtonHint);
        //         this->resize(this->parentWidget()->width()/2, this->parentWidget()->height()/2); // 修复从选项卡切换到多窗口显示报错:unable to set geometry
        //         this->show();
        //     }
        // }

        return QDockWidget::event(event);
    }

    // 点击关闭按钮后不关闭QDockWidget，将浮动窗口嵌入到mainWindow
    void closeEvent(QCloseEvent* evt) override
    {
        if (this->isFloating())
        {
            this->setFloating(false);
            // QEvent* e = new QEvent(QEvent::ZOrderChange);
            // QApplication::sendEvent(this, e);
            evt->ignore();
        }
        // return QDockWidget::closeEvent(evt);
    }
};

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        // 中间窗体默认为 nullptr
        QWidget* centralWidget = takeCentralWidget();

        // this->tabifiedDockWidgets

        // 开启该属性后，viewer1和viewer2原本只能水平布局，现在可以想怎样布局就怎样布局
        this->setDockNestingEnabled(true); // 设置嵌套布局为true，默认为false

        // m_dockWidgets[0] = new QDockWidget();
        m_dockWidgets[0] = new CustomDockWidget();
        MyOGL* oglWidget0 = new MyOGL();
        // oglWidget0->SetCustomSizeHint({ 400, 300 });
        m_dockWidgets[0]->setWidget(oglWidget0);
        m_dockWidgets[0]->setWindowTitle("viewer 1");
        // QPushButton* btn = new QPushButton("Button");
        // btn->setMinimumSize(50, 30);
        // m_dockWidgets[0]->setTitleBarWidget(btn); // 修改dockwidget的标题栏
        auto titleW = m_dockWidgets[0]->titleBarWidget(); // 如果没有使用setTitleBarWidget返回nullptr
        // auto titleWLayout = titleW->layout();
        // titleWLayout->addWidget(btn);
        m_dockWidgets[0]->setFeatures(m_dockWidgets[0]->features() & ~QDockWidget::DockWidgetClosable);

        m_dockWidgets[1] = new CustomDockWidget();
        MyOGL* oglWidget1 = new MyOGL();
        // oglWidget1->SetCustomSizeHint({ 400, 300 });
        m_dockWidgets[1]->setWidget(oglWidget1);
        m_dockWidgets[1]->setWindowTitle("viewer 2");
        m_dockWidgets[1]->setFeatures(m_dockWidgets[1]->features() & ~QDockWidget::DockWidgetClosable);

        m_dockWidgets[2] = new CustomDockWidget();
        MyOGL* oglWidget2 = new MyOGL();
        // oglWidget2->SetCustomSizeHint({ 400, 300 });
        m_dockWidgets[2]->setWidget(oglWidget2);
        m_dockWidgets[2]->setWindowTitle("viewer 3");
        m_dockWidgets[2]->setFeatures(m_dockWidgets[2]->features() & ~QDockWidget::DockWidgetClosable);

        m_dockWidgets[3] = new CustomDockWidget();
        MyOGL* oglWidget3 = new MyOGL();
        // oglWidget3->SetCustomSizeHint({ 400, 300 });
        m_dockWidgets[3]->setWidget(oglWidget3);
        m_dockWidgets[3]->setWindowTitle("viewer 4");
        m_dockWidgets[3]->setFeatures(m_dockWidgets[3]->features() & ~QDockWidget::DockWidgetClosable);

        this->addDockWidget(Qt::TopDockWidgetArea, m_dockWidgets[0]);
        this->addDockWidget(Qt::TopDockWidgetArea, m_dockWidgets[1]);
        this->addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[2]);
        this->addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[3]);

        // dockWidget允许停靠的位置，不设置好像哪里也都可以停靠
        // m_dockWidgets[0]->setAllowedAreas(Qt::AllDockWidgetAreas);
        // m_dockWidgets[1]->setAllowedAreas(Qt::AllDockWidgetAreas);
        // m_dockWidgets[2]->setAllowedAreas(Qt::AllDockWidgetAreas);
        // m_dockWidgets[3]->setAllowedAreas(Qt::AllDockWidgetAreas);

        // 禁止标签页方式停靠
        this->setDockOptions(this->dockOptions() & ~DockOption::AllowTabbedDocks);

        m_dockWidgets[1]->hide();
        m_dockWidgets[2]->hide();
        m_dockWidgets[3]->hide();
    }
public slots:
    void SetViewport(int i)
    {
        auto dockWidth = static_cast<int>(this->geometry().width() * 0.5);
        auto dockHeight = static_cast<int>(this->geometry().height() * 0.5);

        // 将所有悬浮的窗口复位
        std::for_each(m_dockWidgets.begin(), m_dockWidgets.end(), [](QDockWidget* dock) {
                if (dock->isFloating())
                {
                    dock->setFloating(false);
                } });

        switch (i)
        {
        case 1:
        {
            m_dockWidgets[1]->hide();
            m_dockWidgets[2]->hide();
            m_dockWidgets[3]->hide();
        }
        break;
        case 2:
        { // 左1右1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->hide();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
        }
        break;
        case 3:
        { // 上1下1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->hide();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        case 4:
        { // 上1下2
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[1], m_dockWidgets[2], Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[1], m_dockWidgets[2] }, { dockWidth, dockWidth }, Qt::Horizontal);
        }
        break;
        case 5:
        { // 上2下1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
        }
        break;
        case 6:
        { // 左2右1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        case 7:
        { // 4
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->show();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[2], m_dockWidgets[3], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[1], m_dockWidgets[3], Qt::Vertical);

            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[2], m_dockWidgets[3] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[1], m_dockWidgets[3] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        case 8:
        { // 左1右2
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[1], m_dockWidgets[2], Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[1], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        default:
            break;
        }

        m_viewportMode = i;
    }
    /// @brief 打印所有窗口的信息
    void PrintDockInfo()
    {
        std::cout << std::boolalpha << "   === Dock Infomation ===\n";
        for (size_t i = 0; i < 4; i++)
        {
            // 注意isHidden和isVisible的区别
            std::cout << std::endl
                      << i << i << i << std::endl;
            std::cout << "\t area:" << m_dockWidgets[0]->allowedAreas() << '\n';
            std::cout << "\t show:" << !m_dockWidgets[i]->isHidden() << '\n';
            std::cout << "\t float:" << m_dockWidgets[i]->isFloating() << '\n';
            std::cout << "\t visible:" << m_dockWidgets[i]->isVisible() << '\n';
            // std::cout << "\t width:" << m_dockWidgets[i]->width() << '\n';
            // std::cout << "\t height:" << m_dockWidgets[i]->height() << '\n';
        }
    }

    /// @brief 将所有窗口复原到QMainWindow
    void DontFloat()
    {
        for (size_t i = 0; i < 4; i++)
        {
            // 将悬浮的QDockWidget放入QMainWindow
            m_dockWidgets[i]->setFloating(false);
        }
    }

private:
    std::array<QDockWidget*, 4> m_dockWidgets;
    int m_viewportMode { 1 };
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget* parent = nullptr)
        : QWidget(parent)
        , mainWindow(new MyMainWindow())
    {
        auto mode1 = new QAction();
        auto mode2 = new QAction();
        auto mode3 = new QAction();
        auto mode4 = new QAction();
        auto mode5 = new QAction();
        auto mode6 = new QAction();
        auto mode7 = new QAction();
        mode1->setIcon(QIcon("resource/posX.svg"));
        mode2->setIcon(QIcon("resource/posX.svg"));
        mode3->setIcon(QIcon("resource/posX.svg"));
        mode4->setIcon(QIcon("resource/posX.svg"));
        mode5->setIcon(QIcon("resource/posX.svg"));
        mode6->setIcon(QIcon("resource/posX.svg"));
        mode7->setIcon(QIcon("resource/posX.svg"));
        connect(mode1, &QAction::triggered, [this]() { mainWindow->SetViewport(1); });
        connect(mode2, &QAction::triggered, [this]() { mainWindow->SetViewport(2); });
        connect(mode3, &QAction::triggered, [this]() { mainWindow->SetViewport(3); });
        connect(mode4, &QAction::triggered, [this]() { mainWindow->SetViewport(4); });
        connect(mode5, &QAction::triggered, [this]() { mainWindow->SetViewport(5); });
        connect(mode6, &QAction::triggered, [this]() { mainWindow->SetViewport(6); });
        connect(mode7, &QAction::triggered, [this]() { mainWindow->SetViewport(7); });

        // 设置Viewport
        auto viewport = new QToolButton();
        viewport->setIcon(QIcon("resource/expand.svg"));
        viewport->setPopupMode(QToolButton::InstantPopup);
        viewport->addAction(mode1);
        viewport->addAction(mode2);
        viewport->addAction(mode3);
        viewport->addAction(mode4);
        viewport->addAction(mode5);
        viewport->addAction(mode6);
        viewport->addAction(mode7);

        QPushButton* btnPrint = new QPushButton();
        QPushButton* btnRestore = new QPushButton();
        btnPrint->setIcon(QIcon("resource/posX.svg"));
        btnRestore->setIcon(QIcon("resource/posX.svg"));
        connect(btnPrint, SIGNAL(clicked()), mainWindow, SLOT(PrintDockInfo()));
        connect(btnRestore, SIGNAL(clicked()), mainWindow, SLOT(DontFloat()));

        QHBoxLayout* hBtnLayout = new QHBoxLayout(); // 按钮布局
        hBtnLayout->addWidget(viewport);
        hBtnLayout->addWidget(btnPrint);
        hBtnLayout->addWidget(btnRestore);
        hBtnLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

        QVBoxLayout* vMainLayout = new QVBoxLayout(); // 整个窗口布局
        vMainLayout->addLayout(hBtnLayout);
        vMainLayout->addWidget(mainWindow);

        this->setLayout(vMainLayout);
    }

private:
    MyMainWindow* mainWindow { nullptr };
};

#endif // TEST6

#ifdef TEST7

#include <QtWidgets>
#include <iostream>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout();
        QPushButton* btn1 = new QPushButton("question");
        QPushButton* btn2 = new QPushButton("warning");
        QPushButton* btn3 = new QPushButton("information");
        QPushButton* btn4 = new QPushButton("critical");
        QPushButton* btn5 = new QPushButton("about");

        layout->addWidget(btn1);
        layout->addWidget(btn2);
        layout->addWidget(btn3);
        layout->addWidget(btn4);
        layout->addWidget(btn5);

        this->setLayout(layout);

        connect(btn1, SIGNAL(clicked()), this, SLOT(QuestionBox()));
        connect(btn2, SIGNAL(clicked()), this, SLOT(Warning()));
        connect(btn3, SIGNAL(clicked()), this, SLOT(Information()));
        connect(btn4, SIGNAL(clicked()), this, SLOT(Critical()));
        connect(btn5, SIGNAL(clicked()), this, SLOT(About()));
    }
private slots:
    void QuestionBox()
    {
        if (QMessageBox::Yes == QMessageBox::question(this, "s", "sss", QMessageBox::Yes | QMessageBox::No))
        {
            std::cout << "yes\n";
        }
        else
        {
            std::cout << "no\n";
        }
    }

    void Information()
    {
        if (QMessageBox::Ok == QMessageBox::warning(this, "Information", "this is an information.", QMessageBox::Ok | QMessageBox::Cancel))
        {
            std::cout << "ok\n";
        }
        else
        {
            std::cout << "cancel\n";
        }
    }

    void Warning()
    {
        if (QMessageBox::Ok == QMessageBox::information(this, "warning", "this is a warning.", QMessageBox::Ok | QMessageBox::Cancel))
        {
            std::cout << "ok\n";
        }
        else
        {
            std::cout << "cancel\n";
        }
    }

    void Critical()
    {
        QMessageBox::critical(this, "Error", "this is an error.", QMessageBox::Yes);
    }

    void About()
    {
        QMessageBox::about(this, "about", "this is an about");
    }
};
#endif // TEST7

#ifdef TEST8

#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <iostream>

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(QWidget* parent = nullptr)
        : QPushButton(parent)
    {
        std::cout << "construct\n";
        this->setText("custom btn");
    }

    ~CustomButton()
    {
        // 只要为本对象设置了父窗口，父窗口被释放，本对象就会释放
        std::cout << "destruct\n";
    }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        btn1 = new QPushButton("Qt btn", this);
        btn1->setGeometry(0, 0, 100, 100);

        btn2 = new CustomButton(this);
        btn2->setGeometry(100, 100, 100, 100);

        btn3 = std::make_unique<CustomButton>(this);
        btn3->setGeometry(200, 200, 100, 100);

        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(new CustomButton());
        this->setLayout(layout);
    }

    ~Widget()
    {
        // 不需要释放就可以调用析构函数

        // delete btn1;
        // btn1 = nullptr;

        // delete btn2;
        // btn2 = nullptr;
    }

private:
    QPushButton* btn1 { nullptr };
    CustomButton* btn2 { nullptr };

    std::unique_ptr<CustomButton> btn3 { nullptr };
};

#endif // TEST8

#ifdef TEST9

#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <iostream>

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(std::string name = std::string(), QWidget* parent = nullptr)
        : QPushButton(parent)
    {
        std::cout << " === Button construct\n";
        this->setText(name.c_str());
    }

    ~CustomButton() override
    {
        std::cout << " === Button destruct\n";
    }
};

class CustomLayout : public QVBoxLayout
{
    Q_OBJECT

public:
    CustomLayout()
    {
        std::cout << " *** Layout construct\n";
    }

    ~CustomLayout() override
    {
        std::cout << " *** Layout destruct\n";
    }
};

class MiddleWare
{
public:
    MiddleWare()
        : m_widget(nullptr)
        , m_mainLayout(nullptr)
    {
    }

    ~MiddleWare()
    {
        if (m_mainLayout)
        {
            // 释放layout并不能自动释放layout中的部件
            // delete m_mainLayout;
            // m_mainLayout = nullptr;
        }
        if (m_widget)
        {
            // 释放父窗口可以自动释放本类中new出来的部件，但是父窗口不应该在本类中释放
            delete m_widget; // 只将父窗口置为nullptr，不使用delete也不会释放子部件
            m_widget = nullptr;
        }
    }

    void SetParentWidget(QWidget* w)
    {
        m_widget = w;

        m_mainLayout = new CustomLayout();
        auto btnLayout = new QHBoxLayout();

        btnLayout->addWidget(new CustomButton("111"));
        btnLayout->addWidget(new CustomButton("222"));

        m_mainLayout->addLayout(btnLayout);
        m_mainLayout->addWidget(new CustomButton("333"));

        w->setLayout(m_mainLayout);
    }

private:
    QWidget* m_widget;
    CustomLayout* m_mainLayout;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
        : QWidget(parent)
        , m_btnRelease(new QPushButton("Release", this))
        , m_middleWare(std::make_unique<MiddleWare>())
    {
        QVBoxLayout* layout = new QVBoxLayout();
        this->setLayout(layout);
        layout->addWidget(m_btnRelease);
        auto widget = new QWidget();
        layout->addWidget(widget);
        m_middleWare->SetParentWidget(widget);

        connect(m_btnRelease, &QPushButton::clicked, [this]() { this->OnBtnRelease(); });
    }

    ~Widget()
    {
        std::cout << "Widget destruct --------------------\n";
    }

private slots:
    void OnBtnRelease()
    {
        std::cout << "on release\n";
        m_middleWare.reset();
    }

private:
    std::unique_ptr<MiddleWare> m_middleWare { nullptr };
    QPushButton* m_btnRelease;
};

#endif // TEST9

#ifdef TEST10

#include <QBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include <iostream>

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(std::string name = std::string(), QWidget* parent = nullptr)
        : QPushButton(parent)
    {
        std::cout << " === Button construct\n";
        this->setText(name.c_str());
    }

    ~CustomButton() override
    {
        std::cout << " === Button destruct" << this->text().toStdString() << '\n';
    }
};

class CustomVLayout : public QVBoxLayout
{
    Q_OBJECT

public:
    CustomVLayout()
    {
        std::cout << " *** V Layout construct\n";
    }

    ~CustomVLayout() override
    {
        std::cout << " *** V Layout destruct\n";
    }
};

class CustomHLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    CustomHLayout()
    {
        std::cout << " *** H Layout construct\n";
    }

    ~CustomHLayout() override
    {
        std::cout << " *** H Layout destruct\n";
    }
};

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    CustomWidget()
    {
        std::cout << " +++ Widget construct\n";
    }

    ~CustomWidget() override
    {
        std::cout << " +++ Widget destruct\n";
    }
};

class CustomSpacerItem : public QSpacerItem
{
    // Q_OBJECT  // 弹簧不能使用 Q_OBJECT

public:
    CustomSpacerItem(int w, int h, QSizePolicy::Policy hData = QSizePolicy::Minimum,
        QSizePolicy::Policy vData = QSizePolicy::Minimum)
        : QSpacerItem(w, h, hData, vData)
    {
        std::cout << " +++ SpacerItem construct\n";
    }

    ~CustomSpacerItem() override
    {
        std::cout << " +++ SpacerItem destruct\n";
    }
};

class MiddleWare : public QObject
{
    Q_OBJECT

public:
    MiddleWare()
        : m_widget(nullptr)
        , m_mainLayout(nullptr)
    {
    }

    ~MiddleWare()
    {
    }

    void SetParentWidget(QWidget* w)
    {
        m_widget = w;

        m_mainLayout = std::make_unique<CustomVLayout>();
        m_btnLayout = std::make_unique<CustomHLayout>();
        m_subWidget = std::make_unique<CustomWidget>();
        m_subWdigetLayout = std::make_unique<CustomVLayout>();

        m_btn1 = std::make_unique<CustomButton>("111");
        connect(m_btn1.get(), &QPushButton::clicked, [this]() { this->OnBtn1(); });
        m_btn2 = std::make_unique<CustomButton>("222");
        m_btn3 = std::make_unique<CustomButton>("333");
        m_btn4 = std::make_unique<CustomButton>("444");
        m_btn5 = std::make_unique<CustomButton>("555");

        // m_spacerItem = std::make_unique< CustomSpacerItem>(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_spacerItem = new CustomSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_btnLayout->addWidget(m_btn1.get());
        m_btnLayout->addWidget(m_btn2.get());
        m_btnLayout->addWidget(m_btn3.get());
        // m_btnLayout->addItem(m_spacerItem.get());
        m_btnLayout->addItem(m_spacerItem);

        m_subWdigetLayout->addWidget(m_btn4.get());
        m_subWdigetLayout->addWidget(m_btn5.get());

        m_subWidget->setLayout(m_subWdigetLayout.get());

        m_mainLayout->addLayout(m_btnLayout.get());
        m_mainLayout->addWidget(m_subWidget.get());

        m_widget->setLayout(m_mainLayout.get());
    }

private slots:
    void OnBtn1()
    {
        std::cout << "11111111111111111111111\n";
    }

private:
    QWidget* m_widget;

    std::unique_ptr<CustomVLayout> m_mainLayout;

    // 如果将 m_subWidget 声明在[1]处，释放成功
    // 如果将 m_subWidget 声明在[2]处，释放失败，报错 memory.cpp line:3130 "can't delete an incomplete type"
    // 因为 m_subWidget，声明在类的最下面，会最先调用析构函数，且m_subWidget是父对象
    // Qt父对象析构会将所有的子对象自动释放，所以再次调用子对象的析构函数的时候就会崩溃，因为已经释放

    std::unique_ptr<CustomWidget> m_subWidget; // [1]

    std::unique_ptr<CustomVLayout> m_subWdigetLayout;

    // std::unique_ptr< CustomSpacerItem> m_spacerItem; // 不要对QSpacerItem使用智能指针，无论放在那里析构都会崩溃
    CustomSpacerItem* m_spacerItem; // 布局被析构，QSpacerItem也会被析构，布局析构时布局中的小部件不会被析构

    std::unique_ptr<CustomHLayout> m_btnLayout;

    std::unique_ptr<CustomButton> m_btn1;
    std::unique_ptr<CustomButton> m_btn2;
    std::unique_ptr<CustomButton> m_btn3;
    std::unique_ptr<CustomButton> m_btn4;
    std::unique_ptr<CustomButton> m_btn5;

    // std::unique_ptr<CustomWidget> m_subWidget;     // [2]
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
        : QWidget(parent)
        , m_btnRelease(new QPushButton("Release", this))
        , m_middleWare(std::make_unique<MiddleWare>())
    {
        QVBoxLayout* layout = new QVBoxLayout();
        this->setLayout(layout);
        layout->addWidget(m_btnRelease);
        auto widget = new QWidget();
        layout->addWidget(widget);
        m_middleWare->SetParentWidget(widget);

        connect(m_btnRelease, &QPushButton::clicked, [this]() { this->OnBtnRelease(); });
    }

    ~Widget()
    {
        std::cout << "Widget destruct --------------------\n";
    }

private slots:
    void OnBtnRelease()
    {
        std::cout << "on release\n";
        m_middleWare.reset();
    }

private:
    std::unique_ptr<MiddleWare> m_middleWare { nullptr };
    QPushButton* m_btnRelease;
};

#endif // TEST10

#ifdef TEST11

#include <QtWidgets>
#include <iostream>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        m_btn = new QPushButton("test", this);

        // connect(m_btn, &QPushButton::clicked, [this]() {this->Print(); });

        // 最后一个参数指示信号槽连接方式
        connect(m_btn, SIGNAL(clicked()), this, SLOT(Print()), Qt::UniqueConnection);
    }
    ~Widget()
    {
    }

private slots:
    void Print()
    {
        std::cout << "clicked btn\n";
    }

private:
    QPushButton* m_btn;
};

// Qt::QueuedConnection

#endif // TEST11

#ifdef TEST12

#include <QList>
#include <QTreeWidget>
#include <QWidget>

class Widget : public QWidget
{
public:
    Widget()
    {
        QTreeWidget* treeWidget = new QTreeWidget(this);                  // 创建
        treeWidget->setColumnCount(1);                                    // 设置列（注意这是列，不是顶层节点）
        treeWidget->setHeaderLabel("Item Tree");                          // 设置标题
        treeWidget->setGeometry(0, 0, this->width() / 2, this->height()); // 设置大小

        QList<QTreeWidgetItem*> items;

        // 创建两个节点
        QTreeWidgetItem* fItem1 = new QTreeWidgetItem(treeWidget, QStringList("f1"));
        QTreeWidgetItem* fItem2 = new QTreeWidgetItem(treeWidget, QStringList("f2"));

        items.append(fItem1);
        items.append(fItem2);

        // 添加顶层节点
        treeWidget->insertTopLevelItems(0, items);
        // 节点始终保持展开
        // treeWidget->setItemsExpandable(false);
        // treeWidget->expandAll();

        // 创建子节点
        QTreeWidgetItem* fItem1a = new QTreeWidgetItem(fItem1, QStringList(QString("f1a")));
        QTreeWidgetItem* fItem1b = new QTreeWidgetItem(fItem1, QStringList(QString("f1b")));

        QTreeWidgetItem* fItem2a = new QTreeWidgetItem(fItem2, QStringList(QString("f2a")));
        QTreeWidgetItem* fItem2b = new QTreeWidgetItem(fItem2, QStringList(QString("f2b")));

        // 将子节点添加到父节点
        fItem1->addChild(fItem1a);
        fItem1->addChild(fItem1b);

        fItem2->addChild(fItem2a);
        fItem2->addChild(fItem2b);

        // 再添加一级子节点（方法一样）
        QTreeWidgetItem* fItem1aa = new QTreeWidgetItem(fItem1a, QStringList("aaa"));
        fItem1a->addChild(fItem1aa);

        // QTreeWidget* treeWidget = new QTreeWidget(this);
        // treeWidget->setColumnCount(3);
        // QStringList list;
        // list << "f1" << "f2" << "f3";
        // treeWidget->setHeaderLabels(list);
    }
};

#endif // TEST12

#ifdef TEST13

#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <array>
#include <iostream>

class MyOGL : public QOpenGLWidget
{
public:
    void SetBackgroundColor()
    {
        std::cout << "set background color\n";
    }
};

class CustomDockWidget : public QDockWidget
{
    Q_OBJECT;

    // Q_PROPERTY(bool MyProperty READ Test_Q_PROPERTY NOTIFY sigFocus);
public:
    explicit CustomDockWidget(QWidget* parent = nullptr)
        : QDockWidget(parent)
    {
        // 自定义QDockWidget标题栏
        //-------------------------------------------
        auto combobox = new QComboBox();
        combobox->setMinimumSize(50, 30);
        // combobox->addItem("111");
        // combobox->addItem("222");
        // combobox->addItem("333");
        // combobox->addItem("444");

        m_titleWidget = new QWidget();
        auto layout = new QHBoxLayout();
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(combobox);
        // layout->addWidget(new QPushButton("aaa"));
        // layout->addWidget(new QPushButton("bbb"));
        layout->addSpacerItem(new QSpacerItem(100, 30, QSizePolicy::Expanding, QSizePolicy::Minimum));

        m_titleWidget->setObjectName("MyDockWidget");
        m_titleWidget->setStyleSheet("QWidget#MyDockWidget{background-color:red;}");
        m_titleWidget->setLayout(layout);
        m_titleWidget->setMinimumSize(80, 30);

        this->setTitleBarWidget(m_titleWidget);
        // this->setTitleBarWidget(new QPushButton("Button"));
        //--------------------------------------------------
    }

    ~CustomDockWidget()
    {
        std::cout << "destroy\n";
    }

public:
    void SetTitleWidget()
    {
        m_titleWidget->setStyleSheet("QWidget#MyDockWidget{background-color:red;}");
    }

signals:
    // Q_SIGNALS:
    void sigMyFocus();

private slots:
    void OnTopLevelChanged(bool topLevel)
    {
        std::cout << this->parentWidget()->width() << ',' << this->parentWidget()->height() << std::endl;
        if (topLevel)
        {
            // resize的参数不能大于父窗口
            this->resize(this->parentWidget()->width() / 2, this->parentWidget()->height() / 2); // 修复从选项卡切换到多窗口显示报错:unable to set geometry
        }

        // std::cout << "floating changed\t" << topLevel << std::endl;
    }

protected:
    // 为QDockWidget添加最大化、最小化、关闭按钮
    bool event(QEvent* event) override
    {
        // 打印事件类型
        static int index = 0;
        std::cout << index++ << "event\t";
        QMetaEnum eventEnum = QMetaEnum::fromType<QEvent::Type>();
        std::cout << eventEnum.valueToKey(event->type()) << '\n';

        if (event->type() == QEvent::Type::MouseButtonPress || event->type() == QEvent::Type::MouseButtonRelease)
        {
            m_titleWidget->setStyleSheet("QWidget#MyDockWidget{background-color:green;}");
            emit sigMyFocus();
        }

        return QDockWidget::event(event);
    }

    // 点击关闭按钮后不关闭QDockWidget，将浮动窗口嵌入到mainWindow
    void closeEvent(QCloseEvent* evt) override
    {
        if (this->isFloating())
        {
            this->setFloating(false);
            // QEvent* e = new QEvent(QEvent::ZOrderChange);
            // QApplication::sendEvent(this, e);
            evt->ignore();
        }
        // return QDockWidget::closeEvent(evt);
    }

private:
    QWidget* m_titleWidget { nullptr };
};

class Viewport : public QMainWindow
{
    Q_OBJECT
public:
    explicit Viewport(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        // 中间窗体默认为 nullptr
        QWidget* centralWidget = takeCentralWidget();

        // this->tabifiedDockWidgets

        // 开启该属性后，viewer1和viewer2原本只能水平布局，现在可以想怎样布局就怎样布局
        this->setDockNestingEnabled(true); // 设置嵌套布局为true，默认为false

        m_dockWidgets[0] = new CustomDockWidget();
        connect(m_dockWidgets[0], &CustomDockWidget::sigMyFocus, [this]() { this->PickDock(0); });
        MyOGL* oglWidget0 = new MyOGL();
        m_dockWidgets[0]->setWidget(oglWidget0);
        m_dockWidgets[0]->setWindowTitle("viewer 1");
        m_dockWidgets[0]->setFeatures(m_dockWidgets[0]->features() & ~QDockWidget::DockWidgetClosable);

        m_dockWidgets[1] = new CustomDockWidget();
        connect(m_dockWidgets[1], &CustomDockWidget::sigMyFocus, [this]() { this->PickDock(1); });
        MyOGL* oglWidget1 = new MyOGL();
        m_dockWidgets[1]->setWidget(oglWidget1);
        m_dockWidgets[1]->setWindowTitle("viewer 2");
        m_dockWidgets[1]->setFeatures(m_dockWidgets[1]->features() & ~QDockWidget::DockWidgetClosable);

        m_dockWidgets[2] = new CustomDockWidget();
        connect(m_dockWidgets[2], &CustomDockWidget::sigMyFocus, [this]() { this->PickDock(2); });
        MyOGL* oglWidget2 = new MyOGL();
        m_dockWidgets[2]->setWidget(oglWidget2);
        m_dockWidgets[2]->setWindowTitle("viewer 3");
        m_dockWidgets[2]->setFeatures(m_dockWidgets[2]->features() & ~QDockWidget::DockWidgetClosable);

        m_dockWidgets[3] = new CustomDockWidget();
        connect(m_dockWidgets[3], &CustomDockWidget::sigMyFocus, [this]() { this->PickDock(3); });
        MyOGL* oglWidget3 = new MyOGL();
        m_dockWidgets[3]->setWidget(oglWidget3);
        m_dockWidgets[3]->setWindowTitle("viewer 4");
        m_dockWidgets[3]->setFeatures(m_dockWidgets[3]->features() & ~QDockWidget::DockWidgetClosable);

        this->addDockWidget(Qt::TopDockWidgetArea, m_dockWidgets[0]);
        this->addDockWidget(Qt::TopDockWidgetArea, m_dockWidgets[1]);
        this->addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[2]);
        this->addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgets[3]);

        // 禁止标签页方式停靠
        // this->setDockOptions(this->dockOptions() & ~DockOption::AllowTabbedDocks);

        // m_dockWidgets[1]->hide();
        // m_dockWidgets[2]->hide();
        // m_dockWidgets[3]->hide();
    }

    bool event(QEvent* event) override
    {
        // 屏蔽右键qdockwidget标题栏时，弹出菜单
        if (event->type() == QEvent::ContextMenu)
        {
            return false;
        }

        return QMainWindow::event(event);
    }
public slots:
    void SetViewport(int i)
    {
        auto dockWidth = static_cast<int>(this->geometry().width() * 0.5);
        auto dockHeight = static_cast<int>(this->geometry().height() * 0.5);

        // 将所有悬浮的窗口复位
        std::for_each(m_dockWidgets.begin(), m_dockWidgets.end(), [](QDockWidget* dock) {
                if (dock->isFloating())
                {
                    dock->setFloating(false);
                } });

        switch (i)
        {
        case 1:
        {
            m_dockWidgets[1]->hide();
            m_dockWidgets[2]->hide();
            m_dockWidgets[3]->hide();
        }
        break;
        case 2:
        { // 左1右1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->hide();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
        }
        break;
        case 3:
        { // 上1下1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->hide();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        case 4:
        { // 上1下2
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[1], m_dockWidgets[2], Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[1], m_dockWidgets[2] }, { dockWidth, dockWidth }, Qt::Horizontal);
        }
        break;
        case 5:
        { // 上2下1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
        }
        break;
        case 6:
        { // 左2右1
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        case 7:
        { // 4
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->show();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[2], m_dockWidgets[3], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[1], m_dockWidgets[3], Qt::Vertical);

            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[2], m_dockWidgets[3] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[1], m_dockWidgets[3] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        case 8:
        { // 左1右2
            m_dockWidgets[1]->show();
            m_dockWidgets[2]->show();
            m_dockWidgets[3]->hide();

            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[1], Qt::Horizontal);
            this->splitDockWidget(m_dockWidgets[0], m_dockWidgets[2], Qt::Vertical);
            this->splitDockWidget(m_dockWidgets[1], m_dockWidgets[2], Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[1] }, { dockWidth, dockWidth }, Qt::Horizontal);
            this->resizeDocks({ m_dockWidgets[0], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
            this->resizeDocks({ m_dockWidgets[1], m_dockWidgets[2] }, { dockHeight, dockHeight }, Qt::Vertical);
        }
        break;
        default:
            break;
        }

        m_viewportMode = i;
    }

    void PrintDockInfo()
    {
        std::cout << std::boolalpha << "   === Dock Infomation ===\n";
        for (size_t i = 0; i < 4; i++)
        {
            // 注意isHidden和isVisible的区别
            std::cout << std::endl
                      << i << i << i << std::endl;
            // std::cout << "\t area:" << m_dockWidgets[0]->allowedAreas() << '\n';
            std::cout << "\t show:" << !m_dockWidgets[i]->isHidden() << '\n';
            std::cout << "\t float:" << m_dockWidgets[i]->isFloating() << '\n';
            std::cout << "\t visible:" << m_dockWidgets[i]->isVisible() << '\n';
            std::cout << "\t width:" << m_dockWidgets[i]->width() << '\n';
            std::cout << "\t height:" << m_dockWidgets[i]->height() << '\n';
        }
    }

    void DontFloat()
    {
        for (size_t i = 0; i < 4; i++)
        {
            // 将悬浮的QDockWidget放入QMainWindow
            m_dockWidgets[i]->setFloating(false);
        }
    }

    void PickDock(int x)
    {
        std::cout << "pick dock:\t" << x << '\n';

        switch (x)
        {
        case 0:
            m_dockWidgets[1]->SetTitleWidget();
            m_dockWidgets[2]->SetTitleWidget();
            m_dockWidgets[3]->SetTitleWidget();
            break;
        case 1:
            m_dockWidgets[0]->SetTitleWidget();
            m_dockWidgets[2]->SetTitleWidget();
            m_dockWidgets[3]->SetTitleWidget();
            break;
        case 2:
            m_dockWidgets[0]->SetTitleWidget();
            m_dockWidgets[1]->SetTitleWidget();
            m_dockWidgets[3]->SetTitleWidget();
            break;
        case 3:
            m_dockWidgets[1]->SetTitleWidget();
            m_dockWidgets[2]->SetTitleWidget();
            m_dockWidgets[0]->SetTitleWidget();
            break;
        default:
            break;
        }
    }

private:
    std::array<CustomDockWidget*, 4> m_dockWidgets;
    int m_viewportMode { 1 };
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget* parent = nullptr)
        : QWidget(parent)
        , m_viewport(new Viewport())
    {
        auto mode1 = new QAction();
        auto mode2 = new QAction();
        auto mode3 = new QAction();
        auto mode4 = new QAction();
        auto mode5 = new QAction();
        auto mode6 = new QAction();
        auto mode7 = new QAction();
        mode1->setIcon(QIcon("resource/posX.svg"));
        mode2->setIcon(QIcon("resource/threeWindows.svg"));
        mode3->setIcon(QIcon("resource/posX.svg"));
        mode4->setIcon(QIcon("resource/posX.svg"));
        mode5->setIcon(QIcon("resource/posX.svg"));
        mode6->setIcon(QIcon("resource/posX.svg"));
        mode7->setIcon(QIcon("resource/posX.svg"));
        connect(mode1, &QAction::triggered, [this]() { m_viewport->SetViewport(1); });
        connect(mode2, &QAction::triggered, [this]() { m_viewport->SetViewport(2); });
        connect(mode3, &QAction::triggered, [this]() { m_viewport->SetViewport(3); });
        connect(mode4, &QAction::triggered, [this]() { m_viewport->SetViewport(4); });
        connect(mode5, &QAction::triggered, [this]() { m_viewport->SetViewport(5); });
        connect(mode6, &QAction::triggered, [this]() { m_viewport->SetViewport(6); });
        connect(mode7, &QAction::triggered, [this]() { m_viewport->SetViewport(7); });

        // 设置Viewport
        auto viewport = new QToolButton();
        viewport->setIcon(QIcon("resource/expand.svg"));
        viewport->setPopupMode(QToolButton::InstantPopup);
        viewport->addAction(mode1);
        viewport->addAction(mode2);
        viewport->addAction(mode3);
        viewport->addAction(mode4);
        viewport->addAction(mode5);
        viewport->addAction(mode6);
        viewport->addAction(mode7);

        QPushButton* btnPrint = new QPushButton();
        QPushButton* btnRestore = new QPushButton();
        btnPrint->setIcon(QIcon("resource/posX.svg"));
        btnRestore->setIcon(QIcon("resource/posX.svg"));
        connect(btnPrint, SIGNAL(clicked()), m_viewport, SLOT(PrintDockInfo()));
        connect(btnRestore, SIGNAL(clicked()), m_viewport, SLOT(DontFloat()));

        QHBoxLayout* hBtnLayout = new QHBoxLayout(); // 按钮布局
        hBtnLayout->addWidget(viewport);
        hBtnLayout->addWidget(btnPrint);
        hBtnLayout->addWidget(btnRestore);
        hBtnLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

        QVBoxLayout* vMainLayout = new QVBoxLayout(); // 整个窗口布局
        vMainLayout->addLayout(hBtnLayout);
        vMainLayout->addWidget(m_viewport);

        this->setLayout(vMainLayout);
    }

private:
    Viewport* m_viewport { nullptr };
};

#endif // TEST13

#ifdef TEST14

#include <QDebug>
#include <QEvent>
#include <QMetaEnum>
#include <QObject>
#include <QWidget>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject* parent = nullptr) {};
    ~MyClass() {};

    // 自定义枚举必须继承自QObject，且必须使用Q_OBJECT，还必须使用Q_ENUM()或者Q_FLAG()才可以使用QMetaEnum
    enum Color
    {
        Red,
        Orange,
        Yellow,
        Green
    };
    Q_ENUM(Color)
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
    {
        QMetaEnum colorEnum = QMetaEnum::fromType<MyClass::Color>();

        qDebug() << colorEnum.name() << colorEnum.enumName() << colorEnum.scope();

        qDebug() << "----------------";

        // 打印自定义枚举字符串
        for (int ii = 0; ii < colorEnum.keyCount(); ++ii)
        {
            int val = colorEnum.value(ii);
            qDebug() << colorEnum.key(ii) << val << colorEnum.valueToKey(val);
        }

        qDebug() << "---------------";
    }
    ~Widget() {};

    bool event(QEvent* event) override
    {
        // 打印Qt枚举字符串
        QMetaEnum eventEnum = QMetaEnum::fromType<QEvent::Type>();
        const char* s = eventEnum.valueToKey(event->type());
        qDebug() << s;

        return QWidget::event(event);
    }
};

#endif // TEST14

#ifdef TEST15

// https://blog.csdn.net/GoForwardToStep/article/details/53494800

#include <QBoxLayout>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QWidget>

constexpr int cBtnWidth = 30;
constexpr int cBtnHeight = 30;
constexpr int cTitleHeight = 30;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    TitleBar(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        this->setStyleSheet("background-color: rgb(0,127,0);");

        // 标题栏（其实就是窗口最上边）添加自定义部件
        QMenuBar* menuBar = new QMenuBar(this);
        QMenu* menu = menuBar->addMenu("AAA");
        menu->addAction("111");
        menu->addAction("222");
        // menuBar->move(0, 0);
        menuBar->setFixedSize(cBtnWidth, cBtnHeight);

        QComboBox* comboBox = new QComboBox();
        comboBox->setFixedSize(100, cBtnHeight);
        comboBox->addItem("aaa");
        comboBox->addItem("bbb");
        comboBox->addItem("ccc");
        comboBox->addItem("ddd");

        m_btnMax = new QPushButton();
        m_btnMin = new QPushButton();
        m_btnClose = new QPushButton();
        m_btnRestore = new QPushButton();

        m_btnMax->setFixedSize(QSize(cBtnWidth, cBtnHeight));
        m_btnMin->setFixedSize(QSize(cBtnWidth, cBtnHeight));
        m_btnClose->setFixedSize(QSize(cBtnWidth, cBtnHeight));
        m_btnRestore->setFixedSize(QSize(cBtnWidth, cBtnHeight));

        m_btnMax->setToolTip(QStringLiteral("最大化"));
        m_btnMin->setToolTip(QStringLiteral("最小化"));
        m_btnClose->setToolTip(QStringLiteral("关闭"));
        m_btnRestore->setToolTip(QStringLiteral("还原"));

        QSpacerItem* spacerItem = new QSpacerItem(500, cBtnHeight);

        QHBoxLayout* hBoxLayout = new QHBoxLayout(this);
        // hBoxLayout->addWidget(menuBar);
        hBoxLayout->addWidget(comboBox);
        hBoxLayout->addItem(spacerItem);
        hBoxLayout->addWidget(m_btnMin);
        hBoxLayout->addWidget(m_btnMax);
        hBoxLayout->addWidget(m_btnRestore);
        hBoxLayout->addWidget(m_btnClose);

        hBoxLayout->setContentsMargins(5, 0, 0, 0);
        hBoxLayout->setSpacing(0);

        this->setFixedHeight(cTitleHeight);
        this->setWindowFlags(Qt::FramelessWindowHint);
    }
    ~TitleBar()
    {
    }

private:
    QPushButton* m_btnMin;
    QPushButton* m_btnMax;
    QPushButton* m_btnClose;
    QPushButton* m_btnRestore;
};

class Widget : public QWidget
{
public:
    Widget()
    {
        // FramelessWindowHint属性设置窗口去除边框;
        // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        // 设置窗口背景透明;
        // setAttribute(Qt::WA_TranslucentBackground);

        // 注意！！！如果是主窗口不要设置WA_DeleteOnClose属性;
        // 关闭窗口时释放资源;
        setAttribute(Qt::WA_DeleteOnClose);

        TitleBar* titleBar = new TitleBar(this);
        titleBar->move(0, 0);
    }
    ~Widget() { }
};

#endif // TEST15

#ifdef TEST16

#include <QtOpenGLWidgets>
#include <QtWidgets>

#include <iostream>

class tabBarEventFilter : public QObject
{
public:
    bool eventFilter(QObject* w, QEvent* e)
    {
        if (e->type() == QEvent::MouseButtonPress)
        {
            std::cout << "tabBar press\n";
            // return true; // 不再进行处理
        }
        return false;
    }
};

class MyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    MyTabWidget(QWidget* p = nullptr)
        : QTabWidget(p)
    {
        this->setMovable(true);
        this->setAcceptDrops(true);

        // 给TabBar安装一个事件钩子
        QObject* eventFilter = new tabBarEventFilter();
        this->tabBar()->installEventFilter(eventFilter);
    }

public slots:
    void RemoveFirstTab()
    {

        std::cout << "window\t" << this->count() << '\t' << this->widget(0)->objectName().toStdString() << '\n';

        // QWidget* www = new QWidget();
        // www->resize(100, 100);
        ////memcpy(www, this->widget(0), sizeof(QWidget));
        // www->show();
        // this->widget(0)->hide();

        // QWidget* w = new QWidget();
        // QGridLayout* layout = new QGridLayout();
        // layout->addWidget(this->widget(0));
        // w->setLayout(layout);
        // w->resize(300, 200);
        // w->show();

        // 移除索引为零的选项卡
        this->removeTab(0);
    }
    void AddTab()
    {
        static int index = 0;
        this->addTab(new QOpenGLWidget(), "New_" + QString::number(index++));
    }
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget()
        : tabWidget(new MyTabWidget())
        , stackedWidget(new QStackedWidget())
    {
        // 用来放置toolbar
        QMainWindow* toolMainWindow = new QMainWindow();
        toolMainWindow->setCentralWidget(stackedWidget);

        QGridLayout* gridLayout = new QGridLayout();
        this->setLayout(gridLayout);
        gridLayout->addWidget(toolMainWindow);

        std::cout << this->contentsMargins().left() << '\t' << this->contentsMargins().top() << '\t'
                  << this->contentsMargins().right() << '\t' << this->contentsMargins().bottom() << '\n';
        int a = 0, b = 0, c = 0, d = 0;
        // gridLayout->getContentsMargins(&a, &b, &c, &d);
        std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

        // 用来切换截图和渲染窗口
        stackedWidget->addWidget(tabWidget);
        stackedWidget->addWidget(new QWidget());
        stackedWidget->setCurrentWidget(tabWidget);

        QToolBar* toolBar1 = new QToolBar("Tool 1", toolMainWindow);
        QToolBar* toolBar2 = new QToolBar("Tool 2", toolMainWindow);

        QAction* removeTabAct = new QAction("remove");
        QAction* addTabAct = new QAction("add");
        QAction* testAct1 = new QAction("test1");
        QAction* testAct2 = new QAction("test2");

        connect(removeTabAct, &QAction::triggered, [this]() { this->tabWidget->RemoveFirstTab(); });
        connect(addTabAct, &QAction::triggered, [this]() { this->tabWidget->AddTab(); });
        connect(testAct1, &QAction::triggered, [this]() { this->stackedWidget->setCurrentIndex(this->stackedWidget->currentIndex() == 0 ? 1 : 0); });
        connect(testAct2, &QAction::triggered, [this]() { std::cout << "count:" << this->tabWidget->count() << "\tindex:" << this->tabWidget->currentIndex() << '\n'; });

        toolBar1->addAction(removeTabAct);
        toolBar1->addAction(addTabAct);
        toolBar1->addAction(testAct1);
        toolBar1->addAction(testAct2);

        toolBar1->addAction(QIcon("resource/expand.svg"), "111");
        toolBar2->addAction(QIcon("resource/undo.svg"), "222");
        // 第二个参数就是tooltip
        auto act1 = toolBar1->addAction(QIcon("resource/undo.svg"), "test", []() { std::cout << "test\n"; });
        std::cout << "tool tip\t" << act1->toolTip().toStdString() << '\n';

        toolMainWindow->addToolBar(toolBar1);
        toolMainWindow->addToolBar(toolBar2);

        // 用来放置dockwidget
        QMainWindow* tabMainWindow1 = new QMainWindow();
        tabMainWindow1->setObjectName("123456");

        // 每个tab可以添加QDockWidget
        QDockWidget* dock1_1 = new QDockWidget();
        dock1_1->setWidget(new QOpenGLWidget());
        QDockWidget* dock1_2 = new QDockWidget();
        dock1_2->setWidget(new QOpenGLWidget());

        tabMainWindow1->addDockWidget(Qt::TopDockWidgetArea, dock1_1);
        tabMainWindow1->addDockWidget(Qt::BottomDockWidgetArea, dock1_2);

        // 添加多个tabwidget
        tabWidget->addTab(tabMainWindow1, "AAA");
        tabWidget->addTab(new QOpenGLWidget(), "BBB");
        tabWidget->addTab(new QOpenGLWidget(), "CCC");

        // 需要将QTabWidget放在布局中，或者设置大小
        // 或者在QMainWindow->setCentralWidget(tab)不然不会显示
        // tabWidget->setMinimumSize(600, 400);
    }

private:
    MyTabWidget* tabWidget;
    QStackedWidget* stackedWidget;
};

#endif // TEST16

#ifdef TEST17

#include <QBoxLayout>
#include <QEvent>
#include <QPushButton>
#include <QWidget>

#include <iostream>

class MyPushButton : public QPushButton
{
public:
    MyPushButton(QWidget* parent = nullptr) { }
    ~MyPushButton() { }

    bool event(QEvent* evt) override
    {
        // 自定义的按钮置灰以后，还可以响应事件，但是不能响应clicked事件
        if (this->isEnabled())
        {
            std::cout << "is enabled\n";
        }
        else
        {
            std::cout << "is not enabled\n";
        }

        switch (evt->type())
        {
        case QEvent::MouseButtonRelease:
            std::cout << "button release\n";
            break;
        default:
            break;
        }

        return QPushButton::event(evt);
    }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
    {
        QPushButton* btn1 = new QPushButton();
        btn1->setEnabled(false);
        connect(btn1, &QPushButton::clicked, []() { std::cout << "clicked button 1\n"; });

        QPushButton* btn2 = new QPushButton();
        btn2->setEnabled(true);
        connect(btn2, &QPushButton::clicked, []() { std::cout << "clicked button 2\n"; });

        MyPushButton* btn3 = new MyPushButton();
        btn3->setEnabled(false);
        // 置灰后不能响应
        connect(btn3, &QPushButton::clicked, []() { std::cout << "clicked button 3\n"; });

        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(btn1);
        layout->addWidget(btn2);
        layout->addWidget(btn3);

        this->setLayout(layout);
    }
    ~Widget() { }
};

#endif // TEST17

#ifdef TEST18

#include <QBoxLayout>
#include <QDebug>
#include <QDialog>
#include <QPushButton>
#include <QWidget>

class MyDialog : public QDialog
{
public:
    explicit MyDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
        qDebug() << "MyDialog";
        this->setWindowTitle("MyDialog");
        this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
        this->setMinimumSize(400, 300);

        auto layout = new QVBoxLayout();
        this->setLayout(layout);

        {
            auto testDialog = new QPushButton("Test Accept");
            connect(testDialog, &QPushButton::clicked, [this]() mutable {
                this->accept();
                qDebug() << "clicked accept";
            });
            layout->addWidget(testDialog);
        }

        {
            auto testDialog = new QPushButton("Test Reject");
            connect(testDialog, &QPushButton::clicked, [this]() mutable {
                this->reject();
                qDebug() << "clicked reject";
            });
            layout->addWidget(testDialog);
        }

        {
            auto testDialog = new QPushButton("Test Done");
            connect(testDialog, &QPushButton::clicked, [this]() mutable {
                this->done(1);
                qDebug() << "clicked done";
            });
            layout->addWidget(testDialog);
        }
    }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr)
    {
        auto openDialog = new QPushButton("open Dialog");
        connect(openDialog, &QPushButton::clicked, []() {
            qDebug() << "----------------------------------------------------\nclicked button";

            auto dialog = new MyDialog();

            qDebug() << "dialog exec begin";

            if (dialog->exec() == QDialog::Accepted)
            {
                qDebug() << "--- dialog accepted ---";
            }

            qDebug() << "dialog exec end";
        });

        auto layout = new QVBoxLayout();
        layout->addWidget(openDialog);
        this->setLayout(layout);
    }
    ~Widget() = default;
};

#endif // TEST18
