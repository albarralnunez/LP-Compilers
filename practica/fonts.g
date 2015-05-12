#header
<<
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

const double PI  =3.141592653589793238463;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
  int type;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text; int type;
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
    attr->type = type;
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind; 
  as->text = attr->text;
  as->type = attr->type;
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

//global stack, almacena los angulos
vector<double> ang;

double getAng() {
    double res = ang[ang.size()-1];
    for (int i = ang.size()-2; i >= 0; i--){
        if (res != ang[i]) res += ang[i];  
    }
    return res;
}

double calcArea(AST *a, double fac) {
    double aux_res;
    if (a->type == VAR) {
        return calcArea(findFont(a->kind), fac);
    }
    else if (a->kind == "+" || a->kind == "|" ) {
        return calcArea(a->down, fac) + calcArea(a->down->right, fac);
    }
    else if (a->kind == "\\") {
        double aux1 = calcArea(a->down, fac);
        ang.push_back(-45);
        double aux2 = calcArea(a->down->right, fac);
        ang.pop_back();
        return aux1+aux2;
    }
    else if(a->kind == "/") {
        double aux1 = calcArea(a->down, fac);
        ang.push_back(45);
        double aux2 = calcArea(a->down->right, fac);
        ang.pop_back();
        return aux1+aux2;
    }
    else if(a->kind == "*") {
        return calcArea(a->down->right, atof(a->down->kind.c_str()) * fac);
    }
    // else if (a->kind == "[") {
        //usar fac en la altura
        double h = atof(a->down->right->kind.c_str())*fac;
        double r = atof(a->down->kind.c_str());
        return (getAng() == 0) 
            ? PI*pow(r,2)
            : sqrt(pow(h,2)-pow(r,2))*r;
    //return atof(a->down->kind.c_str());
    //}
    //fail
}

double calcAltura(AST *a, double fac) {
    double aux_res;
    if (a->type == VAR) {
        return calcAltura(findFont(a->kind), fac);
    }
    else if (a->kind == "+" || a->kind == "|" ) {
        return max(calcAltura(a->down, fac), calcAltura(a->down->right, fac));
    }
    else if (a->kind == "\\") {
        double aux1 = calcAltura(a->down, fac);
        ang.push_back(-45);
        double aux2 = calcAltura(a->down->right, fac);
        ang.pop_back();
        return max(aux1,aux2);
    }
    else if(a->kind == "/") {
        double aux1 = calcAltura(a->down, fac);
        ang.push_back(45);
        double aux2 = calcAltura(a->down->right, fac);
        ang.pop_back();
        return max(aux1,aux2);
    }
    else if(a->kind == "*") {
        return calcAltura(a->down->right, atof(a->down->kind.c_str()) * fac);
    }
    // else if (a->kind == "[") {
        //usar fac en la altura
        double res = (getAng() == 0)
            ? atof(a->down->right->kind.c_str())*fac
            : atof(a->down->right->kind.c_str())*fac*sin(PI/4);
        return res;
    //return atof(a->down->kind.c_str());
    //}
    //fail
}

void printa(AST *a) {
    ang = vector<double>(1,0);
	if (a->kind == "area") {
		cout << "Area: " << calcArea(a->down, 1) << endl; // area que volem cal
	}
	else if (a->kind == "altu") {
	   cout << "Altura: " << calcAltura(a->down, 1) << endl; // altura que volem cal
	}
	if (a->right != NULL) printa(a->right);
}

int main() {
  root = NULL;
  ANTLR(fonts(&root), stdin);
  ASTPrint(root);
  printa(root->down->down);
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

term2           : INT MUL^ var;
term1           : var (PLUS^ var)*;
expr            : term1 ((ADDRL^ | ADDRR^| ADD^) term1)*;
var             : (PAROP! expr PARCL!)
                | term2
                | literal;

color           : BL
                | VERM
                | GR
                | VERD;

font            : FONTOP^ INT COM! INT COM! color FONTCL!;
