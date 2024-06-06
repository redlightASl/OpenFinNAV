#pragma once
#include "Define.h"


// #ifdef LIBROV_ENABLE_COMPLEX
/* older gcc compilers claim to be C11 compliant but do not support _Generic */
#if defined(__GNUC__) && (__GNUC__ < 7)
#define USE_COMPLEX_LEGACY 1
#endif
#if !defined(USE_COMPLEX_LEGACY) && !defined(I)
#include <complex.h>
typedef fp32_t _Complex mr_Complex_t;

#define MR_COMPLEX_RE(z) creal(z)
#define MR_COMPLEX_IM(z) cimag(z)
#define MR_COMPLEX_RE_P(zp) MR_COMPLEX_RE(*(zp))
#define MR_COMPLEX_IM_P(zp) MR_COMPLEX_IM(*(zp))
#define MR_SET_COMPLEX(zp,x,y) (*(zp) = (x) + I * (y))
#define MR_SET_RE(zp,x) do { MR_COMPLEX_RE(*(zp)) = (x); } while(0)
#define MR_SET_IM(zp,y) do { MR_COMPLEX_IM(*(zp)) = (y); } while(0)
#define MR_COMPLEX_EQ(z1,z2) ((z1) == (z2))
#else
struct mr_Complex
{
   fp32_t complex[2]; // real, imag
};
typedef struct mr_Complex mr_Complex_t;

#define MR_COMPLEX_RE(z) ((z).complex[0])
#define MR_COMPLEX_IM(z) ((z).complex[1])
#define MR_COMPLEX_RE_P(zp) ((zp)->complex[0])
#define MR_COMPLEX_IM_P(zp) ((zp)->complex[1])
#define MR_SET_COMPLEX(zp,x,y) do {(zp)->complex[0]=(x); (zp)->complex[1]=(y);} while(0)
#define MR_SET_RE(zp,x) do {(zp)->complex[0]=(x);} while(0)
#define MR_SET_IM(zp,y) do {(zp)->complex[1]=(y);} while(0)
#define MR_COMPLEX_EQ(z1,z2) (((z1).complex[0] == (z2).complex[0]) && ((z1).complex[1] == (z2).complex[1]))
#endif


mr_Complex_t mr_complex_rect(fp32_t x, fp32_t y);
mr_Complex_t mr_complex_polar(fp32_t r, fp32_t theta);

fp32_t mr_complex_arg(mr_Complex_t z); //求幅角
fp32_t mr_complex_abs(mr_Complex_t z); //求模

mr_Complex_t mr_complex_add(mr_Complex_t a, mr_Complex_t b);
mr_Complex_t mr_complex_sub(mr_Complex_t a, mr_Complex_t b);
mr_Complex_t mr_complex_mul(mr_Complex_t a, mr_Complex_t b);
mr_Complex_t mr_complex_div(mr_Complex_t a, mr_Complex_t b);
mr_Complex_t mr_complex_conj(mr_Complex_t z); //求共轭
mr_Complex_t mr_complex_neg(mr_Complex_t z); //求负数
mr_Complex_t mr_complex_inv(mr_Complex_t z); //求逆

// #endif /* LIBROV_ENABLE_COMPLEX */
