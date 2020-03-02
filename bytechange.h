#ifndef BYTECHANGE_H
#define BYTECHANGE_H

#include <QString>

QByteArray QString2Hex(QString str);
QString hexToString(QByteArray in);
char ConvertHexChar(char ch);

#endif // BYTECHANGE_H
