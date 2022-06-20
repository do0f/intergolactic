#ifndef COURSEWORK_ENTRIES_H
#define COURSEWORK_ENTRIES_H

#include <string>
#include <vector>

struct IType
{
  virtual ~IType() = default;
  virtual std::string print() = 0;
};

struct Basic: IType
{
  Basic(const std::string& name): name(name)
  {
  }
  virtual ~Basic() = default;
  std::string print() override
  {
    return name;
  }
  std::string name;
};

struct Slice: IType
{
  Slice(IType *underlying) : underlying(underlying)
  {
  }
  virtual ~Slice() = default;
  std::string print() override
  {
    return "[]" + underlying->print();
  }
  IType* underlying;
};

struct Pointer: public IType
{
  Pointer(IType *underlying) : underlying(underlying)
  {
  }
  virtual ~Pointer() = default;
  std::string print() override
  {
    return "*" + underlying->print();
  }
  IType* underlying;
};

struct Value
{
  Value(void* value, IType* type): value(value), type(type)
  {
  }
  void* value;
  IType* type;
};

struct Var
{
  Var(const std::string& name, Value* value): name(name), value(value)
  {
  }
  std::string name;
  Value* value;
};

struct VarEntry
{
  VarEntry() = default;
  VarEntry(std::string symbol, std::string datatype);

  std::string symbol;
  std::string datatype;
};

struct TypeEntry
{
  TypeEntry() = default;
  TypeEntry(std::string symbol);
};

struct FuncEntry
{
  FuncEntry() = default;
  FuncEntry(std::string symbol, std::vector<VarEntry> arguments, std::vector<std::string> returns);

  std::string symbol;
  std::vector<VarEntry> arguments;
  std::vector<std::string> returns;
};

#endif