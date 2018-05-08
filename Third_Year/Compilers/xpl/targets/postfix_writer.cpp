#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

inline basic_type * generateType(basic_type * type) {
  basic_type * new_type = new basic_type(type->size(), type->name());
  if (type->subtype()){
	  new_type->_subtype = generateType(type->subtype());
  }
  return new_type;
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
	for (size_t i = 0; i < node->size(); i++) {
		node->node(i)->accept(this, lvl);
	}
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;

	if (_global_context_flag){
		go_to_segment("DATA");
		_pf.ALIGN();

		if (_current_var_is_public){
			_pf.GLOBAL(_global_var_label, _pf.OBJ());
		}

		_pf.LABEL(_global_var_label);
		if(_int_to_double_global_flag){
			_pf.DOUBLE(node->value());
		}
		else{
			_pf.CONST(node->value());
		}
		
		go_to_previous_segment(); // return to previous segment
	}
	else{
		_pf.INT(node->value()); // push an integer to the stack
	}
}

void xpl::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;

	std::string lbl = mklbl(++_lbl); // returned label not used

	if (_global_context_flag){
		go_to_segment("DATA");
		_pf.ALIGN();

		if (_current_var_is_public){
			_pf.GLOBAL(_global_var_label, _pf.OBJ());
		}

		_pf.LABEL(_global_var_label);
		_pf.DOUBLE(node->value());
		go_to_previous_segment(); // return to previous segment
	}
	else{
		
		go_to_segment("RODATA"); 
		_pf.ALIGN(); // make sure we are aligned
		_pf.LABEL(lbl); // give the string a name
		_pf.DOUBLE(node->value()); // output string characters
		go_to_previous_segment(); // goto previous segment

		_pf.ADDR(lbl);
		_pf.DLOAD();
	}

}

void xpl::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {

	ASSERT_SAFE_EXPRESSIONS

	std::string lbl = mklbl(++_lbl); // returned label not used
	
	/* generate the string */
	go_to_segment("RODATA"); // strings are DATA readonly
	_pf.ALIGN(); // make sure we are aligned
	_pf.LABEL(lbl); // give the string a name
	_pf.STR(node->value()); // output string characters
	go_to_previous_segment(); // goto previous segment

	if (_global_context_flag){
		go_to_segment("DATA");
		_pf.ALIGN();

		if (_current_var_is_public){
			_pf.GLOBAL(_global_var_label, _pf.OBJ());
		}

		_pf.LABEL(_global_var_label);
		_pf.ID(lbl);
		go_to_previous_segment(); // goto previous segment
	}
	else{
		_pf.ADDR(lbl); // the string to be printed
	}
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->argument()->accept(this, lvl); // determine the value
	_pf.NEG(); // 2-complement
}

