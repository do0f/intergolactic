#ifndef COURSEWORK_TABLE_H
#define COURSEWORK_TABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "debug.h"
#include "entries.h"
#include "scope.h"

class Table
{
public:
  Table();
  ~Table() = default;

  void PushScope(Scope scope);
  void PopScope();

  void Lookup(Var var, bool isDeclaration, int lineno);
  void Lookup(Type type, bool isDeclaration, int lineno);

  VarEntry GetVar(std::string symbol, int lineno);
  TypeEntry GetType(std::string symbol, int lineno);

  std::shared_ptr<FuncEntry> GetReturn(int lineno);
  std::shared_ptr<StatementType> GetStatement(int lineno);

private:
  enum class EntryType
  {
    var,
    type
  };
  std::size_t lookup(std::string symbol, EntryType type, bool isDeclaration, int lineno);
  // first table is global variables, then variables in scope
  std::vector<Scope> table;
};
#endif