#pragma once

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <iostream>
#include <memory>
#include "client.hpp"
#include "utils.hpp"

using namespace boost;
using boost::asio::ip::tcp;

template <class Type, class Protocol>
class C_manager
{
    static typename Protocol::acceptor* acc;
public:
    C_manager() = delete;
    static Type get_client() const;
    static void init(typename Protocol::acceptor& acc_);
};


template <class Type, class Protocol>
void C_manager<Type,Protocol>::
    init(typename Protocol::acceptor& acc_)
    {
        acc = &acc_;
    }

template <class Type, class Protocol>
Type C_manager<Type,Protocol>::get_client()
    {
        auto sock = acc.accept();
        return Type(sock);
    }

// template <class T>
// class C_manager
// {
//     asio::io_context context;
//     typename T::endpoint endp{{},0};
//     typename T::acceptor acc{context};
//     boost::thread cons_th;
//     void catch_cons();
//     bool is_exist(typename T::socket&) const;
//     std::vector<std::shared_ptr<Client_s<T>>> cons;
// public:
//     void reserve(int r) {   cons.reserve(i);    }
//     void init(std::string&,int);
//     void add_con(typename T::socket&); // now bad to use, cons pushing in another thread
//     void manage();
//     auto begin() const;
//     auto end() const;
//     ~C_manager() {  if(cons_th.joinable()) cons_th.join();    };
// };


// template <class T>
// void C_manager<T>::add_con(typename T::socket& sock)
// {
//     cons.push_back(std::make_shared<Client_s<T>>(std::move(sock)));
// }

// template <class T>
// void C_manager<T>::manage()
// {
//     cons_th = thread([&](){ 
//         std::cout<< "start catching...\n";
//         while(1) catch_cons(); 
//     });
// }

// template <class T>
// void C_manager<T>::catch_cons()
// {
//     auto conn = acc.accept();
//     if(!is_exist(conn)) {
//         add_con(conn);
//         std::cout<<"Connection to " << conn.remote_endpoint().address() << " established\n";
//     }
// }

// template <class T>
// bool C_manager<T>::is_exist(typename T::socket& sock) const
// {

//     //return (std::find(cons.begin(),cons.end(),[&](typename T::socket& s) { s.remote_endpoint().address() == sock.remote_endpoint().address() }) != cons.end());
//     return 0;
// }

// template <class T>
// auto C_manager<T>::begin() const
// {
//     return cons.begin();
// }

// template <class T>
// auto C_manager<T>::end() const
// {
//     return cons.end();
// }

// template <class T>  
// void C_manager<T>::init(std::string& ip_addr,int port)
// {
//     endp = typename T::endpoint(boost::asio::ip::make_address(ip_addr),port);
//     acc.open(endp.protocol());
//     acc.bind(endp);
//     acc.listen();
// }
