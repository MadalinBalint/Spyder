#include "globals.h"
#include "Compiler.h"
#include "File.h"

#include <fstream>
#include <conio.h>
#include <stdarg.h>

using namespace std;

/*****************************************
Operatii pentru scriere Smart Attributes
******************************************/

/* id */
string WriteSmartId(SmartTagAttribute &smart)
{
	string t;

	if (smart.id.size() > 0) {
		t = "id=\"" + smart.id + "\"";
	}

	return t;
}

/* class */
string WriteSmartClass(SmartTagAttribute &smart)
{
	string t;
	int size = smart.clasa.size();
	int sizer = smart.responsive.size();
	int i, sizet;

	if ((size > 0) || (sizer > 0)) {
		t = "class=\"";
		
		sizet = t.size();

		for (i = 0; i < sizer; i++) {
			if (i > 0) t += " ";
			t += smart.responsive[i];
			printf("Responsive: [%s]\n", smart.responsive[i].c_str());
		}

		if (t.size() > sizet) t += " ";

		for (i = 0; i < size; i++) {
			if (i > 0) t += " ";
			t += smart.clasa[i];
		}
		t += "\"";
	}

	return t;
}

/* title */
string WriteSmartTitle(SmartTagAttribute &smart)
{
	string t;

	if (smart.title.size() > 0) {
		t = "title=" + smart.title;
	}

	return t;
}

/* data */
string WriteSmartData(SmartTagAttribute &smart)
{
	string t;

	int size = smart.data.size();

	for (int i = 0; i < size; i++) {
		if (t.size() > 0) t += " ";
		t += "data-" + smart.data[i];
	}

	return t;
}

/* hidden */
string WriteSmartHidden(SmartTagAttribute &smart)
{
	string t;

	if (smart.hidden) {
		t = "hidden";
	}

	return t;
}

/* lang */
string WriteSmartLang(SmartTagAttribute &smart)
{
	string t;

	if (smart.lang.size() > 0) {
		t = "lang=" + smart.lang;
	}

	return t;
}

/* target */
string WriteSmartTarget(SmartTagAttribute &smart)
{
	string t;

	if (smart.target.size() > 0) {
		t = "target=\"" + smart.target + "\"";
	}

	return t;
}

/* x */
string WriteSmartX(SmartTagAttribute &smart, string prop, string separator)
{
	string t;

	int size = smart.x.size();
	if (size > 0) {
		t = prop + "=";
		t += separator;
		t += smart.x[size - 1];
		t += separator;
	}
	
	return t;
}

/* y */
string WriteSmartY(SmartTagAttribute &smart, string prop, string separator)
{
	string t;

	int size = smart.y.size();
	if (size > 0) {
		t = prop + "=";
		t += separator;
		t += smart.y[size - 1];
		t += separator;
	}

	return t;
}

/* w */
string WriteSmartWidth(SmartTagAttribute &smart, string prop, string separator)
{
	string t;

	int size = smart.width.size();
	if (size > 0) {
		t = prop + "=";
		t += separator;
		t += smart.width[size - 1];
		t += separator;
	}

	return t;
}

/* h */
string WriteSmartHeight(SmartTagAttribute &smart, string prop, string separator)
{
	string t;

	int size = smart.height.size();
	if (size > 0) {
		t = prop + "=";
		t += separator;
		t += smart.height[size - 1];
		t += separator;
	}

	return t;
}

/* get, post */
string WriteSmartMethod(SmartTagAttribute &smart, string prop)
{
	string t;

	if (smart.get) {
		t = prop;
		t += "=\"get\"";
	} else
	if (smart.post) {
		t = prop;
		t += "=\"post\"";
	}

	return t;
}

/* url */
string WriteSmartURL(SmartTagAttribute &smart, string prop)
{
	string t;

	int size = smart.url.size();
	if (size > 0) t = prop + '=' + smart.url;

	return t;
}

Compiler::Compiler()
{
}

