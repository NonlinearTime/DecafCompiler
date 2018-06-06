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
stack<const char*> *Program::gBLabels = new stack<const char *>();


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
    cg = new CodeGenerator();
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
    for (int i = 0 ; i < n; ++i) {
        decls->Nth(i)->sTable->AddParent(gStable);
        decls->Nth(i)->creatStable();
    }
}

void Program::Emit() {
    int globalOffset = CodeGenerator::OffsetToFirstGlobal;

    int n = decls->NumElements();

    for (int i = 0 ; i < n ; ++i) {
        Decl * decl = decls->Nth(i);
        if (decl->GetDeclType() == __varDecl) {
            Location *gLoc = new Location(gpRelative,globalOffset,decl->GetName());
            VarDecl *vDecl = dynamic_cast<VarDecl*>(decl);
            vDecl->SetMemLoc(gLoc);
            globalOffset += vDecl->GetMemBytes();
        }
    }

    for (int i = 0 ; i < n ; ++i) {
        decls->Nth(i)->PreEmit();
    }

    for (int i = 0 ; i < n ; ++i) 
        decls->Nth(i)->Emit(cg);
    cg->DoFinalCodeGen();
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::creatStable() {
    for (int i = 0; i < decls->NumElements(); ++i) {
        sTable->InsertDecl(decls->Nth(i));
    }
    for (int i = 0; i < decls->NumElements(); ++i) {
        decls->Nth(i)->sTable->AddParent(sTable);
        decls->Nth(i)->creatStable();
        decls->Nth(i)->sTable->SetClassSymbolTable(decls->Nth(i)->GetDeclType() == classDeclType);
    }
    for (int i = 0; i < stmts->NumElements(); ++i) {
        stmts->Nth(i)->sTable->AddParent(sTable);
        stmts->Nth(i)->creatStable();
        
        stmts->Nth(i)->check();
    }
}

bool StmtBlock::check() {
    return true;
}

Location* StmtBlock::Emit(CodeGenerator* cg) {
    int n = decls->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        VarDecl * vDecl = dynamic_cast<VarDecl*> (decls->Nth(i));
        if (vDecl != NULL) {
            Location * localLoc = cg->GenLocalVar(vDecl->GetName(),vDecl->GetMemBytes());
            vDecl->SetMemLoc(localLoc);
        }
    }
    for (int i = 0 ; i < n ; ++i) 
        decls->Nth(i)->Emit(cg);
    for (int i = 0 , n = stmts->NumElements() ;i < n;++i) 
        stmts->Nth(i)->Emit(cg);
    return NULL;
}

int StmtBlock::GetMemBytes() {
    int bytes = 0;
    int n = decls->NumElements();
    for (int i = 0 ;  i < n  ; ++i) {
        bytes += decls->Nth(i)->GetMemBytes();
    }
    n = stmts->NumElements();
    for (int i = 0 ; i < n ; ++i) {
        bytes += stmts->Nth(i)->GetMemBytes();
    }
    return bytes;
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
    sTable->SetLoopSTable(true);
    init->sTable->AddParent(sTable);
    test->sTable->AddParent(sTable);
    step->sTable->AddParent(sTable);
    body->sTable->AddParent(sTable);
    step->creatStable();
    init->creatStable();
    test->creatStable();
    body->creatStable();

    init->check();
    
    Type * res = test->GetResType();
    if (!res->EqualsTo(Type::boolType)) {
        ReportError::TestNotBoolean(test);
    }

    step->check();
    body->check();
}

bool ForStmt::check() {
    return true;
}

Location* ForStmt::Emit(CodeGenerator * cg) {
    const char * tLabel = cg->NewLabel();
    const char * fLabel = cg->NewLabel();

    Program::gBLabels->push(fLabel);

    init->Emit(cg);
    cg->GenLabel(tLabel);
    Location *tLoc = test->Emit(cg);
    cg->GenIfZ(tLoc, fLabel);
    body->Emit(cg);
    step->Emit(cg);
    cg->GenGoto(tLabel);
    cg->GenLabel(fLabel);

    Program::gBLabels->pop();

    return NULL;
}

