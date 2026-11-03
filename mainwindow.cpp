#include "mainwindow.h"

#include "core/appmanager.h"
#include "core/pages.h"
#include "ui/dashboard.h"
#include "ui/navbutton.h"
#include "ui/placeholderpage.h"
#include "ui/settingspage.h"

#include <QButtonGroup>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>

namespace {
// Keys used for the navigation labels, in page order.
const char *const kNavKeys[Page::Count] = {
    "nav.dashboard", "nav.stream", "nav.chat", "nav.ai", "nav.settings"
};
} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("KickPot"));
    setMinimumSize(1000, 680);
    resize(1280, 800);

    buildUi();

    connect(&AppManager::instance(), &AppManager::languageChanged,
            this, &MainWindow::retranslateUi);
    retranslateUi();
    navigateTo(Page::Dashboard);
}

void MainWindow::buildUi()
{
    auto *central = new QWidget(this);
    central->setObjectName(QStringLiteral("Root"));
    setCentralWidget(central);

    auto *rootLayout = new QHBoxLayout(central);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    // ---------- Sidebar ----------
    auto *sidebar = new QFrame(central);
    sidebar->setObjectName(QStringLiteral("Sidebar"));
    sidebar->setFixedWidth(250);

    auto *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(16, 24, 16, 16);
    sidebarLayout->setSpacing(6);

    auto *logoRow = new QHBoxLayout;
    logoRow->setSpacing(12);
    auto *badge = new QLabel(QStringLiteral("K"), sidebar);
    badge->setObjectName(QStringLiteral("LogoBadge"));
    badge->setFixedSize(40, 40);
    badge->setAlignment(Qt::AlignCenter);
    auto *logoText = new QLabel(QStringLiteral("KickPot"), sidebar);
    logoText->setObjectName(QStringLiteral("LogoText"));
    logoRow->addWidget(badge);
    logoRow->addWidget(logoText);
    logoRow->addStretch();
    sidebarLayout->addLayout(logoRow);
    sidebarLayout->addSpacing(24);

    // Simple symbols used as icons (can be replaced by SVG icons later).
    const QString icons[Page::Count] = {
        QStringLiteral(u"\u25A6"), // dashboard
        QStringLiteral(u"\u25B6"), // stream
        QStringLiteral(u"\u2709"), // chat
        QStringLiteral(u"\u2726"), // AI
        QStringLiteral(u"\u2699")  // settings
    };

    m_navGroup = new QButtonGroup(this);
    m_navGroup->setExclusive(true);
    for (int i = 0; i < Page::Count; ++i) {
        if (i == Page::Settings)
            sidebarLayout->addStretch(); // push Settings to the bottom
        auto *button = new NavButton(icons[i], sidebar);
        m_navGroup->addButton(button, i);
        m_navButtons.append(button);
        sidebarLayout->addWidget(button);
    }

    m_versionLabel = new QLabel(sidebar);
    m_versionLabel->setObjectName(QStringLiteral("VersionLabel"));
    m_versionLabel->setAlignment(Qt::AlignCenter);
    sidebarLayout->addSpacing(10);
    sidebarLayout->addWidget(m_versionLabel);

    // ---------- Pages ----------
    m_pages = new QStackedWidget(central);

    auto *dashboard = new DashboardPage(m_pages);
    connect(dashboard, &DashboardPage::navigateRequested, this, &MainWindow::navigateTo);

    // The order here must match the Page::Index enum.
    m_pages->addWidget(dashboard);
    m_pages->addWidget(new PlaceholderPage("nav.stream", "page.stream.desc",
                                           icons[Page::Stream], m_pages));
    m_pages->addWidget(new PlaceholderPage("nav.chat", "page.chat.desc",
                                           icons[Page::Chat], m_pages));
    m_pages->addWidget(new PlaceholderPage("nav.ai", "page.ai.desc",
                                           icons[Page::Assistant], m_pages));
    m_pages->addWidget(new SettingsPage(m_pages));

    rootLayout->addWidget(sidebar);
    rootLayout->addWidget(m_pages, 1);

    connect(m_navGroup, &QButtonGroup::idClicked, this, &MainWindow::navigateTo);
}

void MainWindow::navigateTo(int pageIndex)
{
    if (pageIndex < 0 || pageIndex >= m_pages->count())
        return;
    m_pages->setCurrentIndex(pageIndex);
    m_navButtons.at(pageIndex)->setChecked(true);
}

void MainWindow::retranslateUi()
{
    const AppManager &app = AppManager::instance();
    for (int i = 0; i < m_navButtons.size(); ++i)
        m_navButtons.at(i)->setLabel(app.text(kNavKeys[i]));
    m_versionLabel->setText(app.text("sidebar.version"));
}
