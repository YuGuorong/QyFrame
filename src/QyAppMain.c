
#include <string.h>
#include <stdio.h>
#include "QinYiApp.h"
extern int test_main(int argc , void * argv[]);

extern void QinYiAppMain(void);

EXT_INFO * g_pext ;
QY_SETTING_PROF   g_Setting;

int main(int argc , void * argv[])
{
    //return test_main(argc , argv);
    g_pMtk = (QY_ADAPTOR*)argv[0];
    g_pext = (EXT_INFO * )g_pMtk->pextern;
    g_SettingProf = &g_Setting;
    QinYiAppMain();
	return 0;	
}