int ForStmt::GetMemBytes() {
    return init->GetMemBytes() + test->GetMemBytes() + body->GetMemBytes() + step->GetMemBytes() ;
}

void WhileStmt::creatStable() {
    sTable->SetLoopSTable(true);
    test->sTable->AddParent(sTable);    
    body->sTable->AddParent(sTable);
    test->creatStable();
    body->creatStable();
    test->check();
    body->check();
}

bool WhileStmt::check() {
    return true;
}

Location* WhileStmt::Emit(CodeGenerator * cg) {
    const char * tLabel = cg->NewLabel();
    const char * fLabel = cg->NewLabel();

    Program::gBLabels->push(fLabel);

    cg->GenLabel(tLabel);
    Location *tLoc = test->Emit(cg);
    cg->GenIfZ(tLoc, fLabel);
    body->Emit(cg);
    cg->GenGoto(tLabel);
    cg->GenLabel(fLabel);

    Program::gBLabels->pop();

    return NULL;
}

int WhileStmt::GetMemBytes() {
    return test->GetMemBytes() + body->GetMemBytes() ;
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::creatStable() {
    test->sTable->AddParent(sTable);
    body->sTable->AddParent(sTable);
    test->creatStable();
    test->check();
    body->creatStable();
    
    body->check();
    if (elseBody) {
        elseBody->sTable->AddParent(sTable);
        elseBody->creatStable();
        elseBody->check();
    }
}

bool IfStmt::check() {
    return true;
}

Location* IfStmt::Emit(CodeGenerator * cg) {
    const char* elseLabel = cg->NewLabel();
    const char* endLabel = cg->NewLabel();

    Location* tLoc = test->Emit(cg);
    cg->GenIfZ(tLoc, elseLabel);
    body->Emit(cg);
    cg->GenGoto(endLabel);
    cg->GenLabel(elseLabel);
    if (elseBody) elseBody->Emit(cg);
    cg->GenLabel(endLabel);

    return NULL;
}

int IfStmt::GetMemBytes() {
    if (elseBody == NULL) 
        return test->GetMemBytes() + body->GetMemBytes();
    else 
        return test->GetMemBytes() + body->GetMemBytes() + elseBody->GetMemBytes();
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
        stmtList->Nth(i)->sTable->AddParent(sTable);
        stmtList->Nth(i)->creatStable();
        stmtList->Nth(i)->check();
    }
}

Location* CaseStmt::Emit(CodeGenerator * cg) {
    int n = stmtList->NumElements();
    for (int i = 0 ; i < n; ++i)
        stmtList->Nth(i)->Emit(cg);
    return NULL;
}

int CaseStmt::GetMemBytes() {
    int memBytes = 0;
    int n = stmtList->NumElements();
    for (int i = 0 ; i < n; ++i)
        memBytes += stmtList->Nth(i)->GetMemBytes();
    return memBytes;
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
        stmtList->Nth(i)->sTable->AddParent(sTable);
        stmtList->Nth(i)->creatStable();
        stmtList->Nth(i)->check();
    }
}

Location* DefaultStmt::Emit(CodeGenerator * cg) {
    int n = stmtList->NumElements();
    for (int i = 0 ; i < n; ++i)
        stmtList->Nth(i)->Emit(cg);
    return NULL;
}

int DefaultStmt::GetMemBytes() {
    int memBytes = 0;
    int n = stmtList->NumElements();
    for (int i = 0 ; i < n; ++i)
        memBytes += stmtList->Nth(i)->GetMemBytes();
    return memBytes;
}

