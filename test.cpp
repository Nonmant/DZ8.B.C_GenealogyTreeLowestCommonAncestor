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

TEST_CASE("test 002", ""){
    std::ifstream input( "../002", std::ofstream::in);
    std::stringstream output;
    parseFile(input,output);
    input.close();

    REQUIRE(output.str() ==
  // I J L M O P T W X
    "1 0 0 0 0 2 0 0 0 "//A
  // A J L M O P T W X
    "2 0 0 0 0 2 0 0 0 "//I
  // A I L M O P T W X
    "0 0 0 0 1 2 0 0 0 "//J
  // A I J M O P T W X
    "0 0 0 0 0 2 0 2 0 "//L
  // A I J L O P T W X
    "0 0 0 0 0 2 0 0 0 "//M
  // A I J L M P T W X
    "0 0 2 0 0 2 0 0 0 "//O
  // A I J L M O T W X
    "1 1 1 1 1 1 1 1 1 "//P
  // A I J L M O P W X
    "0 0 0 0 0 0 2 0 0 "//T
  // A I J L M O P T X
    "0 0 0 1 0 0 2 0 0 "//W
  // A I J L M O P T W
    "0 0 0 0 0 0 2 0 0 "//X
    );
}

TEST_CASE("two trees", ""){
    std::stringstream input, output;
    input << "3\n"
             "A B\n"//B->A
             "C D\n"//D->C
             //Requests:
             "A B\n"//2
             "B A\n"//1
             "C D\n"//2
             "D C\n"//1
             "A C\n"//0
             "A D\n"//0
             "B C\n"//0
             "B D\n"//0
             "C A\n"//0
             "C B\n"//0
             "D A\n"//0
             "D B\n"//0
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "2 "
            "1 "
            "2 "
            "1 "
            "0 "
            "0 "
            "0 "
            "0 "
            "0 "
            "0 "
            "0 "
            "0 "
    );
}

