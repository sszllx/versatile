#ifndef SM2_H
#define SM2_H

#include <QtWidgets>
#include <QSharedPointer>

namespace SM {
    typedef struct sm_obj sm_obj_t;
}

class SM2Alg
{
 public:
    SM2Alg();

    void calNextInterval(QSharedPointer<SM::sm_obj_t> item);
    void calNewEF(QSharedPointer<SM::sm_obj_t> item, int q);

 private:
    QList<SM::sm_obj_t> m_obj_list;
};

#endif // SM2_H
