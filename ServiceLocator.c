#include "ServiceLocator.h"

ServiceLocator* create_service_locator(int max_services) {
	ServiceLocator* sl = (ServiceLocator*)malloc(sizeof(ServiceLocator));
	sl->services = malloc(sizeof(void*)*max_services);
	return sl;
}

void store_service(ServiceLocator* sl, int service_index, void* service) {
	sl->services[service_index] = service;
}

void* get_service(ServiceLocator* sl, int service_index) {
	return sl->services[service_index];
}

void destroy_service_locator(ServiceLocator* sl) {
	free(sl->services);
	free(sl);
}
