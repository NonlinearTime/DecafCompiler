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

int VarDecl::GetMemBytes() {
    //all primitive things are 4 bytes , others such like string const are  pointers
    return CodeGenerator::VarSize;
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
    st_entry *ste = NULL;
    if (extends != NULL) {
        ste = sTable->find(extends->GetTypeName());
        if (!ste) ReportError::IdentifierNotDeclared(extends->id,LookingForClass); //printf("error:%s not define.\n",extends->GetTypeName());
        else {
            int tt = ste->decl->GetDeclType();
            if (tt != classDeclType ) 
                ReportError::IdentifierNotDeclared(extends->id,LookingForClass);
            else {
                sTable->AddBaseClass(ste->decl->sTable);
            }
        }
    }
    if (implements != NULL) {
        for (int i = 0 ; i < implements->NumElements();++i) {
            ste = sTable->find(implements->Nth(i)->GetTypeName());
            if (!ste) ReportError::IdentifierNotDeclared(implements->Nth(i)->id,LookingForInterface);
            else {
                int tt = ste->decl->GetDeclType();
                if (tt != interfaceDeclType) {
                    ReportError::IdentifierNotDeclared(implements->Nth(i)->id,LookingForInterface);
                } else {
                    sTable->AddBaseInterface(ste->decl->sTable);
                    InterfaceDecl *iDecl = dynamic_cast<InterfaceDecl *> (ste->decl);
                    sTable->toImplement += iDecl->members->NumElements();
                }
            }
        }
    }
    int n = members->NumElements();
    
    sTable->SetScopName(GetTypeName());
    sTable->SetClassSymbolTable(true);
    for (int i = 0 ; i < n ; ++i) {
        sTable->InsertDecl(members->Nth(i));
    }
    
    for (int i = 0 ; i < n ; ++i) {
        members->Nth(i)->sTable->AddParent(sTable);
        members->Nth(i)->creatStable();
    }
    if (sTable->implemented != sTable->toImplement) 
        ReportError::InterfaceNotImplemented(this,implements->Nth(0));
}

void ClassDecl::PreEmit() {

}

Location * ClassDecl::Emit(CodeGenerator *cg) {
    return NULL;
}

int ClassDecl::GetMemBytes() {
    return 0;
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

int InterfaceDecl::GetMemBytes() {
    return 0;
}


FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
    isMethod = false;
    label = new std::string(GetName());
    if (*label != "main")
        label->insert(0,"__");
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

Location* FnDecl::Emit(CodeGenerator * cg) {
    int offset = CodeGenerator::OffsetToFirstParam;

    if (isMethod)
        offset += CodeGenerator::VarSize;
    int n = formals->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        VarDecl *d = formals->Nth(i);
        Location *loc = new Location(fpRelative, offset, d->GetName());
        d->SetMemLoc(loc);
        offset += d->GetMemBytes();
    }
    if (body) {
        cg->GenLabel(GetLabel());
        cg->GenBeginFunc()->SetFrameSize(body->GetMemBytes());
        body->Emit(cg);
        cg->GenEndFunc();
    }
    if (*label == "main") {
        cg->GenEndSyscall();
    }
    return NULL; 
}

int FnDecl::GetMemBytes() {
    return CodeGenerator::VarSize; 
}

const char * FnDecl::GetLabel() {
    return label->c_str();
}

bool FnDecl::HasReturnVal() {
    return !returnType->EqualsTo(Type::voidType);
}
