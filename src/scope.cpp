#include "scope.h"
#include "util.h"

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

Var Scope::GetVar(const std::string& name)
{
    const auto var = vars.find(name);
    if (var == vars.cend())
    {
        return Var("", nullptr);
    }
    return var->second;
}

std::unordered_map<std::string, IType*> &Scope::GetTypes()
{
    return types;
}