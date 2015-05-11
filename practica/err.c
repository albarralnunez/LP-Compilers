/*
 * A n t l r  S e t s / E r r o r  F i l e  H e a d e r
 *
 * Generated from: fonts.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
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
#define zzSET_SIZE 4
#include "antlr.h"
#include "ast.h"
#include "tokens.h"
#include "dlgdef.h"
#include "err.h"

ANTLRChar *zztokens[25]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"SPACE",
	/* 03 */	"COM",
	/* 04 */	"PAROP",
	/* 05 */	"PARCL",
	/* 06 */	"FONTOP",
	/* 07 */	"FONTCL",
	/* 08 */	"ASS",
	/* 09 */	"MUL",
	/* 10 */	"PLUS",
	/* 11 */	"ADD",
	/* 12 */	"ADDRL",
	/* 13 */	"ADDRR",
	/* 14 */	"INT",
	/* 15 */	"PLAYFONT",
	/* 16 */	"ARE",
	/* 17 */	"ALT",
	/* 18 */	"BL",
	/* 19 */	"VERM",
	/* 20 */	"GR",
	/* 21 */	"VERD",
	/* 22 */	"ON",
	/* 23 */	"OFF",
	/* 24 */	"VAR"
};
SetWordType zzerr1[4] = {0x0,0x0,0x3,0x1};
SetWordType zzerr2[4] = {0x0,0x0,0xc0,0x0};
SetWordType zzerr3[4] = {0x40,0x0,0x0,0x1};
SetWordType setwd1[25] = {0x0,0x23,0x0,0x0,0x0,0xc0,0x0,
	0x0,0x0,0x0,0xc0,0xc0,0xc0,0xc0,0x20,
	0xd8,0xd4,0xd4,0x0,0x0,0x0,0x0,0x0,
	0x0,0xd4};
SetWordType zzerr4[4] = {0x0,0x38,0x0,0x0};
SetWordType zzerr5[4] = {0x50,0x40,0x0,0x1};
SetWordType zzerr6[4] = {0x0,0x0,0x3c,0x0};
SetWordType setwd2[25] = {0x0,0x0,0x0,0x0,0x0,0x55,0x8,
	0x20,0x0,0x0,0x50,0x53,0x53,0x53,0x0,
	0x55,0x55,0x55,0x0,0x0,0x0,0x0,0x0,
	0x0,0x5d};
