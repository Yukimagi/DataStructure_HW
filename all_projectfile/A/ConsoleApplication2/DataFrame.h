#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
using namespace std;
//Date型別，打印時會印出長相，排序時會先照年月日順序排序。
struct Date
{
    string OriginalDate;
    int Year, month, day;
    Date();
};
//預設建構子，如果都沒定義會將OriginalDate設為"empty date"
Date::Date()
{
    OriginalDate = "empty date";
    Year = 0;
    month = 0;
    day = 0;
}
//運算子多載，用來判斷是否等於
bool operator==(const Date& a, const Date& b)
{
    return  (a.Year == b.Year && a.month == b.month && a.day == b.day);
}
//運算子多載，用來判斷是否不等於
bool operator!=(const Date& a, const Date& b)
{
    if (a.Year != b.Year)return true;
    if (a.month != b.month)return true;
    return a.day != b.day;
}
bool operator<(const Date& a, const Date& b)
{
    if (a.Year != b.Year)return a.Year < b.Year;
    if (a.month != b.month)return a.month < b.month;
    return a.day < b.day;
}
//運算子多載，用來判斷是否小於，用於排序
bool operator>(const Date& a, const Date& b)
{
    if (a.Year != b.Year)return a.Year > b.Year;
    if (a.month != b.month)return a.month > b.month;
    return a.day > b.day;
}
//運算子多載，定義Date結構該怎麼輸入
//在讀取資料時解析資料表，將年月日等欄位轉成數字
istream& operator>>(istream& xin, Date& a)
{
    xin >> a.OriginalDate;
    a.Year = stoi(a.OriginalDate.substr(0, 4));
    a.month = stoi(a.OriginalDate.substr(4, 2));
    a.day = stoi(a.OriginalDate.substr(6, 2));
    return xin;
}
//運算子多載，定義Date結構該怎麼輸出
//直接輸出原本的樣子
ostream& operator<<(ostream& xout, const Date& a)
{
    return xout << a.OriginalDate;
}
//資料表型別，分別記載開盤價格、當日最高價、當日最低價、收盤價格。
struct DataFrame
{
    Date d;
    double Open_price, High_price, Low_price, Close_price;
    DataFrame();
};
//預設建構子，如果都沒定義會將所有price都設為-1
DataFrame::DataFrame()
{
    Open_price = -1;
    High_price = -1;
    Low_price = -1;
    Close_price = -1;
}
//運算子多載，定義DataFrame結構該怎麼輸出
//會分別印出日期、開盤價格、當日最高價、當日最低價、收盤價格。
ostream& operator<<(ostream& xout, const DataFrame& a)
{
    return xout << a.d << " " << a.Open_price << " " << a.High_price << " " << a.Low_price << " " << a.Close_price;
}
//運算子多載，定義DataFrame結構是否不相等
bool operator!=(const DataFrame& a, const DataFrame& b)
{
    return (a.d != b.d) || (a.Close_price != b.Close_price) || (a.High_price != b.High_price) || (a.Low_price != b.Low_price) || (a.Open_price != b.Open_price);
}
//第二種資料表型別，用來做第10題用。
struct DataFrame2
{
    Date d;
    double price;
    DataFrame2();
};
//預設建構子，如果都沒設定price為-1
DataFrame2::DataFrame2()
{
    price = -1;
}
//運算子多載，定義DataFrame2的輸出
ostream& operator<<(ostream& xout, const DataFrame2& a)
{
    return xout << a.d << " " << a.price;
}
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據收盤價格從小到大排序。
struct compareWithclose_price
{
    bool operator()(const DataFrame& a, const DataFrame& b)
    {
        return a.Close_price < b.Close_price;
    }
};
//函數物件，DataFrame用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據日期從小到大排序。
struct compareWithDate
{
    bool operator()(const DataFrame& a, const DataFrame& b)
    {
        return a.d < b.d;
    }
};
//函數物件，DataFrame2用來表示排序時的比較方法，將HeapSortClass的用這個表示就是根據價格從小到大排序。
struct cmpforprice
{
    bool operator()(const DataFrame2& a, const DataFrame2& b)
    {
        if (a.price != b.price)return a.price < b.price;
        return a.d < b.d;
    }
};