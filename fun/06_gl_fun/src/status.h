#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status {
public:
  enum Id { SUCCESS = 0, QUIT_EVENT, FAILURE };

  Status() {}
  Status(Id code, const std::string &msg) : m_id(code), m_msg(msg) {}

  Id getId() const { return m_id; }

  operator bool() const { return m_id < FAILURE; }

  friend std::ostream &operator<<(std::ostream &os, const Status &status) {
    os << status.m_msg;
    return os;
  }

private:
  Id m_id = SUCCESS;
  std::string m_msg;
};

#endif
