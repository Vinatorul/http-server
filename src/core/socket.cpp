#include <core/socket.hpp>

#include <cstring>
#include <iostream>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace core {

namespace {

const int kQueueSize = 10000;

const int kBufSize = 65535;

std::string RecieveData(int socket_descriptor) {
  std::string request;
  static char buf[kBufSize];

  while (1) {
    memset(buf, 0, kBufSize);
    auto recv_size = recv(socket_descriptor, buf, kBufSize, 0);
    if (recv_size > 0) {
      request += buf;
    } else {
      break;
    }
  }

  return request;
}

void Respond(int socket_descriptor,
             std::function<std::string(std::string)> responder_callback) {
  auto response = responder_callback(RecieveData(socket_descriptor));
  send(socket_descriptor, response.c_str(), response.size(), 0);
}
}

int InitSocket(const std::string &hostname, const std::string &service) {
  constexpr struct addrinfo hints {
    AI_PASSIVE,      /* ai_flags */
        AF_UNSPEC,   /* ai_family */
        SOCK_STREAM, /* ai_socktype */
        0,           /* ai_protocol */
        0,           /* ai_addrlen */
        nullptr,     /* ai_addr */
        nullptr,     /* ai_canonname */
        nullptr,     /* ai_next */
  };
  struct addrinfo *options;
  int socket_descriptor = -1;

  if (auto error =
          getaddrinfo(hostname.c_str(), service.c_str(), &hints, &options)) {
    std::cerr << "getaddrinfo error: " << gai_strerror(error) << std::endl;
    return -1;
  }

  for (auto option = options; option != nullptr; option = option->ai_next) {
    socket_descriptor =
        socket(option->ai_family, option->ai_socktype, option->ai_protocol);

    int reuse_address = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &reuse_address,
               sizeof(reuse_address));

    constexpr struct timeval tv { 0, 10000 };
    setsockopt(socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    if (socket_descriptor == -1) {
      continue;
    }

    if (bind(socket_descriptor, option->ai_addr, option->ai_addrlen) == 0) {
      break;
    }

    close(socket_descriptor);
  }

  freeaddrinfo(options);

  if (socket_descriptor == -1) {
    std::cerr << "Could not bind socket" << std::endl;
    return -1;
  }
  if (auto error = listen(socket_descriptor, kQueueSize)) {
    std::cerr << "Listen error: " << error << std::endl;
    return -1;
  }
  return socket_descriptor;
}

void AcceptConnection(
    int socket_descriptor,
    std::function<std::string(std::string)> responder_callback) {
  struct sockaddr client_address;
  socklen_t addrlen = sizeof(client_address);
  int client = accept(socket_descriptor, &client_address, &addrlen);
  if (client == -1) {
    return;
  }

  std::cout << "Accepted connection" << std::endl;

  if (fork() == 0) {
    close(socket_descriptor);
    Respond(client, responder_callback);
    close(client);
    exit(0);
  }

  close(client);
}
}
