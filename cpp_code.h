#ifndef CPP_CODE_H
#define CPP_CODE_H

#include <QObject>

class cpp_code : public QObject
{
    Q_OBJECT
public:
    explicit cpp_code(QObject *parent = nullptr);

signals:
    void cppSendMsg(const QVariant &arg1, const QVariant &arg2);

public slots:
    void cppRecvMsg(const QString &arg1, const int &arg2);

private:

};

#endif // CPP_CODE_H
