#include "globals.h"
#include "File.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Caractere pentru spatiere */
bool isspace(char c) 
{
	if (c == '\t' || c == '\f' || c == '\v' || c == '\n' || c == '\r' || c == ' ') return true;
	return false;
}

/* Caractere pentru inceput nou de linie */
bool isnewline(char c) 
{
	if (c == '\r' || c == '\n') return true;
	return false;
}

/* Caractere alfanumerice */
bool isalpha(char c) 
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
	return false;
}

/* Caractere pentru delimitare declaratii */
bool isdelim(char c) 
{
	if (c == '(' || c <= ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',') return true;
	return false;
}

char *trim(char *c) 
{
	char *e = c + strlen(c) - 1;
	while (*c && (isspace(*c) || isnewline(*c))) c++;
	while (e > c && (isspace(*e) || isnewline(*e))) *e-- = '\0';
	return c;
}

string trim(const string& StrToTrim)
{
	// Find first non whitespace char in StrToTrim

	size_t First = StrToTrim.find_first_not_of(' ');
	size_t Last = StrToTrim.find_last_not_of(' ');

	if ((First == string::npos) && (Last == string::npos)) return "";

	// Check whether something went wrong?
	if (First == string::npos)
	{
		First = 0;
	}

	// Find last non whitespace char from StrToTrim
	
	// If something didn't go wrong, Last will be recomputed to get real length of substring
	if (Last != string::npos)
	{
		Last = (Last + 1) - First;
	}

	// Copy such a string to TrimmedString
	return StrToTrim.substr(First, Last);
}

/* A se folosi doar dupa ce se face trim !!! 
   Ceva de forma "" sau '' fara nimic altceva inainte dupa delimitator*/
bool isstring(string str, char delimiter)
{
	size_t First = str.find_first_of(delimiter);
	size_t Last = str.find_last_of(delimiter);

	if ((First == string::npos) || (Last == string::npos)) return false;

	if (First > 0 || Last < str.size() - 1) return false;

	return true;
}

/* Ceva de genul: a=b */
bool istagattr(string str)
{
	size_t equal = str.find_first_of('=');

	if (equal == string::npos || str.size() < 3) return false;
	
	return true;
}

void setAttribute(int &attr, int val)
{
	attr |= val;
}

void unsetAttribute(int &attr, int val)
{
	attr &= ~val;
}

/* Numara de cate ori apare un anume caracter intr-un sir de caractere */
int count(char *str, char c)
{
	char *p;
	int count = 0;

	while ((p = strchr(str, c)) != NULL) { count++; str = p + 1; }

	return count;
}

Keyword *FindKeyword(char *name)
{
	//printf("FindKeyword [%s]\n", name);
	int keyword_size = sizeof(keywords) / sizeof(Keyword);
	//printf("Keyword size = %i\n", keyword_size);
	for (int i = 0; i < keyword_size; i++) {
		if (strcmp(name, keywords[i].name) == 0) return &keywords[i];
	}

	//printf("++++++++++++++++Nu am gasit %s\n", name);

	return NULL;
}

void ParseMainParameters(vector<string> parametri)
{
	int size = parametri.size();
	string s, t;

	for (int i = 0; i < size; i++) {
		s = parametri[i];
		if (s == "$bootstrap") {
			css_framework = VAR_BOOTSTRAP;
			continue;
		}

		if (s == "$foundation") {
			css_framework = VAR_FOUNDTION;
			continue;
		}

		if (s == "$fixed") {
			css_layout_type = VAR_FIXED;
			continue;
		}

		if (s == "$fluid") {
			css_layout_type = VAR_FLUID;
			continue;
		}

		if (s == "$adaptive") {
			web_adaptive = VAR_ADAPTIVE;
			continue;
		}

		if (s == "$leapmotion") {
			web_gestures = VAR_LEAP_MOTION;
			continue;
		}
	}
}

