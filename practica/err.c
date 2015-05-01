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
	/* 02 */	"PLAYFONT",
	/* 03 */	"SPACE",
	/* 04 */	"COM",
	/* 05 */	"PAROP",
	/* 06 */	"PARCL",
	/* 07 */	"FONTOP",
	/* 08 */	"FONTCL",
	/* 09 */	"ASS",
	/* 10 */	"ARE",
	/* 11 */	"ALT",
	/* 12 */	"ADD",
	/* 13 */	"ADDRL",
	/* 14 */	"ADDRR",
	/* 15 */	"PLUS",
	/* 16 */	"MUL",
	/* 17 */	"INT",
	/* 18 */	"VAR",
	/* 19 */	"BL",
	/* 20 */	"VERM",
	/* 21 */	"GR",
	/* 22 */	"VERD",
	/* 23 */	"ON",
	/* 24 */	"OFF"
};
SetWordType zzerr1[4] = {0x0,0x0,0x80,0x1};
SetWordType zzerr2[4] = {0x0,0x0,0x78,0x0};
SetWordType zzerr3[4] = {0x0,0xc,0x0,0x0};
SetWordType zzerr4[4] = {0xa0,0x0,0x0,0x0};
SetWordType setwd1[25] = {0x0,0x5,0xe8,0x0,0x0,0x0,0x0,
	0x0,0x2,0x0,0xe8,0xe8,0xd0,0xd0,0xd0,
	0xe0,0x80,0x0,0xe8,0x0,0x0,0x0,0x0,
	0x0,0x0};
SetWordType zzerr5[4] = {0x0,0xc,0x4,0x0};
SetWordType setwd2[25] = {0x0,0x8,0x5,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x3,0x3,0x1,0x1,0x1,
	0x1,0x1,0x0,0x3,0x0,0x0,0x0,0x0,
	0x0,0x0};
