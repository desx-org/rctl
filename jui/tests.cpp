#include "utility.hpp"

#include "fmt/format.h"
#include <catch2/catch_test_macros.hpp>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>
#include <locale>

using namespace fmt;

TEST_CASE("aix buffer test","")
{
    std::locale::global(std::locale(""));

    print("start tests\n");

    REQUIRE(do_thing(1) == "do thing: 1");

}
