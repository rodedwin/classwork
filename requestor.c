//cc -o hw requestor.c
/*
 
 AUTHOR:    Edwin Rodriguez
 DATE:      7/16/2020
 FILENAME:  requestor.h
 PURPOSE:
    This program implements the use of libcurl. The user can call the executable "hw"
    to communicate via HTTP.
    For examples on
 
 REFRENCES:
    Portions of the code were adapted from the following websites:
        https://curl.haxx.se/libcurl/c/libcurl-tutorial.html
        https://curl.haxx.se/libcurl/c/example.html
 
*/

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
        // check whether --get or -g is used
        if((strcmp(argv[i], "--get") == 0) || (strcmp(argv[i], "-g") == 0)) {
            printf("GET was called... \n");
            
            for(j=1; j < argc; j++) {
                // check whether --url or -u is used.
                if((strcmp(argv[j], "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    if(string_check(argv[j+1])) {       // Check for correct URL syn.
                        curl_get(argv[j+1], curl, res); // Call GET
                    }
                    return OK;
                }
            }
        }
        /*------GET called------*/
        
        /*------POST called------*/
        // check whether --post or -p is used
        else if((strcmp(argv[i], "--post") == 0) || (strcmp(argv[i], "-o") == 0)) {
            printf("POST was called\n");
            
            for(j=0; j < argc; j++) {
                // check whether --url or -u is used
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int msg_length = 0;
                    for(k=4; k < argc; k++) {
                        msg_length += strlen(argv[k]) + 1;
                    }

                    char message[msg_length];
                    for(k=4; k < argc; k++) {
                        strcat(message, argv[k]);
                        if((k + 1) == argc) {
                            ;
                        }
                        else {
                            strcat(message, " ");
                        }
                    }

                    if(string_check(argv[j+1])) {
                        curl_post(argv[j+1], message, curl, res);
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
                // check whether --url or -u is used
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int msg_length = 0;
                    for(k=4; k < argc; k++) {
                        msg_length += strlen(argv[k]) + 1;
                    }
                    char message[msg_length];
                    for(k=4; k < argc; k++) {
                        strcat(message, argv[k]);
                        if((k + 1) == argc) {
                            ;
                        }
                        else {
                            strcat(message, " ");
                        }
                    }
                    if(string_check(argv[j+1])) {
                        curl_put(argv[j+1], message, curl, res);
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
                // check whether --url or -u is used
                if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
                    int k;
                    int msg_length = 0;
                    for(k=4; k < argc; k++) {
                        msg_length += strlen(argv[k]) + 1;
                    }
                    char message[msg_length];
                    for(k=4; k < argc; k++) {
                        strcat(message, argv[k]);
                        if((k + 1) == argc) {
                            ;
                        }
                        else {
                            strcat(message, " ");
                        }
                    }
                    if(string_check(argv[j+1])) {
                        curl_delete(argv[j+1], message, curl, res);
                    }
                    return OK;
                }
            }
        }
        /*------DELETE called------*/
        
        /*------HELP called------*/
        else if((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0)) {
            help_message();
            return OK;
        }
        /*------HELP called------*/
        else {
            printf("Invalid input, Please see the help section below. \n\n");
            help_message();
            return REQ_ERR;
    }
    }

    return OK;
}