void Compiler::CheckStatements(vector<Statement> &statements)
{
	//printf("\n----------------Incepem verificare declaratiilor:\n");

	int size = statements.size();
	for (int i = 0; i < size; i++) {
		Statement *s = &statements[i];

		s->compile = true;

		if (s->type == STATEMENT) {
			if (FindKeyword(s->keyword) == NULL) {
				s->compile = false;
				printf("Keyword [%s] nu exista!!!\n", s->keyword);
			}
		}		
		
		if (s->statements.size() > 0) CheckStatements(s->statements);
	}
}

string WriteSmartGlobalAttributes(Statement *s)
{
	string t;	

	string id = WriteSmartId(s->smart);
	string clasa = WriteSmartClass(s->smart);
	string lang = WriteSmartLang(s->smart);
	string hidden = WriteSmartHidden(s->smart);
	string title = WriteSmartTitle(s->smart);
	string data = WriteSmartData(s->smart);

	t = id;
	if (clasa.size() > 0) {
		if (t.size() > 0) t += " ";
		t += clasa;
	}

	if (data.size() > 0) {
		if (t.size() > 0) t += " ";
		t += data;
	}

	if (lang.size() > 0) {
		if (t.size() > 0) t += " ";
		t += lang;
	}

	if (hidden.size() > 0) {
		if (t.size() > 0) t += " ";
		t += hidden;
	}

	if (title.size() > 0) {
		if (t.size() > 0) t += " ";
		t += title;
	}

	return t;
}

string WriteSmartNonGlobalAttributes(Statement *s)
{
	int i, size;
	string t;
	vector<SmartAttributeNonGlobal> atribute;

	int attr_size = sizeof(nonglobal) / sizeof(SmartAttributeNonGlobal);
	//printf("Keyword size = %i\n", keyword_size);
	for (i = 0; i < attr_size; i++) {
		if (strcmp(s->keyword, nonglobal[i].tag) == 0) atribute.push_back(nonglobal[i]);
	}

	size = atribute.size();
	for (i = 0; i < size; i++) {
		string a;
		SmartAttributeNonGlobal attr = atribute[i];
		if (attr.idAttr == X) a = WriteSmartX(s->smart, attr.attr, "\""); else
		if (attr.idAttr == Y) a = WriteSmartY(s->smart, attr.attr, "\""); else
		if (attr.idAttr == WIDTH) a = WriteSmartHeight(s->smart, attr.attr, "\""); else
		if (attr.idAttr == HEIGHT) a = WriteSmartWidth(s->smart, attr.attr, "\""); else
		if (attr.idAttr == METHOD) a = WriteSmartMethod(s->smart, attr.attr); else
		if (attr.idAttr == URL) a = WriteSmartURL(s->smart, attr.attr); else
		if (attr.idAttr == TARGET) a = WriteSmartTarget(s->smart); 

		if (a.size() > 0) {
			if (t.size() > 0) t += " ";
			t += a;
		}
	}

	return t;
}

/********************************
 Operatii clasice pentru tag-uri
*********************************/
string WriteArgs(Statement *s) 
{
	int size = s->smart.normal.size();
	
	string t = WriteSmartGlobalAttributes(s);	
	string g = WriteSmartNonGlobalAttributes(s);
	if (g.size() > 0) {
		if (t.size() > 0) t += " ";
		t += g;
	}
	if ((t.size() > 0) && (size > 0)) t += " ";
	//printf("Arg smart = [%s] - keyword = [%s]\n", t.c_str(), s->keyword);

	string a;
	for (int i = 0; i < size; i++) {
		a = s->smart.normal[i];
		if (a.size() > 0) {
			t += a;
			if (i < size - 1) t += " ";
		}
	}

	//printf("ARGS: [%s]\n", t.c_str());

	return t;
}

string OpenTag(Statement *s)
{
	string t = "<" + string(s->keyword);
	string a = WriteArgs(s);

	//printf("Argumente pt [%s] = [%s]\n", s->keyword, a.c_str());

	if (a.size() > 0) t += " " + a;
	if (((s->attribute & ATTR_NO_CLOSING_TAG) == 0) || ((s->attribute & ATTR_XML_CLOSE) == 0)) t += ">";

	return t;
}

