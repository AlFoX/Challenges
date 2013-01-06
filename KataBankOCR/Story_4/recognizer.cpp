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


QString Recognizer::errorToString(ErrorCode code)
{
    switch(code) {
    case OK: return QString("OK");
    case ERR: return QString("ERR");
    case ILL: return QString("ILL");
    case AMB: return QString("AMB");
    }

    return "NAN";
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

        // 4 lines read so starting to process them
        if (lineList.count() == 4) {

            QString accountNumber = decodeValue(lineList);
            ErrorCode code = checkSum(accountNumber);

            // correct errors if possible
            QStringList possibleVariants;
            if (code == ILL || code == ERR) {
                code = errorCorrection(lineList, &possibleVariants);
            }

            QString formattedString;

            // was value corrected or or it's iginal
            if (possibleVariants.size() == 1)
                formattedString.append(possibleVariants[0]);
            else
                formattedString.append(accountNumber);

            // status
            if (code == AMB) {
                formattedString += "  " + errorToString(code) + "  [\'" + possibleVariants.join("\',\'") + "\']";
            } else
                formattedString += "  " + errorToString(code);


            if (outfileName.isEmpty())
                std::cout << formattedString.toStdString() << std::endl;
            else
                out << formattedString << "\n";

            lineList.clear();
            possibleVariants.clear();
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
    if (encodedValue.count() != 3 && encodedValue.count() != 4)
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

        QString decodedChar;

        for (int i=0; i<10; ++i)
            if (m_characters[i] == digit) {
                decodedChar = QString::number(i);
                break;
            }

        decodedNumber += decodedChar.isEmpty() ? "?" : decodedChar;
        digit.clear();
    }

    return decodedNumber;
}


Recognizer::ErrorCode Recognizer::checkSum(const QString & value)
{
    if (value.size() != 9)
        return ILL;

    int sum = 0;
    for (int i=0; i<9; ++i) {
        bool ok;
        sum += (9-i) * value.mid(i,1).toInt(&ok);  // "[]" makes error while compiling because const
        if (!ok)
            return ILL;
    }

    if (sum % 11)
        return ERR;
    else
        return OK;
}


Recognizer::ErrorCode Recognizer::errorCorrection(const QStringList & encodedValue, QStringList * const variants)
{
    // making map of possible characters for each illegible character
    // and calculating checksum for each combination for make list of
    // success combinations "variants"
    // possible characters have only one different item
    // if it has IllegibleValues we are testing ONLY them

    QString value = decodeValue(encodedValue);
    bool hasIllegibleValues = value.contains("?");

    QList <QList<int> > map;

    for (int k=0; k<value.size(); ++k) {
        QList<int> list;

        if (hasIllegibleValues && value[k] != '?') {
            map.append(list);
            continue;
        }

        QStringList illegibleValue;
        for (int i=0; i<3; ++i) // 3 since last line is empty
            illegibleValue.append(encodedValue[i].mid(k*3,3));

        list = possibleCharacters(illegibleValue);

        map.append(list);

    }


    // testing each possible variant for checksum and adding correct one to "variants" list
    for (int i=0; i<value.size(); ++i) {
        for (int j=0; j<map[i].size(); ++j) {
            QString testValue = value;
            testValue.replace(i,1,QString::number(map[i][j]));
            if (checkSum(testValue) == OK)
                variants->append(testValue);
        }
    }


    if (variants->count() == 0)
        return ILL;
    else if (variants->count() == 1)
        return OK;
    else
        return AMB;


    return ERR;
}


QList<int> Recognizer::possibleCharacters(const QStringList & character ) //3 rows character
{
    QList<int> list;
    QString testingChar = character.join("");

    for (int i=0; i<10; ++i) {
        QString baseChar = m_characters[i];

        if (baseChar.size() != testingChar.size()) {
            qDebug() << "size dont match!";
            return list;
        }

        int differencies = 0;
        for (int i=0; i<testingChar.size(); ++i)
            if (baseChar[i] != testingChar[i])
                differencies++;

        if (differencies == 1) // candidate for correction, since there is only one difference
            list.append(i);
    }

    return list;
}
