#include "mainwindow.h"
#include "./ui_mainwindow.h"

static int count_numbers = 0;
static int aft_float = 0;
double operand; //возможно, стоит сделать статик

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_1, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(digit_input()));
    connect(ui->pushButton_sign, SIGNAL(clicked()),this, SLOT(signature()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this, SLOT(calcs()));
    connect(ui->pushButton_min, SIGNAL(clicked()),this, SLOT(calcs()));
    connect(ui->pushButton_mult, SIGNAL(clicked()),this, SLOT(calcs()));
    connect(ui->pushButton_div, SIGNAL(clicked()),this, SLOT(calcs()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_min->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_div->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//это было со старой попыткой ввода, оно некорректно с очень малой дробной частью работало
/*void MainWindow::digit_input(){
    if (count_numbers < 11) {
        QPushButton* button = (QPushButton *)sender();
        QString new_number;
        double displayed_number;
        if(ui->digits->text().contains(".") && button->text() == "0") {
            //new_number = ui->digits->text() + button->text();
            new_number = QString::number((ui->digits->text() + button->text()).toDouble(), 'f', count_numbers);
        } else {
            displayed_number = (ui->digits->text() + button->text()).toDouble();
            //new_number = QString::number(displayed_number, 'g', 11);
            new_number = QString::number(displayed_number, 'f', count_numbers);
        }
        ui->digits->setText(new_number);
        count_numbers++;
    }
}*/

void MainWindow::digit_input(){
    if (count_numbers < 11) {
        QPushButton* button = (QPushButton *)sender();
        QString new_number;
        double displayed_number;
        if(ui->digits->text().contains(".")) {
            aft_float++;
            new_number = QString::number((ui->digits->text() + button->text()).toDouble(), 'f', aft_float);
        } else {
            displayed_number = (ui->digits->text() + button->text()).toDouble();
            new_number = QString::number(displayed_number, 'g', 11);
        }
        ui->digits->setText(new_number);
        count_numbers++;
    }
}


void MainWindow::signature(){
    double displayed_number;
    QString new_number;
    displayed_number = (ui->digits->text()).toDouble();
    displayed_number *= -1;
    new_number = QString::number(displayed_number, 'g', 11); /*с малой дробной частью экспонента появляется,
                                                            но это в угоду отсутствию проблем с целыми числами*/
    //new_number = QString::number(displayed_number, 'f', aft_float);
    ui->digits->setText(new_number);

}

void MainWindow::calcs(){
    QPushButton* button = (QPushButton *)sender();

    operand = ui->digits->text().toDouble();

    button->setChecked(true);
    ui->digits->setText("0");
    count_numbers = 0;
    aft_float = 0;
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (count_numbers < 10) {
        if (!(ui->digits->text().contains('.'))){
            ui->digits->setText(ui->digits->text() + '.');
        }
    }
}


void MainWindow::on_pushButton_clear_clicked()
{
    operand = 0;
    ui->digits->setText("0");
    count_numbers = 0;
    aft_float = 0;
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_min->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_div->setChecked(false);
}


void MainWindow::on_pushButton_score_clicked()
{
    double res, operand2;
    QString new_number;

    operand2 = ui->digits->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
        res = operand + operand2;
        new_number = QString::number(res, 'g', 11);
        ui->digits->setText(new_number);
        ui->pushButton_plus->setChecked(false);

    } else if (ui->pushButton_min->isChecked()){
        res = operand - operand2;
        new_number = QString::number(res, 'g', 11);
        ui->digits->setText(new_number);
        ui->pushButton_min->setChecked(false);
    } else if (ui->pushButton_mult->isChecked()){
        res = operand * operand2;
        new_number = QString::number(res, 'g', 11);
        ui->digits->setText(new_number);
        ui->pushButton_mult->setChecked(false);
    } else if (ui->pushButton_div->isChecked()){
        res = operand / operand2;
        new_number = QString::number(res, 'g', 11);
        ui->digits->setText(new_number);
        ui->pushButton_div->setChecked(false);
    }
}

