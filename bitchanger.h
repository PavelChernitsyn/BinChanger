#ifndef BITCHANGER_H
#define BITCHANGER_H

#include <QObject>
#include <QString>
#include <QFile>

class BitChanger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bit_str READ bit_str WRITE set_number NOTIFY bit_strChanged)
    Q_PROPERTY(QString hex_str READ hex_str WRITE set_number NOTIFY hex_strChanged)

private:
    uint number;
    QString bit_str_;
    QString hex_str_;

    void upd_bit_str();
    void upd_hex_str();

public:
    explicit BitChanger(QObject *parent = nullptr);
    /*Q_INVOKABLE*/ QString bit_str() const;
    /*Q_INVOKABLE*/ QString hex_str() const;
    Q_INVOKABLE void inverse();
    Q_INVOKABLE bool on_off_bit(int);
    Q_INVOKABLE void sum_from_file(QString);
    Q_INVOKABLE bool get_bit_state(int) const;

signals:
    void bit_strChanged();
    void hex_strChanged();

public slots:
    void set_number(QString);
};

#endif // BITCHANGER_H
