#ifndef TCLITENT
#define TCLITENT

#include <boost/asio.hpp>

using namespace boost;

template <class T>
class Client
{
    typename T::socket socket;
    asio::ip::address addr;
public:
    Client(typename T::socket& s);
    Client(Client<T>& c);
    int read(std::string&,system::error_code&);
    int read(char* data, size_t sz, system::error_code& ec);
    int write(std::string&,system::error_code&);
    int write(char*, size_t,system::error_code&);
    int available() const;
    bool is_open() const;

    bool operator==(const Client<T>&) const;
    void operator=(Client<T> c) = delete;
};

template <class T>
Client<T>::Client(typename T::socket& s) : socket{std::move(s)}, addr{socket.remote_endpoint().address()}
{
}

template <class T>
Client<T>::Client(Client<T>& c) : socket{std::move(c.socket)}, addr{socket.remote_endpoint().address()}
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
int Client<T>::write(char* data, size_t sz, system::error_code& ec)
{
    return socket.write_some(asio::buffer(data,sz),ec);
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
    return (c.addr == addr);
}

#endif