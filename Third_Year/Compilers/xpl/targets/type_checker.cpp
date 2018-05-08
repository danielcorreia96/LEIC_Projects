#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }


inline basic_type * generateType(basic_type * type) {
  basic_type * new_type = new basic_type(type->size(), type->name());
  if (type->subtype()){
	  new_type->_subtype = generateType(type->subtype());
  }
  return new_type;
}

inline void forceConvertUnspecToInt(basic_type * target){
  if(target->name() == basic_type::TYPE_UNSPEC)
  {
    target->_name  = basic_type::TYPE_INT;
    target->_size  = 4;
  }
}


inline void checkUnspecTypes(basic_type * left, basic_type * right){
  if(left->name() == basic_type::TYPE_POINTER &&
     right->name() == basic_type::TYPE_POINTER)
  {
    checkUnspecTypes(left->subtype(),right->subtype());
  }

  if(left->name() == basic_type::TYPE_UNSPEC &&
     right->name() == basic_type::TYPE_UNSPEC)
  {
    left->_name  = basic_type::TYPE_INT;
    left->_size  = 4;
    right->_name = basic_type::TYPE_INT;
    right->_size = 4;
  }
  else if (left->name() == basic_type::TYPE_UNSPEC){
    left->_name = right->name();
    left->_size = right->size();
  }
  else if (right->name() == basic_type::TYPE_UNSPEC){
    right->_name = left->name();
    right->_size = left->size();
  }
}

inline void validateTypes(cdk::expression_node * left, cdk::expression_node * right){
  // check if types exist in the xpl language
  if (left->type()->name() != basic_type::TYPE_INT &&
      left->type()->name() != basic_type::TYPE_DOUBLE &&
      left->type()->name() != basic_type::TYPE_POINTER){
        throw std::string("unknown left side type");
  }
  if (right->type()->name() != basic_type::TYPE_INT &&
      right->type()->name() != basic_type::TYPE_DOUBLE &&
      right->type()->name() != basic_type::TYPE_POINTER){
        throw std::string("unknown left side type");
  }

  // check for unspec types situations
  checkUnspecTypes(left->type(), right->type());
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void xpl::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

inline void xpl::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void xpl::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void xpl::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of binary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  

  validateTypes(node->left(), node->right());

  // casos de soma com ponteiros
  if (node->left()->type()->name() == basic_type::TYPE_POINTER &&
      node->right()->type()->name() == basic_type::TYPE_POINTER){
      throw std::string("nao podemos somar dois ponteiros...");
  }
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_POINTER){
      node->type(generateType(node->right()->type()));
  }
  else if (node->left()->type()->name() == basic_type::TYPE_POINTER &&
           node->right()->type()->name() == basic_type::TYPE_INT){
      node->type(generateType(node->left()->type()));
  }
  else{
    // double + double ou inteiro + inteiro
    if (node->left()->type()->name() == node->right()->type()->name()){
      node->type(generateType(node->left()->type()));
    }
    // double + inteiro ou inteiro + double
    else if ((node->left()->type()->name() == basic_type::TYPE_INT &&
             node->right()->type()->name() == basic_type::TYPE_DOUBLE) ||
             (node->left()->type()->name() == basic_type::TYPE_DOUBLE &&
             node->right()->type()->name() == basic_type::TYPE_INT)){
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
  }
}
void xpl::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  // processBinaryExpression(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  validateTypes(node->left(), node->right());

  // caso 1: subtrair ponteiro com ponteiro -> tem de ser os dois do mesmo tipo
  if (node->left()->type()->name() == basic_type::TYPE_POINTER &&
      node->right()->type()->name() == basic_type::TYPE_POINTER)
  {
    if (node->left()->type()->subtype()->name() == node->right()->type()->subtype()->name()) {
      node->type(new basic_type(4, basic_type::TYPE_INT));
    }
    else {
        throw std::string("ponteiros na subtracao nao podem ser de tipos diferentes!!");
    }
  }
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_POINTER){
      node->type(generateType(node->right()->type()));
  }
  else if (node->left()->type()->name() == basic_type::TYPE_POINTER &&
           node->right()->type()->name() == basic_type::TYPE_INT){
      node->type(generateType(node->left()->type()));
  }
  else{
    // double + double ou inteiro + inteiro
    if (node->left()->type()->name() == node->right()->type()->name()){
      node->type(generateType(node->left()->type()));
    }
    // double + inteiro ou inteiro + double
    else if ((node->left()->type()->name() == basic_type::TYPE_INT &&
             node->right()->type()->name() == basic_type::TYPE_DOUBLE) ||
             (node->left()->type()->name() == basic_type::TYPE_DOUBLE &&
             node->right()->type()->name() == basic_type::TYPE_INT)){
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
  }
}
void xpl::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  // processBinaryExpression(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  validateTypes(node->left(), node->right());

  // nao podemos multiplicar com ponteiros
  if (node->left()->type()->name()  == basic_type::TYPE_POINTER ||
      node->right()->type()->name() == basic_type::TYPE_POINTER)
  {
    throw std::string("existem ponteiros na multiplicacao ");
  }

  // double + double ou inteiro + inteiro
  if (node->left()->type()->name() == node->right()->type()->name()){
    node->type(generateType(node->left()->type()));
  }
  // double + inteiro ou inteiro + double
  else if ((node->left()->type()->name() == basic_type::TYPE_INT &&
            node->right()->type()->name() == basic_type::TYPE_DOUBLE) ||
            (node->left()->type()->name() == basic_type::TYPE_DOUBLE &&
            node->right()->type()->name() == basic_type::TYPE_INT)){
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }

}
void xpl::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  node->type(new basic_type(4, basic_type::TYPE_INT));
}
void xpl::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(generateType(symbol->type()));
    
  }
  else {
    throw id;
  }
}

