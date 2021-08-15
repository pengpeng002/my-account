#include "his.h"
#include "ui_his.h"
#include <QHeaderView>
bool inited = false;
His::His(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::His)
{
    ui->setupUi(this);
    statusBar = new QStatusBar(this);//状态栏 用于显示收支信息
    layout()->addWidget(statusBar);
    ui->tableWidget->hideColumn(5);//隐藏id栏 id栏记录在数组中的下标
//    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
//    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);

    QHeaderView *headerGoods = ui->tableWidget->horizontalHeader();//表头
    headerGoods->setSortIndicator(1, Qt::AscendingOrder);//将第一列按升序排序
    headerGoods->setSortIndicatorShown(true);
    connect(headerGoods, SIGNAL(sectionClicked(int)), ui->tableWidget, SLOT (sortByColumn(int)));

    myShow();//显示本月所有收支
    inited=true;
}

His::~His()
{
    delete ui;
}

bool cmp(int a, int b)
{
    return a>b;
}

void His::on_pushButton_clicked()//保存
{
    int size = ui->tableWidget->rowCount();
//    ve.resize(size);
    for (int i=0; i<size; i++)//更新数据
    {
        bool op = ui->tableWidget->item(i, 0)->text() == "收入" ? 0 : 1;
        QString data = ui->tableWidget->item(i,1)->text();
        QString time = ui->tableWidget->item(i,2)->text();
        QStringList a = data.split("-");
        QStringList b = time.split(':');
        double num = ui->tableWidget->item(i, 3)->text().toDouble();
        QString info = ui->tableWidget->item(i, 4)->text();

        LINE line(op, num, MDATE(a[0].toInt(), a[1].toInt(), a[2].toInt(), b[0].toInt(), b[1].toInt()), info.toStdString().c_str());
        ve[ui->tableWidget->item(i, 5)->text().toInt()]=line;
    }
    sort(sem.begin(), sem.end(), cmp);//从大到小拍戏
    for(auto i:sem) ve.erase(ve.begin()+i);//从后往前删除元素
    //this->close();
}

void His::on_pushButton_2_clicked()//取消
{
    this->close();
}

void His::closeEvent(QCloseEvent*)
{
    emit ExitWin();
}

void His::on_pushButton_3_clicked()//删除选中行
{
    QList<QTableWidgetItem*> a = ui->tableWidget->selectedItems();//获取所有选择元素
    vector<int> se;
    for (int i=0; i<a.count(); i++)//得到所有选择行
    {
        se.push_back(ui->tableWidget->row(a.at(i)));
    }
    sort(se.begin(), se.end(), cmp);//从大到小排序
    for (auto i:se)//从后往前删除一行
    {
        sem.push_back(ui->tableWidget->item(i, 5)->text().toInt());//记录删除的id
        ui->tableWidget->removeRow(i);
    }
}

void His::on_pushButton_4_clicked()//搜索条件
{
    Limit *l = new Limit();
    l->show();
    this->hide();
    connect(l, SIGNAL(ExitWin()), this, SLOT(myShow()));
}

void His::myShow()//按搜索条件进行搜索并显示
{
    //start.print(' ');
    //endm.print();
    vector<TL> vec;
    ui->tableWidget->setSortingEnabled(false);
    vec.clear();
    int size = ve.size();
    for (int i=0; i<size; i++)//搜索出所有在start到end时间范围内的记录
    {
        MDATE x=ve[i].date;
        if (x > endm) break;
        if (x >= start && x<=endm)
        {
            //x.print(' '), endm.print(' '), printf("<? = %d\n", x<endm);
            if (op == 0 || (op==1 && ve[i].op==0) || (op==2 && ve[i].op==1))
            vec.push_back({ve[i], i});
        }
    }
    //printf("vec.size() = %d\n", vec.size());
    ui->tableWidget->setRowCount(vec.size());
    double used = 0;
    double ined = 0;
    for (int i=0; i<vec.size(); i++)//将搜索结果显示出来
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(vec[i].line.op ? "支出" : "收入");//收入/支出
        ui->tableWidget->setItem(i, 0, item);

        LINE tmp=vec[i].line;//日期
        QString s=QString("%1-%2-%3").arg(tmp.date.year, 4, 10, QChar('0')).arg(tmp.date.month, 2, 10, QChar('0')).arg(tmp.date.day, 2, 10, QChar('0'));
        item = new QTableWidgetItem;
        item->setText(s);
        ui->tableWidget->setItem(i, 1, item);

        s=QString("%1:%2").arg(tmp.date.hour, 2, 10, QChar('0')).arg(tmp.date.min, 2, 10, QChar('0'));//时间
        item = new QTableWidgetItem;
        item->setText(s);
        ui->tableWidget->setItem(i, 2, item);

        item = new QTableWidgetItem;//金额
        s=QString::number(tmp.num,'f',2);
        item->setData(Qt::EditRole, tmp.num);//按数字排序 必须用setData，且第一个参数为EditRole 否则会按字母排序
        //item->setText(s);
        ui->tableWidget->setItem(i, 3, item);


        item = new QTableWidgetItem;//备注信息
        item->setText(tmp.info);
        ui->tableWidget->setItem(i, 4, item);

        item = new QTableWidgetItem;//id
        item->setText(QString::number(vec[i].id));
        ui->tableWidget->setItem(i, 5, item);

        if (tmp.op) used += tmp.num;//总支出
        else ined += tmp.num;//总收入
    }
    this->show();
    ui->tableWidget->setSortingEnabled(true);
    statusBar->showMessage(QString("支出：")+QString::number(used, 'f', 2)+QString(" 收入：")+QString::number(ined, 'f', 2));//显示收支总额
}
