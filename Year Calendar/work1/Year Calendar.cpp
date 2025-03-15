#include <iostream>
#include <iomanip>
using namespace std;

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;

    // �ж��Ƿ�������
    static bool IsLeapYear(unsigned year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // ��ȡĳ��ĳ�µ�����
    static unsigned GetDaysInMonth(unsigned year, unsigned month) {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return IsLeapYear(year) ? 29 : 28;
        default: return 0;
        }
    }

    // ����ĳ��ĳ��1�������ڼ���0��ʾ��һ��
    unsigned CalculateFirstDayOfWeek() const {
        unsigned totalDays = 0;
        // �ۼӴ�1900�굽��ǰ���֮ǰ����������
        for (unsigned y = 1900; y < year; ++y) {
            totalDays += IsLeapYear(y) ? 366 : 365;
        }
        // �ۼӵ�ǰ����е���ǰ�·�֮ǰ����������
        for (unsigned m = 1; m < month; ++m) {
            totalDays += GetDaysInMonth(year, m);
        }
        return totalDays % 7; // 0��ʾ��һ
    }

    // ����ĳ��ĳ��1�������ڼ���0��ʾ��һ��
    unsigned UnknownMonthCalculate( unsigned month) const {
        unsigned totalDays = 0;
        // �ۼӴ�1900�굽��ǰ���֮ǰ����������
        for (unsigned y = 1900; y < year; ++y) {
            totalDays += IsLeapYear(y) ? 366 : 365;
        }
        // �ۼӵ�ǰ����е���ǰ�·�֮ǰ����������
        for (unsigned m = 1; m < month; ++m) {
            totalDays += GetDaysInMonth(year, m);
        }
        return totalDays % 7; // 0��ʾ��һ
    }

public:
    // �������
    void SetYear(unsigned y) { year = y; }
    // �����·�
    void SetMonth(unsigned m) { month = m; }
    // ��������
    void SetDay(unsigned d) { day = d; }

    // �ж������Ƿ���Ч
    bool Valid() const {
        if (year < 1900) return false; // ��ݲ���С��1900
        if (month < 1 || month > 12) return false; // �·ݱ�����1��12֮��
        if (day < 1 || day > GetDaysInMonth(year, month)) return false; // ���ڱ�������Ч��Χ��
        return true;
    }

    // ��ȡ���
    unsigned GetYear() const { return year; }
    // ��ȡ�·�
    unsigned GetMonth() const { return month; }
    // ��ȡ����
    unsigned GetDay() const { return day; }

    // ��ʾ���ڣ���ʽ��YYYY-MM-DD��
    void Display() const {
        cout << year << "-"
            << setw(2) << setfill('0') << month << "-"
            << setw(2) << day << endl;
    }

    // ��ʾָ���·ݵ�����
    void DisplayMonthCalendar() const {
        if (!Valid()) {
            cout << "Invalid date!" << endl;
            return;
        }

        unsigned days = GetDaysInMonth(year, month);
        unsigned firstDay = CalculateFirstDayOfWeek(); // ����1�������ڼ�

        // �����ͷ
        cout << "                "<<year<<"-"<<month << endl;
        cout << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << endl;

        // ���ǰ���ո�
        //cout<< "   ";
        for (unsigned i = 0; i < firstDay; ++i) {
            cout << "     ";
        }

        // �������
        for (unsigned d = 1; d <= 9; ++d) {
            cout << "   " <<"0"<<d;
            // ���������������6������
            if ((firstDay + d - 1) % 7 == 6) {
                cout << endl;
            }
        }

        for (unsigned d = 10; d <= days; ++d) {
            cout << "   " <<d;
            // ���������������6������
            if ((firstDay + d - 1) % 7 == 6) {
                cout << endl;
            }
        }
        // ������һ��û��������Ҫ����
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
        // �����ͷ
        for ( monthx = 1; monthx < 12; monthx += 3) {
            unsigned pan = 0;
            cout << "                " << year << "-" << monthx << "                              " << year << "-" << monthx + 1 << "                              " << year << "-" << monthx + 2 << endl;
            cout << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << "   Mon  Tue  Wed  Thu  Fri  Sat  Sun" << endl;
            for (unsigned k = 1; k <= 6; ++k) {
                for (unsigned i = 1; i <= 3; ++i) {
                    unsigned firstDay = UnknownMonthCalculate(monthx + i - 1); // ����1�������ڼ�
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
                        
                        // ���������������6������
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
                            // ���������������6������
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
            cout << "Date is��" << endl;
            date.Display();
            cout << "Calendar��" << endl;
            date.DisplayMonthCalendar();
            do {
                cout << "Year Calendar?(Y/N)" << endl;
                cin >> judge0;

                if (judge0 == 'Y' || judge0 == 'N') {
                    inputValid = true; // ������Ч���˳�ѭ��
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
            cout << "�����������Ч��" << endl;
        }
        bool validInput = false;

        do {
            cout << "Continue?(Y/N)" << endl;
            cin >> judge;

            if (judge == 'Y' || judge == 'N') {
                validInput = true; // ������Ч���˳�ѭ��
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