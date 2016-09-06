#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

char *trim(char *c);
string trim(const string& StrToTrim);
void setAttribute(int &attr, int val);
void unsetAttribute(int &attr, int val);

struct Keyword {
	char *name;
	int   attribute;
};

struct SmartAttributeNonGlobal {
	char *tag;
	int idAttr;	
	char *attr;
};

struct Token {
	int   type;
	char *token;
};

struct SmartTagAttribute {
	/* Atribute cu prioritate la scriere atat pt tag-urile standard cat si cele cu parametri specifici */
	string id;
	vector<string> clasa;
	vector<string> data;
	string title;
	bool hidden;
	string lang;
	
	/* Atribute pt tag-urile cu parametri specifici(vor fi interpretati de la caz la caz) */
	string target;
	vector<int> x;
	vector<int> y;
	vector<int> width;
	vector<int> height;
	bool get;
	bool post;
	string url;

	/* Stocam clasele pentru Responsive Web Design */
	vector<string> responsive; 

	/* Atribute in format standard proprietate="valoare" */
	vector<string> normal;
};

struct Statement {
	int   type;
	char *keyword;
	int   attribute;
	vector<string> parameters;
	char *block;
	char *code;
	vector<Statement> statements;
	SmartTagAttribute smart;
	bool compile;
	int args;
};

#define ATTR_HTML5_TAG		   1
#define ATTR_SPECIAL           2
#define ATTR_MAIN              4
#define ATTR_NATIVE_CODE       8
#define ATTR_NO_PARAM          16
#define ATTR_NO_ATTRIBUTES     32
#define ATTR_NO_BLOCK          64
#define ATTR_NO_BLOCK_PARSE    128
#define ATTR_NO_CLOSING_TAG    256
#define ATTR_HEAD              512
#define ATTR_SINGLE_PARAM      1024
#define ATTR_LANG              2048
#define ATTR_SVG               4096 
#define ATTR_DEPRECATED5       8192 /* Tag care numai exista in HTML5 */
#define ATTR_XML_CLOSE         16384 /* /> */

#define HTML5                  ATTR_HTML5_TAG
#define HTML5_NO_CLOSING       ATTR_HTML5_TAG + ATTR_NO_CLOSING_TAG

enum TOKEN_TYPE { 
	FINISH, HTML5_COMMENT /* // sau /* */, INTERNAL_COMMENT /* ; */, KEYWORD, PARAMETERS /* () */,
	SEPARATOR /* , */, BLOCK /* {} */, CODE /* {{ }} */, ARRAY /* [] */, STRING /* "" */, NUMBER, STATEMENT
};

enum TAG_ATRIBUTE_TYPE {
	PROPERTY_VALUE, ID, CLASS, GET, POST, URL, WIDTH, HEIGHT, X, Y, METHOD, TARGET
};

