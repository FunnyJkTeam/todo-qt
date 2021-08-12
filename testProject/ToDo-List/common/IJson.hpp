#ifndef IJSON_H
#define IJSON_H


#include <QObject>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

class IJson{
public:
    virtual ~IJson(){}
    virtual void generateJson(QJsonObject &json) const =0;
    virtual QByteArray toJson() const{
        QJsonObject json;
        this->generateJson(json);
        QJsonDocument document;
        document.setObject(json);
        return document.toJson(QJsonDocument::Compact);
    }
    virtual bool fromJsonByteArray(const QByteArray &data){
        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);  //convert to json doc
        if (!doc.isNull() && (jsonError.error == QJsonParseError::NoError)) {//no error
            QJsonObject tRootObj = doc.object();
            this->fromJson(tRootObj);
            return true;
        }else{
            return false;
        }
    }
    virtual void fromJson(const QJsonObject &json)=0;
};

#endif // IJSON_H
