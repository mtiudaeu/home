#ifndef MACROS_H
#define MACROS_H

#include <stdexcept>
#include <iostream>
#include <assert.h>

#define THROW_ERR(msg)                                               \
  throw std::runtime_error(std::string("Exception : ") + msg + ' ' + \
                           __FILE__ + ':' + std::to_string(__LINE__));

#define LOG_ERROR(msg)                                                 \
  std::cerr << std::string("Error : ") + msg << ' ' << __FILE__ << ':' \
            << __LINE__ << '\n';

#define LOG_INFO(msg)                                                 \
  std::cout << std::string("Info : ") + msg << ' ' << __FILE__ << ':' \
            << __LINE__ << '\n';

#define LOG_DEBUG(msg)                                                 \
  std::cout << std::string("Debug : ") + msg << ' ' << __FILE__ << ':' \
            << __LINE__ << '\n';

#endif
