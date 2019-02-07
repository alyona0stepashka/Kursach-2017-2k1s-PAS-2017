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

namespace PN
{
	void PolishNotation(LT::LexTable* LexT, IT::IdTable* IdT)
	{
		for (int i = 0; i < LexT->size; i++)
		{
			if (LexT->table[i].lexema == LEX_RAVNO)
			{
				Conversation(LexT, IdT, ++i);
			}
		}
	}
	void Conversation(LT::LexTable* lextable, IT::IdTable* idtable, int lextable_pos)
	{
		std::stack<LT::Entry> st;
		LT::Entry outstr[200];
		int len = 0,							//общая длина
			lenout = 0,							//длина выходной строки
			semicolonid;						//ид для элемента таблицы с точкой с запятой
		char t, oper, hesis = 0;				//текущий символ/знак оператора/кол-во скобок
		int indoffunk;							//индекс для замены на элемент с функцией
		for (int i = lextable_pos; lextable->table[i].lexema != LEX_SEMICOLON; i++)
		{
			len = i;
			semicolonid = i + 1;
		}
		len++;
		for (int i = lextable_pos; i < len; i++)
		{
			t = lextable->table[i].lexema;
			if (lextable->table[i].lexema == LEX_PLUS || lextable->table[i].lexema == LEX_MINUS ||
				lextable->table[i].lexema == LEX_STAR)
				oper = idtable->table[lextable->table[i].idxTI].id[0];
			if (t == LEX_RIGHTHESIS)						//выталкивание всего до другой левой скобки
			{
				while (st.top().lexema != LEX_LEFTHESIS)
				{
					outstr[lenout++] = st.top();			//записываем в выходную строку очередной символ между скобками
					hesis++;
					st.pop();								//удаляем вершину стека
				}
				st.pop();									//удаляем левую скобку в стеке
			}
			if (t == LEX_ID || t == LEX_LITERALSTR || t == LEX_LITERALDIG ||
				t == 'z' || t == 'g' || t == 'a')
			{
				if (lextable->table[i + 1].lexema == LEX_LEFTHESIS)
				{
					indoffunk = i;
					i += 2;
					while (lextable->table[i].lexema != LEX_RIGHTHESIS)
					{								//пока внутри аргументов функции, переписываем их в строку
						if (lextable->table[i].lexema != LEX_COMMA)
						{
							outstr[lenout++] = lextable->table[i++];
						}
						else
						{
							hesis++;
							i++;
						}
					}
					outstr[lenout++] = lextable->table[indoffunk];
					outstr[lenout - 1].lexema = LEX_NEWPROC;
					hesis += 2;
				}
				else
					outstr[lenout++] = lextable->table[i];
			}
			if (t == LEX_LEFTHESIS)
			{
				st.push(lextable->table[i]);							//помещаем в стек левую скобку
				hesis++;
			}

			if (oper == '+' || oper == '-' || oper == '*')
			{
				if (!st.size())
					st.push(lextable->table[i]);
				else {
					int pr, id;
					if (st.top().lexema == '(' || st.top().lexema == ')')
						pr = 1;
					else {
						id = st.top().idxTI;
						pr = ArifmPriorities(idtable->table[id].id[0]);
					}
					if (ArifmPriorities(oper) > pr)																		//если приоритет добавляемой операции больше операции на вершине стека
						st.push(lextable->table[i]);																		//добавляем операции в стек
					else
					{
						while (st.size() && ArifmPriorities(oper) <= ArifmPriorities(idtable->table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable->table[i]);
					}
				}
			}
			oper = NULL;				//обнуляем поле знака
		}
		while (st.size())
		{
			outstr[lenout++] = st.top();												//вывод в строку всех знаков из стека
			st.pop();
		}
		for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++, k++)
		{
			lextable->table[i] = outstr[k];												//запись в таблицу польской записи
		}
		lextable->table[lextable_pos + lenout] = lextable->table[semicolonid];			//вставка элемента с точкой с запятой
		for (int i = 0; i < hesis; i++)
		{
			for (int j = lextable_pos + lenout + 1; j < lextable->size; j++)				//сдвигаем на лишнее место
			{
				lextable->table[j] = lextable->table[j + 1];
			}
			lextable->size--;
		}
	}
	int ArifmPriorities(char symb)
	{
		if (symb == LEX_LEFTHESIS || symb == LEX_RIGHTHESIS)
			return 1;
		if (symb == LEX_PLUS || symb == LEX_MINUS)
			return 2;
		if (symb == LEX_STAR)
			return 3;
	}
}