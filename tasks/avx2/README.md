## AVX2

`avx` 相关资料还是比较难找的，稍微在此整理一下。

[TOC]

### 头部文件

``` c
#include <immintrin.h>
```

该头部不仅包含 `avx`、`avx2` 的函数，同样还包含了 `%xmm`/`%ymm` 寄存器（向量）数据类型/结构；

### 数据类型

```
__m{向量大小}{向量类型}
```

向量以 `__m` 两个下划线加一个 m 开头，后面跟着向量所占的比特位个数；向量类型默认为单精度浮点数，`d` 为双精度浮点数，`i` 为整型，根据整型类型的不同，向量中存储的整型个数缺不同；

| 数据类型 | 描述                                    | 大小        |
| -------- | --------------------------------------- | ----------- |
| __m128   | 包含 4 个` float` 类型的 128 bits 向量  | 4 * 32 bits |
| __m128d  | 包含 2 个 `double` 类型的 128 bits 向量 | 2 * 64 bits |
| __m128i  | 包含数个 `int` 类型的 128 bits 向量     | 128 bits    |
| __m256   | 包含 8 个 `float` 类型的 256 bits 向量  | 8 * 32 bits |
| __m256d  | 包含 4 个 `double` 类型的 256 bits 向量 | 4 * 64 bits |
| __m256i  | 包含数个 `int` 类型的 256 bits 向量     | 256 bits    |

以 `__m256i` 为例，对于不同的整数类型，向量中存储的个数为：

| 个数 | 单个数据大小 | 数据类型 |
| ---- | ------------ | -------- |
| 32   | 8 bit        | char     |
| 16   | 16 bit       | short    |
| 8    | 32 bit       | int      |
| 4    | 64 bit       | long     |

### 函数原型

```
__m{向量大小}{向量类型}|void|int _mm{向量大小}_{功能}_{子数据类型}
```

当函数的 `返回类型` 为向量 128 bits 时，开头 `向量大小` 为空；256 bits 时，`向量大小` 为 256；

`功能` 描述了函数的功能，例如向量相加为 `add`；

`子数据类型` 描述了向量中存放的数据类型，

| 数据类型         | 描述                                                 |
| ---------------- | ---------------------------------------------------- |
| ps               | float，将 32 bits 当成一个单精度浮点数               |
| pd               | double，将 64 bits 当成一个双精度浮点数              |
| epi8/16/32/64(x) | 将 8 bits/16 bits/32 bits/64 bits 当成一个有符号整型 |
| epu8/16/32/64(x) | 无符号整型                                           |
| 向量类型         | 输入类型与返回类型不同时会出现                       |
| si128/si256      | 不关心向量中的数据（整型）类型，只关注向量大小       |

*以上以一般常见的数据类型大小为例；*

### 示例代码

```c
#include <immintrin.h>

int main()
{
    double a[4] = {1.1, 2.2, 3.3, 4.4};
    double b[4] = {5.5, 6.6, 7.7, 8.8};
    double c[4];
    
    __m256d ymm0 = __mm256_loadu_pd(a);			// load 256-bits from memory
    __m256d ymm1 = __mm256_loadu_pd(b);			// the addr does not need to be aligned
    											// on any particular boundary
    __m256d ymm2 = __mm256_add_pd(ymm0, ymm1);	// add
    _mm256_store_pd(c, ymm2);					// store 256-bits into memory
    
    return 0;
}
```

由于使用了 `avx` 特性，在编译时需要开启支持：

```bash
gcc -mavx2
```

### 函数列表

想要运用 `avx` 有必要对函数有个大致的了解，可以参考官方文档 [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=AVX,AVX2)。

#### abs

```c
__m256i _mm256_abs_epi16 (__m256i a); // vpabsw
__m256i _mm256_abs_epi32 (__m256i a); // vpabsd
__m256i _mm256_abs_epi8 (__m256i a); // vpabsb
```

求有符号整型绝对值；

