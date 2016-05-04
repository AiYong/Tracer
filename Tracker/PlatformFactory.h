#ifndef _TRACKER_PLATFORMFACTORY_H_
#define _TRACKER_PLATFORMFACTORY_H_

#include "Platform.h"

class PlatformFactory
{
public:

    static Platform* Create(QString const& strName);

    static void Destroy(Platform *platform);

};

#endif // _TRACKER_PLATFORMFACTORY_H_
