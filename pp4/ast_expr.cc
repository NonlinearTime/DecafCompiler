/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "errors.h"


IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Expr * l, Operator *o)
  : Expr(Join(l->GetLocation(), o->GetLocation())) {
    Assert(l != NULL && o != NULL);
    (left = l ) -> SetParent(this);
    (op = o) -> SetParent(this);
    right = NULL;
}   

void CompoundExpr::creatStable() {
    left->sTable->AddParent(sTable);
    right->sTable->AddParent(sTable);
    left->creatStable();
    right->creatStable();
}

bool CompoundExpr::check() {
    Type *res = GetResType();
    if (res->EqualsTo(Type::errorType)) return false;
    return true;
}

Type* CompoundExpr::GetResType() {
    if (left == NULL) {
        return right->GetResType();
    } else if (right == NULL) {
        return left->GetResType();
    } else {
        Type *lType = left->GetResType();
        Type *rType = right->GetResType();
        if (lType->isError() || rType->isError()) return Type::errorType;
        if (lType->GetDeclType() != varDeclType) {
            NamedType* nT = dynamic_cast<NamedType *> (lType);
            if (nT != NULL) {
                ReportError::IdentifierNotDeclared(nT->id,LookingForVariable);
                return Type::errorType;
            }
        }
        if (rType->GetDeclType() != varDeclType) {
            FieldAccess *fA = dynamic_cast<FieldAccess*>(right);
            NamedType* nT = dynamic_cast<NamedType *> (rType);
            if (fA != NULL) {
                // printf("fuck!\n");
                ReportError::IdentifierNotDeclared(fA->field,LookingForVariable);
                return Type::errorType;
            }
        }
        // printf("%s\n",rType->GetTypeName());
        if (lType->EqualsTo(rType)) {
            return lType;
        } else {
            ReportError::IncompatibleOperands(op,lType,rType);
            return Type::errorType;
        }
    }
    return Type::errorType;
}

/* Expr * CompoundExpr::resExpr() {
    Expr* lfExpr = left->resExpr();
    Expr* rghExpr  = right->resExpr();
    char *leftType, *tghEype;
    
    if (lfExpr->GetExprType() != rghExpr->GetExprType()) {
        printf("error: %s %s %s.\n",lfExpr->GetExprName(), op->GetOperation(), rghExpr->GetExprName());
    } else {
        return lfExpr;
    }
} */

Expr * ArithmeticExpr::resExpr() {
    Expr* lfExpr = NULL;
    Expr* rghExpr =NULL;
    // printf("fuck!\n");
    if (left != NULL) lfExpr = left->resExpr();
    if (right != NULL) rghExpr = right->resExpr();
    char *leftType, *tghEype;
    
    // printf("%p %p\n",lfExpr,rghExpr);
    if (lfExpr->GetExprType() != rghExpr->GetExprType()) {
        printf("error: %s %s %s.\n",lfExpr->GetExprName(), op->GetOperation(), rghExpr->GetExprName());
        return NULL;
    } else {
        // printf("fuck!\n");
        return lfExpr == NULL ? rghExpr : lfExpr;
    }
}

Location* ArithmeticExpr::Emit(CodeGenerator *cg) {
    if (left == NULL) return EmitUnary(cg);
    else return EmitBinary(cg);
}

int ArithmeticExpr::GetMemBytes() {
    if (left == NULL) return GetMemBytesUnary();
    else return GetMemBytesBinary();
}

Location* ArithmeticExpr::EmitUnary(CodeGenerator *cg) {
    return NULL;
}

Location* ArithmeticExpr::EmitBinary(CodeGenerator *cg) {
    return NULL;
}

int ArithmeticExpr::GetMemBytesUnary() {
    return 0;
}

int ArithmeticExpr::GetMemBytesBinary() {
    return 0;
}

void ArithmeticExpr::creatStable() {
    if (left) {
        left->sTable->AddParent(sTable);
        left->creatStable();
    } 
    right->sTable->AddParent(sTable);
    right->creatStable(); 
    // check();
}

