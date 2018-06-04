/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "errors.h"
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
    sTable = new SignalTable;
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

void ClassDecl::creatStable(){
    // printf("fuck!\n");
    st_entry *ste = NULL;
    // printf("%p\n",implements);
    if (extends != NULL) {
        ste = sTable->find(extends->GetTypeName());
        // printf("fuck!\n");
        if (!ste) ReportError::IdentifierNotDeclared(extends->id,LookingForClass); //printf("error:%s not define.\n",extends->GetTypeName());
        else {
            int tt = ste->decl->GetDeclType();
            printf("%s %d\n",ste->decl->GetName(), tt);
            if (tt != classDeclType ) 
                // printf("error:%s is not class or interface.\n",extends->GetTypeName());
                ReportError::IdentifierNotDeclared(extends->id,LookingForClass);
            else {
                // sTable->AddParent(ste->decl->sTable);
                sTable->AddBaseClass(ste->decl->sTable);
            }
        }
    }
    if (implements != NULL) {
        // printf("%d\n",implements->NumElements());
        for (int i = 0 ; i < implements->NumElements();++i) {
            ste = sTable->find(implements->Nth(i)->GetTypeName());
            if (!ste) ReportError::IdentifierNotDeclared(implements->Nth(i)->id,LookingForInterface);
            //printf("error:%s not define.\n",extends->GetTypeName());
            else {
                int tt = ste->decl->GetDeclType();
                if (tt != interfaceDeclType) {
                    // printf("error:%s is not class or interface.\n", implements->Nth(i)->GetTypeName());
                    ReportError::IdentifierNotDeclared(implements->Nth(i)->id,LookingForInterface);
                } else {
                    // sTable->AddParent(ste->decl->sTable);
                    sTable->AddBaseInterface(ste->decl->sTable);
                    InterfaceDecl *iDecl = dynamic_cast<InterfaceDecl *> (ste->decl);
                    sTable->toImplement += iDecl->members->NumElements();
                }
            }
        }
    }
    // printf("%d\n",members->NumElements());
    int n = members->NumElements();
    
    sTable->SetScopName(GetTypeName());
    sTable->SetClassSymbolTable(true);
    for (int i = 0 ; i < n ; ++i) {
        sTable->InsertDecl(members->Nth(i));
    }
    
    // printf("fuck!\n");
    for (int i = 0 ; i < n ; ++i) {
        members->Nth(i)->sTable->AddParent(sTable);
        // printf("fuck!\n");
        members->Nth(i)->creatStable();
    }
    if (sTable->implemented != sTable->toImplement) 
        ReportError::InterfaceNotImplemented(this,implements->Nth(0));
    // printf("fuck!\n");
}


InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::creatStable() {
    int n = members->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        sTable->InsertDecl(members->Nth(i));
    }
    // printf("fuck!\n");
    for (int i = 0 ; i < n ; ++i) {
        members->Nth(i)->creatStable();
        // printf("fuck!\n");
        members->Nth(i)->sTable->AddParent(sTable);
    }
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::creatStable() {
    sTable->SetScopName(id->GetName());
    sTable->SetFnSTable(true);
    int n = formals->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        sTable->InsertDecl(formals->Nth(i));
    }
    if (body != NULL) {
        body->sTable->AddParent(sTable);
        body->creatStable();
    }
}



