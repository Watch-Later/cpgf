// Auto generated file, don't modify.

#ifndef __META_TEST_METAGEN_TEMPLATE_CLASSES_H
#define __META_TEST_METAGEN_TEMPLATE_CLASSES_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"




namespace meta_test { 


template <typename D>
void buildMetaClass_TemplateBase(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
}


template <typename D, typename T, typename U, typename N>
void buildMetaClass_TemplateClassA(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("a", (void (D::ClassType::*) (template TemplateClassA<T, U, N >::TemplateClassInnerA<T>*))&D::ClassType::a);
    _d.CPGF_MD_TEMPLATE _method("a", (void (D::ClassType::*) (int))&D::ClassType::a);
    _d.CPGF_MD_TEMPLATE _method("b", (void (D::ClassType::*) (typename TemplateClassA<T, U, N >::Shared*))&D::ClassType::b);
    _d.CPGF_MD_TEMPLATE _method("b", (void (D::ClassType::*) (void *))&D::ClassType::b);
    {
        GDefineMetaClass<typename TemplateClassA<T, U, N >::Shared> _nd = GDefineMetaClass<typename TemplateClassA<T, U, N >::Shared>::declare("Shared");
        _d.CPGF_MD_TEMPLATE _class(_nd);
    }
}


template <typename D, typename T>
void buildMetaClass_TemplateClassB(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("b", (void (D::ClassType::*) (typename TemplateClassA<T, U, N >::Shared*))&D::ClassType::b);
    _d.CPGF_MD_TEMPLATE _method("b", (void (D::ClassType::*) (void *))&D::ClassType::b);
    {
        GDefineMetaClass<typename TemplateClassB<T >::Shared> _nd = GDefineMetaClass<typename TemplateClassB<T >::Shared>::declare("Shared");
        _d.CPGF_MD_TEMPLATE _class(_nd);
    }
}


} // namespace meta_test




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif