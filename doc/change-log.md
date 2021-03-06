<!--notoc-->

# cpgf library changes log

## 2018-09-01 version 1.6.1
  * Improved script engine performance.
  * Refactored script engine.
  * Replaced GScopedPointer and GSharedPointer with std::unique_ptr and std::shared_ptr.
  * Fixed bugs.

## 2017-03-25 version 1.6.0
  * Now the library requires C++11.
  * Rewrote the callback system using C++ variadic template.
  * Rewrote GVariant using C++ variadic template.
  * Optimized script binding performance. Now the performance is a little more than doubled.
  * Added script array support in script binding engine. Now C++ code can access arrays defined in script.
  * Script binding, now script can inherit from C++ class. Available in Lua, V8, and SpiderMonkey.
  * Added script context in script binding.
  * Added customized value converter in script binding.
  * In GMetaType, added function baseIsStdString and baseIsStdWideString to determine if a meta type is std::string or std::wstring.
  * Added VC 2012 and VC 2013 entries in build makefile for easy use.
  * Added source group in CMake build file to filter files better in VC IDE.
  * Optimization in script binding. Now the script objects are reused when possible when passing C++ objects to the script engine. Slightly lower memory and higher performance.
  * Added stack trace message in V8 runner. Now the error line number and stack frames can be printed to the console.
  * Fixed a memory leak in V8 script binding when constructing V8 object from C++.
  * Fixed a bug that the script instance cache may cause crash when the library is shutting down, due to unordered uninitialization.
  * Fixed a bug that script function can't live after its owner script object is freed. Now script function can have its own lifetime.
  * Build config, removed "-D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0" in VC building to avoid linking error with third party libraries.
  * Build config, building with nmake will generate cpgf.lib in folder lib/Debug/ or lib/Release/, instead of lib/

## 2013-07-26 version 1.5.6
  * Added Mozilla SpiderMonkey JavaScript binding. Only tested on Windows with VC.
  * Added GScriptValue to represent values in script binding.
  * Enhanced fundamental type handling in script binding. Now the overloaded function with bool, integer, real (float, double) can be selected correctly.
  * Upgraded thirdparty library jsoncpp to 0.6.0 rc2 from 0.5.0. The new version supports int64. The library is used in the serialization library.
  * Fixed a memory leak in script runner.
  * Fixed a compile error in CMake file when some third party libraries are not available.
  * Fixed a compile error when compiling in VC in Win64 mode.
  * Fixed a compile error when /Zc:wchar_t- is set in VC.
  * Fixed a gcc 4.7.2 warning when deleting object which lacks of virtual destructor.
  * Fixed a compiler error in rapidxml in gcc 4.7.2.
  * Backward incompatible changes:
    * GScriptObject::gainScriptFunction was renamed to getScriptFunction, and the return value was changed to GScriptValue.
    * GScriptObject::createScriptObject result type was changed to GScriptValue, which stores an interface IScriptObject.
    * In GScriptObject, the function bindXXX (such as bindClass) and getXXX (such as getClass) are now deprecated. They will be removed in the future. Use GScriptObject::getValue and GScriptObject::setValue instead.
    * Removed file gfunctionextractor.h and function extractFunction, use gselectfunctionbyarity.h and selectFunctionByArity instead.

## 2013-05-05 version 1.5.5
  * Added tweening and timeline library.
  * Added generic property accessors, getter and setter.
  * Refactored meta property to reuse generic property accessors.
  * Fixed a bug that using function (not pointer) as property accessor may cause wrong address crash in VC.
  * Fixed a bug that using policy GMetaRuleExplicitThis on property setter may cause wrong argument being selected.
  * Fixed a compile error in gstdint.h in VC 2012.

## 2013-02-23 version 1.5.4
  * Improved property supporting in serialization. Now the serialization library can handle properties with getter and setter functions properly.
  * Added including header <cstddef> to gcontainer.h to avoid not finding ptrdiff_t error on some system.

## 2012-12-09 version 1.5.3
  * Python script binding now supports C++ operator overloading.
  * Metagen tool can put template instantiations in separated source file.
  * Now meta data for Irrlicht 3D engine supports Irrlicht 1.8.

