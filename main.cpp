#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RaTex_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;

    w.adjustSize();
    w.setWindowTitle("RaText Rich Text Editor");
    w.setWindowIcon(QIcon(":images/RaText.png"));
    w.show();

     qDebug()<< "style app : "<< a.styleSheet();
    return a.exec();

}
