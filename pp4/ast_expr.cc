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
                ReportError::IdentifierNotDeclared(fA->field,LookingForVariable);
                return Type::errorType;
            }
        }
        if (lType->EqualsTo(rType)) {
            return lType;
        } else {
            ReportError::IncompatibleOperands(op,lType,rType);
            return Type::errorType;
        }
    }
    return Type::errorType;
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
    Location* rLoc = right->Emit(cg);
    Location* tZ = cg->GenLoadConstant(0);
    Location* res = cg->GenBinaryOp(op->GetOperation(),tZ,rLoc);
    return res;
}

Location* ArithmeticExpr::EmitBinary(CodeGenerator *cg) {
    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);

    Location* res = cg->GenBinaryOp(op->GetOperation(),lLoc, rLoc);
    return NULL;
}

int ArithmeticExpr::GetMemBytesUnary() {
    return right->GetMemBytes() + 2 * CodeGenerator::VarSize;
}

int ArithmeticExpr::GetMemBytesBinary() {
    return left->GetMemBytes() + right->GetMemBytes() + CodeGenerator::VarSize;
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
    if (strcmp(op->GetOperation(), "<") == 0) {
        return EmitLess(cg,left,right);
    } else if (strcmp(op->GetOperation(), "<=") == 0) {
        return EmitLessEqual(cg,left, right);
    } else if (strcmp(op->GetOperation(), ">") == 0) {
        return EmitLess(cg, right, left);
    } else if (strcmp(op->GetOperation(), ">=") == 0) {
        return EmitLessEqual(cg, right, left);
    } else Assert(0);
    return NULL;
}

int RelationalExpr::GetMemBytes() {
    const char * ops = op->GetOperation();
    if (strcmp(ops,"<") == 0 || strcmp(ops,">") == 0)
        return GetMemBytesLess(left, right);
    else if (strcmp(ops,"<=") == 0 || strcmp(ops,">=") == 0)
        return GetMemBytesLessEqual(left, right);
    else Assert(0);
    return 0;
}

Location* RelationalExpr::EmitLess(CodeGenerator *cg, Expr *l, Expr *r) {
    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);
    Location* res = cg->GenBinaryOp("<", lLoc, rLoc);
    return res;
}

int RelationalExpr::GetMemBytesLess(Expr *l, Expr *r) {
    return left->GetMemBytes() + right->GetMemBytes() + CodeGenerator::VarSize;
}

Location* RelationalExpr::EmitLessEqual(CodeGenerator *cg, Expr *l, Expr *r) {
    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);

    Location* less = cg->GenBinaryOp("<", lLoc, rLoc);
    Location* equ = cg->GenBinaryOp("==", lLoc, rLoc);
    
    Location* res = cg->GenBinaryOp("||", less, equ);
    
    return res;
}

int RelationalExpr::GetMemBytesLessEqual(Expr *l, Expr *r) {
    return left->GetMemBytes() + right->GetMemBytes() + 3 * CodeGenerator::VarSize;
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
    if (strcmp(op->GetOperation(),"==") == 0) 
        return EmitEqual(cg);
    else if (strcmp(op->GetOperation(),"!=") == 0)
        return EmitNotEqual(cg);
    else Assert(0);
    return NULL;
}

int EqualityExpr::GetMemBytes() {
    const char * ops = op->GetOperation();
    if (strcmp(ops,"==") == 0) 
        return GetMemBytesEqual();
    else if (strcmp(ops, "!=") == 0)
        return GetMemBytesNotEqual();
    else Assert(0);
    return 0;
}

Location* EqualityExpr::EmitEqual(CodeGenerator *cg) {
    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);
    Location* res;
    if (left->GetResType()->EqualsTo(Type::stringType)){
        //builtIn stringcmp
    } else res = cg->GenBinaryOp("==",lLoc,rLoc);
    return res;
}

int EqualityExpr::GetMemBytesEqual() {
    return left->GetMemBytes() + right->GetMemBytes() + CodeGenerator::VarSize ;
}

Location* EqualityExpr::EmitNotEqual(CodeGenerator *cg) {
    //NewLabel returns const chars (label) for GenLabel 
    //cg->GenBinaryOp only suport <, ==, ||, and &&
    // so need to change != to an if-stmt
    const char *eqLabel = cg->NewLabel();
    const char *neqLabel = cg->NewLabel();

    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);
    Location* zLoc = cg->GenLoadConstant(0);
    Location* oLoc = cg->GenLoadConstant(1);
    Location* tmp = cg->GenTempVar();
    Location* res = NULL;
    if (left->GetResType()->EqualsTo(Type::stringType)) {

    } else tmp = cg->GenBinaryOp("==",lLoc, rLoc);

    cg->GenIfZ(tmp,neqLabel);
    cg->GenAssign(res, zLoc);
    cg->GenGoto(eqLabel);
    cg->GenLabel(neqLabel);
    cg->GenAssign(res, oLoc);
    cg->GenLabel(eqLabel);

    return res;
}

