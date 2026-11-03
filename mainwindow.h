#pragma once

#include <QList>
#include <QMainWindow>

class NavButton;
class QButtonGroup;
class QLabel;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void navigateTo(int pageIndex);
    void retranslateUi();

private:
    void buildUi();

    QStackedWidget *m_pages = nullptr;
    QButtonGroup *m_navGroup = nullptr;
    QList<NavButton *> m_navButtons;
    QLabel *m_versionLabel = nullptr;
};
