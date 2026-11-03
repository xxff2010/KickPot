#include "core/appmanager.h"

#include <QCoreApplication>
#include <QFile>
#include <QGuiApplication>
#include <QLocale>
#include <QSettings>

#include <cstring>

namespace {

struct Entry {
    const char *key;
    const char16_t *en;
    const char16_t *ar;
};

const Entry kEntries[] = {
    {"nav.dashboard", u"Dashboard", u"لوحة التحكم"},
    {"nav.stream", u"Stream Viewer", u"مشاهدة البث"},
    {"nav.chat", u"Live Chat", u"الدردشة المباشرة"},
    {"nav.ai", u"AI Assistant", u"المساعد الذكي"},
    {"nav.settings", u"Settings", u"الإعدادات"},
    {"sidebar.version", u"Version 0.1.0 - Phase 2", u"الإصدار 0.1.0 - المرحلة 2"},

    {"dash.title", u"Dashboard", u"لوحة التحكم"},
    {"dash.subtitle", u"Welcome to KickPot, your smart viewing companion.",
     u"أهلاً بك في KickPot، مساعدك الذكي لمتابعة البثوث."},
    {"card.connection", u"Connection", u"حالة الاتصال"},
    {"card.channel", u"Current channel", u"القناة الحالية"},
    {"card.ai", u"AI assistant", u"المساعد الذكي"},
    {"card.messages", u"Chat messages", u"رسائل الدردشة"},
    {"status.disconnected", u"Not connected", u"غير متصل"},
    {"status.none", u"None", u"لا يوجد"},
    {"status.ai.off", u"Not configured", u"غير مُعد"},
    {"dash.activity", u"Recent activity", u"النشاط الأخير"},
    {"dash.activity.empty", u"No activity yet. Open a stream to get started.",
     u"لا يوجد نشاط بعد. افتح بثاً للبدء."},
    {"dash.quick", u"Quick access", u"وصول سريع"},
    {"quick.stream", u"Open a stream", u"فتح بث"},
    {"quick.chat", u"View live chat", u"عرض الدردشة"},
    {"quick.ai", u"Open AI assistant", u"فتح المساعد الذكي"},

    {"page.soon", u"Coming soon", u"قريباً"},
    {"page.stream.desc",
     u"Watch Kick streams with the official embedded player. This page will be built in Phase 3.",
     u"شاهد بثوث Kick عبر المشغّل الرسمي المدمج. سيتم بناء هذه الصفحة في المرحلة 3."},
    {"page.chat.desc",
     u"Follow live chat messages in a clean interface. This page will be built in Phase 4.",
     u"تابع رسائل الدردشة المباشرة في واجهة أنيقة. سيتم بناء هذه الصفحة في المرحلة 4."},
    {"page.ai.desc",
     u"Get context-aware reply suggestions in Arabic and English. This page will be built in Phase 5.",
     u"احصل على اقتراحات ردود مناسبة للسياق بالعربية والإنجليزية. سيتم بناء هذه الصفحة في المرحلة 5."},

    {"settings.title", u"Settings", u"الإعدادات"},
    {"settings.language", u"Application language", u"لغة التطبيق"},
    {"settings.language.desc",
     u"Changes the interface language and layout direction instantly.",
     u"يغيّر لغة الواجهة واتجاهها فوراً."},
    {"settings.more",
     u"More settings (AI provider, Kick account, privacy) will be added in later phases.",
     u"سيتم إضافة المزيد من الإعدادات (مزوّد الذكاء الاصطناعي، حساب Kick، الخصوصية) في المراحل القادمة."},
};

} // namespace

AppManager::AppManager(QObject *parent)
    : QObject(parent)
{
}

AppManager &AppManager::instance()
{
    // Parented to the application object so it is destroyed before QApplication.
    static AppManager *inst = new AppManager(QCoreApplication::instance());
    return *inst;
}

void AppManager::initialize()
{
    QSettings settings;
    const int defaultLanguage =
        (QLocale::system().language() == QLocale::Arabic) ? 1 : 0;
    const int stored = settings.value(QStringLiteral("language"), defaultLanguage).toInt();
    m_language = (stored == 1) ? Language::Arabic : Language::English;
    applyLayoutDirection();
}

void AppManager::setLanguage(Language language)
{
    if (language == m_language)
        return;

    m_language = language;

    QSettings settings;
    settings.setValue(QStringLiteral("language"), static_cast<int>(m_language));

    applyLayoutDirection();
    emit languageChanged();
}

void AppManager::applyLayoutDirection()
{
    QGuiApplication::setLayoutDirection(
        m_language == Language::Arabic ? Qt::RightToLeft : Qt::LeftToRight);
}

QString AppManager::text(const char *key) const
{
    for (const Entry &entry : kEntries) {
        if (std::strcmp(entry.key, key) == 0) {
            return QString::fromUtf16(m_language == Language::Arabic ? entry.ar : entry.en);
        }
    }
    // Missing key: show the key itself so the problem is easy to spot.
    return QString::fromLatin1(key);
}

QString AppManager::loadStyleSheet()
{
    QFile file(QStringLiteral(":/styles/darktheme.qss"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();
    return QString::fromUtf8(file.readAll());
}
