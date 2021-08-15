#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
using std::vector;
using std::endl;
vector<LINE> ve;
int op;
MDATE start, endm;

void readBitFile()//读二进制文件
{
    ifstream in;
    LINE tmp;
    in.open("record.dat", ios::binary | ios::in);
    if (!in) return ;
    while(!in.eof())
    {
        in.read((char*)&tmp, sizeof(tmp));
        ve.push_back(tmp);
    }
    ve.pop_back();//会多读一条，即最后一条重复，原因未知
    in.close();
    sort(ve.begin(), ve.end());//按日期排序
}
void writeBitFile()//写二进制文件，比文本文件快还省空间
{
    ofstream out;
    out.open("record.dat", ios::binary | ios::out);
    for(auto i:ve)
    {
        out.write((char*)&i, sizeof(LINE));
    }
    out.close();
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //MDATE a(2021, 7, 14, 17, 58), b(2021, 7, 13, 23, 59);
    ui->setupUi(this);
    op = 0;//在limit.cpp中被使用
    QDate a = QDate::currentDate();//获取当前系统时间
    endm = {a.year(), a.month(), a.day(), 23, 59};//查看历史界面默认的搜索的最晚时间，即今天
    start = {a.year(), a.month(), 1, 0, 0};//最早时间，即本月1号 即默认为显示本月所有收支记录
    readBitFile();//从文件中读取数据
//    printf("%d\n", ve.size());
}

MainWindow::~MainWindow()
{
    delete ui;
    writeBitFile();//将数据写入文件
}

void MainWindow::on_pushButton_clicked()
{
    AddFrom *v = new AddFrom();//创建记一笔界面
    v->show();//显示界面
    this->hide();//隐藏当前界面
    connect(v, SIGNAL(ExitWin()), this, SLOT(show()));//当记一笔界面关闭时，当前界面打开
}

void MainWindow::on_pushButton_2_clicked()
{
    His *v = new His();//创建看历史界面
    v->show();//显示界面
    this->hide();//隐藏当前界面
    connect(v, SIGNAL(ExitWin()), this, SLOT(show()));//当看历史界面关闭时，当前界面打开
}
