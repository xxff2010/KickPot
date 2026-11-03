#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class StatCard;

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget *parent = nullptr);

signals:
    // Emitted when a quick-access button asks to open another page.
    void navigateRequested(int pageIndex);

private slots:
    void retranslate();

private:
    QLabel *m_title = nullptr;
    QLabel *m_subtitle = nullptr;
    QLabel *m_activityTitle = nullptr;
    QLabel *m_activityEmpty = nullptr;
    QLabel *m_quickTitle = nullptr;

    StatCard *m_connectionCard = nullptr;
    StatCard *m_channelCard = nullptr;
    StatCard *m_aiCard = nullptr;
    StatCard *m_messagesCard = nullptr;

    QPushButton *m_streamButton = nullptr;
    QPushButton *m_chatButton = nullptr;
    QPushButton *m_aiButton = nullptr;
};
