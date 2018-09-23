/* RSAREF.H - header file for RSAREF cryptographic toolkit
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#ifndef _RSAREF_H_
#define _RSAREF_H_
#include <Classes.hpp>
#include <mem.h>
#include "global.h"
#include "md2.h"
#include "md5.h"
#include "des.h"

/* Message-digest algorithms.
 */
#define DA_MD2 3
#define DA_MD5 5

/* Encryption algorithms to be ored with digest algorithm in Seal and Open.
 */
#define EA_DES_CBC 1
#define EA_DES_EDE2_CBC 2
#define EA_DES_EDE3_CBC 3
#define EA_DESX_CBC 4

/* RSA key lengths.
 */
//#define MIN_RSA_MODULUS_BITS 508
#define MIN_RSA_MODULUS_BITS 256
#define MAX_RSA_MODULUS_BITS 1024
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS + 7) / 8)

/* Maximum lengths of encoded and encrypted content, as a function of
   content length len. Also, inverse functions.
 */
#define ENCODED_CONTENT_LEN(len) (4*(len)/3 + 3)
#define ENCRYPTED_CONTENT_LEN(len) ENCODED_CONTENT_LEN ((len)+8)
#define DECODED_CONTENT_LEN(len) (3*(len)/4 + 1)
#define DECRYPTED_CONTENT_LEN(len) (DECODED_CONTENT_LEN (len) - 1)

/* Maximum lengths of signatures, encrypted keys, encrypted
   signatures, and message digests.
 */
#define MAX_SIGNATURE_LEN MAX_RSA_MODULUS_LEN
#define MAX_PEM_SIGNATURE_LEN ENCODED_CONTENT_LEN (MAX_SIGNATURE_LEN)
#define MAX_ENCRYPTED_KEY_LEN MAX_RSA_MODULUS_LEN
#define MAX_PEM_ENCRYPTED_KEY_LEN ENCODED_CONTENT_LEN (MAX_ENCRYPTED_KEY_LEN)
#define MAX_PEM_ENCRYPTED_SIGNATURE_LEN \
  ENCRYPTED_CONTENT_LEN (MAX_SIGNATURE_LEN)
#define MAX_DIGEST_LEN 16

/* Maximum length of Diffie-Hellman parameters.
 */
#define DH_PRIME_LEN(bits) (((bits) + 7) / 8)

/* Error codes.
 */
#define RE_CONTENT_ENCODING 0x0400
#define RE_DATA 0x0401
#define RE_DIGEST_ALGORITHM 0x0402
#define RE_ENCODING 0x0403
#define RE_KEY 0x0404
#define RE_KEY_ENCODING 0x0405
#define RE_LEN 0x0406
#define RE_MODULUS_LEN 0x0407
#define RE_NEED_RANDOM 0x0408
#define RE_PRIVATE_KEY 0x0409
#define RE_PUBLIC_KEY 0x040a
#define RE_SIGNATURE 0x040b
#define RE_SIGNATURE_ENCODING 0x040c
#define RE_ENCRYPTION_ALGORITHM 0x040d


#ifdef IU_NO_PACKAGE
#undef  PACKAGE
#define PACKAGE
#endif
/* Random structure.
 */
struct R_RANDOM_STRUCT{
  unsigned int bytesNeeded;
  unsigned char state[16];
  unsigned int outputAvailable;
  unsigned char output[16];
};

/* RSA public and private key.
 */
struct R_RSA_PUBLIC_KEY{
  unsigned int bits;                           /* length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];                    /* modulus */
  unsigned char exponent[MAX_RSA_MODULUS_LEN];           /* public exponent */
} ;

struct R_RSA_PRIVATE_KEY{
  unsigned int bits;                           /* length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];                    /* modulus */
  unsigned char publicExponent[MAX_RSA_MODULUS_LEN];     /* public exponent */
  unsigned char exponent[MAX_RSA_MODULUS_LEN];          /* private exponent */
  unsigned char prime[2][MAX_RSA_PRIME_LEN];               /* prime factors */
  unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];   /* exponents for CRT */
  unsigned char coefficient[MAX_RSA_PRIME_LEN];          /* CRT coefficient */
} ;

/* RSA prototype key.
 */
struct R_RSA_PROTO_KEY{
  unsigned int bits;                           /* length in bits of modulus */
  int useFermat4;                        /* public exponent (1 = F4, 0 = 3) */
};

/* Diffie-Hellman parameters.
 */
struct R_DH_PARAMS{
  unsigned char *prime;                                            /* prime */
  unsigned int primeLen;                                 /* length of prime */
  unsigned char *generator;                                    /* generator */
  unsigned int generatorLen;                         /* length of generator */
} ;

struct R_DIGEST_CTX{
  int digestAlgorithm;
  union {
    MD2_CTX md2;
    MD5_CTX md5;
  } context;
};

struct R_SIGNATURE_CTX {
  R_DIGEST_CTX digestContext;
};

struct R_ENVELOPE_CTX {
  int encryptionAlgorithm;
  union {
    DES_CBC_CTX des;
    DES3_CBC_CTX des3;
    DESX_CBC_CTX desx;
  } cipherContext;

  unsigned char buffer[8];
  unsigned int bufferLen;
};

/* Random structures.
 */
int PACKAGE __fastcall R_RandomInit(R_RANDOM_STRUCT *);
int PACKAGE __fastcall R_RandomUpdate(R_RANDOM_STRUCT *, unsigned char *, unsigned int);
int PACKAGE __fastcall R_GetRandomBytesNeeded(unsigned int *, R_RANDOM_STRUCT *);
void PACKAGE __fastcall R_RandomFinal(R_RANDOM_STRUCT *);

