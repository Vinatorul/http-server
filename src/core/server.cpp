#include <core/server.hpp>

#include <iostream>

#include <core/http.hpp>
#include <core/socket.hpp>

namespace core {

namespace {

const std::string kDefaultPort = "12345";
const std::string kDefaultHost = "127.0.0.1";
}

std::string Respond(std::string request) {
  std::cout << "Got request:" << request;
  const std::string reply = "HTTP/1.1 200 OK\r\n"
                            "Content-Type: application/json\r\n"
                            "Content-Length: 21\r\n"
                            "Accept-Ranges: bytes\r\n"
                            "Connection: close\r\n"
                            "\r\n"
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