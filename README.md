## 软件版本
| 软件名 | 版本    |
| --     |--      |
| VS     | 2022   |
| Windows|  11    |
| CMake  | 3.21.4 |
| Qt     | 6.2.2  |

## 环境变量设置
|环境变量名|值|
|--|--|
|QT_DIR|***\Qt\6.2.2\msvc2019_64\bin|
|path|***\Qt\6.2.2\msvc2019_64\bin|

## 01 Console
Qt控制台程序，用来测试不需要GUI的程序，例如QJson，QString等
## 02 QGui
Qt桌面应用程序，测试QtWidgets中最原始的Qt类，没有继承
## 03 QGui2
Qt桌面应用程序，继承自QtWidgets中的类，重写QMainWindow、QWidget等
## 04 QGui_UI
在QMainWindow中使用Qt设计师生成的UI文件
## 05 QQuick
测试QQuick、QML
## 06 QWidgetIntoQQuick
将QWidget嵌入到QQuick
## 07 QQuickIntoQWidget
将QQuick嵌入到QWidget
## 08 QtSocketServer
测试QSocket的服务端
## 09 QtSocketClient
测试QSocket的客户端
## 10 QDialog_UI
将QDialog放入ui文件
