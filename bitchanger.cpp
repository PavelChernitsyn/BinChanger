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
    bit_str_.clear();
    while(tmp)
    {
        if (tmp & 1)
            bit_str_.push_front('1');
        else
            bit_str_.push_front('0');
        tmp >>= 1;
    }

    //заполняем оставшиеся биты нулями
    while(bit_str_.size() != 8) bit_str_.push_front('0');

    emit bit_strChanged();

//    qDebug() << "get_bin_str = " << bit_str << " -> " << number;
}

void BitChanger::upd_hex_str()
{
    if (number == 0){
        hex_str_ = "0";
        emit hex_strChanged();
        return;
    }

    QString alphabet = "0123456789ABCDEF";
    uint tmp = number;
    hex_str_.clear();
    while(tmp)
    {
        hex_str_.push_front(alphabet[tmp & 15]);
        tmp >>= 4;
    }

    emit hex_strChanged();
}

QString BitChanger::bit_str() const
{
    return bit_str_;
}

QString BitChanger::hex_str() const
{
    return hex_str_;
}

void BitChanger::inverse()
{
//    qDebug() << "inverse: " << number << " -> " << (~number & 255);
    number = ~number;
    number = number & 255;
//    upd_bit_str();
    /*  upd_hex_str отправляет сигнал о том, что число поменялось *
     *  TextField.onChanged испускает сигнал об этом,             *
     *  вызывается set_number, который нам поменяет bin строку    */
    upd_hex_str();
}

bool BitChanger::on_off_bit(int index)
{
    index = 7 - index; //сопоставление элемента repeater нужному биту
    uint mask = 1 << index;
    bool flag; //true, если бит изменен на вкл, false если на выкл

    if(number & mask) {
        mask = ~mask;
        mask = mask & 255;
        number = number & mask;
        flag = false;
    } else {
        number = number | mask;
        flag = true;
    }
//    upd_bit_str();
    /*  upd_hex_str отправляет сигнал о том, что число поменялось *
     *  TextField.onChanged испускает сигнал об этом,             *
     *  вызывается set_number, который нам поменяет bin строку    */
    upd_hex_str();
    return flag;
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
//    upd_bit_str();
    /*  upd_hex_str отправляет сигнал о том, что число поменялось *
     *  TextField.onChanged испускает сигнал об этом,             *
     *  вызывается set_number, который нам поменяет bin строку    */
    upd_hex_str();
}

bool BitChanger::get_bit_state(int index) const
{
    index = 7 - index;
    uint mask = 1 << index;

    if(number & mask) return true;
    return false;
}

void BitChanger::set_number(QString text)
{
    bool ok;
    number = text.toUInt(&ok, 16);
    upd_bit_str();
//    qDebug() << "Text = " << text << " -> " << number;
}
