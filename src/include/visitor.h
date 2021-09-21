#ifndef VISITOR_H
#define VISITOR_H
#include "AST.h"

typedef struct VISITOR_STRUCT {} visitor_t;

visitor_t* init_visitor();

AST_T* visitor_visit(visitor_t* visitor, AST_T* node);

AST_T* visitor_visit_variable_definition(visitor_t* visitor, AST_T* node);

AST_T* visitor_visit_function_definition(visitor_t* visitor, AST_T* node);

AST_T* visitor_visit_variable(visitor_t* visitor, AST_T* node);

AST_T* visitor_visit_function_call(visitor_t* visitor, AST_T* node);

AST_T* visitor_visit_string(visitor_t* visitor, AST_T* node);

AST_T* visitor_visit_compound(visitor_t* visitor, AST_T* node);

#endif

