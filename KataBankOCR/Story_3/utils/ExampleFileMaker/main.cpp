#include <QtCore>
#include "recognizer.h"

int main()
{
//    QCoreApplication a(argc, argv);
    

    Recognizer r;

    // random number generator initializing for tests;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QFile file("infile.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    for (int i=0; i < 500; ++i) {

        QString strValue;
        for (int i=0; i<9; ++i)
            strValue.append(QString::number(qrand() % 10));

        QStringList accountNumber = r.encodeValue(strValue);

        if (file.isOpen())
            out << accountNumber.join("\n") << "\n";
    }

    if (file.isOpen())
        file.close();

//    return a.exec();
}
