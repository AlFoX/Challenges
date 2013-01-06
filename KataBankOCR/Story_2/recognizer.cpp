#include "recognizer.h"
#include "QtCore"
#include "iostream"

Recognizer::Recognizer()
{
    init();
}


void Recognizer::init()
{
    m_characters[0] = " _ "
                   "| |"
                   "|_|";

    m_characters[1] = "   "
                   "  |"
                   "  |";

    m_characters[2] =  " _ "
                    " _|"
                    "|_ ";

    m_characters[3] =  " _ "
                    " _|"
                    " _|";

    m_characters[4] =  "   "
                    "|_|"
                    "  |";

    m_characters[5] =  " _ "
                    "|_ "
                    " _|";

    m_characters[6] =  " _ "
                    "|_ "
                    "|_|";

    m_characters[7] =  " _ "
                    "  |"
                    "  |";

    m_characters[8] =  " _ "
                    "|_|"
                    "|_|";

    m_characters[9] =  " _ "
                    "|_|"
                    " _|";
}


QString Recognizer::character(int num)
{
    if (num > 9 || num <0) {
        showError("number is out of range [0..9]");
        return QString();
    }

    return m_characters[num];
}


void Recognizer::parseFile(const QString & infileName, const QString & outfileName)
{
    QFile inFile(infileName);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFile outFile(outfileName);
    if (!outfileName.isEmpty() && !outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // use textstream instead of direct file reading for prevent
    // problems with different RETURN symbol on different platforms
    // textstream always returns trimmed string
    QTextStream in(&inFile);
    QTextStream out(&outFile);

    QStringList lineList;
    QString line;

    do {
        line = in.readLine();
        lineList.append(line);

        if (lineList.count() == 4) {
            QString accountNumber = decodeValue(lineList);
            bool isValid = checkSum(accountNumber);
            lineList.clear();
            if (outfileName.isEmpty())
                std::cout << accountNumber.toStdString() << (isValid ? " VALID" : " INVALID") << std::endl;
            else
                out << accountNumber << (isValid ? " VALID" : " INVALID") << "\n";
        }
    } while(!line.isNull());

    inFile.close();
    if (outFile.isOpen())
        outFile.close();
}


QStringList Recognizer::encodeValue(const QString & num)
{
    QString line1, line2, line3, line4;

    for (int i=0; i<num.count(); ++i) {
        int currentDigit = QString(num.mid(i,1)).toInt();

        line1.append(m_characters[currentDigit].mid(0, 3));
        line2.append(m_characters[currentDigit].mid(3, 3));
        line3.append(m_characters[currentDigit].mid(6, 3));
        line4.fill(' ', num.count()*3);
    }

    return QStringList() << line1 << line2 << line3 << line4;
}


QString Recognizer::decodeValue(const QStringList &encodedValue)
{
    if (encodedValue.count() != 4)
        return QString();

    // lines' length checking
    foreach (const QString & str, encodedValue) {
        if (str.size() != 27)
            return QString();
    }

    QString decodedNumber;
    QString digit;

    for (int i=0; i<9; ++i) {
        for (int j=0; j<3; ++j) { // 3 since last line is empty
            digit.append(encodedValue[j].mid(i*3,3));
        }

        for (int i=0; i<10; ++i)
            if (m_characters[i] == digit) {
                decodedNumber += QString::number(i);
                break;
            }
        digit.clear();
    }

    return decodedNumber;
}


bool Recognizer::checkSum(const QString & value)
{
    if (value.size() != 9)
        return false;

    int sum = 0;
    for (int i=0; i<9; ++i) {
        bool ok;
        sum += (9-i) * value.mid(i,1).toInt(&ok);  // "[]" makes error while compiling because const
        if (!ok)
            return false;
    }

    if (sum % 11)
        return false;
    else
        return true;
}
