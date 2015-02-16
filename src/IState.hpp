#ifndef ISTATE_HPP
#define ISTATE_HPP
class IState{
    virtual void process(double deltatime) = 0;
};

#endif
