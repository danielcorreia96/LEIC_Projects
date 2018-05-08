#ifndef __XPL_INDEXING_NODE_H__
#define __XPL_INDEXING_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>

namespace xpl {

  /**
   * Class for describing index nodes.
   */
  class indexing_node: public cdk::lvalue_node {
    cdk::expression_node *_name, *_position;

    public:
    inline indexing_node(int lineno, cdk::expression_node *name, cdk::expression_node *position) :
      lvalue_node(lineno), _name(name), _position(position) {
      }

    public:
    inline cdk::expression_node *name() {
      return _name;
    }

    inline cdk::expression_node *position() {
      return _position;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_indexing_node(this, level);
    }

  };

} // xpl

#endif