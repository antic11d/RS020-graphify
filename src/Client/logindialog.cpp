#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setUp();
}

void LoginDialog::setUp()
{
    m_lblUsername = new QLabel(this);
    m_lblUsername->setText("Username:");

    m_user = new QLineEdit(this);

    m_buttons = new QDialogButtonBox(this);
    m_buttons->addButton(QDialogButtonBox::Ok);
    m_buttons->addButton(QDialogButtonBox::Cancel);
    m_buttons->button(QDialogButtonBox::Ok)->setText("Login");
    m_buttons->button(QDialogButtonBox::Cancel)->setText("Cancel");

    connect(m_buttons->button(QDialogButtonBox::Cancel),
            SIGNAL (clicked()),
            this,
            SLOT (close()));

    connect(m_buttons->button( QDialogButtonBox::Ok ),
            SIGNAL (clicked()),
            this,
            SLOT (slotAcceptLogin()));

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(m_lblUsername, 0, 0);
    layout->addWidget(m_user, 0, 1);
    layout->addWidget(m_buttons, 1, 0);

    this->setLayout(layout);
}

void LoginDialog::slotAcceptLogin()
{
    QString user = m_user->text();

    emit acceptLogin(user);

    close();
}













