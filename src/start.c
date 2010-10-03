
#include <string.h>
#include <stdio.h>

extern char Image$$RO$$Base[]; //��� RO ����ڵ���ʼ��ַ��
extern char Image$$RO$$Limit[];// ��� RO �����ĩβ����ĵ�һ���ֽڵĵ�ַ�� 
extern char Image$$RW$$Base[]; //��� RW ����ڵĿ�ʼ��ַ��  
extern char Image$$RW$$Limit[];// ��� ZI �����ĩβ������ֽڵĵ�ַ�� ��ѡ�� ZI ��ĩβ������ RW ��ĩβ��Ϊ������������֮�䱣�ּ��ݡ��� 
extern char Image$$ZI$$Base[]; //��� ZI ����ڵĿ�ʼ��ַ�� 
extern char Image$$ZI$$Limit[];// ��� ZI �����ĩβ������ֽڵĵ�ַ�� 


#define RO_LENGTH (Image$$RO$$Limit-Image$$RO$$Base)
//#define RW_LENGTH (Image$$RW$$Limit-Image$$RW$$Base) //fla mask ,as :��ѡ�� ZI ��ĩβ������ RW ��ĩβ��Ϊ������������֮�䱣�ּ��ݡ���
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


