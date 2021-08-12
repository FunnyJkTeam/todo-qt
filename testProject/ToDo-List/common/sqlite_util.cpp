#include "sqlite_util.h"



 Sqlite:: Sqlite(const QString &fileName, const QString &hostName, const QString &userName, const QString &passwd)
    :QObject(nullptr),m_hostName(hostName),m_userName(userName),m_passwd(passwd),m_fileName(fileName)
{


}

 Sqlite::~ Sqlite()
{
    if(this->m_db.isOpen())
        this->m_db.close();
    if(nullptr != this->m_query){
        delete this->m_query;
        this->m_query = nullptr;
    }
}

void  Sqlite::initDataBaseFile(const QString &fileName, const QString &hostName, const QString &userName, const QString &passwd)
{
    QFile sqlFile(fileName);
    bool hasInit = sqlFile.exists();
    if(!hasInit){
        if(!sqlFile.open(QIODevice::WriteOnly)){
            qDebug()<<"DataBase File create Error"<<endl;
        }else{
            sqlFile.close();
        }
    }
    this->_connectDB(fileName,hostName,userName,passwd);
    if(!hasInit){
        qDebug()<<"DataBase not exit,init table"<<endl;
        QString tableName = "patient_info";
        QMap<QString,QString> tabaData;
        tabaData.insert("id","INTEGER");
        tabaData.insert("patient_id","TEXT");
        tabaData.insert("name","TEXT");
        tabaData.insert("gender","INTEGER");
        tabaData.insert("age","INTEGER");
        tabaData.insert("age_unit","TEXT");
        tabaData.insert("check_time","TEXT");
        tabaData.insert("room_name","TEXT");
        tabaData.insert("xml_path","TEXT");
        tabaData.insert("delete_time","TEXT");
        int ret =this->createTable(tableName,tabaData);
        qDebug()<<"初始化数据表："<<ret<<endl;
    }

}

void  Sqlite::_connectDB(const QString &fileName, const QString &hostName, const QString &userName, const QString &passwd)
{
    if(!this->m_db.isValid()){
        this->m_db = QSqlDatabase::addDatabase("QSQLITE");
        this->m_db.setHostName(hostName);
        this->m_db.setPassword(passwd);
        this->m_db.setUserName(userName);
        this->m_db.setDatabaseName(fileName);
        if(!this->m_db.open()){
            qDebug("database open error");
            m_error = m_db.lastError();
            return;
        }
        qDebug()<<"sqlite database connected"<<endl;
        this->m_query = new QSqlQuery(m_db);
    }
}


/**
 * @brief  Sqlite::createTable 创建数据库表
 * @param tableName 表名
 * @param tableData 表项 名-属性
 * @return
 */
bool  Sqlite::createTable(const QString &tableName, const QMap<QString, QString> &tableData)
{

    QString sql = "CREATE TABLE "+tableName+" (";
    for(QMap<QString,QString>::const_iterator iter = tableData.constBegin(); iter != tableData.constEnd(); iter++){
        sql.append(iter.key() + " " + iter.value());
        if(iter.key() == "id"){
            sql.append(" PRIMARY KEY AUTOINCREMENT ");
        }
        if(iter != tableData.constEnd()){
            sql.append(",");
        }
    }
    sql.chop(1);
    sql.append(")");
    qDebug()<<sql;
    this->m_query->prepare(sql);
    return this->m_query->exec();
}

int  Sqlite::db_query(const QString &sql)
{
    this->m_query->prepare(sql);
    this->m_query->exec();
    while (this->m_query->next()) {
        qDebug()<<m_query->value(0)<<m_query->value(1)<<m_query->value(2)<<m_query->value(3)<<m_query->value(4)<<m_query->value(5)<<endl;
    }

    return this->m_query->exec();
}

/**
 * @brief  Sqlite::add 插入数据
 * @param tableName 表名
 * @param data 数据项 名-属性
 * @return
 */
