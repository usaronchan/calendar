#include <stdio.h>
#include <stdlib.h>

// 判断是否为闰年
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取指定月份的天数
int getDaysInMonth(int month, int year)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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
        year--;
    }
    int c = year / 100;
    year %= 100;
    int w = (c / 4 - 2 * c + year + year / 4 + 13 * (month + 1) / 5 + day - 1) % 7;
    return (w + 7) % 7;
}

// 打印单个月的日历标题（如“   一月 2025   ”，宽度 20）
void printMonthTitle(int month, int year)
{
    const char *monthNames[] = {
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"};
    // 居中显示，总宽度 20
    printf("     %s %4d     ", monthNames[month - 1], year);
}

// 打印单个月的星期表头（宽度 20）
void printWeekHeader()
{
    printf(" 日 一 二 三 四 五 六  ");
}

// 打印从 startMonth 开始的 3 个月（一个季度）并排的日历
void printQuarter(int startMonth, int year)
{
    // 1. 标题行
    for (int i = 0; i < 3; i++)
    {
        printMonthTitle(startMonth + i, year);
        if (i < 2)
            printf("  "); // 月份间留两个空格
    }
    printf("\n");

    // 2. 星期表头行
    for (int i = 0; i < 3; i++)
    {
        printWeekHeader();
        if (i < 2)
            printf("  ");
    }
    printf("\n");

    // 3. 预先计算三个当月的首日偏移和天数
    int firstDay[3], daysInMon[3];
    for (int i = 0; i < 3; i++)
    {
        int m = startMonth + i;
        firstDay[i] = getDayOfWeek(1, m, year);
        daysInMon[i] = getDaysInMonth(m, year);
    }

    // 4. 按 6 行（星期）打印内容
    for (int week = 0; week < 6; week++)
    {
        for (int i = 0; i < 3; i++)
        {
            // 对当前月的这一周，遍历周日(0)到周六(6)
            for (int dow = 0; dow < 7; dow++)
            {
                int dayNum = week * 7 + dow - firstDay[i] + 1;
                if (dayNum >= 1 && dayNum <= daysInMon[i])
                {
                    printf("%3d", dayNum);
                }
                else
                {
                    printf("   ");
                }
            }
            if (i < 2)
                printf("  "); // 月份间留两个空格
        }
        printf("\n");
    }
}

int main()
{
    int year;
    printf("请输入要显示日历的年份: ");
    if (scanf("%d", &year) != 1)
    {
        fprintf(stderr, "输入无效！\n");
        return 1;
    }

    for (int start = 1; start <= 10; start += 3)
    {
        printQuarter(start, year);
        if (start < 10)
            printf("\n"); // 季度之间空一行
    }

    return 0;
}
