
#include <string.h>
#include <stdio.h>

extern char Image$$RO$$Base[]; //输出 RO 输出节的起始地址。
extern char Image$$RO$$Limit[];// 输出 RO 输出节末尾后面的第一个字节的地址。 
extern char Image$$RW$$Base[]; //输出 RW 输出节的开始地址。  
extern char Image$$RW$$Limit[];// 输出 ZI 输出节末尾后面的字节的地址。 （选择 ZI 区末尾而不是 RW 区末尾是为了与遗留代码之间保持兼容。） 
extern char Image$$ZI$$Base[]; //输出 ZI 输出节的开始地址。 
extern char Image$$ZI$$Limit[];// 输出 ZI 输出节末尾后面的字节的地址。 


#define RO_LENGTH (Image$$RO$$Limit-Image$$RO$$Base)
//#define RW_LENGTH (Image$$RW$$Limit-Image$$RW$$Base) //fla mask ,as :（选择 ZI 区末尾而不是 RW 区末尾是为了与遗留代码之间保持兼容。）
#define RW_LENGTH (Image$$ZI$$Base-Image$$RW$$Base) //fla++,
#define ZI_LENGTH (Image$$ZI$$Limit-Image$$ZI$$Base)





extern int main(int argc , void * argv[]);

 __global_reg(6) int R9;


static void rtcinit(int rtaddr)
{
    char * ro_start;
	char * rw_start;
	char * zi_start;
    //unsigned long rw_len = RW_LENGTH;
    //unsigned long ro_len = RO_LENGTH;
    unsigned long zi_len = ZI_LENGTH;

    ro_start = (char *)(rtaddr-0x14);
    rw_start = ro_start + RO_LENGTH;
    zi_start = rw_start + RW_LENGTH;
	R9 = (int)rw_start ;

    memset(zi_start, 0, zi_len);

}


#pragma arm section code = "Dynamic_entry_sec"

int Dynamic_entry(int argc, void * argv[])
{
    unsigned long iReturnAddr;	    
    __asm
    {
        MOV iReturnAddr,PC
    }
	rtcinit(iReturnAddr);
	main(argc, argv);
    return R9;
}

#pragma arm section code


