// Auto generated file, don't modify.

#include "irrlicht.h"
#include "rect.h"

#include "cpgf/metadata/irrlicht/meta_irrlicht_rect.h"

using namespace cpgf;

namespace meta_irrlicht { 


GDefineMetaInfo createMetaClass_Global_rect()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_rect(0, _d);
    return _d.getMetaInfo();
}


GDefineMetaInfo createMetaClass_Rect()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<rect<s32> > _nd = GDefineMetaClass<rect<s32> >::declare("rect_s32");
        buildMetaClass_Rect<GDefineMetaClass<rect<s32> >, s32 >(0, _nd);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_irrlicht


