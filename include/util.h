
#ifndef COURSEWORK_UTIL_H
#define COURSEWORK_UTIL_H

#include <string>
#include <vector>

#include "entries.h"

void Log(const std::string &msg, int lineno);
void Error(const std::string &msg, int lineno);
void ErrorTypeMismatch(IType* ltype, IType* rtype, int lineno);
void ErrorSizeMismatch(std::size_t lsize, std::size_t rsize, int lineno);
void ErrorVarNotFound(const std::string& name, int lineno);


std::vector<std::string> GetTypes(const std::vector<VarEntry> &entries);
void TypeCheck(const std::vector<std::string> &type1, std::vector<std::string> type2, int lineno);
void SizeCheck(const std::vector<std::string> &ids, const std::vector<std::string> &types, int lineno);

std::string Join(const std::vector<std::string> &vec);

std::vector<std::string> SplitList(std::string list);

std::string FuncType(std::string args, std::string returns);

std::pair<std::string, std::string> FromFuncType(std::string funcType);

std::vector<std::string> GetTypesOfArgs(std::vector<std::string> args);

VarEntry GetVarEntry(std::string arg);

std::string GetSliceType(std::string slice);

bool IsBasicType(std::string type);

bool IsSliceType(std::string type);

#endif