#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "File.h"

#include <vector>
#include <string>

using namespace std;

class Compiler
{
private:
	vector<string> head;
	vector<string> body;
	string lang;
public:
	Compiler();
	void CheckStatements(vector<Statement> &statements);
	void Compile(vector<Statement> statements);
	void CompileStatement(Statement *s, int args);
	void CompileStatement(Statement *s, vector<string> &v, int args);
	string ExtraAtribute(Statement *s, int start);
	string ExtraStatement(Statement *s, int args);
	string CompileExtra(Statement *&s, int args);
	void PushStatement(Statement *s, string h);
	bool EroareParametri(Statement *s, int n);
	~Compiler();
};

