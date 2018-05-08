#ifndef __XPL_FUNCTION_DECL_NODE_H__
#define __XPL_FUNCTION_DECL_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>

namespace xpl {

  /**
   * Class for describing function declaration nodes.
   */
  class function_decl_node: public cdk::basic_node {
    bool _is_private; // "public" keyword
    bool _is_imported; // "use" keyword

    basic_type * _type; // "procedure" keyword corresponde a atribuir o tipo void
    std::string _identifier;
    cdk::sequence_node * _parameters;

  public:
    inline function_decl_node(int lineno,
      bool is_private, bool is_imported,
      basic_type * type, std::string * identifier,
      cdk::sequence_node * parameters) :
        cdk::basic_node(lineno),
        _is_private(is_private), _is_imported(is_imported),
        _type(type), _identifier(*identifier),
        _parameters(parameters){
    }

  public:
    inline basic_type *type() {
      return _type;
    }

    inline std::string identifier() {
      return _identifier;
    }

    inline void identifier(const std::string & new_identifer){
      _identifier = new_identifer;
    }

    inline cdk::sequence_node *parameters() {
      return _parameters;
    }
    
    inline bool is_private() {
      return _is_private;
    }

    inline bool is_imported() {
      return _is_imported;
    }
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_decl_node(this, level);
    }

  };

} // xpl

#endif
