#pragma once
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
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include<iomanip>
#include <stack>

namespace SemAn
{
	struct SemAnalize
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		Error::ARR_OF_ERRORS err;
		bool error = false;

		SemAnalize(IT::IdTable IdT, LT::LexTable LexT);
		void Init();
		void CheckRc();
		void ParOfProc();
		void ParOfStandProc();
		void NonProc();
		void TypesOfProc();
		void Types();
		void IsProc();
		void ParOfIf();
	};
}