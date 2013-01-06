#ifndef CHARACTERSTANDARD_H
#define CHARACTERSTANDARD_H
#include <QString>
#include <QStringList>
#include <QList>


void fillCharacters(QString characters[]) {

    characters[0] =         " _ "
                            "| |"
                            "|_|";

    characters[1] =         "   "
                            "  |"
                            "  |";

    characters[2] =         " _ "
                            " _|"
                            "|_ ";

    characters[3] =         " _ "
                            " _|"
                            " _|";

    characters[4] =         "   "
                            "|_|"
                            "  |";

    characters[5] =         " _ "
                            "|_ "
                            " _|";

    characters[6] =         " _ "
                            "|_ "
                            "|_|";

    characters[7] =         " _ "
                            "  |"
                            "  |";

    characters[8] =         " _ "
                            "|_|"
                            "|_|";

    characters[9] =         " _ "
                            "|_|"
                            " _|";
}


QString numberTemplate1()
{
    QString number =    " _     _  _     _  _  _  _  _ "
                        "| |  | _| _||_||_ |_   ||_||_|"
                        "|_|  ||_  _|  | _||_|  ||_| _|"
                        "                              ";
    return number;
}


QString numberTemplate2()
{
    QString number =    " _  _  _  _  _     _  _     _ "
                        "|_||_|  ||_ |_ |_| _| _|  || |"
                        " _||_|  ||_| _|  | _||_   ||_|"
                        "                              ";
    return number;
}


QString correctTemplate1()
{
    QString number =    " _  _  _  _  _  _  _  _    "
                        "| || || || || || || ||_   |"
                        "|_||_||_||_||_||_||_| _|  |";
    return number;
}


QString correctTemplate2()
{
    QString number =    "    _  _     _  _  _  _  _ "
                        "  | _| _||_||_ |_   ||_||_|"
                        "  ||_  _|  | _||_|  ||_| _|";
    return number;
}


QString incorrectTemplate1()
{
    QString number =    " _  _  _  _  _  _  _  _  _ "
                        " _|| || || || || || || || |"
                        "|_ |_||_||_||_||_||_||_||_|";
    return number;
}


QString incorrectTemplate2()
{
    QString number =    "                           "
                        "  |  |  |  |  |  |  |  |  |"
                        "  |  |  |  |  |  |  |  |  |";
    return number;
}


// => 711111111
QStringList errorCorrection1(QStringList * variants)
{
    *variants << "711111111";
    QStringList list;
    list << "                           ";
    list << "  |  |  |  |  |  |  |  |  |";
    list << "  |  |  |  |  |  |  |  |  |";
    return list;
}

// => 777777177
QStringList errorCorrection2(QStringList * variants)
{
    *variants << "777777177";
    QStringList list;
    list << " _  _  _  _  _  _  _  _  _ ";
    list << "  |  |  |  |  |  |  |  |  |";
    list << "  |  |  |  |  |  |  |  |  |";
    return list;
}

// => 200800000
QStringList errorCorrection3(QStringList * variants)
{
    *variants << "200800000";
    QStringList list;
    list <<             " _  _  _  _  _  _  _  _  _ ";
    list <<             " _|| || || || || || || || |";
    list <<             "|_ |_||_||_||_||_||_||_||_|";
    return list;
}

// => 333393333
QStringList errorCorrection4(QStringList * variants)
{
    *variants << "333393333";
    QStringList list;
    list <<             " _  _  _  _  _  _  _  _  _ ";
    list <<             " _| _| _| _| _| _| _| _| _|";
    list <<             " _| _| _| _| _| _| _| _| _|";
    return list;
}


// => 888888888 AMB ['888886888', '888888880', '888888988']
QStringList errorCorrection5(QStringList * variants)
{
    *variants << "888886888" << "888888880" << "888888988";
    QStringList list;
    list <<             " _  _  _  _  _  _  _  _  _ ";
    list <<             "|_||_||_||_||_||_||_||_||_|";
    list <<             "|_||_||_||_||_||_||_||_||_|";
    return list;
}

//555555555 AMB ['555655555', '559555555']
QStringList errorCorrection6(QStringList * variants)
{
    *variants << "555655555" << "559555555";
    QStringList list;
    list <<             " _  _  _  _  _  _  _  _  _ ";
    list <<             "|_ |_ |_ |_ |_ |_ |_ |_ |_ ";
    list <<             " _| _| _| _| _| _| _| _| _|";
    return list;
}

//=> 666666666 AMB ['666566666', '686666666']
QStringList errorCorrection7(QStringList * variants)
{
    *variants << "666566666" << "686666666";
    QStringList list;
    list <<             " _  _  _  _  _  _  _  _  _ ";
    list <<             "|_ |_ |_ |_ |_ |_ |_ |_ |_ ";
    list <<             "|_||_||_||_||_||_||_||_||_|";
    return list;
}

//=> 999999999 AMB ['899999999', '993999999', '999959999']
QStringList errorCorrection8(QStringList * variants)
{
    *variants << "899999999" << "993999999" << "999959999";
    QStringList list;
    list <<             " _  _  _  _  _  _  _  _  _ ";
    list <<             "|_||_||_||_||_||_||_||_||_|";
    list <<             " _| _| _| _| _| _| _| _| _|";
    return list;
}

//=> 490067715 AMB ['490067115', '490067719', '490867715']
QStringList errorCorrection9(QStringList * variants)
{
    *variants << "490067115" << "490067719" << "490867715";
    QStringList list;
    list <<             "    _  _  _  _  _  _     _ ";
    list <<             "|_||_|| || ||_   |  |  ||_ ";
    list <<             "  | _||_||_||_|  |  |  | _|";
    return list;
}

//=> 123456789
QStringList errorCorrection10(QStringList * variants)
{
    *variants << "123456789";
    QStringList list;
    list <<             "    _  _     _  _  _  _  _ ";
    list <<             " _| _| _||_||_ |_   ||_||_|";
    list <<             "  ||_  _|  | _||_|  ||_| _|";
    return list;
}

//=> 000000051
QStringList errorCorrection11(QStringList * variants)
{
    *variants << "000000051";
    QStringList list;
    list <<             " _     _  _  _  _  _  _    ";
    list <<             "| || || || || || || ||_   |";
    list <<             "|_||_||_||_||_||_||_| _|  |";
    return list;
}

//=> 490867715
QStringList errorCorrection12(QStringList * variants)
{
    *variants << "490867715";
    QStringList list;
    list <<             "    _  _  _  _  _  _     _ ";
    list <<             "|_||_|| ||_||_   |  |  | _ ";
    list <<             "  | _||_||_||_|  |  |  | _|";
    return list;
}

#endif // CHARACTERSTANDARD_H
