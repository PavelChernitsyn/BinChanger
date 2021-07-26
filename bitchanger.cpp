#include "bitchanger.h"
#include <QDebug>

BitChanger::BitChanger(QObject *parent) : QObject(parent), number(0)
{
    upd_bit_str();
    upd_hex_str();
}

void BitChanger::upd_bit_str()
{
    uint tmp = number;
    bit_str.clear();
    while(tmp)
    {
        if (tmp & 1)
            bit_str.push_front('1');
        else
            bit_str.push_front('0');
        tmp >>= 1;
    }

    //заполняем оставшиеся биты нулями
    while(bit_str.size() != 8) bit_str.push_front('0');

    emit bit_strChanged();

//    qDebug() << "get_bin_str = " << bit_str << " -> " << number;
}

void BitChanger::upd_hex_str()
{
    if (number == 0){
        hex_str = "0";
        emit hex_strChanged();
        return;
    }

    QString alphabet = "0123456789ABCDEF";
    uint tmp = number;
    hex_str.clear();
    while(tmp)
    {
        hex_str.push_front(alphabet[tmp & 15]);
        tmp >>= 4;
    }

    emit hex_strChanged();
}

QString BitChanger::get_bin_str_num() const
{
    return bit_str;
}

QString BitChanger::get_hex_str_num() const
{
    return hex_str;
}

void BitChanger::inverse()
{
//    qDebug() << "inverse: " << number << " -> " << (~number & 255);
    number = ~number;
    number = number & 255;
    upd_bit_str();
    upd_hex_str();
}

void BitChanger::on_bit(QString text)
{
    if (text.isEmpty()) return;

    uint index = text.toUInt(nullptr, 10);
    uint mask = 1 << index;
    number = number | mask;
    upd_bit_str();
    upd_hex_str();
}

void BitChanger::off_bit(QString text)
{
    if (text.isEmpty()) return;

    uint index = text.toUInt(nullptr, 10);
    uint mask = 1 << index;
    mask = ~mask;
    mask = mask & 255;
    number = number & mask;
    upd_bit_str();
    upd_hex_str();
}

void BitChanger::sum_from_file(QString filepath)
{
    QFile file(filepath);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading!";
        return;
    }

    QTextStream in(&file);

    size_t i = 0;
    uint tmp = number;
    bool ok;
    while (i != 3 && !in.atEnd())
    {
        QString line = in.readLine();
        uint next_num = line.toUInt(&ok, 10);
        if (!ok || next_num > 100)
        {
            qDebug() << "Incorrect numbers in file!";
            return;
        }
        tmp += next_num;
        ++i;
    }

    file.close();

    if (i != 3) //значит в файле было меньше 3 чисел
    {
        qDebug() << "<3 numbers in file!";
        return;
    }

    number = tmp & 255;
    upd_bit_str();
    upd_hex_str();
}

void BitChanger::set_number(QString text)
{
    bool ok;
    number = text.toUInt(&ok, 16);
    upd_bit_str();
//    qDebug() << "Text = " << text << " -> " << number;
}
