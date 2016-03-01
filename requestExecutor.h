//
// Created by Olexiy Burov on 2/29/16.
//
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

#ifndef EGAUGESIMULATOR_REQUESTEXECUTOR_H
#define EGAUGESIMULATOR_REQUESTEXECUTOR_H
void sendRequest(int *values, int count, uint64_t timestamp);
#endif //EGAUGESIMULATOR_REQUESTEXECUTOR_H
