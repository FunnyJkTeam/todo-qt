#ifndef SQLITE_H
#define SQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <QInternal>
#include <QString>
#include <QDebug>
#include <QSharedPointer>
#include <QFile>
#include <QMessageBox>





class  Sqlite
        :public QObject
{
    Q_OBJECT
protected:

    virtual void initDataBaseFile(const QString &fileName,const QString &hostName="",const QString &userName="",const QString &passwd="");

    void _connectDB(const QString &fileName,const QString &hostName="",const QString &userName="",const QString &passwd="");


public:
     Sqlite(const QString &fileName,const QString &hostName="",const QString &userName="",const QString &passwd="");
     ~Sqlite();

    bool createTable(const QString &tableName,const QMap<QString,QString> &tableData);
    int db_query(const QString &sql);
    int add(const QString &tableName,const QMap<QString,QString> data);
    int del(const QString &tableName,const QMap<QString,QString> where);
    int update(const QString &tableName,const QMap<QString , QString > where,const QMap<QString,QString> data);
    bool find(const QString &tableName,const QList<QString> key,QList<QList<QString>> *row);
    bool find(const QString &tableName,const QList<QString> key,QMap<QString,QString> where,QList<QList<QString>> *row);
    QString errorString();


protected:
    QSqlDatabase m_db;
    QString m_hostName ="";
    QString m_userName ="";
    QString m_passwd = "";
    QString m_fileName = "";
    QSqlError m_error;
    QSqlQuery *m_query = nullptr;
    QSqlRecord m_sqlRecord;



};



#endif // SQLITE_H
