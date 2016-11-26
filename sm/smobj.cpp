#include "smobj.h"

namespace SM {

    typedef struct sm_obj sm_obj_t;

    QSharedPointer<sm_obj_t> newSMObj()
    {
        QSharedPointer<sm_obj_t> obj;
        obj.reset(new sm_obj_t);
        resetSMObj(obj);
        return obj;
    }

    void delSMObj(QSharedPointer<sm_obj_t> obj)
    {
        obj.clear();
    }

    void resetSMObj(QSharedPointer<sm_obj_t> obj)
    {
        if (obj.isNull()) {
            return;
        }

        obj->uuid.clear();
        obj->questions.clear();
        obj->answers.clear();
        obj->repeat = 1;
        obj->interval = 0;
        obj->ef = 2.5;
    }
}
