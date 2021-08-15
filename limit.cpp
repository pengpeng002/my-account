#include "limit.h"
#include "ui_limit.h"

Limit::Limit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Limit)
{
    ui->setupUi(this);
    QDate a = QDate::currentDate();
    ui->comboBox->setCurrentIndex(op);
    ui->dateEdit->setCalendarPopup(1);//是否弹出
    ui->dateEdit_2->setCalendarPopup(1);
    ui->dateEdit->setMaximumDate(a);//可选择的最大日期
    ui->dateEdit_2->setMaximumDate(a);
    ui->dateEdit->setDate(QDate(start.year, start.month, start.day));//当前选择日期
    ui->dateEdit_2->setDate(QDate(endm.year, endm.month, endm.day));
}

Limit::~Limit()
{
    delete ui;
}

void Limit::closeEvent(QCloseEvent*)
{
    emit ExitWin();
}

void Limit::on_dateEdit_2_dateChanged(const QDate &date)
{
    ui->dateEdit->setMaximumDate(date);
}

void Limit::on_dateEdit_dateChanged(const QDate &date)
{
    ui->dateEdit_2->setMinimumDate(date);
}

void Limit::on_pushButton_clicked()//保存
{
    op = ui->comboBox->currentIndex();
    QDate a = ui->dateEdit->date();
    start = {a.year(), a.month(), a.day(), 0, 0};
    a = ui->dateEdit_2->date();
    endm = {a.year(), a.month(), a.day(), 23, 59};
}

void Limit::on_pushButton_2_clicked()
{
    this->close();
}
