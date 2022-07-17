#include <iostream>

#include <fmt/core.h>
#include <fmt/color.h>

#include "util.h"
#include "debug.h"
#include "builtin.h"

void Log(const std::string &msg, int lineno)
{
  fmt::print("line {}: {}\n", lineno, msg);
}

void Error(const std::string &msg, int lineno)
{
  fmt::print("line {}: {}: {}\n", lineno, fmt::format(fmt::fg(fmt::color::red), "error"), fmt::format(fmt::emphasis::bold, "{}", msg));
  exit(1);
}

void ErrorTypeMismatch(IType* ltype, IType* rtype, int lineno)
{
  auto msg = fmt::format("type mismatch {} and {}", ltype->print(), rtype->print());
  Error(msg, lineno);
}

void ErrorSizeMismatch(std::size_t lsize, std::size_t rsize, int lineno)
{
  auto msg = fmt::format("size mismatch {} and {}", lsize, rsize);
  Error(msg, lineno);
}

void ErrorVarNotFound(const std::string& name, int lineno)
{
  auto msg = fmt::format("variable {} not found", name);
  Error(msg, lineno);
}

std::vector<std::string> GetTypes(const std::vector<VarEntry> &entries)
{
  std::vector<std::string> types;
  for (const auto &entry : entries)
  {
    types.push_back(entry.datatype);
  }
  return types;
}

std::string Join(const std::vector<std::string> &vec)
{
  std::string str;
  for (size_t i = 0; i != vec.size(); ++i)
  {
    str = str + vec[i];
    if (i != vec.size() - 1)
    {
      str += ",";
    }
  }

  return str;
}

Basic* ToBasic(IType* type)
{
  return dynamic_cast<Basic*>(type);
} 

Slice* ToSlice(IType* type)
{
  return dynamic_cast<Slice*>(type);
}

void TypeCheck(IType* ltype, IType* rtype, int lineno)
{
  Log(fmt::format("type check {} and {}", ltype->print(), rtype->print()), lineno);

  auto lBasic = ToBasic(ltype);
  auto rBasic = ToBasic(rtype);
  if (lBasic != nullptr || rBasic != nullptr)
  {
    if ((lBasic != nullptr) != (rBasic != nullptr))
    {
      ErrorTypeMismatch(ltype, rtype, lineno);
    }

    if (lBasic->name != rBasic->name)
    {
      ErrorTypeMismatch(ltype, rtype, lineno);
    }
    return;
  }

  auto lSlice = ToSlice(ltype);
  auto rSlice = ToSlice(rtype);
  if (lSlice != nullptr || rSlice != nullptr)
  {
    if ((lSlice != nullptr) != (rSlice != nullptr))
    {
      ErrorTypeMismatch(ltype, rtype, lineno);
    }

    TypeCheck(lSlice->underlying, rSlice->underlying, lineno);
    return;
  }
}

void TypeCheck(const std::vector<IType*> &ltypes, std::vector<IType*> rtypes, int lineno)
{
  SizeCheck(ltypes, rtypes, lineno);
  for (std::size_t i = 0; i < ltypes.size(); ++i)
  {
    TypeCheck(ltypes[i], rtypes[i], lineno);
  }
}

template<typename T>
void SizeCheck(const std::vector<T> &r, const std::vector<T> &l, int lineno)
{
  if (r.size() != l.size())
  {
    ErrorSizeMismatch(r.size(), l.size(), lineno);
  }
}

std::vector<std::string> SplitList(std::string list)
{
	std::vector<std::string> res;
	if (list == "")
	{
		return res;
	}

	std::string delimiter = ",";

	std::size_t pos = 0;
	std::string token;
	while ((pos = list.find(delimiter)) != std::string::npos) 
	{
    	token = list.substr(0, pos);
		res.push_back(token);
    	list.erase(0, pos + delimiter.length());
	}
	res.push_back(list);

	return res;
}

std::string FuncType(std::string args, std::string returns)
{
	return "func (" + args + ") (" + returns + ")";
}

std::pair<std::string, std::string> FromFuncType(std::string funcType)
{
	std::string args;
	std::string returns;
    auto betweenBrackets = [](std::string& str){
        const auto leftBr = str.find('(');
        const auto rightBr = str.find(')');
        const auto res = std::string(str.begin() + leftBr + 1, str.begin() + rightBr);
        str.erase(leftBr, res.size() + 2);
        return res;
    };
	args = betweenBrackets(funcType);
    returns = betweenBrackets(funcType);
    return std::pair<std::string, std::string>{args, returns};
}

std::vector<std::string> GetTypesOfArgs(std::vector<std::string> args)
{
	std::vector<std::string> types;
	for (auto& arg: args)
	{
		arg.erase(arg.begin(), arg.begin() + arg.find(' ') + 1);
		types.push_back(arg);
	}
	return types;
}

VarEntry GetVarEntry(std::string arg)
{
	std::string symbol;
	std::string type;
	std::string delimiter = " ";
	const auto pos = arg.find(delimiter);
	symbol = arg.substr(0, pos);
	arg.erase(0 + delimiter.length());
	type = arg;
	return VarEntry{symbol, type};
}

std::string GetSliceType(std::string slice)
{
    if (slice == stringtype)
    {
        return runetype;
    }
	// erase []
	return slice.erase(0, 2);
}

bool IsBasicType(std::string type)
{
	for (const auto basicType: basicTypes)
	{
		if (type == basicType)
		{
			return true;
		}
	}
	return false;
}

bool IsSliceType(std::string type)
{
    if (type == stringtype || type.size() >= 2 && type[0] == '[' && type[1] == ']')
    {
        return true;
    }
    return false;
}