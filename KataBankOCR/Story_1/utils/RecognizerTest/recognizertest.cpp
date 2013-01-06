#include "functions.h"
#include "recognizer.h"
#include <QtTest/QtTest>

class RecognizerTest : public QObject
{
    Q_OBJECT
private slots:
    void charactersIsCorrect();
    void numberCorrectness();
    void isParsingRevertable();
};


void RecognizerTest::charactersIsCorrect()
{
    Recognizer r;
    QString characters[10];
    fillCharacters(characters);
    QVERIFY (characters[0] == r.character(0));
    QVERIFY (characters[1] == r.character(1));
    QVERIFY (characters[2] == r.character(2));
    QVERIFY (characters[3] == r.character(3));
    QVERIFY (characters[4] == r.character(4));
    QVERIFY (characters[5] == r.character(5));
    QVERIFY (characters[6] == r.character(6));
    QVERIFY (characters[7] == r.character(7));
    QVERIFY (characters[8] == r.character(8));
    QVERIFY (characters[9] == r.character(9));
}


void RecognizerTest::numberCorrectness()
{
    Recognizer r;
    QCOMPARE(numberTemplate1(), r.encodeValue("0123456789").join(""));
    QCOMPARE(numberTemplate2(), r.encodeValue("9876543210").join(""));
}


void RecognizerTest::isParsingRevertable()
{
    Recognizer r;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for (int i=0; i < 5000; ++i) {

        QString strValue;
        for (int i=0; i<9; ++i)
            strValue.append(QString::number(qrand() % 10));

        QStringList accountNumber = r.encodeValue(strValue);
        QString decodedNumber = r.decodeValue(accountNumber);
        QCOMPARE (strValue, decodedNumber);
    }
}





QTEST_MAIN(RecognizerTest)
#include "recognizertest.moc"
