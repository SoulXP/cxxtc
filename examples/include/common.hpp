// Copyright (C) Stefan Olivier
// <https://stefanolivier.com>
// ----------------------------
// Description: Common header for cxxtc examples

#pragma once

// Standard headers
#include <algorithm>
#include <array>
#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <type_traits>
#include <concepts>
#include <filesystem>

// Library headers
#include "traits.hpp"

enum class ArgumentDataType : int 
{
    STRING,
    FLOAT,
    DOUBLE,
    SIGNED_INTEGER,
    UNSIGNED_INTEGER,
};

enum class ArgumentQuantityType : int 
{
    ZERO_OR_ONE,
    ZERO_OR_MORE,
    ONE_OR_MORE,
    ONLY_SPECIFIED,
    RANGE
};

enum class ArgumentSpecifierType : int 
{
    SWITCH,
    POSITIONAL,
    FLAG,
};

struct ArgumentParameter
{
    ArgumentDataType data_type;
    ArgumentSpecifierType flag_type;
    ArgumentQuantityType quantity;
    bool is_required;
    std::string_view argument_name;
};

template<std::size_t TotalArgs>
struct ArgumentParserConfiguration
{
    std::string_view name;
    std::string_view description;
    std::array<ArgumentParameter, TotalArgs> arguments;
};

template<std::size_t TotalArgs>
class ArgumentParser
{
public:
    constexpr ArgumentParser()
        : _total_args(0)
        , _program_name("")
        , _title("")
        , _description("")
        , _user_arguments({})
        , _program_arguments({})
    {}

    explicit ArgumentParser(int argc, char** argv,
                            const ArgumentParserConfiguration<TotalArgs>& configuration)
        : _total_args(argc)
        , _program_name(std::filesystem::path(argv[0]).filename())
        , _title(configuration.name)
        , _description(configuration.description)
        , _user_arguments({})
        , _program_arguments(configuration.arguments)
    {
        if (argc < 2) {
            throw std::runtime_error("not enough parameters provided to argument parser");
        }

        this->_user_arguments.reserve(argc - 1);
        for (int i = 1; i < argc; ++i) {
            this->_user_arguments.emplace_back(argv[i]);
         }
    }

    ~ArgumentParser()
    {

    }

public:
    void print_title() const
    {
        std::cout << this->_program_name << "\n\n"
                  << "DESCRIPTION:\n"
                  << this->_title << "\n\n"
                  << "    " << this->_description << "\n\n";
    }

    void print_help() const
    {
        std::cout << "    -h,--help\n"
                  << "        " << "prints this help message\n";
    }

    void print_usage() const
    {
        this->print_title();
        std::cout << "USAGE: " << this->_program_name << " [-h] ";

        for (const auto& arg : this->_program_arguments) {
            if (arg.flag_type == ArgumentSpecifierType::POSITIONAL) {
                std::cout << '<' << arg.argument_name << "> ";
            }
        }

        std::cout << "\n\n";
        this->print_help();
    }

private:
    int _total_args;
    std::string _program_name;
    std::string_view _title;
    std::string_view _description;
    std::vector<std::string_view> _user_arguments;
    std::array<ArgumentParameter, TotalArgs> _program_arguments;
};

template<std::invocable<int, char**> auto Wrapper, typename TCallable = decltype(Wrapper)>
class ArgumentParserInterface
{
public:
    using my_type = ArgumentParserInterface<Wrapper, TCallable>;

    void parse_args(int argc, char** argv)
    {
        return my_type::parser_wrapper(argc, argv);
    }

private:
    static constexpr std::remove_cvref_t<TCallable> parser_wrapper = Wrapper;
};

class ArgumentParserBuilder
{
public:
    template<std::size_t N>
    [[nodiscard("new argument parser must be consumed")]]
    static consteval auto new_parser(ArgumentParserConfiguration<N> configuration)
    {
        return [configuration](int argc, char** argv) {
            return ArgumentParser<N>(argc, argv, configuration);
        };
    }

    template<typename... Args, std::size_t N = sizeof...(Args)>
        requires cxxtc::traits::identical_v<ArgumentParameter, Args...>
    static consteval ArgumentParserConfiguration<N> new_configuration(std::string_view name,
                                                                      std::string_view description,
                                                                      Args... arguments)
    {
        std::array<ArgumentParameter, N> arguments_list{ arguments... };

        return ArgumentParserConfiguration<N> {
            .name = name,
            .description = description,
            .arguments = arguments_list,
        };
    }

    static consteval ArgumentParameter new_argument(std::string_view argument_name,
                                                    std::string_view data_type_string = "string",
                                                    std::string_view quantity_string = "*",
                                                    int quantity_specifier = 1)
    {
        ArgumentDataType data_type = ArgumentDataType::STRING;
        ArgumentSpecifierType flag_type = ArgumentSpecifierType::POSITIONAL;
        ArgumentQuantityType quantity = ArgumentQuantityType::ONLY_SPECIFIED;

        return ArgumentParameter {
            .data_type = data_type,
            .flag_type = flag_type,
            .quantity = quantity,
            .argument_name = argument_name
        };
    }
};
