#ifndef URI_H_
#define URI_H_

/** @file uri.h
 *
 *  This header file declares the AfterUri::Uri class
 *
 *
 *  @author Rebraws
 *
 * */

#include <string>
#include <span>
#include <vector>
#include <memory>

#include <AfterUri/Error.h>

namespace AfterUri {


/** @brief This class represents a Uniform Resource Identifier
 *
 *
 * */
class Uri
{
public:
  /** @brief Default constructor
   * */
  Uri();

  /** @brief Constructor that tries to parse the URI, if it fails an
   * exception is thrown
   *
   * */
  Uri(std::span<const char> uriStr);


  Uri(const Uri& copyFrom) = delete;
  auto operator=(const Uri& rhs) -> Uri& = delete;

  Uri(Uri&& moveFrom) noexcept;
  auto operator=(Uri&& rhs) noexcept -> Uri&;
  ~Uri();

  /** @brief Parses the uriStr
   *
   * @param[in] uriStr
   *    The uri to parse
   *
   * @return
   *    void
   * */
  [[nodiscard]] auto parseFrom(std::span<const char> uriStr) noexcept -> Error;

  /** @brief Checks whether the parsed uri is valid or not
   *
   * @return
   *    Returns an `Error` value that indicates if the parsing succeded or not
   * */
  [[nodiscard]] auto isValid() const noexcept -> Error;

  /** @brief Returns the scheme as an std::string
   *
   *  @return
   *      A `std::string` that represents the scheme
   *
   * */
  [[nodiscard]] auto getScheme() const noexcept -> const std::string&;

  /**
   * @brief Returns the authority
   *
   *
   * @return
   *    A `std::string` that represents the authority
   * */
  [[nodiscard]] auto getAuthority() const noexcept -> const std::string&;

  /**
   * @brief Returns the port number if is present in the uri
   *
   *
   * @return
   *    A `std::uint16_t` that represents the port number
   * */
  [[nodiscard]] auto getPort() const noexcept -> std::uint16_t;
  /**
   * @brief Checks if the uri contains a port number
   *
   *
   * @return
   *    Returns `true` if a port is present if the uri, `false` otherwise
   * */

  [[nodiscard]] auto hasPort() const noexcept -> bool;

private:
  struct UriImpl;
  Error mError{Error::OK};
  std::unique_ptr<UriImpl> pUri{nullptr};
};


}// namespace AfterUri


#endif
