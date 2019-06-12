//
// Created by kugelblitz on 5/25/19.
//

#ifndef INVINCIBLE_SERVER_REQUESTHANDLER_H
#define INVINCIBLE_SERVER_REQUESTHANDLER_H

#include <pistache/endpoint.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <comm/client/Requests.h>

using namespace Pistache;
using nlohmann::json;

class requestHandler: public Http::Handler {
public:

HTTP_PROTOTYPE(requestHandler);

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        std::string datos;
        if (request.method() == Http::Method::Post) {
            if (request.resource() == "/INSERT") {
                std::string exitoso = "false";
                datos = request.body();

                auto jsonRequest = json::parse(datos);
                std::cout << "Se recibe json : " << jsonRequest.dump(4) << std::endl;

                // Crea json para enviar a MetadataDB
                json jsonMetadata;
                jsonMetadata["table"] = jsonRequest["table"];
                jsonMetadata["cols"] = jsonRequest["cols"];
                jsonMetadata["values"] = jsonRequest["values"];
                std::string metadataRequest = jsonMetadata.dump();

                // Enviar metadata a metadatadb y recibir id
                std::string metadataResponse = this->requestsMetadataDB->sendPostRequest(metadataRequest, INSERT);

                if (metadataResponse != "false") {
                    // Crea json para enviar a RAID5
                    json jsonRAID5;
                    jsonRAID5["imagen"] = jsonRequest["imagen"];
                    jsonRAID5["id"] = metadataResponse;
                    std::string raid5Request = jsonRAID5.dump();

                    // Enviar binario imagen y id a RAID5 y recibe confirmacion
                    std::string RAID5Response = this->requestsRAID5->sendPostRequest(raid5Request, INSERT);

                    exitoso = RAID5Response;
                }

                //Enviar confirmacion a cliente
                response.send(Pistache::Http::Code::Ok, exitoso);
            }

            else if (request.resource() == "/SELECT") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */

                // TODO aqui debe estar logica del select

                std::cout << "Se recibe select request" << std::endl;

                // TODO definir respuesta
                response.send(Pistache::Http::Code::Ok, jsonRequest.dump(4));
            }

            else if (request.resource() == "/UPDATE") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */

                // TODO aqui debe estar logica del update

                // TODO definir respuesta
                response.send(Pistache::Http::Code::Ok, jsonRequest.dump(4));
            }

            else if (request.resource() == "/DELETE") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */

                // TODO aqui debe estar logica del delete

                // TODO definir respuesta
                response.send(Pistache::Http::Code::Ok, jsonRequest.dump(4));
            }

        }
        else {
            std::cout << "se envio respuesta defeault" << std::endl;
            response.send(Pistache::Http::Code::Ok, "<h1>Esta es la respuesta por defecto</h1>");
        }
    }

private:
    std::string *ipAddressRAID5 = new std::string("127.0.0.1"),
    *ipAddressMetadataDB = new std::string("127.0.0.1");
    std::string *portRAID5 = new std::string("9081"),
    *portMetadataDB = new std::string("9082");
    Requests *requestsRAID5 = new Requests(*ipAddressRAID5, *portRAID5);
    Requests *requestsMetadataDB = new Requests(*ipAddressMetadataDB, *portMetadataDB);
};

#endif //INVINCIBLE_SERVER_REQUESTHANDLER_H
