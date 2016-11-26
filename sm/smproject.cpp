#include "smproject.h"
#include "smobj.h"

using namespace SM;

SMProject::SMProject()
{

}

void SMProject::addRootObj(QSharedPointer<sm_obj_t> obj)
{
    if (obj.isNull()) {
        return;
    }

    root_list.append(obj);
}
