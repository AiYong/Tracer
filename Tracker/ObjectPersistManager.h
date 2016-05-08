#ifndef _TRACKER_OBJECTPERSISTERMANAGER_H_
#define _TRACKER_OBJECTPERSISTERMANAGER_H_

#include "Account.h"
#include "ObjectPersister.h"


class ObjectPersistManager
{
public:

    static ObjectPersistManager* GetInstance()
    {
        static ObjectPersistManager oPersistManager;
        return &oPersistManager;
    }

public:

    template<typename D,typename T>
    bool Load(D* pDep,QList<T*> &lObjs)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        oObjectPersister.Load(pDep,lObjs);
        return true;
    }

    template<typename T>
    void Save(QList<T*> const& pObjs)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        oObjectPersister.Save(pObjs);
    }

    template<typename T>
    void Save(T const* pObj)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        oObjectPersister.Save(pObj);
    }

    template<typename T>
    void Update(T const* pObj)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        oObjectPersister.Update(pObj);
    }

    template<typename T>
    void Update(QList<T*> const& pObjs)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        oObjectPersister.Update(pObj);
    }

    template<typename T>
    void RemoveAll(T const* pDep)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        return oObjectPersister.Remove(pDep);
    }

    template<typename T>
    void Remove(T const*pObj)
    {
        ObjectPersister<T> &oObjectPersister = GetObjectPersister<T>();
        return oObjectPersister.Remove(pObj);
    }
};




#endif // _TRACKER_OBJECTPERSISTERMANAGER_H_
