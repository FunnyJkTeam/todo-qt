#ifndef SINGLETON_H
#define SINGLETON_H


#include <QMutex>
#include <QScopedPointer>

template<typename T>

class Singleton
{
public:
    static T& getInstance();//get the intance object

    Singleton(const Singleton &other) = delete ;
    Singleton<T> & operator=(const Singleton &other) = delete;

private:
    static QMutex m_mutex;
    static QScopedPointer<T> self;
};


/**
  Singleton impletation
**/

template<typename T> QMutex Singleton<T>::m_mutex;
template<typename T> QScopedPointer<T> Singleton<T>::self;

template <typename T>
T& Singleton<T>::getInstance(){
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
    Singleton Macro
**/
#define SINGLETON(Class)                           \
private:                                           \
    Class();                                       \
    ~Class();                                      \
    Class(const Class &other) = delete;            \
    Class& operator=(const Class &other) = delete; \
    friend class  Singleton<Class>;                \
    friend struct QScopedPointerDeleter<Class>;    \
                                                   \
public:                                            \
    static Class& instance() {                     \
        return Singleton<Class>::getInstance();    \
    }



#endif // SINGLETON_H
