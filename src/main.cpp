#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if(QLocale().language() == QLocale::Chinese){
        QTranslator *t = new QTranslator;
        if(t->load("l18n/zh_CN.qm")) {
            app.installTranslator(t);
        }
    }

    MainWindow w;
    w.show();
    return app.exec();
}
