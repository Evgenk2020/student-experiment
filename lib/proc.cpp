#include "../include/proc.h"
#include "../include/output.h"
#include <charconv>

// ============================================================================
// processing
// ============================================================================

processing::processing(inp_var args) : _inp_var(std::move(args)) {}

void processing::going()
{
    if (parse_arguments())
    {
        execute_action();
    }
}

processing *select_processor(const inp_var &args, help_processor &h_proc, data_processor &d_proc)
{
    if (args.empty())
    {
        return nullptr;
    }

    const auto &key = args.at(0);

    if (key == keys::k_help_one || key == keys::k_help_two || key == keys::k_info)
    {
        return &h_proc;
    }

    if (key == keys::k_data || key == keys::k_file)
    {
        return &d_proc;
    }

    return nullptr;
}

// ============================================================================
// help_processor
// ============================================================================

bool help_processor::parse_arguments() { return !_inp_var.empty(); }

void help_processor::execute_action()
{
    const auto &key = _inp_var.at(0);

    if (key == keys::k_help_one || key == keys::k_help_two)
    {
        print_info inf(new help_info);
        inf._print();
    }

    else if (key == keys::k_info)
    {
        print_info inf(new inf_info);
        inf._print();
    }
}

// ============================================================================
// data_processor
// ============================================================================

bool data_processor::parse_arguments()
{
    if (_inp_var.size() < 2)
    {
        std::cout << "data error... put decimal values \n";
        return false;
    }

    auto start = _inp_var.begin() + 1;
    auto finish = _inp_var.end();

    if (_inp_var.size() >= 4 && *(finish - 2) == keys::alfa)
    {
        try
        {
            // std::from_chars instead std::stof drops string allocations
            std::string_view alf_str = *(finish - 1);
            auto [ptr, ec] = std::from_chars(alf_str.data(), alf_str.data() + alf_str.size(), alfa_mean);

            if (ec != std::errc{})
            {
                throw std::invalid_argument("bad float");
            }

            finish -= 2;
        }

        catch (...)
        {
            std::cout << "error.. use correct values for alpha\n";
            return false;
        }

        if (alfa_mean <= 0.0 || alfa_mean >= 1.0)
        {
            std::cout << "error... set 0 < alpha < 1\n";
            return false;
        }
    }

    if (*start == keys::space || *(finish - 1) == keys::space)
    {
        std::cout << "data error... put decimal values \n";
        return false;
    }

    local_data_struct temp_data{};
    for (auto it = start; it != finish; ++it)
    {
        if (*it == keys::space)
        {
            _dyn_array.push_back(std::move(temp_data));
            temp_data._l_data.clear();
        }

        else
        {
            try
            {
                double val = 0.0;
                std::string_view num_str = *it;
                auto [ptr, ec] = std::from_chars(num_str.data(), num_str.data() + num_str.size(), val);

                if (ec != std::errc{})
                {
                    throw std::invalid_argument("bad float");
                }

                temp_data._l_data.push_back(val);
            }

            catch (...)
            {
                std::cout << "error.. use correct data values\n";
                return false;
            }
        }
    }

    _dyn_array.push_back(std::move(temp_data));
    return true;
}

void data_processor::execute_action()
{
    const auto &key = _inp_var.at(0);
    variant var_data(_dyn_array);

    if (key == keys::k_data)
    {
        print_info inf(new screen_info);
        inf._print(var_data, alfa_mean);
    }
    
    else if (key == keys::k_file)
    {
        print_info inf(new file_info);
        inf._print(var_data, alfa_mean);
    }
}