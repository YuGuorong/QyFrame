#ifndef QY_TYPEDEF_H
#define QY_TYPEDEF_H
typedef unsigned char   U8;
typedef signed char     S8;
typedef unsigned int    U32;
typedef signed int      S32;
typedef unsigned short  U16;
typedef signed short    S16;


typedef U16 UI_character_type;
typedef UI_character_type*	UI_string_type;
typedef U8*					UI_buffer_type;


#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif


#endif /*QY_TYPEDEF_H*/

