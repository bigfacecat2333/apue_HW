#ifndef MYTBF_H__
#define MYTBF_H__

#define MYTBF_MAX 1024

typedef void mytbf_t;

// 每秒传输字符个数，token上限
mytbf_t *mytbf_init(int cps, int burst);

int mytbf_fetchtoken(mytbf_t *ptr, int size);

int mytbf_returntoken(mytbf_t *ptr, int size);

int mytbf_destory(mytbf_t *ptr);

#endif