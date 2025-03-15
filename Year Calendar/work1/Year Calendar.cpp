#include <iostream>
#include <iomanip>
using namespace std;

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;

    // 判断是否是闰年
    static bool IsLeapYear(unsigned year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // 获取某年某月的天数
    static unsigned GetDaysInMonth(unsigned year, unsigned month) {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return IsLeapYear(year) ? 29 : 28;
        default: return 0;
        }
    }

    // 计算某年某月1日是星期几（0表示周一）
    unsigned CalculateFirstDayOfWeek() const {
        unsigned totalDays = 0;
        // 累加从1900年到当前年份之前的所有天数
        for (unsigned y = 1900; y < year; ++y) {
            totalDays += IsLeapYear(y) ? 366 : 365;
        }
        // 累加当前年份中到当前月份之前的所有天数
        for (unsigned m = 1; m < month; ++m) {
            totalDays += GetDaysInMonth(year, m);
        }
        return totalDays % 7; // 0表示周一
    }

    // 计算某年某月1日是星期几（0表示周一）
    unsigned UnknownMonthCalculate( unsigned month) const {
        unsigned totalDays = 0;
        // 累加从1900年到当前年份之前的所有天数
        for (unsigned y = 1900; y < year; ++y) {
            totalDays += IsLeapYear(y) ? 366 : 365;
        }
        // 累加当前年份中到当前月份之前的所有天数
        for (unsigned m = 1; m < month; ++m) {
            totalDays += GetDaysInMonth(year, m);
        }
        return totalDays % 7; // 0表示周一
    }

