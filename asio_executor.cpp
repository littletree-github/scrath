//
// echo_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <memory>

using namespace std;

class MyClient {
    public:
        void ping() {
            cout << "ping " << endl;
        }
        void foo(int x) {
            cout << "foo(" << x << ") == " << x << endl;
        }
};


class BackupHandler
{
public:
 
   BackupHandler(int poolSize = 4)
   {
      m_pWork.reset( new boost::asio::io_service::work(m_io_service) );
 
      for ( int i = 0; i < poolSize; ++i)
         m_threadGroup.create_thread( boost::bind(&boost::asio::io_service::run, &m_io_service) );
   }
 
   ~BackupHandler()
   {
      m_pWork.reset(); // stop all!
      m_threadGroup.join_all(); // wait for all completition
   }
 
   // this will leave immediately
   template <typename TFunc>
   void enqueue(TFunc fun)
   {
      m_io_service.post(
          boost::bind( &BackupHandler::execute<TFunc>, this, fun )
       );
   }
 
private:
 
   // this will be executed when one of the threads is available
   template <typename TFunc>
   void execute(TFunc& fun)
   {
      MyClient client; // here I should use RAII to get the client resource
      fun(client);
   }
 
private:
 
   boost::asio::io_service m_io_service;
   shared_ptr<boost::asio::io_service::work> m_pWork;
 
   boost::thread_group m_threadGroup;
};

int main() {
BackupHandler bkp(10);
//.. code
bkp.enqueue(
        boost::protect(
    boost::bind(&MyClient::ping, _1) // who's gonna call that? _1!
  ));
//.. other code
bkp.enqueue(
  boost::protect(
    boost::bind(&MyClient::foo, _1, 42)
  ));
 return 0;
}

