#pragma once
#include "stdafx.h"
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

namespace CG
{
	struct Gener
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		std::ofstream out;

		Gener(LT::LexTable lexT, IT::IdTable IdT);

		void Head();
		void Constants();
		void Data();
		void Code();
	};
}