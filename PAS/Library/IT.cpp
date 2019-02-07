#include "stdafx.h"
#include <iostream>
#include "IT.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable* p = new IdTable;
		p->maxsize = size;
		p->size = 0;
		p->table = new Entry[size];
		for (int i = 0; i < size; i++)
			memset(p->table[i].value.vstr.str, '\0', size);
		return (*p);
	}
	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.size++] = entry;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		return (idtable.table[n]);

	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}
	int IsDublId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}
	int checkId(IdTable& idtable, char value[ID_MAXSIZE])
	{
		bool rc = false;
		int i;
		for (i = 0; i<idtable.size; i++)
		{
			if (strcmp(idtable.table[i].value.vstr.str, value) == 0)
			{
				rc = true;
				break;
			}
		}
		return rc ? i : TI_NULLIDX;
	}
	int checkId(IdTable& idtable, int value)
	{
		bool rc = false;
		int i;
		for (i = 0; i<idtable.size; i++)
		{
			if (idtable.table[i].value.vint == value)
			{
				rc = true;
				break;
			}
		}
		return rc ? i : TI_NULLIDX;
	}
}