```c
int main()
{
    int ia[8] = {-10, -20, -30, -40, -50, -60, -70, -80};

    __m256i ymm0 = _mm256_loadu_si256((__m256i *) ia);
    __m256i ymm1 = _mm256_abs_epi32(ymm0);

    // 10, 20, 30, 40, 50, 60, 70, 80
    _mm256_storeu_si256((__m256i *) ia, ymm1);
    
    return 0;
}
```

*不同于浮点数，整数是直接按照向量大小读取与存储的，此时需要将整型地址显式地转化为向量指针；*

#### add

```c
__m256i _mm256_add_epi16 (__m256i a, __m256i b); // vpaddw
__m256i _mm256_add_epi32 (__m256i a, __m256i b); // vpaddd
__m256i _mm256_add_epi64 (__m256i a, __m256i b); // vpaddq
__m256i _mm256_add_epi8 (__m256i a, __m256i b); // vpaddb
__m256d _mm256_add_pd (__m256d a, __m256d b); // vaddpd
__m256 _mm256_add_ps (__m256 a, __m256 b); // vaddps
```

对两个向量做加法；

#### adds

```c
__m256i _mm256_adds_epi16 (__m256i a, __m256i b); // vpaddsw
__m256i _mm256_adds_epi8 (__m256i a, __m256i b); // vpaddsb
__m256i _mm256_adds_epu16 (__m256i a, __m256i b); // vpaddusw
__m256i _mm256_adds_epu8 (__m256i a, __m256i b); // vpaddusb
```

两个整数向量相加且考虑饱和问题；

**饱和运算**，即当运算结果大于某上限或小于某下限时，其运算结果为该上限或下限的一种运算方式。

由于使用饱和运算容易导致结合律以及分配律失效，这种运算并不常见于抽象数学领域，但在数字电路中广泛使用。

```c
int main()
{
    char ca[32] = {
        127, 127, -128, -128, 100, 100, -100, -100,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    char cb[32] = {
        1, 0, -1, 0, 100, 27, -100, -28,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    __m256i ymm0 = _mm256_loadu_si256((__m256i *) ca);
    __m256i ymm1 = _mm256_loadu_si256((__m256i *) cb);

    // 127 127 -128 -128 127 127 -128 -128
    _mm256_adds_epi8(ymm0, ymm1);

    return 0;
}
```

#### addsub

```c
__m256d _mm256_addsub_pd (__m256d a, __m256d b); // vaddsubpd
__m256 _mm256_addsub_ps (__m256 a, __m256 b); // vaddsubps
```

对两个向量偶数索引浮点数做减法（`a` - `b`），奇数索引浮点数做加法；

索引同原数组的索引，假设向量的最左边索引为 0 如同数组的顺序。

```c
int main()
{
    double a[4] = {6.6, 7.7, 8.8, 9.9};
    double b[4] = {1.1, 2.3, 3.3, 0.1};

    __m256d ymm0 = _mm256_loadu_pd(a);
    __m256d ymm1 = _mm256_loadu_pd(b);

    ymm1 = _mm256_addsub_pd(ymm0, ymm1);

    // 5.5 10.0 5.5 10.0
    _mm256_storeu_pd(a, ymm1);
    
    return 0;
}
```

#### alignr

```c
__m256i _mm256_alignr_epi8 (__m256i a, __m256i b, cont int imm8); // vpalignr
```

将向量 `a` 与向量 `b` 对位的 16 字节拼接（`a` 在前）得到 32 字节后，向右移位 `imm8` 个字节后，取低位 16 字节存于目标向量的对位位置；

```
FOR j := 0 to 1
	i := j*128
	tmp[255:0] := ((a[i+127:i] << 128)[255:0] OR b[i+127:i]) >> (imm8*8)
	dst[i+127:i] := tmp[127:0]
ENDFOR
dst[MAX:256] := 0
```

#### and

```c
__m256d _mm256_and_pd (__m256d a, __m256d b); // vandpd
__m256 _mm256_and_ps (__m256 a, __m256 b); // vandps
__m256i _mm256_and_si256 (__m256i a, __m256i b); // vpand
```

