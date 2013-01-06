/*************************************************************************************************************
 *
 * Recognizer class for decoding bank accounts saved by "ingenious machine"
 *
 *************************************************************************************************************/

#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#include <QString>
#include <QStringList>
#include <QDebug>

class Recognizer
{
public:
    Recognizer();

    QString character(int num);
    void parseFile(const QString & infileName, const QString & outfileName);

    QStringList encodeValue(const QString & num);
    QString decodeValue(const QStringList & encodedValue);
    bool checkSum(const QString & value);

private:
    void init();
    void showError(const QString &text) {
        qDebug() << text;
    }

    QString m_characters[10];
};

#endif // RECOGNIZER_H
