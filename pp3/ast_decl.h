/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp3: You will need to extend the Decl classes to implement 
 * semantic processing including detection of declaration conflicts 
 * and managing scoping issues.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"
#include "ast_type.h"
#include "ast_signaltable.h"

class Type;
class NamedType;
class Identifier;
class Stmt;
class SignalTable;

/* enum declType {
    varDeclType = 1, 
    fnDeclType = 2,
    interfaceDeclType = 3,
    classDeclType = 4
}; */


#define __varDecl  1
#define __classDecl  2
#define __interDecl 3
#define __fnDecl 4

class Decl : public Node 
{
  protected:
    Identifier *id;
  
  public:
    Decl(Identifier *name);
    SignalTable *sTable;

    char * GetName() {return id->GetName();}

    friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id; }

    virtual void creatStable() = 0;
    virtual char *GetTypeName() = 0;
    virtual int GetDeclType() = 0;
    virtual const char *GetDeclName() = 0;
    virtual Type *GetType() = 0;

    friend class SignalTable;
};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
    char * GetTypeName() {/* printf("fuck1\n"); */return type->GetTypeName();}
    void creatStable() {}
    int GetDeclType() {return __varDecl;}
    const char *GetDeclName() {return type->GetTypeName();}
    Type *GetType() {
      // printf("fuck!\n");
      // printf("%s\n",GetTypeName());
      // return new Type(GetTypeName(),GetDeclType());
      return type;
    }
    friend class SignalTable;
};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    void creatStable();
    char * GetTypeName() {/* printf("fuck2\n"); */return id->GetName();}
    int GetDeclType() {return __classDecl;}
    const char *GetDeclName() {return "class";}
    Type *GetType() {
      // printf("%s\n",GetTypeName());
      return new NamedType(id,GetDeclType());
      
      // return new Type(GetTypeName(),GetDeclType());
    }
    friend class SignalTable;
};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    void creatStable();
    char * GetTypeName() {/* printf("fuck3\n"); */return id->GetName();}
    int GetDeclType() {return __interDecl;}
    const char *GetDeclName() {return "interface";}
    Type *GetType() {
        return new Type(GetTypeName(),GetDeclType());
    }
    friend class SignalTable;
    friend class ClassDecl;
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    void creatStable();
    char * GetTypeName() {/* printf("fuck4\n"); */return returnType->GetTypeName();}
    int GetDeclType() { return __fnDecl; }
    List<VarDecl*> * GetArgs() {return formals;}
    const char *GetDeclName() {return "function";}
    Type *GetType() {
        return new Type(GetTypeName(),GetDeclType());
    }
    friend class SignalTable;
};

#endif
