//
//  requestor.h
//  ece531classwork
//
//  Created by Edwin Rodriguez on 7/16/20.
//  Copyright © 2020 Edwin Rodriguez. All rights reserved.
//

#ifndef requestor_h
#define requestor_h

//GET
void curl_get(char* url, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl could not execute --get: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
    //printf("Henlo, get: %s pls.\n", url);
}

//POST
void curl_post(char* url, char *curl_message, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(curl_message));
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl could not execute --post: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

//PUT
void curl_put(char* url, char *curl_message, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl could not execute --put: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

//DELETE
void curl_delete(char* url, char *curl_message, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl could not execute --delete: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

//HELP
void help_message() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
    \n|                    HELP                    |\
    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
    \nSyntax:\
    \n\t./hw <flag 1> <flag 2> <url_address> <message>\
    \nExamples:\
    \n\t./hw --get --url\
    \n\t./hw --post --url <url_address> message\
    \n\t./hw --put --url <url_address> message\
    \n\t./hw --delete --url <url_address> message\
    \n\
    \n\t./hw -g -u <url_address>\
    \n\t./hw -o -u <url_address> message\
    \n\t./hw -p -u <url_address> message\
    \n\t./hw -d -u <url_address> message\
    \n\
    \nSyntax for: <url_address>\
    \n\thttp://localhost:port\
    \n\thttp://www.website.com\
    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
    \n|                                            |\
    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
    \n\n");
}


int string_check(char *message) {
    char *http_str = "http://";
    int return_value;
    if(strstr(message, http_str) == NULL) {
        printf("\nMissing http:// \nSee help.\n");
        help_message();
        return 0;
    }
    else {
        char *local_str = "localhost";
        if(strstr(message, local_str) == NULL) {
            return 1;
        }
        else {
            char *colon_char = "host:";
            if(strstr(message, colon_char) == NULL) {
                printf("\nSpecify a port, see help.\n\n");
                help_message();
                return 0;
            }
            else {
                return 1;
            }
        }
    }

}

#endif /* requestor_h */
