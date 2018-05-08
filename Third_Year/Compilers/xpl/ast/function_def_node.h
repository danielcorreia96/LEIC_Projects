// $Id: function_def_node.h,v 1.7 2017/04/20 15:36:00 ist180967 Exp $ -*- c++ -*-
#ifndef __XPL_FUNCTION_DEF_NODE_H__
#define __XPL_FUNCTION_DEF_NODE_H__

#include <cdk/ast/basic_node.h>
#include "function_decl_node.h"
namespace xpl {

  /**
   * Class for describing function definition nodes.
   */
  class function_def_node: public cdk::basic_node {
    bool _is_private; // "public" keyword
    // como a funcao tem um corpo definido, nao podemos usar "use" keyword

    basic_type * _type;
    std::string _identifier;
    cdk::sequence_node * _parameters;
    cdk::expression_node * _value;

    cdk::basic_node *_body; 

  public:
    inline function_def_node(int lineno, bool is_private, basic_type * type, std::string * identifier, cdk::sequence_node * parameters, cdk::expression_node * value, cdk::basic_node * body) :
        cdk::basic_node(lineno), _is_private(is_private), _type(type),
        _identifier(*identifier), _parameters(parameters), _value(value),
        _body(body){
    }

  public:
    inline basic_type *type() {
      return _type;
    }

    inline std::string identifier() {
      return _identifier;
    }

    inline cdk::sequence_node *parameters() {
      return _parameters;
    }

    inline cdk::expression_node *value() {
      return _value;
    }

    inline bool is_private() {
      return _is_private;
    }

    inline cdk::basic_node *body() {
      return _body;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_def_node(this, level);
    }

  };

} // xpl

#endif
