
#include <string.h>
#include <stdio.h>
#include "qyadaptor.h"

QY_ADAPTOR * g_pMtkAdp;

void ShowQinYiMenu(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) )
{
    g_pMtkAdp->qy_ShowQinYiMenu(title,pmenustr,pPopStr,nitems ,fsel, pexit);
}

