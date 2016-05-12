#include "PlatformFactory.h"

#include "CTPPlatform.h"

Platform* PlatformFactory::Create(const QString &strName)
{
    Platform *pPlatform = nullptr;
    if(strName.toUpper() == "CTP")
    {
        pPlatform = new CTPPlatform();
    }
    return pPlatform;
}

void PlatformFactory::Destroy(Platform *platform)
{
    delete platform;
}
