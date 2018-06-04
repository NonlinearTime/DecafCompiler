#ifndef _H_ast_signaltable

#define _H_ast_signaltable

#include "list.h"
#include "hashtable.h"
#include "ast_decl.h"
#include <vector>
#include <string>
#include "errors.h"

const int varDeclType = 1;
const int classDeclType = 2;
const int interfaceDeclType = 3;
const int fnDeclType = 4;
const int emptyExpr = 5;
const int intConstant = 6;
const int doubleConstant = 7;
const int boolConstant = 8;
const int stringConstant = 9;
const int nullConstant = 10;
const int arithmeticExpr = 11;
const int relationalExpr = 12;
const int equalityExpr = 13;
const int logicalExpr = 14;
const int assignExpr = 15;
const int postfixExpr = 16;
const int lValue = 17;
const int __this = 18;
const int arrayAcess = 19;
const int fieldAcess = 20;
const int __call = 21;
const int newExpr = 22;
const int newArrayExpr = 23;
const int readIntegerExpr = 24;
const int readLineExpr = 25;
const int classSymbolTable = 26;


class Decl;

class st_entry {
    public:
        char *name;
        Decl * decl;
        st_entry(char * _name, Decl * _decl) {
            name = _name;
            decl = _decl;
        }
    private:

    protected:

};

class SignalTable {
    public:
        SignalTable();
        void Insert(const char * key, st_entry * entry) {
            hashtable->Enter(key, entry);
        }
        void Removd(const char * key, st_entry * entry) {
            hashtable->Remove(key,entry);
        }
        st_entry * LocalLookup(const char * key) {
            return hashtable->Lookup(key);
        }
        st_entry * Lookup(const char * key);
        st_entry * LookupInterfaces(const char * key);
        void AddParent(SignalTable * p);
        void AddBaseClass(SignalTable *b);
        void AddBaseInterface(SignalTable *i);
        void InsertDecl(Decl *decl);
        bool HasParent() {return parents->NumElements() != 0;}
        bool check(const char * key);
        bool isClassSTable() {return isClassSymbolTable;}
        void SetClassSymbolTable(bool isCST) {isClassSymbolTable = isCST;}
        bool isFnSTable() {return isFnSymbolTable;}
        void SetFnSTable(bool isFST) {isFnSymbolTable = isFST;}
        bool isLoopSTable() {return isLoopSymbolTable;}
        void SetLoopSTable(bool isLST) {isLoopSymbolTable = isLST;}
        bool isInClass();
        bool isInLoop();
        char *GetClassScopeName();
        void SetScopName(const char * name) { scopeName = strdup(name);}
        char *GetFnScopeName();
        st_entry * find(const char * key);
        st_entry * findProtoType(const char * key);

    private:
        Hashtable<st_entry *> *hashtable;
        List<SignalTable *> *parents;
        SignalTable *baseClass;
        List<SignalTable *> *interfaces;
        bool isBaseType(char *t, int dt);
        bool isClassSymbolTable;
        bool isFnSymbolTable;
        bool isLoopSymbolTable;
        char *scopeName;
    protected:
        int toImplement;
        int implemented;
    friend class ClassDecl; 
};

#endif