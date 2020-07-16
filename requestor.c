#include<stdio.h>
#include<string.h>
#include<getopt.h>
#include<curl/curl.h>
#include<stdlib.h>
#include "requestor.h"

#define OK          0
#define INIT_ERR    1
#define REQ_ERR     2

int main(int argc, char *argv[]) {
    
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    int i, j;
    
    //Start at 1 because ./hw will be the first arg
    for(i=1; i < argc; i++) {
        
        if((strcmp(argv[i], "--get") == 0) || (strcmp(argv[i], "-g") == 0)) {
            printf("-g, --get was called... \n");
            for(j=1; j < argc; j++) {
                if((strcmp(argv[j], "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    if(string_check(argv[j+1])) {
                        curl_get(argv[j+1], curl, res);
                    }
                    return OK;
                }
            }
        }
        else if((strcmp(argv[i], "--post") == 0) || (strcmp(argv[i], "-o") == 0)) {
            printf("You called --post\n");
            for(j=0; j < argc; j++) {
                if(i == j) {
                    ;
                }
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int message_len = 0;
                    for(k=4; k < argc; k++) {
                        message_len += strlen(argv[k]) + 1;
                    }
                    //printf("Message Length is %d\n", message_len);
                    char curl_message[message_len];
                    for(k=4; k < argc; k++) {
                        strcat(curl_message, argv[k]);
                        if((k + 1) == argc) {
                            ;
                        }
                        else {
                            strcat(curl_message, " ");
                        }
                    }
                    //printf("String: %s\n", curl_message);
                    if(string_check(argv[j+1])) {
                        curl_post(argv[j+1], curl_message, curl, res);
                    }
                    return OK;
                }
            }
        }
        else if((strcmp(argv[i], "--put") == 0) || (strcmp(argv[i], "-p") == 0)) {
            //printf("You called --put\n");
            for(j=0; j < argc; j++) {
                if(i == j) {
                    ;
                }
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int message_len = 0;
                    for(k=4; k < argc; k++) {
                        message_len += strlen(argv[k]) + 1;
                    }
                    //printf("Message Length is %d\n", message_len);
                    char curl_message[message_len];
                    for(k=4; k < argc; k++) {
                        strcat(curl_message, argv[k]);
                        if((k + 1) == argc) {
                            ;
                        }
                        else {
                            strcat(curl_message, " ");
                        }
                    }
                    if(string_check(argv[j+1])) {
                        curl_put(argv[j+1], curl_message, curl, res);
                    }
                    return OK;
                    
                }
            }
        }
        else if((strcmp(argv[i], "--delete") == 0) || (strcmp(argv[i], "-d") == 0)) {
            //printf("You called --delete\n");
            for(j=0; j < argc; j++) {
                if(i == j) {
                    ;
                }
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int message_len = 0;
                    for(k=4; k < argc; k++) {
                        message_len += strlen(argv[k]) + 1;
                    }
                    //printf("Message Length is %d\n", message_len);
                    char curl_message[message_len];
                    for(k=4; k < argc; k++) {
                        strcat(curl_message, argv[k]);
                        if((k + 1) == argc) {
                            ;
                        }
                        else {
                            strcat(curl_message, " ");
                        }
                    }
                    if(string_check(argv[j+1])) {
                        curl_delete(argv[j+1], curl_message, curl, res);
                    }
                    return OK;
                }
            }
        }
        else if((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0)) {
            help_message();
            return OK;
        }
    }
    usage_message();
    return OK;
}
