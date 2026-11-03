#pragma once

#include <QString>
#include <QWidget>

class QLabel;

// Temporary page for features that will be built in later phases.
class PlaceholderPage : public QWidget
{
    Q_OBJECT

public:
    // titleKey / descKey are keys from AppManager::text().
    PlaceholderPage(const char *titleKey, const char *descKey,
                    const QString &icon, QWidget *parent = nullptr);

private slots:
    void retranslate();

private:
    const char *m_titleKey;
    const char *m_descKey;

    QLabel *m_icon = nullptr;
    QLabel *m_title = nullptr;
    QLabel *m_description = nullptr;
    QLabel *m_badge = nullptr;
};
