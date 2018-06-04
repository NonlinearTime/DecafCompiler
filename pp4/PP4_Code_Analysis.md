# PP4 代码分析

## codegen

### NewLabel

```c++
char *NewLabel();
```

- 分配一个独一无二的label名字，并返回。
- 不生成任何Tac命令。

### GenTempVar

```c++
 Location *GenTempVar();
```

- 创建并返回一个新的临时变量的Location


- 不生成Tac语句。

### GenLocalVar

```c++
Location *GenLocalVar(const char *name, int size);
```

- 创建新的局部变量的Location

### GenLoadConstant

```c++
Location *GenLoadConstant(int value);
Location *GenLoadConstant(const char *str);
```

- 根据参数创建int常量或者字符串常量，存储为新的临时变量（temp var）
- 整数0，false的布尔值，空指针NULL均加载为int 0，参数为0，大小为4B
- 传入字符串以加载字符串常量

### GenLoadLabel

```c++
Location *GenLoadLabel(const char *label);
```

- 载入新的Label，存储为新的临时变量

### GenAssign

```c++
void GenAssign(Location *dst, Location *src);
```

- 生成赋值语句对应的Tac
- 输入为复制语句的两个操作数的Location

### GenStore

```c++
void GenStore(Location *addr, Location *val, int offset = 0);
```

- 将传入的val存储到给定的合法地址所指的位置。
- 根据输入参数offset使用相对寻址，默认为0。

###GenLoad

```c++
Location *GenLoad(Location *addr, int offset = 0);
```

- 将内存指定地址处的内容读出到一个临时变量，并返回临时变量的Location
- offset默认为0

### GenBinaryOp

```c++
Location *GenBinaryOp(const char *opName, Location *op1, Location *op2);
```

- 生成二元运算的Tac指令
- 根据opName字符串判断指令的类型
- 返回值为计算结果所在位置，计算结果作为临时变量返回。

### GenPushParam

```c++
void GenPushParam(Location *param);
```

- 将单个函数参数压栈
- 压栈的函数参数以Location形式给出
- Decaf压栈顺序为从右往左压栈

### GenPopParams

```c++
void GenPopParams(int numBytesOfParams);
```

- 将参数列表全部出栈
- 参数为全部参数的总字节数
- 函数通过根据字节数调整栈顶指针实现出栈

### GenLCall

```c++
Location *GenLCall(const char *label, bool fnHasReturnValue);
```

- LCalll用于运行时调用一个Label指出的函数，跳转至Label
- 调用前必须将参数入栈
- fnHasReturnValue指出是否有返回值，有返回值则存入临时变量并返回，没有则返回NULL

### GenACall

```c++
Location *GenACall(Location *fnAddr, bool fnHasReturnValue);
```

- ACall用于运行时调用一个Location指出的函数，跳转至该地址
- fnAddr应该包含了应该跳转至的目标地址
- fnAddr一般由vtable中读出

### GenBuiltInCall

```c++
              // These codes are used to identify the built-in functions
typedef enum { Alloc, ReadLine, ReadInteger, StringEqual,
               PrintInt, PrintString, PrintBool, Halt, NumBuiltIns } BuiltIn;
Location *GenBuiltInCall(BuiltIn b, Location *arg1 = NULL, Location *arg2 = NULL);
```

- 生成调用内置函数的Tac指令
- b指定调用函数
- 根据不同函数给出参数，默认为NULL

### GenIfZ

```c++
void GenIfZ(Location *test, const char *label);
```

- 生成分支语句Tac指令
- test为测试结果地址，label为目标地址

### GenGoto

```c++
void GenGoto(const char *label);
```

- GOTO语句
- label为跳转目标地址

### GenReturn 

```c++
void GenReturn(Location *val = NULL);
```

- 若return并不返回一个值那么参数为NULL

### GenLabel

```c++
void GenLabel(const char *label);
```

- 生成Label

### GenBeginFucn && GenEndFunc

```c++
// These methods generate the Tac instructions that mark the start
// and end of a function/method definition.
BeginFunc *GenBeginFunc();
void GenEndFunc();
```

### GenVTable

```c++
void GenVTable(const char *className, List<const char*> *methodLabels);
```

- 生成定义vtable的Tac指令串
- methodLabel为一个方法label的list
- className指出该VTable属于哪一个类

### DoFinalCodeGen

```c++
void DoFinalCodeGen();
```

- 目标代码生成工作，即将中间代码TAC翻译成MIPS汇编代码，并输出到标准输出流
- 如果debug标识tac打开，(-d tac)，将不会翻译成MIPS,而是将未翻译的TAC语句输出到标准输出流
- 有益于debug!!!

## Tac

