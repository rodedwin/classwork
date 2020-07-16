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
    
    /*------CURL Stuff------*/
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    /*------CURL Stuff------*/
    
    /*------variables------*/
    int i, j;
    /*------variables------*/
    
    for(i=1; i < argc; i++) {
        
        /*------GET called------*/
        if((strcmp(argv[i], "--get") == 0) || (strcmp(argv[i], "-g") == 0)) {
            printf("GET was called... \n");
            for(j=1; j < argc; j++) {
                if((strcmp(argv[j], "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    if(string_check(argv[j+1])) {
                        curl_get(argv[j+1], curl, res);
                    }
                    return OK;
                }
            }
        }
        /*------GET called------*/
        
        /*------POST called------*/
        else if((strcmp(argv[i], "--post") == 0) || (strcmp(argv[i], "-o") == 0)) {
            printf("POST was called\n");
            for(j=0; j < argc; j++) {
                
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int message_len = 0;
                    for(k=4; k < argc; k++) {
                        message_len += strlen(argv[k]) + 1;
                    }

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
                        curl_post(argv[j+1], curl_message, curl, res);
                    }
                    return OK;
                }
            }
        }
        /*------POST called------*/
        
        /*------PUT called------*/
        else if((strcmp(argv[i], "--put") == 0) || (strcmp(argv[i], "-p") == 0)) {
            printf("PUT was called\n");
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
        /*------PUT called------*/
        
        /*------DELETE called------*/
        else if((strcmp(argv[i], "--delete") == 0) || (strcmp(argv[i], "-d") == 0)) {
            printf("DELETE was called\n");
            
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
        /*------DELETE called------*/
        
        /*------HELP called------*/
        else if((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0)) {
            printf("HELP was called");
            help_message();
            return OK;
        }
        /*------HELP called------*/
    }

    return OK;
}
