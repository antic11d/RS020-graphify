#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);

signals:
    void acceptLogin(QString user);

public slots:
    void slotAcceptLogin();

private:
    QLabel *m_lblUsername;
    QLineEdit *m_user;

    QDialogButtonBox *m_buttons;

    void setUp();
};

#endif // LOGINDIALOG_H
