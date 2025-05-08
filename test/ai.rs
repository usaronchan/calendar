use std::io;

// 判断是否为闰年
fn is_leap_year(year : i32) -> bool{
    (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)}

// 获取指定月份的天数
fn days_in_month(month : usize, year : i32)
    ->usize
{
    let days = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];
    if month
        == 2 && is_leap_year(year){
                    29} else
        {
            days[month - 1]
        }
}

// 获取指定日期是星期几（0 - 6，0 表示星期日）
fn day_of_week(day : i32, month : i32, year : i32) -> usize
{
    let(m, y) = if month < 3
    {
        (month + 12, year - 1)
    }
    else {
        (month, year)};
    let c = y / 100;
    let d = y % 100;
    let w = (c / 4 - 2 * c + d + d / 4 + (13 * (m + 1)) / 5 + day - 1) % 7;
    ((w + 7) % 7) as usize
}

// 打印单个月标题，宽度 20
fn print_month_title(month : usize, year : i32)
{
    let names = [
        "一月",
        "二月",
        "三月",
        "四月",
        "五月",
        "六月",
        "七月",
        "八月",
        "九月",
        "十月",
        "十一月",
        "十二月",
    ];
    let title = format !("{} {}", names[month - 1], year);
    let total_width = 20;
    let pad = (total_width - title.chars().count()) / 2;
    print !("{}{}{}", " ".repeat(pad), title, " ".repeat(total_width - pad - title.chars().count()));
}

// 打印星期表头
fn print_week_header()
{
    print !(" 日 一 二 三 四 五 六  ");
}

// 打印一行三个连续月
fn print_quarter(start_month : usize, year : i32)
{
    // 标题行
    for
        i in 0..3
        {
            print_month_title(start_month + i, year);
            if i
                < 2 { print !("  "); }
        }
    println !();

    // 星期表头
    for
        i in 0..3
        {
            print_week_header();
            if i
                < 2 { print !("  "); }
        }
    println !();

    // 计算首日与天数
    let mut first = [0; 3];
    let mut days = [0; 3];
    for
        i in 0..3
        {
            first[i] = day_of_week(1, (start_month + i) as i32, year);
            days[i] = days_in_month(start_month + i, year) as i32;
        }

    // 打印最多 6 行
    for
        week in 0..6
        {
        for
            i in 0..3
            {
            for
                dow in 0..7
                {
                    let day = week * 7 + dow as usize + 1 - first[i] as usize;
                    if day
                        >= 1 && (day as i32) <= days[i]
                        {
                            print !("{:>3}", day);
                        }
                    else
                    {
                        print !("   ");
                    }
                }
            if i
                < 2 { print !("  "); }
            }
        println !();
        }
}

fn main()
{
    let mut input = String::new ();
    println !("请输入要显示日历的年份: ");
    io::stdin().read_line(&mut input).unwrap();
    let year : i32 = input.trim().parse().expect("请输入一个有效的年份");

    for
        m in(1.. 12).step_by(3)
        {
            print_quarter(m, year);
            if m
                < 10 { println !(); }
        }
}