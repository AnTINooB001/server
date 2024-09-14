#pragma once

#include <string>
#include <boost/asio.hpp>
using namespace boost;

class Point
{
    int x;
    int y;
public:
    Point() {};
    Point(int x_, int y_) : x{x_}, y{y_} {};
    int getX() const { return x; }
    int getY() const { return y; }
};

class Object
{
protected:
    Point p;
    char sym;
public:
    Object() {};
    Object(Point p_, char s) : sym{s}, p{p_} {};
    virtual Point getPoint() const { return p; };
    virtual void setPoint(Point p_) { p = p_; };
    virtual char getSym() const { return sym; };
    virtual ~Object() { };
};

template <class Protocol>
std::string& addr_from_name(asio::io_context& context, std::string& name)
{
    std::cout << "ffdfasdf";
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
