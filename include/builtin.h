#ifndef COURSEWORK_BUILTIN_H
#define COURSEWORK_BUILTIN_H

#include "entries.h"

namespace builtin
{
    static Type inttype = Type{"int"};
    static Type int32type = Type{"int32"};
    static Type int64type = Type{"int64"};

    static Type uinttype = Type{"uint"};
    static Type uint32type = Type{"uint32"};
    static Type uint64type = Type{"uint64"};

    static Type stringtype = Type{"string"};
    static Type runetype = Type{"rune"};
    static Type bytetype = Type{"byte"};

    static Type float32type = Type{"float32"};
    static Type float64type = Type{"float64"};

    static Type booltype = Type{"bool"};
    static Type empty = Type{""};

    static const auto basicTypes = {inttype, int32type, int64type, uinttype, uint32type, uint64type, stringtype, runetype, bytetype, float32type, float64type, booltype};

    static const auto append = VarEntry{"append", "func ([]Type, ...Type) ([]Type)"};

    static const auto basicFunctions = {append};
}

#endif