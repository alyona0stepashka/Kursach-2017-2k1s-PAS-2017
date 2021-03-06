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

#define LEXEMA_FIXZISE 1				//������������� ������ �������
#define LT_MAXSIZE 4096					//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff		//��� �������� ������� ���������������
#define LEX_DIG			'd'		//	������� ��� �����
#define LEX_STR			's'		//	������� ��� �����
#define LEX_VAR			'v'		//	������� ��� ���������� ���������������
#define LEX_PROCEDURE	'p'		//	������� ��� ���������� ��������
#define LEX_RC			'r'		//	����������� ��������
#define LEX_HEAD		'h'		//	����� �����
#define LEX_WRITE		'w'		//	����� ������
#define LEX_ID			'i'		//	�������������
#define LEX_LITERALSTR	'l'		//	������� ���������
#define LEX_LITERALDIG	'k'		//	������� ��������
#define LEX_SEMICOLON	';'		//	;
#define LEX_COMMA		','		//	,
#define LEX_LEFTBRACE	'{'		//	{
#define LEX_RIGHTBRACE	'}'		//	}
#define LEX_LEFTHESIS	'('		//	(
#define LEX_RIGHTHESIS	')'		//	)
#define LEX_PLUS		'+'		//	+
#define LEX_MINUS		'-'		//	-
#define LEX_STAR		'*'		//	*
#define	LEX_SLASH		'/'		//	/
#define LEX_RAVNO		'='		//=

namespace LT
{							//������� ������
	struct Entry
	{
		char lexema;		//�������
		int sn;				//����� ������ � �������� ����
		int idxTI;			//������ � ������� ��������������� 
	};
	struct LexTable
	{
		int maxize;							//������� ������� ������ 
		int size;							//������� ������ ������� ������
		Entry* table;						//������ ����� ������� ������	
	};
	LexTable Create(						//������� ������
		int size							//�������
	);
	Entry GetEntry(LexTable& lextable, int n);
	Entry Add(								//�������� ������ ������� ������
		LexTable& lextable,					//��������� �������
		Entry entry							//������ ������ ������
	);
	void Delete(LexTable& lextable);		//������� ������� ������
}