int EqualityExpr::GetMemBytesNotEqual() {
    return left->GetMemBytes() + right->GetMemBytes() + 4 * CodeGenerator::VarSize;
}

void LogicalExpr::creatStable() {
    if (left) {
        left->sTable->AddParent(sTable);
        left->creatStable();
    } 
    right->sTable->AddParent(sTable);
    right->creatStable(); 
}

Type* LogicalExpr::GetResType() {
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
    const char *ops = op->GetOperation();
    if (strcmp(ops, "&&") == 0) 
        return EmitAnd(cg);
    else if (strcmp(ops, "||") == 0) 
        return EmitOr(cg);
    else if (strcmp(ops, "!") == 0)
        return EmitNot(cg);
    else Assert(0);
    return NULL;
}

int LogicalExpr::GetMemBytes() {
    const char *ops = op->GetOperation();
    if (strcmp(ops, "&&") == 0) 
        return GetMemBytesAnd();
    else if (strcmp(ops, "||") == 0) 
        return GetMemBytesOr();
    else if (strcmp(ops, "!") == 0)
        return GetMemBytesNot();
    else Assert(0);
    return 0;
}

Location* LogicalExpr::EmitAnd(CodeGenerator *cg) {
    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);
    Location* res = cg->GenBinaryOp("&&",lLoc, rLoc);

    return res;
}

int LogicalExpr::GetMemBytesAnd() {
    return left->GetMemBytes() + right->GetMemBytes() + CodeGenerator::VarSize ;
}

Location* LogicalExpr::EmitOr(CodeGenerator *cg) {
    Location* lLoc = left->Emit(cg);
    Location* rLoc = right->Emit(cg);
    Location* res = cg->GenBinaryOp("||",lLoc, rLoc);

    return res;
}

int LogicalExpr::GetMemBytesOr() {
    return left->GetMemBytes() + right->GetMemBytes() + CodeGenerator::VarSize ;
}

Location* LogicalExpr::EmitNot(CodeGenerator *cg) {
    Assert(left == NULL);
    Assert(right != NULL);
    const char * oLabel = cg->NewLabel();
    const char * zLabel = cg->NewLabel();
    Location* rLoc = right->Emit(cg);
    Location* res = cg->GenTempVar();
    Location* zLoc = cg->GenLoadConstant(0);
    Location* oLoc = cg->GenLoadConstant(1);

    cg->GenIfZ(rLoc,zLabel);
    cg->GenAssign(res,oLoc);
    cg->GenGoto(oLabel);
    cg->GenLabel(zLabel);
    cg->GenAssign(res,zLoc);
    cg->GenLabel(oLabel);

    return res;
}

int LogicalExpr::GetMemBytesNot() {
    return left->GetMemBytes() + right->GetMemBytes() + 3 * CodeGenerator::VarSize ;
}

Type* AssignExpr::GetResType() {
    Assert(left != NULL && right != NULL);
    Type *lType = left->GetResType();
    Type *rType = right->GetResType();
    if (lType->isError() || rType->isError()) return Type::errorType;
    if (lType->EqualsTo(rType) && !lType->EqualsTo(Type::voidType)) {
        return lType;
    } else {
        ReportError::IncompatibleOperands(op,lType,rType);
        return Type::errorType;
    }
}

Location* AssignExpr::Emit(CodeGenerator *cg) {
    Location* rLoc = right->Emit(cg);
    LValue *lval = dynamic_cast<LValue*>(left);

    /** for LValue, which we can find mem locatioN, should just
     * store the value into the mem, but if not , the Emit 
     * function return a location of tmp value, and just 
     * assign the val to the tmp value **/
    if (lval != NULL) 
        return lval->EmitStore(cg, rLoc);
    Location *lLoc = left->Emit(cg);
    cg->GenAssign(lLoc, rLoc);
    return lLoc;
}

int AssignExpr::GetMemBytes() {
    LValue *lval = dynamic_cast<LValue*>(left);
    if (lval != NULL) 
        return right->GetMemBytes() + lval->GetMemBytesStore();
    return right->GetMemBytes() + left->GetMemBytes();
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
    const char * ops = op->GetOperation();
    if (strcmp(ops, "++"))
        return EmitPlus(cg);
    else if (strcmp(ops, "--")) 
        return EmitMinus(cg);
    else Assert(0);
    return NULL;
}

int PostfixExpr::GetMemBytes() {
    const char * ops = op->GetOperation();
    if (strcmp(ops, "++"))
        return GetMemBytesPlus();
    else if (strcmp(ops, "--")) 
        return GetMemBytesMinus();
    else Assert(0);
    return 0;
}

