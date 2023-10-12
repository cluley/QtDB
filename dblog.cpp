#include "dblog.h"
#include "database.h"
#include "ui_dblog.h"

DBLog::DBLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBLog)
{
    ui->setupUi(this);

    ui->le_hostName->setText("981757-ca08998.tmweb.ru");
    ui->le_dbName->setText("netology_cpp");
    ui->le_login->setText("netology_usr_cpp");
    ui->le_password->setText("CppNeto3");
    ui->sb_connProt->setValue(5432);

    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
}

DBLog::~DBLog()
{
    delete ui;
}

void DBLog::on_buttonBox_accepted()
{

    data[hostName] = ui->le_hostName->text();
    data[dbName] = ui->le_dbName->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_password->text();
    data[port] = ui->sb_connProt->text();

    emit sig_sendData(data);

}