SmartTagAttribute ParseSmartAttributes(vector<string> parametri, int start)
{	
	SmartTagAttribute smart;
	smart.hidden = false;
	smart.get = false;
	smart.post = false;

	/* Cautam atribute inteligente */
	int size = parametri.size();
	string s, t, col, push, pull, offset;	

	printf("Start = %i, size = %i\n", start, size);

	for (int i = start; i < size; i++) {
		s = parametri[i];
		printf("**** Parametru: %i = [%s]\n", i, s.c_str());

		col = s.substr(0, 2);		
		push = s.substr(0, 7);
		pull = s.substr(0, 7);
		offset = s.substr(0, 9);

		/*printf("col = %s\n", col.c_str());
		printf("push = %s\n", push.c_str());
		printf("pull = %s\n", pull.c_str());
		printf("offset = %s\n", offset.c_str());*/
		
		/* xs - extra small */
		if (col == "xs") {
			t = s.substr(2);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) xs [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-xs-"+t);
				continue;
			  }
		} 

		/* xs-push */
		if (push == "xs-push") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) xs_push [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-xs-push-" + t);
				continue;
			  }
		} 

		/* xs-pull */
		if (pull == "xs-pull") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) xs_pull [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-xs-pull-" + t);
				continue;
			  }
		} 

		/* xs-offset */
		if (offset == "xs-offset") {
			t = s.substr(9);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) xs_offset [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-xs-offset-" + t);
				continue;
			  }
		}

		/* xs-offset */
		if (s == "xs-hidden") {
			printf("%i) xs_hidden\n", i + 1);
			smart.responsive.push_back("hidden-xs");
			continue;
		}

		/* sm - small */
		if (col == "sm") {
			t = s.substr(2);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) sm [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-sm-" + t);
				continue;
			  }
		} 

		/* sm-push */
		if (push == "sm-push") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) sm_push [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-sm-push-" + t);
				continue;
			  }
		}

		/* sm-pull */
		if (pull == "sm-pull") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) sm_pull [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-sm-pull-" + t);
				continue;
			  }
		}

		/* sm-offset */
		if (offset == "sm-offset") {
			t = s.substr(9);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) sm_offset [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-sm-offset-" + t);
				continue;
			  }
		}

		/* sm-hidden */
		if (s == "sm-hidden") {
			printf("%i) sm_hidden\n", i + 1);
			smart.responsive.push_back("hidden-sm");
			continue;
		} 

		/* md - medium */
		if (col == "md") {
			t = s.substr(2);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) md [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-md-" + t);
				continue;
			  }
		}

		/* md-push */
		if (push == "md-push") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) md_push [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-md-push-" + t);
				continue;
			  }
		} 

		/* md-pull */
		if (pull == "md-pull") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) md_pull [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-md-pull-" + t);
				continue;
			  }
		}

		/* md-offset */
		if (offset == "md-offset") {
			t = s.substr(9);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) md_offset [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-md-offset-" + t);
				continue;
			  }
		}

		/* md-hidden */
		if (s == "md-hidden") {
			printf("%i) md_hidden\n", i + 1);
			smart.responsive.push_back("hidden-md");
			continue;
		}

		/* lg */
		if (col == "lg") {
			t = s.substr(2);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) lg [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-lg-" + t);
				continue;
			  }
		}

		/* lg-push */
		if (push == "lg-push") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) lg_push [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-lg-push-" + t);
				continue;
			  }
		}

		/* lg-pull */
		if (pull == "lg-pull") {
			t = s.substr(7);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) lg_pull [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-lg-pull-" + t);
				continue;
			  }
		}

		/* lg-offset */
		if (offset == "lg-offset") {
			t = s.substr(9);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				printf("%i) lg_offset [%s], %i\n", i + 1, t.c_str(), h);
				smart.responsive.push_back("col-lg-offset-" + t);
				continue;
			  }
		} 

		if (s == "lg-hidden") {
			printf("%i) lg_hidden\n", i + 1);
			smart.responsive.push_back("hidden-lg");
			continue;
		}

		/* id - se memoreaza ultimul id introdus */
		if (s[0] == '#') {
			t = s.substr(1);
			if (smart.id.size() > 0) printf("ATENTIE: Aveti deja un id definit!!!\n");
			//printf("%i) id [%s], [%s] \n", i + 1, s.c_str(), t.c_str());
			smart.id = t;
			continue;
		}

		/* class */
		if (s[0] == '.') {
			t = s.substr(1);
			//printf("%i) class [%s] \n", i + 1, t.c_str());
			smart.clasa.push_back(t);
			continue;
		}

		/* title */
		if (s[0] == '~') {
			t = s.substr(1);
			//printf("%i) title [%s]\n", i + 1, t.c_str());
			smart.title = t;
			continue;
		}

		/* hidden */
		if (s == "!") {
			//printf("%i) hidden [%s]\n", i + 1, s.c_str());
			smart.hidden = true;
			continue;
		}

		/* lang */
		if (s[0] == '&') {
			t = s.substr(1);
			//printf("%i) lang [%s]\n", i + 1, t.c_str());
			smart.lang = t;
			continue;
		}

		/* data-* */
		if (s[0] == '*') {
			t = s.substr(1);
			//printf("%i) data-* [%s]\n", i + 1, t.c_str());
			smart.data.push_back(t);
			continue;
		}

		/* target */
		if ((s == "_blank") || (s == "_self") || (s == "_top") || (s == "_parent")) {
			//printf("%i) target [%s]\n", i + 1, s.c_str());
			smart.target = s;
			continue;
		}

		/* x */
		if (s[0] == 'x') {
			t = s.substr(1);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				//printf("%i) width [%s], %i\n", i + 1, t.c_str(), h);
				smart.x.push_back(h);
				continue;
			  }
		}

		/* y */
		if (s[0] == 'y') {
			t = s.substr(1);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				//printf("%i) height [%s], %i\n", i + 1, t.c_str(), h);
				smart.y.push_back(h);
				continue;
			  }
		}

		/* width */
		if (s[0] == 'w') {
			t = s.substr(1);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				//printf("%i) width [%s], %i\n", i + 1, t.c_str(), h);
				smart.width.push_back(h);
				continue;
			  }
		}

		/* height */
		if (s[0] == 'h') {
			t = s.substr(1);
			int h = atoi(t.c_str());
			char nr[10];
			_itoa_s(h, nr, 10);
			if (strlen(nr) == t.size()) {
				//printf("%i) height [%s], %i\n", i + 1, t.c_str(), h);
				smart.height.push_back(h);
				continue;
			  }
		}

		if (s == "get") {			
			//printf("%i) get\n", i + 1);
			smart.get = true;
			smart.post = false;
			continue;
		}

		if (s == "post") {
			//printf("%i) post\n", i + 1);
			smart.get = false;
			smart.post = true;
			continue;
		}

		/* url */
		if (s[0] == '@') {
			t = s.substr(1);
			//printf("%i) url [%s]\n", i + 1, t.c_str());
			smart.url = t;
			continue;
		}

		smart.normal.push_back(s);
	}

	return smart;
}

