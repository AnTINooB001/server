#include "connection_manager.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <memory>

using namespace boost;
using boost::asio::ip::tcp;

template <class T = tcp>
class Host
{
    using Client_t = Client<T>;
    using Collection_t =  std::vector<std::shared_ptr<Client_t>>;

    system::error_code ec;
    asio::io_context context;
    typename T::acceptor acc{context};
    Collection_t clients;
    C_manager<Collection_t,Client_t,T> manager{clients,acc};
    int port;
    std::string addr;
public:
    Host(const std::string&, const int, const int);
    void open();
    auto begin() const;
    auto end() const;
    size_t size() const;
};

template <class T>y
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

    manager.manage();
    std::cout<<"host opened\n";
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

// template <class T = tcp>
// class Host
// {
//     asio::io_context context;
//     C_manager<T> manager;
//     std::string& addr_from_name(std::string&);
// public:
//     void open(std::string,int);
//     auto begin() const;
//     auto end() const;
// };

// template <class T>
// std::string& Host<T>::addr_from_name(std::string& name)
// {
//     system::error_code ec;
//     typename T::resolver res(context);
//     auto cont = res.resolve(name,"",ec);

//     if(ec) {
//         std::cout<< "Cant resolve - " << name << " detail: " << ec.message() << std::endl;
//         return name;
//     }

//     name = cont->endpoint().address().to_string();
//     return name;
// }

// template <class T>
// void Host<T>::open(std::string ip_addr,int port)
// {
//     std::string ip = addr_from_name(ip_addr);
//     manager.init(ip,port);
//     manager.manage();
//     std::cout<< "Hosting " <<ip << " opened on port "<< port << std::endl;
// }

// template <class T>
// auto Host<T>::begin() const
// {
//     return manager.begin();
// }

// template <class T>
// auto Host<T>::end() const
// {
//     return manager.end();
// }