void xpl::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl);
  node->type(generateType(node->lvalue()->type()));
}

void xpl::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl);
  node->rvalue()->accept(this, lvl);

  // check strings mismatch
  if (node->lvalue()->type()->name() == basic_type::TYPE_STRING || 
      node->rvalue()->type()->name() == basic_type::TYPE_STRING){
    if (node->lvalue()->type()->name() != node->rvalue()->type()->name()){
      throw std::string("wrong string type matching");
    } 
  }
  else{
    validateTypes(node->lvalue(), node->rvalue()); 
  }
  // check if types are compatible
  if (node->lvalue()->type()->name() == node->rvalue()->type()->name()){
      // verificar se os tipos do valor de retorno e da funçao sao iguais
      if (node->lvalue()->type()->subtype() && node->rvalue()->type()->subtype()){
        if (node->lvalue()->type()->subtype()->name() == node->rvalue()->type()->subtype()->name()){
          // verificar matching de subtipos dos ponteiros, se forem ponteiros
        }
      }
        // nao sao ponteiros, logo o matching esta certo
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_INT && node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE){
    // caso de mismatch valido int-double 
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT){
    // caso de mismatch valido double-int
  }
  else{
    throw std::string("invalid type matching in assignment");
  }
  node->type(generateType(node->lvalue()->type()));
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if(node->argument()->type()->name() == basic_type::TYPE_UNSPEC){
    node->argument()->type()->_name = basic_type::TYPE_INT;
    node->argument()->type()->_size = 4;
  }
  // processUnspec(node->argument()->type());
}