Expr * RelationalExpr::resExpr() {
    Expr* lfExpr = left->resExpr();
    Expr* rghExpr  = right->resExpr();
    char *leftType, *tghEype;
    
    if (lfExpr->GetExprType() != rghExpr->GetExprType()) {
        printf("error: %s %s %s.\n",lfExpr->GetExprName(), op->GetOperation(), rghExpr->GetExprName());
        return NULL;
    } else {
        return new BoolConstant(*op->GetLocation(),"false");
    }
}

Type* RelationalExpr::GetResType() {
    Assert(left!=NULL && right != NULL);
    Type *lType = left->GetResType();
    Type *rType = right->GetResType();
    if (lType->isError()  || rType->isError()) return Type::errorType;
    if (lType->EqualsTo(rType) && !lType->EqualsTo(Type::voidType)) {
        return new Type("bool", boolConstant);
    } else {
        ReportError::IncompatibleOperands(op,lType,rType);
        return Type::errorType;
    }
}

Location* RelationalExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int RelationalExpr::GetMemBytes() {
    return 0;
}

Location* RelationalExpr::EmitLess(CodeGenerator *cg, Expr *l, Expr *r) {
    return NULL;
}

int RelationalExpr::GetMemBytesLess(Expr *l, Expr *r) {
    return 0;
}

Location* RelationalExpr::EmitLessEqual(CodeGenerator *cg, Expr *l, Expr *r) {
    return NULL;
}

int RelationalExpr::GetMemBytesLessEqual(Expr *l, Expr *r) {
    return 0;
}

Expr * EqualityExpr::resExpr() {
    Expr* lfExpr = left->resExpr();
    Expr* rghExpr  = right->resExpr();
    char *leftType, *tghEype;
    
    if (lfExpr->GetExprType() != rghExpr->GetExprType()) {
        printf("error: %s %s %s.\n",lfExpr->GetExprName(), op->GetOperation(), rghExpr->GetExprName());
        return NULL;
    } else {
        return new BoolConstant(*op->GetLocation(),"false");
    }
}


Type* EqualityExpr::GetResType() {
    Assert(left!=NULL && right != NULL);
    Type *lType = left->GetResType();
    Type *rType = right->GetResType();
    if (lType->isError() || rType->isError()) return Type::errorType;
    if (lType->EqualsTo(rType) && !lType->EqualsTo(Type::voidType)) {
        return new Type("bool", boolConstant);
    } else {
        ReportError::IncompatibleOperands(op,lType,rType);
        return Type::errorType;
    }
}

Location* EqualityExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int EqualityExpr::GetMemBytes() {
    return 0;
}

Location* EqualityExpr::EmitEqual(CodeGenerator *cg) {
    return NULL;
}

int EqualityExpr::GetMemBytesEqual() {
    return 0;
}

Location* EqualityExpr::EmitNotEqual(CodeGenerator *cg) {
    return NULL;
}

int EqualityExpr::GetMemBytesNotEqual() {
    return 0;
}

void LogicalExpr::creatStable() {
    if (left) {
        left->sTable->AddParent(sTable);
        left->creatStable();
    } 
    right->sTable->AddParent(sTable);
    right->creatStable(); 
}

Expr * LogicalExpr::resExpr() {
    Expr* lfExpr = left->resExpr();
    Expr* rghExpr  = right->resExpr();
    char *leftType, *tghEype;
    
    if (lfExpr->GetExprType() != rghExpr->GetExprType()) {
        printf("error: %s %s %s.\n",lfExpr->GetExprName(), op->GetOperation(), rghExpr->GetExprName());
        return NULL;
    } else {
        return new BoolConstant(*op->GetLocation(),"false");
    }
}

Type* LogicalExpr::GetResType() {
    // printf("fuck!\n");
    Assert(right != NULL);
    Type *lType = NULL;
    if (left != NULL) lType = left->GetResType();
    Type *rType = right->GetResType();
    if (lType != NULL) {
        if (lType->isError() || rType->isError()) return Type::errorType;
        if (lType->EqualsTo(rType) && !lType->EqualsTo(Type::voidType)) {
            return new Type("bool",boolConstant);
        } else {
            ReportError::IncompatibleOperands(op,lType,rType);
            return Type::errorType;
        }
    } else {
        if (rType->isError()) return Type::errorType;
        if (!rType->EqualsTo(Type::boolType)) {
            ReportError::IncompatibleOperand(op,rType);
            return Type::errorType;
        }
        return new Type("bool",boolConstant);
    }
}

