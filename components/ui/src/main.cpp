
#include <QApplication>
#include <QtWidgets>

#include <QStringListModel>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;
    
    QStringList numbers;
    numbers << "BDP" << "CCS" << "PROPELLER" << "SENSORS" << "BOILANCY";
    QAbstractItemModel *model = new QStringListModel(numbers);    
    
    QListView *view = new QListView(splitter);
    view->setMaximumWidth(150);
    view->setModel(model);
    
    QWidget *widget = new QWidget(splitter);
    
    splitter->resize(800,600);
    splitter->setCollapsible(0,0);
    splitter->setCollapsible(1,0);
    splitter->show();
    return app.exec();
}