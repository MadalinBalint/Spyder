/*
	Cuvinte cheie (keywords): toate tag-urile specifice HTML5 + urmatoarele: main, html5, css, js, php, attr, title, keywords
	Operatori: () - pentru parametri cuvant cheie (nu toate cuvintele cheie pot prezenta parametri)
	           ,  - pentru separarea parametrilor, valorilor
			   :  - pentru array-uri gen JSON: "proprietate" : "valoare"
			   [] - delimiteaza inceputul si sfarsitul unui array
			   {} - delimiteaza inceputul si sfarsitul declaratiilor de instructiuni ce urmeaza dupa un cuvant cheie
			   {{ }} - delimiteaza inceputul si sfarsitul declaratie pt cod sursa; el este scris ca atare fara ghilimele simple sau duble;
			           valabil doar pt cuvintele cheie: html5, css, js, php
			   " - delimiteaza un sir de caractere (string)
*/

#include "globals.h"
#include "File.h"
#include "Compiler.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>

int css_framework = VAR_NOT_DEFINED;
int css_layout_type = VAR_NOT_DEFINED;
int web_adaptive = VAR_NOT_DEFINED;
int web_gestures = VAR_NOT_DEFINED;
int level = 1;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\nSpyder - limbaj programare WEB - v1g - 02.2015\n\n");
		printf("Sintaxa: SPYDER.EXE fisier.web\n");

		_getch();

		return 0;
	}

	printf("Procesam fisierul %s.\n", argv[1]);

	File *f = new File(argv[1]);
	Compiler *c = new Compiler();

	if (f->Open()) {
		if (f->Read()) {
			f->Parse();
		} else {
			printf("\nEroare la citirea datelor din fisierul %s.\n", argv[1]);
			_getch();

			return -1;
		  }
	} else {
		printf("\nFisierul %s nu exista sau nu poate fi accesat.\n", argv[1]);
		_getch();

		return -1;
	  }
	
	vector<Statement> statements = f->GetStatements();
	f->Print(statements);
	c->CheckStatements(statements);
	c->Compile(statements);

	_getch();

	delete f;
	delete c;

    return 0;
}