Location* LogicalExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int LogicalExpr::GetMemBytes() {
    return 0;
}

Location* LogicalExpr::EmitAnd(CodeGenerator *cg) {
    return NULL;
}

int LogicalExpr::GetMemBytesAnd() {
    return 0;
}

Location* LogicalExpr::EmitOr(CodeGenerator *cg) {
    return NULL;
}

int LogicalExpr::GetMemBytesOr() {
    return 0;
}

Location* LogicalExpr::EmitNot(CodeGenerator *cg) {
    return NULL;
}

int LogicalExpr::GetMemBytesNot() {
    return 0;
}


Expr * AssignExpr::resExpr() {
    Expr* lfExpr = left->resExpr();
    Expr* rghExpr  = right->resExpr();
    char *leftType, *tghEype;
    printf("fuck!\n");
    printf("%p %p\n",lfExpr,rghExpr);
    printf("%d\n",sTable->HasParent());
    if (lfExpr->GetExprType() != rghExpr->GetExprType()) {
        printf("error: %s %s %s.\n",lfExpr->GetExprName(), op->GetOperation(), rghExpr->GetExprName());
        return NULL;
    } else {
        return lfExpr;
    }
}

/* bool AssignExpr::check() {
    resExpr();
    return false;
}
 */
Type* AssignExpr::GetResType() {
    Assert(left != NULL && right != NULL);
    Type *lType = left->GetResType();
    Type *rType = right->GetResType();
    // printf("fuck!\n");
    if (lType->isError() || rType->isError()) return Type::errorType;
    if (lType->EqualsTo(rType) && !lType->EqualsTo(Type::voidType)) {
        return lType;
    } else {
        // printf("%s\n",lType->GetTypeName());
        ReportError::IncompatibleOperands(op,lType,rType);
        // printf("fuck!\n");
        return Type::errorType;
    }
}

Location* AssignExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int AssignExpr::GetMemBytes() {
    return 0;
}

Expr * PostfixExpr::resExpr() {
    Expr* lExpr = NULL;
    if (left != NULL) lExpr  = left->resExpr();
    int lType = lExpr->GetExprType();
    
    if (lType != intConstant && lType != doubleConstant) {
        printf("error: %s %s.\n",op->GetOperation(), lExpr->GetExprName());
        return NULL;
    } else {
        return lExpr;
    }
}

void PostfixExpr::creatStable() {
    Assert(left != NULL);
    left->sTable->AddParent(sTable);
    left->creatStable();
}

Type* PostfixExpr::GetResType() {
    Assert(right != NULL);
    Type *lType = left->GetResType();
    if (lType->isError()) return Type::errorType;
    switch (lType->GetDeclType()) {
        case classDeclType: 
            ReportError::IncompatibleLeftOperand(lType,op);
            return Type::errorType;
        case interfaceDeclType:
            ReportError::IncompatibleLeftOperand(lType,op);
            return Type::errorType;
        case fnDeclType:
            ReportError::IncompatibleLeftOperand(lType,op);
            return Type::errorType;
        default:
            return lType;
    }
}

Location* PostfixExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int PostfixExpr::GetMemBytes() {
    return 0;
}

/* bool PostfixExpr::check() {
    return true;
} */

/* bool LValue::check() {
    return true;
} */

/* ************************* */

void This::creatStable() {
    
}

Type* This::GetResType() {
    if (!sTable->isInClass()) {
        ReportError::ThisOutsideClassScope(this);
        return Type::errorType;
    }
    char *scopeName = sTable->GetClassScopeName();
    return new Type(scopeName, classDeclType);
}

Location* This::Emit(CodeGenerator *cg) {
    return NULL;
}

