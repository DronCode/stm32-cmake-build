//
// Created by droncode on 11/20/17.
//

#include "CppTest.h"

cxx_mcu::CppTest &cxx_mcu::CppTest::get() {
    static cxx_mcu::CppTest* instance = nullptr;

    if (!instance)
    {
        instance = new CppTest;
    }

    return *instance;
}

int cxx_mcu::CppTest::operator()(int a, int b) const {
    return (a + b) * a;
}