/* Cryptographic procedures "by parts"
 */
int PACKAGE __fastcall R_DigestInit(R_DIGEST_CTX *, int);
int PACKAGE __fastcall R_DigestUpdate(R_DIGEST_CTX *, unsigned char *, unsigned int);
int PACKAGE __fastcall R_DigestFinal(R_DIGEST_CTX *, unsigned char *, unsigned int *);

int PACKAGE __fastcall R_SignInit(R_SIGNATURE_CTX *, int);
int PACKAGE __fastcall R_SignUpdate(R_SIGNATURE_CTX *, unsigned char *, unsigned int);
int PACKAGE __fastcall R_SignFinal(R_SIGNATURE_CTX *, unsigned char *, unsigned int *, R_RSA_PRIVATE_KEY *);

int PACKAGE __fastcall R_VerifyInit(R_SIGNATURE_CTX *, int);
int PACKAGE __fastcall R_VerifyUpdate(R_SIGNATURE_CTX *, unsigned char *, unsigned int);
int PACKAGE __fastcall R_VerifyFinal(R_SIGNATURE_CTX *, unsigned char *, unsigned int, R_RSA_PUBLIC_KEY *);

int PACKAGE __fastcall R_SealInit(R_ENVELOPE_CTX *, unsigned char **, unsigned int *, unsigned char [8],
    unsigned int, R_RSA_PUBLIC_KEY **, int, R_RANDOM_STRUCT *);
int PACKAGE __fastcall R_SealUpdate(R_ENVELOPE_CTX *, unsigned char *, unsigned int *, unsigned char *,
    unsigned int);
int PACKAGE __fastcall R_SealFinal(R_ENVELOPE_CTX *, unsigned char *, unsigned int *);

int PACKAGE __fastcall R_OpenInit(R_ENVELOPE_CTX *, int, unsigned char *, unsigned int, unsigned char [8],
    R_RSA_PRIVATE_KEY *);
int PACKAGE __fastcall R_OpenUpdate(R_ENVELOPE_CTX *, unsigned char *, unsigned int *, unsigned char *,
    unsigned int);
int PACKAGE __fastcall R_OpenFinal(R_ENVELOPE_CTX *, unsigned char *, unsigned int *);

/* Cryptographic enhancements by block.
 */
int PACKAGE __fastcall R_SignPEMBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int *,
    unsigned char *, unsigned int, int, int, R_RSA_PRIVATE_KEY *);
int PACKAGE __fastcall R_SignBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int, int,
    R_RSA_PRIVATE_KEY *);
int PACKAGE __fastcall R_VerifyPEMSignature(unsigned char *, unsigned int *, unsigned char *, unsigned int,
    unsigned char *, unsigned int, int, int, R_RSA_PUBLIC_KEY *);
int PACKAGE __fastcall R_VerifyBlockSignature(unsigned char *, unsigned int, unsigned char *, unsigned int, int,
    R_RSA_PUBLIC_KEY *);
int PACKAGE __fastcall R_SealPEMBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int *,
    unsigned char *, unsigned int *, unsigned char [8], unsigned char *,
    unsigned int, int, R_RSA_PUBLIC_KEY *, R_RSA_PRIVATE_KEY *,
    R_RANDOM_STRUCT *);
int PACKAGE __fastcall R_OpenPEMBlock
  (unsigned char *, unsigned int *, unsigned char *, unsigned int,
    unsigned char *, unsigned int, unsigned char *, unsigned int,
    unsigned char [8], int, R_RSA_PRIVATE_KEY *, R_RSA_PUBLIC_KEY *);
int PACKAGE __fastcall R_DigestBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int, int);

/* Printable ASCII encoding and decoding.
 */
int PACKAGE __fastcall R_EncodePEMBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int);
int PACKAGE __fastcall R_DecodePEMBlock(unsigned char *, unsigned int *, unsigned char *, unsigned int);

/* Key-pair generation.
 */
int PACKAGE __fastcall R_GeneratePEMKeys(R_RSA_PUBLIC_KEY *, R_RSA_PRIVATE_KEY *, R_RSA_PROTO_KEY *,
    R_RANDOM_STRUCT *);

/* Diffie-Hellman key agreement.
 */
int PACKAGE __fastcall R_GenerateDHParams(R_DH_PARAMS *, unsigned int, unsigned int, R_RANDOM_STRUCT *);
int PACKAGE __fastcall R_SetupDHAgreement(unsigned char *, unsigned char *, unsigned int, R_DH_PARAMS *,
    R_RANDOM_STRUCT *);
int PACKAGE __fastcall R_ComputeDHAgreedKey(unsigned char *, unsigned char *, unsigned char *, unsigned int,
    R_DH_PARAMS *);

/* Routines supplied by the implementor.
 */
/*
void __fastcall R_memset(POINTER, int, unsigned int);
void __fastcall R_memcpy(POINTER, POINTER, unsigned int);
int __fastcall R_memcmp(POINTER, POINTER, unsigned int);
*/
//#define R_memset((Pointer1), (val), (len)) memset((Pointer1), (val), (len))
//#define R_memcpy((Pointer1), (Pounter2), (len)) memcpy(Pointer1, (Pointer2), (len))
//#define R_memcmp((Pointer1), (Pointer2), (len)) memcmp((Pointer1), (Pointer2), (len))

#define R_memset memset
#define R_memcpy memcpy
#define R_memcmp memcmp
//__memcmp__

#endif
