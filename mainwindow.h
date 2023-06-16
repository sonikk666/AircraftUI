#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aircraft.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void aircraftsSlot(QList<Aircraft>* allAircraft);  // приём данных о списке всех самолётов

private slots:
    void onPressPlay();  // поведение при нажании или клике в первом ListWidget на самолёт(reg_num)

};
#endif // MAINWINDOW_H
