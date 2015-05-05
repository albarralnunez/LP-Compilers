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
#define SPACE 2
#define COM 3
#define PAROP 4
#define PARCL 5
#define FONTOP 6
#define FONTCL 7
#define ASS 8
#define MUL 9
#define PLUS 10
#define ADD 11
#define ADDRL 12
#define ADDRR 13
#define INT 14
#define PLAYFONT 15
#define ARE 16
#define ALT 17
#define BL 18
#define VERM 19
#define GR 20
#define VERD 21
#define ON 22
#define OFF 23
#define VAR 24

#ifdef __USE_PROTOS
void fonts(AST**_root);
#else
extern void fonts();
#endif

#ifdef __USE_PROTOS
void play(AST**_root);
#else
extern void play();
#endif

#ifdef __USE_PROTOS
void defs(AST**_root);
#else
extern void defs();
#endif

#ifdef __USE_PROTOS
void instDef(AST**_root);
#else
extern void instDef();
#endif

#ifdef __USE_PROTOS
void instrPl(AST**_root);
#else
extern void instrPl();
#endif

#ifdef __USE_PROTOS
void literal(AST**_root);
#else
extern void literal();
#endif

#ifdef __USE_PROTOS
void term2p(AST**_root);
#else
extern void term2p();
#endif

#ifdef __USE_PROTOS
void term1p(AST**_root);
#else
extern void term1p();
#endif

#ifdef __USE_PROTOS
void term2(AST**_root);
#else
extern void term2();
#endif

#ifdef __USE_PROTOS
void term1(AST**_root);
#else
extern void term1();
#endif

#ifdef __USE_PROTOS
void var(AST**_root);
#else
extern void var();
#endif

#ifdef __USE_PROTOS
void expr(AST**_root);
#else
extern void expr();
#endif

#ifdef __USE_PROTOS
void color(AST**_root);
#else
extern void color();
#endif

#ifdef __USE_PROTOS
void font(AST**_root);
#else
extern void font();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType setwd1[];
extern SetWordType zzerr5[];
extern SetWordType zzerr6[];
extern SetWordType zzerr7[];
extern SetWordType zzerr8[];
extern SetWordType setwd2[];
extern SetWordType zzerr9[];
extern SetWordType zzerr10[];
extern SetWordType zzerr11[];
extern SetWordType setwd3[];
