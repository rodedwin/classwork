//
//  requestor.h
//  ece531classwork
//
//  Created by Edwin Rodriguez on 7/16/20.
//  Copyright © 2020 Edwin Rodriguez. All rights reserved.
//

#ifndef requestor_h
#define requestor_h

// function for usage info
void usage(void) {
                printf("\nUSAGE: ./hw [URL] '<url>' [VERB] '<content>'                           \n\n");
                printf("%40s\n", "HELP MENU");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("%-15s%-15s%-35s%-25s\n","FLAGS", "ARGUMENTS", "EXAMPLE ARG FORMAT", "SUMMARY");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("%-15s%-15s%-35s%-25s\n","-h/--help", "N/A", "N/A", "help and usage options");
                printf("%-15s%-15s%-35s%-25s\n","-g/--get", "N/A", "N/A", "[VERB] http get option");
                printf("%-15s%-15s%-35s%-25s\n","-o/--post", "'content'", "'Post this text'", "[VERB] http post option");
                printf("%-15s%-15s%-35s%-25s\n","-p/--put", "'content'", "'Put this text'", "[VERB] http put option");
                printf("%-15s%-15s%-35s%-25s\n","-d/--delete", "'content'", "'Delete this text'", "[VERB] http delete option");
                printf("%-15s%-15s%-35s%-25s\n","-u/--url", "'url'", "'http://localhost:8080'", "[URL] http url option");
                printf("%50s\n", "'http://www.cnn.com'");
                printf("%53s\n\n", "'http://IPADDRESS:PORT'");
                printf("%44s\n", "EXAMPLE USAGE");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("%-20s%-30s\n","HTTP REQUEST", "COMMAND");
                printf("---------------------------------------------------------------------------------------------\n");
                printf("%-20s%-30s\n","HTTP GET", "./hw --url 'http://httpbin.org/get' --get");
                printf("%-20s%-30s\n","HTTP POST", "./hw --url 'http://httpbin.org/post' --post 'This text gets posted!'");
                printf("%-20s%-30s\n","HTTP PUT", "./hw --url 'http://httpbin.org/put --put 'This text gets put!'");
                printf("%-20s%-30s\n","HTTP DELETE", "./hw --url 'http://httpbin.org/delete' --delete 'This text gets deleted!'");
}

// function for HTTP GET
void curl_get(char *url, CURL *curl, CURLcode res) {
    long http_code = 0;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "[CURL] Could not execute HTTP GET: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("[HTTP CODE]: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

// function for HTTP PUT
void curl_put(char *url, char *content, CURL *curl, CURLcode res) {
    long http_code = 0;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "[CURL] Could not execute HTTP PUT: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("[HTTP CODE]: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

// function for HTTP POST
void curl_post(char *url, char *content, CURL *curl, CURLcode res) {
    long http_code = 0;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(content));
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "[CURL] Could not execute HTTP POST: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("[HTTP CODE]: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

// function for HTTP DELETE
void curl_delete(char *url, char *content, CURL *curl, CURLcode res) {
    long http_code = 0;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "[CURL] Could not execute HTTP DELETE: %s\n", curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("[HTTP CODE]: %ld\n", http_code);
        curl_easy_cleanup(curl);
    }
}

#endif /* requestor_h */
