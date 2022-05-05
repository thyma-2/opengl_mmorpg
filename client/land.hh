#pragma once
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "3d/model.hh"
#include "3d/object.hh"
#include "network/net.h"

void generate_land(char *hcsv, char *tcsv);

struct surface
{
	int y00,y01,y11,y10;
};
