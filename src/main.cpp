#include <QApplication>
#include <QDebug>
#include <QTranslator>

#include "config.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationVersion(VERSION);

    QTranslator translator;

    for (auto lang : QLocale().uiLanguages()) {
        QString qm_filename = QString(":/lang/%1_%2.qm").arg(PROJECT_NAME).arg(lang);
        QFile qm_file(qm_filename);
        if (qm_file.exists()) {
            qDebug() << "Load translator: " + qm_filename;
            translator.load(qm_filename);
            QApplication::installTranslator(&translator);
            break;
        }
    }


    MainWindow w;
    w.show();
    return QApplication::exec();
}
