/* File: ast_expr.h
 * ----------------
 * The Expr class and its subclasses are used to represent
 * expressions in the parse tree.  For each expression in the
 * language (add, call, New, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp3: You will need to extend the Expr classes to implement 
 * semantic analysis for rules pertaining to expressions.
 */


#ifndef _H_ast_expr
#define _H_ast_expr

#include "ast.h"
#include "ast_stmt.h"
#include "list.h"

class NamedType; // for new
class Type; // for NewArray


class Expr : public Stmt 
{
  public:
    Expr(yyltype loc) : Stmt(loc) {}
    Expr() : Stmt() {}
    virtual bool check() = 0;
    virtual void creatStable() = 0;
    virtual int GetExprType() = 0;
    virtual const char *GetExprName() = 0;
    virtual Type* GetResType() = 0;

    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetMemBytes() = 0;
};

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr
{
  public:
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return emptyExpr;}
    const char *GetExprName() {return "EmptyExpr";}
    Type* GetResType() {return NULL;}

    Location* Emit(CodeGenerator *cg) {return NULL;}
    int GetMemBytes() {return 0;};
};

class IntConstant : public Expr 
{
  protected:
    int value;
  
  public:
    IntConstant(yyltype loc, int val);
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return intConstant;}
    const char *GetExprName() {return "int";}
    Type* GetResType() {return new Type(GetExprName(),GetExprType());}
    
    Location* Emit(CodeGenerator *cg) {return cg->GenLoadConstant(value);}
    int GetMemBytes() {return 4;}
};

class DoubleConstant : public Expr 
{
  protected:
    double value;
    
  public:
    DoubleConstant(yyltype loc, double val);
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return doubleConstant;}
    const char *GetExprName() {return "double" ;}
    Type* GetResType() {return new Type(GetExprName(),GetExprType());}
    Location* Emit(CodeGenerator *cg) {Assert(0); return NULL;}
    int GetMemBytes() {return 4;}
};

class BoolConstant : public Expr 
{
  protected:
    bool value;
    
  public:
    BoolConstant(yyltype loc, bool val);
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return boolConstant;}
    const char *GetExprName() {return "bool";}
    Type* GetResType() {return new Type(GetExprName(),GetExprType());}
    Location* Emit(CodeGenerator *cg) {return cg->GenLoadConstant(value ? 1 : 0);}
    int GetMemBytes() {return 4;}
};

class StringConstant : public Expr 
{ 
  protected:
    char *value;
    
  public:
    StringConstant(yyltype loc, const char *val);
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return stringConstant;}
    const char *GetExprName() {return "string";}
    Type* GetResType() {return new Type(GetExprName(),GetExprType());}
    Location* Emit(CodeGenerator *cg) {return cg->GenLoadConstant(value);}
    int GetMemBytes() {return 4;}
};

class NullConstant: public Expr 
{
  public: 
    NullConstant(yyltype loc) : Expr(loc) {}
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return nullConstant;}
    const char *GetExprName() {return "null";}
    Type* GetResType() {return new Type(GetExprName(),GetExprType());}
    Location* Emit(CodeGenerator *cg) {return cg->GenLoadConstant(0);}
    int GetMemBytes() {return 4;}
};

class Operator : public Node 
{
  protected:
    char tokenString[4];
    
  public:
    Operator(yyltype loc, const char *tok);
    friend ostream& operator<<(ostream& out, Operator *o) { return out << o->tokenString; }
    void creatStable() {}
    const char * GetOperation() {return tokenString;}
 };
 
class CompoundExpr : public Expr
{
  protected:
    Operator *op;
    Expr *left, *right; // left will be NULL if unary
    
  public:
    CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
    CompoundExpr(Operator *op, Expr *rhs);  
    CompoundExpr(Expr *rhs, Operator *op); // for unary
    virtual void creatStable(); 
    virtual bool check();     
    virtual int GetExprType() = 0;
    virtual const char *GetExprName() = 0;
    virtual Type* GetResType();

    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetMemBytes() = 0;
};

class ArithmeticExpr : public CompoundExpr 
{
  public:
    ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    void creatStable(); 
    int GetExprType() {return arithmeticExpr;}  
    const char *GetExprName() {return op->GetOperation();}
    // bool check();
    // const char *GetResType();
    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

  private:
    Location * EmitUnary(CodeGenerator *cg);
    int GetMemBytesUnary();

    Location * EmitBinary(CodeGenerator *cg);
    int GetMemBytesBinary();
};

class RelationalExpr : public CompoundExpr 
{
  public:
    RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    // void creatStable() {}    
    int GetExprType() {return relationalExpr;} 
    const char *GetExprName() {return op->GetOperation();}
    Type * GetResType();

    Location * Emit(CodeGenerator * cg);
    int GetMemBytes();

  private:
    Location * EmitLess(CodeGenerator *cg, Expr *l, Expr *r);
    int GetMemBytesLess(Expr *l, Expr *r);

    Location * EmitLessEqual(CodeGenerator *cg, Expr *l, Expr *r);
    int GetMemBytesLessEqual(Expr *l, Expr *r);  
  
};

class EqualityExpr : public CompoundExpr 
{
  public:
    EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "EqualityExpr"; }
    // void creatStable() {}     
    int GetExprType() {return equalityExpr;}
    const char *GetExprName() {return op->GetOperation();}
    Type* GetResType();

    Location * Emit(CodeGenerator *cg);
    int GetMemBytes();
  private:
    Location* EmitEqual(CodeGenerator *cg);
    int GetMemBytesEqual();

    Location* EmitNotEqual(CodeGenerator *cg);
    int GetMemBytesNotEqual();
};

