#ifdef DEBUG
	#include <iostream>	
	#define DBG(x) std::cerr << "DBG: " << x << std::endl
	#define DBG_DO(x) x
#else
	#define DBG(x)    //
	#define DBG_DO(x) //
#endif

