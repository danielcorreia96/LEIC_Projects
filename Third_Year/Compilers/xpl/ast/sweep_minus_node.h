#ifndef __XPL_SWEEPMINUSNODE_H__
#define __XPL_SWEEPMINUSNODE_H__

#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing sweep-minus cycle nodes.
   */
  class sweep_minus_node: public cdk::basic_node {
    cdk::lvalue_node *_lvalue; 
    cdk::expression_node *_init, *_condition, *_step;
    cdk::basic_node *_instruction;
  public:
    inline sweep_minus_node(int lineno,
      cdk::lvalue_node *lvalue, 
      cdk::expression_node *init, cdk::expression_node *condition, 
      cdk::expression_node *step, cdk::basic_node *instruction) :
        basic_node(lineno), _lvalue(lvalue),
        _init(init), _condition(condition),
        _step(step), _instruction(instruction) {
    }

  public:
    inline cdk::lvalue_node *lvalue() {
      return _lvalue;
    }

    inline cdk::expression_node *init() {
      return _init;
    }

    inline cdk::expression_node *condition() {
      return _condition;
    }
    
    inline cdk::expression_node *step() {
      return _step;
    }
    
    inline cdk::basic_node *instruction() {
      return _instruction;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweep_minus_node(this, level);
    }

  };

} // xpl

#endif