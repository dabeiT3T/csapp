## AVX2

`avx` 相关资料还是比较难找的，稍微在此整理一下。

[TOC]

### 头部文件

``` c
#include <immintrin.h>
```

该头部不仅包含 `avx`、`avx2` 的函数，同样还包含了 `xmm` 寄存器（向量）数据类型/结构；

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

当函数的参数为 128 bits 时，开头 `向量大小` 为空；256 bits 时，`向量大小` 为 256；

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
    
    __m256d xmm0 = __mm256_loadu_pd(a);			// load 256-bits from memory
    __m256d xmm1 = __mm256_loadu_pd(b);			// the addr does not need to be aligned
    											// on any particular boundary
    __m256d xmm2 = __mm256_add_pd(xmm0, xmm1);	// add
    _mm256_store_pd(c, xmm2);					// store 256-bits into memory
    
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

    __m256i xmm0 = _mm256_loadu_si256((__m256i *) ia);
    __m256i xmm1 = _mm256_abs_epi32(xmm0);

    // 10, 20, 30, 40, 50, 60, 70, 80
    _mm256_storeu_si256((__m256i *) ia, xmm1);
    
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

    __m256i xmm0 = _mm256_loadu_si256((__m256i *) ca);
    __m256i xmm1 = _mm256_loadu_si256((__m256i *) cb);

    // 127 127 -128 -128 127 127 -128 -128
    xmm1 = _mm256_adds_epi8(xmm0, xmm1);

    return 0;
}
```

#### addsub

```c
__m256d _mm256_addsub_pd (__m256d a, __m256d b); // vaddsubpd
__m256 _mm256_addsub_ps (__m256 a, __m256 b); // vaddsubps
```

对两个向量偶数索引浮点数做减法（`a` - `b`），奇数索引浮点数做加法；

索引同原数组的索引，向量的最左边索引为 0。

```c
int main()
{
    double a[4] = {6.6, 7.7, 8.8, 9.9};
    double b[4] = {1.1, 2.3, 3.3, 0.1};

    __m256d xmm0 = _mm256_loadu_pd(a);
    __m256d xmm1 = _mm256_loadu_pd(b);

    xmm1 = _mm256_addsub_pd(xmm0, xmm1);

    // 5.5 10.0 5.5 10.0
    _mm256_storeu_pd(a, xmm1);
    
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
    
    // __256i xmm0 = ...

    // 1 2 3 4 5 6 7 8
    xmm1 = _mm256_avg_epu16(xmm0, xmm1);

    return 0;
}
```

#### blend

```c
__m256i _mm256_blend_epi16 (__m256i a, __m256i b, const int imm8); // vpblendw
__m128i _mm_blend_epi32 (__m128i a, __m128i b, const int imm8); // vpblendd
__m256i _mm256_blend_epi32 (__m256i a, __m256i b, const int imm8); // vpblendd
__m256d _mm256_blend_pd (__m256d a, __m256d b, const int imm8); // vblendpd
__m256 _mm256_blend_pd (__m256 a, __m256 b, const int imm8); // vblendps
```

根据 `imm8` 作为掩码混合向量 `a` 和向量 `b`；

- 如果 `imm8` 第 `x` 位为 0 时，目标向量索引 `x` 取值向量 `a` 对应数值；
- 如果 `imm8` 第 `x` 位为 1 时，目标向量索引 `x` 取值向量 `b` 对应数值；

注意

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
    
	// __256i xmm0 = ...
    
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    xmm1 = _mm256_blend_epi16(xmm0, xmm1, 0b10101010);

    return 0;
}
```

