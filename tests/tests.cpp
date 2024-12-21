#include "../src/iwcpp.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Testing Sample File 1 : Strings") {
    string expectedOutput = "Hello World\n";
    stringstream capturedOutput; // Create a stringstream to capture output
    
    streambuf* originalCoutBuffer = cout.rdbuf(); // Backup the original std::cout stream

    cout.rdbuf(capturedOutput.rdbuf()); // Redirect std::cout to the stringstream

    IWCPP code("tests/sampFiles/test1.iwc");  // Run the executable with test.iwc
    code.run();

    cout.rdbuf(originalCoutBuffer); // Restore the original std::cout stream

    REQUIRE(capturedOutput.str() == expectedOutput);  // Check if the program ran successfully
}

TEST_CASE("Testing Sample File 2 : Ints") {
    string expectedOutput = "3\n";
    stringstream capturedOutput; // Create a stringstream to capture output
    
    streambuf* originalCoutBuffer = cout.rdbuf(); // Backup the original std::cout stream

    cout.rdbuf(capturedOutput.rdbuf()); // Redirect std::cout to the stringstream

    IWCPP code("tests/sampFiles/test2.iwc");  // Run the executable with test.iwc
    code.run();

    cout.rdbuf(originalCoutBuffer); // Restore the original std::cout stream

    REQUIRE(capturedOutput.str() == expectedOutput);  // Check if the program ran successfully
}

TEST_CASE("Testing Sample File 3 : Floats") {
    string expectedOutput = "6.280000\n";
    stringstream capturedOutput; // Create a stringstream to capture output
    
    streambuf* originalCoutBuffer = cout.rdbuf(); // Backup the original std::cout stream

    cout.rdbuf(capturedOutput.rdbuf()); // Redirect std::cout to the stringstream

    IWCPP code("tests/sampFiles/test3.iwc");  // Run the executable with test.iwc
    code.run();

    cout.rdbuf(originalCoutBuffer); // Restore the original std::cout stream

    REQUIRE(capturedOutput.str() == expectedOutput);  // Check if the program ran successfully
}

TEST_CASE("Testing Sample File 4 : Output") {
    string expectedOutput = "Hello World";
    ifstream ins;

    IWCPP code("tests/sampFiles/test4.iwc");  // Run the executable with test.iwc
    code.run();

    ins.open("testOutput.txt");
    string testOutput;
    getline(ins, testOutput);

    REQUIRE(testOutput == expectedOutput);  // Check if the program ran successfully
}

TEST_CASE("Testing Sample File 5 : Input") {
    string expectedOutput = "Hello World\n";
    stringstream capturedOutput; // Create a stringstream to capture output
    
    streambuf* originalCoutBuffer = cout.rdbuf(); // Backup the original std::cout stream

    cout.rdbuf(capturedOutput.rdbuf()); // Redirect std::cout to the stringstream

    IWCPP code("tests/sampFiles/test5.iwc");  // Run the executable with test.iwc
    code.run();

    cout.rdbuf(originalCoutBuffer); // Restore the original std::cout stream

    REQUIRE(capturedOutput.str() == expectedOutput);  // Check if the program ran successfully
}