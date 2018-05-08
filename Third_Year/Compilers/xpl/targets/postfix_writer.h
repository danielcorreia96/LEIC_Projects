#ifndef __XPL_SEMANTICS_POSTFIX_WRITER_H__
#define __XPL_SEMANTICS_POSTFIX_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace xpl {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<xpl::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;

    // current function pointer
    std::shared_ptr<xpl::symbol> _current_function;

    // current variable visibility (public/private)
    bool _current_var_is_public;

    // label for global variables
    std::string _global_var_label;

    // global context flag
    bool _global_context_flag;

    // current and previous segment name
    std::string _current_segment;
    std::string _previous_segment;

    // store labels for next and stop jumps
    std::vector<std::string> _next_labels;
    std::vector<std::string> _stop_labels;

    // offset for local variables
    int _local_var_offset;

    // offset for function arguments
    int _function_args_offset;
    bool _function_args_context_flag;

    // map to store functions defined that have parameters
    std::map<std::string, cdk::sequence_node*> _defined_functions_parameters_map;

    // vector to store external function that i need to import
    std::vector<std::string> _external_elements_to_import;

    // flag for global variable case where type is double but value is int
    bool _int_to_double_global_flag;

  public:

    void go_to_segment(std::string target_segment_name){
      if (_current_segment == target_segment_name){
        //std::cout << "Already at target segment: " << target_segment_name << std::endl;
        return;
      }
      // save current segment before moving
      _previous_segment = _current_segment;

      if (target_segment_name == "TEXT"){
        _current_segment = "TEXT";
        _pf.TEXT();
      }
      else if (target_segment_name == "DATA"){
        _current_segment = "DATA";
        _pf.DATA();
      }
      else if (target_segment_name == "RODATA"){
        _current_segment = "RODATA";
        _pf.RODATA();
      }
      else if (target_segment_name == "BSS"){
        _current_segment = "BSS";
        _pf.BSS();
      }
      else {
        throw std::string("ERROR: unknown segment --- something's wrong!!");
      }

      //std::cout << "Moved from " << _previous_segment << " to " << _current_segment << std::endl;

      if (_previous_segment == "UNSPEC"){
        //std::cout << "Previous segment was UNSPEC so we assign the new current segment: " << _current_segment << std::endl;
        _previous_segment = _current_segment;
      }
    }

    void go_to_previous_segment(){
      go_to_segment(_previous_segment);
    }

    void add_external_element(std::string function_label){
      for (std::vector<std::string>::iterator it =_external_elements_to_import.begin(); 
           it !=_external_elements_to_import.end(); ++it)
      {
        if (function_label == *it){
          //std::cout << "external function is already in the list of functions to import" << std::endl;
          return;
        }
      }
      //std::cout << "adding external function:   " << function_label << std::endl;
      _external_elements_to_import.push_back(function_label);

    }

    void remove_external_element(std::string function_label){
      for (std::vector<std::string>::iterator it =_external_elements_to_import.begin(); 
           it !=_external_elements_to_import.end(); ++it)
      {
        if (function_label == *it){
          //std::cout << "found the external function in the list...deleting..." << function_label << std::endl;
          _external_elements_to_import.erase(it);
          return;
        }
      }
    }

    void import_external_elements(){
			// library function imports - system?
			_pf.EXTERN("argc");
			_pf.EXTERN("argv");
			_pf.EXTERN("envp");

			// library function imports - read 
			_pf.EXTERN("readi");
			_pf.EXTERN("readd");

			// library function imports - prints
			_pf.EXTERN("printi");
			_pf.EXTERN("prints");
			_pf.EXTERN("printd");
			_pf.EXTERN("println");

      for (std::vector<std::string>::iterator it =_external_elements_to_import.begin(); 
           it !=_external_elements_to_import.end(); ++it)
      {
        _pf.EXTERN(*it);
      }
    }
  
  
  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<xpl::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0), _global_context_flag(true), 
        _current_segment("UNSPEC"), _previous_segment("UNSPEC"), _local_var_offset(0), _function_args_offset(0),
        _function_args_context_flag(false), _int_to_double_global_flag(false)
         {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
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
