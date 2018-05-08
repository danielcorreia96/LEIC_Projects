#ifndef __XPL_VARIABLE_DECL_NODE_H__
#define __XPL_VARIABLE_DECL_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>

namespace xpl {

  /**
   * Class for describing variable declaration nodes.
   */
  class variable_decl_node: public cdk::basic_node {
    basic_type * _type;
    std::string _identifier;
    cdk::expression_node * _value;

    bool _is_private;
    bool _is_imported;

  public:
    inline variable_decl_node(int lineno, basic_type * type, std::string * identifier,
      cdk::expression_node * value, bool is_private,
      bool is_imported, bool is_argument) :
        cdk::basic_node(lineno), _type(type), _identifier(*identifier),
        _value(value), _is_private(is_private),
        _is_imported(is_imported){
    }

  public:
    inline basic_type *type() {
      return _type;
    }

    inline std::string identifier() {
      return _identifier;
    }

    inline cdk::expression_node *value() {
      return _value;
    }

    inline bool is_private() {
      return _is_private;
    }

    inline bool is_imported() {
      return _is_imported;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_decl_node(this, level);
    }

  };

} // xpl

#endif
