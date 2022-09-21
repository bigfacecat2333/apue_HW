#ifndef PROTO_H__
#define PROTO_H__

#include <stdint.h>

#define NAMEMAX 512-8-8//(UDP推荐长度-UDP报头长度-结构体的长度（math，chinese）)

struct msg_st{
    uint32_t math;
    uint32_t chinese;
    char name[0];  // NAMEMAX值
}__attribute__((packed));//不对齐,gcc解决

#endif
