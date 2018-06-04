/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "errors.h"

SignalTable *Program::gStable = new SignalTable; 


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */
    int n = decls->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        gStable->InsertDecl(decls->Nth(i));
    }
    // printf("fuck!\n");
    for (int i = 0 ; i < n; ++i) {
        
        // printf("fuck!\n");
        decls->Nth(i)->sTable->AddParent(gStable);
        decls->Nth(i)->creatStable();
        // printf("fuck!\n");
    }
    // printf("fuck!!\n");
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::creatStable() {
    // printf("fuck!\n");
    // printf("%d\n",decls->NumElements());
    for (int i = 0; i < decls->NumElements(); ++i) {
        sTable->InsertDecl(decls->Nth(i));
    }
    // printf("fuck!!!\n");
    for (int i = 0; i < decls->NumElements(); ++i) {
        // printf("%d\n",i);
        decls->Nth(i)->sTable->AddParent(sTable);
        // decls->Nth(i)->sTable->AddParent(Program::gStable);
        decls->Nth(i)->creatStable();
        decls->Nth(i)->sTable->SetClassSymbolTable(decls->Nth(i)->GetDeclType() == classDeclType);
        // printf("fuck!!!!\n");
    }
    // printf("fuck!!!!\n");
    for (int i = 0; i < stmts->NumElements(); ++i) {
        // printf("%d %d\n",stmts->NumElements(), i);
        stmts->Nth(i)->sTable->AddParent(sTable);
        // stmts->Nth(i)->sTable->AddParent(Program::gStable);
        stmts->Nth(i)->creatStable();
        
        stmts->Nth(i)->check();
        // printf("%d\n",stmts->Nth(i)->sTable->HasParent());
    }
}

bool StmtBlock::check() {
    return true;
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}



ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::creatStable() {
    // printf("for fuck!\n");
    init->sTable->AddParent(sTable);
    test->sTable->AddParent(sTable);
    step->sTable->AddParent(sTable);
    body->sTable->AddParent(sTable);
    // printf("fuck!\n");
    step->creatStable();
    init->creatStable();
    test->creatStable();
    body->creatStable();
    // printf("fuck!\n");

    sTable->SetLoopSTable(true);

    init->check();
    
    Type * res = test->GetResType();
    if (!res->EqualsTo(Type::boolType)) {
        ReportError::TestNotBoolean(test);
    }

    step->check();
    body->check();
    // printf("fuck!\n");
    // init->creatStable();
}

bool ForStmt::check() {
    return true;
}

void WhileStmt::creatStable() {
    // printf("fuck!\n");
    test->sTable->AddParent(sTable);    
    body->sTable->AddParent(sTable);
    test->creatStable();
    body->creatStable();
    sTable->SetLoopSTable(true);
    test->check();
    body->check();
}

bool WhileStmt::check() {
    return true;
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::creatStable() {
    // printf("fuck!\n");
    test->sTable->AddParent(sTable);
    body->sTable->AddParent(sTable);
    test->creatStable();
    test->check();
    body->creatStable();
    // printf("fuck!\n");
    
    // printf("fuck!\n");
    body->check();
    // printf("fuck!\n");
    if (elseBody) {
        // printf("fuck!\n");
        // printf("fuck!\n");
        elseBody->sTable->AddParent(sTable);
        elseBody->creatStable();
        // printf("fuck!\n");
        elseBody->check();
    }
}

bool IfStmt::check() {
    return true;
}

CaseStmt::CaseStmt(Expr *l, List<Stmt*> *stmtL) {
    Assert(l != NULL && stmtL != NULL);
    (label = l) ->SetParent(this);
    (stmtList = stmtL) -> SetParentAll(this);
}

void CaseStmt::creatStable() {
    label->sTable->AddParent(sTable);
    label->check();
    for (int i = 0 ; i < stmtList->NumElements() ; ++i) {
        stmtList->Nth(i)->creatStable();
        stmtList->Nth(i)->sTable->AddParent(sTable);
        stmtList->Nth(i)->check();
    }
}

DefaultStmt::DefaultStmt(List<Stmt*> *stmtL) {
    Assert(stmtL != NULL);
    (stmtList = stmtL) -> SetParentAll(this);
}

bool DefaultStmt::check() {
    return true;
}

void DefaultStmt::creatStable() {
    for (int i = 0 ; i < stmtList->NumElements() ; ++i) {
        stmtList->Nth(i)->creatStable();
        stmtList->Nth(i)->sTable->AddParent(sTable);
        stmtList->Nth(i)->check();
    }
}

SwitchStmt::SwitchStmt(Expr *e, List<CaseStmt*> *caseL,  DefaultStmt *Ds) {
    Assert(e != NULL && caseL != NULL );
    (expr = e) -> SetParent(this);
    (caseList = caseL) -> SetParentAll(this);
    if (Ds) (defaultStmt = Ds) -> SetParent(this);
    else defaultStmt = NULL;
}

void SwitchStmt::creatStable() {
    for (int i = 0 ; i < caseList->NumElements() ; ++i) {
        caseList->Nth(i)->creatStable();
        caseList->Nth(i)->sTable->AddParent(sTable);
        caseList->Nth(i)->check();
    }
    defaultStmt->creatStable();
    defaultStmt->sTable->AddParent(sTable);
    defaultStmt->check();
}

bool SwitchStmt::check() {
    return true;
}

void BreakStmt::creatStable() {
    if (!sTable->isInLoop())
        ReportError::BreakOutsideLoop(this);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::creatStable() {
    expr->sTable->AddParent(sTable);
    expr->creatStable();
    Type * res = expr->GetResType();
    // printf("%s\n",res->GetTypeName());
    if (res->EqualsTo(Type::errorType)) return;
    char * fnScopeName = sTable->GetFnScopeName();
    // printf("%s\n",fnScopeName);
    // printf("fuck!\n");
    Decl* decl = sTable->find(fnScopeName)->decl;
    // printf("%p\n",decl);
    // printf("fuck!\n");
    if(!res->EqualsTo(decl->GetType())) {
        ReportError::ReturnMismatch(this,res,decl->GetType());
    }
}

bool ReturnStmt::check() {
    return true;
}  

PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::creatStable() {
    int n = args->NumElements();
    for (int i = 0 ; i < n; ++i) {
        args->Nth(i)->sTable->AddParent(sTable);
        args->Nth(i)->creatStable();
    }
    Type *t = NULL;
    for (int i = 0 ; i < n; ++i) {
        t = args->Nth(i)->GetResType();
        if (!t->EqualsTo(Type::intType) && !t->EqualsTo(Type::doubleType) && !t->EqualsTo(Type::stringType)) {
            ReportError::PrintArgMismatch(args->Nth(i),i,t);
        }
    }
}

bool PrintStmt::check() {
    return true;
}


