#include <gtest/gtest.h>
#include "UriTest.h"
#include <algorithm>




TEST_F(UriTest, isValid) {
 AfterUri::Uri parsed;
  for (auto& test : mTestCases) {
    parsed.parseFrom(test.uri);
    EXPECT_EQ(parsed.isValid(), test.error) << test.uri;
  }
}

TEST_F(UriTest, getScheme) {
  std::ranges::for_each(mTestCases, [](const auto test) -> void {
      AfterUri::Uri parsed;
      parsed.parseFrom(test.uri);
      EXPECT_EQ(parsed.getScheme(), test.scheme) << test.uri;
      });
}


TEST_F(UriTest, getAuthority) {
 AfterUri::Uri parsed;
  for (auto& test : mTestCases) {
    parsed.parseFrom(test.uri);
    EXPECT_EQ(parsed.getAuthority(), test.authority) << test.uri;
  }


}

TEST_F(UriTest, hasPort) {
  AfterUri::Uri parsed;
  for (auto& test : mTestCases) {
    parsed.parseFrom(test.uri);
    EXPECT_EQ(parsed.hasPort(), test.has_port) << test.uri;
  }

}

TEST_F(UriTest, getPort) {
  AfterUri::Uri parsed;
  for (auto& test : mTestCases) {
    parsed.parseFrom(test.uri);
    EXPECT_EQ(parsed.getPort(), test.port) << test.uri;
  }
  
}



