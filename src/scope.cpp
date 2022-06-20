#include "scope.h"

Scope::Scope(StatementType statement)
{
    this->statement = std::make_shared<StatementType>(statement);
}
Scope::Scope(FuncEntry func)
{
    this->func = std::make_shared<FuncEntry>(func);
}
bool Scope::IsStatement() const
{
    return statement != nullptr;
}
bool Scope::IsFunc() const
{
    return func != nullptr;
}

std::shared_ptr<FuncEntry> Scope::GetFunc()
{
    return func;
}
std::shared_ptr<StatementType> Scope::GetStatement()
{
    return statement;
}

std::unordered_map<std::string, Var> &Scope::GetVars()
{
    return vars;
}
std::unordered_map<std::string, Type> &Scope::GetTypes()
{
    return types;
}