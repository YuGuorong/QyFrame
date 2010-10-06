
#include <string.h>
#include <stdio.h>
#include "QinYiApp.h"
extern int test_main(int argc , void * argv[]);

extern void mmi_QinYi_app_entry(void);
int main(int argc , void * argv[])
{
    //return test_main(argc , argv);
    g_pMtk = (QY_ADAPTOR*)argv[0];
    mmi_QinYi_app_entry();
	return 0;	
}

