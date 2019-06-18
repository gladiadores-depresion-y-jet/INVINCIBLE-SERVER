//
// Created by david on 07/06/19.
//

#include "Requests.h"

Requests::Requests(std::string &ipAddress, std::string &port) {
    this->ipAddress = &ipAddress;
    this->port = &port;

    curl_global_init(CURL_GLOBAL_ALL);
}

size_t Requests::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Requests::sendPostRequest(std::string &data, ResourceOfRequest resourceOfRequest) {

    this->readBuffer = "";
    std::string request;

    switch (resourceOfRequest) {
        case CREATE:
            request = "CREATE";
            break;
        case RESTORE:
            request = "RESTORE";
            break;
        case INSERT:
            request = "INSERT";
            break;
        case IMAGE:
            request = "IMAGE";
            break;
        case SELECT:
            request = "SELECT";
            break;
        case UPDATE:
            request = "UPDATE";
            break;
        case DELETE:
            request = "DELETE";
            break;
    }

    // Generate url with specified parameters
    std::ostringstream url;
    url << "http://" << *this->ipAddress << ":" << *this->port << "/" << request;

    this->curl = curl_easy_init();
    if(this->curl) {
        // set up curl to fulfill post request with parameters
        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &this->readBuffer);

        // Perform the request, res will get the return code
        this->res = curl_easy_perform(this->curl);
        std::cout << this->readBuffer << std::endl;
        /* Check for errors */
        if(this->res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(this->res));

        // cleanup for next request
        curl_easy_cleanup(this->curl);

    }
    curl_global_cleanup();

    return this->readBuffer;
}