int This::GetMemBytes() {
    return 0;
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::creatStable() {
    Assert(base != NULL && subscript != NULL);
    base -> sTable->AddParent(sTable);
    subscript->sTable->AddParent(sTable);
    base->creatStable();
    subscript->creatStable();
}

bool ArrayAccess::check() {
    return GetResType()->EqualsTo(Type::errorType);
}

Type* ArrayAccess::GetResType() {
    Assert(base != NULL && subscript != NULL);
    Type *bType = base->GetResType();
    Type *sType = subscript->GetResType();
    if (bType->isError() || sType->isError()) return Type::errorType;
    if (!sType->EqualsTo(Type::intType)) {
        ReportError::SubscriptNotInteger(subscript);
        return Type::errorType;
    }
    
    if (bType->GetTypeNum() != ArrayTypeNum) {
        ReportError::BracketsOnNonArray(this);
        return Type::errorType;
    }
    return new Type(bType->GetTypeName(),arrayAcess);
}

/* Attention */
Expr * ArrayAccess::resExpr() {
    Expr * rExpr = NULL, *bExpr = NULL;
    if (subscript != NULL) rExpr = subscript->resExpr();
    if (base != NULL) bExpr = base -> resExpr();
    if (rExpr->GetExprType() != intConstant) {
        printf("error:array index cannot be %s\n", rExpr->GetExprName());
        return NULL;
    } else {
        return bExpr;
    }
}

Location* ArrayAccess::Emit(CodeGenerator *cg) {
    return nullptr;
}

int ArrayAccess::GetMemBytes() {
    return 0;
}

Location* ArrayAccess::EmitStore(CodeGenerator *cg, Location *val) {
    return NULL;
}

int ArrayAccess::GetMemBytesStore() {
    return 0;
}

Location* ArrayAccess::EmitAddr(CodeGenerator *cg) {
    return NULL;
}

int ArrayAccess::GetMemBytesAddr() {
    return 0;
}

Location* ArrayAccess::EmitRuntimeSubscriptCheck(CodeGenerator *cg,
                                                 Location *arr,
                                                 Location *sub) {
    return NULL;
}

int ArrayAccess::GetMemBytesRuntimeSubscriptCheck() {
    return 0;
}

FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}

Expr * FieldAccess::resExpr() {
    Expr* bExpr = NULL;
    if (base != NULL) bExpr = base->resExpr();
    else {
        char *id = field->GetName();
        // printf("%s %d\n",id, sTable->HasParent());
        st_entry *ste = sTable->find(id);
        if (ste != NULL) {
            sTable = ste->decl->sTable;
            // ste->decl->GetDeclType();
            return this;
        }
    }
    // printf("b:%p\n",bExpr);
    return bExpr;
}

bool FieldAccess::check() {
    return GetResType()->EqualsTo(Type::errorType);
}

void FieldAccess::creatStable() {
    // printf("fuck!!!\n");
    if (base != NULL) {
        base->sTable->AddParent(sTable);
        base->creatStable();
    }
}

int FieldAccess::GetExprType() {
    
    return fieldAcess;
}

