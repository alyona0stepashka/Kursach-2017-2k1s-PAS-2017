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

#define LEX_NEWPROC '@'

namespace PN
{
	void PolishNotation(LT::LexTable* LexT, IT::IdTable* IdT);
	void Conversation(LT::LexTable* LexT, IT::IdTable* IdT, int position);
	int ArifmPriorities(char symb);
}