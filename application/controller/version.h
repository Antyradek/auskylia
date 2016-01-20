#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "20";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 78;
	static const long REVISION  = 418;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 138;
	#define RC_FILEVERSION 1,0,78,418
	#define RC_FILEVERSION_STRING "1, 0, 78, 418\0"
	static const char FULLVERSION_STRING [] = "1.0.78.418";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 78;
	

}
#endif //VERSION_H
