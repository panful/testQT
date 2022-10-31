/*
* 0.自定义信号和槽
* 1.QJson
* 2.QJson QVariant QString 互相转换
* 3.QPointer
* 4.槽函数使用lambda
* 5.QVariant
* 6.QClipboard剪贴板
* 7.QVarLengthArray
* 8.序列化与反序列化
* 9.正则表达式
* 10 Qt调用js脚本正则表达式匹配中文
*/

#define TEST10

#ifdef TEST0

#include "mockQt.h"

int main()
{
    MockQt mock;
    mock.TestFunc(0);
    mock.TestFunc(1);
    mock.TestFunc(2);

    return 0;
}

#endif // TEST0

#ifdef TEST1

#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVarLengthArray>
#include <QDebug>

int main()
{
    QVariantMap m;
    QVariantList l;
    l.insert(2, 99);
    l.insert(3, 88);
    l.insert(3, 77);
    m.insert("1", 1);
    m.insert("2", 2);
    m.insert("3", 3);
    m.insert("2", 5);

    m["4"] = 4;
    m["3"] = 6;

    auto json = QJsonDocument::QJsonDocument(QVariant(m).toJsonObject()).toJson(); //QVariantMap转为json
    auto str = QString(json); //json转为QString字符串


    //QJsonArray ja;
    //QJsonDocument jd;
    //QJsonObject jo;
    //QJsonValue jv;
    //QJsonPrivate //命名空间

    //QByteArray ba;
    //QByteArrayList bal;
    //QByteArrayData bad;
    //QVarLengthArray<int> vla;

    QVariantList people;

    QVariantMap bob;
    bob.insert("Name", "Bob");
    bob.insert("Phonenumber", 123);

    QVariantMap alice;
    alice.insert("Name", "Alice");
    alice.insert("Phonenumber", 321);

    people << bob << alice;

    auto json2 = QJsonDocument::QJsonDocument(QVariant(people).toJsonObject()).toJson();

    //QJson::Serializer serializer;
    //QByteArray json = serializer.serialize(people);

    qDebug() << json;




    //--
    QJsonObject object
    {
        {"error",QString::fromStdString("std string")}
    };

    auto json3 = QJsonDocument::fromJson((object));

    //QJsonDocument jsonDoc1 = QJsonDocument::fromJson(QByteArray());
    //QJsonDocument jsonDoc2 = QJsonDocument::fromVariant(QVariant());
    //QJsonDocument jsonDoc3 = QJsonDocument::fromBinaryData(QByteArray());

    //QString str1 = object["str"].toString();

    //QVariantMap vmap1 = object.toVariantMap();

    //--

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>

int main()
{
    // QString 转 QJsonDocument
    QString str1 = "{\"key1\":{\"key2\":8888}}";
    QByteArray jsonData1;
    QJsonDocument jsonDoc1 = QJsonDocument::fromJson(jsonData1.append("{\"key1\":{\"key2\":8888}}"));
    //QJsonDocument jsonDoc1 = QJsonDocument::fromJson(jsonData1.append(str1)); //Qt6不支持
    // QJsonDocument 转 QJsonObject
    QJsonObject obj1 = jsonDoc1.object();
    // 获取QJsonObject的value
    QString key = obj1.keys().at(0);
    QJsonValue value = obj1.value(key);
    // QJsonValue 转 QJsonObject
    QJsonObject ret1 = value.toObject();
    // 获取QJsonObject的value
    QString key2 = ret1.keys().at(0);
    // QVariantMap 转 QJsonDocument
    QVariantMap var1;
    var1.insert("key1", 111);
    var1.insert("key2", 222);
    QJsonDocument jsonDoc2 = QJsonDocument::fromVariant(QVariant(var1));
    QJsonDocument jsonDoc3 = QJsonDocument::QJsonDocument(QVariant(var1).toJsonObject());
    // QVariantMap 转 QString
    QByteArray byte1 = QJsonDocument::QJsonDocument(QVariant(var1).toJsonObject()).toJson();
    QString str2 = byte1;
    // QVariantMap 转 QJsonObject
    QJsonObject obj2 = QVariant(var1).toJsonObject();
    QJsonObject obj3 = QJsonObject(QJsonDocument::fromJson(QJsonDocument::fromVariant(QVariant(var1)).toJson()).object());
    // QJsonObject 转 QVariantMap
    QVariantMap map1 = obj2.toVariantMap();

    qDebug() << "test\n";
    return 0;
}


#endif // TEST2

#ifdef TEST3

#include <QPointer>
#include <iostream>

class Test
{
public:
    Test() { std::cout << "construct\n"; }
    ~Test() { std::cout << "deconstruct\n"; }
};

int main()
{
    std::cout << " === test\n";
    {
        QPointer<Test> t = QPointer<Test>::QPointer();
    }
}



#endif // TEST3

#ifdef TEST4


//connect(send, SIGNAL(triggered()), receive, SLOT(func()));
//connect(send, &QAction::triggered, receive, [this]() {std::cout << "sss\n"; });  // receive如果是this，可写可不写
//connect(send, SIGNAL(triggered()), receive, [this]() {std::cout << "sss\n"; });  // 不能这样使用


int main()
{}

#endif // TEST4

#ifdef TEST5

#include <iostream>
#include <QVariant>
#include <QDebug>
#include <vector>
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(int*)
int main()
{
    std::string str = "test";
    QVariant v1 = 12;
    QVariant v2; v2.setValue(str); //非Qt(C++)内置类型必须用setValue赋值
    //QVariant v2 = "test";  //此时的v2只能转为QString，不能直接转为std::string
    QVariant v3;
    v3.setValue(2.0f);
    auto val1 = v3.value<float>();
    auto val2 = v3.toFloat();

    bool can1 = v2.canConvert<float>();      //false
    bool can2 = v2.canConvert<std::string>();//true
    bool can3 = v2.canConvert<int>();        //false
    bool can4 = v2.canConvert<QString>();    //false

    auto val3 = v2.value<std::string>();

    int arr[]{ 1,2,3 };
    //保存
    QVariant varP = QVariant::fromValue((void*)arr);
    //获取
    int* r1 = (int*)varP.value<void*>();

    QVariant v4; v4.setValue(r1); //此处不能用arr
    auto* r2 = v4.value<int*>();

    std::vector<QVariant> vecVar{ v1,v2,v3,v4 };
    auto ret = vecVar.front().value<float>();

    qDebug("test");
    return 0;
}

#endif // TEST5

#ifdef TEST6

#include <QApplication>
#include <QClipboard>
#include <QImage>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    auto clipBoard = QApplication::clipboard();
    //clipBoard->setText("test clip board 2");

    unsigned char pixels[] = {
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
        255,0,0,255,
    };
    QImage image = QImage(pixels, 3, 3, QImage::Format_RGBA8888);
    clipBoard->setImage(image);

    return 0;
}

