#ifndef __XPL_STACKSIZE_CALCULATOR_H__
#define __XPL_STACKSIZE_CALCULATOR_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace xpl {

  class stacksize_calculator: public basic_ast_visitor {
    private:
      size_t _stack_size;

  public:
    stacksize_calculator(std::shared_ptr<cdk::compiler> compiler):
      basic_ast_visitor(compiler), _stack_size(0)
    {
    }

    size_t get_stack_size(){
      return _stack_size;
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);
    void do_not_node(cdk::not_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    void do_and_node(cdk::and_node * const node, int lvl);
    void do_or_node(cdk::or_node * const node, int lvl);

  public:
    void do_identifier_node(cdk::identifier_node * const node, int lvl);
    void do_rvalue_node(cdk::rvalue_node * const node, int lvl);
    void do_assignment_node(cdk::assignment_node * const node, int lvl);

  public:
    void do_function_def_node(xpl::function_def_node * const node, int lvl);
    void do_evaluation_node(xpl::evaluation_node * const node, int lvl);
    void do_print_node(xpl::print_node * const node, int lvl);
    void do_read_node(xpl::read_node * const node, int lvl);

  public:
    void do_while_node(xpl::while_node * const node, int lvl);
    void do_if_node(xpl::if_node * const node, int lvl);
    void do_if_else_node(xpl::if_else_node * const node, int lvl);

    void do_stop_node(xpl::stop_node * const  node, int lvl);
    void do_return_node(xpl::return_node * const  node, int lvl);
    void do_next_node(xpl::next_node * const  node, int lvl);
    void do_sweep_plus_node(xpl::sweep_plus_node * const  node, int lvl);
    void do_sweep_minus_node(xpl::sweep_minus_node * const  node, int lvl);
    void do_block_node(xpl::block_node * const  node, int lvl);
    void do_mem_alloc_node(xpl::mem_alloc_node * const  node, int lvl);
    void do_mem_address_node(xpl::mem_address_node * const  node, int lvl);
    void do_indexing_node(xpl::indexing_node * const  node, int lvl);
    void do_identity_node(xpl::identity_node * const  node, int lvl);
    void do_println_node(xpl::println_node * const  node, int lvl);
    void do_function_decl_node(xpl::function_decl_node * const  node, int lvl);
    void do_variable_decl_node(xpl::variable_decl_node * const  node, int lvl);
    void do_function_call_node(xpl::function_call_node * const  node, int lvl);
    void do_null_node(xpl::null_node * const  node, int lvl);
    
  };

} // xpl

#endif
