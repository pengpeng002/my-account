#ifndef LIMIT_H
#define LIMIT_H
//搜索界面
#include <QWidget>
#include <QDate>
#include "data.h"

namespace Ui {
class Limit;
}

class Limit : public QWidget
{
    Q_OBJECT

public:
    explicit Limit(QWidget *parent = 0);
    ~Limit();
    void closeEvent(QCloseEvent*);

private:
    Ui::Limit *ui;
signals:
    void ExitWin();
private slots:
    void on_dateEdit_2_dateChanged(const QDate &date);
    void on_dateEdit_dateChanged(const QDate &date);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

extern int op;
extern MDATE start, endm;

#endif // LIMIT_H
