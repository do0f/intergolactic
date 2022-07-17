#ifndef COURSEWORK_BUILTIN_H
#define COURSEWORK_BUILTIN_H

#include "entries.h"

namespace builtin
{
    // Types:
    static const Basic any_type = Basic{"any"};
    static const Basic bool_type = Basic{"bool"};
    static const Basic byte_type = Basic{"byte"};
    static const Basic comparable_type = Basic{"comparable"};

    static const Basic complex64_type = Basic{"complex64"};
    static const Basic complex128_type = Basic{"complex128"};
    static const Basic error_type = Basic{"error"};
    static const Basic float32_type = Basic{"float32"};
    static const Basic float64_type = Basic{"float64"};

    static const Basic int_type = Basic{"int"};
    static const Basic int8_type = Basic{"int8"};
    static const Basic int16_type = Basic{"int16"};
    static const Basic int32_type = Basic{"int32"};
    static const Basic int64_type = Basic{"int64"};
    static const Basic rune_type = Basic{"rune"};
    static const Basic string_type = Basic{"string"};

    static const Basic uint_type = Basic{"uint"};
    static const Basic uint8_type = Basic{"uint8"};
    static const Basic uint16_type = Basic{"uint16"};
    static const Basic uint32_type = Basic{"uint32"};
    static const Basic uint64_type = Basic{"uint64"};
    static const Basic uintptr_type = Basic{"uintptr"};

    static Basic empty = Basic{""};

    static const auto basicTypes = {any_type, bool_type, byte_type, comparable_type,
    complex64_type, complex128_type, error_type, float32_type, float64_type,
    int_type, int8_type, int16_type, int32_type, int64_type, rune_type, string_type,
    uint_type, uint8_type, uint16_type, uint32_type, uint64_type, uintptr_type};

    // Constants:
    static const Value true_value = Value{nullptr, &bool_type};
    static const Value false_value = Value{nullptr, &bool_type};
    static const Value iota_value = Value{nullptr, &int_type};

    // Zero value:
    static const Basic nil_value = Basic{"nil"};

    // Functions:
    static const auto append = VarEntry{"append", "func ([]Type, ...Type) ([]Type)"};

    static const auto basicFunctions = {append};
}

#endif