#include "cpgf/gmetaconverter.h"



namespace cpgf {


bool GMetaConverterStdString::canToCString()
{
	return true;
}

const char * GMetaConverterStdString::toCString(const void * instance, int * needFree)
{
	*needFree = false;
	
	return static_cast<const std::string *>(instance)->c_str();
}


} // namespace cpgf
