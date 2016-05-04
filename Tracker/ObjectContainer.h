#ifndef _TRACKER_OBJECTCONTAINER_H_
#define _TRACKER_OBJECTCONTAINER_H_

#include <QObject>
#include <QMap>

template<typename T>
class ObjectContainer : public QObject
{
    Q_OBJECT
public:

    explicit ObjectContainer(QObject *parent = 0);

public:

    T* GetObject(QString const& strId);

    void PutObject(QString const& strId,T* pObj);

private:

    QMap<T*,T*> m_mCaches;

};

template<typename T>
ObjectContainer<T>& GetObjectContainer()
{
    static ObjectContainer<T> oContainer;
    return oContainer;
}

#endif // _TRACKER_OBJECTCONTAINER_H_
