#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

uint16_t load_uint16_big(void *p) 
{
	uint8_t *p8 = (uint8_t *) p;
	uint16_t a = p8[0];
	uint16_t b = p8[1];
	
	return (a << 8) | (b);
}

// Parse Flow 2 into 5 BIGNUMs, check p and q upper and lower bounds
int flow2_pqlen_ok(void *p1, void *p2) 
{
	uint8_t q_range[4] = {0x00, 0xFF, 0x01, 0x00};
	BIGNUM* p;   
	BIGNUM* q;
	BIGNUM* q_min = BN_new();
	BIGNUM* q_max = BN_new();
	BIGNUM* s_a_bn = BN_new();
	BIGNUM* s_a_bn_max = BN_new();
	BN_one(q_min);
	BN_one(q_max);
	BN_one(s_a_bn);
	BN_one(s_a_bn_max);
	BN_CTX* ctx = BN_CTX_new();
	//255 and 256
	int p_check[2];
	int q_check[2];
	int ret;	//value to be returned if everything is ok
	uint16_t bytes[5];
	uint8_t* buf1 = (uint8_t *)p1;
	uint8_t* buf2 = (uint8_t *)p2;
	for(int i = 0; i < 5; i++)
	{
		bytes[i] = load_uint16_big(buf2 + (i * 2));
	}
	uint16_t qint_min = load_uint16_big(q_range);
	uint16_t qint_max = load_uint16_big(q_range+2);
	uint16_t s_a = load_uint16_big(buf1);
	uint16_t s_a_max = s_a * 2;
	s_a -= 1;

	p = BN_bin2bn(buf2 + 10, bytes[0], NULL);
	q = BN_bin2bn(buf2 + 10 + bytes[0], bytes[1], NULL);

	BN_lshift(s_a_bn, s_a_bn, s_a);
	BN_lshift(s_a_bn_max, s_a_bn_max, s_a_max);

	//p_check[0] must be >= 0
	p_check[0] = BN_cmp(p, s_a_bn);
	//p_check[1] must be <= 0
	p_check[1] = BN_cmp(p, s_a_bn_max);

	BN_lshift(q_min, q_min, qint_min);
	BN_lshift(q_max, q_max, qint_max);
	//q_check[0] must be >= 0
	q_check[0] = BN_cmp(q, q_min);
	//q_check[1] must be <= 0
	q_check[1] = BN_cmp(q, q_max);
	
	BN_CTX_free(ctx);
	BN_free(p);	
	BN_free(q);
	BN_free(s_a_bn);
	BN_free(s_a_bn_max);
	BN_free(q_min);
	BN_free(q_max);
	if((p_check[0] >= 0 && p_check[1] <= 0) && 
			(q_check[0] >= 0 && q_check[1] <= 0))
		ret = 1;
	else
		ret = 0;
	return ret;
}