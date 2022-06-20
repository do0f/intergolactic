#include "entries.h"

VarEntry::VarEntry(std::string symbol, std::string datatype): symbol(symbol), datatype(datatype)
{
}

TypeEntry::TypeEntry(std::string symbol): symbol(symbol)
{
}

FuncEntry::FuncEntry(std::string symbol, std::vector<VarEntry> arguments, std::vector<std::string> returns): 
  symbol(symbol), arguments(arguments), returns(returns)
{
}