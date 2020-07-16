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
    printf("Help:\
    \n\t./hw --get --url\
    \n\t./hw --post --url <web_url> message\
    \n\t./hw --put --url <web_url> message\
    \n\t./hw --delete --url <web_url> message\
    \n\
    \n\t./hw -g -u <web_url>\
    \n\t./hw -o -u <web_url> message\
    \n\t./hw -p -u <web_url> message\
    \n\t./hw -d -u <web_url> message\
    \n\
    <web_url>:\
    \n\t http://localhost:port\
    \n\t or\
    \n\t http://www.website.com\n");
}


int string_check(char *message) {
    char *http_str = "http://";
    int return_value;
    if(strstr(message, http_str) == NULL) {
        printf("\nMissing \"http://\" \n\n");
        help_message();
        return_value = 0;
        return return_value;
    }
    else {
        char *local_str = "localhost";
        if(strstr(message, local_str) == NULL) {
            return_value = 1;
            return return_value;
        }
        else {
            char *colon_char = "host:";
            if(strstr(message, colon_char) == NULL) {
                printf("\nPlease specify a port after localhost\n\n");
                help_message();
                return_value = 0;
                return return_value;
            }
            else {
                return_value =1;
                return return_value;
            }
        }
    }

}

#endif /* requestor_h */
