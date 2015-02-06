#ifndef BOOST_ASIO_HAS_MOVE
#define BOOST_ASIO_HAS_MOVE 1
#endif

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <type_traits>
namespace asio = boost::asio;
namespace ip = boost::asio::ip;
using boost::asio::ip::tcp;
using namespace std;

using boost::asio::io_service;
using boost::asio::buffer;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void client_session(ip::tcp::socket sock) {
  try {
    while (true) {
      char data[512];
      size_t len = sock.read_some(buffer(data));
      if (len > 0)
        write(sock, buffer("ok", 2));
    }
  } catch (boost::system::system_error &err) {
    cout << err.what() << endl;
  }
}

int main() {
  io_service service;
  ip::tcp::endpoint ep(ip::tcp::v4(), 2001); // listen on 2001
  ip::tcp::acceptor acc(service, ep);
  while (true) {
    auto sock = ip::tcp::socket(service);
    acc.accept(sock);
    if (std::is_move_constructible<tcp::socket>::value) {
      auto t = std::thread(client_session, std::move(sock));
      t.detach();
    } else {
      cout << "sorry, socket not movable" << endl;
    }
  }
}
