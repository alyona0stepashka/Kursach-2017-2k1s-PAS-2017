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

namespace FST
{
	bool step(FST& fst, short* &rstates)	//один шаг автомата
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);	//смена массивов
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
		};
		return rc;
	};
	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short)*fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;				//продвинули позицию
			rc = step(fst, rstates);	//один шаг автомата
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}
	RELATION::RELATION(char c, short nn)
	{
		symbol = c;
		nnode = nn;
	};
	NODE::NODE()	//по умолчанию
	{
		n_relation = 0;
		RELATION *relations = NULL;
	};
	NODE::NODE(short n, RELATION rel, ...)	//с параметрами
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};
	FST::FST(char* s, char l, LEXAN plexsw, short ns, NODE n, ...)
	{
		string = s;
		lex = l;
		nstates = ns;
		lexsw = plexsw;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;
	};
	NODE AllSymb()
	{
		NODE p;
		p.relations = new RELATION[316];
		p.n_relation = 316;
		int k = 0;
		for (int i = 0x20; i < 0x7F; i++)
		{
			if (i == 0x27) continue;

			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 2;
			k++;
			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 1;
			k++;
		};
		for (int i = 0xC0; i <= 0xFF; i++)
		{

			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 2;
			k++;
			p.relations[k].symbol = (char)i;
			p.relations[k].nnode = 1;
			k++;
		};
		p.n_relation = k;
		return p;
	}
	FST::FST()
	{}

	FST* ArrFst()
	{
		FST fstDig("", 'd', TYPE, 6,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('u', 3)),
			NODE(1, RELATION('n', 4)),
			NODE(1, RELATION('t', 5)),
			NODE());
		FST fstStr("", 's', TYPE, 5,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('d', 4)),
			NODE());
		FST fstVar("", 'v', LEXEMS, 5,
			NODE(1, RELATION('o', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('p', 3)),
			NODE(1, RELATION('s', 4)),
			NODE());
		FST fstProcedure("", 'p', LEXEMS, 8,
			NODE(1, RELATION('d', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('s', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('i', 5)),
			NODE(1, RELATION('n', 6)),
			NODE(1, RELATION('y', 7)),
			NODE());
		FST fstRc("", 'r', LEXEMS, 13,
			NODE(1, RELATION('q', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE(1, RELATION('t', 5)),
			NODE(1, RELATION('e', 6)),
			NODE(1, RELATION('s', 7)),
			NODE(1, RELATION('s', 8)),
			NODE(1, RELATION('e', 9)),
			NODE(1, RELATION('n', 10)),
			NODE(1, RELATION('c', 11)),
			NODE(1, RELATION('e', 12)),
			NODE());
		FST fstHead("", 'h', HEAD, 6,
			NODE(1, RELATION('b', 1)),
			NODE(1, RELATION('i', 2)),
			NODE(1, RELATION('r', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('h', 5)),
			NODE());
		FST fstWriteS("", 'y', LIB, 7,
			NODE(1, RELATION('q', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('q', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('s', 6)),
			NODE());
		FST fstWriteD("", 'x', LIB, 7,
			NODE(1, RELATION('q', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('q', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('d', 6)),
			NODE());
		FST fstRadical("", 'a', LIB, 8,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('d', 3)),
			NODE(1, RELATION('i', 4)),
			NODE(1, RELATION('c', 5)),
			NODE(1, RELATION('a', 6)),
			NODE(1, RELATION('l', 7)),
			NODE());
		FST fstDegree("", 'g', LIB, 7,
			NODE(1, RELATION('d', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('g', 3)),
			NODE(1, RELATION('r', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('e', 6)),
			NODE());
		FST fstStrLen("", 'z', LIB, 5,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('r', 3)),
			NODE(1, RELATION('l', 4)),
			NODE());
		FST fstIf("", 'c', LEXEMS, 3,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('f', 2)),
			NODE());
		FST fstElse("", 'e', LEXEMS, 5,
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('l', 2)),
			NODE(1, RELATION('s', 3)),
			NODE(1, RELATION('e', 4)),
			NODE());
		FST fstDigLit("", 'k', LIT, 2,
			NODE(20, RELATION('0', 0), RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0),
				RELATION('5', 0), RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0),
				RELATION('0', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),
				RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1)),
			NODE());
		FST fstStrLit("", 'l', LIT, 4,
			NODE(1, RELATION((char)0x27, 1)),
			AllSymb(),
			NODE(1, RELATION((char)0x27, 3)),
			NODE());
		FST fstId("", 'i', ID, 2,
			NODE(52, RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0),
				RELATION('f', 0), RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0),
				RELATION('k', 0), RELATION('l', 0), RELATION('m', 0), RELATION('n', 0), RELATION('o', 0),
				RELATION('p', 0), RELATION('q', 0), RELATION('r', 0), RELATION('s', 0), RELATION('t', 0),
				RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0), RELATION('y', 0),
				RELATION('z', 0),
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1),
				RELATION('f', 1), RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1),
				RELATION('k', 1), RELATION('l', 1), RELATION('m', 1), RELATION('n', 1), RELATION('o', 1),
				RELATION('p', 1), RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),
				RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1), RELATION('y', 1),
				RELATION('z', 1)),
			NODE());
		FST fstPlus("", '+', OPERATOR, 2,
			NODE(1, RELATION('+', 1)),
			NODE());
		FST fstMinus("", '-', OPERATOR, 2,
			NODE(1, RELATION('-', 1)),
			NODE());
		FST fstStar("", '*', OPERATOR, 2,
			NODE(1, RELATION('*', 1)),
			NODE());
		FST fstLeftIf("", '[', LEXEMS, 2,
			NODE(1, RELATION('[', 1)),
			NODE());
		FST fstRighIf("", ']', LEXEMS, 2,
			NODE(1, RELATION(']', 1)),
			NODE());
		FST fstLeftBr("", '(', LEXEMS, 2,
			NODE(1, RELATION('(', 1)),
			NODE());
		FST fstRighBr("", ')', LEXEMS, 2,
			NODE(1, RELATION(')', 1)),
			NODE());
		FST fstLeftBlock("", '{', LEXEMS, 2,
			NODE(1, RELATION('{', 1)),
			NODE());
		FST fstRighBlock("", '}', LEXEMS, 2,
			NODE(1, RELATION('}', 1)),
			NODE());
		FST fstSemicolon("", ';', LEXEMS, 2,
			NODE(1, RELATION(';', 1)),
			NODE());
		FST fstDot("", '.', LEXEMS, 2,
			NODE(1, RELATION('.', 1)),
			NODE());
		FST fstComma("", ',', LEXEMS, 2,
			NODE(1, RELATION(',', 1)),
			NODE());
		FST fstRavno("", '=', LEXEMS, 2,
			NODE(1, RELATION('=', 1)),
			NODE());
		FST fstLess("", '<', LEXEMS, 2,
			NODE(1, RELATION('<', 1)),
			NODE());
		FST* rc = new FST[ARR_FST_SIZE];
		rc[0] = fstProcedure;		//
		rc[1] = fstHead;			//
		rc[2] = fstDigLit;			//
		rc[3] = fstDot;				//
		rc[4] = fstComma;			//
		rc[5] = fstVar;				//
		rc[6] = fstDig;				//	
		rc[7] = fstStr;				//
		rc[8] = fstLeftBr;			//
		rc[9] = fstLeftBlock;		//
		rc[10] = fstLeftIf;
		rc[11] = fstRc;				//
		rc[12] = fstWriteS;			//
		rc[13] = fstWriteD;
		rc[14] = fstRadical;
		rc[15] = fstDegree;
		rc[16] = fstStrLen;
		rc[17] = fstIf;
		rc[18] = fstElse;
		rc[19] = fstPlus;
		rc[20] = fstMinus;
		rc[21] = fstStar;
		rc[22] = fstLess;
		rc[23] = fstRavno;			//
		rc[24] = fstRighBr;			//
		rc[25] = fstRighBlock;		//
		rc[26] = fstRighIf;
		rc[27] = fstSemicolon;		//
		rc[28] = fstId;				//
		rc[29] = fstStrLit;			//
		return rc;
	}
}