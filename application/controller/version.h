#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "03";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 44;
	static const long REVISION  = 243;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 73;
	#define RC_FILEVERSION 1,0,44,243
	#define RC_FILEVERSION_STRING "1, 0, 44, 243\0"
	static const char FULLVERSION_STRING [] = "1.0.44.243";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 44;
	

}
#endif //VERSION_H
