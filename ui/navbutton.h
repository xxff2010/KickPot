#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// Sidebar navigation button: icon + text.
// Uses a layout inside the button so it mirrors automatically in RTL mode.
class NavButton : public QPushButton
{
public:
    explicit NavButton(const QString &icon, QWidget *parent = nullptr)
        : QPushButton(parent)
    {
        setObjectName(QStringLiteral("NavButton"));
        setCheckable(true);
        setCursor(Qt::PointingHandCursor);
        setFixedHeight(46);

        auto *layout = new QHBoxLayout(this);
        layout->setContentsMargins(16, 0, 16, 0);
        layout->setSpacing(12);

        m_icon = new QLabel(icon, this);
        m_icon->setFixedWidth(24);
        m_icon->setAlignment(Qt::AlignCenter);
        m_icon->setAttribute(Qt::WA_TransparentForMouseEvents);

        m_text = new QLabel(this);
        m_text->setAttribute(Qt::WA_TransparentForMouseEvents);

        layout->addWidget(m_icon);
        layout->addWidget(m_text, 1);
    }

    void setLabel(const QString &text) { m_text->setText(text); }

private:
    QLabel *m_icon = nullptr;
    QLabel *m_text = nullptr;
};
