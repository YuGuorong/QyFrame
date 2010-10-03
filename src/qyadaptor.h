#ifndef QY_ADAPTOR_H
#define QY_ADAPTOR_H
#include "typedef.h"

extern void ShowQinYiMenu(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) );
extern void SetKeyHandler(FuncPtr funcPtr,U16 keyCode,U16 keyType);

typedef struct tag_qy_adaptor
{
    void (*qy_ShowQinYiMenu)(void);
    void (*qy_SetKeyHandler)(FuncPtr funcPtr,U16 keyCode,U16 keyType);

}QY_ADAPTOR;


extern QY_ADAPTOR * g_pMtkAdp;

#endif /*QY_ADAPTOR_H*/