File::File(char *filename) 
{
	if (filename != NULL) {
		int size = strlen(filename);

		if (size > 0) {
			this->filename = (char *)malloc(size + 1);
			memcpy_s(this->filename, size + 1, filename, size + 1);
		}

		file_size = FileSize();
	}

	f = NULL;	
}

bool File::Open() 
{
	if (filename == NULL) return false;

	if (fopen_s(&f, filename, "r") != 0) return false;

	if (f == NULL) return false;

	return true;
}

bool File::Read()
{
	program = (char *)calloc(1, file_size + 1);

	if (program == NULL) return false;

	fread_s(program, file_size, 1, file_size, f);

	return true;
}

bool File::Parse()
{
	statements = Parse(program);

	return true;
}

vector<Statement> File::Parse(char* &prog)
{
	vector<Statement> statements;
	vector<Token> tokens;
	Token *t;

	do {		
		t = GetToken(prog);
		if (t == NULL) break;
		if (t && t->type != FINISH) {
			tokens.push_back(*t);			
		}
	} while (t && t->type != FINISH);

	if (t == NULL) {
		printf("Eroare la procesarea fisierului!!!\n");
		return statements;
	}

	statements = Preprocess(tokens);

	int size = statements.size();
	for (int i = 0; i < size; i++) {
		Statement *s = &statements[i];
		if (s->type == STATEMENT) {
			if (s->block && ((s->attribute & ATTR_NO_BLOCK_PARSE) == 0)) {
				s->statements = Parse(s->block);
			}			
		}
	}

	return statements;
}

