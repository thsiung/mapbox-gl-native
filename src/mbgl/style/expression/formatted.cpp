#include <mbgl/style/expression/formatted.hpp>
#include <mbgl/style/conversion_impl.hpp>
#include <mbgl/style/expression/is_constant.hpp>
#include <mbgl/style/expression/is_expression.hpp>
#include <mbgl/style/expression/literal.hpp>
#include <mbgl/style/expression/expression.hpp>
#include <mbgl/style/expression/type.hpp>
#include <mbgl/style/expression/compound_expression.hpp>
#include <mbgl/style/expression/boolean_operator.hpp>

namespace mbgl {
namespace style {
namespace conversion {
    
using namespace mbgl::style::expression;

optional<Formatted> Converter<Formatted>::operator()(const Convertible& value, Error& error) const {
    using namespace mbgl::style::expression;
    if (isUndefined(value)) {
        return Formatted();
    } else if (isExpression(value)) {
        ParsingContext ctx(type::Formatted);
        ParseResult expression = ctx.parseLayerPropertyExpression(value);
        if (!expression) {
            error.message = ctx.getCombinedErrors();
            return nullopt;
        }
        assert(*expression);
        if (!isFeatureConstant(**expression)) {
            error.message = "data expressions not supported";
            return nullopt;
        }
        if (!isZoomConstant(**expression)) {
            error.message = "zoom expressions not supported";
            return nullopt;
        }
        return Formatted("foobar");
    } else {
        auto result = toString(value);
        if (result) {
            return Formatted(result->c_str());
        } else {
            return nullopt;
        }
        
    }
}

} // namespace conversion
} // namespace style
} // namespace mbgl

