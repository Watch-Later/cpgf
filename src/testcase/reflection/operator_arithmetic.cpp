#include "operator_common.h"


namespace {

class TestObject
{
	DEF_TEST_OBJECT(TestObject)

public:
	TestObject operator + (int n) const {
		return TestObject(this->value + n);
	}

	TestObject operator - (int n) const {
		return TestObject(this->value - n);
	}

	TestObject operator * (int n) const {
		return TestObject(this->value * n);
	}

	TestObject operator / (int n) const {
		return TestObject(this->value / n);
	}

	TestObject operator % (int n) const {
		return TestObject(this->value % n);
	}

	TestObject operator % (int n) {
		return TestObject(this->value % (n + 1));
	}

};

int operator + (int n, const TestObject & obj) {
	return n * 2 + obj.value;
}


GMETA_DEFINE_CLASS(TestObject, TestObject, "operator_arithmetic::TestObject") {
	using namespace cpgf;

	reflectOperator<TestObject & (GMetaSelf, const TestObject &)>(mopHolder = mopHolder);

	reflectOperator<TestObject (const GMetaSelf &, int)>(mopHolder + mopHolder);
	reflectOperator<int (int, const TestObject &)>(mopHolder + mopHolder);

	reflectOperator<TestObject (const GMetaSelf &, int)>(mopHolder - mopHolder);

	reflectOperator<TestObject (const GMetaSelf &, int)>(mopHolder * mopHolder);

	reflectOperator<TestObject (const GMetaSelf &, int)>(mopHolder / mopHolder);

	// test operator function constness correct
	reflectOperator<TestObject (const GMetaSelf &, int)>(mopHolder % mopHolder);
	reflectOperator<TestObject (GMetaSelf, int)>(mopHolder % mopHolder);
}

void doTestLib()
{
	using namespace cpgf;

	const GMetaClass * metaClass;
	const GMetaOperator * metaOperator;

	metaClass = findMetaClass("operator_arithmetic::TestObject");
	testCheckAssert(metaClass != NULL);
	std::cout << "Lib: " << metaClass->getName() << std::endl;

	{
		metaOperator = getOperator(mopHolder = mopHolder, metaClass, 0); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		((TestObject *)obj)->value *= 2;
		testCheckAssert(back != *(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, back));
		testCheckAssert(back == *(TestObject *)obj);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder + mopHolder, metaClass, 0); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, 3));
		testCheckEqual(res, back + 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder + mopHolder, metaClass, 1); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		int n = fromVariant<int>(metaOperator->invokeBinary(3, pointerToRefVariant((TestObject *)obj)));
		testCheckEqual(n, 3 + back);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder - mopHolder, metaClass, 0); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, 3));
		testCheckEqual(res, back - 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder * mopHolder, metaClass, 0); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, 3));
		testCheckEqual(res, back * 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder / mopHolder, metaClass, 0); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, 3));
		testCheckEqual(res, back / 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder % mopHolder, metaClass, 0); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		const TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, 3));
		testCheckEqual(res, back % 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator = getOperator(mopHolder % mopHolder, metaClass, 1); testCheckAssert(metaOperator != NULL);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaOperator->invokeBinary(obj, 3));
		testCheckEqual(res, back % 3);
		metaClass->destroyInstance(obj);
	}

}

void doTestAPI()
{
	using namespace cpgf;

	GMetaScopedPointer<IMetaService> service(createMetaService());
	testCheckAssert(service);

	GMetaScopedPointer<IMetaClass> metaClass(service->findClassByName("operator_arithmetic::TestObject"));
	testCheckAssert(metaClass);

	std::cout << "API: " << metaClass->getName() << std::endl;

	GMetaScopedPointer<IMetaOperator> metaOperator;

	{
		metaOperator.reset(getOperator(mopHolder = mopHolder, metaClass, 0)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		((TestObject *)obj)->value *= 2;
		testCheckAssert(back != *(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, back));
		testCheckAssert(back == *(TestObject *)obj);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder + mopHolder, metaClass, 0)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, 3));
		testCheckEqual(res, back + 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder + mopHolder, metaClass, 1)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		int n = fromVariant<int>(metaCallOperatorBinary(metaOperator, 3, pointerToRefVariant((TestObject *)obj)));
		testCheckEqual(n, 3 + back);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder - mopHolder, metaClass, 0)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, 3));
		testCheckEqual(res, back - 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder * mopHolder, metaClass, 0)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, 3));
		testCheckEqual(res, back * 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder / mopHolder, metaClass, 0)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, 3));
		testCheckEqual(res, back / 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder % mopHolder, metaClass, 0)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		const TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, 3));
		testCheckEqual(res, back % 3);
		metaClass->destroyInstance(obj);
	}

	{
		metaOperator.reset(getOperator(mopHolder % mopHolder, metaClass, 1)); testCheckAssert(metaOperator);
		void * obj = metaClass->createInstance();
		TestObject back(*(TestObject *)obj);
		TestObject res = fromVariant<TestObject>(metaCallOperatorBinary(metaOperator, obj, 3));
		testCheckEqual(res, back % 3);
		metaClass->destroyInstance(obj);
	}

}


void doTest()
{
	doTestLib();
	doTestAPI();
}

gTestCase(doTest);


}
