#ifndef DATA_H
#define DATA_H
#include <string.h>
#include <string>
#include <vector>
using namespace std;
const int MAX_LEN = 1024;
struct MDATE//my date
{
    int year, month, day, hour, min;//年 月 日 时 分
    MDATE() {}
    MDATE(int a, int b, int c, int d, int e)
    {
        year=a, month=b, day=c, hour=d, min=e;
    }

    bool operator < (const MDATE &a) const//重载小于运算符
    {
        if (year < a.year) return true;
        if (year > a.year) return false;
        if (month < a.month) return true;
        if (month > a.month) return false;
        if (day < a.day) return true;
        if (day > a.day) return false;
        if (hour < a.hour) return true;
        if (hour > a.hour) return false;
        if (min < a.min) return true;
        return false;
    }

    bool operator == (const MDATE &a) const//等于运算符
    {
        return a.year == year && a.month == month && a.day == day && hour == a.hour && a.min == min;
    }

    friend bool operator <= (const MDATE &a, const MDATE &b)//小于等于运算符
    {
        return a<b || a==b;
    }

    friend bool operator > (const MDATE &a, const MDATE &b)//大于运算符
    {
        return !(a <= b);
    }

    friend bool operator >= (const MDATE &a, const MDATE &b)//大于等于运算符
    {
        return !(a<b);
    }

    void print(char c='\n')//debug时用来输出信息
    {
        printf("%04d-%02d-%02d %02d:%02d%c", year, month, day, hour, min, c);
    }

};
struct LINE//一条记录
{
    bool op;//收入/支出
    double num;//金额
    MDATE date;
    char info[MAX_LEN];//备注信息 最大1024

    LINE() {}
    LINE(bool a, double b, MDATE c, string d)
    {
        op = a;
        num = b;
        date = c;
        strcpy(info, d.c_str());
    }

    friend bool operator < (const LINE &a, const LINE &b)//重载小于运算符
    {
        return a.date < b.date;
    }

    void print()//debug时用来输出信息
    {
        printf("%s %.2lf %04d-%02d-%02d %02d:%02d %s\n", op?"true":"false", num, date.year, date.month, date.day, date.hour, date.min, info);
    }
};

struct TL//表中的一行
{
    LINE line;
    int id;
    TL(LINE line, int id): id(id), line(line) {}

    void print()
    {
        printf("id=%d ", id);
        line.print();
    }
};

extern vector<LINE> ve;//存储所有记录
extern int op;//收入/支出
extern MDATE start, endm;//搜索历史记录的开始与结束时间

#endif // DATA_H