class LogicalExpr : public CompoundExpr 
{
  public:
    LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    const char *GetPrintNameForNode() { return "LogicalExpr"; }
    void creatStable();   
    int GetExprType() {return logicalExpr;}
    const char *GetExprName() {return op->GetOperation();}
    Type* GetResType();
    // bool check();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

  private:
    Location* EmitAnd(CodeGenerator *cg);
    int GetMemBytesAnd();

    Location* EmitOr(CodeGenerator *cg);
    int GetMemBytesOr();

    Location* EmitNot(CodeGenerator *cg);
    int GetMemBytesNot();
};

class AssignExpr : public CompoundExpr 
{
  public:
    AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "AssignExpr"; }
    // void creatStable() {printf("fuck!\n");}    
    int GetExprType() {return assignExpr;} 
    const char *GetExprName() {return op->GetOperation();}
    // bool check();
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();
};

class PostfixExpr : public CompoundExpr
{
  public:
    PostfixExpr(Expr *lhs, Operator *op) : CompoundExpr(lhs,op) {}
    const char *GetPrintNameForNode() { return "PostfixExpr"; }
    void creatStable();  
    // bool check(); 
    const char *GetExprName() {return op->GetOperation();}
    int GetExprType() {return postfixExpr;}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

  private:
    Location* EmitMinus(CodeGenerator *cg);
    int GetMemBytesMinus();
    Location* EmitPlus(CodeGenerator * cg);
    int GetMemBytesPlus();
};

class LValue : public Expr 
{
  public:
    LValue(yyltype loc) : Expr(loc) {}
    virtual void creatStable() = 0 ;   
    // virtual bool check();
    virtual const char *GetExprName() = 0;
    virtual int GetExprType() {return lValue;}
    virtual Type* GetResType() = 0;

    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetMemBytes() = 0;

    //attension!!!    
    virtual Location* EmitStore(CodeGenerator *cg, Location *val) = 0;
    virtual int GetMemBytesStore() = 0;
};

class This : public Expr 
{
  public:
    This(yyltype loc) : Expr(loc) {}
    void creatStable();  
    bool check() {return true;}
    int GetExprType() {return __this;}
    const char *GetExprName() {return "this";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();
};

class ArrayAccess : public LValue 
{
  protected:
    Expr *base, *subscript;
    
  public:
    ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
    void creatStable();
    bool check(); 
    int GetExprType() {return arrayAcess;}
    const char *GetExprName() {return "ArrayAccess";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

    Location* EmitStore(CodeGenerator *cg, Location *val);
    int GetMemBytesStore();

  private:
    Location* EmitAddr(CodeGenerator *cg);
    int GetMemBytesAddr();

    Location* EmitRuntimeSubscriptCheck(CodeGenerator *cg, Location *siz,
                                        Location *sub);
    int GetMemBytesRuntimeSubscriptCheck();
};

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
class FieldAccess : public LValue 
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    
  public:
    FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
    bool check();     
    int GetExprType();
    const char *GetExprName() {return "FieldAccess";}
    void creatStable();
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

    Location* EmitStore(CodeGenerator *cg, Location *val);
    int GetMemBytesStore();

  private:
    Location* EmitMemLoc(CodeGenerator *cg, VarDecl *fieldDecl);
    int GetMemBytesMemLoc(VarDecl *fieldDecl);

    Location* EmitMemLocStore(CodeGenerator *cg, Location *val,
                              VarDecl *fieldDecl);
    int GetMemBytesMemLocStore(VarDecl *fieldDecl);

    friend class CompoundExpr;
};

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */
class Call : public Expr 
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    List<Expr*> *actuals;
    
  public:
    Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);
    void creatStable();
    bool check();
    int GetExprType() {return __call;}
    const char *GetExprName() {return "call";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

  private:
    Location* EmitLabel(CodeGenerator *cg);
    int GetMemBytesLabel();

    Location* EmitArrayLength(CodeGenerator *cg);
    int GetMemBytesArrayLength();

    Location* EmitDynamicDispatch(CodeGenerator *cg, Location *b);
    int GetMemBytesDynamicDispatch();

    FnDecl* GetDecl();
    bool IsArrayLengthCall();
    bool IsMethodCall();
};


class NewExpr : public Expr
{
  protected:
    NamedType *cType;
    
  public:
    NewExpr(yyltype loc, NamedType *clsType);
    void creatStable();
    bool check();
    int GetExprType() {return newExpr;}
    const char *GetExprName() {return "new";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();
};

class NewArrayExpr : public Expr
{
  protected:
    Expr *size;
    Type *elemType;
    
  public:
    NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
    void creatStable();
    bool check();
    int GetExprType() {return newArrayExpr;}
    const char *GetExprName() {return "NewArray";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();

  private:
    Location* EmitRuntimeSizeCheck(CodeGenerator *cg, Location *siz);
    int GetMemBytesRuntimeSizeCheck();
};

class ReadIntegerExpr : public Expr
{
  public:
    ReadIntegerExpr(yyltype loc) : Expr(loc) {}
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return readIntegerExpr;}
    const char *GetExprName() {return "ReadInt";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();
};

class ReadLineExpr : public Expr
{
  public:
    ReadLineExpr(yyltype loc) : Expr (loc) {}
    void creatStable() {}
    bool check() {return true;}
    int GetExprType() {return readLineExpr;}
    const char *GetExprName() {return "ReadLine";}
    Type* GetResType();

    Location* Emit(CodeGenerator *cg);
    int GetMemBytes();
};

    
#endif
