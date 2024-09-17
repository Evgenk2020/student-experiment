#ifndef PROC_H
#define PROC_H

#include <iostream>
#include <map>
#include <vector>
#include "../include/localdata.h"

typedef std::map<int, std::string> inp_var;

struct keys
{
    const std::string k_help_one = "-h";
    const std::string k_help_two = "--help";
    const std::string k_info = "-i";
    const std::string k_data = "-d";
    const std::string k_file = "-df";
    const std::string alfa = "alf";
    const std::string space = "--";
};

class processing
{
protected:
    keys _keys;
    inp_var _inp_var;
    virtual void helping() = 0;
    virtual void converting() = 0;
    virtual void counting() = 0;

public:
    virtual ~processing();
    void going();
};

class decree : public processing
{
private:
    local_data_dyn_array _dyn_array;
    float alfa_mean = -1;

public:
    ~decree();
    decree(inp_var _inp);
    void helping() override;
    void converting() override;
    void counting() override;
};

#endif // PROC_H