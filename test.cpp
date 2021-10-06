#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"9\n"
                  "Alexei Peter_I\n"
                  "Anna Peter_I\n"
                  "Elizabeth Peter_I\n"
                  "Peter_II Alexei\n"
                  "Peter_III Anna\n"
                  "Paul_I Peter_III\n"
                  "Alexander_I Paul_I\n"
                  "Nicholaus_I Paul_I\n"
                  "Anna Nicholaus_I\n"
                  "Peter_II Peter_I\n"
                  "Alexei Paul_I";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "1 2 0 ");
}

