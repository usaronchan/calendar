#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// 判断是否为闰年
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取指定月份的天数
int getDaysInMonth(int month, int year)
{
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }
    return days[month - 1];
}

// 获取指定日期是星期几（0 - 6，0 表示星期日）
int getDayOfWeek(int day, int month, int year)
{
    if (month < 3)
    {
        month += 12;
        --year;
    }
    int c = year / 100;
    int y = year % 100;
    int w = (c / 4 - 2 * c + y + y / 4 + 13 * (month + 1) / 5 + day - 1) % 7;
    return (w + 7) % 7;
}

// 打印单个月标题，宽度 20
void printMonthTitle(int month, int year)
{
    static const std::vector<std::string> monthNames = {
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"};
    std::ostringstream oss;
    oss << monthNames[month - 1] << " " << year;
    std::string title = oss.str();
    int totalWidth = 20;
    int padding = (totalWidth - title.size()) / 2;
    std::cout << std::string(padding, ' ') << title << std::string(totalWidth - padding - title.size(), ' ');
}

// 打印星期表头
void printWeekHeader()
{
    std::cout << " 日 一 二 三 四 五 六  ";
}

// 打印一行三个连续月
void printQuarter(int startMonth, int year)
{
    // 标题行
    for (int i = 0; i < 3; ++i)
    {
        printMonthTitle(startMonth + i, year);
        if (i < 2)
            std::cout << "  ";
    }
    std::cout << '\n';
    // 星期表头
    for (int i = 0; i < 3; ++i)
    {
        printWeekHeader();
        if (i < 2)
            std::cout << "  ";
    }
    std::cout << '\n';

    // 计算首日和天数
    int firstDay[3], daysInMon[3];
    for (int i = 0; i < 3; ++i)
    {
        firstDay[i] = getDayOfWeek(1, startMonth + i, year);
        daysInMon[i] = getDaysInMonth(startMonth + i, year);
    }

    // 打印 6 周
    for (int week = 0; week < 6; ++week)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int dow = 0; dow < 7; ++dow)
            {
                int day = week * 7 + dow - firstDay[i] + 1;
                if (day >= 1 && day <= daysInMon[i])
                {
                    std::cout << std::setw(3) << day;
                }
                else
                {
                    std::cout << "   ";
                }
            }
            if (i < 2)
                std::cout << "  ";
        }
        std::cout << '\n';
    }
}

int main()
{
    int year;
    std::cout << "请输入要显示日历的年份: ";
    if (!(std::cin >> year))
    {
        std::cerr << "输入无效！" << std::endl;
        return 1;
    }
    for (int m = 1; m <= 10; m += 3)
    {
        printQuarter(m, year);
        if (m < 10)
            std::cout << '\n';
    }
    return 0;
}
