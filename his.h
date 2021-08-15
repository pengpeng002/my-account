#ifndef HIS_H
#define HIS_H
//看历史界面
#include <QWidget>
#include <QStatusBar>
#include <set>
#include "data.h"
#include "limit.h"

namespace Ui {
class His;
}

class His : public QWidget
{
    Q_OBJECT

public:
    explicit His(QWidget *parent = 0);
    ~His();
    void closeEvent(QCloseEvent*);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void myShow();

private:
    Ui::His *ui;
    QStatusBar *statusBar;//状态栏
    vector<int> sem;//所有被删除的行的id

signals:
    void ExitWin();
};

#endif // HIS_H
