#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QSystemTrayIcon>
#include <dbmanager.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("adgellida");
    app.setApplicationName("ubunsys");

    //SETTINGS

    static const QString path (QDir::homePath() + "/.ubunsys/configurations/config.db");
    DbManager db(path);

    //######## Language selection

//    if (db.isOpen())
//    {
    QTranslator translator;

    QString languageSelected = db.getStatus("language");

    if ((languageSelected == "Spanish") || (languageSelected == "Español")){

        translator.load(":/languages/ubunsys_es_ES.qm");
        app.installTranslator(&translator);
        qDebug() << "Spanish loaded";
    }

//    }

    //######## Theme selection

    QString themeSelected = db.getStatus("theme");

    if ((themeSelected == "Dark") || (themeSelected == "Oscuro")){

        QFile file(":qdarkstyle/style.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&file);
        qApp->setStyleSheet(ts.readAll());
        qDebug() << "Dark loaded";
    }

    else if ((themeSelected == "Default") || (themeSelected == "Por defecto")){

        qDebug() << "Default loaded";
    }

    else {

        qDebug() << "Default loaded";
    }

    //theme end

    MainWindow w;
    w.show();
    //Widget o;
    //o.show();
    return app.exec();
}
