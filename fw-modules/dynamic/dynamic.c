/*
 * FlowWing Runtime Library
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This file provides the C runtime support for the FlowWing compiler,
 * including memory management (GC), dynamic typing, string manipulation,
 * and standard I/O wrappers.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdint.h>
 #include <gc.h> // Boehm GC
 
 // ==========================================
 // Constants & Definitions
 // ==========================================
 
 // Operator IDs (Must match IRGenerator.cpp)
 #define OP_ADD 1
 #define OP_SUB 2
 #define OP_MUL 3
 #define OP_DIV 4
 #define OP_MOD 5
 #define OP_EQ  6
 #define OP_NEQ 7
 #define OP_LT  8
 #define OP_LTE 9
 #define OP_GT  10
 #define OP_GTE 11
 #define OP_LOGICAL_AND 12 // &&
 #define OP_LOGICAL_OR  13 // ||
 #define OP_SLASH_SLASH 14 
 
 // Bitwise Operator IDs
 #define OP_BITWISE_AND 15 // &
 #define OP_BITWISE_OR  16 // |
 #define OP_BITWISE_XOR 17 // ^
 
 // Dynamic Value Type Tags (Must match DynamicValueType in C++)
 #define DYN_TAG_INT8    0
 #define DYN_TAG_INT32   1
 #define DYN_TAG_INT64   2
 #define DYN_TAG_FLOAT32 3
 #define DYN_TAG_FLOAT64 4
 #define DYN_TAG_STRING  5
 #define DYN_TAG_BOOLEAN 6
 #define DYN_TAG_NIRAST  7
 #define DYN_TAG_CHAR    8


 // Unary Operator IDs
#define OP_BANG  20 
#define OP_TILDE 21 
 
 // The Dynamic Value Structure
 // Layout: { i32, i64 } - Matches LLVM IR struct layout
 typedef struct {
     int32_t tag;
     int64_t value;
 } DynamicValue;
 
 // ==========================================
 // Forward Declarations
 // ==========================================
 
 void fg_panic(const char* fmt, const char* val);
 
 // String Utils
 char* fg_cs(const char* str1, const char* str2);
 char* fg_itos(int num);
 char* fg_lltos(long long num);
 char* fg_i8tos(int8_t num);
 char* fg_dtos(double f);
 char* fg_ftos(float f);
 char* fg_ctos(int c);
 
 // print
 void fg_pf(const char* str);
 
 // Dynamic Handling
 char* fg_dyn_to_string_ptr(DynamicValue* v);
 DynamicValue fg_perform_dynamic_op(DynamicValue* lhs, DynamicValue* rhs, int op);

 // ==========================================
 // Dynamic Typing Logic
 // ==========================================
 
 // Helper: Convert ANY Dynamic Value to a C string (char*)
 char* fg_dyn_to_string_ptr(DynamicValue* v) {
     switch (v->tag) {
         case DYN_TAG_INT8:    return fg_i8tos((int8_t)v->value);
         case DYN_TAG_INT32:   return fg_itos((int32_t)v->value);
         case DYN_TAG_INT64:   return fg_lltos((int64_t)v->value);
         case DYN_TAG_FLOAT32: {
             float f; memcpy(&f, &v->value, sizeof(float));
             return fg_ftos(f);
         }
         case DYN_TAG_FLOAT64: {
             double d; memcpy(&d, &v->value, sizeof(double));
             return fg_dtos(d);
         }
         case DYN_TAG_STRING:  return (char*)(intptr_t)v->value;
         case DYN_TAG_BOOLEAN: return v->value ? "true" : "false";
         case DYN_TAG_NIRAST:  return "nir";
         case DYN_TAG_CHAR:    return fg_ctos((int)v->value);
         default: return "";
     }
 }
 
 // Helper: Extract double for calculation
 double get_dyn_double(DynamicValue* v) {
     if (v->tag == DYN_TAG_FLOAT64) {
         double d; memcpy(&d, &v->value, sizeof(double)); return d;
     }
     if (v->tag == DYN_TAG_FLOAT32) {
         float f; memcpy(&f, &v->value, sizeof(float)); return (double)f;
     }
     if (v->tag == DYN_TAG_INT64 || v->tag == DYN_TAG_INT32 || v->tag == DYN_TAG_INT8) {
         return (double)v->value;
     }
     if (v->tag == DYN_TAG_BOOLEAN) return (double)v->value;
     fg_panic("Runtime Error: Invalid type for arithmetic (expected number). Tag: %d", fg_itos(v->tag));
     return 0;
 }
 
 // Helper: Extract int64 for calculation
 int64_t get_dyn_int(DynamicValue* v) {
     if (v->tag == DYN_TAG_FLOAT64 || v->tag == DYN_TAG_FLOAT32) {
         return (int64_t)get_dyn_double(v);
     }
     return v->value; // Works for Int8/32/64/Bool
 }

char* to_string_op_code(int op) {
    switch (op) {
        case OP_ADD: return "add";
        case OP_SUB: return "sub";
        case OP_MUL: return "mul";
        case OP_DIV: return "div";
        case OP_MOD: return "mod";
        case OP_EQ: return "eq";
        case OP_NEQ: return "neq";
        case OP_LT: return "lt";
        case OP_LTE: return "lte";
        case OP_GT: return "gt";
        case OP_GTE: return "gte";
        case OP_BITWISE_AND: return "bitwise_and";
        case OP_BITWISE_OR: return "bitwise_or";
        case OP_BITWISE_XOR: return "bitwise_xor";
        case OP_SLASH_SLASH: return "int_div";
        case OP_LOGICAL_AND: return "logical_and";
        case OP_LOGICAL_OR: return "logical_or";
        default: return "unknown";
    }
}
 
 // ==========================================
 // MASTER DYNAMIC OPERATION FUNCTION
 // ==========================================
 DynamicValue fg_perform_dynamic_op(DynamicValue* lhs, DynamicValue* rhs, int op) {
     DynamicValue result; 
     result.tag = DYN_TAG_NIRAST;
     result.value = 0;
 
     // String Concatenation Rule
     // If Op is ADD (+) and ANY operand is a String, cast both to String and concat.
     if (op == OP_ADD && (lhs->tag == DYN_TAG_STRING || rhs->tag == DYN_TAG_STRING)) {
         char* s1 = fg_dyn_to_string_ptr(lhs);
         char* s2 = fg_dyn_to_string_ptr(rhs);
         char* resStr = fg_cs(s1, s2);
         
         result.tag = DYN_TAG_STRING;
         result.value = (intptr_t)resStr;
         return result;
     }
 
     // Floating Point Promotion Rule
     // If any operand is float/double, promote calculation to double.
     bool is_float_op = (lhs->tag == DYN_TAG_FLOAT64 || lhs->tag == DYN_TAG_FLOAT32 ||
                         rhs->tag == DYN_TAG_FLOAT64 || rhs->tag == DYN_TAG_FLOAT32);
 
     // Exception: Bitwise ops on floats are illegal, but let's assume binder caught that. 
     // If checking runtime errors strictly:
     if (is_float_op && (op >= OP_BITWISE_AND && op <= OP_BITWISE_XOR)) {
          fg_panic("Runtime Error: Invalid operator for floating point numbers. %s\n", to_string_op_code(op));
     }
 
     if (is_float_op) {
         double left = get_dyn_double(lhs);
         double right = get_dyn_double(rhs);
         double res = 0.0;
         bool is_bool_res = false;
 
         switch(op) {
             case OP_ADD: res = left + right; break;
             case OP_SUB: res = left - right; break;
             case OP_MUL: res = left * right; break;
             case OP_DIV: 
                 if (right == 0.0) fg_panic("Runtime Error: Division by zero.", "");
                 res = left / right; 
                 break;
             // Comparisons
             case OP_EQ:  res = (left == right); is_bool_res = true; break;
             case OP_NEQ: res = (left != right); is_bool_res = true; break;
             case OP_LT:  res = (left < right);  is_bool_res = true; break;
             case OP_LTE: res = (left <= right); is_bool_res = true; break;
             case OP_GT:  res = (left > right);  is_bool_res = true; break;
             case OP_GTE: res = (left >= right); is_bool_res = true; break;
             default: fg_panic("Runtime Error: Unknown float operator.", "");
         }
 
         if (is_bool_res) {
             result.tag = DYN_TAG_BOOLEAN;
             result.value = (int64_t)res;
         } else {
             result.tag = DYN_TAG_FLOAT64;
             memcpy(&result.value, &res, sizeof(double));
         }
         return result;
     }
 
     // Integer Logic
     int64_t left = get_dyn_int(lhs);
     int64_t right = get_dyn_int(rhs);
     int64_t res = 0;
     bool is_bool_res = false;
     bool is_div_result_decimal = false; // Regular division / produces float
 
     switch(op) {
         case OP_ADD: res = left + right; break;
         case OP_SUB: res = left - right; break;
         case OP_MUL: res = left * right; break;
         case OP_SLASH_SLASH: // Integer Division
              if (right == 0) fg_panic("Runtime Error: Integer Division by zero.", "");
              res = left / right;
              break;
         case OP_DIV: // Standard Division (Promotes to Float usually)
              if (right == 0) fg_panic("Runtime Error: Division by zero.", "");
              // If perfect division, we can keep int? Usually Langs promote to float.
              // Let's implement FlowWing logic: Integers dividing always produce float unless // is used.
              {
                  double dres = (double)left / (double)right;
                  result.tag = DYN_TAG_FLOAT64;
                  memcpy(&result.value, &dres, sizeof(double));
                  return result;
              }
         case OP_MOD: 
              if (right == 0) fg_panic("Runtime Error: Modulo by zero.", "");
              res = left % right; 
              break;
              
         // Bitwise
         // Note: C bitwise ops (&, |) work on integers natively
         // Logical Operators (Returns Boolean)

        // Bitwise Operators (Returns Integer)
        case OP_BITWISE_AND: // &
            res = left & right; 
            break;
        case OP_BITWISE_OR:  // |
            res = left | right; 
            break;
        case OP_BITWISE_XOR: // ^
            res = left ^ right; 
            break;
         
 
         // Comparisons
         case OP_EQ:  res = (left == right); is_bool_res = true; break;
         case OP_NEQ: res = (left != right); is_bool_res = true; break;
         case OP_LT:  res = (left < right);  is_bool_res = true; break;
         case OP_LTE: res = (left <= right); is_bool_res = true; break;
         case OP_GT:  res = (left > right);  is_bool_res = true; break;
         case OP_GTE: res = (left >= right); is_bool_res = true; break;
         
         default: fg_panic("Runtime Error: Unknown integer operator. %s\n", to_string_op_code(op));
     }
 
     result.tag = is_bool_res ? DYN_TAG_BOOLEAN : DYN_TAG_INT64;
     result.value = res;
     return result;
 }

 // ==========================================
// MASTER DYNAMIC UNARY OPERATION FUNCTION
// ==========================================
DynamicValue fg_perform_dynamic_unary_op(DynamicValue* val, int op) {
    DynamicValue result; 
    result.tag = DYN_TAG_NIRAST;
    result.value = 0;

    // 1. Handle Logical NOT (!)
    // Rules:
    // - Bool: !val
    // - Int/Float: val == 0 is true, else false
    // - String: len == 0 is true (optional, or treated as true always)
    // - Nirast: always true
    if (op == OP_BANG) {
        bool truthy = false;
        switch(val->tag) {
            case DYN_TAG_BOOLEAN: truthy = (val->value != 0); break;
            case DYN_TAG_INT8:
            case DYN_TAG_INT32:
            case DYN_TAG_INT64:   truthy = (val->value != 0); break;
            case DYN_TAG_FLOAT32: 
            case DYN_TAG_FLOAT64: {
                double d = get_dyn_double(val);
                truthy = (d != 0.0);
                break;
            }
            case DYN_TAG_STRING:  truthy = true; break; // Non-null pointer is true
            case DYN_TAG_NIRAST:  truthy = false; break;
            default: truthy = false;
        }
        
        result.tag = DYN_TAG_BOOLEAN;
        result.value = (!truthy); // The actual NOT operation
        return result;
    }

    // 2. Handle Negation (-) and Identity (+)
    if (op == OP_SUB || op == OP_ADD) {
        bool is_float = (val->tag == DYN_TAG_FLOAT32 || val->tag == DYN_TAG_FLOAT64);
        
        if (op == OP_ADD) {
            // Unary + is effectively a no-op for numbers, but we should validate it's a number
            if (!is_float && val->tag != DYN_TAG_INT64 && val->tag != DYN_TAG_INT32 && val->tag != DYN_TAG_INT8) {
                 fg_panic("Runtime Error: Invalid type for unary plus.", "");
            }
            return *val; // Return copy
        }

        // Unary Minus (-)
        if (is_float) {
            double d = get_dyn_double(val);
            d = -d;
            result.tag = DYN_TAG_FLOAT64;
            memcpy(&result.value, &d, sizeof(double));
        } else {
            // Integer
            int64_t i = get_dyn_int(val);
            result.tag = DYN_TAG_INT64;
            result.value = -i;
        }
        return result;
    }

    // 3. Handle Bitwise NOT (~)
    if (op == OP_TILDE) {
        // Only valid for integers
        if (val->tag == DYN_TAG_FLOAT32 || val->tag == DYN_TAG_FLOAT64) {
            fg_panic("Runtime Error: Bitwise NOT (~) cannot be applied to decimals.", "");
        }
        
        int64_t i = get_dyn_int(val);
        result.tag = DYN_TAG_INT64;
        result.value = ~i;
        return result;
    }

    fg_panic("Runtime Error: Unknown unary operator. %s\n", to_string_op_code(op));
    return result;
}
 
 // Dynamic Print Function

 void fg_print_dynamic(DynamicValue* dyn_val) {
     if (!dyn_val) {
         fg_pf("(null)");
         return;
     }
     char* str = fg_dyn_to_string_ptr(dyn_val);
     fg_pf(str);
 }
 
 