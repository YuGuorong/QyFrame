
#include <string.h>
#include <stdio.h>
#include "QinYiApp.h"
extern int test_main(int argc , void * argv[]);

const U8 g_strMainMenu0[] = { ("\xDB\x8F\x65\x51\x0\x0") /*L"Ω¯»Î"*/};
const U8 g_strMainMenu1[] = { ("\x7B\x76\x55\x5F\x0\x0") /*L"µ«¬º"*/};
const U8 g_strMainMenu2[] = { ("\xBE\x8B\x6E\x7F\x0\x0") /*L"…Ë÷√"*/};
U8*  g_strMainMenu[3];
int g_testval;

int OnQinYiSelMainMenu(int qinyi_app_menu_sel)
{
    switch(qinyi_app_menu_sel)
    {
    case 0:
        QyAdpTrace("0");
        break;
    case 1:
        kal_prompt_trace(MOD_MMI,"argv is %d", g_testval);
        mmi_scan_display_popup(L"fasfd",MMI_EVENT_WARNING);
        break;
    default:
        break;
    }
    return 0;
}


int main(int argc , void * argv[])
{
    //return test_main(argc , argv);
    g_strMainMenu[0] = (U8*)g_strMainMenu0;
    g_strMainMenu[1] = (U8*)g_strMainMenu1;
    g_strMainMenu[2] = (U8*)g_strMainMenu2;
    g_pMtk = (QY_ADAPTOR*)argv[0];
    g_testval = argc;
    ShowQinYiMenu(NULL,g_strMainMenu,NULL,3,OnQinYiSelMainMenu, NULL);
	return 0;	
}

