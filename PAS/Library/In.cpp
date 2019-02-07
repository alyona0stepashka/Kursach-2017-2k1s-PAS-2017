#pragma once
#include "stdafx.h"
#include "Error.h"
#include "In.h"
#include <fstream>
#include <iostream>


namespace In
{
	IN getin(wchar_t infile[])
	{
		std::ifstream in(infile);
		if (in.fail())
		{
			throw ERROR_THROW(110);
		}
		else
		{
			IN ret;
			Error::ARR_OF_ERRORS err;
			bool error = false;
			ret.size = ret.lines = 0;
			unsigned char symb;
			int isymb;
			int col = 0;
			unsigned char* text;
			text = new unsigned char[IN_MAX_LEN_TEXT];
			while (!in.eof())
			{
				symb = in.get();
				if (in.eof())
					break;
				isymb = (int)symb;
				if (symb == IN_CODE_ENDL)
				{
					text[ret.size] = '|';
					ret.size++;
					ret.lines++;
					col = 0;
				}
				else if (ret.code[isymb] == 1 || ret.code[isymb] == 3)
				{
					text[ret.size] = symb;
					ret.size++;
					col++;
				}
				else if (ret.code[isymb] == 2)
				{
					err.AddErr(111, ret.lines, col);
					error = true;
				}
				if (ret.size == IN_MAX_LEN_TEXT - 1)
					throw ERROR_THROW(112);
			}
			if (error)
				throw err;
			text[ret.size] = 0x00;
			in.close();

			strcat((char*)text, " \0");
			ret.size += 2;

			char buf[IN_WORD_MAX_LEN];
			short wordLen = 0;
			int line = 0;
			for (int i = 0; i < ret.size; i++)	//разбивка на лексемы и запись их в очередь
			{
				buf[wordLen] = text[i];
				wordLen++;
				if (wordLen == IN_WORD_MAX_LEN - 1)
					throw ERROR_THROW_IN(113, line, -1);
				if (text[i] == 39)			//разбор лексемы между ''
				{
					i++;
					while (text[i] != 39)
					{
						buf[wordLen] = text[i];
						i++;
						wordLen++;
						if (wordLen == IN_WORD_MAX_LEN - 2)
							throw ERROR_THROW_IN(114, line, -1);
					}
					buf[wordLen] = 39;
					buf[wordLen + 1] = '\0';
					ret.Words.push(buf);
					ret.Line.push(line);
					wordLen = 0;
				}
				else if (text[i] == IN_CODE_SPACE)	//проверка на пробел
				{
					buf[wordLen - 1] = '\0';
					if (buf[0] != '\0')
					{
						ret.Words.push(buf);
						ret.Line.push(line);
					}
					wordLen = 0;
				}
				else if (ret.code[(int)text[i]] == IN::S)	//проверка на сепаратор
				{
					buf[wordLen - 1] = '\0';
					if (buf[0] != '\0')
					{
						ret.Words.push(buf);
						ret.Line.push(line);
					}
					char tmp[2];
					tmp[0] = text[i]; tmp[1] = '\0';
					ret.Words.push(tmp);
					ret.Line.push(line);
					wordLen = 0;
				}
				else if (text[i] == STR_NUMB_SEP)
				{
					buf[wordLen - 1] = '\0';
					if (buf[0] != '\0')
					{
						ret.Words.push(buf);
						ret.Line.push(line);
					}
					line++;
					wordLen = 0;
				}
			}
			return ret;
		}
	};
};