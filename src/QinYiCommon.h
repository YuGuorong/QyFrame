#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "QinYiApp.h"
#include "GlobalDefs.h"
#include "fs_errcode.h"
#include "fs_type.h"
#include "soc_sap.h"
#define QY_APPLICATION_VERSION    19

__global_reg(6) int QY_R9;



 int Decode(int fsh, void * buff, int buf_sz, void * pout);
