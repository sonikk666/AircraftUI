#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("<b>Все найденные самолёты</b>");
    ui->label_2->setText("<b>Параметры выбранного самолёта</b>");
    ui->label_3->setText("<b>История полётов выбранного самолёта</b>");

    connect(ui->listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onPressPlay()));
    connect(ui->listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onPressPlay()));

    ui->tableWidget->clear();

    QStringList table_labels = {
        "DATE",
        "FROM",
        "TO",
        "FLIGHT",
        "FLIGHT TIME",
        "STD",
        "ATD",
        "STA",
        "STATUS"
    };
    ui->tableWidget->setHorizontalHeaderLabels( table_labels );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::aircraftsSlot(QList<Aircraft>* allAircraft)
{
    ui->listWidget->clear();
    QString aircrafts_count = QString::number(allAircraft->size());

    ui->label->setText("<b>Количество найденных самолётов " + aircrafts_count + " шт.</b>");
    foreach (Aircraft aircraft, *allAircraft)
    {
        QVariant var;
        var.setValue(aircraft);
        Aircraft air = var.value<Aircraft>();

        QListWidgetItem *item = new QListWidgetItem;
        item->setText("Reg_num     " + aircraft.regNumber);
        item->setData(Qt::UserRole, var);

        ui->listWidget->setSortingEnabled(true);  // Сортировка списка включена
        ui->listWidget->addItem(item);
//        ui->statusbar->showMessage(item->text());
//        item2->setToolTip("Всплывающая подсказка");
    }
}


void MainWindow::onPressPlay() {
    QListWidgetItem *item = ui->listWidget->currentItem(); //получить текущий Item
    QVariant var = item->data(Qt::UserRole);
    Aircraft air = var.value<Aircraft>();

    ui->listWidget_2->clear();
    ui->tableWidget->clearContents();

    ui->listWidget_2->addItem("Reg_num            " + air.regNumber);
//    ui->listWidget_2->addItem("urlAircraft        " + air.urlAircraft);
    ui->listWidget_2->addItem("Aircraft               " + air.aircraft);
    ui->listWidget_2->addItem("Airline                 " + air.airline);
    ui->listWidget_2->addItem("Operator            " + air.nameOperator);
    ui->listWidget_2->addItem("TypeCode           " + air.typeCode);
    ui->listWidget_2->addItem("CodeAirlane       " + air.codeAirlane);
    ui->listWidget_2->addItem("CodeOperator   " + air.codeOperator);
    ui->listWidget_2->addItem("ModeS                " + air.modeS);
    ui->listWidget_2->addItem("MSN                " + air.msn);
    ui->listWidget_2->addItem("Age                " + air.age);

    QString flights_count = QString::number(air.allFlightsHistory.size());
    ui->listWidget_2->addItem("Flights count      " + flights_count);
    ui->label_3->setText("<b>История полётов выбранного самолёта. Количество полётов - " + flights_count + " шт.</b>");

    if (air.allFlightsHistory.empty())
    {
        ui->tableWidget->setRowCount(1);
        QTableWidgetItem* my_item_11 = new QTableWidgetItem( "flights_count = " + flights_count );
        ui->tableWidget->setItem( 0, 0,  my_item_11);

    } else
    {
        ui->tableWidget->setRowCount(air.allFlightsHistory.size());
        int n = 0;
        foreach (FlightHistory oneHistory, air.allFlightsHistory)
        {
            QTableWidgetItem* my_item_0 = new QTableWidgetItem( oneHistory.date );
            QTableWidgetItem* my_item_1 = new QTableWidgetItem( oneHistory.flight_from );
            QTableWidgetItem* my_item_2 = new QTableWidgetItem( oneHistory.flight_to );
            QTableWidgetItem* my_item_3 = new QTableWidgetItem( oneHistory.flight );
            QTableWidgetItem* my_item_4 = new QTableWidgetItem( oneHistory.flight_time ); // flight time
            QTableWidgetItem* my_item_5 = new QTableWidgetItem( oneHistory.std );
            QTableWidgetItem* my_item_6 = new QTableWidgetItem( oneHistory.atd );
            QTableWidgetItem* my_item_7 = new QTableWidgetItem( oneHistory.sta );
            QTableWidgetItem* my_item_8 = new QTableWidgetItem( oneHistory.status ); // status flight

            ui->tableWidget->setItem( n, 0, my_item_0 );
            ui->tableWidget->setItem( n, 1, my_item_1 );
            ui->tableWidget->setItem( n, 2, my_item_2 );
            ui->tableWidget->setItem( n, 3, my_item_3 );
            ui->tableWidget->setItem( n, 4, my_item_4 );
            ui->tableWidget->setItem( n, 5, my_item_5 );
            ui->tableWidget->setItem( n, 6, my_item_6 );
            ui->tableWidget->setItem( n, 7, my_item_7 );
            ui->tableWidget->setItem( n, 8, my_item_8 );
            ++n;
        }
    }
}
