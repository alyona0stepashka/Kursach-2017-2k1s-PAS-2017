#pragma once
#define LEXEMA_FIXZISE 1				//фиксированный размер лексемы
#define LT_MAXSIZE 4096					//максимальное кол-во строк в таблице лексем
#define LT_TI_NULLIDX 0xffffffff		//нет элемента таблицы идентификаторов
#define LEX_DIG			'd'		//	лексема дл€ чисел
#define LEX_STR			's'		//	лексема дл€ строк
#define LEX_VAR			'v'		//	лексема дл€ объ€влени€ идентификаторов
#define LEX_PROCEDURE	'p'		//	лексема дл€ объ€влени€ процедур
#define LEX_RC			'r'		//	возвращение значени€
#define LEX_HEAD		'h'		//	точка входа
#define LEX_WRITE		'w'		//	поток вывода
#define LEX_ID			'i'		//	идентификатор
#define LEX_LITERALSTR	'l'		//	литерал строковый
#define LEX_LITERALDIG	'k'		//	литерал знаковый
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
{							//таблица лексем
	struct Entry
	{
		char lexema;		//лексема
		int sn;				//номер строки в исходном коде
		int idxTI;			//индекс в таблице идентификаторов 
	};
	struct LexTable
	{
		int maxize;							//емкость таблицы лексем 
		int size;							//текущий размер таблицы лексем
		Entry* table;						//массив строк табилцы лексем	
	};
	LexTable Create(						//таблица лексем
		int size							//емкость
	);
	Entry GetEntry(LexTable& lextable, int n);
	Entry Add(								//получить строку таблицы лексем
		LexTable& lextable,					//экземпл€р таблицы
		Entry entry							//строка таблцы лексем
	);
	void Delete(LexTable& lextable);		//удалить таблицу лексем
}