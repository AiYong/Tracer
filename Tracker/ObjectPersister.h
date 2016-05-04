#ifndef _TRACKER_OBJECTPERSISTER_H_
#define _TRACKER_OBJECTPERSISTER_H_

#include <QtSql>
#include <QVariantList>
#include "ObjectContainer.h"

/**
 * @brief 对象持久化器主模板
 */
template<typename T>
class ObjectPersister
{
public:

    template<typename D>
    void Load(D *pDep,QList<T*> &lObjs)
    {

    }

    void Save(QList<T*> const&lObjs)
    {

    }

    void Save(T const* pObj)
    {

    }

    void Update(QList<T*> const& lOjbs)
    {

    }

    void Update(T const* pObj)
    {

    }

    void Remove(QList<T*> const& lObjs)
    {

    }

    void Remove(T const* pObjs)
    {

    }

    template<typename D>
    void RemoveAll(D const* pDep)
    {

    }
};


template<typename T>
ObjectPersister<T>& GetObjectPersister()
{
    static ObjectPersister<T> oObjectPersister;
    return oObjectPersister;
}

#endif // _TRACKER_OBJECTPERSISTER_H_
