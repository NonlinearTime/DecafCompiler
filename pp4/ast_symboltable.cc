#include "ast_symboltable.h"


SymbolTable::SymbolTable() {
    hashtable = new Hashtable<st_entry *>;
    parents = new List<SymbolTable *>;
    isClassSymbolTable = false;
    isFnSymbolTable = false;
    scopeName = NULL;
    isLoopSymbolTable = false;
    baseClass = NULL;
    interfaces = new List<SymbolTable *>;
    toImplement = 0;
    implemented = 0;
}

bool SymbolTable::isBaseType(char *t, int dt) {
    if (dt == varDeclType) {
        return strcmp(t, "int") == 0 || strcmp(t, "double") == 0 || strcmp(t, "bool") == 0 || strcmp(t, "string") == 0;
    } else if (dt == fnDeclType) {
        return strcmp(t, "int") == 0 || strcmp(t, "double") == 0 || strcmp(t, "bool") == 0 || strcmp(t, "string") == 0 || strcmp(t, "void") == 0;        
    }
    return true;
}

st_entry * SymbolTable::Lookup(const char * key) {
    st_entry * ste = NULL;
    ste = LocalLookup(key);
    if (!ste && baseClass != NULL)  ste = baseClass->Lookup(key);
    return ste;
}

st_entry * SymbolTable::LookupInterfaces(const char * key) {
    st_entry * ste = NULL;
    int n = interfaces->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        ste = interfaces->Nth(i)->LocalLookup(key);
        if (ste != NULL) return ste;
    }
    return ste;
}

void SymbolTable::InsertDecl(Decl *decl) {
    if (Lookup(decl->GetName()) == NULL) {
        switch (decl->GetDeclType()) {
            case varDeclType: {
                char * tn = decl->GetTypeName();
                VarDecl *vDecl = dynamic_cast<VarDecl*>(decl);
                NamedType *nT = dynamic_cast<NamedType*>(vDecl->type);
                ArrayType *aT = dynamic_cast<ArrayType*>(vDecl->type);
                if (!nT && !aT) {
                    Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                } else if (nT != NULL) {
                    st_entry *ste = find(nT->GetTypeName());
                    if (ste == NULL)
                        ReportError::IdentifierNotDeclared(nT->id,LookingForType);
                    else if (ste->decl->GetDeclType() == varDeclType ) {
                        ReportError::IdentifierNotDeclared(nT->id,LookingForType);
                    } else 
                        Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                } else if (aT !=NULL) {
                    char * et = aT->elemType->GetTypeName();
                    if (isBaseType(et,varDeclType))  {
                        Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                    } else {
                        NamedType *anT = dynamic_cast<NamedType*>(aT->elemType);
                        st_entry *ste = find(aT->elemType->GetTypeName());
                        if (ste == NULL) {
                            ReportError::IdentifierNotDeclared(anT->id,LookingForType);
                        }
                        else if (ste->decl->GetDeclType() == varDeclType ) {
                            ReportError::IdentifierNotDeclared(nT->id,LookingForType);
                        } else 
                            Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                    }
                }
                break;
            }
            case fnDeclType: {
                char * tn = decl->GetTypeName();
                FnDecl *fDecl = dynamic_cast<FnDecl*>(decl);                
                if (isBaseType(tn, fnDeclType)) {
                    Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                } else {
                    NamedType *nT = dynamic_cast<NamedType*>(fDecl->returnType);
                    ArrayType *aT = dynamic_cast<ArrayType*>(fDecl->returnType);
                    if ( nT != NULL) {
                        st_entry *ste = find(nT->GetTypeName());
                        if (ste == NULL)
                            ReportError::IdentifierNotDeclared(nT->id,LookingForType);
                        else if (ste->decl->GetDeclType() == varDeclType) 
                            ReportError::IdentifierNotDeclared(nT->id,LookingForType);
                        else Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                    } else if ( aT != NULL) {
                        char * et = aT->elemType->GetTypeName();
                        if (isBaseType(et,varDeclType))  {
                            Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                        } else {
                            NamedType *anT = dynamic_cast<NamedType*>(aT->elemType);
                            st_entry *ste = find(aT->elemType->GetTypeName());
                            if (ste == NULL) {
                                ReportError::IdentifierNotDeclared(anT->id,LookingForType);
                            } else if (ste->decl->GetDeclType() == varDeclType) 
                                ReportError::IdentifierNotDeclared(anT->id,LookingForType);
                            else Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                        }
                    }
                }
                st_entry * ste = LookupInterfaces(decl->GetName());
                if (!ste) Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                else {
                    FnDecl * proto = dynamic_cast<FnDecl *> (ste->decl);
                    if (!proto) {
                        printf("fuck!\n");
                        break;
                    } 
                    List<VarDecl *> *fArgs = fDecl->GetArgs();
                    List<VarDecl *> *pArgs = proto->GetArgs();
                    if (!fDecl->returnType->EqualsTo(proto->returnType)) {
                        ReportError::OverrideMismatch(fDecl);
                        break;
                    }
                    int n = pArgs->NumElements();
                    if (fArgs->NumElements() != n) {
                        ReportError::OverrideMismatch(fDecl);
                        break;
                    }
                    
                    for (int i = 0 ; i < n ; ++i) {
                        if (fArgs->Nth(i)->GetType()->EqualsTo(pArgs->Nth(i)->GetType())
                            && strcmp(fArgs->Nth(i)->GetName(),pArgs->Nth(i)->GetName()) == 0) {
                            Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
                        } else {
                            ReportError::OverrideMismatch(fDecl);
                            break;
                        }
                    }
                    implemented += 1;
                }
                break;
            }
            default:
                Insert(decl->GetName(), new st_entry(decl->GetName(), decl));
        }        
    } else {
        ReportError::DeclConflict(decl,Lookup(decl->GetName())->decl);
        printf("error: redefinition of %s\n", decl->GetName());
    }
}

