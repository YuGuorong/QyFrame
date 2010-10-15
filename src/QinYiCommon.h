#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "QinYiApp.h"
#include "GlobalDefs.h"
#include "fs_errcode.h"
#include "fs_type.h"
#include "soc_sap.h"
#define QY_APPLICATION_VERSION    8

 int Decode(int fsh, void * buff, int buf_sz, void * pout);