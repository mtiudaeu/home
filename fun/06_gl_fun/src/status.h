#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status {
public:
  enum Id { SUCCESS = 0, FAILURE };

  Status() {}
  Status(Id code, const std::string& msg) :
    m_code(code),
    m_msg(msg)
  {
  }
  operator bool() const { return m_code >= FAILURE; }

  friend std::ostream &operator<<(std::ostream &os, const Status& status) {
    os << status.m_msg;
    return os;
  }

private:
  Id m_code;
  std::string m_msg;
};



#endif
