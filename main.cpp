#include <iostream>

#include <pistache/endpoint.h>
#include <comm/requestHandler.h>

using namespace Pistache;

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options()
            .threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<requestHandler>());
    server.serve();

    server.shutdown();

    return 0;
}