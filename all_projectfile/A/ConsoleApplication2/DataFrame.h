#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cfloat>
using namespace std;
//Date���O�A���L�ɷ|�L�X���ۡA�ƧǮɷ|���Ӧ~��鶶�ǱƧǡC
struct Date
{
    string OriginalDate;
    int Year, month, day;
    Date();
};
//�w�]�غc�l�A�p�G���S�w�q�|�NOriginalDate�]��"empty date"
Date::Date()
{
    OriginalDate = "empty date";
    Year = 0;
    month = 0;
    day = 0;
}
//�B��l�h���A�ΨӧP�_�O�_����
bool operator==(const Date& a, const Date& b)
{
    return  (a.Year == b.Year && a.month == b.month && a.day == b.day);
}
//�B��l�h���A�ΨӧP�_�O�_������
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
//�B��l�h���A�ΨӧP�_�O�_�p��A�Ω�Ƨ�
bool operator>(const Date& a, const Date& b)
{
    if (a.Year != b.Year)return a.Year > b.Year;
    if (a.month != b.month)return a.month > b.month;
    return a.day > b.day;
}
//�B��l�h���A�w�qDate���c�ӫ���J
//�bŪ����ƮɸѪR��ƪ�A�N�~��鵥����ন�Ʀr
istream& operator>>(istream& xin, Date& a)
{
    xin >> a.OriginalDate;
    a.Year = stoi(a.OriginalDate.substr(0, 4));
    a.month = stoi(a.OriginalDate.substr(4, 2));
    a.day = stoi(a.OriginalDate.substr(6, 2));
    return xin;
}
//�B��l�h���A�w�qDate���c�ӫ���X
//������X�쥻���ˤl
ostream& operator<<(ostream& xout, const Date& a)
{
    return xout << a.OriginalDate;
}
//��ƪ��O�A���O�O���}�L����B���̰����B���̧C���B���L����C
struct DataFrame
{
    Date d;
    double Open_price, High_price, Low_price, Close_price;
    DataFrame();
};
//�w�]�غc�l�A�p�G���S�w�q�|�N�Ҧ�price���]��-1
DataFrame::DataFrame()
{
    Open_price = -1;
    High_price = -1;
    Low_price = -1;
    Close_price = -1;
}
//�B��l�h���A�w�qDataFrame���c�ӫ���X
//�|���O�L�X����B�}�L����B���̰����B���̧C���B���L����C
ostream& operator<<(ostream& xout, const DataFrame& a)
{
    return xout << a.d << " " << a.Open_price << " " << a.High_price << " " << a.Low_price << " " << a.Close_price;
}
//�B��l�h���A�w�qDataFrame���c�O�_���۵�
bool operator!=(const DataFrame& a, const DataFrame& b)
{
    return (a.d != b.d) || (a.Close_price != b.Close_price) || (a.High_price != b.High_price) || (a.Low_price != b.Low_price) || (a.Open_price != b.Open_price);
}
//�ĤG�ظ�ƪ��O�A�ΨӰ���10�D�ΡC
struct DataFrame2
{
    Date d;
    double price;
    DataFrame2();
};
//�w�]�غc�l�A�p�G���S�]�wprice��-1
DataFrame2::DataFrame2()
{
    price = -1;
}
//�B��l�h���A�w�qDataFrame2����X
ostream& operator<<(ostream& xout, const DataFrame2& a)
{
    return xout << a.d << " " << a.price;
}
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھڦ��L����q�p��j�ƧǡC
struct compareWithclose_price
{
    bool operator()(const DataFrame& a, const DataFrame& b)
    {
        return a.Close_price < b.Close_price;
    }
};
//��ƪ���ADataFrame�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھڤ���q�p��j�ƧǡC
struct compareWithDate
{
    bool operator()(const DataFrame& a, const DataFrame& b)
    {
        return a.d < b.d;
    }
};
//��ƪ���ADataFrame2�ΨӪ�ܱƧǮɪ������k�A�NHeapSortClass���γo�Ӫ�ܴN�O�ھڻ���q�p��j�ƧǡC
struct cmpforprice
{
    bool operator()(const DataFrame2& a, const DataFrame2& b)
    {
        if (a.price != b.price)return a.price < b.price;
        return a.d < b.d;
    }
};