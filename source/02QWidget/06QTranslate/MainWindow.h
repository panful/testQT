#pragma once

#include <QMainWindow>

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QPushButton* m_button;
    QPushButton* m_englishButton;
    QPushButton* m_chineseButton;
};