vector<string> File::ParseParameters(char* &prog, char delimiter)
{
	vector<string> parametri;
	char *token = NULL;

	if (strlen(prog) == 0) return parametri;

	//printf("[] Parametri de procesat: {%s}\n", prog);

	/*char *pt = strtok(prog, delimiter);
	while (pt != NULL) {
		if (strlen(pt) > 0) {
			char *s = trim(pt);
			parametri.push_back(s);
		}
		pt = strtok(NULL, delimiter);
	}*/
	char *cstart, *cend;
	int size;
	bool sir = false;

	cstart = prog;

	while (*prog != 0) {
		if (*prog == '"') {
			while (*prog != '"') prog++;
			prog++;
		}

		if (*prog == delimiter) {
			cend = prog;

			size = cend - cstart;
			if (token) {
				free(token);
				token = NULL;
			}
			token = (char *)calloc(1, size + 1);
			strncpy(token, cstart, size);

			parametri.push_back(trim(string(token)));

			//printf("Token = [%s], size = %i\n", parametri.back().c_str(), parametri.back().size());

			prog++;
			//while (isspace(*prog) && *prog) ++prog;
			cstart = prog;
		} 
		
		prog++;
	} 

	cend = prog;

	size = cend - cstart;
	if (token) {
		free(token);
		token = NULL;
	}
	token = (char *)calloc(1, size + 1);
	strncpy(token, cstart, size);
	parametri.push_back(trim(string(token)));

	//printf("Token = [%s], size = %i\n", parametri.back().c_str(), parametri.back().size());

	/*printf("[][] = ");
	for (int i = 0; i < parametri.size(); i++) printf("[%s]", parametri[i].c_str());
	printf("\n");*/


	return parametri;
}

vector<Statement> File::Preprocess(vector<Token> date)
{
	int i = 0;
	int size = date.size();
	vector<Statement> pp;

	Statement *s = NULL;
	Token *t;

	//printf("Marime date tokenuri = %i\n", size);

	printf("Preprocesam token-urile.\n");

	if (size == 0) return pp;

	do {
		t = &date[i];
		
		if (t->type == INTERNAL_COMMENT);

		if (t->type == KEYWORD) {
			if (s != NULL) {
				pp.push_back(*s);
				s = NULL;
			}

			s = new Statement;
			s->type = STATEMENT;
			s->keyword = t->token;			
			Keyword *k = FindKeyword(t->token);
			if (k) s->attribute = k->attribute; else s->attribute = 0;
			s->block = NULL;
			s->code = NULL;
			s->args = 0;
			s->smart.hidden = 0;
			s->smart.get = 0;
			s->smart.post = 0;
		}

		if (t->type == PARAMETERS) {
			if ((s->attribute & ATTR_SINGLE_PARAM) > 0) {
				char *p = trim(t->token);
				if (strlen(p) > 0) s->parameters.push_back(p);
			} else {
				s->parameters = ParseParameters(t->token, ',');
				s->smart = ParseSmartAttributes(s->parameters, 0);
			  }
		}

		if (t->type == BLOCK) {
			s->block = t->token;

			pp.push_back(*s);
			s = NULL;
		}

		if (t->type == CODE) {
			s->type = CODE;
			s->block = NULL;
			s->code = trim(t->token);

			pp.push_back(*s);
			s = NULL;
		}

		if (t->type == HTML5_COMMENT) {
			if (s != NULL) {
				pp.push_back(*s);
				s = NULL;
			}

			s = new Statement;
			s->type = HTML5_COMMENT;
			s->keyword = NULL;
			s->attribute = 0;
			s->block = trim(t->token);
			s->code = NULL;
			s->args = 0;
			s->smart.hidden = 0;
			s->smart.get = 0;
			s->smart.post = 0;
		}

		if (t->type == STRING) {
			if (s != NULL) {
				pp.push_back(*s);
				s = NULL;
			}

			s = new Statement;
			s->type = STRING;
			s->keyword = NULL;
			s->attribute = 0;
			s->block = trim(t->token);
			s->code = NULL;
			s->args = 0;
			s->smart.hidden = 0;
			s->smart.get = 0;
			s->smart.post = 0;
		}

		if (t->type == NUMBER) {
			if (s != NULL) {
				pp.push_back(*s);
				s = NULL;
			}

			s = new Statement;
			s->type = NUMBER;
			s->keyword = NULL;
			s->attribute = 0;
			s->block = trim(t->token);
			s->code = NULL;
			s->args = 0;
			s->smart.hidden = 0;
			s->smart.get = 0;
			s->smart.post = 0;
		}

		i++;
	} while (i < size);

	if (s != NULL) {
		pp.push_back(*s);
		s = NULL;
	}

	return pp;
}

