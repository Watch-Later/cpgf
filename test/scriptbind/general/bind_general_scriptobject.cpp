#include "../testscriptbind.h"
#include "../testscriptbindmetadata2.h"


namespace {

void testCreateScriptObject(TestScriptContext * context)
{
	QVARNEWOBJ(existObj, TestObject());

	GScriptObject * bindingLib = context->getBindingLib();
	IScriptObject * bindingApi = context->getBindingApi();

	if(bindingLib != nullptr) {
		GScopedInterface<IScriptObject> existScriptObject(bindingLib->createScriptObject("existObj").toScriptObject());
		GCHECK(! existScriptObject);
		
		GCHECK(bindingLib->getValue("nso").isNull());
		GScopedInterface<IScriptObject> firstScriptObject(bindingLib->createScriptObject("nso").toScriptObject());
		GVariant v = 38;
		scriptSetValue(firstScriptObject.get(), "ix", GScriptValue::fromPrimary(v));
		
		GCHECK(bindingLib->getValue("sec.third.fourth").isNull());
		GScopedInterface<IScriptObject> secondScriptObject(bindingLib->createScriptObject("sec.third.fourth").toScriptObject());
		v = 6;
		scriptSetValue(secondScriptObject.get(), "iy", GScriptValue::fromPrimary(v));
	}
	if(bindingApi != nullptr) {
		GScopedInterface<IScriptObject> existScriptObject(scriptCreateScriptObject(bindingApi, "existObj").toScriptObject());
		GCHECK(! existScriptObject);
		
		GCHECK(scriptGetValue(bindingApi, "nso").isNull());
		GScopedInterface<IScriptObject> newScriptObject(scriptCreateScriptObject(bindingApi, "nso").toScriptObject());
		GVariant v = 38;
		scriptSetValue(newScriptObject.get(), "ix", GScriptValue::fromPrimary(v));

		GCHECK(scriptGetValue(bindingApi, "sec.third.fourth").isNull());
		GScopedInterface<IScriptObject> secondScriptObject(scriptCreateScriptObject(bindingApi, "sec.third.fourth").toScriptObject());
		v = 6;
		scriptSetValue(secondScriptObject.get(), "iy", GScriptValue::fromPrimary(v));
	}

	QASSERT(nso.ix == 38);
	QASSERT(sec.third.fourth.iy == 6);

	if(bindingLib != nullptr) {
		GScopedInterface<IScriptObject> firstScriptObject(bindingLib->createScriptObject("nso").toScriptObject());
		GCHECK(fromVariant<int>(scriptGetValue(firstScriptObject.get(), "ix").toPrimary()) == 38);
		
		GScopedInterface<IScriptObject> secondScriptObject(bindingLib->createScriptObject("sec.third.fourth").toScriptObject());
		GCHECK(fromVariant<int>(scriptGetValue(secondScriptObject.get(), "iy").toPrimary()) == 6);
	}
	if(bindingApi != nullptr) {
		GVariant v;
		GScopedInterface<IScriptObject> newScriptObject(scriptCreateScriptObject(bindingApi, "nso").toScriptObject());
		v = scriptGetValue(newScriptObject.get(), "ix").toPrimary();
		GCHECK(fromVariant<int>(v) == 38);

		GScopedInterface<IScriptObject> secondScriptObject(scriptCreateScriptObject(bindingApi, "sec.third.fourth").toScriptObject());
		v = 0;
		v = scriptGetValue(secondScriptObject.get(), "iy").toPrimary();
		GCHECK(fromVariant<int>(v) == 6);
	}
}

#define CASE testCreateScriptObject
#include "../bind_testcase.h"


void testGetScriptObject(TestScriptContext * context)
{
	QVARNEWOBJ(existObj, TestObject());

	QVAR(scope = {});
	if(context->isLua()) {
		QDO(scope.obj = TestObject(6));
		QDO(scope.i = 5);
	}
	if(context->isV8() || context->isSpiderMonkey()) {
		QDO(scope.obj = new TestObject(6));
		QDO(scope.i = 5);
	}
	if(context->isPython()) {
		QDO(scope['obj'] = TestObject(6));
		QDO(scope['i'] = 5);
	}

	GScriptObject * bindingLib = context->getBindingLib();
	IScriptObject * bindingApi = context->getBindingApi();
	
	GVariant v;
	void * instance = nullptr;

	if(bindingLib != nullptr) {
		GScopedInterface<IScriptObject> existScriptObject(bindingLib->createScriptObject("existObj").toScriptObject());
//		GCHECK(! existScriptObject);

		GScopedInterface<IScriptObject> newScriptObject(bindingLib->createScriptObject("scope").toScriptObject());
		v = GVariant();
		v = scriptGetValue(newScriptObject.get(), "i").toPrimary();
		GCHECK(fromVariant<int>(v) == 5);
		instance = scriptGetValue(newScriptObject.get(), "obj").toObjectAddress(nullptr, nullptr, nullptr);
	}
	if(bindingApi != nullptr) {
		GScopedInterface<IScriptObject> existScriptObject(scriptCreateScriptObject(bindingApi, "existObj").toScriptObject());
//		GCHECK(! existScriptObject);

		GScopedInterface<IScriptObject> newScriptObject(scriptCreateScriptObject(bindingApi, "scope").toScriptObject());
		v = scriptGetValue(newScriptObject.get(), "i").toPrimary();
		GCHECK(fromVariant<int>(v) == 5);
		instance = scriptGetValue(newScriptObject.get(), "obj").toObjectAddress(nullptr, nullptr, nullptr);
	}
	
	GCHECK(instance != nullptr);
	if(instance)
	GCHECK(static_cast<TestObject *>(instance)->value == 6);
}

#define CASE testGetScriptObject
#include "../bind_testcase.h"


}
