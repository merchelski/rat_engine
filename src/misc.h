#ifndef MISC_H
#define MISC_H

#include <stdlib.h>

// comment out DEBUG definition to turn off ASSERT
#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed ",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

enum enum_bool
{
	FALSE, TRUE
};

#endif
