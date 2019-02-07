#include "stdafx.h"
#include <iostream>

extern "C"
{
	int __stdcall ququed(unsigned  int num)
	{
		std::cout << num << std::endl;
		return 0;
	}
	int __stdcall quques(char* str)
	{
		std::cout << str << std::endl;
		return 0;
	}

	int __stdcall isqr(unsigned  int b, unsigned   int a)
	{
		int rc;
		rc = pow(a, b);
		return rc;
	}
	int __stdcall isqrt(unsigned  int b, unsigned   int a)
	{
		int rc;
		rc = pow(a, (1 / (double)b));
		return rc;
	}
	/*int __stdcall sum(unsigned  int b, unsigned   int a)
	{
		int rc;
		rc = a+b;
		return rc;
	}
	int __stdcall diff(unsigned  int b, unsigned   int a)
	{
		int rc;
		rc = a-b;
		return rc;
	}
	int __stdcall less(unsigned  int b, unsigned   int a)
	{
		int rc;
		if (b < a) rc = -1;
		else if (b == a) rc = 0;
		else rc = 1;
		return rc;
	}*/
	int __stdcall strl(char* c)
	{
		return strlen(c);
	}
}
//includelib ../Debug/LP_asm01d.lib