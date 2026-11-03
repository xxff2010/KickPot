#pragma once

#include <QWidget>

class QComboBox;
class QLabel;

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

private slots:
    void retranslate();

private:
    QLabel *m_title = nullptr;
    QLabel *m_languageTitle = nullptr;
    QLabel *m_languageDesc = nullptr;
    QLabel *m_moreNote = nullptr;
    QComboBox *m_languageCombo = nullptr;
};
