#ifndef BITCHANGER_H
#define BITCHANGER_H

#include <QObject>
#include <QString>
#include <QFile>

class BitChanger : public QObject
{
    Q_OBJECT

private:
    uint number;
    QString bit_str;
    QString hex_str;

    void upd_bit_str();
    void upd_hex_str();

public:
    explicit BitChanger(QObject *parent = nullptr);
    Q_INVOKABLE QString get_bin_str_num() const;
    Q_INVOKABLE QString get_hex_str_num() const;
    Q_INVOKABLE void inverse();
//    Q_INVOKABLE void on_bit(QString);
//    Q_INVOKABLE void off_bit(QString);
    Q_INVOKABLE bool on_off_bit(QString);
    Q_INVOKABLE void sum_from_file(QString);

signals:
    void bit_strChanged();
    void hex_strChanged();

public slots:
    void set_number(QString);
};

#endif // BITCHANGER_H
