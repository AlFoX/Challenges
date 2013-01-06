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
#include <QMap>

class Recognizer
{
public:
    enum ErrorCode {OK, ILL, ERR, AMB};
    Recognizer();

    QString character(int num);
    void parseFile(const QString & infileName, const QString & outfileName);

    QStringList encodeValue(const QString & num);
    QString decodeValue(const QStringList & encodedValue);

    ErrorCode checkSum(const QString & value);
    ErrorCode errorCorrection(const QStringList & encodedValue, QStringList * const variants);

private:
    void init();
    QString errorToString(ErrorCode code);
    QList<int> possibleCharacters(const QStringList & character ); //3 rows character
//    void resursiveErrorCorrection(const QString & value, int charNum, const QList<QList<int> > &map, QStringList * const variants);

    void showError(const QString &text) {
        qDebug() << text;
    }


    QString m_characters[10];
};

#endif // RECOGNIZER_H
