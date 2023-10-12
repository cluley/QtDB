#ifndef DBLOG_H
#define DBLOG_H

#include <QDialog>

namespace Ui {
class DBLog;
}

class DBLog : public QDialog
{
    Q_OBJECT

public:
    explicit DBLog(QWidget *parent = nullptr);
    ~DBLog();

signals:
   void sig_sendData(QVector<QString> dbData);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DBLog *ui;
    QVector<QString> data;

};

#endif // DBLOG_H
