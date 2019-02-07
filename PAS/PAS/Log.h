#pragma once
#include "stdafx.h"
#include "CodeGeneration.h"
#include "Error.h"
#include "FST.h"
#include "GRB.h"
#include "In.h"
#include "IT.h"
#include "LexicalAnalize.h" 
#include "LT.h"
#include "MFST.h"
#include "Parm.h"
#include "PolishNotation.h"
#include "SemA.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include<iomanip>
#include <stack>

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