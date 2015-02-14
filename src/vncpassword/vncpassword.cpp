// vncpassword.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
	#include "d3des.h"
}

#define MAXPWLEN 8
unsigned char FixedKey[8] = { 23, 82, 107, 6, 35, 78, 88, 7 };

int main(int argc, char* argv[])
{
	char* prog = (char*)argv[0];
	if (argc < 2 || argc > 2) {
		fprintf(stderr, "Usage: %s <Password>", prog);
		return 1;
	}
	char* passwd =  argv[1];
	if (strlen(argv[1]) > MAXPWLEN) {
		fprintf(stderr, "ERROR: Password cannot be longer than %i characters", MAXPWLEN);
		return 1;
	}

	// Pad password with nulls
	unsigned char encryptedPasswd[MAXPWLEN + 1];
	for (unsigned int i = 0; i < MAXPWLEN; i++) {
		if (i < strlen(passwd))
			encryptedPasswd[i] = passwd[i];
		else
			encryptedPasswd[i] = 0;
	}
	// Zero the memory of the plaintext password
	memset(passwd, 0, sizeof(passwd));

	// Create the obfuscated VNC key
	deskey(FixedKey, EN0);
	des(encryptedPasswd, encryptedPasswd);

	// Write the key to standard output
	for (unsigned int i = 0; i < MAXPWLEN; i++) {
		fprintf(stdout, "%02x\n", encryptedPasswd[i]);
	}

	// Zero the memory of the encrypted password
	memset(encryptedPasswd, 0, sizeof(encryptedPasswd));

	return 0;
}

