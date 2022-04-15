
/* Inner product. Accumulate in temporary */
void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum0 = (data_t) 0;
    data_t sum1 = (data_t) 0;
    data_t sum2 = (data_t) 0;
    data_t sum3 = (data_t) 0;
    data_t sum4 = (data_t) 0;
    data_t sum5 = (data_t) 0;

    for (i = 0; i < limit; i+=6) {
        sum0 = sum0 + udata[i] * vdata[i];
        sum1 = sum1 + udata[i+1] * vdata[i+1];
        sum2 = sum2 + udata[i+2] * vdata[i+2];
        sum3 = sum3 + udata[i+3] * vdata[i+3];
        sum4 = sum4 + udata[i+4] * vdata[i+4];
        sum5 = sum5 + udata[i+5] * vdata[i+5];
    }

    for (; i < length; i++)
        sum0 = sum0 + udata[i] * vdata[i];

    *dest = sum0 + sum1 + sum2 + sum3 + sum4 + sum5;
}

// int
// to reach the (min CEP) throughput of the int-mul(1.0), we need the factor >= C * L = 1 * 3 = 3.
// to reach the (min CEP) throughput of the int-add(0.5), we need the factor >= 2 * 1 = 2;
// here the factor is 6, so we can reach the min CEP.
// but, int-add needs to wait for the result from int-mul(1.0). the main path changed.
// as a result, the min CPE limits to 1.0.

// float
// to reach the (min CEP) throughput of the float-mul(1.0), we need the factor >= C * L = 2 * 3 = 6.
// to reach the (min CEP) throughput of the float-add(1.0), we need the factor >= 1 * 3 = 3;
// here the factor is 6, so we can reach the min CEP.
// as a result, the min CPE limit to 1.0.
