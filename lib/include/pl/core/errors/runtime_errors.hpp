#pragma once

#include <pl/core/errors/error.hpp>

namespace pl::core::ast { class ASTNode; }
namespace pl::ptrn { class Pattern; }

namespace pl::core::err {

    class EvaluatorError : public RuntimeError<Location> {
    public:
        EvaluatorError(u32 errorCode, std::string title) noexcept :
                RuntimeError(errorCode, std::move(title)) { }
    };

    const inline EvaluatorError E0001(1, "Evaluator bug.");
    const inline EvaluatorError E0002(2, "Math expression error.");
    const inline EvaluatorError E0003(3, "Variable error.");
    const inline EvaluatorError E0004(4, "Type error.");
    const inline EvaluatorError E0005(5, "Placement error.");
    const inline EvaluatorError E0006(6, "Array index error.");
    const inline EvaluatorError E0007(7, "Limit error.");
    const inline EvaluatorError E0008(8, "Attribute error.");
    const inline EvaluatorError E0009(9, "Function error.");
    const inline EvaluatorError E0010(10, "Control flow error.");
    const inline EvaluatorError E0011(11, "Memory error.");
    const inline EvaluatorError E0012(12, "Built-in function error.");
    const inline EvaluatorError E0013(13, "Ambiguity error.");

}