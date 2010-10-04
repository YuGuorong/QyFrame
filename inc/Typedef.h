#ifndef QY_TYPEDEF_H
#define QY_TYPEDEF_H
typedef unsigned char   U8;
typedef signed char     S8;
typedef unsigned int    U32;
typedef signed int      S32;
typedef unsigned short  U16;
typedef signed short    S16;


typedef unsigned char           kal_uint8;
typedef signed char             kal_int8;
typedef char                    kal_char;
typedef unsigned short          kal_wchar;

typedef unsigned short int      kal_uint16;
typedef signed short int        kal_int16;

typedef unsigned int            kal_uint32;
typedef signed int              kal_int32;

typedef unsigned short WCHAR;
typedef unsigned int   UINT;
typedef unsigned char  BYTE;

typedef void * HANDLE;
typedef int FS_HANDLE;


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

