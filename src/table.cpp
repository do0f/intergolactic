#include "table.h"
#include "builtin.h"
#include "util.h"

// global table
// needs to have builtin stuff
Table::Table()
{
  Scope globalScope;
  auto &types = globalScope.GetTypes();
  for (const auto &basicType : basicTypes)
  {
    types[basicType] = TypeEntry{basicType};
  }

  auto &vars = globalScope.GetVars();
  for (const auto &basicFunc : basicFunctions)
  {
    vars[basicFunc.symbol] = basicFunc;
  }

  table.push_back(globalScope);
}

void Table::PushScope(Scope scope)
{
  table.push_back(scope);
}

void Table::PopScope()
{
  table.pop_back();
}

std::size_t Table::lookup(std::string symbol, EntryType type, bool isDeclaration, int lineno)
{
  switch (type)
  {
  case EntryType::var:
    DEBUG_PRINT("lookup var %s\n", symbol.c_str());
    break;
  case EntryType::type:
    DEBUG_PRINT("lookup type %s\n", symbol.c_str());
    break;
  }

  int foundScope = 0;
  for (int scopeNum = table.size() - 1; scopeNum >= 0; --scopeNum)
  {
    bool found = false;
    auto scope = table[scopeNum];
    switch (type)
    {
    case EntryType::var:
      found = scope.GetVars().find(symbol) != scope.GetVars().cend();
      break;
    case EntryType::type:
      found = scope.GetTypes().find(symbol) != scope.GetTypes().cend();
      break;
    }

    if (found)
    {
      foundScope = scopeNum + 1;
      break;
    }
  }

  // if its being referenced without initialisation
  if (!isDeclaration && foundScope == 0)
  {
    printf("\033[0;31m Line : %d | Semantic Error : %s is not defined\n \n\033[0m\n", lineno, symbol.c_str());
    exit(1);
  }
  // if variable was found in same scope
  if (isDeclaration && foundScope == table.size())
  {
    printf("\033[0;31m Line : %d | Semantic Error : %s is already defined, can't redefine identifier.\n \n\033[0m\n", lineno, symbol.c_str());
    exit(1);
  }

  return foundScope;
}

void Table::Lookup(Var var, bool isDeclaration, int lineno)
{
  const auto foundScope = lookup(var.name, EntryType::var, isDeclaration, lineno);
  if (isDeclaration)
  {
    table[table.size() - 1].GetVars()[var.name] = var;
  }
}

void Table::Lookup(IType* type, bool isDeclaration, int lineno)
{
  const auto foundScope = lookup(type.name, EntryType::type, isDeclaration, lineno);
  if (isDeclaration)
  {
    table[table.size() - 1].GetTypes()[type.name] = type;
  }
}

Var Table::GetVar(const std::string& name, int lineno)
{
  for (int scope = table.size() - 1; scope > 0; --scope)
  {
    auto var = table[scope].GetVar(name);
    if (var.name != "")
    {
      return var;
    }
  }
  ErrorVarNotFound(name, lineno);
}

TypeEntry Table::GetType(std::string symbol, int lineno)
{
  const auto foundScope = lookup(symbol, EntryType::type, false, lineno);
  const auto entry = table[foundScope - 1].GetTypes().find(symbol);
  return entry->second;
}

std::shared_ptr<FuncEntry> Table::GetReturn(int lineno)
{
  DEBUG_PRINT("%d: looking for return scope\n", lineno);
  for (auto &scope : this->table)
  {
    if (!scope.IsFunc())
    {
      continue;
    }
    return scope.GetFunc();
  }

  printf("\033[0;31m Line : %d | Syntax Error : return statement can't be used not in function.\n \n\033[0m\n", lineno);
  exit(1);
}

std::shared_ptr<StatementType> Table::GetStatement(int lineno)
{
  DEBUG_PRINT("%d: looking for statement scope\n", lineno);
  for (auto &scope : this->table)
  {
    if (!scope.IsStatement())
    {
      continue;
    }
    return scope.GetStatement();
  }

  printf("\033[0;31m Line : %d | Syntax Error : break of continue statement can't be used not in for or switch.\n \n\033[0m\n", lineno);
  exit(1);
}