/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 *
 * pp3: You will need to extend the Type classes to implement
 * the type system and rules for type equivalency and compatibility.
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>
#include <cstring>
using namespace std;

class NamedType;
class ArrayType;

const int TypeNum = 1;
const int NameTypeNum = 2;
const int ArrayTypeNum = 3;

class Type : public Node 
{
  protected:
    char *typeName;
    int declType;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    Type(const char *name, int type);
    
    virtual void PrintToStream(ostream& out) { out << typeName; }
    friend ostream& operator<<(ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEquivalentTo(Type *other) { return this == other; }
    virtual char * GetTypeName() {return typeName;}
    virtual int GetTypeNum() {return TypeNum;}
    bool isConstant() {
      return strcmp(GetTypeName(), "int")    == 0 ||
             strcmp(GetTypeName(), "double") == 0 ||
             strcmp(GetTypeName(), "bool")   == 0 ||
             strcmp(GetTypeName(), "void")   == 0 ||
             strcmp(GetTypeName(), "null")   == 0 ||
             strcmp(GetTypeName(), "string") == 0;
    }

    bool isError() {
      return strcmp(GetTypeName(), "error") == 0;
    }

    virtual bool EqualsTo(Type* t) {
        if (GetTypeNum() == t->GetTypeNum())
            return strcmp(GetTypeName(),t->GetTypeName()) == 0;
        else {
            return false;
        }
    }

    int GetDeclType() {return declType;}

    friend class SymbolTable;
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    
  public:
    NamedType(Identifier *i);
    NamedType(Identifier *i, int type);
    
    void PrintToStream(ostream& out) { out << id; }

    char * GetTypeName() {return id->GetName();}
    virtual int GetTypeNum() {return NameTypeNum;}
    bool EqualsTo(Type* t) {
        if (GetTypeNum() == t->GetTypeNum()) return strcmp(GetTypeName(),t->GetTypeName()) == 0;
        else return false;
    }
    friend class SymbolTable;
    friend class NewExpr;
    friend class FnDecl;
    friend class ClassDecl;
    friend class CompoundExpr;
};

class ArrayType : public Type 
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    

    void PrintToStream(ostream& out) { out << elemType << "[]"; }

    char * GetTypeName() {
      return elemType->GetTypeName();
    }

    virtual int GetTypeNum() {return ArrayTypeNum;}

    bool EqualsTo(Type* t) {
        if (GetTypeNum() == t->GetTypeNum()) return strcmp(GetTypeName(),t->GetTypeName()) == 0;
        else return false;
    }  

    friend class SymbolTable;
};

 
#endif
