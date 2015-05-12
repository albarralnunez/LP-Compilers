/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   antlr -gt fonts.g
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

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
#define GENAST

#include "ast.h"

#define zzSET_SIZE 4
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#include "ast.c"
zzASTgvars

ANTLR_INFO

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
    : pow((pow(h,2)-pow(r,2)),1/2)*r;
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

void
#ifdef __USE_PROTOS
fonts(AST**_root)
#else
fonts(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  defs(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(PLAYFONT);  zzCONSUME;
  play(zzSTR); zzlink(_root, &_sibling, &_tail);
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x1);
  }
}

void
#ifdef __USE_PROTOS
play(AST**_root)
#else
play(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==INT) ) {
      instrPl(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x2);
  }
}

void
#ifdef __USE_PROTOS
defs(AST**_root)
#else
defs(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (setwd1[LA(1)]&0x4) ) {
      instDef(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x8);
  }
}

void
#ifdef __USE_PROTOS
instDef(AST**_root)
#else
instDef(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==VAR) ) {
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
      zzmatch(VAR); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzmatch(ASS); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
      expr(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzEXIT(zztasp2);
      }
    }
  }
  else {
    if ( (LA(1)==ALT) ) {
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
        zzmatch(ALT); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
        expr(zzSTR); zzlink(_root, &_sibling, &_tail);
        zzEXIT(zztasp2);
        }
      }
    }
    else {
      if ( (LA(1)==ARE) ) {
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
          zzmatch(ARE); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
          expr(zzSTR); zzlink(_root, &_sibling, &_tail);
          zzEXIT(zztasp2);
          }
        }
      }
      else {zzFAIL(1,zzerr1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x10);
  }
}

void
#ifdef __USE_PROTOS
instrPl(AST**_root)
#else
instrPl(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    zzmatch(INT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    {
      zzBLOCK(zztasp3);
      zzMake0;
      {
      if ( (LA(1)==ON) ) {
        zzmatch(ON); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {
        if ( (LA(1)==OFF) ) {
          zzmatch(OFF); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {zzFAIL(1,zzerr2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
      zzEXIT(zztasp3);
      }
    }
    zzmatch(VAR); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x20);
  }
}

void
#ifdef __USE_PROTOS
literal(AST**_root)
#else
literal(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==FONTOP) ) {
    font(zzSTR); zzlink(_root, &_sibling, &_tail);
  }
  else {
    if ( (LA(1)==VAR) ) {
      zzmatch(VAR); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    }
    else {zzFAIL(1,zzerr3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x40);
  }
}

void
#ifdef __USE_PROTOS
term2(AST**_root)
#else
term2(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(INT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(MUL); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  var(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x80);
  }
}

void
#ifdef __USE_PROTOS
term1(AST**_root)
#else
term1(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  var(zzSTR); zzlink(_root, &_sibling, &_tail);
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==PLUS) ) {
      zzmatch(PLUS); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
      var(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x1);
  }
}

void
#ifdef __USE_PROTOS
expr(AST**_root)
#else
expr(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  term1(zzSTR); zzlink(_root, &_sibling, &_tail);
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (setwd2[LA(1)]&0x2) ) {
      {
        zzBLOCK(zztasp3);
        zzMake0;
        {
        if ( (LA(1)==ADDRL) ) {
          zzmatch(ADDRL); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {
          if ( (LA(1)==ADDRR) ) {
            zzmatch(ADDRR); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
          }
          else {
            if ( (LA(1)==ADD) ) {
              zzmatch(ADD); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
            }
            else {zzFAIL(1,zzerr4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
        zzEXIT(zztasp3);
        }
      }
      term1(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x4);
  }
}

void
#ifdef __USE_PROTOS
var(AST**_root)
#else
var(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==PAROP) ) {
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
      zzmatch(PAROP);  zzCONSUME;
      expr(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzmatch(PARCL);  zzCONSUME;
      zzEXIT(zztasp2);
      }
    }
  }
  else {
    if ( (LA(1)==INT) ) {
      term2(zzSTR); zzlink(_root, &_sibling, &_tail);
    }
    else {
      if ( (setwd2[LA(1)]&0x8) ) {
        literal(zzSTR); zzlink(_root, &_sibling, &_tail);
      }
      else {zzFAIL(1,zzerr5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x10);
  }
}

void
#ifdef __USE_PROTOS
color(AST**_root)
#else
color(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==BL) ) {
    zzmatch(BL); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  }
  else {
    if ( (LA(1)==VERM) ) {
      zzmatch(VERM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    }
    else {
      if ( (LA(1)==GR) ) {
        zzmatch(GR); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {
        if ( (LA(1)==VERD) ) {
          zzmatch(VERD); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {zzFAIL(1,zzerr6,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x20);
  }
}

void
#ifdef __USE_PROTOS
font(AST**_root)
#else
font(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(FONTOP); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(INT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(COM);  zzCONSUME;
  zzmatch(INT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(COM);  zzCONSUME;
  color(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(FONTCL);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x40);
  }
}