```c++
    // A Location object is used to identify the operands to the
    // various TAC instructions. A Location is either fp or gp
    // relative (depending on whether in stack or global segemnt)
    // and has an offset relative to the base of that segment.
    // For example, a declaration for integer num as the first local
    // variable in a function would be assigned a Location object
    // with name "num", segment fpRelative, and offset -8.

typedef enum {fpRelative, gpRelative} Segment;

  // for convenience, the instruction classes are listed here.
  // the interfaces for the classes follows below

  class LoadConstant;
  class LoadStringConstant;
  class LoadLabel;
  class Assign;
  class Load;
  class Store;
  class BinaryOp;
  class Label;
  class Goto;
  class IfZ;
  class BeginFunc;
  class EndFunc;
  class Return;
  class PushParam;
  class RemoveParams;
  class LCall;
  class ACall;
  class VTable;
```

### Location

```c++
class Location
{
  protected:
    const char *variableName;
    Segment segment;
    int offset;

  public:
    Location(Segment seg, int offset, const char *name);

    const char *GetName()           { return variableName; }
    Segment GetSegment()            { return segment; }
    int GetOffset()                 { return offset; }

    friend ostream& operator<<(ostream& out, Location *loc);
};

```

- variableName:变量名
- segment: 标识全局变量还是局部变量(function内)
  - fpRelative：局部变量
  - gpRelative：全局变量
- offset：相对段基址的偏移地址

### Instruction

```c++
  // base class from which all Tac instructions derived
  // has the interface for the 2 polymorphic messages: Print & Emit

class Instruction {
    protected:
        char printed[128];

    public:
        virtual ~Instruction() {}
	virtual void Print();
	virtual void EmitSpecific(Mips *mips) = 0;
	virtual void Emit(Mips *mips);
};
```

## MIPS

### Register

```c++
typedef enum {zero, at, v0, v1, a0, a1, a2, a3,
			t0, t1, t2, t3, t4, t5, t6, t7,
			s0, s1, s2, s3, s4, s5, s6, s7,
			t8, t9, k0, k1, gp, sp, fp, ra, NumRegs } Register;
```

- 枚举类型，给32个寄存器编号，以及便于记忆

### RegContents

```c++
struct RegContents {
	bool isDirty;
	Location *var;
	const char *name;
	bool isGeneralPurpose;
    } regs[NumRegs];

```

- 寄存器内容结构体
- isDirty: 是否是脏数据，是则在下一次写入该寄存器时写回内存(使用sw语句)
- var: 寄存器中值
- name: 寄存器名字
- isGeneralPurpose: 是否为通用寄存器

寄存器组初始化

```c++
Mips::Mips() {
  mipsName[BinaryOp::Add] = "add";
  mipsName[BinaryOp::Sub] = "sub";
  mipsName[BinaryOp::Mul] = "mul";
  mipsName[BinaryOp::Div] = "div";
  mipsName[BinaryOp::Mod] = "rem";
  mipsName[BinaryOp::Eq] = "seq";
  mipsName[BinaryOp::Less] = "slt";
  mipsName[BinaryOp::And] = "and";
  mipsName[BinaryOp::Or] = "or";
  regs[zero] = (RegContents){false, NULL, "$zero", false};
  regs[at] = (RegContents){false, NULL, "$at", false};
  regs[v0] = (RegContents){false, NULL, "$v0", false};
  regs[v1] = (RegContents){false, NULL, "$v1", false};
  regs[a0] = (RegContents){false, NULL, "$a0", false};
  regs[a1] = (RegContents){false, NULL, "$a1", false};
  regs[a2] = (RegContents){false, NULL, "$a2", false};
  regs[a3] = (RegContents){false, NULL, "$a3", false};
  regs[k0] = (RegContents){false, NULL, "$k0", false};
  regs[k1] = (RegContents){false, NULL, "$k1", false};
  regs[gp] = (RegContents){false, NULL, "$gp", false};
  regs[sp] = (RegContents){false, NULL, "$sp", false};
  regs[fp] = (RegContents){false, NULL, "$fp", false};
  regs[ra] = (RegContents){false, NULL, "$ra", false};
  regs[t0] = (RegContents){false, NULL, "$t0", true};
  regs[t1] = (RegContents){false, NULL, "$t1", true};
  regs[t2] = (RegContents){false, NULL, "$t2", true};
  regs[t3] = (RegContents){false, NULL, "$t3", true};
  regs[t4] = (RegContents){false, NULL, "$t4", true};
  regs[t5] = (RegContents){false, NULL, "$t5", true};
  regs[t6] = (RegContents){false, NULL, "$t6", true};
  regs[t7] = (RegContents){false, NULL, "$t7", true};
  regs[t8] = (RegContents){false, NULL, "$t8", true};
  regs[t9] = (RegContents){false, NULL, "$t9", true};
  regs[s0] = (RegContents){false, NULL, "$s0", true};
  regs[s1] = (RegContents){false, NULL, "$s1", true};
  regs[s2] = (RegContents){false, NULL, "$s2", true};
  regs[s3] = (RegContents){false, NULL, "$s3", true};
  regs[s4] = (RegContents){false, NULL, "$s4", true};
  regs[s5] = (RegContents){false, NULL, "$s5", true};
  regs[s6] = (RegContents){false, NULL, "$s6", true};
  regs[s7] = (RegContents){false, NULL, "$s7", true};
  lastUsed = zero;
}
const char *Mips::mipsName[BinaryOp::NumOps];
```

