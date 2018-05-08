#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated


// Function to convert basic_types to string
inline std::string convertTypeToString(basic_type *type) {
  switch(type->name()) {
    case basic_type::TYPE_INT:     return "int";  break;
    case basic_type::TYPE_DOUBLE:  return "double";   break;
    case basic_type::TYPE_BOOLEAN: return "boolean";  break;
    case basic_type::TYPE_STRING:  return "string";   break;
    case basic_type::TYPE_POINTER: return convertTypeToString(type->subtype()) + "*";
    case basic_type::TYPE_VOID:    return "void"; break;
    default:                       return "unspec";
  }
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

void xpl::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}

void xpl::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}

//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}
void xpl::xml_writer::do_identity_node(xpl::identity_node * const  node, int lvl){
  do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_not_node(cdk::not_node * const  node, int lvl){
  do_unary_expression(node, lvl);
}


//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_and_node(cdk::and_node * const node, int lvl){
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_or_node(cdk::or_node * const node, int lvl){
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

void xpl::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  openTag(node, lvl);

  node->lvalue()->accept(this, lvl + 4);
  //reset_new_symbol();

  node->rvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_function_def_node(xpl::function_def_node * const node, int lvl) {
  openTag(node, lvl);
    os() << std::string(lvl, ' ') << "  <is_private>" << std::boolalpha << node->is_private() << "</is_private>" << std::endl;
    os() << std::string(lvl, ' ') << "  <returnType>" << convertTypeToString(node->type()) << "</returnType>" << std::endl;
    os() << std::string(lvl, ' ') << "  <functionName>" << node->identifier() << "</functionName>" << std::endl;
    
    openTag("returnValue", lvl + 2);
      if(node->value() != NULL)
        node->value()->accept(this, lvl + 4);
    closeTag("returnValue", lvl + 2);

    openTag("arguments", lvl + 2);
      if(node->parameters() != NULL)
        node->parameters()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);

    openTag("body", lvl + 2);
      if(node->body() != NULL)
        node->body()->accept(this, lvl + 4);
    closeTag("body", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_print_node(xpl::print_node * const node, int lvl) {
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_read_node(xpl::read_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_while_node(xpl::while_node * const node, int lvl) {
  openTag(node, lvl);
    openTag("condition", lvl + 2);
    node->condition()->accept(this, lvl + 4);
    closeTag("condition", lvl + 2);
    
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_if_node(xpl::if_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_stop_node(xpl::stop_node * const  node, int lvl){
  openTag(node, lvl);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_return_node(xpl::return_node * const  node, int lvl){
  openTag(node, lvl);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_next_node(xpl::next_node * const  node, int lvl){
  openTag(node, lvl);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_sweep_plus_node(xpl::sweep_plus_node * const  node, int lvl){
  openTag(node, lvl);
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);

    openTag("init", lvl + 2);
    node->init()->accept(this, lvl + 4);
    closeTag("init", lvl + 2);

    openTag("condition", lvl + 2);
    node->condition()->accept(this, lvl + 4);
    closeTag("condition", lvl + 2);

    openTag("step", lvl + 2);
    node->step()->accept(this, lvl + 4);
    closeTag("step", lvl + 2);
    
    openTag("sweep_instruction", lvl + 2);
    node->instruction()->accept(this, lvl + 4);
    closeTag("sweep_instruction", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_sweep_minus_node(xpl::sweep_minus_node * const  node, int lvl){
  openTag(node, lvl);
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);

    openTag("init", lvl + 2);
    node->init()->accept(this, lvl + 4);
    closeTag("init", lvl + 2);

    openTag("condition", lvl + 2);
    node->condition()->accept(this, lvl + 4);
    closeTag("condition", lvl + 2);

    openTag("step", lvl + 2);
    node->step()->accept(this, lvl + 4);
    closeTag("step", lvl + 2);
    
    openTag("sweep_instruction", lvl + 2);
    node->instruction()->accept(this, lvl + 4);
    closeTag("sweep_instruction", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_block_node(xpl::block_node * const  node, int lvl){
  openTag(node, lvl);

    openTag("declarations", lvl + 2);
      if (node->declarations() != NULL)
        node->declarations()->accept(this, lvl + 4);
    closeTag("declarations", lvl + 2);

    openTag("instructions", lvl + 2);
      if (node->instructions() != NULL)
        node->instructions()->accept(this, lvl + 4);
    closeTag("instructions", lvl + 2);

  closeTag(node, lvl);
}

void xpl::xml_writer::do_mem_alloc_node(xpl::mem_alloc_node * const  node, int lvl){
  do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_mem_address_node(xpl::mem_address_node * const  node, int lvl){
  do_unary_expression(node, lvl);
}

void xpl::xml_writer::do_indexing_node(xpl::indexing_node * const  node, int lvl){
  openTag(node, lvl);
    openTag("name", lvl + 2);
      node->name()->accept(this, lvl + 4);
    closeTag("name", lvl + 2);

    openTag("position", lvl + 2);
      node->position()->accept(this, lvl + 4);
    closeTag("position", lvl + 2);
  closeTag(node, lvl);
}


void xpl::xml_writer::do_println_node(xpl::println_node * const  node, int lvl){
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_function_decl_node(xpl::function_decl_node * const  node, int lvl){
  openTag(node, lvl);
    os() << std::string(lvl, ' ') << "  <is_private>" << std::boolalpha << node->is_private() << "</is_private>" << std::endl;
    os() << std::string(lvl, ' ') << "  <is_imported>" << std::boolalpha << node->is_imported() << "</is_imported>" << std::endl;
    os() << std::string(lvl, ' ') << "  <returnType>" << convertTypeToString(node->type()) << "</returnType>" << std::endl;
    os() << std::string(lvl, ' ') << "  <functionName>" << node->identifier() << "</functionName>" << std::endl;

    openTag("arguments", lvl + 2);
      if(node->parameters() != NULL)
        node->parameters()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);

  closeTag(node, lvl);
}

void xpl::xml_writer::do_variable_decl_node(xpl::variable_decl_node * const  node, int lvl){
  openTag(node, lvl);
    os() << std::string(lvl, ' ') << "  <is_private>" << std::boolalpha << node->is_private() << "</is_private>" << std::endl;
    os() << std::string(lvl, ' ') << "  <is_imported>" << std::boolalpha << node->is_imported() << "</is_imported>" << std::endl;
    os() << std::string(lvl, ' ') << "  <variableType>" << convertTypeToString(node->type()) << "</variableType>" << std::endl;
    os() << std::string(lvl, ' ') << "  <variableName>" << node->identifier() << "</variableName>" << std::endl;

    openTag("value", lvl + 2);
      if (node->value() != NULL)
        node->value()->accept(this, lvl + 4);
    closeTag("value", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_function_call_node(xpl::function_call_node * const  node, int lvl){
  openTag(node, lvl);
    os() << std::string(lvl, ' ') << "  <functionName>" << node->identifier() << "</functionName>" << std::endl;

    openTag("parameters", lvl + 2);
      if (node->parameters() != NULL)
        node->parameters()->accept(this, lvl + 4);
    closeTag("parameters", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_null_node(xpl::null_node * const  node, int lvl){
  openTag(node, lvl);
  closeTag(node, lvl);
}

/*
void xpl::xml_writer::do_template_node(xpl::template_node * const  node, int lvl){
  // TODO
}
*/
