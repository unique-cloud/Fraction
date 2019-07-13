// Author: Xiaorui Tang
// Date: 07/12/2019

#include "UTest.h"

void UTest::test(const std::string &description, const bool state)
{
    std::string info;
    if (state)
    {
        pass_cnt_++;
        info = pass_info;
    }
    else
    {
        fail_cnt_++;
        info = fail_info;
    }
    std::cout << name << ": " << description << " -> " << info << std::endl;
}

void UTest::report()
{
    std::cout << name << ": " << pass_cnt_ << " " << pass_info << ", "
              << fail_cnt_ << " " << fail_info << std::endl;
}
