#include <AfterUri/stdExtension.h>
#include <AfterUri/parseFunctions.h>

#include <string>
#include <string_view>
#include <algorithm>
#include <charconv>

#include <iostream> // debug

#ifdef _WIN32
#include <ws2tcpip.h>
#include <in6addr.h>

#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

namespace internalFunc {
using namespace AfterUri;

auto str_view_to_int(const std::string_view number) -> std::optional<int>
{

  int out;
  const std::from_chars_result result =
    std::from_chars(number.data(), number.data() + number.size(), out);

  if (result.ec == std::errc::invalid_argument
      || result.ec == std::errc::result_out_of_range) {
    return {};
  }

  return out;
}


auto parse_scheme(std::span<const char>& uri_str, Error& error)
  -> std::optional<std::string>
{

  const auto scheme_end = std::ranges::find(uri_str, ':');
  
  if (std::next(scheme_end) != uri_str.end() && 
      *std::next(scheme_end) == ':') {
    error = Error::UNKOWN_ERROR;
    return {};
  }

  if (scheme_end != uri_str.end() && scheme_end != uri_str.begin()) {
    String scheme(uri_str.begin(), scheme_end, ::tolower);
    uri_str = std::span<const char>(std::next(scheme_end), uri_str.end());
    return static_cast<std::string>(scheme);
  }

  error = Error::NO_SCHEME;

  return {};
}


auto check_ip(const std::string_view ip_address, int af) -> Error
{
  
  if (ip_address.size() < 3) {
    return Error::UNKOWN_ERROR;
  }

  int result{};
  std::string ip;
  if (af == AF_INET6) {
    ip = std::string(std::next(ip_address.begin()), 
        std::prev(ip_address.end()));
    in6_addr addr;
    result = inet_pton(af, ip.c_str(), &(addr));

  } else {
    ip = ip_address; 
    in_addr addr;
    result = inet_pton(af, ip.c_str(), &(addr));
  }
  /*  If result is zero then is not a valid IPv4 dotted-decimal string
   *  or a valid IPv6 address string*/
  if (result == 0) {
    return af == AF_INET ? Error::INVALID_IPv4 : Error::INVALID_IPv6;
  }

  return Error::OK;
}

auto check_hostname(const std::string_view hostname) -> Error
{

  Error error = Error::OK;

   /*Check if it contains only numbers, '.' and ':'
   *
   *TODO: Should check that : only appears at most once if it's an ipv4 
   */
  const auto isIPv4 = [](const std::string_view ip) -> bool {
    return std::ranges::find_if(ip, [](const auto character) -> bool {
      return !std::isdigit(character) || character != '.' || character != ':';
    }) == ip.end();
  };


  if (*hostname.begin() == '[' && *std::prev(hostname.end()) == ']') {
    error = check_ip(hostname, AF_INET6);
  } else if (isIPv4(hostname)) {
    error = check_ip(hostname, AF_INET);
  }

  return error;
}


/*
 *  authority = [userinfo "@"] host [":" port ]
 *
 *  The authority component is preceeded by a double slash("//")
 *  and is terminated by the next slash, question mark, or number sign,
 *  or by the end of the URI
 * */
auto parse_authority(std::span<const char>& uri_str)
  -> std::optional<std::string>
{

  if (uri_str.begin() == uri_str.end() || std::next(uri_str.begin()) == uri_str.end() || *uri_str.begin() != '/' || *std::next(uri_str.begin()) != '/') {
    return {};
  }

  auto end_authority = std::find_if(uri_str.begin() + 2, uri_str.end(),
      [](const auto character) -> bool { 
        return character == '/' || character == '?' || character == '#'
      ;});

  String authority(uri_str.begin() + 2, end_authority, ::tolower);
  
  if (end_authority != uri_str.end()) {
    uri_str =
      std::span<const char>(std::next(end_authority), uri_str.end());
  }
  
  return static_cast<std::string>(authority);
}


auto authority_contains_port(const std::string& authority) -> bool {
 

  auto bracket = std::ranges::find(authority, ']');

  if (bracket != authority.end() ) {
    return std::next(bracket) != authority.end() ? *std::next(bracket) == ':' : false;
  }

  return std::ranges::find(authority, ':') != authority.end();

}


auto extract_user_info(const std::string& authority) -> std::optional<std::string> {
  
  auto end_user_info = std::ranges::find(authority, '@');

  if (end_user_info == authority.end()) {
    return {};
  }

  return std::string(authority.begin(), end_user_info);
}

auto extract_port_number(const std::string& authority) -> std::uint16_t {

  auto bracket = std::ranges::find(authority, ']');
  std::string_view port;
  if (bracket != authority.end()) {
    port = std::string_view(bracket + 2, authority.end());
  } else {
    port = std::string_view(std::next(std::ranges::find(authority, ':')), 
        authority.end());
  }
  // Maybe implement something like narrow_cast, to throw if the value
  // changes when doing the type conversion
  return static_cast<std::uint16_t>(str_view_to_int(port).value_or(0));
}

// extracts the hostname from a non-empty authority
auto extract_hostname(std::string_view authority) -> std::string_view {

  // Check if it has user info 
  auto end_user_info = std::ranges::find(authority, '@');

  if (end_user_info != authority.end()) {
    authority = std::string_view(std::next(end_user_info), authority.end());
  }


  // check if hostname it's a possible ipv6
  if (*authority.begin() == '[') {
    auto end_ipv6 = std::ranges::find(authority, ']');

    return std::string_view(authority.begin(), 
        end_ipv6 != authority.end() ? std::next(end_ipv6) : authority.end());

  }

  const auto end_hostname = std::find(authority.rbegin(), authority.rend(), ':');
  if (end_hostname == authority.rend()) {
    return std::string_view(authority.begin(), authority.end());
  }

  return std::string_view(authority.begin(), std::prev(end_hostname.base()));
}

} // namespace internalFunc
