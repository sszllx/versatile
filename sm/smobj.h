#ifndef SM_OBJ_H
#define SM_OBJ_H

#include <QtCore>
#include <QSharedPointer>

namespace SM {
    typedef enum {
        topic = 0,
        learn,
    } OBJ_TYPE;

    typedef enum {
        string = 0,
        picture,
        sound,
        video,
        TYPE_NUM,
    } ITEM_TYPE;

    typedef struct {
        ITEM_TYPE type;
        QString uri; // 如果是字符串，则uri就是字符串的内容
    } sm_item_t;

    struct sm_obj {
        // TODO:
        // Add layout information
        QString parent_uuid;
        QString uuid;
        OBJ_TYPE obj_type;
        QList<sm_item_t> questions;
        QList<sm_item_t> answers;
        int repeat;
        int interval; // days
        int ef; // E-Factor
        QDateTime last; // 最近一次重复的时间
        QDateTime next; // 下一次重复的时间
    };

    QSharedPointer<struct sm_obj> newSMObj();
    void delSMObj(QSharedPointer<struct sm_obj> obj);
    void resetSMObj(QSharedPointer<struct sm_obj> obj);
}


#endif // SM_OBJ_H