浮点数对位与，整型直接整个向量进行与操作；

#### andnot

```c
__m256d _mm256_andnot_pd (__m256d a, __m256d b); // vandnpd
__m256 _mm256_andnot_ps (__m256 a, __m256 b); // vandnps
__m256i _mm256_andnot_si256 (__m256i a, __m256i b); // vpandn
```

浮点数先将对位的 `a` 取非后再与对位的 `b` 进行与操作；

整型先将向量 `a` 整个取非后，直接与向量 `b` 整个向量进行与操作；

#### avg

```c
__m256i _mm256_avg_epu16 (__m256i a, __m256i b); // vpavgw
__m256i _mm256_avg_epu8 (__m256i a, __m256i b); // vpavgb
```

计算对位整型的平均值；**注意是向上取整；**

```c
int main()
{
    unsigned short a[16] = {
        1, 2, 3, 4, 5, 6, 7, 8,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    unsigned short b[16] = {
        0, 1, 2, 3, 5, 6, 7, 8,
        0, 0, 0, 0, 0, 0, 0, 0
    };	
    
    // __256i ymm0 = ...

    // 1 2 3 4 5 6 7 8
    _mm256_avg_epu16(ymm0, ymm1);

    return 0;
}
```

#### blend

```c
__m256i _mm256_blend_epi16 (__m256i a, __m256i b, const int imm8); // vpblendw
__m128i _mm_blend_epi32 (__m128i a, __m128i b, const int imm8); // vpblendd
__m256i _mm256_blend_epi32 (__m256i a, __m256i b, const int imm8); // vpblendd
__m256d _mm256_blend_pd (__m256d a, __m256d b, const int imm8); // vblendpd
__m256 _mm256_blend_ps (__m256 a, __m256 b, const int imm8); // vblendps
```

根据 `imm8` 作为掩码混合向量 `a` 和向量 `b`；

- 如果 `imm8` 第 `x` 位为 0 时，目标向量索引 `x` 取值向量 `a` 对应数值；
- 如果 `imm8` 第 `x` 位为 1 时，目标向量索引 `x` 取值向量 `b` 对应数值；

**注意**

- 当数据类型是 `epi16` 时，`imm8` 只能是 8 位有效位立即数，所以当子数据类型为 `epi16` 时，使用 `imm8[j%8]` 其中 `j` 为向量的索引；
- 其余情况，`imm8` 的有效位数必须与向量包含的索引数匹配；否则编译器会报错；

```c
int main()
{
    short a[16] = {
        1, 0, 3, 0, 5, 0, 7, 0,
        9, 0, 11, 0, 13, 0, 15, 0
    };
    short b[16] = {
        0, 2, 0, 4, 0, 6, 0, 8,
        0, 10, 0, 12, 0, 14, 0, 16
    };
    
	// __256i ymm0 = ...
    
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    _mm256_blend_epi16(ymm0, ymm1, 0b10101010);

    return 0;
}
```

#### blendv

```c
__m256i _mm256_blendv_epi8 (__m256i a, __m256i b, __m256i mask); // vpblendvb
__m256d _mm256_blendv_pd (__m256d a, __m256d b, __m256d mask); // vblendvpd
__m256 _mm256_blendv_ps (__m256 a, __m256 b, __m256 mask); // vblendvps
```

根据掩码向量中对位掩码的最高位（符号位）来取值于向量 `a` 还是向量 `b`；

- 如果掩码最高位（符号位）为 0 （正数）时，目标向量取值向量 `a` 对应数值；
- 如果掩码最高位（符号位）为 1 （负数）时，目标向量取值向量 `b` 对应数值；

