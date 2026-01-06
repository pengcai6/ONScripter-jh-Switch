/* -*- C++ -*-
 *
 *  test_main.cpp - Main entry point for ONScripter-jh-Switch test suite
 *
 *  Copyright (C) 2025 ONScripter-jh-Switch contributors
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 */

#include "test_framework.h"

// Include all test files
// The TEST_CASE macros in these files auto-register tests
#include "test_encoding.cpp"
#include "test_lua_animation.cpp"
#include "test_coordinates.cpp"
#include "test_rendering.cpp"

int main(int argc, char* argv[]) {
    printf("ONScripter-jh-Switch Unit Tests\n");
    printf("================================\n\n");

    // Check for filter argument
    const char* filter = nullptr;
    if (argc > 1) {
        filter = argv[1];
        printf("Filter: %s\n", filter);
    }

    // Run tests
    int failed = 0;
    if (filter) {
        failed = TestFramework::runTests(filter);
    } else {
        failed = TestFramework::runAllTests();
    }

    // Return exit code (0 = success, non-zero = failure count)
    return failed;
}
