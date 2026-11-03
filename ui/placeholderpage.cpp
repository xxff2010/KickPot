#include "ui/placeholderpage.h"

#include "core/appmanager.h"

#include <QLabel>
#include <QVBoxLayout>

PlaceholderPage::PlaceholderPage(const char *titleKey, const char *descKey,
                                 const QString &icon, QWidget *parent)
    : QWidget(parent)
    , m_titleKey(titleKey)
    , m_descKey(descKey)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(32, 28, 32, 28);
    layout->setSpacing(14);
    layout->addStretch();

    m_icon = new QLabel(icon, this);
    m_icon->setObjectName(QStringLiteral("BigIcon"));
    m_icon->setAlignment(Qt::AlignCenter);

    m_title = new QLabel(this);
    m_title->setObjectName(QStringLiteral("PageTitle"));
    m_title->setAlignment(Qt::AlignCenter);

    m_description = new QLabel(this);
    m_description->setObjectName(QStringLiteral("MutedText"));
    m_description->setAlignment(Qt::AlignCenter);
    m_description->setWordWrap(true);
    m_description->setMaximumWidth(520);

    m_badge = new QLabel(this);
    m_badge->setObjectName(QStringLiteral("Badge"));
    m_badge->setAlignment(Qt::AlignCenter);

    layout->addWidget(m_icon, 0, Qt::AlignHCenter);
    layout->addWidget(m_title, 0, Qt::AlignHCenter);
    layout->addWidget(m_description, 0, Qt::AlignHCenter);
    layout->addWidget(m_badge, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(&AppManager::instance(), &AppManager::languageChanged,
            this, &PlaceholderPage::retranslate);
    retranslate();
}

void PlaceholderPage::retranslate()
{
    const AppManager &app = AppManager::instance();
    m_title->setText(app.text(m_titleKey));
    m_description->setText(app.text(m_descKey));
    m_badge->setText(app.text("page.soon"));
}
