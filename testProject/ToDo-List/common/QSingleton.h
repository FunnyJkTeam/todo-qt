#ifndef QSINGLETON_H
#define QSINGLETON_H


/***************************************************************
*  @Copyright:  Copyright (c) 2021 MQ. All rights reserved.
*  @ProjName:   EcgMonitorV3_0
*  @FileName:   QSingleton.h
*  @Brief:
*  @Author:     刘卓辉
*  @Date:       2021-05-25 T 14:27
****************************************************************/
#include <QObject>
#include <QMutex>
#include <QScopedPointer>


template<typename T>

class QSingleton
{
public:
    static T& getInstance();//get the intance object

    QSingleton(const QSingleton &other) = delete ;
    QSingleton<T> & operator=(const QSingleton &other) = delete;

private:
    static QMutex m_mutex;
    static QScopedPointer<T> self;
};


/**
  QSingleton impletation
**/

template<typename T> QMutex QSingleton<T>::m_mutex;
template<typename T> QScopedPointer<T> QSingleton<T>::self;

template <typename T>
T& QSingleton<T>::getInstance(){
    if(self.isNull()){
        m_mutex.lock();
        if(self.isNull()){
            self.reset(new T());//this potiner will deleted at the end of global domain
        }
        m_mutex.unlock();
    }
    return *self.data();
}


/**
    QSingleton Macro
**/
#define QSINGLETON(Class)                           \
private:                                           \
    Class();                 \
    ~Class();                                       \
    Class(const Class &other) = delete;            \
    Class& operator=(const Class &other) = delete; \
    friend class  QSingleton<Class>;                \
    friend struct QScopedPointerDeleter<Class>;    \
                                                   \
public:                                            \
    static Class& instance() {                     \
        return QSingleton<Class>::getInstance();    \
    }


#endif // QSINGLETON_H
