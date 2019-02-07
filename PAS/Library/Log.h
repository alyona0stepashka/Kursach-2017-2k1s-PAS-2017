#pragma once
#include "stdafx.h"
#include <fstream>

#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"

namespace Log		//–абота с протоколом
{
	struct LOG		//протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];		//им€ файла протокола
		std::ofstream * stream;				//выходной поток
	};

	static const LOG INITLOG = { L"", NULL };		//структура дл€ начальной инициализации LOG
	LOG  GetLog(wchar_t logfile[]);					//сформировать структуру LOG
	void WriteLine(LOG log, char* c, ...);			//вывести в протокол конкатенацию строк
	void WriteLine(LOG log, wchar_t* c, ...);		//вывести в протокол конкатенацию строк
	void WriteLog(LOG log);							//вывести в протокол заголовок
	void WriteParm(LOG log, Parm::PARM parm);		//вывести в протокол информацию о входных параметрах
	void WriteIn(LOG log, In::IN in);				//вывести в протокол информацию о входном потоке
	void WriteError(LOG log, Error::ERROR error);	//вывести в прокол информацию об ошибке
	void WriteLexTable(LOG log, LT::LexTable lexT);
	void WriteIdTable(LOG log, IT::IdTable idT);
	void Close(LOG log);							//закрыть протокол
}