Type* FieldAccess::GetResType() {
    bool res = false;
    char *key = field->GetName();
    if (base == NULL) {
        // res = sTable->check(key);
        st_entry * ste = sTable->find(key);
        // printf("%d\n",sTable->HasParent());
        if (!ste) {
            // printf("fuck!\n");
            // printf("%s\n",key);
            ReportError::IdentifierNotDeclared(field,LookingForVariable);
            return Type::errorType;
        } else {
            // printf("%s %s\n",ste->decl->GetTypeName(), key);
            // printf("%s\n",ste->decl->GetType()->GetTypeName());
            
            return ste->decl->GetType();
        }
    } else {
        Type* bType = base->GetResType();
        if (bType->isError()) return Type::errorType;
        // st_entry *st = sTable->find(bType->GetTypeName());
        // printf("%s\n",bType->GetTypeName());
        st_entry * ste = sTable->find(bType->GetTypeName());
        if (ste == NULL) {
            // printf("fuck!\n");
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        if (ste->decl->GetDeclType() != classDeclType) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        // printf("fuck!\n");
        st_entry *mte = ste->decl->sTable->Lookup(key);
        // printf("fuck!\n");
        if (!mte) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        if (mte->decl->GetDeclType() == varDeclType) {
            ReportError::InaccessibleField(field,bType);
        }
        // printf("%p\n",mte->decl->GetType());
        // printf("fuck!\n");
        return mte->decl->GetType();
    }
}

Location* FieldAccess::Emit(CodeGenerator *cg) {
    return NULL;
}

int FieldAccess::GetMemBytes() {
    return 0;
}

Location* FieldAccess::EmitStore(CodeGenerator *cg, Location *val) {
    return NULL;
}

int FieldAccess::GetMemBytesStore() {
    return 0;
}

Location* FieldAccess::EmitMemLoc(CodeGenerator *cg, VarDecl *fieldDecl) {
    return NULL;
}

int FieldAccess::GetMemBytesMemLoc(VarDecl *fieldDecl) {
    return 0;
}

Location* FieldAccess::EmitMemLocStore(CodeGenerator *cg, Location *val, VarDecl *fieldDecl) {
    return NULL;
}

int FieldAccess::GetMemBytesMemLocStore(VarDecl *fieldDecl) {
    return 0;
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

void Call::creatStable() {
    if (base != NULL) {
        base->sTable->AddParent(sTable); 
        base->creatStable();
    }
    for (int i = 0 ; i < actuals->NumElements(); ++i) {
        actuals->Nth(i)->sTable->AddParent(sTable);
        actuals->Nth(i)->creatStable();
    }
}

bool Call::check() {
    return GetResType()->EqualsTo(Type::errorType);
}

/* ***************************** */
Expr * Call::resExpr() {
    return NULL;
}

Type* Call::GetResType() {
    char *id = field->GetName();
    if (base == NULL) {
        st_entry * ste = sTable->find(id);
        for (int i = 0 ; i < actuals->NumElements();++i)
            if(actuals->Nth(i)->GetResType()->isError()) ;
        if (ste == NULL) {
            ReportError::IdentifierNotDeclared(field,LookingForFunction);
            return Type::errorType;
        }
        if (ste->decl->GetDeclType() != fnDeclType) {
            ReportError::IdentifierNotDeclared(field,LookingForFunction);
            return Type::errorType;
        }
        FnDecl * fn = dynamic_cast<FnDecl *>(ste->decl);
        List<VarDecl*> * args = fn->GetArgs();

        if (args->NumElements() != actuals->NumElements()) {
            ReportError::NumArgsMismatch(field,args->NumElements(),actuals->NumElements());
            return Type::errorType;
        }

        for(int i = 0 ; i < args->NumElements(); ++i) {
            if (actuals->Nth(i)->GetResType()->isError()) return Type::errorType;
            if (!args->Nth(i)->GetType()->EqualsTo(actuals->Nth(i)->GetResType())){
                ReportError::ArgMismatch(actuals->Nth(i),i,args->Nth(i)->GetType(),actuals->Nth(i)->GetResType());
                return Type::errorType;
            }
        }

        return fn->GetType();
    } else {
        Type* bType = base->GetResType();
        // printf("fuck!\n");
        if (bType->isError()) return Type::errorType;
        
        st_entry * ste = sTable->find(bType->GetTypeName());
        // printf("fuck!\n");
        if (ste == NULL) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        if (ste->decl->GetDeclType() != classDeclType) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        for (int i = 0 ; i < actuals->NumElements();++i)
            if(actuals->Nth(i)->GetResType()->isError()) ;
        // printf("fuck!\n");
        st_entry *mte = ste->decl->sTable->Lookup(id);
        if (!mte) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        // printf("fuck!\n");
        if (mte->decl->GetType()->GetDeclType() != fnDeclType) return Type::errorType;
        // printf("fuck!\n");
        FnDecl * fn = dynamic_cast<FnDecl *>(mte->decl);
        // printf("%p\n",fn);
        List<VarDecl*> * args = fn->GetArgs();
        // printf("fuck!\n");
        if (args->NumElements() != actuals->NumElements()) {
            ReportError::NumArgsMismatch(field,args->NumElements(),actuals->NumElements());
            return Type::errorType;
        }
        // printf("fuck!\n");
        for(int i = 0 ; i < args->NumElements(); ++i) {
            if (!args->Nth(i)->GetType()->EqualsTo(actuals->Nth(i)->GetResType())){
                ReportError::ArgMismatch(actuals->Nth(i),i,args->Nth(i)->GetType(),actuals->Nth(i)->GetResType());
                return Type::errorType;
            }
        }
        return fn->GetType();
    }
}

Location* Call::Emit(CodeGenerator *cg) {
    return NULL;
}

int Call::GetMemBytes() {
    return 0;
}

Location* Call::EmitLabel(CodeGenerator *cg) {
    return NULL;
}

int Call::GetMemBytesLabel() {
    return 0;
}

Location* Call::EmitArrayLength(CodeGenerator *cg) {
    return NULL;
}

int Call::GetMemBytesArrayLength() {
    return 0;
}

Location* Call::EmitDynamicDispatch(CodeGenerator *cg, Location *b) {
    return NULL;
}

int Call::GetMemBytesDynamicDispatch() {
    return 0;
}

bool Call::IsArrayLengthCall() {
    return false;
}

bool Call::IsMethodCall() { 
    return false;
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::creatStable() {
    
}

bool NewExpr::check() {
    return GetResType()->EqualsTo(Type::errorType);
}

Expr* NewExpr::resExpr() {
    return NULL;
}

Type * NewExpr::GetResType() {
    char * name = cType->GetTypeName();
    st_entry *ste = sTable->find(name);
    if (!ste) {
        ReportError::IdentifierNotDeclared(cType->id,LookingForClass);
        return Type::errorType;
    }
    if (ste->decl->GetType()->GetDeclType() != classDeclType && ste->decl->GetType()->GetDeclType() != varDeclType) {
        ReportError::IdentifierNotDeclared(cType->id,LookingForClass);
        return Type::errorType;
    }
    return ste->decl->GetType();
}

Location* NewExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int NewExpr::GetMemBytes() {
    return 0;
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::creatStable() {
    size->sTable->AddParent(sTable);
    size->creatStable();
}

Expr* NewArrayExpr::resExpr() {
    return NULL;
}

bool NewArrayExpr::check() {
    return GetResType()->EqualsTo(Type::errorType);
}

Type* NewArrayExpr::GetResType() {
    Assert(size != NULL && elemType != NULL);
    Type * sType = size->GetResType();
    char * tName = elemType->GetTypeName();
    if (sType->isError()) return Type::errorType;
    if (!sType->EqualsTo(Type::intType)) {
        ReportError::NewArraySizeNotInteger(size);
    }
    if (!elemType->isConstant()) {
        st_entry * ste = sTable->find(tName);
        if (!ste) {
            ReportError::IdentifierNotDeclared(new Identifier(*(elemType->GetLocation()),elemType->GetTypeName()),LookingForType);
            return Type::errorType;
        }
        if (ste->decl->GetType()->GetDeclType() != classDeclType) {
            // ReportError::IdentifierNotDeclared(cType->id,LookingForClass);
            ReportError::IdentifierNotDeclared(new Identifier(*(elemType->GetLocation()),elemType->GetTypeName()),LookingForType);
            return Type::errorType;
        }
    }
    // strcat(tName,"Array");
    return new ArrayType(*GetLocation(),elemType);
    // return new Type(tName,newArrayExpr);
}

Location* NewArrayExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int NewArrayExpr::GetMemBytes() {
    return 0;
}

Location* NewArrayExpr::EmitRuntimeSizeCheck(CodeGenerator *cg, Location *siz) {
    return NULL;
}

int NewArrayExpr::GetMemBytesRuntimeSizeCheck() {
    return 0;
}

Location* ReadIntegerExpr::Emit(CodeGenerator *cg) {
    return 0;
}

int ReadIntegerExpr::GetMemBytes() {
    return 0;
}

Type* ReadIntegerExpr::GetResType() {
    return Type::intType;
}

Location* ReadLineExpr::Emit(CodeGenerator *cg) {
    return NULL;
}

int ReadLineExpr::GetMemBytes() {
    return 0;
}
Type* ReadLineExpr::GetResType() {
    return Type::stringType;
}