string CloseTag(Statement *s)
{
	string t;

	/* Pentru unele tag-uri SVG */
	if ((s->attribute & ATTR_XML_CLOSE) > 0) {
		t += '/';
	} else
	if ((s->attribute & ATTR_NO_CLOSING_TAG) == 0) {
		t += "</" + string(s->keyword);
	}
	t += ">";

	return t;
}

string HTML5Comment(Statement *s)
{
	string t;

	if (strlen(s->block) > 0) {
		t = "<!-- ";
		t += s->block;
		t += " -->";
	}	

	return t;
}

string space()
{
	string s;
	for (int i = 0; i < level; i++) s += "   ";
	return s;
}

void Compiler::Compile(vector<Statement> statements)
{
	vector<Statement> main;
	Statement *s;
	bool main_block = false;

	int size = statements.size();
	for (int i = 0; i < size; i++) {
		 s = &statements[i];

		if ((s->attribute & ATTR_MAIN) > 0) {
			main = s->statements;
			ParseMainParameters(s->parameters);
			main_block = true;
			break;
		}
	}

	if (!main_block) {
		printf("Eroare: nu am gasit inceputul programului ('start') !!!\n");
		_getch();
		return;
	}

	if (css_layout_type > 0) level++;

	size = main.size();

	for (int i = 0; i < size; i++) {
		s = &main[i];
		CompileStatement(s, s->args);
	}	

	fstream f;
	f.open("index.html", fstream::out);

	f << "<!DOCTYPE html>\n\n";
	f << "<html";
	if (lang.size() > 0) f << " lang=" << lang;
	f << ">\n";

	int h = head.size();
	if (h > 0) {
		f << "<head>\n";
		for (int i = 0; i < h; i++) {
			f << head[i] << "\n";
		}
		f << "</head>\n\n";
	}	

	int b = body.size();
	if (b > 0) {
		f << "<body>\n";
		if (css_layout_type == VAR_FLUID) {
			level = 1;
			f << space() + "<div class=\"container-fluid\">\n";
		} else
		if (css_layout_type == VAR_FIXED) {
			level = 1;
			f << space() + "<div class=\"container\">\n";
		} 

		for (int i = 0; i < body.size(); i++) {
			f << body[i] << "\n";
		}

		if ((css_layout_type == VAR_FLUID) || (css_layout_type == VAR_FIXED)) {
			level = 1;
			f << space() + "</div>\n";
		}		

		f << "</body>\n";
	}	

	f << "</html>";

	f.close();
}

void Compiler::CompileStatement(Statement *s, vector<string> &v, int args)
{
	string h, e, ce;
	
	if (s->compile) {
		if (s->type == HTML5_COMMENT) {
			h = space() + HTML5Comment(s);
			v.push_back(h);
		} else
		if (s->type == CODE) {
			h = space() + s->code;
			v.push_back(h);
		} else
		if (s->type == STATEMENT) {
			if ((s->attribute & ATTR_SPECIAL) > 0) {
				ce = CompileExtra(s, args);
				if (ce.size() > 0) {
					h = space() + ce;
					v.push_back(h);
				}				
			} else {
				h = space() + OpenTag(s);								

				int size = s->statements.size();
				if (size == 0) {
					h += CloseTag(s);
				} else 
				if ((size == 1) && (s->statements[0].type == STRING || s->statements[0].type == NUMBER)) {
					h += s->statements[0].block;
					h += CloseTag(s);
				} else {
					v.push_back(h);
					++level;

					for (int i = 0; i < size; i++) {
						CompileStatement(&s->statements[i], v, s->args);
					}

					--level;
					
					h = space() + CloseTag(s);
				}
				//printf("H = [%s]\n", h.c_str());

                v.push_back(h);
			  }
		} else
		if (s->type == STRING) {
			h = space() + s->block;
			v.push_back(h);
		} else
		if (s->type == NUMBER) {
			h = space() + s->block;
			v.push_back(h);
		}
	} else {
		/* Asta in caz ca gaseste ceva nedefinit in interiorul unui bloc */
		h = space() + s->keyword;
		v.push_back(h);
	  }
}

