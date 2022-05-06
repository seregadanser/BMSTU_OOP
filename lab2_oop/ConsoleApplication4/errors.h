#pragma once
#include <exception>
#include <iostream>
//#include <string>
#include <sstream>


class BaseErrors : public std::exception
{
public:
    BaseErrors(const std::string& time ,std::string filename, int line, std::string operation, std::string info = "Ошибка")
    {
        err_info = "\nFile name: " + filename + "\nNumber of line: " + std::to_string(line) + "\nIn operation: "+  operation  + "\nInfo: " + info + "\nTime"+ time;
    }
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
protected:
	std::string err_info;
};

class NullElemError : public BaseErrors
{
public:
    NullElemError(const std::string& time, std::string filename, int line, std::string operation, std::string info = "Invalible number of elements") : BaseErrors(time, filename, line, operation, info) {};
};

class MemError : public BaseErrors
{
public:
    MemError(const std::string& time, std::string filename, int line, std::string operation, std::string info = "Memory error") : BaseErrors(time, filename, line, operation, info) {};
};

class NoPtr : public BaseErrors
{
public:
    NoPtr(const std::string& time, std::string filename, int line, std::string operation, std::string info = "No ptr") : BaseErrors(time, filename, line, operation, info) {};
};

class IndexError : public BaseErrors
{
public:
    IndexError(const std::string& time, std::string filename, int line, std::string operation, std::string info = "Index out of range") : BaseErrors(time, filename, line, operation, info) {};
};

class ZerroDivisionError : public BaseErrors
{
public:
    ZerroDivisionError(const std::string& time, std::string filename, int line, std::string operation, std::string info = "Zerro division") : BaseErrors(time, filename, line, operation, info) {};
};

class DifferLen : public BaseErrors
{
public:
    DifferLen(const std::string& time, std::string filename, int line, std::string operation, std::string info = "Different vec len") : BaseErrors(time, filename, line, operation, info) {};
};