unsigned long File::FileSize()
{
	FILE *f = NULL;
	fopen_s(&f, filename, "rb");
	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		unsigned long size = ftell(f);
		fclose(f);

		f = NULL;

		return size;
	}	

	return 0;
}

Token *File::GetToken() {
	return GetToken(program);
}

Token *GetTokenString(char* &prog)
{
	Token *token = NULL;

	int c = count(prog, '"');

	//printf("Cate ghilimele = %i\n", c);

	while (isspace(*prog) && *prog) ++prog;

	char *cstart, *cend;
	int size;

	if (c == 0) {
		token = new Token;

		cstart = prog;
		while (!isnewline(*prog)) prog++;
		cend = prog;

		size = cend - cstart;
		token->type = NUMBER;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
	} else

	/* Sir de caractere intre ghilimele duble */
	if (*prog == '"' && c >= 2) {
		token = new Token;

		prog++;
		cstart = prog;
		while (*prog != '"' && !isnewline(*prog)) prog++;
		cend = prog;
		if (isnewline(*prog)) {
			printf("Eroare de sintaxa la ->%s", prog);
			return NULL;
		}

		size = cend - cstart;
		token->type = STRING;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		//printf("String = [%s]\n", token->token);
		prog++;
		while (isspace(*prog) && *prog) ++prog;		
	}

	return token;
}