#endif // TEST6

#ifdef TEST7

#include <QVarLengthArray>

int main()
{
    QVarLengthArray<int> var1;
    QVarLengthArray<int, 10> var2;

    var1.push_back(1);
    var1.push_back(2);
    var1.push_back(3);

    var2.push_back(33);
    var2.append(22);
    auto size = var2.size();
    auto empty = var2.empty();
    auto data = var2.data();

    qDebug("test");
}

#endif // TEST7

#ifdef TEST8

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>

#include <cstring>

int main(int argc,char** argv)
{

    // 定义整形值（数据类型可按自己意向更改）
    int val = 666;
    // 创建一个数据流对象，并设置数据容器和打开方式
    QByteArray* byteArray = new QByteArray();
    QDataStream stream1(byteArray, QIODevice::WriteOnly);
    // 通过'<<'运算符将数据写入
    stream1 << val;
    auto len = strlen(byteArray->data());

    // 创建一个数据流对象，并设置数据容器和打开方式
    QDataStream stream2(byteArray, QIODevice::ReadOnly);
    // 创建序列化值所对应的类型变量（如本类型转换前类型为int，接收类型也应与之对应）
    int ret = 0;   // 初始化是和序列化值区分
    // 通过'>>'运算符将数据从流中读出
    stream2 >> ret;

    int a = 9, b = 8, c = 7;
    QByteArray* b1 = new QByteArray();
    QDataStream s3(b1, QIODevice::WriteOnly);
    s3.writeBytes(reinterpret_cast<char*>(&a), 4);
    auto buf1 = b1->data();
    auto len1 = strlen(buf1);
    auto ret1 = reinterpret_cast<int*>(buf1);

    int test = 0;
}


#endif // TEST8

#ifdef TEST9

#include <QCoreApplication>
#include <QDebug>
#include <QRegExp>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

// cmake -> Core5Compat

int main(int argc, char* argv[])
{
#define PrintResult(str) qDebug() << "Before:\t" << str;qDebug() << "After:\t" << str.replace(reg1, "image:url(./resource/newSvgFile.svg);");qDebug()<<"--------";
    // 替换
    {
        QString r = "image:url(.*);";
        QString s = "{image:url(./resource/test.svg);}this is a svg file.";
        QString s1 = "{image:url();}this is a svg file.";
        QString s2 = "{image:url(******);}this is a svg file.";
        QString s3 = "{image:url((******);}))this is a svg file.";

        QRegularExpression reg1(r);

        PrintResult(s);
        PrintResult(s1);
        PrintResult(s2);
        PrintResult(s3);

    }

    return 0;
}

#endif // TEST9

#ifdef TEST10

#include <QtCore/QCoreApplication>
#include <QJSEngine>  // cmake Qml
#include <QDebug>
#include <QFile>
#include <QTextStream>

using namespace std;

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QJSEngine js;
    QJSValue module = js.importModule("resource/math.mjs");
    QJSValue sumFunction = module.property("sum");
    QString str = "38u48djhfod中国，@##@!_)+bia發財";
    QJSValueList args;
    args << str;
    QJSValue result = sumFunction.call(args);
    if (result.isError())
    {
        qDebug() << result.toString();
        return -1;
    }
    qDebug() << result.toBool();
    return a.exec();
}
#endif // TEST10
