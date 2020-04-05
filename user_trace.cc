#include "system.h"
#include "prototypes.h"
//
//          User_trace debug code
//
  void user_trace( int type, string function_name, bool debug )
  {
	  if( !debug ) return;
	  if( type == 1 )
		  cout << "...Trace. Entering: "<< function_name << endl;
	  if( type == 2 )
		  cout << "...Trace. Leaving: " << function_name << endl;
	  return;
  }
  