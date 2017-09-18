#include <stdexcept>

#define THROW_ERR(msg)                                                      \
  throw std::runtime_error(std::string("Error : ") + msg + ' ' + __FILE__ + \
                           ':' + std::to_string(__LINE__));

