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
namespace CG
{

	Gener::Gener(LT::LexTable plexT, IT::IdTable pidT)
	{
		idT = pidT;
		lexT = plexT;
		out = std::ofstream("../../PASasm/PASasm/PASasm.asm");
		Head();
		Constants();
		Data();
		Code();
	}
	void Gener::Head()
	{
		out << ".586\n";
		out << "\t.model flat, stdcall\n";
		out << "\tincludelib libucrt.lib\n";
		out << "\tincludelib libucrt.lib\n";
		out << "\tincludelib kernel32.lib\n";
		out << "\tExitProcess PROTO :DWORD\n\n";
		out << "\tincludelib ../Debug/KDVlib.lib\n";
		out << "\twrites PROTO :DWORD\n";
		out << "\twrited PROTO :DWORD\n";
		out << "\tstrl PROTO :DWORD\n";
		out << "\tdegree PROTO :DWORD, :DWORD\n";
		out << "\tradical PROTO :DWORD, :DWORD\n";
		out << "\n.stack 4096\n";
	}
	void Gener::Constants()
	{
		out << ".const\n";
		for (int i = 0; i < idT.size; i++)
		{
			if (idT.table[i].idtype == 4)
			{
				out << "\t" << idT.table[i].id;
				if (idT.table[i].iddatatype == 2)
					out << " BYTE " << idT.table[i].value.vstr.str << ", 0";
				if (idT.table[i].iddatatype == 1)
					out << " DWORD " << idT.table[i].value.vint;
				out << '\n';
			}
		}
	}
	void Gener::Data()
	{
		out << ".data\n";
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'v')
			{
				if (idT.table[lexT.table[i + 2].idxTI].idtype == 1)
				{
					out << "\t" << idT.table[lexT.table[i + 2].idxTI].id;
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == 2)
						out << " DWORD ?";
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == 1)
						out << " DWORD ?";
					out << '\n';
				}
				for (int j = i; j < lexT.size; j++)
					lexT.table[j] = lexT.table[j + 4];
				lexT.size -= 4;
				i--;
			}
		}
	}
	void Gener::Code()
	{
		out << "\n.code\n";
		int indOfProc = 0;
		int indOflex = -1;
		int rhesis = -1;
		bool rif = false;
		bool proc = false;
		bool head = false;
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'p')
			{
				indOfProc = i + 2;
				out << idT.table[lexT.table[indOfProc].idxTI].id << " PROC ";
				proc = true;
				while (lexT.table[i].lexema != ')')
				{
					rhesis = i;
					i++;
				}
				while (lexT.table[i].lexema != '(')
				{
					if (lexT.table[i].lexema == 'i')
					{
						if (idT.table[lexT.table[i].idxTI].iddatatype == 1)
						{
							out << idT.table[lexT.table[i].idxTI].id << ":DWORD";
							if (lexT.table[i - 2].lexema != '(')
								out << ", ";
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == 2)
						{
							out << idT.table[lexT.table[i].idxTI].id << ":DWORD";
							if (lexT.table[i - 2].lexema != '(')
								out << ", ";
						}
					}
					i--;
				}
				i = rhesis;
				out << std::endl;
			}
			if (lexT.table[i].lexema == 'h')
			{
				head = true;
				out << "main PROC\n";
			}
			if (lexT.table[i].lexema == '}')
			{
				if (proc)
				{
					out << idT.table[lexT.table[indOfProc].idxTI].id << " ENDP\n\n";
					proc = false;
				}
				else
					out << "call ExitProcess\nmain ENDP\n";
				indOfProc = 0;
			}
			if (lexT.table[i].lexema == 'r')
			{
				if (head)
					out << "push 0\n";
				else
				{
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == 1)
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == 2)
						out << "\tmov eax, offset " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
				}
			}
			if (lexT.table[i].lexema == 'y')
			{
				if (lexT.table[i + 2].lexema == 'i')
					out << "\tpush " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				else
					out << "\tpush offset " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "\tcall writes\n";
			}
			if (lexT.table[i].lexema == 'x')
			{
				out << "\tpush " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "\tcall writed\n";
			}
			if (lexT.table[i].lexema == 'c')
			{
				out << "mov eax, " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "cmp eax, " << idT.table[lexT.table[i + 4].idxTI].id << "\n";
				out << "jb less" << std::endl << "ja more\n";
				out << "less:\n";
			}
			if (lexT.table[i].lexema == ']')
			{
				if (!rif)
				{
					out << "jmp flag\n";
					out << "more:\n";
					rif = true;
				}
				else
				{
					out << "flag:\n";
					rif = false;
				}

			}
			if (lexT.table[i].lexema == '=')
			{
				indOflex = i - 1;
				while (lexT.table[i].lexema != ';')
				{
					if (lexT.table[i].lexema == 'i')
					{
						out << "push " << idT.table[lexT.table[i].idxTI].id << "\n";
					}
					if (lexT.table[i].lexema == 'k')
						out << "push " << idT.table[lexT.table[i].idxTI].id << "\n";
					if (lexT.table[i].lexema == 'l')
						out << "push offset " << idT.table[lexT.table[i].idxTI].id << "\n";
					if (lexT.table[i].lexema == '@')
					{
						out << "call " << idT.table[lexT.table[i].idxTI].id << "\n";
						out << "push eax\n";
					}
					if (lexT.table[i].lexema == '+')
					{
						out << "pop eax\n";
						out << "pop ebx\n";
						out << "add eax, ebx\n";
						out << "push eax\n";
					}
					if (lexT.table[i].lexema == '-')
					{
						out << "pop ebx\n";
						out << "pop eax\n";
						out << "sub eax, ebx\n";
						out << "push eax\n";
					}
					if (lexT.table[i].lexema == '*')
					{
						out << "pop eax\n";
						out << "pop ebx\n";
						out << "mul ebx\n";
						out << "push eax\n";
					}
					i++;
				}
				out << "pop " << idT.table[lexT.table[indOflex].idxTI].id << "\n\n";
			}
		}
		out << "end main";
	}
}
//TODO: вставить стандартную либц в шапку