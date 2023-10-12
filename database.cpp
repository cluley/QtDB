#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    qModel = new QSqlQueryModel(this);

}

DataBase::~DataBase()
{
    delete dataBase;
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

    tModel = new QSqlTableModel(this, *dataBase);

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

    bool status;
    status = dataBase->open( );

    emit sig_SendStatusConnection(status);

}

void DataBase::ReadAnswerFromDB()
{
    switch(currentRequestedModel)
    {
    case modelType::query:
        view->setModel(qModel);
        view->showColumn(0);
        break;
    case modelType::table:
        view->setModel(tModel);
        view->hideColumn(0);
        break;
    default:
        break;
    };

    view->setWindowTitle("ПоискКино");
    view->show();

}

void DataBase::RequestToTableDB(QString request)
{
    tModel->setTable("film");
    tModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tModel->select();
    tModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Название фильма"));
    tModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Описание"));
    tModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Год релиза"));

    QSqlError err;
    if(tModel->lastError().isValid()){
        err = tModel->lastError();
    }

    currentRequestedModel = modelType::table;

    emit sig_SendStatusRequest(err);
}

void DataBase::BindView(QTableView* view_)
{
    view = view_;
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

    qModel->setQuery(request, *dataBase);
    qModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Название фильма"));
    qModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Описание фильма"));

    QSqlError err;
    if (qModel->lastError().isValid()){
            err = qModel->lastError();
    }

    currentRequestedModel = modelType::query;

    emit sig_SendStatusRequest(err);
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}



