			#include "api__in_mkv.h"
			#include "main.h"
			#include <api/service/waservicefactory.h>
			
			api_config *AGAVE_API_CONFIG = 0;
			
			api_language *WASABI_API_LNG = 0;
			HINSTANCE WASABI_API_LNG_HINST = 0, WASABI_API_ORIG_HINST = 0;
			
			template <class api_T>
			void ServiceBuild(api_T *&api_t, GUID factoryGUID_t)
			{
		if (plugin.service)
		{
	waServiceFactory *factory = plugin.service->service_getServiceByGuid(factoryGUID_t);
	if (factory)
api_t = reinterpret_cast<api_T *>( factory->getInterface() );
		}
			}
			
			template <class api_T>
			void ServiceRelease(api_T *api_t, GUID factoryGUID_t)
			{
		if (plugin.service && api_t)
		{
	waServiceFactory *factory = plugin.service->service_getServiceByGuid(factoryGUID_t);
	if (factory)
factory->releaseInterface(api_t);
		}
		api_t = NULL;
			}
			
			void WasabiInit()
			{
		ServiceBuild(AGAVE_API_CONFIG, AgaveConfigGUID);
		ServiceBuild(WASABI_API_LNG, languageApiGUID);
		// need to have this initialised before we try to do anything with localisation features
		WASABI_API_START_LANG(plugin.hDllInstance,InMkvLangGUID);
			}
			
			void WasabiQuit()
			{
		ServiceRelease(AGAVE_API_CONFIG, AgaveConfigGUID);
		ServiceRelease(WASABI_API_LNG, languageApiGUID);
			}