#ifndef COURSEWORK_SCOPE_H
#define COURSEWORK_SCOPE_H

#include <memory>
#include <unordered_map>
#include "entries.h"

enum class StatementType
{
  For,
  Switch
};

class Scope
{
public:
  // for simple scopes such as global, if statement or just braces
  Scope() = default;
  Scope(StatementType statement);
  Scope(FuncEntry func);
  bool IsStatement() const;
  bool IsFunc() const;

  std::shared_ptr<FuncEntry> GetFunc();
  std::shared_ptr<StatementType> GetStatement();

  std::unordered_map<std::string, Var> &GetVars();
  std::unordered_map<std::string, Type> &GetTypes();

private:
  std::unordered_map<std::string, Var> vars;
  std::unordered_map<std::string, Type> types;

  std::shared_ptr<StatementType> statement;
  std::shared_ptr<FuncEntry> func;
};


#endif