public:
    // 设置年份
    void SetYear(unsigned y) { year = y; }
    // 设置月份
    void SetMonth(unsigned m) { month = m; }
    // 设置日期
    void SetDay(unsigned d) { day = d; }

    // 判断日期是否有效
    bool Valid() const {
        if (year < 1900) return false; // 年份不能小于1900
        if (month < 1 || month > 12) return false; // 月份必须在1到12之间
        if (day < 1 || day > GetDaysInMonth(year, month)) return false; // 日期必须在有效范围内
        return true;
    }

    // 获取年份
    unsigned GetYear() const { return year; }
    // 获取月份
    unsigned GetMonth() const { return month; }
    // 获取日期
    unsigned GetDay() const { return day; }

    // 显示日期（格式：YYYY-MM-DD）
    void Display() const {
        cout << year << "-"
            << setw(2) << setfill('0') << month << "-"
            << setw(2) << day << endl;
    }

    // 显示指定月份的日历
    void DisplayMonthCalendar() const {
        if (!Valid()) {
            cout << "Invalid date!" << endl;
            return;
        }

        unsigned days = GetDaysInMonth(year, month);
        unsigned firstDay = CalculateFirstDayOfWeek(); // 计算1日是星期几

        // 输出表头
        cout << "                "<<year<<"-"<<month << endl;
        cout << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << endl;

        // 输出前导空格
        //cout<< "   ";
        for (unsigned i = 0; i < firstDay; ++i) {
            cout << "     ";
        }

        // 输出日期
        for (unsigned d = 1; d <= 9; ++d) {
            cout << "   " <<"0"<<d;
            // 如果是周六（索引6）则换行
            if ((firstDay + d - 1) % 7 == 6) {
                cout << endl;
            }
        }

        for (unsigned d = 10; d <= days; ++d) {
            cout << "   " <<d;
            // 如果是周六（索引6）则换行
            if ((firstDay + d - 1) % 7 == 6) {
                cout << endl;
            }
        }
        // 如果最后一行没有满，需要换行
        if ((firstDay + days - 1) % 7 != 6) {
            cout << endl;
        }
    }

    void DisplayYearCalendar() const
    {
        if (!Valid()) {
            cout << "Invalid date!" << endl;
            return;
        }
        unsigned monthx = 1;
        unsigned da[3]= { 1,1,1 };
        // 输出表头
        for ( monthx = 1; monthx < 12; monthx += 3) {
            unsigned pan = 0;
            cout << "                " << year << "-" << monthx << "                              " << year << "-" << monthx + 1 << "                              " << year << "-" << monthx + 2 << endl;
            cout << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << endl;
            for (unsigned k = 1; k <= 6; ++k) {
                for (unsigned i = 1; i <= 3; ++i) {
                    unsigned firstDay = UnknownMonthCalculate(monthx + i - 1); // 计算1日是星期几
                    unsigned days = GetDaysInMonth(year, monthx + i - 1);
                    //cout<<firstDay<<days<<endl;
                    if (pan == 0) {
                        for (unsigned j = 0; j < firstDay; ++j) {
                            cout << "     ";
                        }
                    }
                    unsigned hh = 0;
                    if (k == 6) {
                        for (unsigned p = 1;p <= 3;p++) {
                            if (da[i - 1] > days) {
                                cout << "            ";
                            }
                            if (da[i - 1] <= days) {
                                for (unsigned d = da[i - 1]; d <= days; ++d) {
                                    cout << "   " << d;
                                    if (d == days) {
                                        da[i - 1] = d + 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    for (unsigned d = da[i - 1]; d <= 9; ++d) {
                        cout << "   " << "0" << d;
                        
                        // 如果是周六（索引6）则换行
                        if ((firstDay + d - 1) % 7 == 6) {
                            cout << " ";
                            da[i - 1] = d+1;
                            hh = 1;
                            break;
                        }
                        if (d == 9) {
                            da[i - 1] = d + 1;
                            break;
                        }
                    }
                    //cout << da[i - 1] << endl;
                    if (da[i - 1] > 9 && hh == 0) {
                        for (unsigned d = da[i-1]; d <= days; ++d) {
                            cout << "   " << d;
                            // 如果是周六（索引6）则换行
                            if ((firstDay + d - 1) % 7 == 6) {
                                cout << " ";
                                da[i - 1] = d+1;
                                break;
                            }
                            if (d == days) {
                                da[i - 1] = d + 1;
                                unsigned yu = 6 - ((firstDay + d - 1) % 7);
                                for (unsigned t = 0; t < yu; ++t) {
                                    cout << "     ";
                                }
                                cout << " ";
                                break;
                            }
                        }
                    }
                    
                    if (i == 3) {
                        pan = 1;
                        cout << endl;
                    }
                }
            }
            da[0]=da[1]=da[2]=1;
        }
    }

};



int main() {
    Date date;
    unsigned y, m, d;
    char judge;
    char judge0;
    while (1) {
        cout << "Input year(year>=1900):";
        cin >> y;
        cout << "Input month(1<=month<=12):";
        cin >> m;
        cout << "Input day(1<=day<=31):";
        cin >> d;

        date.SetYear(y);
        date.SetMonth(m);
        date.SetDay(d);
        bool inputValid = false;

        if (date.Valid()) {
            cout << "Date is：" << endl;
            date.Display();
            cout << "Calendar：" << endl;
            date.DisplayMonthCalendar();
            do {
                cout << "Year Calendar?(Y/N)" << endl;
                cin >> judge0;

                if (judge0 == 'Y' || judge0 == 'N') {
                    inputValid = true; // 输入有效，退出循环
                }
                else {
                    cout << "Please enter Y or N." << endl;
                }
            } while (!inputValid);
            if (judge0 == 'Y') {
                date.DisplayYearCalendar();
            }
        }
        else {
            cout << "输入的日期无效！" << endl;
        }
        bool validInput = false;

        do {
            cout << "Continue?(Y/N)" << endl;
            cin >> judge;

            if (judge == 'Y' || judge == 'N') {
                validInput = true; // 输入有效，退出循环
            }
            else {
                cout << "Please enter Y or N." << endl;
            }
        } while (!validInput);

        if (judge == 'N') {
            break;
        }
    }

    return 0;
}