Location* PostfixExpr::EmitMinus(CodeGenerator *cg) {
    Location* one = cg->GenLoadConstant(1);
    Location* lLoc = left->Emit(cg);
    LValue * lVal = dynamic_cast<LValue*>(left);
    Location* tLoc = cg->GenBinaryOp("-", lLoc, one);

    if (lVal != NULL) {
        return lVal->EmitStore(cg,tLoc);
    }
    cg->GenAssign(lLoc, tLoc);
    return lLoc;
}
int PostfixExpr::GetMemBytesMinus() {
    LValue * lVal = dynamic_cast<LValue*>(left);
    if (lVal != NULL) {
        return lVal->GetMemBytesStore() + left->GetMemBytes() + CodeGenerator::VarSize;
    }
    return left->GetMemBytes() + CodeGenerator::VarSize;
}
Location* PostfixExpr::EmitPlus(CodeGenerator * cg) {
    Location* one = cg->GenLoadConstant(1);
    Location* lLoc = left->Emit(cg);
    LValue * lVal = dynamic_cast<LValue*>(left);
    Location* tLoc = cg->GenBinaryOp("+", lLoc, one);

    if (lVal != NULL) {
        return lVal->EmitStore(cg,tLoc);
    }
    cg->GenAssign(lLoc, tLoc);
    return lLoc;
}
int PostfixExpr::GetMemBytesPlus() {
    LValue * lVal = dynamic_cast<LValue*>(left);
    if (lVal != NULL) {
        return lVal->GetMemBytesStore() + left->GetMemBytes() + CodeGenerator::VarSize;
    }
    return left->GetMemBytes() + CodeGenerator::VarSize;
}

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

bool FieldAccess::check() {
    return GetResType()->EqualsTo(Type::errorType);
}

void FieldAccess::creatStable() {
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
        st_entry * ste = sTable->find(key);
        if (!ste) {
            ReportError::IdentifierNotDeclared(field,LookingForVariable);
            return Type::errorType;
        } else {
            return ste->decl->GetType();
        }
    } else {
        Type* bType = base->GetResType();
        if (bType->isError()) return Type::errorType;
        st_entry * ste = sTable->find(bType->GetTypeName());
        if (ste == NULL) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        if (ste->decl->GetDeclType() != classDeclType) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        st_entry *mte = ste->decl->sTable->Lookup(key);
        if (!mte) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        if (mte->decl->GetDeclType() == varDeclType) {
            ReportError::InaccessibleField(field,bType);
        }
        return mte->decl->GetType();
    }
}

Location* FieldAccess::Emit(CodeGenerator *cg) {
    char *key = field->GetName();
    if (base == NULL) {
        Decl * decl = sTable->find(key)->decl;
        Assert(decl != NULL);
        VarDecl* vDecl = dynamic_cast<VarDecl*> (decl);
        Assert(vDecl != NULL);
        Location *loc = vDecl->GetMemLoc();
        if (loc) return loc;
        else {}
    } else {
        /** object orient like obj.mem
         * for which need to load method or artribute before using
         * because an object is stored as a pointer as a local variable
         * so, when call a method, we need to find method address according 
         * VTable of class by VTable address and offset to the head of VTable
         * and artribute so on**/
    }
    return NULL;
}

int FieldAccess::GetMemBytes() {
    char *key = field->GetName();
    if (base == NULL) {
        VarDecl *vDecl = dynamic_cast<VarDecl*>(sTable->find(key)->decl);
        Assert(vDecl != NULL);
        Location *loc = vDecl->GetMemLoc();
        if (loc) return 0;
        else {}
    }
    return CodeGenerator::VarSize;
}

Location* FieldAccess::EmitStore(CodeGenerator *cg, Location *val) {
    char *key = field->GetName();
    if (base == NULL) {
        VarDecl *vDecl = dynamic_cast<VarDecl*>(sTable->find(key)->decl);
        Assert(vDecl != NULL);
        Location * loc = vDecl->GetMemLoc();
        if (loc) {
            cg->GenAssign(loc,val);
            return loc;
        } else {
            return NULL;
        }
    }
    /** object orient **/
    /** object.xxx **/ 
    return NULL;
}

int FieldAccess::GetMemBytesStore() {
    /** Just store value into destination, 
     * will not generation tmp value**/
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
        if (bType->isError()) return Type::errorType;
        
        st_entry * ste = sTable->find(bType->GetTypeName());
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
        st_entry *mte = ste->decl->sTable->Lookup(id);
        if (!mte) {
            ReportError::FieldNotFoundInBase(field,bType);
            return Type::errorType;
        }
        if (mte->decl->GetType()->GetDeclType() != fnDeclType) return Type::errorType;
        FnDecl * fn = dynamic_cast<FnDecl *>(mte->decl);
        List<VarDecl*> * args = fn->GetArgs();
        if (args->NumElements() != actuals->NumElements()) {
            ReportError::NumArgsMismatch(field,args->NumElements(),actuals->NumElements());
            return Type::errorType;
        }
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
            ReportError::IdentifierNotDeclared(new Identifier(*(elemType->GetLocation()),elemType->GetTypeName()),LookingForType);
            return Type::errorType;
        }
    }
    return new ArrayType(*GetLocation(),elemType);
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