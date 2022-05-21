#ifndef ERROR_H_
#define ERROR_H_

/** @file Error.h
 *
 *  This files declared the AfterUri::Error enum class
 *
 *  @author Rebraws
 * */


namespace AfterUri {

enum class Error {
  OK, 
  NO_SCHEME,
  UNKOWN_ERROR,
  INVALID_IPv4,
  INVALID_IPv6,
};

}

#endif
