#pragma once
#include "CodeGeneration.h"
#include "Error.h" 
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
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include<iomanip>
#include <stack>

#define ARR_FST_SIZE 30
namespace FST
{
	struct RELATION			//ребро: символ -> вершина графа перехода КА
	{
		char symbol;		//символ перехода
		short nnode;		//номер смежной вершины
		RELATION(
			char c = 0x00,	//символ перехода
			short ns = NULL //новое состояние
		);
	};

	struct NODE	//вершина графа переходов
	{
		short n_relation;		//количество инцидентных рёбер
		RELATION *relations;	//инцидентные рёбра
		NODE();
		NODE(
			short n,			//количество инцидентных рёбер
			RELATION rel, ...	//список рёбер
		);
	};

	enum LEXAN
	{
		LEXEMS, TYPE, LIT, ID, LIB, HEAD, OPERATOR
	};
	struct FST	//недетерминированный конечный автомат
	{
		char* string;		//цепочка (строка, завершается 0х00)
		char  lex;			//оексема, соответствующая автомату
		short position;		//текущая позиция в цепочке
		short nstates;		//количество состояний автомата
		NODE* nodes;		//граф переходов: [0] -начальное состояние, [nstate-1] -конечное
		short* rstates;		//возможные состояния автомата на данной позиции
		LEXAN lexsw;
		FST(
			char* s,		//цепочка(строка, завершается 0х00)
			char  l,		//оексема, соответствующая автомату
			LEXAN plexsw,
			short ns,		//количество состояний автомата
			NODE  n, ...	//список состояний (граф переходов)
		);
		FST();
	};

	bool execute(		//выполнить распознавание цепочки
		FST& fst		//недетерминированный конечный автомат
	);
	NODE AllSymb();
	FST* ArrFst();		//массив автоматов
}