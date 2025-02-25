						/*
					dct64_i486.c: DCT64, a plain C variant for i486
						
					copyright 1998-2006 by the mpg123 project - free software under the terms of the LGPL 2.1
					see COPYING and AUTHORS files in distribution or http://mpg123.org
					initially written by Fabrice Bellard
						*/
						
						/* Discrete Cosine Tansform (DCT) for subband synthesis.
                        *
                        * This code is optimized for 80486. It should be compiled with gcc
                        * 2.7.2 or higher.
                        *
                        * Note: This code does not give the necessary accuracy. Moreover, no
                        * overflow test are done.
                        *
                        * (c) 1998 Fabrice Bellard.  
                        */
						
						#include "mpg123lib_intern.h"
						
						#define COS_0_0 16403
						#define COS_0_1 16563
						#define COS_0_2 16890
						#define COS_0_3 17401
						#define COS_0_4 18124
						#define COS_0_5 19101
						#define COS_0_6 20398
						#define COS_0_7 22112
						#define COS_0_8 24396
						#define COS_0_9 27503
						#define COS_0_10 31869
						#define COS_0_11 38320
						#define COS_0_12 48633
						#define COS_0_13 67429
						#define COS_0_14 111660
						#define COS_0_15 333906
						#define COS_1_0 16463
						#define COS_1_1 17121
						#define COS_1_2 18577
						#define COS_1_3 21195
						#define COS_1_4 25826
						#define COS_1_5 34756
						#define COS_1_6 56441
						#define COS_1_7 167154
						#define COS_2_0 16704
						#define COS_2_1 19704
						#define COS_2_2 29490
						#define COS_2_3 83981
						#define COS_3_0 17733
						#define COS_3_1 42813
						#define COS_4_0 23170         
						
						#define SETOUT(out,n,expr) out[FIR_BUFFER_SIZE*(n)]=(expr)
						#define MULL(a,b) (((long long)(a)*(long long)(b)) >> 15)
						#define MUL(a,b) \
						(\
                    ((!(b & 0x3F)) ? (((a)*(b >> 6)) >> 9) :\
                    ((!(b & 0x1F)) ? (((a)*(b >> 5)) >> 10) :\
                    ((!(b & 0x0F)) ? (((a)*(b >> 4)) >> 11) :\
                    ((!(b & 0x07)) ? (((a)*(b >> 3)) >> 12) :\
                    ((!(b & 0x03)) ? (((a)*(b >> 2)) >> 13) :\
                    ((!(b & 0x01)) ? (((a)*(b >> 1)) >> 14) :\
(((a)*(b   )) >> 15))))))))
						
						
						void dct64_1_486(int *out0,int *out1,int *b1,int *b2)
						{
                        b1[0x00] = b2[0x00] + b2[0x1F];
                        b1[0x1F] = MUL((b2[0x00] - b2[0x1F]),COS_0_0);
						
                        b1[0x01] = b2[0x01] + b2[0x1E];
                        b1[0x1E] = MUL((b2[0x01] - b2[0x1E]),COS_0_1);
						
                        b1[0x02] = b2[0x02] + b2[0x1D];
                        b1[0x1D] = MUL((b2[0x02] - b2[0x1D]),COS_0_2);
						
                        b1[0x03] = b2[0x03] + b2[0x1C];
                        b1[0x1C] = MUL((b2[0x03] - b2[0x1C]),COS_0_3);
						
                        b1[0x04] = b2[0x04] + b2[0x1B];
                        b1[0x1B] = MUL((b2[0x04] - b2[0x1B]),COS_0_4);
						
                        b1[0x05] = b2[0x05] + b2[0x1A];
                        b1[0x1A] = MUL((b2[0x05] - b2[0x1A]),COS_0_5);
						
                        b1[0x06] = b2[0x06] + b2[0x19];
                        b1[0x19] = MUL((b2[0x06] - b2[0x19]),COS_0_6);
						
                        b1[0x07] = b2[0x07] + b2[0x18];
                        b1[0x18] = MUL((b2[0x07] - b2[0x18]),COS_0_7);
						
                        b1[0x08] = b2[0x08] + b2[0x17];
                        b1[0x17] = MUL((b2[0x08] - b2[0x17]),COS_0_8);
						
                        b1[0x09] = b2[0x09] + b2[0x16];
                        b1[0x16] = MUL((b2[0x09] - b2[0x16]),COS_0_9);
						
                        b1[0x0A] = b2[0x0A] + b2[0x15];
                        b1[0x15] = MUL((b2[0x0A] - b2[0x15]),COS_0_10);
						
                        b1[0x0B] = b2[0x0B] + b2[0x14];
                        b1[0x14] = MUL((b2[0x0B] - b2[0x14]),COS_0_11);
						
                        b1[0x0C] = b2[0x0C] + b2[0x13];
                        b1[0x13] = MUL((b2[0x0C] - b2[0x13]),COS_0_12);
						
                        b1[0x0D] = b2[0x0D] + b2[0x12];
                        b1[0x12] = MULL((b2[0x0D] - b2[0x12]),COS_0_13);
						
                        b1[0x0E] = b2[0x0E] + b2[0x11];
                        b1[0x11] = MULL((b2[0x0E] - b2[0x11]),COS_0_14);
						
                        b1[0x0F] = b2[0x0F] + b2[0x10];
                        b1[0x10] = MULL((b2[0x0F] - b2[0x10]),COS_0_15);
						
						
                        b2[0x00] = b1[0x00] + b1[0x0F]; 
                        b2[0x0F] = MUL((b1[0x00] - b1[0x0F]),COS_1_0);
                        b2[0x01] = b1[0x01] + b1[0x0E]; 
                        b2[0x0E] = MUL((b1[0x01] - b1[0x0E]),COS_1_1);
                        b2[0x02] = b1[0x02] + b1[0x0D]; 
                        b2[0x0D] = MUL((b1[0x02] - b1[0x0D]),COS_1_2);
                        b2[0x03] = b1[0x03] + b1[0x0C]; 
                        b2[0x0C] = MUL((b1[0x03] - b1[0x0C]),COS_1_3);
                        b2[0x04] = b1[0x04] + b1[0x0B]; 
                        b2[0x0B] = MUL((b1[0x04] - b1[0x0B]),COS_1_4);
                        b2[0x05] = b1[0x05] + b1[0x0A]; 
                        b2[0x0A] = MUL((b1[0x05] - b1[0x0A]),COS_1_5);
                        b2[0x06] = b1[0x06] + b1[0x09]; 
                        b2[0x09] = MUL((b1[0x06] - b1[0x09]),COS_1_6);
                        b2[0x07] = b1[0x07] + b1[0x08]; 
                        b2[0x08] = MULL((b1[0x07] - b1[0x08]),COS_1_7);
						
                        b2[0x10] = b1[0x10] + b1[0x1F];
                        b2[0x1F] = MUL((b1[0x1F] - b1[0x10]),COS_1_0);
                        b2[0x11] = b1[0x11] + b1[0x1E];
                        b2[0x1E] = MUL((b1[0x1E] - b1[0x11]),COS_1_1);
                        b2[0x12] = b1[0x12] + b1[0x1D];
                        b2[0x1D] = MUL((b1[0x1D] - b1[0x12]),COS_1_2);
                        b2[0x13] = b1[0x13] + b1[0x1C];
                        b2[0x1C] = MUL((b1[0x1C] - b1[0x13]),COS_1_3);
                        b2[0x14] = b1[0x14] + b1[0x1B];
                        b2[0x1B] = MUL((b1[0x1B] - b1[0x14]),COS_1_4);
                        b2[0x15] = b1[0x15] + b1[0x1A];
                        b2[0x1A] = MUL((b1[0x1A] - b1[0x15]),COS_1_5);
                        b2[0x16] = b1[0x16] + b1[0x19];
                        b2[0x19] = MUL((b1[0x19] - b1[0x16]),COS_1_6);
                        b2[0x17] = b1[0x17] + b1[0x18];
                        b2[0x18] = MULL((b1[0x18] - b1[0x17]),COS_1_7);
						
						
                        b1[0x00] = b2[0x00] + b2[0x07];
                        b1[0x07] = MUL((b2[0x00] - b2[0x07]),COS_2_0);
                        b1[0x01] = b2[0x01] + b2[0x06];
                        b1[0x06] = MUL((b2[0x01] - b2[0x06]),COS_2_1);
                        b1[0x02] = b2[0x02] + b2[0x05];
                        b1[0x05] = MUL((b2[0x02] - b2[0x05]),COS_2_2);
                        b1[0x03] = b2[0x03] + b2[0x04];
                        b1[0x04] = MULL((b2[0x03] - b2[0x04]),COS_2_3);
						
                        b1[0x08] = b2[0x08] + b2[0x0F];
                        b1[0x0F] = MUL((b2[0x0F] - b2[0x08]),COS_2_0);
                        b1[0x09] = b2[0x09] + b2[0x0E];
                        b1[0x0E] = MUL((b2[0x0E] - b2[0x09]),COS_2_1);
                        b1[0x0A] = b2[0x0A] + b2[0x0D];
                        b1[0x0D] = MUL((b2[0x0D] - b2[0x0A]),COS_2_2);
                        b1[0x0B] = b2[0x0B] + b2[0x0C];
                        b1[0x0C] = MULL((b2[0x0C] - b2[0x0B]),COS_2_3);
						
                        b1[0x10] = b2[0x10] + b2[0x17];
                        b1[0x17] = MUL((b2[0x10] - b2[0x17]),COS_2_0);
                        b1[0x11] = b2[0x11] + b2[0x16];
                        b1[0x16] = MUL((b2[0x11] - b2[0x16]),COS_2_1);
                        b1[0x12] = b2[0x12] + b2[0x15];
                        b1[0x15] = MUL((b2[0x12] - b2[0x15]),COS_2_2);
                        b1[0x13] = b2[0x13] + b2[0x14];
                        b1[0x14] = MULL((b2[0x13] - b2[0x14]),COS_2_3);
						
                        b1[0x18] = b2[0x18] + b2[0x1F];
                        b1[0x1F] = MUL((b2[0x1F] - b2[0x18]),COS_2_0);
                        b1[0x19] = b2[0x19] + b2[0x1E];
                        b1[0x1E] = MUL((b2[0x1E] - b2[0x19]),COS_2_1);
                        b1[0x1A] = b2[0x1A] + b2[0x1D];
                        b1[0x1D] = MUL((b2[0x1D] - b2[0x1A]),COS_2_2);
                        b1[0x1B] = b2[0x1B] + b2[0x1C];
                        b1[0x1C] = MULL((b2[0x1C] - b2[0x1B]),COS_2_3);
						
						
                        b2[0x00] = b1[0x00] + b1[0x03];
                        b2[0x03] = MUL((b1[0x00] - b1[0x03]),COS_3_0);
                        b2[0x01] = b1[0x01] + b1[0x02];
                        b2[0x02] = MUL((b1[0x01] - b1[0x02]),COS_3_1);
						
                        b2[0x04] = b1[0x04] + b1[0x07];
                        b2[0x07] = MUL((b1[0x07] - b1[0x04]),COS_3_0);
                        b2[0x05] = b1[0x05] + b1[0x06];
                        b2[0x06] = MUL((b1[0x06] - b1[0x05]),COS_3_1);
						
                        b2[0x08] = b1[0x08] + b1[0x0B];
                        b2[0x0B] = MUL((b1[0x08] - b1[0x0B]),COS_3_0);
                        b2[0x09] = b1[0x09] + b1[0x0A];
                        b2[0x0A] = MUL((b1[0x09] - b1[0x0A]),COS_3_1);
                        
                        b2[0x0C] = b1[0x0C] + b1[0x0F];
                        b2[0x0F] = MUL((b1[0x0F] - b1[0x0C]),COS_3_0);
                        b2[0x0D] = b1[0x0D] + b1[0x0E];
                        b2[0x0E] = MUL((b1[0x0E] - b1[0x0D]),COS_3_1);
						
                        b2[0x10] = b1[0x10] + b1[0x13];
                        b2[0x13] = MUL((b1[0x10] - b1[0x13]),COS_3_0);
                        b2[0x11] = b1[0x11] + b1[0x12];
                        b2[0x12] = MUL((b1[0x11] - b1[0x12]),COS_3_1);
						
                        b2[0x14] = b1[0x14] + b1[0x17];
                        b2[0x17] = MUL((b1[0x17] - b1[0x14]),COS_3_0);
                        b2[0x15] = b1[0x15] + b1[0x16];
                        b2[0x16] = MUL((b1[0x16] - b1[0x15]),COS_3_1);
						
                        b2[0x18] = b1[0x18] + b1[0x1B];
                        b2[0x1B] = MUL((b1[0x18] - b1[0x1B]),COS_3_0);
                        b2[0x19] = b1[0x19] + b1[0x1A];
                        b2[0x1A] = MUL((b1[0x19] - b1[0x1A]),COS_3_1);
						
                        b2[0x1C] = b1[0x1C] + b1[0x1F];
                        b2[0x1F] = MUL((b1[0x1F] - b1[0x1C]),COS_3_0);
                        b2[0x1D] = b1[0x1D] + b1[0x1E];
                        b2[0x1E] = MUL((b1[0x1E] - b1[0x1D]),COS_3_1);
						
                        {
                    int i;
                    for(i=0;i<32;i+=4) {
                    b1[i+0x00] = b2[i+0x00] + b2[i+0x01];
                    b1[i+0x01] = MUL((b2[i+0x00] - b2[i+0x01]),COS_4_0);
                    b1[i+0x02] = b2[i+0x02] + b2[i+0x03];
                    b1[i+0x03] = MUL((b2[i+0x03] - b2[i+0x02]),COS_4_0);
                    }
                        }
						
                        b1[0x02] += b1[0x03];
                        b1[0x06] += b1[0x07];
                        b1[0x04] += b1[0x06];
                        b1[0x06] += b1[0x05];
                        b1[0x05] += b1[0x07];
						
                        b1[0x0A] += b1[0x0B];
                        b1[0x0E] += b1[0x0F];
                        b1[0x0C] += b1[0x0E];
                        b1[0x0E] += b1[0x0D];
                        b1[0x0D] += b1[0x0F];
						
                        b1[0x12] += b1[0x13];
                        b1[0x16] += b1[0x17];
                        b1[0x14] += b1[0x16];
                        b1[0x16] += b1[0x15];
                        b1[0x15] += b1[0x17];
						
                        b1[0x1A] += b1[0x1B];
                        b1[0x1E] += b1[0x1F];
                        b1[0x1C] += b1[0x1E];
                        b1[0x1E] += b1[0x1D];
                        b1[0x1D] += b1[0x1F];
						
                        SETOUT(out0,16,b1[0x00]);
                        SETOUT(out0,12,b1[0x04]);
                        SETOUT(out0, 8,b1[0x02]);
                        SETOUT(out0, 4,b1[0x06]);
                        SETOUT(out0, 0,b1[0x01]);
                        SETOUT(out1, 0,b1[0x01]);
                        SETOUT(out1, 4,b1[0x05]);
                        SETOUT(out1, 8,b1[0x03]);
                        SETOUT(out1,12,b1[0x07]);
						
                        b1[0x08] += b1[0x0C];
                        SETOUT(out0,14,b1[0x08]);
                        b1[0x0C] += b1[0x0a];
                        SETOUT(out0,10,b1[0x0C]);
                        b1[0x0A] += b1[0x0E];
                        SETOUT(out0, 6,b1[0x0A]);
                        b1[0x0E] += b1[0x09];
                        SETOUT(out0, 2,b1[0x0E]);
                        b1[0x09] += b1[0x0D];
                        SETOUT(out1, 2,b1[0x09]);
                        b1[0x0D] += b1[0x0B];
                        SETOUT(out1, 6,b1[0x0D]);
                        b1[0x0B] += b1[0x0F];
                        SETOUT(out1,10,b1[0x0B]);
                        SETOUT(out1,14,b1[0x0F]);
						
                        b1[0x18] += b1[0x1C];
                        SETOUT(out0,15,b1[0x10] + b1[0x18]);
                        SETOUT(out0,13,b1[0x18] + b1[0x14]);
                        b1[0x1C] += b1[0x1a];
                        SETOUT(out0,11,b1[0x14] + b1[0x1C]);
                        SETOUT(out0, 9,b1[0x1C] + b1[0x12]);
                        b1[0x1A] += b1[0x1E];
                        SETOUT(out0, 7,b1[0x12] + b1[0x1A]);
                        SETOUT(out0, 5,b1[0x1A] + b1[0x16]);
                        b1[0x1E] += b1[0x19];
                        SETOUT(out0, 3,b1[0x16] + b1[0x1E]);
                        SETOUT(out0, 1,b1[0x1E] + b1[0x11]);
                        b1[0x19] += b1[0x1D];
                        SETOUT(out1, 1,b1[0x11] + b1[0x19]);
                        SETOUT(out1, 3,b1[0x19] + b1[0x15]);
                        b1[0x1D] += b1[0x1B];
                        SETOUT(out1, 5,b1[0x15] + b1[0x1D]);
                        SETOUT(out1, 7,b1[0x1D] + b1[0x13]);
                        b1[0x1B] += b1[0x1F];
                        SETOUT(out1, 9,b1[0x13] + b1[0x1B]);
                        SETOUT(out1,11,b1[0x1B] + b1[0x17]);
                        SETOUT(out1,13,b1[0x17] + b1[0x1F]);
                        SETOUT(out1,15,b1[0x1F]);
						}
						
						
						/*
                        * the call via dct64 is a trick to force GCC to use
                        * (new) registers for the b1,b2 pointer to the bufs[xx] field
                        */
						void dct64_i486(int *a,int *b,real *samples)
						{
                        int bufs[64];
                        int i;
						
						#ifdef REAL_IS_FIXED  
						#define TOINT(a) ((a) * 32768 / (int)REAL_FACTOR)
						
                        for(i=0;i<32;i++) {
                    bufs[i]=TOINT(samples[i]);
                        }
						#else      
                        int *p = bufs;
                        register double const scale = ((65536.0 * 32) + 1) * 65536.0;
                        
                        for(i=0;i<32;i++) {
                    *((double *) (p++)) = scale + *samples++; /* beware on bufs overrun: 8B store from x87 */
                        }
						#endif
                        
                        dct64_1_486(a,b,bufs+32,bufs);
						}
						
						