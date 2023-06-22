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
    for (auto aircraft : *allAircraft)
    {
        QVariant var;
        var.setValue(aircraft);
        Aircraft air = var.value<Aircraft>();

        QListWidgetItem *item = new QListWidgetItem;
        item->setText("Reg_num     " + aircraft.get_m_regNumber());
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

    ui->listWidget_2->addItem("Reg_num            " + air.get_m_regNumber());
//    ui->listWidget_2->addItem("urlAircraft        " + air.urlAircraft);
    ui->listWidget_2->addItem("Aircraft               " + air.get_m_aircraft());
    ui->listWidget_2->addItem("Airline                 " + air.get_m_airline());
    ui->listWidget_2->addItem("Operator            " + air.get_m_nameOperator());
    ui->listWidget_2->addItem("TypeCode           " + air.get_m_typeCode());
    ui->listWidget_2->addItem("CodeAirlane       " + air.get_m_codeAirlane());
    ui->listWidget_2->addItem("CodeOperator   " + air.get_m_codeOperator());
    ui->listWidget_2->addItem("ModeS                " + air.get_m_modeS());
    ui->listWidget_2->addItem("MSN                " + air.get_m_msn());
    ui->listWidget_2->addItem("Age                " + air.get_m_age());

    QString flights_count = QString::number(air.get_m_allFlightsHistory().size());
    ui->listWidget_2->addItem("Flights count      " + flights_count);
    ui->label_3->setText("<b>История полётов выбранного самолёта. Количество полётов - " + flights_count + " шт.</b>");

    if (air.get_m_allFlightsHistory().empty())
    {
        ui->tableWidget->setRowCount(1);
        QTableWidgetItem* my_item_11 = new QTableWidgetItem( "flights_count = " + flights_count );
        ui->tableWidget->setItem( 0, 0,  my_item_11);

    } else
    {
        ui->tableWidget->setRowCount(air.get_m_allFlightsHistory().size());
        int n = 0;
        for (auto oneHistory : air.get_m_allFlightsHistory())
        {
            QTableWidgetItem* my_item_0 = new QTableWidgetItem( oneHistory.get_m_date() );
            QTableWidgetItem* my_item_1 = new QTableWidgetItem( oneHistory.get_m_flightFrom() );
            QTableWidgetItem* my_item_2 = new QTableWidgetItem( oneHistory.get_m_flightTo() );
            QTableWidgetItem* my_item_3 = new QTableWidgetItem( oneHistory.get_m_flight() );
            QTableWidgetItem* my_item_4 = new QTableWidgetItem( oneHistory.get_m_flightTime() ); // flight time
            QTableWidgetItem* my_item_5 = new QTableWidgetItem( oneHistory.get_m_std() );
            QTableWidgetItem* my_item_6 = new QTableWidgetItem( oneHistory.get_m_atd() );
            QTableWidgetItem* my_item_7 = new QTableWidgetItem( oneHistory.get_m_sta() );
            QTableWidgetItem* my_item_8 = new QTableWidgetItem( oneHistory.get_m_status() ); // status flight

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
