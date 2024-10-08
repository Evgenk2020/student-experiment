#ifndef OUTPUT_H
#define OUTPUT_H

#include "../include/stat.h"

class general_info
{
public:
    virtual void see_info() = 0;
    virtual ~general_info();
};

class help_info : public general_info
{
public:
    void see_info() override;
};

class inf_info : public general_info
{
public:
    void see_info() override;
};

//--------------------------------------------------

class data_info
{
public:
    virtual void see_info(variant *var, float _all) = 0;
    virtual ~data_info();
};

class screen_info : public data_info
{
public:
    void see_info(variant *var, float _all) override;
};

class file_info : public data_info
{
public:
    void see_info(variant *var, float _all) override;
};

//--------------------------------------------------

class print_info
{
private:
    general_info *g_info = nullptr;
    data_info *d_info = nullptr;

public:
    print_info(general_info *temp);
    print_info(data_info *temp);
    void _print();
    void _print(variant var, float _alf_temp);
    ~print_info();
};

#endif // OUTPUT_H