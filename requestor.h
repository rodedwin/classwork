/*
 
 AUTHOR:    Edwin Rodriguez
 DATE:      7/16/2020
 FILENAME:  requestor.h
 PURPOSE:   Contains functions for requestor.c
 
 REFRENCES:
 Portions of the code were adapted from the following websites:
 https://curl.haxx.se/libcurl/c/libcurl-tutorial.html
 https://curl.haxx.se/libcurl/c/example.html
 
 */

#ifndef requestor_h
#define requestor_h

/*--------------------HELP Function--------------------*/
void help_message() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
           \n|                    HELP                    |\
           \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
           \nSyntax:\
           \n\t./hw <verb 1> <verb 2> <url_address> <message>\
           \nSyntax for <url_address>:\
           \n\thttp://localhost:port\
           \n\thttp://www.website.com\
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
           \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
           \n|                END OF HELP                 |\
           \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
           \n\n");
}
/*--------------------HELP Function--------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*--------------------GET Function--------------------*/
void curl_get(char* url, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "GET Failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\n\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}
/*--------------------GET Function--------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*--------------------POST Function--------------------*/
void curl_post(char* url, char *message, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(message));
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "POST Failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\n\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}
/*--------------------POST Function--------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*--------------------PUT Function--------------------*/
void curl_put(char* url, char *message, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "PUT failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\n\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}
/*--------------------PUT Function--------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*--------------------DELETE Function--------------------*/
void curl_delete(char* url, char *message, CURL *curl, CURLcode res) {
    long http_code = 0;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "DELETE failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("\n\nHTTP CODE: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}
/*--------------------DELETE Function--------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*--------------String Syntax Check Function-------------*/
int string_check(char *message) {
    
    if(strstr(message, "http://") == NULL) {
        printf("\nMissing http:// see help.\n");
        help_message();
        return 0;
    }
    
    else {
        char *localhost = "localhost";
        if(strstr(message, localhost) == NULL) {
            return 1;
        }
        else {
            char *port = "host:";
            if(strstr(message, port) == NULL) {
                printf("\nPort not specified after localhost, see help.\n\n");
                help_message();
                return 0;
            }
            else {
                printf("something's wrong with the URL, see help.\n");
                help_message();
                return 1;
            }
        }
    }
    /*--------------String Syntax Check Function-------------*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}

#endif /* requestor_h */