void xpl::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
	//TODO
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	
	node->left()->accept(this, lvl);
	if(node->type()->name() == basic_type::TYPE_DOUBLE &&
	   node->left()->type()->name() == basic_type::TYPE_INT)
	{
		_pf.I2D();
	}
	else if (node->type()->name() == basic_type::TYPE_POINTER && 
			 node->left()->type()->name() == basic_type::TYPE_INT) 
	{
		_pf.INT(node->type()->subtype()->size());
		_pf.MUL();
	}

	node->right()->accept(this, lvl);
	if(node->type()->name() == basic_type::TYPE_DOUBLE &&
	   node->right()->type()->name() == basic_type::TYPE_INT)   
	{
		_pf.I2D();
	}
	else if (node->type()->name() == basic_type::TYPE_POINTER && 
			 node->right()->type()->name() == basic_type::TYPE_INT) 
	{
		_pf.INT(node->type()->subtype()->size());
		_pf.MUL();
	}



	if(node->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DADD();
	}
	else{
		_pf.ADD();
	}
}
void xpl::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
/*	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.SUB();*/
	ASSERT_SAFE_EXPRESSIONS;
	
	node->left()->accept(this, lvl);
	if(node->type()->name() == basic_type::TYPE_DOUBLE &&
	   node->left()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	}

	node->right()->accept(this, lvl);
	if(node->type()->name() == basic_type::TYPE_DOUBLE &&
	   node->right()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	}

	if(node->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DSUB();
	}
	else{
		_pf.SUB();
	}
}
void xpl::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {

	ASSERT_SAFE_EXPRESSIONS;
	
	node->left()->accept(this, lvl);
	if(node->type()->name() == basic_type::TYPE_DOUBLE &&
	   node->left()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	}

	node->right()->accept(this, lvl);
	if(node->type()->name() == basic_type::TYPE_DOUBLE &&
	   node->right()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	}

	if(node->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DMUL();
	}
	else{
		_pf.MUL();
	}
}
void xpl::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.DIV();
}
void xpl::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.MOD();
}
void xpl::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.LT();
}
void xpl::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.LE();
}
void xpl::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.GE();
}
void xpl::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.GT();
}
void xpl::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.NE();
}
void xpl::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->left()->accept(this, lvl);
	node->right()->accept(this, lvl);
	_pf.EQ();
}
void xpl::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	std::string end_and_op_label = mklbl(++_lbl);

	node->left()->accept(this, lvl);
	_pf.DUP();
	_pf.JZ(end_and_op_label);
	node->right()->accept(this, lvl);
	
	_pf.ALIGN();
	_pf.LABEL(end_and_op_label);
}
void xpl::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	std::string end_or_op_label = mklbl(++_lbl);

	node->left()->accept(this, lvl);
	_pf.DUP();
	_pf.JNZ(end_or_op_label);
	node->right()->accept(this, lvl);

	_pf.ALIGN();
	_pf.LABEL(end_or_op_label);
}
//---------------------------------------------------------------------------

void xpl::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	const std::string& id = node->name();
  	std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
	if (!symbol){
		throw std::string ("symbol " + id + " undeclared");
	}
	if (!symbol->is_global() || symbol->is_function()){
		_pf.LOCAL(symbol->offset());
	}
	else{
		_pf.ADDR(symbol->name());
	}
}

void xpl::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->lvalue()->accept(this, lvl);
	if(node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DLOAD();
	}
	else{
		_pf.LOAD();
	}
}

