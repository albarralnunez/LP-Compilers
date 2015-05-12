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


//-----------------------------------------------
// Definició font
//-----------------------------------------------

struct Font {
  int radi;
  int alt;
  string col;
  Font(AST *a) {
    radi = atoi(child(a, 0)->kind.c_str());
    alt = atoi(child(a, 1)->kind.c_str());
    col = child(a, 2)->kind;
  }
};


//-----------------------------------------------
// Càlcul àrea
//-----------------------------------------------

const double INC = sin(45.0 * PI / 180.0);

inline int inclina(int type, int inc) {
  if (type == ABS1) return min(inc+1, 1);
  else if (type == ABS2) return max(inc-1, -1);
  return 0;
}

double calcArea(AST *a, int inc, int fac) {
  if (a->type == CO) {
    Font f(a);                               // definicio: [ a, b, c ]
    if (inc) {
      double altura = INC*f.alt;             // altura font * sin 45º
      double base_2 = f.radi;                // radi font
      return fac*altura*base_2;              // area triangle: (base*altura*fac) / 2
    } else {
      double radi = f.radi;                  // radi font
      return PI*radi*radi;                   // area cercle: PI r^2
    }
  } else if (a->type == ID) {
    return calcArea(findFont(a->kind), inc, fac);
  } else if (a->type == MULT) {
    return calcArea(child(a, 1), inc, fac*atoi(child(a, 0)->kind.c_str()));
  } else if (a->type == ORD0 || a->type == ABS0) {
    double area1 = calcArea(child(a, 0), inc, fac);
    double area2 = calcArea(child(a, 1), inc, fac);
    return area1+area2;
  } else if (a->type == ABS1 || a->type == ABS2) {
    double area1 = calcArea(child(a, 0), inc, fac);
    double area2 = calcArea(child(a, 1), inclina(a->type, inc), fac);
    return area1+area2;
  }
  return -1.0;
}

double calcArea(AST *a) {
  return calcArea(a, 0, 1);
}


//-----------------------------------------------
// Càlcul altura
//-----------------------------------------------

double calcAltura(AST *a, int inc, int fac) {
  if (a->type == CO) {
    Font f(a);
    double altura = inc ? INC*f.alt : f.alt;
    return altura*fac;
  } else if (a->type == ID) {
    return calcAltura(findFont(a->kind), inc, fac);
  } else if (a->type == MULT) {
    return calcAltura(child(a, 1), inc, fac*atoi(child(a, 0)->kind.c_str()));
  } else if (a->type == ORD0 || a->type == ABS0) {
    double alt1 = calcAltura(child(a, 0), inc, fac);
    double alt2 = calcAltura(child(a, 1), inc, fac);
    return max(alt1, alt2);
  } else if (a->type == ABS1 || a->type == ABS2) {
    double alt1 = calcAltura(child(a, 0), inc, fac);
    double alt2 = calcAltura(child(a, 1), inclina(a->type, inc), fac);
    return max(alt1, alt2);
  }
  return -1.0;
}

double calcAltura(AST *a) {
  return calcAltura(a, 0, 1);
}


//-----------------------------------------------
// Evalua arbre
//-----------------------------------------------

void eval() {
  AST *a = root->down->down;
  while (a != NULL) {
    if (a->type==AREA) cout << "area " << calcArea(a->down) << endl;
    else if (a->type==ALTU) cout << "altura " << calcAltura(a->down) << endl;
    a = a->right;
  }
}

int main() {
  root = NULL;
  ANTLR(fonts(&root), stdin);
  ASTPrint(root);
  eval();
}
>>

#lexclass START
#token PLAYFONT "PLAY"

#token ABS0 "\|"
#token ABS1 "\/"
#token ABS2 "\\"
#token ORD0 "\+"
#token MULT "\*"
#token MOVE "\="

#token AREA "area"
#token ALTU "altu"

#token PO "\("
#token PC "\)"
#token CO "\["
#token CC "\]"
#token COMA "\,"

#token BLAU "blau"
#token VERM "vermell"
#token GROC "groc"
#token VERD "verd"

#token ON "on"
#token OFF "off"

#token NUM "[0-9]+"
#token ID "[A-Za-z][A-Za-z0-9]*"

#token SPACE "[\ \n]" << zzskip();>>


fonts: defs PLAYFONT! play <<#0=createASTlist(_sibling);>> ;

defs: (defs_rule)* <<#0=createASTlist(_sibling);>> ;
play: (play_rule)* <<#0=createASTlist(_sibling);>> ;

defs_rule: (ID MOVE^ | AREA^ | ALTU^) font_eval ;
font_eval: font_abs ((ABS0^ | ABS1^ | ABS2^) font_abs)* ;
font_abs: font_ord (ORD0^ font_ord)* ;
font_ord: font_def | NUM MULT^ font_ord | PO! font_eval PC! ;
font_def: CO^ NUM COMA! NUM COMA! font_color CC! | ID ;
font_color: VERD | BLAU | VERM | GROC ;

play_rule: NUM (ON^ | OFF^) ID;




