/* RSA.H - header file for RSA.C
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

//int RSAPublicEncrypt (unsigned char *, unsigned int *, unsigned char *, unsigned int,
//    R_RSA_PUBLIC_KEY *, R_RANDOM_STRUCT *);
#ifndef _RSA_H_
#define _RSA_H_
#include "rsaref.h"



int PACKAGE __fastcall RSAPublicEncrypt(
unsigned char *output,                                      /* output block */
unsigned int *outputLen,                          /* length of output block */
unsigned char *input,                                        /* input block */
unsigned int inputLen,                             /* length of input block */
R_RSA_PUBLIC_KEY *publicKey,                              /* RSA public key */
R_RANDOM_STRUCT *randomStruct                          /* random structure */
);
int PACKAGE __fastcall RSAPublicDecrypt (
unsigned char *output,                                      /* output block */
unsigned int *outputLen,                          /* length of output block */
unsigned char *input,                                        /* input block */
unsigned int inputLen,                             /* length of input block */
R_RSA_PUBLIC_KEY *publicKey                               /* RSA public key */
);
int PACKAGE __fastcall RSAPrivateEncrypt (
unsigned char *output,                                      /* output block */
unsigned int *outputLen,                          /* length of output block */
unsigned char *input,                                        /* input block */
unsigned int inputLen,                             /* length of input block */
R_RSA_PRIVATE_KEY *privateKey                           /* RSA private key */
);
int PACKAGE __fastcall RSAPrivateDecrypt (
unsigned char *output,                                      /* output block */
unsigned int *outputLen,                          /* length of output block */
unsigned char *input,                                        /* input block */
unsigned int inputLen,                             /* length of input block */
R_RSA_PRIVATE_KEY *privateKey                           /* RSA private key */
);

#endif

