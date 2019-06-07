//
// Created by kugelblitz on 5/25/19.
//

#ifndef INVINCIBLE_SERVER_REQUESTHANDLER_H
#define INVINCIBLE_SERVER_REQUESTHANDLER_H

#include <pistache/endpoint.h>
#include <iostream>
#include <sstream>

using namespace Pistache;

class requestHandler: public Http::Handler {
public:

HTTP_PROTOTYPE(requestHandler);

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        if (request.method() == Http::Method::Post) {
            if (request.resource() == "/INSERT") {
                response.send(Pistache::Http::Code::Ok, request.query().get("hilera").get());
                // TODO logica insert
            }
            else if (request.resource() == "/SELECT") {
                int largo = request.query().get("numChars").get().length();
                std::stringstream ss;
                ss << largo;
                response.send(Pistache::Http::Code::Ok, ss.str());
                // TODO logica select
            }
            else if (request.resource() == "/DELETE") {
                // TODO logica delete
            }
            else if (request.resource() == "/UPDATE") {
                // TODO logica update
            }
        }
        else {
            std::cout << "se envio respuesta defeault" << std::endl;
            response.send(Pistache::Http::Code::Ok, "<h1>Esta es la respuesta por defecto</h1>");
        }

    }
};


#endif //INVINCIBLE_SERVER_REQUESTHANDLER_H
