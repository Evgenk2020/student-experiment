#include "../include/output.h"
#include "../include/proc.h"
#include <regex>

processing::~processing() {}

void processing::going()
{
    if (_inp_var.size() == 1)
    {
        this->helping();
    }

    if (_inp_var.size() > 1)
    {
        this->converting();
        this->counting();
    }
}

decree::~decree() {}
decree::decree(inp_var _inp) { _inp_var = _inp; }

void decree::helping()
{
    if (_inp_var.at(1) == _keys.k_help_one || _inp_var.at(1) == _keys.k_help_two)
    {
        print_info inf(new help_info);
        inf._print();
    }

    else if (_inp_var.at(1) == _keys.k_info)
    {
        print_info inf(new inf_info);
        inf._print();
    }

    else
    {
        std::cout << "error... use -h or --help for details" << std::endl;
    }
}

void decree::converting()
{
    using gg_iter = std::map<int, std::string>::iterator;

    std::string al = _keys.alfa;
    auto alf_check = [al](gg_iter temp)
    {
        return ((--(--temp))->second == al);
    };

    std::string ln = _keys.space;
    auto lines_check_finish = [ln](gg_iter temp)
    {
        return ((--temp)->second == ln);
    };

    auto lines_check_start = [ln](gg_iter temp)
    {
        return ((temp)->second == ln);
    };

    gg_iter start = _inp_var.find(2);
    gg_iter finish = _inp_var.end();

    if (alf_check(finish))
    {
        try
        {
            alfa_mean = stof((--finish)->second);
        }

        catch (const std::exception &e)
        {
            std::cout << "error.. use correct data values" << std::endl;
            exit(1);
        }

        finish = _inp_var.find(_inp_var.size() - 1);

        if (alfa_mean <= 0 || alfa_mean >= 1)
        {
            std::cout << "error... set 0 < alpha < 1" << std::endl;
            exit(1);
        }
    }

    local_data_struct _temp_datas;
    for (auto a = start; a != finish; a++)
    {
        if (lines_check_finish(finish) || lines_check_start(start))
        {
            std::cout << "data error..." << std::endl;
            exit(1);
        }

        if (a->second == ln)
        {
            _dyn_array.push_back(_temp_datas);
            _temp_datas._l_data.clear();
        }

        else
        {
            try
            {
                _temp_datas._l_data.push_back(stof(a->second));
            }

            catch (const std::exception &e)
            {
                std::cout << "error.. use correct data values" << std::endl;
                exit(1);
            }
        }
    }

    _dyn_array.push_back(_temp_datas);
    _temp_datas._l_data.clear();
}

void decree::counting()
{
    if (_inp_var.at(1) == _keys.k_data)
    {
        print_info inf(new screen_info);
        inf._print(_dyn_array, alfa_mean);
    }

    else if (_inp_var.at(1) == _keys.k_file)
    {
        print_info inf(new file_info);
        inf._print(_dyn_array, alfa_mean);
    }

    else
    {
        std::cout << "incorrect key.. use [-d | -df] keys for results" << std::endl;
    }
}