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

    /**
     * Se encarga de manejar todos los pedidos HTTP al puerto donde se inicializa el servidor.
     *
     * @param request, contiene info del pedido recibido.
     * @param response, permite responder al pedido.
     */
    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        std::string datos;
        std::string metadataResponse;
        std::string RAID5Response;
        std::string respuesta = "false";


        if (request.method() == Http::Method::Post) {
            datos = request.body();
            json jsonRequest;
            if (request.resource() == "/RESTORE") {
                std::cout << "Se recibe restore request con cuerpo : " << datos << std::endl;

                json junk;
                junk["algo"] = "algo";
                std::string junkString = junk.dump();
                metadataResponse = this->requestsMetadataDB->sendPostRequest(junkString, RESTORE);

                response.send(Pistache::Http::Code::Ok, metadataResponse);
            }

            else if (request.resource() == "/CREATE") {
                std::cout << "Se recibe create request con cuerpo : " << datos << std::endl;

                metadataResponse = this->requestsMetadataDB->sendPostRequest(datos, CREATE);

                response.send(Pistache::Http::Code::Ok, metadataResponse);
            }

            else if (request.resource() == "/RESTORE") {
                datos= request.body();

                std::cout << "llega request tipo restore" << std::endl;

                metadataResponse = this->requestsMetadataDB->sendPostRequest(datos, RESTORE);

                std::cout <<  "Enviando de vuelta a cliente : " << metadataResponse << std::endl;

                response.send(Pistache::Http::Code::Ok, metadataResponse);
            }

            else if (request.resource() == "/INSERT") {
                std::cout << "Se recibe insert request con cuerpo : " << datos << std::endl;
                jsonRequest = json::parse(datos);

                // Crea json para enviar a MetadataDB
                json jsonMetadata;

                jsonMetadata["table"] = jsonRequest["table"];
                jsonMetadata["cols"] = jsonRequest["cols"];
                jsonMetadata["values"] = jsonRequest["values"];
                std::string metadataRequest = jsonMetadata.dump();

                // Enviar metadata a metadatadb y recibir id
                metadataResponse = this->requestsMetadataDB->sendPostRequest(metadataRequest, INSERT);
                std::cout << "Respuesta de metadatadb : " <<  metadataResponse << std::endl;
                /*
                if (metadataResponse != "false") {
                    // Crea json para enviar a RAID5
                    json jsonRAID5;
                    jsonRAID5["imagen"] = jsonRequest["imagen"];
                    jsonRAID5["id"] = metadataResponse;
                    std::string raid5Request = jsonRAID5.dump();

                    // Enviar binario imagen y id a RAID5 y recibe confirmacion
                    RAID5Response = this->requestsRAID5->sendPostRequest(raid5Request, INSERT);

                    respuesta = RAID5Response;
                }*/

                //Enviar confirmacion a cliente
                response.send(Pistache::Http::Code::Ok, respuesta);
            }

            else if (request.resource() == "/SELECT") {
                std::cout << "Se recibe select request con cuerpo : " << datos << std::endl;

                jsonRequest = json::parse(datos);

                std::string metadataRequest = jsonRequest.dump();
                metadataResponse = this->requestsMetadataDB->sendPostRequest(metadataRequest, SELECT);
                std::cout << "Respuesta metadatadb" << metadataResponse << std::endl;
                /*if (metadataResponse != "false") {
                    auto jsonMetadata = json::parse(metadataResponse);

                    json idJson;
                    idJson = jsonMetadata["id"];
                    std::string raid5Request = idJson.dump();
                    RAID5Response = this->requestsRAID5->sendPostRequest(raid5Request, SELECT);
                    if (RAID5Response != "false") {
                        json jsonImage = json::parse(RAID5Response);

                        jsonMetadata["imagen"] = jsonImage["image"];

                        respuesta = jsonMetadata.dump();
                    }
                }*/

                response.send(Pistache::Http::Code::Ok, respuesta);
            }

            else if (request.resource() == "/UPDATE") {
                std::cout << "Se recibe update request con cuerpo : " << datos << std::endl;

                metadataResponse = this->requestsMetadataDB->sendPostRequest(datos, UPDATE);
                if (metadataResponse != "false") {
                    respuesta = metadataResponse;
                }

                response.send(Pistache::Http::Code::Ok, metadataResponse);
            }

            else if (request.resource() == "/DELETE") {
                // TODO adaptar para cuando se borra toda la galeria.
                std::cout << "Se recibe delete request con cuerpo : " << datos << std::endl;

                std::string metadataRequest = jsonRequest.dump();
                metadataResponse = this->requestsMetadataDB->sendPostRequest(metadataRequest, DELETE);
                if (metadataResponse != "false") {
                    RAID5Response = this->requestsRAID5->sendPostRequest(metadataResponse, DELETE);
                    if (RAID5Response != "false") {
                        respuesta = RAID5Response;
                    }
                }
                response.send(Pistache::Http::Code::Ok, respuesta);
            }

        }
        else {
            std::cout << "se envio respuesta defeault" << std::endl;
            response.send(Pistache::Http::Code::Ok, "<h1>Esta es la respuesta por defecto</h1>");
        }
    }

private:
    /** Define ip y puerto de RAID5 */
    std::string *ipAddressRAID5 = new std::string("127.0.0.1"), *portRAID5 = new std::string("9081");
    /** Define ip y puerto de MetadataDB */
    std::string *ipAddressMetadataDB = new std::string("127.0.0.1") ,*portMetadataDB = new std::string("9082");

    /** Permite hacer pedidos al RAID5 */
    Requests *requestsMetadataDB = new Requests(*ipAddressMetadataDB, *portMetadataDB);
    /** Permite hacer pedidos a MetadataDB */
    Requests *requestsRAID5 = new Requests(*ipAddressRAID5, *portRAID5);
};

#endif //INVINCIBLE_SERVER_REQUESTHANDLER_H
