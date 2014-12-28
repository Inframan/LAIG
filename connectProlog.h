#pragma once
#include <winsock2.h>
#include <iostream>
#include "GameBoard.h"

#define IPADDRESS "127.0.0.1"
#define PORT 60070


using namespace std;


bool socketConnect();

void envia(char *s, int len);

void recebe(char *ans);

void quit();

int startConnection();