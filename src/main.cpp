#include "../include/proc.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "error.. data is empty. try [-h | --help] for more info" << std::endl;
        return 1;
    }

    inp_var _inp_var{};
    _inp_var.reserve(argc - 1);

    for (int i = 1; i < argc; i++)
    {
        _inp_var.emplace_back(argv[i]);
    }

    help_processor h_proc(_inp_var);
    data_processor d_proc(_inp_var);
    processing *proc = select_processor(_inp_var, h_proc, d_proc);

    if (proc)
    {
        proc->going();
    }
    
    else
    {
        std::cout << "error... unknown or invalid command key\n";
        return 1;
    }

    return 0;
}