void Compiler::CompileStatement(Statement *s, int args)
{
	string h, e, ce;
	
	if (s->compile) {
		if (s->type == HTML5_COMMENT) {
			h = space() + HTML5Comment(s);
			PushStatement(s, h);
		} else
		if (s->type == CODE) {
			h = space() + s->code;
			PushStatement(s, h);
		} else
		if (s->type == STATEMENT) {
			if ((s->attribute & ATTR_SPECIAL) > 0) {
				ce = CompileExtra(s, args);
				if (ce.size() > 0) {
					h = space() + ce;
					PushStatement(s, h);
				}
			} else {
				h = space() + OpenTag(s);

				int size = s->statements.size();
				if (size == 0) {
					h += CloseTag(s);
				} else
				if ((size == 1) && (s->statements[0].type == STRING || s->statements[0].type == NUMBER)) {
					h += s->statements[0].block;
					h += CloseTag(s);
				} else {
					PushStatement(s, h);
					++level;

					for (int i = 0; i < size; i++) {
						CompileStatement(&s->statements[i], s->args);
					}

					--level;

					h = space() + CloseTag(s);
				  }

				  //printf("H = [%s]\n", h.c_str());

				  PushStatement(s, h);
			  }
		} else
		if (s->type == STRING) {
			h = space() + s->block;
			PushStatement(s, h);
		} else
		if (s->type == NUMBER) {
			h = space() + s->block;
			PushStatement(s, h);
		}
	}
}

string Compiler::ExtraAtribute(Statement *s, int start) 
{
	s->smart = ParseSmartAttributes(s->parameters, start);
	int size = s->smart.normal.size();

	/* 1) Scriem atributele inteligente globale */
	string t = WriteSmartGlobalAttributes(s);

	/* 2) Scriem atributele inteligente non-globale (specifice tag-ului) */	
	string g = WriteSmartNonGlobalAttributes(s);
	if (g.size() > 0) {
		if (t.size() > 0) t += " ";
		t += g;
	}

	/* 3) Scriem restul atributelor ramase */
	string a;
	for (int i = 0; i < size; i++) {
		a = s->smart.normal[i];
		if (a.size() > 0) {
			if (t.size() > 0) t += " ";
			t += a;
		}
	}

	if (t.size() > 0) t = " " + t;

	return t;
}

string Compiler::ExtraStatement(Statement *s, int args) 
{
	int stat = s->statements.size(), i;
	string t;
	vector<string> text;

	level++;
	for (i = 0; i < stat; i++) {
		if (args > 0) CompileStatement(&s->statements[i], text, args); else
			          CompileStatement(&s->statements[i], text, s->args);
	}
	level--;

	int size = text.size();
	for (i = 0; i < size; i++) {
		/*if (text[i].size() > 0) */t += "\n" + text[i];
		//printf("text[%i] = [%s]\n", i, text[i].c_str());
	}
	if (size > 0) t += "\n";

	//printf("*********Extra = [%s]\n", t.c_str());

	return t;
}

string GetFileExtension(string file_name)
{
	string extension, filename;

	char *name = (char *)file_name.c_str();
	Token *t = GetTokenString(name);

	filename = string(t->token);
	extension = filename.substr(filename.find_last_of(".") + 1);

	return extension;
}

string GetString(string sir)
{
	int f1 = sir.find_first_of("\"");
	int f2 = sir.find_last_of("\"");

	if (f1 != string::npos) {
		return sir.substr(f1 + 1, f2 - (f1 + 1));
	}

	return "";
}

