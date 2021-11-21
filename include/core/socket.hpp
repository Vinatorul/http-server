#pragma once

#include <functional>
#include <string>

namespace core {

int InitSocket(const std::string &hostname, const std::string &service);

void AcceptConnection(
    int socket_descriptor,
    std::function<std::string(std::string)> responder_callback);
}
