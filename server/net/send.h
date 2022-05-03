#pragma once
#include <stddef.h>
#include <string.h>
#include "host.h"
#include "../unit.h"

void send_file(int socket,char *map, size_t size_map);
void send_unit_list(int socket);
int generate_order(char *order);
