#ifndef __XPL_MEM_ADDRESS_NODE_H__
#define __XPL_MEM_ADDRESS_NODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace xpl {

  /**
   * Class for describing memory address nodes ('?').
   */
  class mem_address_node: public cdk::unary_expression_node {

    public:
      inline mem_address_node(int lineno, cdk::expression_node *lvalue) :
        cdk::unary_expression_node(lineno, lvalue) {
        }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_mem_address_node(this, level);
      }

  };

} // xpl

#endif