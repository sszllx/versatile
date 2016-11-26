#ifndef SMPROJECT_H
#define SMPROJECT_H

#include <QtCore>

namespace SM {
    typedef struct sm_obj sm_obj_t;
}

class SMProject : public QObject
{
    Q_OBJECT
public:
    SMProject();

    void addRootObj(QSharedPointer<SM::sm_obj_t> obj);

private:
    QList<QSharedPointer<SM::sm_obj_t> > root_list;
};

#endif // SMPROJECT_H
