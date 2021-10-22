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
                  "Alexander_I Nicholaus_I\n"
                  "Peter_II Paul_I\n"
                  "Alexander_I Anna";
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
    REQUIRE(buffer.str() == "Paul_I\n"
                            "Peter_I\n"
                            "Anna\n");
}
/*
TEST_CASE("test 014", ""){
    BENCHMARK("Longest file"){
    std::ifstream input( "../014", std::ofstream::in);
    std::ofstream output("../014.a", std::ofstream::trunc);

    parseFile(input,output);
    input.close();
    output.close();
    };

    BENCHMARK("Longest file, only adding"){
    std::ifstream input( "../014.onlyAdding", std::ofstream::in);
    std::stringstream output;

    parseFile(input,output);
    input.close();
    REQUIRE(output.str() == "");
    };
}

TEST_CASE("two trees", ""){
    std::stringstream input, output;
    input << "3\n"
             "A B\n"//B->A
             "C D\n"//D->C
             //Requests:
             "A B\n"//B
             "B A\n"//B
             "C D\n"//D
             "D C\n"//D
             "A C\n"//
             "A D\n"//
             "B C\n"//
             "B D\n"//
             "C A\n"//
             "C B\n"//
             "D A\n"//
             "D B\n"//
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "B\n"
            "B\n"
            "D\n"
            "D\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
    );
}

TEST_CASE("same", ""){
    std::stringstream input, output;
    input << "2\n"
             "A B\n"//B->A
             //Requests:
             "A A\n"//A
             "B B\n"//B
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "A\n"
            "B\n"
    );
}

TEST_CASE("root and lowest descendant", ""){
    std::stringstream input, output;
    input << "5\n"
             "B A\n"//A->B
             "C A\n"//A->C
             "E C\n"//C->E
             "D C\n"//C->E
             //Requests:
             "A E\n"//A
             "E A\n"//A
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "A\n"
            "A\n"
    );
}

TEST_CASE("root and middle descendant", ""){
    std::stringstream input, output;
    input << "5\n"
             "B A\n"//A->B
             "C A\n"//A->C
             "E C\n"//C->E
             "D C\n"//C->E
             //Requests:
             "A C\n"//A
             "C A\n"//A
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "A\n"
            "A\n"
    );
}

TEST_CASE("middle and its child", ""){
    std::stringstream input, output;
    input << "5\n"
             "B A\n"//A->B
             "C A\n"//A->C
             "E C\n"//C->E
             "D C\n"//C->E
             //Requests:
             "E C\n"//C
             "C E\n"//C
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "C\n"
            "C\n"
    );
}

TEST_CASE("middle 2 brothers", ""){
    std::stringstream input, output;
    input << "5\n"
             "B A\n"//A->B
             "C A\n"//A->C
             "E C\n"//C->E
             "D C\n"//C->E
             //Requests:
             "B C\n"//A
             "C B\n"//A
             "E D\n"//C
             "D E\n"//C
             ;
    parseFile(input,output);

    REQUIRE(output.str() ==
            "A\n"
            "A\n"
            "C\n"
            "C\n"
    );
}
*/