## 2012-11-24 version 1.5.2
  * Added meta data for Irrlicht 3D engine. Now we can use Irrlicht in Lua, JavaScript and Python.
  * 18 samples in Irrlicht were converted to Lua, JavaScript and Python.
  * Added function "import" in script binding core service to load libraries at runtime from within script.
  * Added GMetaObjectArray to use C++ object array in script.
  * Added GMetaDebug to ease debugging script. Now script can set break point (int 3) and trace messages.
  * Added GMetaCore to provide core functions in script. cloneClass was moved to GMetaCore. A new function "cast" was added to cast object from script. To use "cast", RTTI must be enabled in the meta data.
  * Improved reflecting for variadic functions, now suppport non-variadic parameters. E.g, int myVariadicFunc(int a, const char * b, GMetaVariadicParam * v);
  * Now dotted nested namespace can be passed to createScriptObject. E.g, createScriptObject("a.b.c"), then script can use the script object a.b.c
  * Added function holdObject to GScriptObject and IScriptObject to hold meta data which is created dynamically.
  * Added meta traits to manage script object lifetime. Now script engine can handle cpgf interfaces correctly.
  * Metagen can reflect bitfield as property by adding getter and setter functions.
  * Metagen can wrap C++ operator overloading with named function, which is usable by script.
  * Metagen can split large source file to smaller files.
  * Now fromVariant<GVariant>(variant) will return the variant directly.
  * Changed the utility functions in gmetaapiutil.h from template to non-template, to keep the API minimal.
  * Moved and renamed gbytearray.h/cpp to metautility/gmetabytearray.h/cpp, and renamed class GByteArray and GMetaByteArray.
  * Renamed byte array functions getMemory/getCurrentMemory to getPointer/getCurrentPointer.
  * Now when passing to method parameter, or setting to field, object pointer can be casted correctly according to the class hierarchy. This is useful in multiple inheritance.
  * Removed function gainScriptObject from GScriptObject and IScriptObject. Now createScriptObject can return the existing script object.
  * Improved meta traits.
  * Now in reflection, the base meta class can be resolved correctly even it is reflected later than derived classes.
  * Now converting an C++ object to GVariant won't trigger any operator & overloading.
  * Fixed a bug that in script, assign an object with another variable with same instance may cause the object be freed.
  * Fixed a bug that in Python binding, None value was not handled when passing from script to C++ and it was converted to wrong GVariant.
  * Fixed a bug that in V8 Javascript binding, there is null pointer crash if the object constructor returns NULL. Now an exception is raised instead of crash.
  * Fixed a bug that function isInheritedFrom in GMetaClass and IMetaClass works wrong.
  * Fixed a bug that if a GVariant holding a reference to fundamental, when casting it to a fundamental in different type size, the result is wrong.
  * Fixed a bug that script binding doesn't distinguish between functions which are only different in constness.

## 2012-10-13 version 1.5.1
  * Support shared pointer in script binding. There are meta traits for shared pointer in C++11, Boost, and cpgf.
  * Removed class GMetaVariant and file gmetavariant.h
  * Added new variant type vtTypedVar to support holding meta type in GVariant.
  * Script object created by createScriptObject in Python binding, now supports attribute access as a.attr instead of a["attr"], to be consistent with other script bindings.
  * Added destroyInplace to meta class to destruct an object but don't free the memory.
  * Fixed a bug that invokeScriptFunction may crash if the calling function or object is freed during the function call.
  * Fixed a bug that GVariant converts shadow object to wrong pointer. (It was assumed to convert to value, now it can be converted to pointer)
  * Fixed a bug that the meta policy transfer object owner ship doesn't work for method parameter in script binding.
  * Removed gbytearrayapi.h, removed IByteArray to minimum the API interface.

## 2012-09-22 version 1.5.0
  * Significantly rewritten the script binding engine. Now the code is much better!
  * Now script can "inherit" from C++ class, in a unified way. Script can call cpgf.cloneClass to do that. See unit tests of metagen.
  * Now script can pass meta class back to C++. In script, func(CppClass), in C++, func(IMetaClass * cppClass).
  * Rename function injectMetaClassToScript to injectObjectToScript which is more appropriate.

