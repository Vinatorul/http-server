#include <core/http.hpp>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace core {

namespace {

void InitServer() {
  // constexpr struct addrinfo hints {
  //   AI_PASSIVE,      /* ai_flags */
  //       AF_UNSPEC,   /* ai_family */
  //       SOCK_STREAM, /* ai_socktype */
  //       0            /* ai_protocol */
  // };
}
}

void ServeForever() { InitServer(); }
}