```
FOR j := 0 to 31
	i := j*8
	IF mask[i+7]
		dst[i+7:i] := b[i+7:i]
	ELSE
		dst[i+7:i] := a[i+7:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

#### broadcast

```c
__m256d _mm256_broadcast_pd (__m128d const * mem_addr); // vbroadcastf128
__m256 _mm256_broadcast_ps (__m128 const * mem_addr); // vbroadcastf128
__m256d _mm256_broadcast_sd (double const * mem_addr); // vbroadcastsd
__m128 _mm_broadcast_ss (float const * mem_addr); // vbroadcastss
__m256 _mm256_broadcast_ss (float const * mem_addr); // vbroadcastss
```

通过地址将向量或单个浮点数扩展复制到目标长度的向量中；

#### broadcastb

```c
__m128i _mm_broadcastb_epi8 (__m128i a); // vpbroadcastb
__m256i _mm256_broadcastb_epi8 (__m128i a); // vpbroadcastb
```

将向量 `a` 最低位 `a[7:0] ` 8-bit 整型扩展复制到目标长度的向量中；

#### broadcastd

```c
__m128i _mm_broadcastd_epi32 (__m128i a); // vpbroadcastd
__m256i _mm256_broadcastd_epi32 (__m128i a); // vpbroadcastd
```

将向量 `a` 最低位 `a[31:0] ` 32-bit 整型扩展复制到目标长度的向量中；

#### broadcastq

```c
__m128i _mm_broadcastd_epi64 (__m128i a); // vpbroadcastq
__m256i _mm256_broadcastd_epi64 (__m128i a); // vpbroadcastq
```

将向量 `a` 最低位 `a[63:0] ` 64-bit 整型扩展复制到目标长度的向量中；

#### broadcastsd

```c
__m128d _mm_broadcastsd_pd (__m128d a); // movddup
__m256d _mm256_broadcastsd_pd (__m128d a); // vpbroadcastsd
```

将向量 `a` 最低位 `a[63:0] ` 64-bit 双精度浮点数扩展复制到目标长度的向量中；

#### broadcastsi128

```c
__m256i _mm_broadcastsi128_si256 (__m128i a); // vbroadcasti128
__m256i _mm256_broadcastsi128_si256 (__m128d a); // vbroadcasti128
```

将向量 `a` 128-bit 整型数据扩展复制到目标长度的向量中；

*不知道是否是文档的错误，两者返回类型一致；*

#### broadcastss

```c
__m128 _mm_broadcastss_ps (__m128 a); // vbroadcastss
__m256 _mm256_broadcastss_ps (__m128 a); // vbroadcastss
```

将向量 `a` 最低位 `a[31:0] ` 32-bit 单精度浮点数扩展复制到目标长度的向量中；

#### broadcastw

```c
__m128i _mm_broadcastw_epi16 (__m128i a); // vpbroadcastw
__m256i _mm256_broadcastw_epi616 (__m128i a); // vpbroadcastw
```

将向量 `a` 最低位 `a[15:0] ` 16-bit 整型扩展复制到目标长度的向量中；

#### bslli

```c
__m256i _mm256_bslli_epi128 (__m256i a, const int imm8); // vpslldq
```

将前后两通路向左移 `imm8` 个字节，低位补 0；

`imm8` 取低位单字节，若值大于 15 则取值 16；

#### bsrli

```c
__m256i _mm256_bsrli_epi128 (__m256i a, const int imm8); // vpsrldq
```

将前后两通路向右移 `imm8` 个字节，**高位补 0**；

`imm8` 取低位单字节，若值大于 15 则取值 16；

```c
int main()
{
    long a[4] = {
        -1, -1, -1, 1
    };

    // __256i ymm0 = ...

    // 1st lane: (0xffffffffffffffff ffffffffffffffff >> 64) == 0xffffffffffffffff
    // 2nd lane: (0x0000000000000001 ffffffffffffffff >> 64) == 0x0000000000000001
    // __256i: 0xffffffffffffffff 0000000000000000 0000000000000001 0000000000000000
    // -1 0 1 0
    _mm256_bsrli_epi128(ymm0, 8);
}
```

#### castpd

```c
__m256 _mm256_castpd_ps (__m256d a);
__m256i _mm256_castpd_si256 (__m256d a);
```

将向量类型 `__m256d` 转化为 `__m256` 或 `__m256i`；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castpd128

```c
__m256d _mm256_castpd128_pd256 (__m128d a);
```

将向量类型 `__m128d` 转化为 `__m256d`；高位 128-bit 是未定义的；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castpd256

```c
__m128d _mm256_castpd256_pd128 (__m256d a);
```

将向量类型 `__m256d` 转化为 `__m128d`；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castps

```c
__m256d _mm256_castps_pd (__m256 a);
__m256i _mm256_castps_si256 (__m256 a);
```

将向量类型 `__m256` 转化为 `__m256d` 或 `__m256i`；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castps128

```c
__m256 _mm256_castps128_ps256 (__m128 a);
```

将向量类型 `__m128` 转化为 `__m256`；高位 128-bit 是未定义的；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castps256

```c
__m128 _mm256_castps256_ps128 (__m256 a);
```

将向量类型 `__m256` 转化为 `__m128`；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castsi128

```c
__m256i _mm256_castsi128_si256 (__m128i a);
```

将向量类型 `__m128i` 转化为 `__m256i`；高位 128-bit 是未定义的；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### castsi256

```c
__m256d _mm256_castsi256_pd (__m256i a);
__m256 _mm256_castsi256_ps (__m256i a);
__m128i _mm256_castsi256_si128 (__m256i a);
```

将向量类型 `__m256i` 转化为 `__m256d`、`__m256` 或 `__m128i`；

*该函数只是修改汇编中媒体寄存器指代而不生成任何指令，所以没有延迟。*

#### ceil

```c
__m256d _mm256_ceil_pd (__m256d a); // vroundpd
__m256 _mm256_ceil_ps (__m256 a); // vroundps
```

将向量中的各个浮点数向上取整返回结果；

#### cmp

```c
__m128d _mm_cmp_pd (__128d a, __m128d b, const int imm8); // vcmppd
__m256d _mm256_cmp_pd (__m256d a, __256d b, const int imm8); // vcmppd
__m128 _mm_cmp_ps (__m128 a, __m128 b, const int imm8); // vcmpps
__m256 _mm256_cmp_ps (__m256 a, __256 b, const int imm8); // vcmpps
__m128d _mm_cmp_sd (__m128d a, __m128d b, const int imm8); // vcmpsd
__m128 _mm_cmp_ss (__m128 a, __m128 b, const int imm8); // vcmpss
```

得到将两个向量中对位的数按照 `imm8` 代表的方式进行比较的结果向量；成立时按照数的类型大小所有位置 1，否则置 0；

`sd` 和 `ss` 比较低位单个浮点数，并从向量 `a` 中复制高位至 128 位，其余高位置 0；

`imm8` 有效值及说明：

```c
/* Compare predicates for scalar and packed compare intrinsics.  */

