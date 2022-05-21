#include <AfterUri/uri.h>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <AfterUri/uriImpl.h>

namespace AfterUri {

Uri::Uri() : mError(Error::OK), pUri(new UriImpl()) {}

Uri::Uri(std::span<const char> uriStr) : mError(Error::OK), pUri(new UriImpl())
{

  mError = pUri->parse(uriStr);

  switch (mError) {
  case Error::OK:
    break;
  case Error::NO_SCHEME:
    throw std::logic_error{ "No scheme present in URI" };
    break;
  default:
    throw std::logic_error{ "Unkown ERROR" };
  }
}

Uri::Uri(Uri&& moveFrom) = default;
auto Uri::operator=(Uri&& rhs) -> Uri& = default;
Uri::~Uri() = default;

auto Uri::parseFrom(const std::span<const char> uriStr) noexcept -> Error
{
  mError = pUri->parse(uriStr);
  return mError;
}

auto Uri::isValid() const noexcept -> Error { return mError; }

auto Uri::getScheme() const noexcept -> std::string
{
  return pUri->getScheme();
}

auto Uri::getAuthority() const noexcept -> std::string
{
  return pUri->getAuthority();
}

auto Uri::hasPort() const noexcept -> bool { return pUri->hasPort(); }

auto Uri::getPort() const noexcept -> std::uint16_t { return pUri->getPort(); }

}// namespace AfterUri
