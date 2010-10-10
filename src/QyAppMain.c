
#include <string.h>
#include <stdio.h>
#include "QinYiApp.h"
extern int test_main(int argc , void * argv[]);

extern void QinYiAppMain(void);
int main(int argc , void * argv[])
{
    //return test_main(argc , argv);
    g_pMtk = (QY_ADAPTOR*)argv[0];
    QinYiAppMain();
	return 0;	
}

