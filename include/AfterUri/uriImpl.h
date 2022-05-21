#ifndef URIIMPL_H_
#define URIIMPL_H_
#include <AfterUri/stdExtension.h>
#include <AfterUri/parseFunctions.h>
#include <AfterUri/uri.h>

using namespace InternalUriStdExt;
struct AfterUri::Uri::UriImpl {

  auto parse(std::span<const char> uri_str) -> Error {
    using namespace std::string_literals; 
    Error error = Error::OK;
    scheme = internalFunc::parse_scheme(uri_str, error).value_or(""s);

    if (error != Error::OK) {
      return error;
    }

    authority = internalFunc::parse_authority(uri_str).value_or(""s);

    if (!authority.empty()) {
      userInfo = internalFunc::extract_user_info(authority).value_or(""s); 
      
      const auto hostname =
          internalFunc::extract_hostname(authority);
      error = internalFunc::check_hostname(hostname);
      
      if (error != Error::OK) {
        return error;
      }
      
    } else {
      userInfo.clear();
    }

    containsPort = internalFunc::authority_contains_port(authority);
    port = containsPort ? internalFunc::extract_port_number(authority) : 0U;

    return error;
  }

  auto getScheme() const noexcept -> const std::string & { return scheme; }

  auto getAuthority() const noexcept -> const std::string & {
    return authority;
  }

  auto getPort() const noexcept -> std::uint16_t { return port; }

  auto hasPort() const noexcept -> bool { return containsPort; }

  auto getQuery() const noexcept -> const std::string& { return query; }

  bool containsPort{false};
  std::uint16_t port;
  std::string scheme;
  std::string authority;
  std::string userInfo;
  std::vector<std::string> paths;
  std::string query;
  std::string fragmentId;
};

#endif
