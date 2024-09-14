#pragma once

#include <boost/asio.hpp>

using namespace boost;

template <class T>
class Client
{
    typename T::socket socket;
    asio::ip::address addr;
public:
    Client(typename T::socket&& s);
    int read(std::string&,system::error_code&);
    int write(std::string&,system::error_code&);
    int read(char* data, size_t sz, system::error_code& ec);
    int available() const;
    bool is_open() const;

    bool operator==(const Client<T>&) const;
    
    void operator=(Client c) = delete;
};

template <class T>
Client<T>::Client(typename T::socket&& s) : socket{std::move(s)}, addr{socket.remote_endpoint().address()}
{
}

template <class T>
int Client<T>::read(std::string& str, system::error_code& ec)
{
    return socket.read_some(asio::buffer(str),ec);
}

template <class T>
int Client<T>::read(char* data, size_t sz, system::error_code& ec)
{
    return socket.read_some(asio::buffer(data,sz),ec);
}

template <class T>
int Client<T>::write(std::string& str, system::error_code& ec)
{
    return socket.write_some(asio::buffer(str),ec);
}

template <class T>
int Client<T>::available() const
{
    return socket.available();
}

template <class T>
bool Client<T>::is_open() const
{
    return socket.is_open();
}

template <class T>
bool Client<T>::operator==(const Client<T>& c) const
{
    return (c.addr == this->socket.addr);
}
