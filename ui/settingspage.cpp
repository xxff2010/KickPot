#include "ui/settingspage.h"

#include "core/appmanager.h"

#include <QComboBox>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(32, 28, 32, 28);
    root->setSpacing(20);

    m_title = new QLabel(this);
    m_title->setObjectName(QStringLiteral("PageTitle"));

    auto *card = new QFrame(this);
    card->setObjectName(QStringLiteral("Card"));
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(20, 18, 20, 18);
    cardLayout->setSpacing(10);

    m_languageTitle = new QLabel(card);
    m_languageTitle->setObjectName(QStringLiteral("SectionTitle"));
    m_languageDesc = new QLabel(card);
    m_languageDesc->setObjectName(QStringLiteral("MutedText"));
    m_languageDesc->setWordWrap(true);

    m_languageCombo = new QComboBox(card);
    m_languageCombo->setFixedWidth(220);
    // Language names are always shown in their own language.
    m_languageCombo->addItem(QStringLiteral("English"),
                             static_cast<int>(AppManager::Language::English));
    m_languageCombo->addItem(QStringLiteral(u"العربية"),
                             static_cast<int>(AppManager::Language::Arabic));

    cardLayout->addWidget(m_languageTitle);
    cardLayout->addWidget(m_languageDesc);
    cardLayout->addWidget(m_languageCombo, 0, Qt::AlignLeft);

    m_moreNote = new QLabel(this);
    m_moreNote->setObjectName(QStringLiteral("MutedText"));
    m_moreNote->setWordWrap(true);

    root->addWidget(m_title);
    root->addWidget(card);
    root->addWidget(m_moreNote);
    root->addStretch();

    connect(m_languageCombo, &QComboBox::currentIndexChanged, this, [this](int index) {
        const int value = m_languageCombo->itemData(index).toInt();
        AppManager::instance().setLanguage(static_cast<AppManager::Language>(value));
    });

    connect(&AppManager::instance(), &AppManager::languageChanged,
            this, &SettingsPage::retranslate);
    retranslate();
}

void SettingsPage::retranslate()
{
    const AppManager &app = AppManager::instance();

    m_title->setText(app.text("settings.title"));
    m_languageTitle->setText(app.text("settings.language"));
    m_languageDesc->setText(app.text("settings.language.desc"));
    m_moreNote->setText(app.text("settings.more"));

    // Keep the combo box in sync without triggering another language change.
    m_languageCombo->blockSignals(true);
    m_languageCombo->setCurrentIndex(
        m_languageCombo->findData(static_cast<int>(app.language())));
    m_languageCombo->blockSignals(false);
}