int  Sqlite::add(const QString &tableName, const QMap<QString, QString> data)
{
    QString sql = "INSERT INTO "+tableName + "(";
    QString values = " values (";
    for(QMap<QString,QString>::const_iterator iter = data.constBegin();iter != data.constEnd();iter ++){
        sql.append(iter.key() + ", ");
        values.append(iter.value() + ", ");
    }
    sql.chop(2);
    values.chop(2);
    sql.append(")");
    values.append(")");
    sql.append(values);
    qDebug()<<sql;
    this->m_query->prepare(sql);
    return this->m_query->exec();
}


/**
 * @brief  Sqlite::del 删除一条记录
 * @param tableName 表名
 * @param where 删除的过滤器
 * @return
 */
int  Sqlite::del(const QString &tableName, const QMap<QString, QString> where)
{
    QString sql = "DELETE ";
    sql.append(tableName);
    sql.append(" WHERE ");
    for(QMap<QString,QString>::const_iterator iter = where.constBegin();iter != where.constEnd();iter ++){
        sql.append(iter.key() + " = ");
        sql.append("'"+iter.value()+"' ");
    }
    sql.chop(2);
    qDebug()<<sql;
    this->m_query->prepare(sql);
    return this->m_query->exec();
}


/**
 * @brief  Sqlite::update 更新一条记录
 * @param tableName 表名
 * @param where 修改位置
 * @param data 新的修改值
 * @return
 */
int  Sqlite::update(const QString &tableName, const QMap<QString, QString> where, const QMap<QString, QString> data)
{
    QString sql = "UPDATE "+tableName + " set";
    for(QMap<QString,QString>::const_iterator iter = data.constBegin();iter != data.constEnd();iter ++){
        sql.append(iter.key() + " = ");
        sql.append(iter.value() + " ");
    }
    sql.append("WHERE ");
    for(QMap<QString,QString>::const_iterator iter = where.constBegin();iter != where.constEnd();iter ++){
        sql.append(iter.key() + " = ");
        sql.append(iter.value()+" ");
    }
    qDebug()<<sql;
    this->m_query->prepare(sql);
    return this->m_query->exec();
}

/**
 * @brief  Sqlite::find 查找所有数据
 * @param tableName 表名
 * @param key 键值
 * @param row 返回值地址
 * @return
 */
bool  Sqlite::find(const QString &tableName, const QList<QString> key, QList<QList<QString> > *row)
{

    QString sql = "SELECT ";
    int len = key.size();
    for(int i=0;i<len;i++){
        sql.append(key.at(i));
        sql.append(",");
    }
    sql.chop(1);
    sql.append(" from "+tableName);
    qDebug()<<sql;
    this->m_query->prepare(sql);
    if(this->m_query->exec()){
        while (this->m_query->next()) {
            QList<QString> j;
            for(int i = 0 ; i < len;i++){
                j.append(this->m_query->value(i).toString());
            }
            row->append(j);
        }
        return true;
    }else{
        return false;
    }
}

bool  Sqlite::find(const QString &tableName, const QList<QString> key, QMap<QString, QString> where, QList<QList<QString> > *row)
{
    QString sql = "SELECT ";
    int len = key.size();
    for(int i = 0;i<len;i++){
        sql.append(key.at(i));
        sql.append(", ");
    }
    sql.chop(1);
    sql.append(" FROM "+tableName);
    sql.append(" WHERE ");
    for(QMap<QString,QString>::const_iterator iter = where.constBegin();iter != where.constEnd();iter++){
        sql.append(iter.key() + "="+iter.value()+",");
    }
    sql.chop(1);
    qDebug()<<sql;
    this->m_query->prepare(sql);
    if(this->m_query->exec()){
        while (this->m_query->next()) {
            QList<QString> j;
            for(int i = 0;i<len;i++){
                j.append(m_query->value(i).toString());
            }
            row->append(j);
        }
        return true;
    }
    return false;
}



QString  Sqlite::errorString()
{
    return this->m_error.text();
}
