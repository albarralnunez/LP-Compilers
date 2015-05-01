#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: fonts.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define PLAYFONT 2
#define SPACE 3
#define COM 4
#define PAROP 5
#define PARCL 6
#define FONTOP 7
#define FONTCL 8
#define ASS 9
#define ARE 10
#define ALT 11
#define ADD 12
#define ADDRL 13
#define ADDRR 14
#define PLUS 15
#define MUL 16
#define INT 17
#define VAR 18
#define BL 19
#define VERM 20
#define GR 21
#define VERD 22
#define ON 23
#define OFF 24

#ifdef __USE_PROTOS
void play(AST**_root);
#else
extern void play();
#endif

#ifdef __USE_PROTOS
void color(AST**_root);
#else
extern void color();
#endif

#ifdef __USE_PROTOS
void inst(AST**_root);
#else
extern void inst();
#endif

#ifdef __USE_PROTOS
void exprp(AST**_root);
#else
extern void exprp();
#endif

#ifdef __USE_PROTOS
void exprop(AST**_root);
#else
extern void exprop();
#endif

#ifdef __USE_PROTOS
void exprmu(AST**_root);
#else
extern void exprmu();
#endif

#ifdef __USE_PROTOS
void font(AST**_root);
#else
extern void font();
#endif

#ifdef __USE_PROTOS
void value(AST**_root);
#else
extern void value();
#endif

#ifdef __USE_PROTOS
void defs(AST**_root);
#else
extern void defs();
#endif

#ifdef __USE_PROTOS
void fonts(AST**_root);
#else
extern void fonts();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType setwd1[];
extern SetWordType zzerr5[];
extern SetWordType setwd2[];
