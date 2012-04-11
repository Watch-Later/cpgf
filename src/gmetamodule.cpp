#include "cpgf/gmetamodule.h"
#include "cpgf/gmetaclass.h"
#include "cpgf/gmetaenum.h"
#include "cpgf/gmetafundamental.h"
#include "cpgf/gstringmap.h"


namespace cpgf {

class GMetaTypedItemList
{
public:
	typedef GStringMap<const GMetaTypedItem *, GStringMapReuseKey> MapType;

public:
	GMetaTypedItemList() : freeItems(false) {
	}

	explicit GMetaTypedItemList(bool freeItems) : freeItems(freeItems) {
	}

	~GMetaTypedItemList() {
		if(this->freeItems) {
			for(MapType::const_iterator it = this->itemMap.begin(); it != this->itemMap.end(); ++it) {
				delete it->second;
			}
		}
	}

	void add(const GMetaTypedItem * item) {
		const char * name = item->getTypeName().c_str();
		MapType::const_iterator it = this->itemMap.find(name);
		if(it == this->itemMap.end()) {
			this->itemMap.set(name, item);
		}
	}

	void remove(const GMetaTypedItem * item) {
		this->itemMap.remove(item->getTypeName().c_str());
	}

	const GMetaTypedItem * findByType(const GTypeInfo & type) const {
		for(MapType::const_iterator it = this->itemMap.begin(); it != this->itemMap.end(); ++it) {
			if(it->second->getMetaType().getBaseType() == type) {
				return it->second;
			}
		}

		return NULL;
	}

	const GMetaTypedItem * findByName(const char * name) const {
		if(name == NULL || !*name) {
			return NULL;
		}

		MapType::const_iterator it = this->itemMap.find(name);
		return it == this->itemMap.end() ? NULL : it->second;
	}

	const MapType * getItemMap() const {
		return &this->itemMap;
	}

private:
	MapType itemMap;
	bool freeItems;
};

class GMetaModuleImplement
{
public:
	GScopedPointer<GMetaTypedItemList> classList;
	GScopedPointer<GMetaTypedItemList> enumList;
};

GMetaModule::GMetaModule()
	: implement(new GMetaModuleImplement)
{
}

GMetaModule::~GMetaModule()
{
	this->unregisterAll();
}

void GMetaModule::unregisterAll()
{
	if(this->implement->classList) {
		GScopedPointer<GMetaTypedItemList> tempClassList(this->implement->classList.take());
		for(GMetaTypedItemList::MapType::const_iterator it = tempClassList->getItemMap()->begin(); it != tempClassList->getItemMap()->end(); ++it) {
			this->unregisterMetaClass(static_cast<const GMetaClass *>(it->second));
			static_cast<const GMetaClass *>(it->second)->setModule(NULL);
		}
	}
}

void GMetaModule::registerMetaClass(const GMetaClass * metaClass)
{
	this->doRegisterMetaClass(metaClass);

	size_t count;
	size_t i;

	count = metaClass->getEnumCount();
	for(i = 0; i < count; ++i) {
		doRegisterMetaEnum(metaClass->getEnumAt(i));
	}
}

void GMetaModule::unregisterMetaClass(const GMetaClass * metaClass)
{
	this->doUnregisterMetaClass(metaClass);

	size_t count;
	size_t i;

	count = metaClass->getEnumCount();
	for(i = 0; i < count; ++i) {
		doUnregisterMetaEnum(metaClass->getEnumAt(i));
	}
}

void GMetaModule::doRegisterMetaClass(const GMetaClass * metaClass)
{
	if(metaClass->isGlobal()) {
		return;
	}

	if(! this->implement->classList) {
		this->implement->classList.reset(new GMetaTypedItemList);
	}

	this->implement->classList->add(metaClass);
}

void GMetaModule::doRegisterMetaEnum(const GMetaEnum * metaEnum)
{
	if(! this->implement->enumList) {
		this->implement->enumList.reset(new GMetaTypedItemList);
	}

	this->implement->enumList->add(metaEnum);
}

void GMetaModule::doUnregisterMetaClass(const GMetaClass * metaClass)
{
	if(metaClass->isGlobal()) {
		return;
	}

	if(this->implement->classList) {
		this->implement->classList->remove(metaClass);
	}
}

void GMetaModule::doUnregisterMetaEnum(const GMetaEnum * metaEnum)
{
	if(this->implement->enumList) {
		this->implement->enumList->remove(metaEnum);
	}
}

const GMetaTypedItem * GMetaModule::findItemByType(const GTypeInfo & type) const
{
	const GMetaTypedItem * item = NULL;

	if(this->implement->classList) {
		item = this->implement->classList->findByType(type);
	}

	if(item == NULL && this->implement->enumList) {
		item = this->implement->enumList->findByType(type);
	}

	return item;
}

const GMetaTypedItem * GMetaModule::findItemByName(const char * name) const
{
	const GMetaTypedItem * item = NULL;

	if(this->implement->classList) {
		item = this->implement->classList->findByName(name);
	}

	if(item == NULL && this->implement->enumList) {
		item = this->implement->enumList->findByName(name);
	}

	return item;
}

const GMetaClass * GMetaModule::findClassByType(const GTypeInfo & type) const
{
	if(this->implement->classList) {
		return static_cast<const GMetaClass *>(this->implement->classList->findByType(type));
	}
	else {
		return NULL;
	}
}

const GMetaClass * GMetaModule::findClassByName(const char * name) const
{
	if(this->implement->classList) {
		return static_cast<const GMetaClass *>(this->implement->classList->findByName(name));
	}
	else {
		return NULL;
	}
}



} // namespace cpgf