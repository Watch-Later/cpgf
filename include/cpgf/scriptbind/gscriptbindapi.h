#ifndef __GSCRIPTBINDAPI_H
#define __GSCRIPTBINDAPI_H

#include "cpgf/gmetaapi.h"
#include "cpgf/gmetavariant.h"


namespace cpgf {


struct IScriptConfig : public IBaseObject
{
	virtual void G_API_CC setAccessStaticMethodViaInstance(gapi_bool set) = 0;
	virtual gapi_bool G_API_CC allowAccessStaticMethodViaInstance() = 0;

	virtual void G_API_CC setAccessEnumTypeViaInstance(gapi_bool set) = 0;
	virtual gapi_bool G_API_CC allowAccessEnumTypeViaInstance() = 0;

	virtual void G_API_CC setAccessEnumValueViaInstance(gapi_bool set) = 0;
	virtual gapi_bool G_API_CC allowAccessEnumValueViaInstance() = 0;

	virtual void G_API_CC setAccessClassViaInstance(gapi_bool set) = 0;
	virtual gapi_bool G_API_CC allowAccessClassViaInstance() = 0;
};


struct IScriptName : public IBaseObject
{
	virtual const char * G_API_CC getName() = 0;
};


struct IScriptObject : public IBaseObject
{
	virtual IScriptConfig * G_API_CC getConfig() = 0;
	virtual IScriptObject * G_API_CC getOwner() = 0;
	virtual gapi_bool G_API_CC isGlobal() = 0;

	virtual IScriptName * G_API_CC createName(const char * name) = 0;
	virtual gapi_bool G_API_CC cacheName(IScriptName * name) = 0;

	virtual uint32_t G_API_CC getType(IScriptName * name) = 0;

	virtual void G_API_CC bindClass(IScriptName * name, IMetaClass * metaClass) = 0;
	virtual void G_API_CC bindEnum(IScriptName * name, IMetaEnum * metaEnum) = 0;

	virtual IScriptObject * G_API_CC createScriptObject(IScriptName * name) = 0;
	
	virtual void G_API_CC invoke(IScriptName * name, GMetaVarData * outResult, const GMetaVarData * params, uint32_t paramCount) = 0;
	virtual void G_API_CC invokeIndirectly(IScriptName * name, GMetaVarData * outResult, GMetaVarData const * const * params, uint32_t paramCount) = 0;

	virtual void G_API_CC setFundamental(IScriptName * name, const GVariantData * value) = 0;
	virtual void G_API_CC setString(IScriptName * stringName, const char * s) = 0;
	virtual void G_API_CC setObject(IScriptName * objectName, void * instance, IMetaClass * type, gapi_bool transferOwnership) = 0;
	virtual void G_API_CC setMethod(IScriptName * name, void * instance, IMetaMethod * method) = 0;
	
	virtual void G_API_CC getFundamental(IScriptName * name, GVariantData * outResult) = 0;
	virtual char * G_API_CC getString(IScriptName * stringName) = 0;
	
	virtual void * G_API_CC getObject(IScriptName * objectName) = 0;
	virtual IMetaClass * G_API_CC getObjectType(IScriptName * objectName) = 0;
	virtual IMetaClass * G_API_CC getClass(IScriptName * className) = 0;
	
	virtual IMetaMethod * G_API_CC getMethod(IScriptName * methodName) = 0;
	virtual IMetaEnum * G_API_CC getEnum(IScriptName * enumName) = 0;
	
	virtual void G_API_CC assignValue(IScriptName * fromName, IScriptName * toName) = 0;
	virtual gapi_bool G_API_CC valueIsNull(IScriptName * name) = 0;
	virtual void G_API_CC nullifyValue(IScriptName * name) = 0;

};



} // namespace cpgf





#endif
