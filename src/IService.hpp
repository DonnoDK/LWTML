#ifndef ISERVICE_HPP
#define ISERVICE_HPP

class IService{
public:
    enum Services{
        KEYBOARD_INPUT,
        RENDERER
    };
    virtual unsigned int type() const = 0;
    virtual ~IService(){}
};

#endif