## 2012-07-28 version 1.4.5

  * Fixed a bug that in V8 binding, passing existing C++ object to script will cause a new object is created.
  * In script binding, now script function can override C++ virtual member functions.
  * Fixed memory leak in class GMetaVariant.
  * Removed meta name replacer from meta data. 

## 2012-07-07 version 1.4.4

  * Script binding supports wide string (wchar_t *) in method parameters and return value.
  * vtByteArray is removed from GVariant.
  * Now script binding doesn't auto convert IByteArray * to void *, the script should use IByteArray::getMemory to pass the pointer.
  * Lua binding, fixed a bug that no exception was thrown when assigning to enumerator value.
  * Refactored the script binding engines a lot.
  * Added code for tutorials in samples folder. 


## 2012-06-09 version 1.4.3

  * Added Python script binding for Python 2.7.3. (warning -- may memory leak)
  * Function fromVariant -- now integer 0 can be auto casted to NULL pointer.
  * Fixed a bug that the ownerItem in GMetaItem in a dangling define may point to bad pointer. 

## 2012-05-26 version 1.4.2

  * Added object pool to interface based reflection APIs to reduce memory fragment and improve performance.
  * Added Lua 5.2 support in script binding. Now both Lua 5.1 and 5.2 are supported.
  * Fixed a bug in Lua binding that global accessor uses wrong table. 

## 2012-05-19 version 1.4.1

  * Added meta data for SFML library. All meta data is auto generated by the tool metagen.
  * Added sample code to demonstrate using SFML in Lua and V8 Javascript.
  * Rewrote the tool metagen in Java.
  * Enhanced metagen to be able to handle more complicated classes.
  * Added script runner to make executing script easier.
  * Now a normal function can be reflected as meta constructor. Useful to add extra constructors to classes.
  * Split CMakeLists.txt to several single files for better structure.
  * Added separated temporary folders to CMake build for MinGW and VC.
  * Changed build.config.txt do disable all non-core component, such as Lua, V8 binding, by default.
  * Fixed a few compile errors when reflecting certain kind of classes.
  * Fixed a bug that cause crash on bad pointer when reflecting nested classes.
  * Fixed a bug that crashes when base class is not reflected in script binding.
  * Fixed a bug in Lua binding that treated nil as 0, not nil will be converted to (void *)0. 

## 2012-04-22 version 1.4.0

  * Added serialization library.
  * Added meta traits for script binding and serialization.
  * The old meta converter of std::string is refactored to meta traits.
  * Now GVariant supports wide string.
  * Fixed a bug that annotation interface may point to NULL meta annotation.
  * Added sample and unit tests for serialization. 

## 2012-02-26 version 1.3.0

  * Added a tool written in Perl to generate meta data from Doxygen XML files automatically. (Basic features, only tested with Box2D)
  * Added meta data for Box2D physical engine.
  * Added a sample application for Box2D binding.
  * Now the OpenGL metadata can be compiled with GCC.
  * Added the OpenGL sample to cmake build file.
  * Added policy GMetaPolicyDestructorAbsent to allow meta data for class with private destructor.
  * Added class GDefineMetaInfo in gmetadefine.h to ease splitting meta data building to different source files. (Reduce using templates).
  * Added "dangle" and GDefineMetaDangle.
  * Added function getStdTypeInfo to GTypeInfo to get C++ type info.
  * Removed all virtual functions from meta templates to reduce code bloat (the unit test executable size is decreased by 10%).
  * Fixed a bug that _class prototype in GMetaDefine is wrong. 

## 2012-02-05 version 1.2.5

  * Support parameters default value for meta invokable. Method, constructor and object functor operator.
  * Refactored GMetaEnum to remove unnecessary code. 

