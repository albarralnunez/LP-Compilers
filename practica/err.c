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
	/* 09 */	"ADD",
	/* 10 */	"ADDRL",
	/* 11 */	"ADDRR",
	/* 12 */	"PLUS",
	/* 13 */	"MUL",
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
SetWordType zzerr1[4] = {0x0,0x0,0x3c,0x0};
SetWordType zzerr2[4] = {0x40,0x0,0x0,0x1};
SetWordType zzerr3[4] = {0x40,0x40,0x0,0x1};
SetWordType zzerr4[4] = {0x0,0xe,0x0,0x0};
SetWordType setwd1[25] = {0x0,0x0,0x0,0x0,0x0,0x0,0x8,
	0x1,0x0,0x76,0x76,0x76,0xb6,0x36,0x0,
	0xb6,0xb6,0xb6,0x0,0x0,0x0,0x0,0x0,
	0x0,0xbe};
SetWordType zzerr5[4] = {0x0,0x0,0xc0,0x0};
SetWordType setwd2[25] = {0x0,0x30,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0xb,0x7,0x7,0x0,0x0,0x0,0x0,0x0,
	0x0,0x7};
