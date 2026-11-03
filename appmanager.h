#pragma once

#include <QObject>
#include <QString>

// Central place for application-wide state: language, settings, theme loading.
class AppManager : public QObject
{
    Q_OBJECT

public:
    enum class Language { English = 0, Arabic = 1 };

    static AppManager &instance();

    // Must be called once after QApplication is created.
    void initialize();

    Language language() const { return m_language; }
    void setLanguage(Language language);

    // Returns the UI text for the given key in the current language.
    QString text(const char *key) const;

    // Reads the dark theme stylesheet from the Qt resource system.
    static QString loadStyleSheet();

signals:
    void languageChanged();

private:
    explicit AppManager(QObject *parent = nullptr);
    void applyLayoutDirection();

    Language m_language = Language::English;
};
