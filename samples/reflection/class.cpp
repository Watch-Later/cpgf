#include "reflect_common.h"



namespace {

class TestAbstract
{
public:
	virtual ~TestAbstract() {}
	virtual void abstractFunction() = 0;
};


G_AUTO_RUN_BEFORE_MAIN()
{
	using namespace cpgf;

	GDefineMetaClass<TestAbstract>
		::define("class::TestAbstract")

		._method("abstractFunction", &TestAbstract::abstractFunction)
	;
}


class TestNoDefaultConstructor
{
public:
	TestNoDefaultConstructor(int) {
	}
};


G_AUTO_RUN_BEFORE_MAIN()
{
	using namespace cpgf;

	GDefineMetaClass<TestNoDefaultConstructor>::Policy<GMetaPolicyNoDefaultConstructor>
		::define("class::TestNoDefaultConstructor")
	;
}


class TestNoCopyConstructor
{
public:
	TestNoCopyConstructor() {
	}

private:
	TestNoCopyConstructor(const TestNoCopyConstructor &);
	TestNoCopyConstructor & operator = (const TestNoCopyConstructor &);
};


G_AUTO_RUN_BEFORE_MAIN()
{
	using namespace cpgf;

	GDefineMetaClass<TestNoCopyConstructor>::Policy<cpgf::GMetaPolicyNoCopyConstructor>
		::define("class::TestNoCopyConstructor")
	;
}


class TestNoDefaultAndCopyConstructor
{
public:
	TestNoDefaultAndCopyConstructor(int) {
	}

private:
	TestNoDefaultAndCopyConstructor(const TestNoDefaultAndCopyConstructor &);
	TestNoDefaultAndCopyConstructor & operator = (const TestNoDefaultAndCopyConstructor &);
};


G_AUTO_RUN_BEFORE_MAIN()
{
	using namespace cpgf;

	GDefineMetaClass<TestNoDefaultAndCopyConstructor>::Policy<cpgf::GMetaPolicyNoDefaultAndCopyConstructor>
		::define("class::TestNoDefaultAndCopyConstructor")
	;
}


void doTestLib()
{
	using namespace cpgf;

	std::cout << "Lib: " << "Test Meta Classes" << std::endl;
	
	const GMetaClass * metaClass;
	char buffer[4096];

	metaClass = findMetaClass("class::TestAbstract");
	testCheckAssert(metaClass != nullptr);
	testCheckAssert(metaClass->isAbstract());
	testCheckAssert(! metaClass->canCreateInstance());
	testCheckAssert(! metaClass->canCopyInstance());
	testBeginException;
		metaClass->createInstance();
	testEndException(GException);
	testBeginException;
		metaClass->createInplace(buffer);
	testEndException(GException);

	metaClass = findMetaClass("class::TestNoDefaultConstructor");
	testCheckAssert(metaClass != nullptr);
	testCheckAssert(! metaClass->isAbstract());
	testCheckAssert(! metaClass->canCreateInstance());
	testCheckAssert(metaClass->canCopyInstance());
	testBeginException;
		metaClass->createInstance();
	testEndException(GException);
	testBeginException;
		metaClass->createInplace(buffer);
	testEndException(GException);

	metaClass = findMetaClass("class::TestNoCopyConstructor");
	testCheckAssert(metaClass != nullptr);
	testCheckAssert(! metaClass->isAbstract());
	testCheckAssert(metaClass->canCreateInstance());
	testCheckAssert(! metaClass->canCopyInstance());
	testBeginException;
		metaClass->cloneInstance(nullptr);
	testEndException(GException);
	testBeginException;
		metaClass->cloneInplace(nullptr, buffer);
	testEndException(GException);

	metaClass = findMetaClass("class::TestNoDefaultAndCopyConstructor");
	testCheckAssert(metaClass != nullptr);
	testCheckAssert(! metaClass->isAbstract());
	testCheckAssert(! metaClass->canCreateInstance());
	testCheckAssert(! metaClass->canCopyInstance());
	testBeginException;
		metaClass->cloneInstance(nullptr);
	testEndException(GException);
	testBeginException;
		metaClass->cloneInplace(nullptr, buffer);
	testEndException(GException);

}

void doTestAPI()
{
	using namespace cpgf;

	std::cout << "API: " << "Test Meta Classes" << std::endl;
	
	GScopedInterface<IMetaService> service(createDefaultMetaService());
	testCheckAssert((bool)service);

	GScopedInterface<IMetaClass> metaClass;

	char buffer[4096];

	metaClass.reset(service->findClassByName("class::TestAbstract"));
	testCheckAssert((bool)metaClass);
	testCheckAssert(!! metaClass->isAbstract());
	testCheckAssert(! metaClass->canCreateInstance());
	testCheckAssert(! metaClass->canCopyInstance());
	testBeginException;
		metaClass->createInstance();
		metaCheckError(metaClass.get());
	testEndException(GException);
	testBeginException;
		metaClass->createInplace(buffer);
		metaCheckError(metaClass.get());
	testEndException(GException);

	metaClass.reset(service->findClassByName("class::TestNoDefaultConstructor"));
	testCheckAssert((bool)metaClass);
	testCheckAssert(! metaClass->isAbstract());
	testCheckAssert(! metaClass->canCreateInstance());
	testCheckAssert(!! metaClass->canCopyInstance());
	testBeginException;
		metaClass->createInstance();
		metaCheckError(metaClass.get());
	testEndException(GException);
	testBeginException;
		metaClass->createInplace(buffer);
		metaCheckError(metaClass.get());
	testEndException(GException);

	metaClass.reset(service->findClassByName("class::TestNoCopyConstructor"));
	testCheckAssert((bool)metaClass);
	testCheckAssert(! metaClass->isAbstract());
	testCheckAssert(!! metaClass->canCreateInstance());
	testCheckAssert(! metaClass->canCopyInstance());
	testBeginException;
		metaClass->cloneInstance(nullptr);
		metaCheckError(metaClass.get());
	testEndException(GException);
	testBeginException;
		metaClass->cloneInplace(nullptr, buffer);
		metaCheckError(metaClass.get());
	testEndException(GException);

	metaClass.reset(service->findClassByName("class::TestNoDefaultAndCopyConstructor"));
	testCheckAssert((bool)metaClass);
	testCheckAssert(! metaClass->isAbstract());
	testCheckAssert(! metaClass->canCreateInstance());
	testCheckAssert(! metaClass->canCopyInstance());
	testBeginException;
		metaClass->cloneInstance(nullptr);
		metaCheckError(metaClass.get());
	testEndException(GException);
	testBeginException;
		metaClass->cloneInplace(nullptr, buffer);
		metaCheckError(metaClass.get());
	testEndException(GException);

}


void doTest()
{
	doTestLib();
	doTestAPI();
}


gTestCase(doTest);


}
