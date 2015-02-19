#ifndef ISTATE_HPP
#define ISTATE_HPP
class IState{
public:
    virtual void process(double deltatime) = 0;
};
#endif
