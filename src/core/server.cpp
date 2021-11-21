#include <core/server.hpp>

#include <core/http.hpp>
#include <core/socket.hpp>

namespace core {

namespace {

const std::string kDefaultPort = "12345";
const std::string kDefaultHost = "127.0.0.1";
}

std::string Respond(std::string /*request*/) {
  const std::string reply = "HTTP/1.1 200 OK\n"
                            "Content-Type: application/json\n"
                            "Content-Length: 21\n"
                            "Accept-Ranges: bytes\n"
                            "Connection: close\n"
                            "\n"
                            "{\"data\": \"some-json\"}";
  return reply;
}

void ServeForever() {
  int socket_descriptor = InitSocket(kDefaultHost, kDefaultPort);
  if (socket_descriptor < 0) {
    return;
  }

  while (true) {
    AcceptConnection(socket_descriptor, Respond);
  }
}
}