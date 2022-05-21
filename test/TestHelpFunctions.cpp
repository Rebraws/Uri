#include <gtest/gtest.h>
#include <algorithm>
#include <string_view>
#include <string>
#include "UriTest.h"
#include <AfterUri/parseFunctions.h>

TEST(HelpFunc, extract_hostname)
{
  using namespace std::string_view_literals;

  std::string authority = "www.example.com";

  auto hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "www.example.com"sv);

  authority = "example.com";
  hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "example.com"sv);

  authority = "www.example.com:80";
  hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "www.example.com"sv);

  authority = "rebraws@www.example.com:80";
  hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "www.example.com"sv);

  authority = "username:password@subdomain.example.com:8000";
  hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "subdomain.example.com"sv);

  authority = "[2001:0db8:85a3:0000:0000:8a2e:0370:7334]";
  hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "[2001:0db8:85a3:0000:0000:8a2e:0370:7334]"sv);

  authority = "username:password123@[2001:0db8:85a3:0000:0000:8a2e:0370:7334]";
  hostname = internalFunc::extract_hostname(authority);
  EXPECT_EQ(hostname, "[2001:0db8:85a3:0000:0000:8a2e:0370:7334]"sv);
}