static struct Keyword keywords[] = {
	{ "a",                ATTR_SPECIAL },
	{ "abbr",             ATTR_SPECIAL },
	{ "acronym",          HTML5 + ATTR_DEPRECATED5 },
	{ "address",          HTML5 },
	{ "animate",          HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "animatecolor",     HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "animatemotion",    HTML5 + ATTR_SVG },
	{ "animatetransform", HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "area",             HTML5 },
	{ "article",          HTML5 },
	{ "aside",            HTML5 },
	{ "audio",            HTML5 },
	{ "author",           ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM },
	{ "b",                HTML5 },
	{ "base",             ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_BLOCK },
	{ "bdi",              HTML5 },
	{ "bdo",              HTML5 },
	{ "big",              HTML5 + ATTR_DEPRECATED5 },
	{ "blockquote",       ATTR_SPECIAL },	
	{ "br",               ATTR_SPECIAL + ATTR_NO_ATTRIBUTES + ATTR_NO_PARAM + ATTR_NO_BLOCK + ATTR_NO_CLOSING_TAG },
	{ "button",           ATTR_SPECIAL + ATTR_NO_CLOSING_TAG },
	{ "canvas",           HTML5 },	
	{ "caption",          ATTR_SPECIAL + ATTR_NO_BLOCK },
	{ "center",           HTML5 + ATTR_DEPRECATED5 },
	{ "charset",          ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM },
	{ "circle",           HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "cite",             HTML5 },
	{ "clippath",         HTML5 + ATTR_SVG },
	{ "code",             HTML5 },
	{ "col",              HTML5_NO_CLOSING },
	{ "column",           ATTR_SPECIAL },
	{ "colgroup",         HTML5 },
	{ "cursor",           HTML5 + ATTR_SVG },
	{ "datalist",         HTML5 },
	{ "dd",               HTML5 },
	{ "defs",             HTML5 + ATTR_SVG },
	{ "del",              HTML5 },
	{ "desc",             HTML5 + ATTR_SVG },
	{ "description",      ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM },
	{ "details",          HTML5 },
	{ "dfn",              HTML5 },
	{ "dialog",           HTML5 },
	{ "div",              HTML5 },
	{ "dir",              HTML5 + ATTR_DEPRECATED5 },
	{ "dl" ,              HTML5 },
	{ "dt",               HTML5 },
	{ "ellipse",          HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "em",               HTML5 },
	{ "embed",            HTML5 },
	{ "fieldset",         HTML5 },
	{ "figure",           HTML5 },
	{ "figcaption",       HTML5 },
	{ "font",             HTML5 + ATTR_DEPRECATED5 },
	{ "font-face",        HTML5 + ATTR_SVG },
	{ "font-face-name",   HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "font-face-src",    HTML5 + ATTR_SVG },
	{ "font-face-uri",    HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "footer",           HTML5 },
	{ "foreignobject",    HTML5 + ATTR_SVG },
	{ "form",             ATTR_SPECIAL },
	{ "frame",            HTML5_NO_CLOSING + ATTR_DEPRECATED5 },
	{ "frameset",         HTML5 + ATTR_DEPRECATED5 },
	{ "g",                HTML5 + ATTR_SVG },
	{ "generator",        ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK },
	{ "glyph",            HTML5 + ATTR_SVG },
	{ "h1",               HTML5 },
	{ "h2",               HTML5 },
	{ "h3",               HTML5 },
	{ "h4",               HTML5 },
	{ "h5",               HTML5 },
	{ "h6",               HTML5 },
	{ "header",           HTML5 },
	{ "hr",               ATTR_SPECIAL + ATTR_NO_ATTRIBUTES + ATTR_NO_PARAM + ATTR_NO_BLOCK + ATTR_NO_CLOSING_TAG },
	{ "html",             ATTR_SPECIAL + ATTR_NATIVE_CODE + ATTR_NO_ATTRIBUTES + ATTR_NO_PARAM },
	{ "i",                HTML5 },
	{ "image",            HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "img",              ATTR_SPECIAL + ATTR_NO_BLOCK + ATTR_NO_CLOSING_TAG },
	{ "input",            ATTR_SPECIAL + ATTR_NO_BLOCK + ATTR_NO_CLOSING_TAG },
	{ "ins",              HTML5 },
	{ "kbd",              HTML5 },
	{ "keywords",         ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM },
	{ "label",            ATTR_SPECIAL + ATTR_NO_BLOCK_PARSE },
	{ "lang",             ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM + ATTR_LANG },
	{ "legend",           ATTR_SPECIAL + ATTR_NO_BLOCK },
	{ "li",               HTML5 },
	{ "line",             HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "lineargradient",   HTML5 + ATTR_SVG },
	{ "link",             ATTR_SPECIAL + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM + ATTR_HEAD },	
	{ "main",             HTML5 },
	{ "map",              HTML5 },
	{ "mark",             HTML5 },
	{ "marker",           HTML5 + ATTR_SVG },
	{ "mask",             HTML5 + ATTR_SVG },
	{ "menu",             HTML5 },
	{ "menuitem",         HTML5 },
	{ "meta",             HTML5_NO_CLOSING + ATTR_HEAD + ATTR_NO_BLOCK },
	{ "meter",            HTML5 },
	{ "missing-glyph",    HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "mpath",            HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "nav",              HTML5 },
	{ "navbar",           ATTR_SPECIAL },
	{ "navbrand",         ATTR_SPECIAL },
	{ "navdheader",       ATTR_SPECIAL },
	{ "navdropdown",      ATTR_SPECIAL },
	{ "navheader",        ATTR_SPECIAL },
	{ "navitem",          ATTR_SPECIAL },
	{ "navlogo",          ATTR_SPECIAL },
	{ "navmenu",          ATTR_SPECIAL },
	{ "navseparator",     ATTR_SPECIAL },
	{ "navtext",          ATTR_SPECIAL },
	{ "noframes",         HTML5 + ATTR_DEPRECATED5 },
	{ "noscript",         HTML5 },
	{ "object",           HTML5 },
	{ "ol",               HTML5 },
	{ "optgroup",         ATTR_SPECIAL },
	{ "option",           ATTR_SPECIAL + ATTR_NO_BLOCK_PARSE },
	{ "output",           HTML5 },
	{ "p",                HTML5 },
	{ "param",            HTML5_NO_CLOSING },
	{ "path",             HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "pattern",          HTML5 + ATTR_SVG },
	{ "polygon",          HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "polyline",         HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "pre",              HTML5 },
	{ "progress",         HTML5 },
    { "q",                HTML5 },
	{ "radialgradient",   HTML5 + ATTR_SVG },
	{ "rect",             HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "row",              ATTR_SPECIAL },
	{ "rp",               HTML5 },
	{ "rt",               HTML5 },
	{ "ruby",             HTML5 },
	{ "s",                HTML5 },
	{ "samp",             HTML5 },
	{ "script",           HTML5 },
	{ "section",          HTML5 },
	{ "select",           HTML5 },
	{ "small",            HTML5 },
	{ "source",           HTML5_NO_CLOSING },
	{ "span",             HTML5 },
	{ "start",            ATTR_SPECIAL + ATTR_MAIN + ATTR_NO_ATTRIBUTES + ATTR_NO_PARAM },
	{ "stop",             HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "strong",           HTML5 },
	{ "strike",           HTML5 + ATTR_DEPRECATED5 },
	{ "style",            HTML5 + ATTR_HEAD },
	{ "sub",              HTML5 },
	{ "summary",          HTML5 },
	{ "sup",              HTML5 },
	{ "svg",              HTML5 },
	{ "switch",           HTML5 + ATTR_SVG },
	{ "symbol",           HTML5 + ATTR_SVG },
	{ "table",            ATTR_SPECIAL },
	{ "tbody",            ATTR_SPECIAL }, // doar pt args!!!
	{ "td",               HTML5 },
	{ "text",             HTML5 + ATTR_SVG },
	{ "textarea",         ATTR_SPECIAL },
	{ "textpath",         HTML5 + ATTR_SVG },
	{ "tfoot",            ATTR_SPECIAL },
	{ "th",               HTML5 },
	{ "thead",            ATTR_SPECIAL },
	{ "time",             HTML5 },
	{ "title",            ATTR_SPECIAL + ATTR_HEAD + ATTR_NO_ATTRIBUTES + ATTR_NO_BLOCK + ATTR_SINGLE_PARAM },
	{ "tr",               ATTR_SPECIAL },
	{ "track",            HTML5_NO_CLOSING },
	{ "tref",             HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "tspan",            HTML5 + ATTR_SVG },
	{ "tt",               HTML5 + ATTR_DEPRECATED5 },
	{ "u",                HTML5 },
	{ "ul",               HTML5 },
	{ "use",              HTML5 + ATTR_SVG + ATTR_XML_CLOSE },
	{ "var",              HTML5 },
	{ "video",            HTML5 },
	{ "wbr",              HTML5 }
};

