#include "addfrom.h"
#include "ui_addfrom.h"

extern vector<LINE> ve;
AddFrom::AddFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFrom)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(1);//默认为支出
    QDateTime cur=QDateTime::currentDateTime();
    ui->tableWidget->item(0, 0)->setText(cur.toString("yyyy-MM-dd"));
    ui->tableWidget->item(0, 1)->setText(cur.toString("hh:mm"));//记一笔界面默认显示的时间与日期为当前时间
}

AddFrom::~AddFrom()
{
    delete ui;
}

void AddFrom::on_pbok_clicked()//确定按钮 保存添加的记录并关闭界面
{
    bool op = ui->comboBox->currentIndex();//支出/收入 0=收入 1=支出
    QString data = ui->tableWidget->item(0,0)->text();//日期
    QString time = ui->tableWidget->item(0,1)->text();//时间
    QStringList a = data.split("-");
    QStringList b = time.split(':');
    double num = ui->tableWidget->item(0, 2)->text().toDouble();//金额
    QString info = ui->tableWidget->item(0, 3)->text();//备注

    LINE line(op, num, MDATE(a[0].toInt(), a[1].toInt(), a[2].toInt(), b[0].toInt(), b[1].toInt()), info.toStdString().c_str());
    ve.push_back(line);//插入一条记录
    sort(ve.begin(), ve.end());//按日期排序
    this->close();
}

void AddFrom::closeEvent(QCloseEvent*)
{
    emit ExitWin();
}

void AddFrom::on_pbcancel_clicked()//取消按钮 直接关闭界面 不保存输入的信息
{
    this->close();
}

