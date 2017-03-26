#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<openssl/md5.h>

char mdString[33];
char *md5_conversion(char data[]){

	MD5_CTX c;
	unsigned char md[MD5_DIGEST_LENGTH];
	int r, i;

	r = MD5_Init(&c);
	if(r != 1) {
		perror("init");
		exit(1);
	}

	r = MD5_Update(&c, data, strlen(data));
	if(r != 1) {
		perror("update");
		exit(1);
	}

	r = MD5_Final(md, &c);
	if(r != 1) {
		perror("final");
		exit(1);
	}
		for(i = 0; i < 16; i++)
		 sprintf(&mdString[i * 2], "%02x", (unsigned int)md[i]);

	printf("md5 digest: %s\n", mdString);
	return mdString;
}