void xpl::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	
	node->rvalue()->accept(this, lvl); // determine the new value
	if(node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DDUP();
	}
	else{
		_pf.DUP();
	}

	// verificar se preciso fazer trocas de inteiros-doubles
	if(node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	}


	node->lvalue()->accept(this, lvl);
	if(node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DSTORE();
	}
	else{
		_pf.STORE();
	}
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_function_def_node(xpl::function_def_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;

	// function label
	std::string function_label;

	// size needed in stack for return value
	size_t return_stacksize = node->type()->size();

	// size needed in stack for variable declarations in function locally
	xpl::stacksize_calculator stsize_calc(_compiler);
	node->accept(&stsize_calc, lvl);
	size_t local_stacksize = stsize_calc.get_stack_size();


	// setup offset for function
	_local_var_offset = 0;
	_function_args_offset = 8;

	// do symbol table stuff
	std::shared_ptr<xpl::symbol> symbol = _symtab.find(node->identifier());
  	if (symbol){
    	if (symbol->is_defined()){
      		throw std::string("symbol redefinition!!");
    	}
		else if (!symbol->is_function()){
			throw std::string("symbol does not correspond to a function");
		}
		else{
			// check if this function is imported
			if (symbol->is_imported() && !symbol->is_defined()){
				remove_external_element(node->identifier());
			}

			symbol->function_arguments(node->parameters());
			symbol->is_defined(true);
			function_label = symbol->name();
		}
  	}
	else {

		// label gets the name of the function
		function_label = node->identifier();

		//insert symbol in symbol table
		// symbol(type,name,offset,parameters, is_function,is_defined, is_global, is_imported)
		symbol = std::make_shared<xpl::symbol>(
			generateType(node->type()),
			node->identifier(),
			-return_stacksize,
			true, true, true, false,
			node->parameters()
		);
		_symtab.insert(node->identifier(), symbol);
	}

	_current_function = symbol;

	// Push function context
	_symtab.push();
	_global_context_flag = false;
	go_to_segment("TEXT");
	_pf.ALIGN();

	if (!node->is_private()){

		if (node->identifier() == "xpl"){
			// xpl function is the main
			_pf.GLOBAL("_main", _pf.FUNC());
			_pf.LABEL("_main");
			_pf.ALIGN();

		}
		else if (node->identifier() == "_main"){
	      throw std::string("_main name is reserved, so it is invalid...");
		}
		else {
			_pf.GLOBAL(function_label, _pf.FUNC());
   		}
	}

	_pf.LABEL(function_label);

	// saves space for stack
  	_pf.ENTER(local_stacksize + return_stacksize);

	// write return value
	if (node->value()) {
	  	node->value()->accept(this, lvl);

		if(node->type()->name() == basic_type::TYPE_DOUBLE && node->value()->type()->name() == basic_type::TYPE_INT){
			_pf.I2D();
		}

		_pf.LOCAL(-return_stacksize);
		_local_var_offset -= node->type()->size();
		if(node->type()->name() == basic_type::TYPE_DOUBLE){
			_pf.DSTORE();
		}
		else {
			_pf.STORE();			
		}
	}

	if (node->parameters()){
		_function_args_context_flag = true;
		node->parameters()->accept(this, lvl);
		_function_args_context_flag = false;
	}

	node->body()->accept(this, lvl);

	if (node->type()->name() != basic_type::TYPE_VOID){
		_pf.LOCAL(-return_stacksize);
		if(node->type()->name() == basic_type::TYPE_DOUBLE){
			_pf.DLOAD();
			_pf.DPOP();
		}
		else{
			_pf.LOAD();
			_pf.POP();
		}
	}
 	
	// end the main function
	_pf.LEAVE();
	_pf.RET();
	
	_symtab.pop();
	_global_context_flag = true;
	_current_function = NULL;
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->argument()->accept(this, lvl); // determine the value
	if (node->argument()->type()->name() == basic_type::TYPE_INT) {
		_pf.TRASH(4); // delete the evaluated value
	} 
	else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.TRASH(8);
	}
	else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
		_pf.TRASH(4); // delete the evaluated value's address
	} 
	else if (node->argument()->type()->name() == basic_type::TYPE_VOID){
		// do nothing
	} 
	else if (node->argument()->type()->name() == basic_type::TYPE_POINTER){
		_pf.TRASH(4);
	}
	else {
		std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
		exit(1);
	}
}

