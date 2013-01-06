#ifndef CHARACTERSTANDARD_H
#define CHARACTERSTANDARD_H
#include <QString>


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



#endif // CHARACTERSTANDARD_H
