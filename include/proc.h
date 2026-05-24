#ifndef PROC_H
#define PROC_H

#include <iostream>
#include <string>
#include <vector>
#include "../include/localdata.h"

using inp_var = std::vector<std::string>;

struct keys
{
    static inline const std::string k_help_one = "-h";
    static inline const std::string k_help_two = "--help";
    static inline const std::string k_info = "-i";
    static inline const std::string k_data = "-d";
    static inline const std::string k_file = "-df";
    static inline const std::string alfa = "alf";
    static inline const std::string space = "--";
};

class processing
{
protected:
    inp_var _inp_var;

    virtual bool parse_arguments() = 0;
    virtual void execute_action() = 0;

public:
    explicit processing(inp_var args);
    virtual ~processing() = default;
    void going();
};

class help_processor final : public processing
{
protected:
    bool parse_arguments() override;
    void execute_action() override;

public:
    using processing::processing;
};

class data_processor final : public processing
{
private:
    local_data_dyn_array _dyn_array{};
    double alfa_mean = -1.0;

protected:
    bool parse_arguments() override;
    void execute_action() override;

public:
    using processing::processing;
};

processing *select_processor(const inp_var &args, help_processor &h_proc, data_processor &d_proc);

#endif // PROC_H