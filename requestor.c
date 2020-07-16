//  main.c
//  ece531classwork
//  Created by Edwin Rodriguez on 7/16/20.
//  Copyright © 2020 Edwin Rodriguez. All rights reserved.

#include<stdio.h>
#include<string.h>
#include<getopt.h>
#include<curl/curl.h>
#include<stdlib.h>
#include "requestor.h"

#define OK 0

int main(int argc, char **argv) {
    
    int c;
    int gflag = 0, uflag = 0, oflag = 0, pflag = 0, dflag = 0;
    char *content, *url;
    CURL *curl;
    CURLcode res;

    while(1) {
        static struct option long_options[] =
        {
            {"help", no_argument, 0, 'h'},
            {"get", no_argument, 0, 'g'},
            {"url ", required_argument, 0 , 'u'},
            {"post", required_argument, 0, 'o'},
            {"put", required_argument, 0, 'p'},
            {"delete", required_argument, 0, 'd'},
            {0,0,0,0}
        };
    
        // getopt stores option index here
        int long_index = 0;

        c = getopt_long_only(argc, argv, "hgu:o:p:d:", \
            long_options, &long_index);

        // raise usage error if no command line options entered
        if(argc <= 1) {
            printf("WARNING: Missing command line options!\n");
            usage();
            exit(-1);
        }

        // detect end of options
        if(c == -1)
            break;

        // switch for command line options
        switch(c) {
            case 'h':
                usage();
                break;
            case 'u':
                if(uflag >= 1) {
                    printf("WARNING: Only URL allowed one url!\n");
                    usage();
                    exit(1);
                } else {
                    uflag++;
                    url = optarg;
                    printf("[HTTP URL] url: %s\n", url);
                    break;
                }
            case 'g':
                if (gflag >= 1) {
                    printf("WARNING: Only one VERB option allowed!\n");
                    usage();
                    exit(1);
                } else {
                    gflag++;
                    pflag++;
                    oflag++;
                    dflag++;
                    printf("[HTTP GET]\n");
                    curl_get(url, curl, res);
                    break;
                }
            case 'o':
                if(oflag) {
                    printf("WARNING: Only one VERB option allowed!\n");
                    usage();
                    exit(1);
                } else {
                    oflag++;
                    gflag++;
                    pflag++;
                    dflag++;
                    content = optarg;
                    printf("[HTTP POST] content: %s\n", content);
                    curl_post(url, content, curl, res);
                    break;
                }
            case 'p':
                if(pflag >= 1) {
                    printf("WARNING: Only one VERB option allowed!\n");
                    usage();
                    exit(1);
                } else {
                    pflag++;
                    oflag++;
                    gflag++;
                    dflag++;
                    content = optarg;
                    printf("[HTTP PUT] content: %s\n", content);
                    curl_put(url, content, curl, res);
                    break;
                }
            case 'd':
                if(dflag >= 1) {
                    printf("WARNING: Only one VERB option allowed!\n");
                    usage();
                    exit(1);
                } else {
                    dflag++;
                    oflag++;
                    gflag++;
                    dflag++;
                    content = optarg;
                    printf("[HTTP DELETE] content: %s\n", content);
                    curl_delete(url, content, curl, res);
                    break;
                }
            case '?':
                // invalid command line options, error already raised by getopt_long
                printf("WARNING: Invalid command line options!\n");
                usage();
                break;
            default:
                abort();
        }
    }
    
    return OK;
}
