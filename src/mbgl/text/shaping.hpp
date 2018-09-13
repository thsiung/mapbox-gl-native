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
    SectionOptions(double scale_, FontStackHash fontStackHash_)
        : scale(scale_), fontStackHash(fontStackHash_)
    {}
    
    double scale;
    FontStackHash fontStackHash;
};
    
struct TaggedString {
    TaggedString() {}
    
    TaggedString(std::u16string text_, SectionOptions options)
    : text(std::move(text_))
    , sectionIndex(text.size(), 0) {
        sections.push_back(std::move(options));
    }
    
    std::size_t length() const {
        return text.size();
    }
    
    bool empty() const {
        return text.empty();
    }
    
    const SectionOptions& getSection(std::size_t index) const {
        return sections.at(sectionIndex.at(index));
    }
    
    char16_t getCharCodeAt(std::size_t index) const {
        return text[index];
    }
    
    double getMaxScale() const {
        double maxScale = 0.0;
        for (const auto& section : sections) {
            maxScale = std::max(maxScale, section.scale);
        }
        return maxScale;
    }
    
    void trim();
    
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
