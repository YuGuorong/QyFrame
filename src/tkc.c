
#include <string.h>
#include <stdio.h>


typedef int (*strfnx)(char * ptr);


typedef struct tstint
{
    int 	pid;
    int 	vid;
    char   *pstrin;
    char   *pstrout;
    int    *psubid;
    strfnx  pfnx_Mtk;
    strfnx  pfnx_qy;
} TST_INPUT;


int g_QyPid = 0xccddee;
int g_QyVid = 0x33aa5577;
char plink [] = {"Hellow ygr world!"};

int Testdynload(TST_INPUT *pinput)
{
	char tmps[32]={"ygr:"};
	pinput->pfnx_Mtk(tmps);
	sprintf(tmps, "[%X, %X]",g_QyPid++, g_QyVid);
	strcat(pinput->pstrin,tmps);
	return  3;

}

int Teststrcan(char *a)
{
	strcpy(a, "ygr test mtk");
	return 0;	
}
	
 
int main(int argc , void * argv[])
{

	TST_INPUT * pin = (TST_INPUT * )argv[0];
	int a = argc;

	pin->pid = g_QyPid;
	pin->vid = g_QyVid;
	pin->psubid = &g_QyPid;
	pin->pstrout = plink;
	pin->pfnx_qy = Teststrcan;
	a += Testdynload(pin);

	return a;	

}

