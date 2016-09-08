#pragma once

#ifndef STYLE_MKZINF_H_
#define STYLE_MKZINF_H_

#include <iostream>
#include <string>

namespace maikaze
{
    class MkzInf
    {
    public:
        MkzInf() {}
        MkzInf(std::int32_t p_code, std::string p_string) { err_code_ = p_code; detail_ = p_string; }
        ~MkzInf() {}

        void ShowErr() { std::cout << "error code:" << err_code_ << "  detail: " << detail_ << std::endl; }

    private:
        std::int32_t err_code_;
        std::string detail_;
    };
}
#endif // !STYLE_MKZINF_H_
