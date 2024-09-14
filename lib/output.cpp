#include "../include/output.h"
#include <iostream>
#include <fstream>

general_info::~general_info() {}

void help_info::see_info()
{
    std::cout << "*** Статистична обробка - визначення довірчого інтервалу ***" << std::endl
              << std::endl
              << "Для виводу в термінал:" << std::endl
              << "-d [перше число] [друге число] [наступне число]" << std::endl
              << "-d [перше число] [друге число] [наступне число] alf [альфа]" << std::endl
              << "-d [перший ряд ([перше] [друге] [наступне число])] -- [другий ряд] -- [наступний ряд]" << std::endl
              << "-d [перший ряд ([перше] [друге] [наступне число])] -- [другий ряд] -- [наступний ряд] alf [альфа]" << std::endl
              << std::endl
              << "Для виводу в файл:" << std::endl
              << "-df [перше число] [друге число] [наступне число]" << std::endl
              << "-df [перше число] [друге число] [наступне число] alf [альфа]" << std::endl
              << "-df [перший ряд ([перше] [друге] [наступне число])] -- [другий ряд] -- [наступний ряд]" << std::endl
              << "-df [перший ряд ([перше] [друге] [наступне число])] -- [другий ряд] -- [наступний ряд] alf [альфа]" << std::endl
              << std::endl
              << "Для довідки:" << std::endl
              << "-h | --help" << std::endl
              << std::endl
              << "Для додаткової інформації:" << std::endl
              << "-i" << std::endl;
}

void inf_info::see_info()
{
    std::cout << "Утиліта визначає довірчий інтервал рядів чисел:" << std::endl
              << std::endl
              << "Довірчий інтервал для середнього значення генеральної сукупності з нормальний розподілом є діапазоном" << std::endl
              << "з обох боків середнього значення." << std::endl
              << std::endl
              << "Довірчий інтервал (англ. confidence interval) - у математичній статистиці є типом інтервальної оцінки," << std::endl
              << "яку обчислюють за даними спостереження, і яка покриває невідомий статистичний параметр із заданою надійністю." << std::endl
              << "Це інтервал, у межах якого з заданою довірчою імовірністю можна чекати значення оцінюваної (шуканої) випадкової величини." << std::endl
              << "Застосовують для повнішої оцінки точності порівняно з точковою оцінкою." << std::endl
              << std::endl
              << "Тлумачення довірчого інтервалу - якщо рівень довіри P великий (0.95 або 0.99), то довірчий інтервал майже напевно" << std::endl
              << "містить істинне значення θ." << std::endl
              << std::endl
              << "Довірчі межі випадкових похибок - це верхня та нижня межі інтервалу, в які похибки потрапляють із заданою ймовірністю Р." << std::endl
              << "Величина Р називається довірчою ймовірністю. Для визначення довірчих меж похибок необхідно знати густину розподілу" << std::endl
              << "похибок та ймовірність потрапляння похибок у довірчі межі." << std::endl
              << std::endl
              << "Альфа - рівень значності, який використовується для обчислення довірчого рівня. Довірчий рівень становить (1 - альфа)," << std::endl
              << "або, іншими словами, альфа, що дорівнює 0.05, свідчить про довірчий рівень у 95 відсотків." << std::endl;
}

//--------------------------------------------------

data_info::~data_info() {}

void screen_info::see_info(variant *stat, float _all)
{
    stat->alf(_all);
    stat->spot();

    if (stat->average_lines.size() == 1)
    {
        std::cout << "Послідовність: ";
        for (auto data : stat->data)
        {
            std::cout << data << ' ';
        }
        std::cout << std::endl;
    }

    else
    {
        int counter = 1;
        for (auto vars : stat->input_data)
        {
            std::cout << "Послідовність варіанту " << counter << ": ";
            counter++;

            for (auto numbers : vars)
            {
                std::cout << numbers << ' ';
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Альфа: " << stat->alpha << std::endl;
    std::cout << "Довірчий інтервал: " << stat->confidence_interval << std::endl;

    if (stat->average_lines.size() == 1)
    {
        std::cout << "Середнє: " << stat->average << ' '
                  << "[нижня межа: " << (stat->average - stat->confidence_interval) << ' '
                  << "верхня межа: " << (stat->average + stat->confidence_interval) << ']'
                  << std::endl;
    }

    else
    {
        std::string lines = "========================================================================================";

        std::cout << lines << std::endl;
        for (int i = 0; i < stat->average_lines.size(); i++)
        {
            std::cout << "Середнє по варіанту " << (i + 1) << ": " << stat->average_lines.at(i)
                      << ' ' << "[нижня межа: " << (stat->average_lines.at(i) - stat->confidence_interval)
                      << ' ' << "верхня межа: " << (stat->average_lines.at(i) + stat->confidence_interval) << ']'
                      << std::endl;
        }
        std::cout << lines << std::endl;
    }
}

void file_info::see_info(variant *var, float _all)
{
    std::ofstream writer("disp-stat.csv", std::ios::app);
    const char coma = ',';
    const char quo = '\"';

    std::locale m_loc("uk_UA.utf8");
    writer.imbue(m_loc);

    var->alf(_all);
    var->spot();

    if (var->average_lines.size() == 1)
    {
        writer << quo << "Послідовність:" << quo << coma;
        for (auto data : var->data)
        {
            writer << quo << data << quo << coma;
        }
        writer << std::endl;
    }

    else
    {
        int counter = 1;
        for (auto vars : var->input_data)
        {
            writer << quo << "Послідовність варіанту " << counter << quo << coma;
            counter++;

            for (auto numbers : vars)
            {
                writer << quo << numbers << quo << coma;
            }
            writer << std::endl;
        }
    }

    writer << quo << "Альфа:" << quo << coma << quo << var->alpha << quo << std::endl;
    writer << quo << "Довірчий інтервал:" << quo << coma << quo << var->confidence_interval << quo << std::endl;

    if (var->average_lines.size() == 1)
    {
        writer << quo << "Середнє:" << quo << coma << quo << var->average << quo << coma
               << quo << "нижня межа:" << quo << coma << quo << (var->average - var->confidence_interval) << quo << coma
               << quo << "верхня межа:" << quo << coma << quo << (var->average + var->confidence_interval) << quo << coma
               << std::endl << std::endl;
    }

    else
    {
        for (int i = 0; i < var->average_lines.size(); i++)
        {
            writer << quo << "Середнє по варіанту " << (i + 1) << ":" << quo << coma << quo << var->average_lines.at(i) << quo << coma
                      << quo << "нижня межа:" << quo << coma << quo << (var->average_lines.at(i) - var->confidence_interval) << quo << coma
                      << quo << "верхня межа:" << quo << coma << quo << (var->average_lines.at(i) + var->confidence_interval) << quo << coma
                      << std::endl;
        }
        writer << std::endl;
    }

    std::cout << "Дані додані у файл disp-stat.csv" << std::endl;
}

//--------------------------------------------------

print_info::print_info(general_info *temp) : g_info(temp) {}
print_info::print_info(data_info *temp) : d_info(temp) {}

void print_info::_print() { g_info->see_info(); }
void print_info::_print(variant var, float _alf_temp) { d_info->see_info(&var, _alf_temp); }

print_info::~print_info()
{
    delete g_info;
    g_info = nullptr;

    delete d_info;
    d_info = nullptr;
}
