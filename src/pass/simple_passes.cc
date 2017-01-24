/*!
 *  Copyright (c) 2016 by Contributors
 * \file simple_passes.cc
 * \brief Implementation of simple passes
 */
#include <tvm/ir.h>
#include <tvm/ir_visitor.h>
#include <tvm/ir_pass.h>

namespace tvm {
namespace ir {

class IRSideEffect : public IRVisitor {
 public:
  void Visit(const NodeRef& e) final {
    if (has_side_effect_) return;
  }

  void Visit_(const Call* op) final {
    if (!op->is_pure()) {
      has_side_effect_ = true; return;
    } else {
      IRVisitor::Visit_(op);
    }
  }

  bool has_side_effect_{false};
};

bool HasSideEffect(const Expr& e) {
  IRSideEffect v;
  v.Visit(e);
  return v.has_side_effect_;
}
}  // namespace ir
}  // namespace tvm