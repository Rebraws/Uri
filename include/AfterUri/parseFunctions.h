#ifndef PARSEFUNCTIONS_H_
#define PARSEFUNCTIONS_H_

#include <AfterUri/Error.h>
#include <AfterUri/stdExtension.h>
#include <optional>
#include <span>
#include <string>
#include <string_view>

namespace internalFunc {
using namespace AfterUri;
using InternalUriStdExt::String;
  /** @brief Checks if `ip_address` is a valid IPv4 or IPv6 address
 *
 * @param[in] ip_address
 *    IPv4 or IPv6 address as an string
 * @param[in] af
 *    The address family (AF_INET or AF_INET6)
 *
 * @return
 *    Returns `Error::OK` if it's a valid address, otherwise it returns either
 *    Error::INVALID_IPv4 or Error::INVALID_IPv6
 * */
auto check_ip(const std::string_view ip_address, int af) -> Error;

auto check_hostname(const std::string_view hostname) -> Error;
/** @brief Searchs and returns the scheme in an URI string
 *
 *  @param[in] uri_str
 *    Uri to be parsed
 *
 *  @return
 *    Returns the scheme of the URI as an std::string, if it's not found
 *    then it returns a std::nullopt
 * */
auto parse_scheme(std::span<const char> &uri_str, Error &error)
    -> std::optional<std::string>;

/** @brief Returns the authority of the URI
 *
 *  @param[in] uri_str
 *    URI string to be parsed
 *
 *  @return
 *     Returns the authority of the URI as an std::string, if no authority is
 * found then it returns std::nullopt
 * */
auto parse_authority(std::span<const char> &uri_str)
    -> std::optional<std::string>;

auto authority_contains_port(const std::string &authority) -> bool;

auto extract_user_info(const std::string &authority)
    -> std::optional<std::string>;
auto extract_port_number(const std::string &authority) -> std::uint16_t;
auto extract_hostname(std::string_view authority) -> std::string_view;

} // namespace internalFunc

#endif
