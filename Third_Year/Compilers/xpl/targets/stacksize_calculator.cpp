#include <string>
#include "targets/stacksize_calculator.h"
#include "ast/all.h"  // automatically generated


void xpl::stacksize_calculator::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
		node->node(i)->accept(this, lvl);
	}
}

void xpl::stacksize_calculator::do_variable_decl_node(xpl::variable_decl_node * const  node, int lvl){
  _stack_size += node->type()->size();
}

void xpl::stacksize_calculator::do_function_def_node(xpl::function_def_node * const node, int lvl) {
  node->body()->accept(this, lvl);
}

void xpl::stacksize_calculator::do_function_call_node(xpl::function_call_node * const  node, int lvl){
  if (node->parameters()){
    node->parameters()->accept(this, lvl);
  }
}

void xpl::stacksize_calculator::do_block_node(xpl::block_node * const  node, int lvl){
  if (node->declarations())
    node->declarations()->accept(this, lvl);

  if (node->instructions())
    node->instructions()->accept(this, lvl);
}

void xpl::stacksize_calculator::do_sweep_plus_node(xpl::sweep_plus_node * const  node, int lvl){
  if (node->init()){
    node->init()->accept(this, lvl);
  }
}

void xpl::stacksize_calculator::do_sweep_minus_node(xpl::sweep_minus_node * const  node, int lvl){
  if (node->init()){
    node->init()->accept(this, lvl);
  }
}
void xpl::stacksize_calculator::do_integer_node(cdk::integer_node * const node, int lvl) {

}
void xpl::stacksize_calculator::do_double_node(cdk::double_node * const node, int lvl) {

}
void xpl::stacksize_calculator::do_string_node(cdk::string_node * const node, int lvl) {

}


// remaining nodes aren't needed to calculate the stack size

void xpl::stacksize_calculator::do_neg_node(cdk::neg_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_identity_node(xpl::identity_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_not_node(cdk::not_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_add_node(cdk::add_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_sub_node(cdk::sub_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_mul_node(cdk::mul_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_div_node(cdk::div_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_mod_node(cdk::mod_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_lt_node(cdk::lt_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_le_node(cdk::le_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_ge_node(cdk::ge_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_gt_node(cdk::gt_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_ne_node(cdk::ne_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_eq_node(cdk::eq_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_and_node(cdk::and_node * const node, int lvl){}
void xpl::stacksize_calculator::do_or_node(cdk::or_node * const node, int lvl){}
void xpl::stacksize_calculator::do_identifier_node(cdk::identifier_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_assignment_node(cdk::assignment_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_print_node(xpl::print_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_read_node(xpl::read_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_while_node(xpl::while_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_if_node(xpl::if_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_if_else_node(xpl::if_else_node * const node, int lvl) {}
void xpl::stacksize_calculator::do_stop_node(xpl::stop_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_return_node(xpl::return_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_next_node(xpl::next_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_mem_alloc_node(xpl::mem_alloc_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_mem_address_node(xpl::mem_address_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_indexing_node(xpl::indexing_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_println_node(xpl::println_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_null_node(xpl::null_node * const  node, int lvl){}
void xpl::stacksize_calculator::do_function_decl_node(xpl::function_decl_node * const  node, int lvl){}