/* Lista cu toate tag-urile care ar putea accepta atribute inteligente non-globale */
static struct SmartAttributeNonGlobal nonglobal[] = {
	{ "a",          URL,    "href" },
	{ "a",          TARGET, "target" },
	{ "applet",     URL,    "code" },
	{ "applet",     WIDTH,  "width" },
	{ "applet",     HEIGHT, "height" },
	{ "area",       URL,    "href" },
	{ "area",       TARGET, "target" },
	{ "base",       URL,    "href" },
	{ "base",       TARGET, "target" },	
	{ "blockquote", URL,    "cite" },
	{ "button",     URL,    "formaction" },
	{ "button",     METHOD, "formmethod" },
	{ "button",     TARGET, "formtarget" },
	{ "canvas",     WIDTH,  "width" },
	{ "canvas",     HEIGHT, "height" },
	{ "col",        WIDTH,  "width" },
	{ "colgroup",   WIDTH,  "width" },
	{ "del",        URL,    "cite" },
	{ "embed",      URL,    "src" },
	{ "embed",      WIDTH,  "width" },
	{ "embed",      HEIGHT, "height" },
	{ "form",       URL,    "action" },
	{ "form",       METHOD, "method" },
	{ "form",       TARGET, "target" },
	{ "frame",      URL,    "src" },
	{ "frame",      WIDTH,  "marginwidth" },
	{ "frame",      HEIGHT, "marginheight" },
	{ "iframe",     URL,    "src" },
	{ "iframe",     WIDTH,  "width" },
	{ "iframe",     HEIGHT, "height" },
	{ "img",        URL,    "src" },
	{ "img",        WIDTH,  "width" },
	{ "img",        HEIGHT, "height" },
	{ "input",      URL,    "formaction" },
	{ "input",      WIDTH,  "width" },
	{ "input",      HEIGHT, "height" },
	{ "input",      METHOD, "formmethod" },
	{ "input",      TARGET, "formtarget" },
	{ "ins",        URL,    "cite" },
	{ "link",       URL,    "href" },
	{ "link",       TARGET, "target" },
	{ "menuitem",   URL,    "icon" },
	{ "navbrand",   URL,    "href" },
	{ "navlogo",    URL,    "src" },
	{ "object",     URL,    "data" },
	{ "object",     WIDTH,  "width" },
	{ "object",     HEIGHT, "height" },
	{ "pre",        WIDTH,  "width" },
	{ "q",          URL,    "cite" },
	{ "script",     URL,    "src" },
	{ "source",     URL,    "src" },
	{ "table",      WIDTH,  "width" },
	{ "td",         WIDTH,  "width" },
	{ "td",         HEIGHT, "height" },
	{ "textarea",   WIDTH,  "cols" },
	{ "textarea",   HEIGHT, "rows" },
	{ "th",         WIDTH,  "width" },
	{ "th",         HEIGHT, "height" },
	{ "track",      URL,    "src" },
	{ "video",      URL,    "src" },
	{ "video",      WIDTH,  "width" },
	{ "video",      HEIGHT, "height" }
};

Keyword *FindKeyword(char *name);
SmartTagAttribute ParseSmartAttributes(vector<string> parametri, int start);
Token *GetTokenString(char* &prog);
void ParseMainParameters(vector<string> parametri);

class File
{
private:	
	FILE *f;
	char *filename; /* Nume fisier */
	char *program;  /* Continutul fisierului */	
	unsigned long file_size; /* Marimea fisier */ 

	/* Contine fiecare declaratie prelucrata pe fiecare componenta: keyword, parameters(optional), block definition sau comment */
	vector<Statement> statements;
public:
	File(char *filename);
	bool Open();
	bool Read();
	bool Parse();
	vector<Statement> Parse(char* &prog);
	vector<string> ParseParameters(char* &prog, char delimiter);	
	vector<Statement> Preprocess(vector<Token> date);
	unsigned long FileSize();
	Token *GetToken();
	Token *GetToken(char* &prog);
	//Token *GetTokenString(char* &prog);
	vector<Statement> GetStatements();
	void Print(vector<Statement> statements);
	~File();
};