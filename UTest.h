// Author: Xiaorui Tang
// Date: 07/12/2019

#ifndef _FRACTION_UTEST_H_
#define _FRACTION_UTEST_H_

#include <iostream>

const std::string pass_info = "pass";
const std::string fail_info = "fail";

class UTest
{
    std::string name;
    unsigned pass_cnt_;
    unsigned fail_cnt_;

public:
    UTest(const std::string &name) : name(name), pass_cnt_(0), fail_cnt_(0){};
    void test(const std::string &description, const bool state);
    void report();
};

#endif