// Auto generated file, don't modify.

#ifndef __META_IRRLICHT_IRRLIST_H
#define __META_IRRLICHT_IRRLIST_H


#include "gmetaobjectlifemanager_irrlicht_ireferencecounted.h"
#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace irr;
using namespace irr::core;


namespace meta_irrlicht { 


template <typename D, typename T>
void buildMetaClass_List(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const list< T > &)>();
    _d.CPGF_MD_TEMPLATE _method("begin", (list<T >::Iterator (D::ClassType::*) ())&D::ClassType::begin);
    _d.CPGF_MD_TEMPLATE _method("begin", (list<T >::ConstIterator (D::ClassType::*) () const)&D::ClassType::begin);
    _d.CPGF_MD_TEMPLATE _method("clear", &D::ClassType::clear);
    _d.CPGF_MD_TEMPLATE _method("empty", &D::ClassType::empty);
    _d.CPGF_MD_TEMPLATE _method("end", (list<T >::Iterator (D::ClassType::*) ())&D::ClassType::end);
    _d.CPGF_MD_TEMPLATE _method("end", (list<T >::ConstIterator (D::ClassType::*) () const)&D::ClassType::end);
    _d.CPGF_MD_TEMPLATE _method("erase", &D::ClassType::erase);
    _d.CPGF_MD_TEMPLATE _method("getLast", (list<T >::Iterator (D::ClassType::*) ())&D::ClassType::getLast);
    _d.CPGF_MD_TEMPLATE _method("getLast", (list<T >::ConstIterator (D::ClassType::*) () const)&D::ClassType::getLast);
    _d.CPGF_MD_TEMPLATE _method("getSize", &D::ClassType::getSize);
    _d.CPGF_MD_TEMPLATE _method("insert_after", &D::ClassType::insert_after);
    _d.CPGF_MD_TEMPLATE _method("insert_before", &D::ClassType::insert_before);
    _d.CPGF_MD_TEMPLATE _method("push_back", &D::ClassType::push_back);
    _d.CPGF_MD_TEMPLATE _method("push_front", &D::ClassType::push_front);
    _d.CPGF_MD_TEMPLATE _method("size", &D::ClassType::size);
    _d.CPGF_MD_TEMPLATE _method("swap", &D::ClassType::swap);
    _d.CPGF_MD_TEMPLATE _operator<void (*)(cpgf::GMetaSelf, const list< T > &)>(mopHolder = mopHolder);
    {
        GDefineMetaClass<list::ConstIterator> _nd = GDefineMetaClass<list::ConstIterator>::declare("ConstIterator");
        _nd.CPGF_MD_TEMPLATE _constructor<void * ()>();
        _nd.CPGF_MD_TEMPLATE _constructor<void * (const list<T >::Iterator&)>();
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::ConstIterator&)>(mopHolder != mopHolder, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >());
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::Iterator&)>(mopHolder != mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<const T & (*)(cpgf::GMetaSelf)>(*mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator (*)(const cpgf::GMetaSelf &, s32)>(mopHolder + mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator& (*)(cpgf::GMetaSelf)>(++mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator (*)(cpgf::GMetaSelf)>(mopHolder++);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator& (*)(cpgf::GMetaSelf, s32)>(mopHolder += mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator (*)(const cpgf::GMetaSelf &, s32)>(mopHolder - mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator& (*)(cpgf::GMetaSelf)>(--mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator (*)(cpgf::GMetaSelf)>(mopHolder--);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator& (*)(const cpgf::GMetaSelf &, s32)>(mopHolder -= mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<const T * (*)(cpgf::GMetaSelf)>(mopHolder -> mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::ConstIterator& (*)(cpgf::GMetaSelf, const list<T >::Iterator&)>(mopHolder = mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::ConstIterator&)>(mopHolder == mopHolder, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >());
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::Iterator&)>(mopHolder == mopHolder);
        _d.CPGF_MD_TEMPLATE _class(_nd);
    }
    {
        GDefineMetaClass<list::Iterator> _nd = GDefineMetaClass<list::Iterator>::declare("Iterator");
        _nd.CPGF_MD_TEMPLATE _constructor<void * ()>();
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::Iterator&)>(mopHolder != mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::ConstIterator&)>(mopHolder != mopHolder, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >());
        _nd.CPGF_MD_TEMPLATE _operator<T & (*)(cpgf::GMetaSelf)>(*mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator (*)(const cpgf::GMetaSelf &, s32)>(mopHolder + mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator& (*)(cpgf::GMetaSelf)>(++mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator (*)(cpgf::GMetaSelf)>(mopHolder++);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator& (*)(cpgf::GMetaSelf, s32)>(mopHolder += mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator (*)(const cpgf::GMetaSelf &, s32)>(mopHolder - mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator& (*)(cpgf::GMetaSelf)>(--mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator (*)(cpgf::GMetaSelf)>(mopHolder--);
        _nd.CPGF_MD_TEMPLATE _operator<list<T >::Iterator& (*)(const cpgf::GMetaSelf &, s32)>(mopHolder -= mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<T * (*)(cpgf::GMetaSelf)>(mopHolder -> mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::Iterator&)>(mopHolder == mopHolder);
        _nd.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const list<T >::ConstIterator&)>(mopHolder == mopHolder, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >());
        _d.CPGF_MD_TEMPLATE _class(_nd);
    }
}


} // namespace meta_irrlicht




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
