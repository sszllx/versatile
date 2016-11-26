
#include "sm2.h"
#include "smobj.h"

using namespace SM;

#define CHECK_SMART_PTR(obj) \
    do { \
        if (obj.isNull()) { \
            return; \
        } \
    } while (0);

SM2Alg::SM2Alg()
{

}

// 计算下一次间隔的时长
void SM2Alg::calNextInterval(QSharedPointer<sm_obj_t> item)
{
    CHECK_SMART_PTR(item);

    int repeat = item->repeat;
    if (repeat == 1) {
        item->interval = 1;

        return;
    } else if (repeat == 2) {
        item->interval = 6;

        return;
    }

    item->interval = item->interval * item->ef;

    return;
}

// q为0~5的记忆等级
void SM2Alg::calNewEF(QSharedPointer<sm_obj_t> item, int q)
{
    CHECK_SMART_PTR(item);

    item->ef = item->ef-0.8 +0.28*q-0.02*q*q;
}