## 2012-01-28 version 1.2.4

  * Added meta data for OpenGL, GLU, and GLUT.
  * Added binary data support (via IByteArray) in script binding.
  * Added a sample application to show how to use OpenGL in Lua and V8 Javascript.
  * Extended meta enum to accept a GVariant. Now meta enum can be not only integer, but also float, pointer, string, etc. Useful to reflect constants.
  * Fixed a bug in V8 binding that enum value can't be accessed through class. 

## 2012-01-24 version 1.2.3

  * Added script function wrapper. Now script can pass script function to C++ as method parameters.
  * Added script object wrapper. Now script can pass script object to C++ as method parameters.
  * Added meta data for STL iterator, vector, list and deque.
  * V8 binding -- Added object property enumerator. Now using for..in will enumerate all meta data in the object.
  * Added policy GMetaRuleGetterExplicitThis and GMetaRuleSetterExplicitThis for property getter and setter.
  * Added vtInterface in GVariant.
  * Improved code portability, now the library can compile in Intel C++ Compiler Composer XE and Embarcadero C++ Builder 2010.
  * Fixed a bug that in script binding, if a method returns GVariant, the result will be wrongly converted to an object. 

## 2012-01-07 version 1.2.2

  * Added meta policy GMetaRuleExplicitThis.
  * Support binding object functor as meta method.
  * Support C++0x/C++11 rvalue reference in variant, callback and reflection.
  * Support return reference to fundamental from script function. (Pass by value instead of reference)
  * Renamed GDefineMetaClass::inner to GDefineMetaClass::declare.
  * Now the meta class created by GDefineMetaClass::declare can be freed automatically if it's not added to other class.
  * Refactored to make script binding less dependence on static variables.
  * Fixed a bug that can't cast a variant with fundamental to const T &.
  * Fixed a bug that crash when return unbound nested class from member function in V8 binding. 

## 2011-12-18 version 1.2.1

  * Fixed the code compatibility. Now the library can be compiled by GCC 3.4.2. (Tested with MingW GCC).
  * Remove a type casting between void * and function pointer in gcallback. Now the library is more compatible with C++ standard.
  * Added xcode project generating in CMake build. 

## 2011-12-17 version 1.2.0

  * Added new meta data definition syntax. Now no macro is required to build the meta data.
  * Added bindAccessible in script binding.
  * Removed gmetareflect .h and .cpp, which was macro based meta data reflection. 

## 2011-12-10 version 1.1.0

  * Added Google V8 Javascript engine binding.
  * Added non-meta data support in script binding. The script can use arbitrary data type. (void *, T *, while T is not reflected).
  * Added second parameter "void ** outInstance" to function GScriptObject::getMethod
  * Refactored unit tests of script binding.
  * Added unit tests for script binding of Lua and V8.
  * Removed GScriptName and changed all name type to const char *
  * Fixed a memory bug that cause binding engine wrong references to GScriptConfig on the stack.
  * Fixed memory leak in GScopedInterface when call "reset" with same pointer.
  * Fixed a bug that can't access a member object's member in script binding. (a.b.c = 1 will cause a.b be copied, now a.b is referenced) 

## 2011-11-27 version 1.0.1

  * Refactored Lua binding, using better and faster algorithm to travel for data and methods.
  * Distinguish static and member data access in Lua binding.
  * Add: class GMetaClassTraveller in gmetaclasstraveller.h to ease iterating class hierarchy.
  * Add: function gdynamic_cast in gglobal.h for safe and fast dynamic cast.
  * Add: unit tests test_lua_basic.cpp, test_lua_operator.cpp, test_lua_hierarchy.cpp
  * Bug fix: binding Lua operators to wrong meta table.
  * Bug fix: Lua passes two parameters to __unm operator that cpgf doesn't handle correctly.
  * Bug fix: some exceptions raised by interface API were not detected in Lua binding. Now re-throw it to Lua.
  * Memory leak fix: leak when exception is raised during any Lua callback.
  * Remove: function getMethodList and getMethodListInHierarchy from GMetaClass and IMetaClass. They were replaced with better algorithm.
  * Remove: error output to stderr in Lua binding.
  * Add separate license file. 

## 2011-11-05 version 1.0.0

  * First release.
