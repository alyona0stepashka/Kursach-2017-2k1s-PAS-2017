#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		bool fl = false, fl_out = false, fl_log = false;
		PARM rc;
		wchar_t *buf;
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			if (wcsstr(argv[i], PARM_IN))
			{
				wcscpy_s(rc.in, &argv[i][4]);
				fl = true;
			}
			if (wcsstr(argv[i], PARM_OUT))
			{
				wcscpy_s(rc.out, &argv[i][5]);
				fl_out = true;
			}
			if (wcsstr(argv[i], PARM_LOG))
			{
				wcscpy_s(rc.log, &argv[i][5]);
				fl_log = true;
			}
			if (wcsstr(argv[i], PARM_lex))
				rc.lex = true;
			if (wcsstr(argv[i], PARM_ID))
				rc.id = true;
			if (wcsstr(argv[i], PARM_TREE))
				rc.tree = true;
		}
		if (!fl)
			throw ERROR_THROW(100);
		if (!fl_out)
		{
			wcscpy_s(rc.out, rc.in);
			wcsncat_s(rc.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
		}
		if (!fl_log)
		{
			wcscpy_s(rc.log, rc.in);
			wcsncat_s(rc.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		return rc;
	}
}