Token *File::GetToken(char* &prog)
{
	Token *token = NULL;

	while (isspace(*prog) && *prog) ++prog;

	/* Sfarsit de fisier */
	if (*prog == '\0') {
		token = new Token;
		token->type = FINISH;
		token->token = NULL;
		return token;
	}

	/* Comentariu: HTML5 sau intern */
	char *cstart, *cend;
	int size;

	if (*prog == ';') {
		token = new Token;

		prog++;

		cstart = prog;
		while (!isnewline(*prog)) prog++;
		cend = prog;

		size = cend - cstart;
		token->type = INTERNAL_COMMENT;
		token->token = (char *)calloc(1, size+1);	
		strncpy(token->token, cstart, size);
		printf("Comentariu intern = [%s]\n", token->token);
		while (isspace(*prog) && *prog) ++prog;

		printf("%s", prog);

		return token;
	} 

	/* Comentariu pe o linie */
	if (*prog == '/' && *(prog+1) == '/') {
		token = new Token;

		prog += 2;

		cstart = prog;
		while (!isnewline(*prog)) prog++;
		cend = prog;

		size = cend - cstart;
		token->type = HTML5_COMMENT;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		printf("Comentariu HTML5 pe o linie = [%s]\n", token->token);
		while (isspace(*prog) && *prog) ++prog;

		return token;
	} 

	/* Comentariu pe una sau mai multe linii */
	if (*prog == '/' && *(prog + 1) == '*') {
		token = new Token;

		prog += 2;

		cstart = prog;
		while (*prog != '*' && *(prog + 1) != '/') prog++;
		cend = prog;

		size = cend - cstart;
		token->type = HTML5_COMMENT;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		printf("Comentariu HTML5 multilinie = [%s]\n", token->token);
		prog += 2;
		while (isspace(*prog) && *prog) ++prog;

		return token;
	}

	/* Cuvant cheie */
	if (isalpha(*prog)) {
		token = new Token;

		cstart = prog;
		while (!isdelim(*prog)) prog++;
		cend = prog;

		size = cend - cstart;
		token->type = KEYWORD;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		printf("Keyword = [%s]\n", token->token);
		while (isspace(*prog) && *prog) ++prog;

		return token;
	}

	/* Parametri cuvinte cheie */
	if (*prog == '(') {
		token = new Token;

		prog++;

		cstart = prog;
		while (*prog != ')' && *prog) prog++;
		cend = prog;

		size = cend - cstart;
		token->type = PARAMETERS;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		printf("- parametri = [%s]\n", token->token);
		prog++;
		while (isspace(*prog) && *prog) ++prog;

		return token;
	}

	/* Delimitator de cod sursa */
	if (*prog == '{' && *(prog + 1) == '{') {
		token = new Token;

		prog += 2;

		while (isspace(*prog) && *prog) ++prog;

		cstart = prog;
		while (*prog != '}' && *(prog + 1) != '}') prog++;
		cend = prog;

		size = cend - cstart;
		token->type = CODE;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		printf("- cod sursa = [%i caractere]\n", strlen(token->token));
		prog += 3;
		while (isspace(*prog) && *prog) ++prog;

		return token;
	}

	/* Delimitator de bloc */
	if (strchr("{", *prog)) {
		token = new Token;
		prog++;
		int level = 1;

		while (isspace(*prog) && *prog) ++prog;
		cstart = prog;
		do {
			if (*prog == NULL) {
				printf("Tocmai s-a terminat brusc citirea!!!");
				break;
			}
			if (*prog == '{') ++level;
			if (*prog == '}') --level;
			if (level > 0) prog++;
		} while ((level > 0) && *prog);

		if (level > 1) printf("&&&&&&&&&&&&& Avem o problema la citire!!!!\n");

		cend = prog;

		size = cend - cstart;
		token->type = BLOCK;
		token->token = (char *)calloc(1, size + 1);
		strncpy(token->token, cstart, size);
		//printf("- declaratie bloc = %i caractere, [\n%s]\n", strlen(token->token), token->token);
		prog++;
		while (isspace(*prog) && *prog) ++prog;

		return token;
	}	

	/* Sir de caractere intre ghilimele duble */
	if (*prog == '"') {
		token = GetTokenString(prog);

		if (token != NULL) printf("- sir de caractere = [%s]\n", token->token);

		return token;
	}

	printf("Am ajuns unde nu trebuie [%s]\n", prog);
	return NULL;
}

vector<Statement> File::GetStatements()
{
	return statements;
}

void File::Print(vector<Statement> statements)
{
	int size = statements.size();
	for (int i = 0; i < size; i++) {
		Statement *s = &statements[i];
		printf("%i) Statement type %i\n", i + 1, s->type);
		printf("    Keyword = [%s]\n", s->keyword);
		printf("    Attribute = %i\n", s->attribute);
		printf("    Code = [%s]\n", s->code);
		printf("    Block = [%s]\n", s->block);
		printf("    Parameters: ");
		for (int j = 0; j < s->parameters.size(); j++) printf("{%s} ", s->parameters[j].c_str());
		printf("\n");
		if (s->statements.size() > 0) Print(s->statements);
	}
}

File::~File()
{
	if (f != NULL) {
		fclose(f);
		f = NULL;
	}

	if (filename != NULL) {
		free(filename);
		filename = NULL;
	}
}