#pragma once

/**
 * @desc: Test C++ support
 * @note: Uncomment to check that this file uses in build
 */
//#error ERROR

namespace cxx_mcu {
    class CppTest {
    public:
        static CppTest& get();

        CppTest() = default;
        ~CppTest() noexcept = default;

        int operator()(int a, int b) const;
    };
}