#include "UniqueId.h"
    
XRender::UniqueID id_source = 0;
XRender::UniqueID XRender::RequestUniqueID()
{
    return id_source++;
}