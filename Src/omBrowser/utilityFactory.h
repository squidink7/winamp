	#ifndef NULLSOFT_WINAMP_UTILITY_FACTORY_HEADER
	#define NULLSOFT_WINAMP_UTILITY_FACTORY_HEADER
	
	#if defined(_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
	#endif
	
	#include <api/service/waservicefactory.h>
	#include <api/service/services.h>
	
	class OmUtility;
	
	class OmUtilityFactory : public waServiceFactory
	{
	public:
OmUtilityFactory();
~OmUtilityFactory();
	
	public:
FOURCC GetServiceType();
const char *GetServiceName();
GUID GetGUID();
void *GetInterface(int global_lock);
int SupportNonLockingInterface();
int ReleaseInterface(void *ifc);
const char *GetTestString();
int ServiceNotify(int msg, int param1, int param2);
	public:
HRESULT Register(api_service *service);
HRESULT Unregister(api_service *service);
	
	protected:
RECVS_DISPATCH;
	
	protected:
OmUtility *object;
	};
	
	#endif //NULLSOFT_WINAMP_UTILITY_FACTORY_HEADER