void xpl::type_checker::do_print_node(xpl::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);

  // force unspec conversion for read_node cases
  forceConvertUnspecToInt(node->argument()->type());
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_read_node(xpl::read_node * const node, int lvl) {
  ASSERT_UNSPEC;
  // o tipo depende do contexto, nao da pra saber nesta fase...
  node->type(new basic_type(0, basic_type::TYPE_UNSPEC));
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_while_node(xpl::while_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_if_node(xpl::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void xpl::type_checker::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void xpl::type_checker::do_stop_node(xpl::stop_node * const  node, int lvl){
}

void xpl::type_checker::do_return_node(xpl::return_node * const  node, int lvl){
}

void xpl::type_checker::do_next_node(xpl::next_node * const  node, int lvl){
}

void xpl::type_checker::do_sweep_plus_node(xpl::sweep_plus_node * const  node, int lvl){
  
  if (node->lvalue()){
    node->lvalue()->accept(this, lvl + 4);
  }
  if (node->init()){
    node->init()->accept(this, lvl + 4);
  }
  if (node->condition())  {
    node->condition()->accept(this, lvl + 4);
  }
  if (node->step()){
    node->step()->accept(this, lvl + 4);
  }
}

void xpl::type_checker::do_sweep_minus_node(xpl::sweep_minus_node * const  node, int lvl){
  
  if (node->lvalue()){
    node->lvalue()->accept(this, lvl + 4);
  }
  if (node->init()){
    node->init()->accept(this, lvl + 4);
  }
  if (node->condition())  {
    node->condition()->accept(this, lvl + 4);
  }
  if (node->step()){
    node->step()->accept(this, lvl + 4);
  }
}

void xpl::type_checker::do_block_node(xpl::block_node * const  node, int lvl){}

void xpl::type_checker::do_mem_alloc_node(xpl::mem_alloc_node * const  node, int lvl){
  ASSERT_UNSPEC;

  node->argument()->accept(this,lvl);

  if(node->argument()->type()->name() != basic_type::TYPE_INT){
    throw std::string("argument of memory alloc needs to be an integer!!");
  }

  node->type(new basic_type(4, basic_type::TYPE_POINTER));

  // subtype of pointer depends on the program context
  node->type()->_subtype = new basic_type(0, basic_type::TYPE_UNSPEC);
}

void xpl::type_checker::do_mem_address_node(xpl::mem_address_node * const  node, int lvl){
  ASSERT_UNSPEC;

  node->argument()->accept(this, lvl);

  node->type(new basic_type(4, basic_type::TYPE_POINTER));
  node->type()->_subtype = generateType(node->argument()->type());
}


void xpl::type_checker::do_indexing_node(xpl::indexing_node * const  node, int lvl){
  ASSERT_UNSPEC;

  node->name()->accept(this,lvl);
  node->position()->accept(this,lvl);
  validateTypes(node->name(), node->position());

  if(node->name()->type()->name() == basic_type::TYPE_POINTER &&
     node->position()->type()->name() == basic_type::TYPE_INT)
  {
    node->type(generateType(node->name()->type()->subtype()));
  }
  else{
    throw std::string("invalid arguments type for indexing operation");
  }
}

void xpl::type_checker::do_identity_node(xpl::identity_node * const  node, int lvl){
  processUnaryExpression(node, lvl);
}

void xpl::type_checker::do_println_node(xpl::println_node * const  node, int lvl){
  node->argument()->accept(this, lvl + 2);

  // force unspec conversion for read_node cases
  forceConvertUnspecToInt(node->argument()->type());
}

void xpl::type_checker::do_function_decl_node(xpl::function_decl_node * const  node, int lvl){}

void xpl::type_checker::do_function_def_node(xpl::function_def_node * const  node, int lvl){
  if (node->value()){
    node->value()->accept(this, lvl);
    if (node->type()->name() == node->value()->type()->name()){
      // verificar se os tipos do valor de retorno e da funçao sao iguais
      if (node->type()->subtype() && node->value()->type()->subtype()){
        if (node->type()->subtype()->name() == node->value()->type()->subtype()->name()){
          // verificar matching de subtipos dos ponteiros, se forem ponteiros
        }
      }
        // nao sao ponteiros, logo o matching esta certo
    }
    else if (node->type()->name() == basic_type::TYPE_INT && node->value()->type()->name() == basic_type::TYPE_DOUBLE){
      // caso de mismatch valido int-double 
    }
    else if (node->type()->name() == basic_type::TYPE_DOUBLE && node->value()->type()->name() == basic_type::TYPE_INT){
      // caso de mismatch valido double-int
    }
    else{
      throw std::string("invalid type matching in function definition");
    }
  }

}

void xpl::type_checker::do_variable_decl_node(xpl::variable_decl_node * const  node, int lvl){

  if (node->value()) {
    node->value()->accept(this, lvl);
    checkUnspecTypes(node->type(), node->value()->type());
  }
}

void xpl::type_checker::do_function_call_node(xpl::function_call_node * const  node, int lvl){
  ASSERT_UNSPEC;
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(node->identifier());
  if (!symbol){
    throw std::string("function does not exist -> " + node->identifier());
  }
  node->type(generateType(symbol->type()));

	cdk::sequence_node * function_args = symbol->function_arguments();
	cdk::sequence_node * funcall_args = node->parameters();

	if (funcall_args && function_args && funcall_args->size() == function_args->size()){
		size_t j = function_args->size() - 1;
	
		for (size_t i = 0; i < function_args->size() && j >= 0; i++, j--)	{
			xpl::variable_decl_node * function_def_arg = dynamic_cast<xpl::variable_decl_node*>(function_args->node(j));
			cdk::expression_node * funcall_arg = dynamic_cast<cdk::expression_node*>(funcall_args->node(j));

			if (function_def_arg == NULL || funcall_arg == NULL){
				throw std::string("dynamic cast of parameters failed??");
			}
			funcall_arg->accept(this,lvl);

      checkUnspecTypes(funcall_arg->type(), function_def_arg->type());
      // check if types are compatible
      if (function_def_arg->type()->name() == funcall_arg->type()->name()){
      	// verificar se os tipos do valor de retorno e da funçao sao iguais
      	if (function_def_arg->type()->subtype() && funcall_arg->type()->subtype()){
      		if (function_def_arg->type()->subtype()->name() == funcall_arg->type()->subtype()->name()){
      		// verificar matching de subtipos dos ponteiros, se forem ponteiros
      		}
      	}
      		// nao sao ponteiros, logo o matching esta certo
      }
      else if (function_def_arg->type()->name() == basic_type::TYPE_INT && funcall_arg->type()->name() == basic_type::TYPE_DOUBLE){
      	// caso de mismatch valido int-double 
      }
      else if (function_def_arg->type()->name() == basic_type::TYPE_DOUBLE && funcall_arg->type()->name() == basic_type::TYPE_INT){
      	// caso de mismatch valido double-int
      }
      else{
      	throw std::string("invalid type matching in assignment");
      }
		}
	}  
}

void xpl::type_checker::do_null_node(xpl::null_node * const  node, int lvl){
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