/* Equal (ordered, non-signaling)  */
#define _CMP_EQ_OQ	0x00
/* Less-than (ordered, signaling)  */
#define _CMP_LT_OS	0x01
/* Less-than-or-equal (ordered, signaling)  */
#define _CMP_LE_OS	0x02
/* Unordered (non-signaling)  */
#define _CMP_UNORD_Q	0x03
/* Not-equal (unordered, non-signaling)  */
#define _CMP_NEQ_UQ	0x04
/* Not-less-than (unordered, signaling)  */
#define _CMP_NLT_US	0x05
/* Not-less-than-or-equal (unordered, signaling)  */
#define _CMP_NLE_US	0x06
/* Ordered (nonsignaling)   */
#define _CMP_ORD_Q	0x07
/* Equal (unordered, non-signaling)  */
#define _CMP_EQ_UQ	0x08
/* Not-greater-than-or-equal (unordered, signaling)  */
#define _CMP_NGE_US	0x09
/* Not-greater-than (unordered, signaling)  */
#define _CMP_NGT_US	0x0a
/* False (ordered, non-signaling)  */
#define _CMP_FALSE_OQ	0x0b
/* Not-equal (ordered, non-signaling)  */
#define _CMP_NEQ_OQ	0x0c
/* Greater-than-or-equal (ordered, signaling)  */
#define _CMP_GE_OS	0x0d
/* Greater-than (ordered, signaling)  */
#define _CMP_GT_OS	0x0e
/* True (unordered, non-signaling)  */
#define _CMP_TRUE_UQ	0x0f
/* Equal (ordered, signaling)  */
#define _CMP_EQ_OS	0x10
/* Less-than (ordered, non-signaling)  */
#define _CMP_LT_OQ	0x11
/* Less-than-or-equal (ordered, non-signaling)  */
#define _CMP_LE_OQ	0x12
/* Unordered (signaling)  */
#define _CMP_UNORD_S	0x13
/* Not-equal (unordered, signaling)  */
#define _CMP_NEQ_US	0x14
/* Not-less-than (unordered, non-signaling)  */
#define _CMP_NLT_UQ	0x15
/* Not-less-than-or-equal (unordered, non-signaling)  */
#define _CMP_NLE_UQ	0x16
/* Ordered (signaling)  */
#define _CMP_ORD_S	0x17
/* Equal (unordered, signaling)  */
#define _CMP_EQ_US	0x18
/* Not-greater-than-or-equal (unordered, non-signaling)  */
#define _CMP_NGE_UQ	0x19
/* Not-greater-than (unordered, non-signaling)  */
#define _CMP_NGT_UQ	0x1a
/* False (ordered, signaling)  */
#define _CMP_FALSE_OS	0x1b
/* Not-equal (ordered, signaling)  */
#define _CMP_NEQ_OS	0x1c
/* Greater-than-or-equal (ordered, non-signaling)  */
#define _CMP_GE_OQ	0x1d
/* Greater-than (ordered, non-signaling)  */
#define _CMP_GT_OQ	0x1e
/* True (unordered, signaling)  */
#define _CMP_TRUE_US	0x1f
```

`NaN`（非数）的阶码全为 1，符号位被忽略。通过尾数来判断是 `QNaN` 还是 `SNaN`：

- `QNaN`

  quiet `NaN`，静默非数。当禁止异常时，若浮点运算无效（例如“除以零”、“对负数开方”等），就返回 `QNaN` 表示运算无效。`QNaN` 的尾数最高位为 1，其他位非 0；

- `SNaN`

  signaling `NaN`，信号非数。当浮点运算遇到 `SNaN` 时，会立即抛出异常。例如可以用来检查变量是否被初始化。`SNaN` 的尾数最高位为 0，其他位非 0；

- `QNaN` Floating-Point Indefinite

  表示“不确定浮点值”的静默非数。

一般的比较关系只对数字（包括无穷大）有效。即两边的操作数都是数字，任何一个都不是 `NaN`。若任意操作数是 `NaN`，那么将无法进行比较，比较结果都返回 `False` 除了“不等于”比较，因为它是“等于”的相反值。

`无序` 是专门为 `NaN` 而设计的比较关系，

- 无序

  当至少一个操作数是 `NaN` 时，即 `无序`；可以理解为“不能比较大小”；

- 有序

  当操作数都不是 `NaN` 时，即 `有序`；可以理解为“能比较大小”；

浮点比较会因为是否抛出异常分为：

- `signaling`（发信号）

  遇到 `NaN` 时，设置 `IE`（Invalid Operation Flag），根据 `IM`（Invalid Operation Mask）决定是返回比较结果，还是抛出 `#IA`（Invalid Arithmetic Operand Exception）异常；

- `non-signaling`（不发信号）

  遇到 `NaN` 时，总是返回比较结果，从不抛出异常。

总结

1. 当比较方式为 `U` （`无序`）时，存在 `NaN` 时，直接返回 `True`，其余时候存在 `NaN` 时都返回 `False`；
2. `signaling` 和 `non-signaling` 只是用来控制是否抛出异常，对于比较结果没有影响；
