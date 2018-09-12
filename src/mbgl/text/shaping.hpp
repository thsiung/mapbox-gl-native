#pragma once

#include <mbgl/text/glyph.hpp>
#include <mbgl/renderer/image_atlas.hpp>
#include <mbgl/style/types.hpp>

namespace mbgl {

class SymbolFeature;
class BiDi;

class PositionedIcon {
private:
    PositionedIcon(ImagePosition image_,
                   float top_,
                   float bottom_,
                   float left_,
                   float right_,
                   float angle_)
        : _image(std::move(image_)),
          _top(top_),
          _bottom(bottom_),
          _left(left_),
          _right(right_),
          _angle(angle_) {}

    ImagePosition _image;
    float _top;
    float _bottom;
    float _left;
    float _right;
    float _angle;

public:
    static PositionedIcon shapeIcon(const ImagePosition&,
                                    const std::array<float, 2>& iconOffset,
                                    style::SymbolAnchorType iconAnchor,
                                    const float iconRotation);

    const ImagePosition& image() const { return _image; }
    float top() const { return _top; }
    float bottom() const { return _bottom; }
    float left() const { return _left; }
    float right() const { return _right; }
    float angle() const { return _angle; }
};
    
struct SectionOptions {
    optional<double> scale;
    optional<FontStackHash> fontStackHash;
};
    
struct TaggedString {
    TaggedString() {}
    
    TaggedString(std::u16string text_, SectionOptions options)
    : text(std::move(text_))
    , sectionIndex(text.size(), 0) {
        sections.push_back(std::move(options));
    }
    
    std::u16string text;
    std::vector<uint8_t> sectionIndex;
    std::vector<SectionOptions> sections;
};

const Shaping getShaping(const TaggedString& string,
                         float maxWidth,
                         float lineHeight,
                         style::SymbolAnchorType textAnchor,
                         style::TextJustifyType textJustify,
                         float spacing,
                         const Point<float>& translate,
                         float verticalHeight,
                         const WritingModeType,
                         BiDi& bidi,
                         const GlyphMap& glyphs);

} // namespace mbgl
