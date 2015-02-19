#include "ServiceLocator.hpp"
#include "IService.hpp"
#include <iostream>
ServiceLocator::ServiceLocator(){
    _shouldDeallocateServices = true;
}

ServiceLocator::~ServiceLocator(){
    if(_shouldDeallocateServices == true){
        /* TODO: deallocate services */
        std::map<unsigned int, IService*>::iterator it = _services.begin();
        for(; it != _services.end(); ++it){
            IService* s = it->second;
            delete s;
        }
    }
}

void ServiceLocator::installService(IService* service){
    if(service == NULL){
        return;
    }
    std::map<unsigned int, IService*>::iterator it = _services.find(service->type());
    if(it == _services.end()){
        _services.insert(std::pair<unsigned int, IService*>(service->type(), service));
    }else{
        std::cerr << "service already installed: " << service->type() << std::endl;
    }
}

IService* ServiceLocator::service(unsigned int serviceType){
    std::map<unsigned int, IService*>::iterator it = _services.find(serviceType);
    if(it == _services.end()){
        std::cerr << "service not installed - could not locate" << std::endl;
        return NULL;
    }
    return it->second;
}

void ServiceLocator::setShouldDeallocateServices(bool answer){
    _shouldDeallocateServices = answer;
}