SwitchStmt::SwitchStmt(Expr *e, List<CaseStmt*> *caseL,  DefaultStmt *Ds) {
    Assert(e != NULL && caseL != NULL );
    (expr = e) -> SetParent(this);
    (caseList = caseL) -> SetParentAll(this);
    if (Ds) (defaultStmt = Ds) -> SetParent(this);
    else defaultStmt = NULL;
}

void SwitchStmt::creatStable() {
    sTable->SetLoopSTable(true);
    expr->sTable->AddParent(sTable);
    expr->creatStable();
    expr->check();
    for (int i = 0 ; i < caseList->NumElements() ; ++i) {
        caseList->Nth(i)->sTable->AddParent(sTable);
        caseList->Nth(i)->creatStable();
        caseList->Nth(i)->check();
    }
    defaultStmt->sTable->AddParent(sTable);    
    defaultStmt->creatStable();
    defaultStmt->check();
}

Location* SwitchStmt::Emit(CodeGenerator * cg) {
    int n = caseList->NumElements();
    char* caseLabels[n];
    for (int i = 0 ; i < n ; ++i) 
        caseLabels[i] = cg->NewLabel();
    const char* defaultLabel = cg->NewLabel();
    const char* endLabel = cg->NewLabel();

    Program::gBLabels->push(endLabel);

    Location* eLoc = expr->Emit(cg);
    Location* tLoc = NULL;

    for (int i = 0 ; i < n ; ++i) {
        const char* botLabel = cg->NewLabel(); 
        Location* clabelLoc = caseList->Nth(i)->label->Emit(cg);
        tLoc = cg->GenBinaryOp("==",eLoc,clabelLoc);
        cg->GenIfZ(tLoc,botLabel);
        cg->GenGoto(caseLabels[i]);
        cg->GenLabel(botLabel);
    }
    cg->GenGoto(defaultLabel);

    for (int i = 0 ; i < n; ++i) {
        cg->GenLabel(caseLabels[i]);
        caseList->Nth(i)->Emit(cg);
    }
    cg->GenLabel(defaultLabel);
    defaultStmt->Emit(cg);
    cg->GenLabel(endLabel);

    Program::gBLabels->pop();

    return NULL;
}

int SwitchStmt::GetMemBytes() {
    int memBytes = 0;
    int n = caseList->NumElements();
    memBytes += expr->GetMemBytes();
    for (int i = 0 ; i < n ; ++i) 
        memBytes += CodeGenerator::VarSize 
        + caseList->Nth(i)->label->GetMemBytes()
        + caseList->Nth(i)->GetMemBytes();
    memBytes += defaultStmt->GetMemBytes();
    
    return memBytes;
}

bool SwitchStmt::check() {
    return true;
}

void BreakStmt::creatStable() {
    if (!sTable->isInLoop())
        ReportError::BreakOutsideLoop(this);
}

Location* BreakStmt::Emit(CodeGenerator * cg) {
    cg->GenGoto(Program::gBLabels->top());
    return NULL;
}

int BreakStmt::GetMemBytes() {
    return 0;
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::creatStable() {
    expr->sTable->AddParent(sTable);
    expr->creatStable();
    Type * res = expr->GetResType();
    if (res->EqualsTo(Type::errorType)) return;
    char * fnScopeName = sTable->GetFnScopeName();
    Decl* decl = sTable->find(fnScopeName)->decl;
    if(!res->EqualsTo(decl->GetType())) {
        ReportError::ReturnMismatch(this,res,decl->GetType());
    }
}

bool ReturnStmt::check() {
    return true;
}  

Location* ReturnStmt::Emit(CodeGenerator * cg) {
    Location * loc = expr->Emit(cg);
    cg->GenReturn(loc);
    return NULL;
}

int ReturnStmt::GetMemBytes() {
    if (expr == NULL) return 0;
    else return expr->GetMemBytes();
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

Location* PrintStmt::Emit(CodeGenerator * cg) {
    return NULL;
}

int PrintStmt::GetMemBytes() {
    return 0;
}


