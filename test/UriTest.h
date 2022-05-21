#ifndef URITEST_H_
#define URITEST_H_

#include <gtest/gtest.h>
#include <AfterUri/AfterUri.h>
#include <vector>
#include <string>
class UriTest : public ::testing::Test {
public:
  auto SetUp() -> void override;    

  struct TestCase {
    std::string uri;
    std::string authority;
    std::string scheme;
    std::vector<std::string> path;
    std::string queryStr;
    std::string fragment;
    bool has_port;
    std::uint16_t port;
    AfterUri::Error error;

  };
  
  std::vector<TestCase> mTestCases;


};


#endif
