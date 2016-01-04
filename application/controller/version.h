#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "04";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 45;
	static const long REVISION  = 249;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 74;
	#define RC_FILEVERSION 1,0,45,249
	#define RC_FILEVERSION_STRING "1, 0, 45, 249\0"
	static const char FULLVERSION_STRING [] = "1.0.45.249";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 45;
	

}
#endif //VERSION_H
