#ifndef __XPL_SEMANTICS_SYMBOL_H__
#define __XPL_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>
#include <cdk/ast/sequence_node.h>

namespace xpl {

    class symbol {
      basic_type *_type;
      std::string _name;
      int _offset;

      bool _is_function;
      bool _is_defined;
      bool _is_global;
      bool _is_imported;

      cdk::sequence_node * _function_arguments;

    public:
      inline symbol(basic_type *type, const std::string &name, int offset,
                    bool is_function, bool is_defined, bool is_global,
                    bool is_imported, cdk::sequence_node * arguments
      ) :
          _type(type), _name(name), _offset(offset),
          _is_function(is_function), _is_defined(is_defined),
          _is_global(is_global), _is_imported(is_imported),
          _function_arguments(arguments)
      {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline int offset() const {
        return _offset;
      }
      
      inline bool is_function() { return _is_function;  }
      inline bool is_defined()  { return _is_defined;   }
      inline bool is_global()   { return _is_global;    }
      inline bool is_imported() { return _is_imported;  }

      inline cdk::sequence_node * function_arguments(){
        return _function_arguments;
      }

      inline void function_arguments(cdk::sequence_node * arguments){
        _function_arguments = arguments;
      }

      inline void offset(int v) {
        _offset = v;
      }

      inline void is_defined(bool new_value){
        _is_defined = new_value;
      }

    };

} // xpl

#endif
