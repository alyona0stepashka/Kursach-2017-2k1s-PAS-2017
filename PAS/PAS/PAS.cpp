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

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::GetLog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

		/////////лексический анализ////////////
		Lex::TABLES tables = Lex::Lexic(in);

		if (parm.lex)
			Log::WriteLexTable(log, tables.Lex);
		if (parm.id)
			Log::WriteIdTable(log, tables.Id);
		/////////синтаксический анализ/////////
		MFST_TRACE_START(log);
		MFST::Mfst mfst(tables, GRB::getGreibach());
		if (!mfst.start(log))
			throw ERROR_THROW(609);
		mfst.savededucation();
		if (parm.tree)
			mfst.printrules(log);

		/////////семантический анализ//////////
		SemAn::SemAnalize sem(tables.Id, tables.Lex);

		/////////польская запись///////////////
		PN::PolishNotation(&tables.Lex, &tables.Id);

		///////////////генерация кода//////////
		CG::Gener(tables.Lex, tables.Id);
		Log::Close(log);
		std::cout << "Выполнено успешно!" << std::endl;
	}
	catch (Error::ERROR e)
	{
		std::cout << "Ошибка " << e.id << ": " << e.message;
		if (e.inext.line != -1)
			std::cout << "; Строка: " << e.inext.line;
		if (e.inext.col != -1)
			std::cout << ", Столбец: " << e.inext.col << std::endl;
		std::cout << std::endl;
		if (e.id != 100)
			Log::WriteError(log, e);
	}
	catch (Error::ARR_OF_ERRORS e)
	{
		for (int i = 0; i < e.size; i++)
		{
			std::cout << "Ошибка " << e.errors[i].id << ": " << e.errors[i].message;
			if (e.errors[i].inext.line != -1)
				std::cout << "; Строка: " << e.errors[i].inext.line;
			if (e.errors[i].inext.col != -1)
				std::cout << ", Столбец: " << e.errors[i].inext.col << std::endl;
			std::cout << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "Ошибка 1 [SYSTEM]: Системный сбой" << std::endl;
	}
	return 0;
}