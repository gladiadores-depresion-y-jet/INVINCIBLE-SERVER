//
// Created by david on 07/06/19.
//

#ifndef INVINCIBLE_CLIENTLOGIC_REQUESTS_H
#define INVINCIBLE_CLIENTLOGIC_REQUESTS_H

#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include "ResourceOfRequest.h"

class Requests {
public:

    /**
     * Obtiene ipaddress y puerto a donde hacer el request.
     * Tambien, en caso de correrse en windows inicia winsock
     */
    Requests(std::string &ipAddress, std::string &port);

    /**
     * Permite que curl pueda escribir en el readBuffer la resquesta que el servidor da al hacer un request.
     *
     * @param contents
     * @param size
     * @param nmemb
     * @param userp
     * @return
     */
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    /**
     * Envia un POST request.
     *
     * @param data, info que se enviara al servidor como cuerpo del request
     * @param resourceOfRequest, tipo de REST resource al cual se le quiere hacer el request
     */
    std::string sendPostRequest(std::string &data, ResourceOfRequest resourceOfRequest);

private:
    CURL *curl;
    // Si es puntero, da error de sigsegv por como curl lo maneja
    CURLcode res;

    std::string readBuffer;
    std::string *ipAddress;
    std::string *port;
};


#endif //INVINCIBLE_CLIENTLOGIC_REQUESTS_H
