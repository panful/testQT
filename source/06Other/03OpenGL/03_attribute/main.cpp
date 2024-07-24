/*
* 1.
*/

#define TEST1

#ifdef TEST1

// Qt5中编译参数"-opengl desktop"、'-no-angle'的作用 https://bbs.csdn.net/topics/394475398
// 设置Qt程序属性 https://blog.csdn.net/a15005784320/article/details/114155629
// OpenGLES ANGLE 学习 https://www.ewbang.com/community/article/details/961160176.html

/*
对于desktop / native，可以将环境变量QT_OPENGL设置为desktop或将应用程序属性设置为Qt::AA_UseDesktopOpenGL
对于ANGLE，可以将环境变量QT_OPENGL设置为angle或将应用程序属性设置为Qt::AA_UseOpenGLES
对于软件渲染，将环境变量QT_OPENGL设置为software或将应用程序属性设置为Qt::AA_UseSoftwareOpenGL

使用configure选项创建Qt的静态构建来设置你想要的OpenGL的实现（但要注意Qt许可规则 ）

对于桌面/本机，请包含 - opengl desktop
对于ANGLE， 不要包含 - opengl选项; 那是因为它是默认的
还有让Qt选择最佳选择的 - opengl dynamic 。 这是在Qt 5.4中引入的。 如果你想要这个选项，但不需要任何其他原因的静态构建，则不需要创建静态构建，因为预编译的二进制文件自Qt 5.5以来使用此选项。
*/
#include <QApplication>
#include <QWidget>
#include <QDebug>

int main(int argc,char** argv)
{
    //qputenv("QT_OPENGL", "angle");
    //qputenv("Path", "C:/Qt/6.2.2/msvc2019_64/bin");

    //QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    //QApplication::setAttribute(Qt::AA_UseOpenGLES);

    QApplication app(argc, argv);

    //QWidget* w = new QWidget();
    //w->setAttribute(Qt::WA_RightToLeft);

    return app.exec();
}

#endif // TEST1