void xpl::postfix_writer::do_print_node(xpl::print_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	node->argument()->accept(this, lvl); // determine the value to print
	if (node->argument()->type()->name() == basic_type::TYPE_INT) {
		_pf.CALL("printi");
		_pf.TRASH(4); // delete the printed value
	} 
	else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
		_pf.CALL("prints");
		_pf.TRASH(4); // delete the printed value's address
	}
	else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.CALL("printd");
		_pf.TRASH(8);
	} 
	else {
		std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
		exit(1);
	}

	//_pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_read_node(xpl::read_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	if (node->type()->name() == basic_type::TYPE_INT){
	 _pf.CALL("readi");
	 _pf.PUSH();
	}
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_while_node(xpl::while_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;

	std::string condition = mklbl(++_lbl);
	std::string endwhile = mklbl(++_lbl);

	_pf.LABEL(condition);

	// store labels for next and stop jumps
	_next_labels.push_back(condition);
	_stop_labels.push_back(endwhile);

	node->condition()->accept(this, lvl);
	_pf.JZ(endwhile);
	node->block()->accept(this, lvl + 2);
	_pf.JMP(condition);
	_pf.LABEL(endwhile);

	// clean up store labels for next and stop jumps
	_next_labels.pop_back();
	_stop_labels.pop_back();

	
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_node(xpl::if_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;
	int lbl1;
	node->condition()->accept(this, lvl);

	_pf.JZ(mklbl(lbl1 = ++_lbl));

	node->block()->accept(this, lvl + 2);

	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
	ASSERT_SAFE_EXPRESSIONS;

	std::string else_label = mklbl(++_lbl);
	std::string endif_label = mklbl(++_lbl);

	node->condition()->accept(this, lvl);
	_pf.JZ(else_label);

	node->thenblock()->accept(this, lvl + 2);
	_pf.JMP(endif_label);
	
	_pf.ALIGN();
	_pf.LABEL(else_label);
	if(node->elseblock()){
		node->elseblock()->accept(this, lvl + 2);
	}
	
	_pf.ALIGN();
	_pf.LABEL(endif_label);
}

void xpl::postfix_writer::do_stop_node(xpl::stop_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	if (_stop_labels.empty()){
		throw std::string("something's weird...no sweep cycles exist at the moment");
	}
	_pf.JMP(_stop_labels.back());
}


void xpl::postfix_writer::do_return_node(xpl::return_node * const  node, int lvl){
	if(_current_function == NULL) {
    	throw std::string("WRONG! Cannot outside of a function");
  	}

	if (_current_function->type()->name() != basic_type::TYPE_VOID){
		_pf.LOCAL(_current_function->offset());

		// TODO doubles
		_pf.LOAD();
		_pf.POP();
	}

	_pf.LEAVE();
	_pf.RET();
}

void xpl::postfix_writer::do_next_node(xpl::next_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	if (_next_labels.empty()){
		throw std::string("something's weird...no loop cycles exist at the moment");
	}
	_pf.JMP(_next_labels.back());
}

void xpl::postfix_writer::do_sweep_plus_node(xpl::sweep_plus_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;

	// Condition, increment and end labels
	std::string condition = mklbl(++_lbl);
	std::string increment = mklbl(++_lbl);
	std::string endfor = mklbl(++_lbl);

	// store labels for next and stop jumps
	_next_labels.push_back(increment);
	_stop_labels.push_back(endfor);


	cdk::assignment_node * init = new cdk::assignment_node(node->lineno(), node->lvalue(), node->init());
	do_assignment_node(init, lvl);

	// sweep var rvalue node
	cdk::rvalue_node * sweep_var_rvalue = new cdk::rvalue_node(node->lineno(), node->lvalue());

	// Evaluate condition
	_pf.ALIGN();
	_pf.LABEL(condition);
	cdk::le_node * le_condition = new cdk::le_node(node->lineno(),sweep_var_rvalue, node->condition());
	do_le_node(le_condition, lvl);
	_pf.JZ(endfor);

	node->instruction()->accept(this, lvl);

	// evalutate increment expression
	_pf.ALIGN();
	_pf.LABEL(increment);
	cdk::add_node * increment_expression = new cdk::add_node(node->lineno(), sweep_var_rvalue, node->step());
	cdk::assignment_node * step = new cdk::assignment_node(node->lineno(), node->lvalue(), increment_expression);
	do_assignment_node(step, lvl);
	_pf.JMP(condition);

	_pf.ALIGN();
	_pf.LABEL(endfor);

	// clean up store labels for next and stop jumps
	_next_labels.pop_back();
	_stop_labels.pop_back();

}

void xpl::postfix_writer::do_sweep_minus_node(xpl::sweep_minus_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;

	// Condition, increment and end labels
	std::string condition = mklbl(++_lbl);
	std::string increment = mklbl(++_lbl);
	std::string endfor = mklbl(++_lbl);

	// store labels for next and stop jumps
	_next_labels.push_back(increment);
	_stop_labels.push_back(endfor);


	cdk::assignment_node * init = new cdk::assignment_node(node->lineno(), node->lvalue(), node->init());
	do_assignment_node(init, lvl);

	// sweep var rvalue node
	cdk::rvalue_node * sweep_var_rvalue = new cdk::rvalue_node(node->lineno(), node->lvalue());

	// Evaluate condition
	_pf.ALIGN();
	_pf.LABEL(condition);
	cdk::ge_node * le_condition = new cdk::ge_node(node->lineno(),sweep_var_rvalue, node->condition());
	do_ge_node(le_condition, lvl);
	_pf.JZ(endfor);

	// evaluate block
	node->instruction()->accept(this, lvl);

	// evalutate increment expression
	_pf.ALIGN();
	_pf.LABEL(increment);
	cdk::sub_node * increment_expression = new cdk::sub_node(node->lineno(), sweep_var_rvalue, node->step());
	cdk::assignment_node * step = new cdk::assignment_node(node->lineno(), node->lvalue(), increment_expression);
	do_assignment_node(step, lvl);
	_pf.JMP(condition);

	_pf.ALIGN();
	_pf.LABEL(endfor);

	// clean up store labels for next and stop jumps
	_next_labels.pop_back();
	_stop_labels.pop_back();

}

void xpl::postfix_writer::do_block_node(xpl::block_node * const  node, int lvl){
	// create context for new block
	_symtab.push();
	if (node->declarations() != NULL){
		node->declarations()->accept(this, lvl);
	}
	if (node->instructions() != NULL){
		node->instructions()->accept(this, lvl);
	}
	_symtab.pop();
}


void xpl::postfix_writer::do_mem_alloc_node(xpl::mem_alloc_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;

	node->argument()->accept(this,lvl);
	_pf.INT(node->type()->subtype()->size());
	_pf.MUL();

	// Allocate space and leave address on the stack
  	_pf.ALLOC();
  	_pf.SP();
}

void xpl::postfix_writer::do_mem_address_node(xpl::mem_address_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	node->argument()->accept(this, lvl);
}

void xpl::postfix_writer::do_indexing_node(xpl::indexing_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;

	node->name()->accept(this, lvl);

	node->position()->accept(this, lvl);

	_pf.INT(node->type()->size());
	_pf.MUL();

	_pf.ADD();


}

void xpl::postfix_writer::do_identity_node(xpl::identity_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	node->argument()->accept(this, lvl); // determine the value
}

void xpl::postfix_writer::do_println_node(xpl::println_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	node->argument()->accept(this, lvl); // determine the value to print
	if (node->argument()->type()->name() == basic_type::TYPE_INT) {
		_pf.CALL("printi");
		_pf.TRASH(4); // delete the printed value
	} 
	else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
		_pf.CALL("prints");
		_pf.TRASH(4); // delete the printed value's address
	} 
	else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.CALL("printd");
		_pf.TRASH(8);
	} 
	else {
		std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
		exit(1);
	}
	_pf.CALL("println"); // print a newline
}

