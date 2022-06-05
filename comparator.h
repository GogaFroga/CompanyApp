#pragma once

#ifndef COURSEWORK_COMPARATOR_H
#define COURSEWORK_COMPARATOR_H
#include <algorithm>
#include <string>

template <typename T>
class Comparator
{
public:
    virtual bool compare(const T& num1, const T& num2) = 0;
    virtual ~Comparator() = default;
};

class CMP_INT_EQ : public Comparator<int>
{
public:
    bool compare(const int& num1, const int& num2) override;
};

bool CMP_INT_EQ::compare(const int& num1, const int& num2)
{
    if (num1 == num2)
        return true;
    else
        return false;
}

class CMP_INT : public Comparator<int>
{
public:
    bool compare(const int& num1, const int& num2) override;
};

bool CMP_INT::compare(const int& num1, const int& num2)
{
    if (num1 > num2)
        return true;
    return false;
}

class CMP_STR : public Comparator<std::string>
{
public:
    bool compare(const std::string& num1, const std::string& num2) override;
};

bool CMP_STR::compare(const std::string& num1, const std::string& num2)
{
    if (num1 == num2)
        return true;
    return false;
}

#endif //COURSEWORK_COMPARATOR_H
