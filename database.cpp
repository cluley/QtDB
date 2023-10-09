#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    qModel = new QSqlQueryModel();
    tModel = new QSqlTableModel();
    view = new QTableView();

}

DataBase::~DataBase()
{
    delete dataBase;
    delete qModel;
    delete tModel;
    delete view;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    ///Тут должен быть код ДЗ


    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}

void DataBase::ReadAnswerFromDB()
{
    view->setModel(qModel);
    view->setWindowTitle("ПоискКино");
    view->show();

}


/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request)
{

    qModel->setQuery(request);
    qModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Название фильма"));
    qModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Описание фильма"));

    QSqlError err;
    if (qModel->lastError().isValid()){
            err = qModel->lastError();
    }

    emit sig_SendStatusRequest(err);
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}



