#include <QtCore>
#include "recognizer.h"
#include "iostream"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();

    QString inFile;
    QString outFile;

   if (argc > 1)
       inFile = args[1];
   if (argc > 2)
       outFile = args[2];

   if (inFile.isEmpty()) {
       std::cout << "run: story_1 \"input file\" [\"output file\"] " << std::endl;
       return 0;
   }

    Recognizer r;
    r.parseFile(inFile, outFile);

}
