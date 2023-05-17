#include <tinytest.h>

#include <iostream>

namespace {
using std::cout;
using TinyTest::TestResults;
}  // namespace

TestResults test_something() {
  return TestResults().Pass();
}

int main(int argc, char* argv[]) {
  TestResults results;

  results += test_something();

  PrintResults(cout, results);

  return results.Failed() + results.Errors();
}
