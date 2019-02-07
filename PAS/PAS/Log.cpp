#include "stdafx.h"

#include "CodeGeneration.h"
#include "Error.h"
#include "FST.h"
#include "GRB.h"
#include "In.h"
#include "IT.h"
#include "LexicalAnalize.h"
#include "Log.h"
#include "LT.h"
#include "MFST.h"
#include "Parm.h"
#include "PolishNotation.h"
#include "SemA.h"


namespace Log
{
	LOG GetLog(wchar_t logfile[])
	{
		std::ofstream out(logfile);

		LOG *rc = new LOG;
		rc->stream = new std::ofstream(logfile);
		if (rc->stream->fail())
		{
			throw ERROR_THROW(112);
		}
		wcscpy_s(rc->logfile, logfile);
		return *rc;
	}
	void WriteLine(LOG log, char* c, ...)
	{
		char **p = &c;
		while (strcmp(*p, ""))
		{
			*(log.stream) << *p;
			p++;
		}
	}
	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t **p = &c;
		char buf[PARM_MAX_SIZE];
		while (wcscmp(*p, L""))
		{
			wcstombs(buf, *p, PARM_MAX_SIZE);
			*(log.stream) << buf;
			p++;
		}
	}
	void WriteLog(LOG log)
	{
		*(log.stream) << "--- Протокол ----" << std::endl;
		time_t sec;
		char buf[80];
		time(&sec);
		tm *k = localtime(&sec);
		strftime(buf, 80, " %x %X", k);
		*(log.stream) << "Дата: " << buf << std::endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char buf[PARM_MAX_SIZE];
		*(log.stream) << "---- Параметры --------" << std::endl;
		wcstombs(buf, parm.log, PARM_MAX_SIZE);
		*(log.stream) << "-log: " << buf << std::endl;
		wcstombs(buf, parm.out, PARM_MAX_SIZE);
		*(log.stream) << "-out: " << buf << std::endl;
		wcstombs(buf, parm.in, PARM_MAX_SIZE);
		*(log.stream) << "-in: " << buf << std::endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*(log.stream) << "--- Исходные данные ------" << std::endl;
		*(log.stream) << "Количество символов: " << in.size << std::endl;
		*(log.stream) << "Количество строк: " << in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*(log.stream) << "Ошибка " << error.id << ": " << error.message << std::endl;
		*(log.stream) << "строка " << error.inext.line << " позиция " << error.inext.col << std::endl;
	}
	void WriteLexTable(LOG log, LT::LexTable lexT)
	{
		*(log.stream) << "\n\n------------------Таблица лексем--------------------" << std::endl;
		*(log.stream) << "Номер | Лексема | Строка |   Инд в ТИ  \n";
		for (int i = 0; i < lexT.size; i++)
			*(log.stream) << i << "\t   " << lexT.table[i].lexema << "\t     " << lexT.table[i].sn << "  \t" << lexT.table[i].idxTI << std::endl;
	}
	void WriteIdTable(LOG log, IT::IdTable idT)
	{
		*(log.stream) << "\n------------Таблица идентификаторов-------------" << std::endl;

		for (int i = 0; i < idT.size; i++)
		{
			*(log.stream) << "№ " << i << std::endl;
			*(log.stream) << "Имя идентификатора: " << idT.table[i].id << std::endl;
			if (idT.table[i].iddatatype == 1)
				*(log.stream) << "Тип данных : DIG" << std::endl;
			if (idT.table[i].iddatatype == 2)
				*(log.stream) << "Тип данных : STR" << std::endl;
			if (idT.table[i].iddatatype == 3)
				*(log.stream) << "Тип данных : OPR" << std::endl;
			if (idT.table[i].idtype == 1)
				*(log.stream) << "Тип идентификатора: переменная" << std::endl;
			if (idT.table[i].idtype == 2)
				*(log.stream) << "Тип идентификатора: функция" << std::endl;
			if (idT.table[i].idtype == 3)
				*(log.stream) << "Тип идентификатора: параметр" << std::endl;
			if (idT.table[i].idtype == 4)
				*(log.stream) << "Тип идентификатора: литерал" << std::endl;
			if (idT.table[i].idtype == 5)
				*(log.stream) << "Тип идентификатора: оператор" << std::endl;
			*(log.stream) << "Первая строка: " << idT.table[i].idxfirstLE << std::endl;
			if (idT.table[i].idtype != 2)
			{
				if (idT.table[i].iddatatype == IT::DIG)
					*(log.stream) << "Значение: " << idT.table[i].value.vint << std::endl;
				if (idT.table[i].iddatatype == IT::STR)
				{
					*(log.stream) << "Значение: " << idT.table[i].value.vstr.str << std::endl;
					*(log.stream) << "Длина: " << idT.table[i].value.vstr.len << std::endl;
				}
			}
			*(log.stream) << std::endl;
		}
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}