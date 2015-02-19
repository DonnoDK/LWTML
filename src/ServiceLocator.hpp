#ifndef SERVICE_LOCATOR_HPP
#define SERVICE_LOCATOR_HPP
#include <map>
class ServiceLocator{
private:
    bool _shouldDeallocateServices;
    std::map<unsigned int, class IService*> _services;
public:
    ServiceLocator();
    ~ServiceLocator();
    void installService(class IService* service);
    class IService* service(unsigned int serviceType);
    void setShouldDeallocateServices(bool answer);
};
#endif