### GetRegister

源代码：

```c++
Mips::Register Mips::GetRegister(Location *var, Reason reason,
					   Register avoid1, Register avoid2)
{
  Register reg;

  if (!FindRegisterWithContents(var, reg)) {
    if (!FindRegisterWithContents(NULL, reg)) { 
      reg = SelectRegisterToSpill(avoid1, avoid2);
      SpillRegister(reg);
    }
    regs[reg].var = var;
    if (reason == ForRead) {                 // load current value
      Assert(var->GetOffset() % 4 == 0); // all variables are 4 bytes
      const char *offsetFromWhere = var->GetSegment() == fpRelative? regs[fp].name : regs[gp].name;
      Emit("lw %s, %d(%s)\t# load %s from %s%+d into %s", regs[reg].name,
	    var->GetOffset(), offsetFromWhere, var->GetName(),
	    offsetFromWhere, var->GetOffset(), regs[reg].name);
	    regs[reg].isDirty = false;
    }
  }
  if (reason == ForWrite)
    regs[reg].isDirty = true;
  return reg;
}
```

- 方法作用：找出合适的寄存器

> \* Given a location for a current var, a reason (ForRead or ForWrite)
>
>  \* and up to two registers to avoid, this method will assign
>
>  \* to a var to register trying these alternatives in order:
>
>  \*  1) if that var is already in a register ("same" is determined
>
>  \*     by matching name and same scope), we use that one
>
>  \*  2) find an empty register to use for the var
>
>  \*  3) find an in-use register that is not dirty.  We don't need
>
>  \*     to write value back to memory since it's clean, so we just
>
>  \*     replace with the new var
>
>  \*  4) spill an in-use, dirty register, by writing its contents to
>
>  \*     memory and then replace with the new var
>
>  \* For steps 3 & 4, we respect the registers given to avoid (ie the
>
>  \* other operands in this operation). The register descriptors are
>
>  \* updated to show the new state of the world. If for read, we
>
>  \* load the current value from memory into the register. If for
>
>  \* write, we mark the register as dirty (since it is getting a
>
>  \* new value).

代码解析

```c++
if (!FindRegisterWithContents(var, reg)) {
    ...
}
if (reason == ForWrite)
    regs[reg].isDirty = true;
  return reg;
```

- 寄存器采用延迟写策略，将寄存器内容写入内存时，仅将dirty为置为1.
- 查找寄存器组中是否有已经存放了var的寄存器，若有，则判断是否为将寄存器内容写入内存。若是，则将dirty置1。
- 不存在这样的寄存器时，进行下一步

```c++
 if (!FindRegisterWithContents(var, reg)) {
    if (!FindRegisterWithContents(NULL, reg)) { 
      ...
    }
    regs[reg].var = var;
    if (reason == ForRead) {                 // load current value
      Assert(var->GetOffset() % 4 == 0); // all variables are 4 bytes
      const char *offsetFromWhere = var->GetSegment() == fpRelative? regs[fp].name : regs[gp].name;
      Emit("lw %s, %d(%s)\t# load %s from %s%+d into %s", regs[reg].name,
	    var->GetOffset(), offsetFromWhere, var->GetName(),
	    offsetFromWhere, var->GetOffset(), regs[reg].name);
	    regs[reg].isDirty = false;
    }
  }
```

- 查找未使用的寄存器，若有则将数据Location填入
- 判断是否为从内存将数据读入该寄存器，若是则生成LW指令，并将dirty位置0
- 不存在未使用的寄存器的情况，转下一步

```c++
if (!FindRegisterWithContents(NULL, reg)) { 
      reg = SelectRegisterToSpill(avoid1, avoid2);
      SpillRegister(reg);
    }
```

- 找出最佳寄存器(不包含avoid1与avoid2这两个应该避免的寄存器)，使得
  - 寄存器数据尽量不为脏数据
  - 若全部包含脏数据，选择最靠近上次使用过的寄存器的寄存器
- 将脏数据(若有)写回内存，方法为生成一条sw语句