string Compiler::CompileExtra(Statement *&s, int args)
{
	string t, es;

	int size = s->parameters.size(), i;	

	if (strcmp(s->keyword, "a") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<a href=";
			t += s->parameters[0];
			t += ExtraAtribute(s, 1);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</a>";
		} else {
			t = "<a";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</a>";
		  }
	}

	if (strcmp(s->keyword, "abbr") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<abbr title=";
			t += s->parameters[0];
			t += ExtraAtribute(s, 1);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</abbr>";
		} else {
			t = "<abbr";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</abbr>";
		  }		
	}

	if (strcmp(s->keyword, "author") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<meta name=\"author\" content=";
			t += s->parameters[0];
			t += ">";
		}		
	}

	if (strcmp(s->keyword, "base") == 0) {
		if (!EroareParametri(s, 2)) {
			t = "<base href=";
			t += s->parameters[0];
			t += " target=";
			t += s->parameters[1];
			t += ">";
		} else {
			t = "<base";
			t += ExtraStatement(s, 0);
			t += ">";
		  }		
	}

	if (strcmp(s->keyword, "blockquote") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<blockquote cite=";
			t += s->parameters[0];
			t += ExtraAtribute(s, 1);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</blockquote>";
		} else {
			t = "<blockquote";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</blockquote>";
		  }
	}

	if (strcmp(s->keyword, "br") == 0) {
		t = "<br>";
	}

	if (strcmp(s->keyword, "button") == 0) {
		if (!EroareParametri(s, 3)) {
			string p1 = s->parameters[0];
			string p2 = s->parameters[1];
			string p3 = s->parameters[2];

			t = "<button";
			if (GetString(p1).size() > 0) t += " type=" + p1;
			if (GetString(p2).size() > 0) t += " name=" + p2;
			if (GetString(p3).size() > 0) t += " value=" + p3;
			
			t += ExtraAtribute(s, 3);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</button>";
		} else {
			t = "<button";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</button>";
		  }
	}

	if (strcmp(s->keyword, "caption") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<caption";
			t += ExtraAtribute(s, 1);
			t += ">";
			t += s->parameters[0];
			t += "</caption>";
		} else {
			t = "<caption";
			t += ExtraAtribute(s, 1);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</caption>";
		  }
	}

	if (strcmp(s->keyword, "charset") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<meta charset=";
			t += s->parameters[0];
			t += ">";
		}		
	}	

	if (strcmp(s->keyword, "description") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<meta name=\"description\" content=";
			t += s->parameters[0];
			t += ">";
		}		
	}

	if (strcmp(s->keyword, "form") == 0) {
		string a;
		t = "<form";
		a = ExtraAtribute(s, 0);
		if (a.size() > 0) t += " " + a;
		t += ">";
		t += ExtraStatement(s, 0);
		t += space() + "</form>";
	}

	if (strcmp(s->keyword, "generator") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<meta name=\"generator\" content=";
			t += s->parameters[0];
			t += ">";
		}		
	}	

	if (strcmp(s->keyword, "hr") == 0) {
		t = "<hr>";
	}

	if (strcmp(s->keyword, "html") == 0) {
		t = space() + s->block;
	}	

	if (strcmp(s->keyword, "img") == 0) {
		if (!EroareParametri(s, 2)) {
			t = "<img src=";
			t += s->parameters[0];
			t += " alt=";
			t += s->parameters[1];
			t += ExtraAtribute(s, 2);
			t += ">";
		} else {
			t = "<img";
			t += ExtraAtribute(s, 0);
			t += ">";
		  }
	}

	if (strcmp(s->keyword, "input") == 0) {
		if (!EroareParametri(s, 3)) {
			string p1 = s->parameters[0];
			string p2 = s->parameters[1];
			string p3 = s->parameters[2];

			t = "<input type=";
			t += s->parameters[0];
			t += " name=";
			t += s->parameters[1];
			t += " value=";
			t += s->parameters[2];
			t += ExtraAtribute(s, 3);
			t += ">";

		}
		else {
			t = "<input";
			t += ExtraAtribute(s, 0);
			t += ">";
		}
	}

	if (strcmp(s->keyword, "keywords") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<meta name=\"keywords\" content=";
			t += s->parameters[0];
			t += ">";
		}		
	}

	if (strcmp(s->keyword, "label") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<label for=";
			t += s->parameters[0];
			t += ExtraAtribute(s, 1);
			t += ">";
			t += trim(s->block);
			t += "</label>";
		} else {
			t = "<label";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</label>";
		 }		
	}

	if (strcmp(s->keyword, "lang") == 0) {
		if (!EroareParametri(s, 1)) {
			if (s->parameters.size() > 0) {
				lang = s->parameters[0];
			}
		}
	}

	if (strcmp(s->keyword, "legend") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<legend";
			t += ExtraAtribute(s, 1);
			t += ">";
			t += s->parameters[0];
			t += "</legend>";
		} else {
			t = "<legend";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</legend>";
		  }
		
	}

	if (strcmp(s->keyword, "link") == 0) {
		if (!EroareParametri(s, 1)) {
			string ext = GetFileExtension(s->parameters[0]);

		    /* .css - Cascading Style Sheets */
		    if (ext == "css") {
			    t = "<link rel=\"stylesheet\" href=";
			    t += s->parameters[0];
			    t += ">";
		    } else
		    /* .js - JavaScript */
		    if (ext == "js") {
				t = "<script src=";
			    t += s->parameters[0];
				t += "></script>";
			} else
			/* .php - PHP */
			if (ext == "php") {
				t = "<?php include '"+GetString(s->parameters[0])+"'; ?>";
			}

			//printf("LINK Extensie = [%s]\n", ext.c_str());
		} else {
			t = "<link";
			t += ExtraAtribute(s, 0);
			t += "</link>";
		  }
	}

	if (strcmp(s->keyword, "navbar") == 0) {
		s->parameters.insert(s->parameters.begin(), ".navbar-default");
		s->parameters.insert(s->parameters.begin(), ".navbar");		

		t = "<nav";
		t += ExtraAtribute(s, 0);
		t += ">";
		es = ExtraStatement(s, 0);
		if (es.size() > 0) t += es; else t += "\n";
		t += space() + "</nav>";
	}

	if (strcmp(s->keyword, "navbrand") == 0) {
		if (!EroareParametri(s, 1)) {
			s->parameters.push_back(".navbar-brand");

			t = "<a";
			t += ExtraAtribute(s, 1);
			t += ">";
			t += GetString(s->parameters[0]);
			t += "</a>";
		}		
	}

	if (strcmp(s->keyword, "navdheader") == 0) {
		if (!EroareParametri(s, 1)) {
			s->parameters.push_back(".dropdown-header");

			t = "<li";
			t += ExtraAtribute(s, 1);
			t += ">";
			t += GetString(s->parameters[0]);
			t += "</a>";
		}
	}

	if (strcmp(s->keyword, "navdropdown") == 0) {
		if (!EroareParametri(s, 1)) {
			s->parameters.push_back(".dropdown");

			t = "<li";
			t += ExtraAtribute(s, 1);
			t += ">\n";
			level++;
			t += space() + "<a href=\"#\" class=\"dropdown-toggle\" data-toggle=\"dropdown\" role=\"button\" aria-haspopup=\"true\" aria-expanded=\"false\">";
			t += GetString(s->parameters[0]);
			t += "<span class=\"caret\"></span></a>\n";
			t += space() + "<ul class=\"dropdown-menu\">";
			level++;
			es = ExtraStatement(s, 0);
			if (es.size() > 0) t += es; else t += "\n";
			level--;
			t += space() + "</ul>";
			level--;			
			t += space() + "</li>";
		}
	}

	if (strcmp(s->keyword, "navheader") == 0) {
		s->parameters.insert(s->parameters.begin(), ".navbar-header");

		t = "<div";
		t += ExtraAtribute(s, 0);
		t += ">\n";
		level++;
		t += space() + "<button type=\"button\" class=\"navbar-toggle collapsed\" data-toggle=\"collapse\" data-target=\"#navbar\" aria-expanded=\"false\" aria-controls=\"navbar\">\n";
		level++;
		t += space() + "<span class=\"sr-only\">Toggle navigation</span>\n";
		t += space() + "<span class=\"icon-bar\"></span>\n";
		t += space() + "<span class=\"icon-bar\"></span>\n";
		t += space() + "<span class=\"icon-bar\"></span>\n";
		level--;
		t += space() + "</button>";
		level--;
		es = ExtraStatement(s, 0);
		if (es.size() > 0) t += es; else t += "\n";
		t += space() + "</div>";
	}

	if (strcmp(s->keyword, "navitem") == 0) {
		if (!EroareParametri(s, 2)) {
			t = "<li";
			t += ExtraAtribute(s, 2);
			t += ">";
			t += "<a href=";
			t += s->parameters[1];
			t += ">";
			t += GetString(s->parameters[0]);
			t += "</a>";
			t += "</li>";
		}		
	}

	if (strcmp(s->keyword, "navlogo") == 0) {
		t = "<a class=\"navbar-brand\" style=\"padding: 5px\" href=\"#\">\n";
		level++;
		t += space() + "<img style=\"max-height: 100%; height: 100%; width: auto; margin: 0 auto\"";
		t += ExtraAtribute(s, 0);
		t += ">\n";
		level--;
		t += space() + "</a>";			
	}

	if (strcmp(s->keyword, "navmenu") == 0) {
		s->parameters.insert(s->parameters.begin(), ".collapse");
		s->parameters.insert(s->parameters.begin(), ".navbar-collapse");

		t = "<div";
		t += ExtraAtribute(s, 0);
		t += ">\n";
		level++;
		t += space() + "<ul class=\"nav navbar-nav\">";
		es = ExtraStatement(s, 0);
		//printf("es = [%s]\n", es.c_str());
		if (es.size() > 0) t += es; else t += "\n";
		t += space() + "</ul>\n";
		level--;		
		t += space() + "</div>";
	}

	if (strcmp(s->keyword, "navseparator") == 0) {
		t = "<li role=\"separator\" class=\"divider\"></li>";
	}

	if (strcmp(s->keyword, "navtext") == 0) {
		if (!EroareParametri(s, 1)) {
			s->parameters.push_back(".navbar-text");

			t += "<p";
			t += ExtraAtribute(s, 1);
			t += ">";
			t += GetString(s->parameters[0]);
			t += "</p>";
		}
	}

	if (strcmp(s->keyword, "optgroup") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<optgroup label=";
			t += s->parameters[0];
			t += ExtraAtribute(s, 1);
			t += ">";
			es = ExtraStatement(s, 0);
			if (es.size() > 0) t += es; else t += "\n";
			t += space() + "</optgroup>";
		} else {
			t = "<optgroup";
			t += ExtraAtribute(s, 0);
			t += ">";
			es = ExtraStatement(s, 0);
			if (es.size() > 0) t += es; else t += "\n";
			t += space() + "</optgroup>";
		  }		
	}

	if (strcmp(s->keyword, "option") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<option value=";
			t += s->parameters[0];
			t += ExtraAtribute(s, 1);
			t += ">";
			t += trim(s->block);
			t += "</option>";
		} else {
			t = "<option";
			t += ExtraAtribute(s, 0);
			t += ">";
			es = ExtraStatement(s, 0);
			if (es.size() > 0) t += es; else t += "\n";
			t += space() + "</option>";
		  }
	}

	if (strcmp(s->keyword, "row") == 0) {
		s->parameters.insert(s->parameters.begin(), ".row");

		/*printf("ROW[] = ");
		for (int i = 0; i < s->parameters.size(); i++) printf("[%s] ", s->parameters[i].c_str());
		printf("\n");*/

		t = "<div";		
		t += ExtraAtribute(s, 0);
		t += ">";
		t += ExtraStatement(s, 0);
		t += space() + "</div>";
	}

	if (strcmp(s->keyword, "table") == 0) {
		if (!EroareParametri(s, 1)) {
			if (size > 0) s->args = atoi(s->parameters[0].c_str()); else s->args = 0;

			if (s->args > 0) {
				t = "<table";
				t += ExtraAtribute(s, 1);
				t += ">";
				t += ExtraStatement(s, 0);
				t += space() + "</table>";
			} else {
				t = "<table";
				t += ExtraAtribute(s, 0);
				t += ">";
				t += ExtraStatement(s, 0);
				t += space() + "</table>";
			  }
		} else {
			t = "<table";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</table>";
		  }
	}

	if (strcmp(s->keyword, "tbody") == 0) {
		t = "<tbody";
		t += ExtraAtribute(s, 0);
		t += ">";
		t += ExtraStatement(s, args);
		t += space() + "</tbody>";
	}

	if (strcmp(s->keyword, "textarea") == 0) {
		if (!EroareParametri(s, 2)) {
			t = "<textarea rows=\"";
			t += s->parameters[0] + "\"";
			t += " cols=\"";
			t += s->parameters[1] + "\"";
			t += ExtraAtribute(s, 2);
			t += ">";
			t += trim(s->block);
			t += "</textarea>";
		} else {
			t = "<textarea";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</textarea>";
		  }		
	}

	if (strcmp(s->keyword, "tfoot") == 0) {
		if (!EroareParametri(s, args)) {
			t = "<tfoot";
			t += ExtraAtribute(s, args);
			t += ">\n";
			level++;
			t += space() + "<tr>\n";
			level++;

			/* Doar atunci cand nr de argumente sunt <= cu nr de parametri introdusi, altfel eroare!!! */
			if (args <= size) {
				for (i = 0; i < args; i++) {
					t += space() + "<td>" + s->parameters[i] + "</td>\n";
				}
			}

			level--;
			t += space() + "</tr>\n";
			level--;
			t += space() + "</tfoot>";
		} else {
			t = "<tfoot";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</tfoot>";
		  };
	}

	if (strcmp(s->keyword, "thead") == 0) {
		if (!EroareParametri(s, args)) {			
			t = "<thead";
			t += ExtraAtribute(s, args);
			t += ">\n";
			level++;
			t += space() + "<tr>\n";
			level++;

			/* Doar atunci cand nr de argumente sunt <= cu nr de parametri introdusi, altfel eroare!!! */
			if (args <= size) {
				for (i = 0; i < args; i++) {
					t += space() + "<th>" + s->parameters[i] + "</th>\n";
				}
			}

			level--;
			t += space() + "</tr>\n";			
			level--;
			t += space() + "</thead>";
		} else {
			t = "<thead";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</thead>";
		  };		
	}

	if (strcmp(s->keyword, "title") == 0) {
		if (!EroareParametri(s, 1)) {
			t = "<title>";
			t += s->parameters[0];
			t += "</title>";
		}		
	}

	if (strcmp(s->keyword, "tr") == 0) {
		if (!EroareParametri(s, args)) {
			t = "<tr>\n";
			level++;

			/* Doar atunci cand nr de argumente sunt <= cu nr de parametri introdusi, altfel eroare!!! */
			if (args <= size) {
				for (i = 0; i < args; i++) {
					t += space() + "<th>" + s->parameters[i] + "</th>\n";
				}
			}

			level--;
			t += space() + "</tr>";
		} else {
			t = "<tr";
			t += ExtraAtribute(s, 0);
			t += ">";
			t += ExtraStatement(s, 0);
			t += space() + "</tr>";
		  };
	}

	return t;
}

void Compiler::PushStatement(Statement *s, string h)
{
	/* Fara atributul LANG */
	if ((s->attribute & ATTR_LANG) == 0) {
		if ((s->attribute & ATTR_HEAD) > 0) head.push_back(h); else body.push_back(h);
	}	
}

bool Compiler::EroareParametri(Statement *s, int n)
{
	int size = s->parameters.size();
	if (size == 0) return true;

	if (size < n) {
		printf("Functia '%s' trebuie sa aiba minim %i parametri. Am gasit doar %i !!!\n", s->keyword, n, size);
		return true;
	}

	return false;
}

Compiler::~Compiler()
{
	head.clear();
	body.clear();
}