void SymbolTable::AddParent(SymbolTable *p) {
    parents->Append(p);
}

void SymbolTable::AddBaseClass(SymbolTable *b) {
    baseClass = b;
}

void SymbolTable::AddBaseInterface(SymbolTable* i) {
    interfaces->Append(i);
}

bool SymbolTable::check(const char * key) {
    int n = parents->NumElements();
    // printf("%d\n",n);
    if (Lookup(key) != NULL) return true;
    for (int i = 0; i < n; ++i)
        if (parents->Nth(i)->check(key)) return true;
    return false;
}

st_entry * SymbolTable::find(const char * key) {
    int n = parents->NumElements();
    st_entry * ste = NULL;
    for (int i = 0 ; i < n; ++i) {
        ste = parents->Nth(i)->Lookup(key);
        if (ste != NULL) {
            return ste;
        }
        ste = parents->Nth(i)->find(key);
    }
    return ste;
}

st_entry * SymbolTable::findProtoType(const char * key) {
    int n = interfaces->NumElements();
    st_entry * ste = NULL;
    for (int i = 0 ; i < n; ++i) {
        ste = interfaces->Nth(i)->LocalLookup(key);
        if (ste != NULL) {
            return ste;
        }
        ste = interfaces->Nth(i)->find(key);
    }
    return ste;
}

bool SymbolTable::isInClass() {
    if (isClassSTable()) return true;
    for (int i = 0; i < parents->NumElements(); ++i) {
        if (parents->Nth(i)->isInClass()) return true;
    }
    return false;
}

bool SymbolTable::isInLoop() {    
    if (isLoopSTable()) return true;
    for (int i = 0; i < parents->NumElements(); ++i) {
        if (parents->Nth(i)->isInLoop()) return true;
    }
    return false;
}

char * SymbolTable::GetClassScopeName() {
    char *res = NULL;
    if (isClassSTable()) return scopeName;
    for (int i = 0; i < parents->NumElements(); ++i) {
        res = parents->Nth(i)->GetClassScopeName();
    }
    return res;
}

char * SymbolTable::GetFnScopeName() {
    char *res = NULL;
    if (isFnSTable()) return scopeName;
    for (int i = 0; i < parents->NumElements(); ++i) {
        res = parents->Nth(i)->GetFnScopeName();
    }
    return res;
}


