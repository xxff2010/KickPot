#include <QApplication>
#include <QFont>

#include "core/appmanager.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName(QStringLiteral("KickPot"));
    QCoreApplication::setApplicationName(QStringLiteral("KickPot"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.1.0"));

    // Segoe UI supports both Latin and Arabic scripts on Windows.
    app.setFont(QFont(QStringLiteral("Segoe UI"), 10));

    // Load saved language and set the layout direction before creating any window.
    AppManager::instance().initialize();
    app.setStyleSheet(AppManager::loadStyleSheet());

    MainWindow window;
    window.show();

    return app.exec();
}
