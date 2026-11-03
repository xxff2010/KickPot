#pragma once

#include <QFrame>
#include <QLabel>
#include <QStyle>
#include <QVBoxLayout>

// Small card showing a title and a colored value (used on the dashboard).
class StatCard : public QFrame
{
public:
    explicit StatCard(QWidget *parent = nullptr)
        : QFrame(parent)
    {
        setObjectName(QStringLiteral("Card"));
        setMinimumHeight(104);

        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(18, 16, 18, 16);
        layout->setSpacing(6);

        m_title = new QLabel(this);
        m_title->setObjectName(QStringLiteral("CardTitle"));

        m_value = new QLabel(this);
        m_value->setObjectName(QStringLiteral("CardValue"));

        layout->addWidget(m_title);
        layout->addWidget(m_value);
        layout->addStretch();
    }

    void setTitle(const QString &title) { m_title->setText(title); }

    // state: "ok", "warning", "error" or empty for the default color.
    void setValue(const QString &value, const QString &state = QString())
    {
        m_value->setText(value);
        m_value->setProperty("state", state);
        // Re-apply the stylesheet so the [state="..."] selector takes effect.
        m_value->style()->unpolish(m_value);
        m_value->style()->polish(m_value);
    }

private:
    QLabel *m_title = nullptr;
    QLabel *m_value = nullptr;
};
