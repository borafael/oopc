#ifndef __SERVICE_LOCATOR_H__
#define __SERVICE_LOCATOR_H__

#include <stdlib.h>

typedef struct {
	void** services;
} ServiceLocator;

ServiceLocator* create_service_locator(int max_services);

void store_service(ServiceLocator* sl, int service_index, void* service);

void* get_service(ServiceLocator* sl, int service_index);

void destroy_service_locator(ServiceLocator* sl);

#endif
