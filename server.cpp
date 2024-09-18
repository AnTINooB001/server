#include "host.hpp"

template<class T>
void main_loop(Host<T>& host);

int main(int argc, char* argv[])
{
    std::string addr = "0.0.0.0";
    Host host(addr,1111,10);

    host.open();
    main_loop(host);
    
    return 0;
}

template<class T>
void main_loop(Host<T>& host)
{
    system::error_code ec;
    int avail = 0;
    int readed = 0;
    int res_readed = 0;
    int ind = 0;
    std::vector<char> buffer(64);
    
    while(1) {
        int iter = 0;
        for (auto i = host.begin(); i != host.end(); i++,iter++) {
            if(ec || (avail = (*i)->available()) == 0) {
                continue;
            }
            std::cout<<"iteration i = " << iter << std::endl;
            std::string res{};
            do {
                readed = (*i)->read(buffer.data(),buffer.size(),ec);
                res += buffer.data();
                avail -= readed;
                res_readed += readed;
            }while(avail != 0);
            
            std::cout<<"Readed\n" << res_readed << "\n";
            int ji = 0;
            for (auto j = host.begin(); j != host.end(); j++,ji++) {
                std::cout<< "ji = " << ji << std::endl;
                if((*i).get() == (*j).get())
                    continue;
                int w = (*j)->write(res,ec);
                std::cout<<"Writed\n" << w << std::endl;
            }
        }
    }
}

