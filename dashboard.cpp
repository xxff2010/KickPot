#include "ui/dashboard.h"

#include "core/appmanager.h"
#include "core/pages.h"
#include "ui/statcard.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

DashboardPage::DashboardPage(QWidget *parent)
    : QWidget(parent)
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(32, 28, 32, 28);
    root->setSpacing(20);

    m_title = new QLabel(this);
    m_title->setObjectName(QStringLiteral("PageTitle"));
    m_subtitle = new QLabel(this);
    m_subtitle->setObjectName(QStringLiteral("PageSubtitle"));
    root->addWidget(m_title);
    root->addWidget(m_subtitle);

    // Row of status cards.
    auto *cards = new QHBoxLayout;
    cards->setSpacing(16);
    m_connectionCard = new StatCard(this);
    m_channelCard = new StatCard(this);
    m_aiCard = new StatCard(this);
    m_messagesCard = new StatCard(this);
    cards->addWidget(m_connectionCard);
    cards->addWidget(m_channelCard);
    cards->addWidget(m_aiCard);
    cards->addWidget(m_messagesCard);
    root->addLayout(cards);

    // Lower row: recent activity (wide) + quick access (narrow).
    auto *lower = new QHBoxLayout;
    lower->setSpacing(16);

    auto *activityCard = new QFrame(this);
    activityCard->setObjectName(QStringLiteral("Card"));
    auto *activityLayout = new QVBoxLayout(activityCard);
    activityLayout->setContentsMargins(20, 18, 20, 18);
    activityLayout->setSpacing(12);
    m_activityTitle = new QLabel(activityCard);
    m_activityTitle->setObjectName(QStringLiteral("SectionTitle"));
    m_activityEmpty = new QLabel(activityCard);
    m_activityEmpty->setObjectName(QStringLiteral("MutedText"));
    m_activityEmpty->setWordWrap(true);
    m_activityEmpty->setAlignment(Qt::AlignCenter);
    activityLayout->addWidget(m_activityTitle);
    activityLayout->addStretch();
    activityLayout->addWidget(m_activityEmpty);
    activityLayout->addStretch();

    auto *quickCard = new QFrame(this);
    quickCard->setObjectName(QStringLiteral("Card"));
    auto *quickLayout = new QVBoxLayout(quickCard);
    quickLayout->setContentsMargins(20, 18, 20, 18);
    quickLayout->setSpacing(12);
    m_quickTitle = new QLabel(quickCard);
    m_quickTitle->setObjectName(QStringLiteral("SectionTitle"));
    m_streamButton = new QPushButton(quickCard);
    m_streamButton->setObjectName(QStringLiteral("PrimaryButton"));
    m_chatButton = new QPushButton(quickCard);
    m_chatButton->setObjectName(QStringLiteral("SecondaryButton"));
    m_aiButton = new QPushButton(quickCard);
    m_aiButton->setObjectName(QStringLiteral("SecondaryButton"));
    for (QPushButton *button : {m_streamButton, m_chatButton, m_aiButton})
        button->setCursor(Qt::PointingHandCursor);
    quickLayout->addWidget(m_quickTitle);
    quickLayout->addWidget(m_streamButton);
    quickLayout->addWidget(m_chatButton);
    quickLayout->addWidget(m_aiButton);
    quickLayout->addStretch();

    lower->addWidget(activityCard, 2);
    lower->addWidget(quickCard, 1);
    root->addLayout(lower, 1);

    connect(m_streamButton, &QPushButton::clicked, this,
            [this]() { emit navigateRequested(Page::Stream); });
    connect(m_chatButton, &QPushButton::clicked, this,
            [this]() { emit navigateRequested(Page::Chat); });
    connect(m_aiButton, &QPushButton::clicked, this,
            [this]() { emit navigateRequested(Page::Assistant); });

    connect(&AppManager::instance(), &AppManager::languageChanged,
            this, &DashboardPage::retranslate);
    retranslate();
}

void DashboardPage::retranslate()
{
    const AppManager &app = AppManager::instance();

    m_title->setText(app.text("dash.title"));
    m_subtitle->setText(app.text("dash.subtitle"));

    m_connectionCard->setTitle(app.text("card.connection"));
    m_connectionCard->setValue(app.text("status.disconnected"), QStringLiteral("warning"));

    m_channelCard->setTitle(app.text("card.channel"));
    m_channelCard->setValue(app.text("status.none"));

    m_aiCard->setTitle(app.text("card.ai"));
    m_aiCard->setValue(app.text("status.ai.off"), QStringLiteral("warning"));

    m_messagesCard->setTitle(app.text("card.messages"));
    m_messagesCard->setValue(QStringLiteral("0"));

    m_activityTitle->setText(app.text("dash.activity"));
    m_activityEmpty->setText(app.text("dash.activity.empty"));

    m_quickTitle->setText(app.text("dash.quick"));
    m_streamButton->setText(app.text("quick.stream"));
    m_chatButton->setText(app.text("quick.chat"));
    m_aiButton->setText(app.text("quick.ai"));
}
