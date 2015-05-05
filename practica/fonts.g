#header
<<
#include <string>
#include <iostream>
#include <map>
using namespace std;

const double PI  =3.141592653589793238463;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as,attr,ttype,textt) as=createASTnode(attr,ttype,textt)
AST* createASTnode(Attrib* attr,int ttype, char *textt);
>>

<<
#include <cstdlib>
#include <cmath>

//global structures
AST *root;


// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
    attr->kind = text;
    attr->text = "";
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind; 
  as->text = attr->text;
  as->right = NULL; 
  as->down = NULL;
  return as;
}


/// create a new "list" AST node with one element
AST* createASTlist(AST *child) {
 AST *as=new AST;
 as->kind="list";
 as->right=NULL;
 as->down=child;
 return as;
}

AST *findFont(string id) {
  AST *n = root->down->down;
  while (n != NULL and (n->kind != "=" or n->down->kind != id)) n = n->right;
  if (n == NULL) {cout << "NOT FOUND: " << id << " " << endl;return NULL;}
  return n->down->right;
}

/// get nth child of a tree. Count starts at 0.
/// if no such child, returns NULL
AST* child(AST *a,int n) {
AST *c=a->down;
for (int i=0; c!=NULL && i<n; i++) c=c->right;
return c;
}



/// print AST, recursively, with indentation
void ASTPrintIndent(AST *a,string s)
{
  if (a==NULL) return;

  cout<<a->kind;
  if (a->text!="") cout<<"("<<a->text<<")";
  cout<<endl;

  AST *i = a->down;
  while (i!=NULL && i->right!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"  |"+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }
  
  if (i!=NULL) {
      cout<<s+"  \\__";
      ASTPrintIndent(i,s+"   "+string(i->kind.size()+i->text.size(),' '));
      i=i->right;
  }
}

/// print AST 
void ASTPrint(AST *a)
{
  while (a!=NULL) {
    cout<<" ";
    ASTPrintIndent(a,"");
    a=a->right;
  }
}


int main() {
  root = NULL;
  ANTLR(fonts(&root), stdin);
  ASTPrint(root);
// poseu aquí la vostra crida per avaluar les instruccions
}
>>

#lexclass START
#token SPACE    "[\ \n]" << zzskip();>>
#token COM      "\,"
#token PAROP    "\("
#token PARCL    "\)"
#token FONTOP   "\["
#token FONTCL   "\]"
#token ASS      "\="
#token MUL	    "\*"
#token PLUS	    "\+"
#token ADD	    "\|"
#token ADDRL    "\\"
#token ADDRR	"\/"
#token INT	    "[0-9]+"
#token PLAYFONT "PLAY"
#token ARE      "area"
#token ALT      "altu"
#token BL       "blau"
#token VERM     "vermell"
#token GR       "groc"
#token VERD     "verd"
#token ON       "on"
#token OFF      "off"
#token VAR      "[a-zA-Z]+[0-9]*"

fonts           : defs PLAYFONT! play <<#0=createASTlist(_sibling);>>;

play            : (instrPl)* <<#0=createASTlist(_sibling);>>;

defs            : (instDef)* <<#0=createASTlist(_sibling);>>;

instDef         : (VAR ASS^ expr)
                | (ALT^ expr) 
                | (ARE^ expr);

instrPl         : (INT (ON^ | OFF^) VAR);

literal         : font | VAR;

//First dig. represents Term group, second dig. the lvl of priority
term2p          : INT (MUL^ var|); //TEST PARE
term1p          : literal ((ADDRL^ | ADDRR^| ADD^) var|); //TEST PARE
term2           : INT (MUL^ literal)*; //TEST PARE
term1           : literal ((ADDRL^ | ADDRR^| ADD^) literal)*; //TEST PARE
var             : (PAROP! (term1 | term2) PARCL!) | (term1p | term2p);
expr            : var (PLUS^ var)*;

color           : BL
                | VERM
                | GR
                | VERD;

font            : FONTOP^ INT COM! INT COM! color FONTCL!;
