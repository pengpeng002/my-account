#ifndef ADDFROM_H
#define ADDFROM_H
//记一笔界面
#include <QWidget>
#include "data.h"
#include <QDateTime>
namespace Ui {
class AddFrom;
}

class AddFrom : public QWidget
{
    Q_OBJECT

public:
    explicit AddFrom(QWidget *parent = 0);
    ~AddFrom();
    void closeEvent(QCloseEvent*);
private slots:
    void on_pbok_clicked();

    void on_pbcancel_clicked();

private:
    Ui::AddFrom *ui;
signals:
    void ExitWin();
};

#endif // ADDFROM_H