void xpl::postfix_writer::do_function_decl_node(xpl::function_decl_node * const  node, int lvl){

 	if (node->identifier() == "xpl"){
 		node->identifier("_main");
 	}
  else if (node->identifier() == "_main"){
    throw std::string("_main name is reserved, so it is invalid...");
  }

	std::shared_ptr<xpl::symbol> symbol = _symtab.find(node->identifier());
  if (symbol){
    throw std::string("function redefinition!!");
  }
  else{

    //insert symbol in symbol table
    // symbol(type,name,offset, is_function,is_defined, is_global, is_imported, function_arguments)
    symbol = std::make_shared<xpl::symbol>(
		generateType(node->type()),
    	node->identifier(),
    	-node->type()->size(),
    	true, false, true, node->is_imported(),
		node->parameters()
    );
    _symtab.insert(node->identifier(), symbol);

	if (node->is_imported()){
		add_external_element(symbol->name());
	}
  }
}

void xpl::postfix_writer::do_variable_decl_node(xpl::variable_decl_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;

	_current_var_is_public = !node->is_private();
	bool variable_is_initialized = node->value() != nullptr;

	std::shared_ptr<xpl::symbol> symbol = _symtab.find_local(node->identifier());
	
	if (symbol){
		throw std::string("symbol redeclaration");
	}
	else{
		//TODO parameters accepts
		if (_function_args_context_flag){
			// symbol(type,name,offset,is_function,is_defined, is_global,is_imported, function_arguments)
			symbol = std::make_shared<xpl::symbol>(
				generateType(node->type()),
				node->identifier(), 
				_function_args_offset,
				false, false, false, false,
				nullptr
			);
			_symtab.insert(node->identifier(), symbol);

			_function_args_offset += node->type()->size();
			return;
		}
		if (_global_context_flag){
			// symbol(type,name,offset,is_function,is_defined, is_global, is_imported)
			symbol = std::make_shared<xpl::symbol>(
				generateType(node->type()),
				node->identifier(), 
				0,
				false, variable_is_initialized, _global_context_flag, node->is_imported(),
				nullptr
			);
			_symtab.insert(node->identifier(), symbol);

			if(symbol->is_imported()){
				remove_external_element(symbol->name());
			}

			if (variable_is_initialized) {
				// variable is initialized

				_global_var_label = node->identifier();

				// variable is of type double but value is an int ---> convert int to double
				if (node->type()->name()          == basic_type::TYPE_DOUBLE &&
					node->value()->type()->name() == basic_type::TYPE_INT) 
				{
					_int_to_double_global_flag = true;
					node->value()->accept(this, lvl);
					_int_to_double_global_flag = false;
				}
				else{
					node->value()->accept(this, lvl);
				}
			}
			else{
				go_to_segment("BSS");
				_pf.ALIGN();
				_pf.LABEL(node->identifier());
				_pf.BYTE(node->type()->size());
				go_to_previous_segment(); // return to previous segment
			}
		}
		else{
			_local_var_offset -= node->type()->size();
			// symbol(type,name,offset,parameters,is_function,is_defined, is_global, is_imported)
			symbol = std::make_shared<xpl::symbol>(
				generateType(node->type()),
				node->identifier(), 
				_local_var_offset,
				false, variable_is_initialized, _global_context_flag, node->is_imported(),
				nullptr
			);
			_symtab.insert(node->identifier(), symbol);

			if(symbol->is_imported()){
				add_external_element(symbol->name());
			}

			if (node->value()){
				if(symbol->is_imported()){
					remove_external_element(symbol->name());
				}

				node->value()->accept(this,lvl);

				// verificar se preciso fazer trocas de inteiros-doubles
				if(node->type()->name() == basic_type::TYPE_DOUBLE && node->value()->type()->name() == basic_type::TYPE_INT){
					_pf.I2D();
				}

				_pf.LOCAL(_local_var_offset);
				if(node->type()->name() == basic_type::TYPE_DOUBLE){
					_pf.DSTORE();
				}
				else{
					_pf.STORE();
				}
			}
		}
	}
}

void xpl::postfix_writer::do_function_call_node(xpl::function_call_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	std::shared_ptr<xpl::symbol> symbol = _symtab.find(node->identifier());
	if (!symbol){
		throw std::string("function does not exist -> " + node->identifier());
	}

	size_t funcall_args_size = 0;

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

			funcall_args_size += funcall_arg->type()->size();

			if(function_def_arg->type()->name() == basic_type::TYPE_DOUBLE && funcall_arg->type()->name() == basic_type::TYPE_INT){
				funcall_args_size += 4;
				_pf.I2D();
			}
			
		}
	}

	_pf.CALL(symbol->name());
	_pf.TRASH(funcall_args_size);

	if (node->type()->name() == basic_type::TYPE_VOID){
		// do nothing
	}
	else if (node->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.DPUSH();		
	}
	else{
		_pf.PUSH();
	}

}

void xpl::postfix_writer::do_null_node(xpl::null_node * const  node, int lvl){
	ASSERT_SAFE_EXPRESSIONS;
	cdk::integer_node * null_int = new cdk::integer_node(node->lineno(), 0);
	do_integer_node(null_int, lvl);


}

