#ifndef __XPL_MEM_ALLOC_NODE_H__
#define __XPL_MEM_ALLOC_NODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace xpl {

  /**
   * Class for describing memory allocation nodes ('[]').
   */
  class mem_alloc_node: public cdk::unary_expression_node {

    public:
      inline mem_alloc_node(int lineno, cdk::expression_node *lvalue) :
        cdk::unary_expression_node(lineno, lvalue) {
        }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_mem_alloc_node(this, level);
      }

  };

} // xpl

#endif