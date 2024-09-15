#ifndef TUTILS
#define TUTILS

#include <string>
#include <boost/asio.hpp>
#include <iostream>
using namespace boost;

template <class Protocol>
std::string& addr_from_name(asio::io_context& context, std::string& name)
{
    system::error_code ec;
    typename Protocol::resolver res(context);
    auto cont = res.resolve(name,"",ec);

    if(ec) {
        std::cout<< "Cant resolve - " << name << " detail: " << ec.message() << std::endl;
        return name;
    }

    name = cont->endpoint().address().to_string();
    return name;
}

#endif