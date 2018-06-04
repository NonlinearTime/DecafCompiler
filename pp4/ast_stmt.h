/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp3: You will need to extend the Stmt classes to implement
 * semantic analysis for rules pertaining to statements.
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"
#include "ast_signaltable.h"

class Decl;
class VarDecl;
class Expr;
  
class Program : public Node
{
  protected:
     List<Decl*> *decls;
     
  public:
     Program(List<Decl*> *declList);
     static SignalTable *gStable;
     void Check();
     void Emit();
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {sTable = new SignalTable;}
     Stmt(yyltype loc) : Node(loc) {sTable = new SignalTable;}
     SignalTable *sTable;

    virtual void creatStable() = 0;
    virtual bool check() = 0;
    virtual int GetMemBytes() = 0;
    virtual Location* Emit(CodeGenerator *cg) = 0;
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    void creatStable();
    bool check();

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

  
class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;
  
  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);

    virtual void creatStable() = 0;
    virtual bool check() = 0;
    virtual Location* Emit(CodeGenerator* cg) = 0;
    virtual int GetMemBytes() = 0;
};

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}

    virtual void creatStable() = 0;
    virtual bool check() = 0;
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    void creatStable() ;
    bool check();

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    void creatStable();
    bool check();

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    void creatStable();
    bool check();

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class CaseStmt : public Stmt
{
  protected:
    Expr *label;
    List<Stmt*> *stmtList;
  public:
    CaseStmt(Expr *l, List<Stmt*> *stmtL);
    void creatStable();
    bool check() {return true;}

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class DefaultStmt : public Stmt
{
  protected:
    List<Stmt*> *stmtList;
  public:
    DefaultStmt(List<Stmt*> *stmtL);
    void creatStable();
    bool check();

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};


class SwitchStmt : public Stmt
{
  protected:
    Expr *expr;
    List<CaseStmt*> *caseList;
    DefaultStmt *defaultStmt;
  public:
    SwitchStmt(Expr *e, List<CaseStmt*> *caseL,  DefaultStmt *Ds);
    void creatStable();
    bool check();

    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class BreakStmt : public Stmt 
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    void creatStable();
    bool check() {return true;}
    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
  public:
    ReturnStmt(yyltype loc, Expr *expr);
    void creatStable();
    bool check();
    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
    void creatStable();
    bool check();
    Location* Emit(CodeGenerator* cg) ;
    int GetMemBytes();
};


#endif
