#include "../include/output.h"
#include <iostream>
#include <fstream>
#include <print>
#include <filesystem>
#include <string>
#include <format>
#include <ranges>
#include <locale>

void help_info::see_info()
{
    std::println(
        "*** Статистична обробка - визначення довірчого інтервалу ***\n"
        "\n"
        "Для виводу в термінал:\n"
        "-d [перше число] [друге число] ... [наступне число]\n"
        "-d [перше число] [друге число] ... [наступне число] alf [альфа 0 <..< 1]\n"
        "-d [перший ряд ([перше] [друге] ... [наступне число])] -- [другий ряд] -- ... [наступний ряд]\n"
        "-d [перший ряд ([перше] [друге] ... [наступне число])] -- [другий ряд] -- ... [наступний ряд] alf [альфа 0 <...< 1]\n"
        "\n"
        "Для виводу в файл:\n"
        "-df [перше число] [друге число] ... [наступне число]\n"
        "-df [перше число] [друге число] ... [наступне число] alf [альфа 0 <..< 1]\n"
        "-df [перший ряд ([перше] [друге] ... [наступне число])] -- [другий ряд] -- ... [наступний ряд]\n"
        "-df [перший ряд ([перше] [друге] ... [наступне число])] -- [другий ряд] -- ... [наступний ряд] alf [альфа 0 <...< 1]\n"
        "\n"
        "Для довідки:\n"
        "-h | --help\n"
        "\n"
        "Для додаткової інформації:\n"
        "-i");
}

void inf_info::see_info()
{
    std::println(
        "Утиліта визначає довірчий運行 інтервал рядів чисел:\n"
        "\n"
        "Довірчий інтервал для среднього значення генеральної сукупності з нормальний розподілом є діапазоном\n"
        "з обох боків середнього значення.\n"
        "\n"
        "Довірчий інтервал (англ. confidence interval) - у математичній статистиці є типом інтервальної оцінки,\n"
        "яку обчислюють за даними спостереження, і яка покриває невідомий статистичний параметр із заданою надійністю.\n"
        "Це інтервал, у межах якого з заданою довірчою імовірністю можна чекати значення оцінюваної (шуканої) випадкової величини.\n"
        "Застосовують для повнішої оцінки точності порівняно з точковою оцінкою.\n"
        "\n"
        "Тлумачення довірчого інтервалу - якщо рівень довіри P великий (0.95 або 0.99), то довірчий інтервал майже напевно\n"
        "містить істинне значение θ.\n"
        "\n"
        "Довірчі межі випадкових похибок - це верхня та нижня межі інтервалу, в які похибки потрапляють із заданою ймовірністю Р.\n"
        "Величина Р називається довірчою ймовірністю. Для визначення довірчих меж похибок необхідно знати густину розподілу\n"
        "похибок та ймовірність потрапляння похибок у довірчі межі.\n"
        "\n"
        "Альфа - рівень значності, який використовується для обчислення довірчого рівня. Довірчий рівень становить (1 - альфа),\n"
        "або, іншими словами, альфа, що дорівнює 0.05, свідчить про довірчий уровень у 95 відсотків.");
}

//--------------------------------------------------

void screen_info::see_info(const variant *stat, double _all)
{
    auto *mutable_stat = const_cast<variant *>(stat);
    mutable_stat->alf(_all);
    mutable_stat->spot();

    if (stat->input_data.size() == 1)
    {
        std::print("Послідовність:");
        for (auto const &data : stat->input_data.front()._l_data)
        {
            std::print(" {}", data);
        }
        std::print("\n");
    }

    else
    {
        int counter = 1;
        for (auto const &vars : stat->input_data)
        {
            std::print("Послідовність варіанту {}:", counter++);
            for (auto const &numbers : vars._l_data)
            {
                std::print(" {}", numbers);
            }
            std::print("\n");
        }
    }

    std::print("Альфа: {}\n", stat->alpha);
    std::print("Довірчий інтервал: {}\n", stat->confidence_interval);

    if (stat->input_data.size() == 1)
    {
        std::print("Середнє: {} [нижня межа: {} верхня межа: {}]\n",
                   stat->average, (stat->average - stat->confidence_interval),
                   (stat->average + stat->confidence_interval));
    }

    else
    {
        const std::string lines(90, '=');
        std::print("{}\n", lines);

        // using C++23 std::views::enumerate instead of old counters
        for (auto const &[i, var] : stat->input_data | std::views::enumerate)
        {
            std::print("Середнє по варіанту {}: {} [нижня межа: {} верхня межа: {}]\n",
                       i + 1, var.mid_aver(), (var.mid_aver() - stat->confidence_interval),
                       (var.mid_aver() + stat->confidence_interval));
        }
        std::print("{}\n", lines);
    }
}

void file_info::see_info(const variant *var, double _all)
{
    namespace fs = std::filesystem;
    namespace views = std::ranges::views;

    const fs::path file{"disp-stat.csv"};
    std::ofstream csv(file, std::ios::app);
    const std::locale loc{"uk_UA.utf8"};

    auto *mutable_var = const_cast<variant *>(var);
    mutable_var->alf(_all);
    mutable_var->spot();

    auto format_seq = [&](std::string_view label, auto &&seq)
    {
        auto quoted = seq | views::transform([&](const auto &v)
                                             { return std::format(loc, "\"{:L}\"", v); });
        return std::format("{}{}\n", std::format("\"{}\",", label), std::ranges::to<std::string>(quoted | views::join_with(',')));
    };

    if (var->input_data.size() == 1)
    {
        csv << format_seq("Послідовність:", var->input_data.front()._l_data);
    }
    else
    {
        auto lines = var->input_data | views::transform([&, i = 0](const auto &v) mutable
                                                        { return format_seq(std::format("Послідовність варіанту {}:", ++i),
                                                                            v._l_data); });
        csv << std::ranges::to<std::string>(lines | views::join);
    }

    auto write = [&](std::string_view label, const auto &value)
    {
        csv << std::format(loc, "\"{}\",\"{:L}\"\n", label, value);
    };

    write("Альфа:", var->alpha);
    write("Довірчий інтервал:", var->confidence_interval);

    auto avg_line = [&](std::string_view label, const auto &avg)
    {
        return std::format(
            loc,
            "\"{}\",\"{:L}\",\"нижня межа:\",\"{:L}\",\"верхня межа:\",\"{:L}\"",
            label, avg, avg - var->confidence_interval, avg + var->confidence_interval);
    };

    if (var->input_data.size() == 1)
    {
        csv << avg_line("Середнє:", var->average) << "\n\n";
    }
    
    else
    {
        auto lines = var->input_data | views::transform([&, i = 0](const auto &v) mutable
                                                        { return avg_line(std::format("Середнє по варіанту {}:", ++i), v.mid_aver()); });
        csv << std::ranges::to<std::string>(lines | views::join_with('\n')) << "\n\n";
    }

    std::print("Дані додані у файл {}\n", file.string());
}

//--------------------------------------------------

print_info::print_info(general_info *temp) : g_info(temp) {}
print_info::print_info(data_info *temp) : d_info(temp) {}

void print_info::_print() { g_info->see_info(); }
void print_info::_print(const variant &var, double _alf_temp) { d_info->see_info(&var, _alf_temp); }

print_info::~print_info()
{
    delete g_info;
    g_info = nullptr;

    delete d_info;
    d_info = nullptr;
}