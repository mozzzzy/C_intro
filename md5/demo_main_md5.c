/*
	compile : cc -o demo_main_md5.c md5_converter.c -o md5_test.exe -lcrypto
*/

#include<stdio.h>
#include"md5_converter.h"


int main(void){

	char data[100] = "133.43.100.197/3mb.pdf";
	char* got_data;
	got_data = md5_conversion(data);

	printf("main : %s\n",got_data);
	return 0;

}
