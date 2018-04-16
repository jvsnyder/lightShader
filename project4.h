#ifndef _PROJECT4_H_
#define _PROJECT4_H_

#include "Matrix4.h"

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

