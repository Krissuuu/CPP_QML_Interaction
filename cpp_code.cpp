#include "cpp_code.h"

#include "QDebug"
#include <QVariant>

cpp_code::cpp_code(QObject *parent) : QObject{parent}
{

}

void cpp_code::cppRecvMsg(const QString &arg1,const int &arg2){
    qDebug() << "cppRecvMsg" << arg1 << arg2;
    qDebug() << "emit cppSendMsg";
    QVariant return_arg = arg1;
    QVariant return_arg2 = arg2;
    emit cppSendMsg(return_arg, return_arg2);
}
