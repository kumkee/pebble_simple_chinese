#include "lylunar.h"
#include "utils.h"

bool rm_leading_0(char* str)
{
   if(str[0] == '0')
   {
	memmove(str, &str[1], strlen(str));
	return true;
   }
   else
	return false;
}


bool rp_leading_0(char* str)
{
   if(str[0] == '0')
   {
	str[0] = ' ';
	return true;
   }
   else
	return false;
}


