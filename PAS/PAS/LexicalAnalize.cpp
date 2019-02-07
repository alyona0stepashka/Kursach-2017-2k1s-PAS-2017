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

#define LA_ERRORS 200

namespace Lex
{
	LT::LexTable lexT = LT::Create(LT_MAXSIZE);
	IT::IdTable  idT = IT::Create(TI_MAXSIZE);

	int SelectFst(char* word)
	{
		FST::FST* ArrOfFst = FST::ArrFst();
		for (int i = 0; i < ARR_FST_SIZE; i++)
		{
			ArrOfFst[i].string = word;
			if (FST::execute(ArrOfFst[i]))
			{
				return i;
			}
		}
		return -1;
	}
	Lex::TABLES Lexic(In::IN in)
	{
		FST::FST* ArrOfFst = FST::ArrFst();
		Error::ARR_OF_ERRORS err;
		TABLES rc;
		int num;
		int z = 0;				//счёьчик
		int type;				//тип данных
		bool proc = false;		//процедура
		bool error = false;
		bool var = false;
		short head = 0;
		int param = 1;			//является ли параметром
		int ravn = 0;
		int lit = 0;
		int ident = 0;
		char pref[6] = "\0";
		char name[ID_MAXSIZE];
		char liter[ID_MAXSIZE] = "literal";
		char* buf;
		while (!in.Words.empty())
		{
			buf = &in.Words.front()[0];
			num = SelectFst(buf);
			if (num == -1)
			{
				err.AddErr(120, in.Line.front(), -1);
				error = true;
			}
			switch (ArrOfFst[num].lexsw)
			{
			case 0:		//lexems
			{
				if (ArrOfFst[num].lex == LEX_RIGHTHESIS)
					param = 1;
				if (ArrOfFst[num].lex == LEX_RIGHTBRACE)
					strcpy(pref, "");
				if (ArrOfFst[num].lex == LEX_RAVNO)
					ravn = 2;
				if (ArrOfFst[num].lex == LEX_VAR)
					var = true;
				if (ArrOfFst[num].lex == LEX_PROCEDURE)
				{
					proc = true;
					param = 3;
				}
				AddLit(ArrOfFst[num].lex, in.Line.front(), -1);
				break;
			}
			case 1:		//type
			{
				if (ArrOfFst[num].lex == LEX_DIG)
					type = 1;
				else
					type = 2;
				AddLit(ArrOfFst[num].lex, in.Line.front(), -1);
				break;
			}
			case 2:		//lit
			{
				char* ind = liter;
				strcat(ind, std::to_string(lit).c_str());
				if (ArrOfFst[num].lex == 'k')
				{
					int val = atoi(buf);
					AddId(ind, lexT.size, 1, 4);
					idT.table[idT.size - 1].value.vint = val;

				}
				if (ArrOfFst[num].lex == 'l')
				{
					strncpy(idT.table[idT.size].value.vstr.str, buf, strlen(buf));
					idT.table[idT.size].value.vstr.len = strlen(buf) - 2;
					AddId(ind, lexT.size, 2, 4);
				}
				lit++;
				ind[7] = '\0';
				AddLit(ArrOfFst[num].lex, in.Line.front(), idT.size - 1);
				break;
			}
			case 3:		//id
			{
				int check = IT::IsDublId(idT, buf);
				strncpy(name, buf, ID_MAXSIZE);
				name[10] = '\0';
				if (proc /*|| idT.table[check].idtype == IT::F*/)//для процедуры
				{
					strncpy(pref, buf, 3);
					pref[3] = '\0';
					strcat(pref, std::to_string(ident).c_str());
					pref[5] = '\0';
					ident++;
					AddId(name, lexT.size, type, 2);
					proc = false;
					//block = true;
				}
				else//для переменной
				{
					if (check == TI_NULLIDX /*|| idT.table[check].idtype != IT::F*/)
					{
						buf[5] = '\0';
						strcpy(name, strcat(buf, pref));
						AddId(name, lexT.size, type, param);
						var = false;
					}
				}
				check = IT::IsId(idT, name);
				if (lexT.table[idT.table[check].idxfirstLE - 1].lexema != 'd' && lexT.table[idT.table[check].idxfirstLE - 1].lexema != LEX_STR)
				{
					err.AddErr(121, in.Line.front(), -1);
					error = true;
				}
				AddLit(ArrOfFst[num].lex, lexT.size, check);
				break;
			}
			case 4:		//lib
			{
				if (ArrOfFst[num].lex == 'a')
					AddId(buf, in.Line.front(), 0, 2);
				if (ArrOfFst[num].lex == 'g')
					AddId(buf, in.Line.front(), 0, 2);
				if (ArrOfFst[num].lex == 'z')
					AddId(buf, in.Line.front(), 0, 2);
				int check = IT::IsId(idT, buf);
				AddLit(ArrOfFst[num].lex, in.Line.front(), check);
				break;
			}
			case 5:		//head
			{
				strncpy(pref, buf, 3);
				pref[3] = '\0';
				AddLit(ArrOfFst[num].lex, in.Line.front(), -1);
				head++;
				break;
			}
			case 6:		//operations
			{
				AddId(buf, in.Line.front(), 3, 5);
				AddLit(ArrOfFst[num].lex, lexT.size, IT::IsId(idT, buf));
				break;
			}
			}
			in.Words.pop();
			in.Line.pop();
			ravn--;
			if (idT.size == TI_MAXSIZE)
				throw ERROR_THROW(122);
			if (lexT.size == LT_MAXSIZE)
				throw ERROR_THROW(123);
		}
		if (head == 0)
			throw ERROR_THROW(124);
		if (head >= 2)
			throw ERROR_THROW(125);
		if (error)
			throw err;

		rc.Id = idT;
		rc.Lex = lexT;
		return rc;
	}
	void AddId(char* name, int str, int type, int idtype)
	{
		if (IT::IsDublId(idT, name) == TI_NULLIDX)
		{
			strcpy(idT.table[idT.size].id, name);
			idT.table[idT.size].idxfirstLE = str;
			//тип данных
			if (type == 1)
				idT.table[idT.size].iddatatype = IT::DIG;
			if (type == 2)
				idT.table[idT.size].iddatatype = IT::STR;
			if (type == 3)
				idT.table[idT.size].iddatatype = IT::OPR;
			//тип ид
			if (idtype == 1)
				idT.table[idT.size].idtype = IT::V;
			if (idtype == 2)
				idT.table[idT.size].idtype = IT::F;
			if (idtype == 3)
				idT.table[idT.size].idtype = IT::P;
			if (idtype == 4)
				idT.table[idT.size].idtype = IT::L;
			if (idtype == 5)
				idT.table[idT.size].idtype = IT::O;
			idT.size++;
		}
	}
	void AddLit(char lex, int str, int id)
	{
		lexT.table[lexT.size].lexema = lex;
		lexT.table[lexT.size].sn = str;
		lexT.table[lexT.size].idxTI = id;
		lexT.size++;
	}
}