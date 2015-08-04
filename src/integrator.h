#ifndef INTEGRATOR_H
#define INTEGRATOR_H


class integrator
{
public:
    integrator();
    ~integrator();
    bool setDivider(int);
    bool update(void);
    bool initialize(void);
};

#endif // INTEGRATOR_H
