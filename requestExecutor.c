//
// Created by Olexiy Burov on 2/29/16.
//

#include "requestExecutor.h"
void error(const char *msg) { perror(msg); exit(0); }

const char *formRows(int *values, int count) {
    const char *rows = malloc(count * 110 * sizeof(char));
    for (int i = 0; i < count; ++i) {
        char buffer[100];
        int value = values[i];
        sprintf(buffer," <r><c>%d</c></r>",value);
        strcat(rows,buffer);
    }
    return rows;
}


const char *formRequestBody(int *values, int count, uint64_t timestamp) {
    char *request_fmt =
            "POST / HTTP/1.1\r\n"
                    "Content-Type: application/xml\r\n"
                    "Content-Length: %d\r\n\r\n%s\r\n";
    char *bodyFormat =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
                    "<!DOCTYPE group PUBLIC \"-//ESL/DTD eGauge 1.0//EN\" \"http://www.egauge.net/DTD/egauge-hist.dtd\">"
                    "<group serial=\"0x0000000a\">"
                    "<data columns=\"1\" time_stamp=\"0x%08x\" time_delta=\"0.1\" delta=\"false\">"
                    " <cname t=\"V\">Test</cname>"
                    " %s"
                    "</data>"
                    "</group>";

    const char *body = malloc((300 + count * 110) * sizeof(char));
    const char *rows = formRows(values,count);

    sprintf(body,bodyFormat,timestamp,rows);
    free(rows);

    int content_length = strlen(body);

    const char *request = malloc((300 + count * 200) * sizeof(char));
    sprintf(request,request_fmt,content_length,body);
    free(body);

    printf("Request: %s\n",request);
    return request;
}

void sendRequest(int *values, int count, uint64_t timestamp) {
    /* first what are we going to send and where are we going to send it? */
    char *request = formRequestBody(values,count,timestamp);
    int portno = 9002;
    char *host = "db.sead.systems";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char response[4096];

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    total = strlen(request);
    sent = 0;
    do {
        bytes = write(sockfd,request+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        printf("Response:\n%s\n",response);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);
}
