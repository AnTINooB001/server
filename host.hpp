#ifndef THOST
#define THOST

#include "client.hpp"
#include "utils.hpp"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using namespace boost;
using boost::asio::ip::tcp;

template <class T = tcp>
class Host
{
    using Client_t = Client<T>;
    using Collection_t =  std::vector<std::shared_ptr<Client_t>>;

    thread th;
    system::error_code ec;
    asio::io_context context;
    typename T::acceptor acc{context};
    Collection_t clients;
    int port;
    std::string addr;
    void main_loop();
    Client_t get_client();
    void add_new(Client_t& client);
    void add(typename Collection_t::iterator it, Client_t& client);
public:
    Host(const std::string&, const int, const int);
    void open();
    auto begin() const;
    auto end() const;
    size_t size() const;
    ~Host();
};

template <class T>
void Host<T>::main_loop()
{
     auto client = get_client();
     auto cmp = [&](std::shared_ptr<Client_t> val) {
         return *val == client;
     };
     auto it = std::find_if(clients.begin(),clients.end(),cmp);
     if(it != clients.end())
         add(it,client);
     else
         add_new(client);
}

template <class T>
typename Host<T>::Client_t Host<T>::get_client()
{
    auto sock = acc.accept();
    return Client_t(sock);
}

template <class T>
void Host<T>::add_new(Client_t& client)
{
    clients.push_back(std::make_shared<Client_t>(client));
}

template <class T>
void Host<T>::add(typename Collection_t::iterator it,Client_t& client)
{
    clients.insert(it,std::make_shared<Client_t>(client));
}

template <class T>
Host<T>::Host(const std::string& addr_, const int port_, const int count) : addr{addr_}, port{port_}
{
    clients.reserve(count);
}

template <class T>
void Host<T>::open()
{
    if(!addr.empty() && !isdigit(addr[0]))
        addr = addr_from_name<asio::ip::tcp>(context,addr);
    std::cout<< "Opening host\n\taddr - " << addr << "\n\tport - " << port << std::endl;
    typename T::endpoint endp(asio::ip::make_address(addr),port);
    
    acc.open(endp.protocol(),ec);
    if(ec)
        std::cout<< "Error: acceptor not open\ndetails: " << ec.message();
    
    acc.bind(endp,ec);
    if(ec)
        std::cout<< "Error: acceptor not binded\ndetails: " << ec.message();
    
    acc.listen();

    std::cout<<"host opened\n";

    th = thread([&](){
        while(1)
            main_loop();
    });
}

template <class T>
auto Host<T>::begin() const
{
    return clients.begin();
}

template <class T>
auto Host<T>::end() const
{
    return clients.end();
}

template <class T>
size_t Host<T>::size() const
{
    return clients.size();
}

template <class T>
Host<T>::~Host()
{
    if(th.joinable())
        th.join();
}

#endif
