#pragma once

#include <ml/Core/Memory/SpanReader.h>
#include <ml/Core/Memory/SpanWriter.h>
#include <ml/Core/String/StringUtil.h>
#include <string_view>

namespace ml {

/**
 * A serializable/deserializable std::string_view from a memory stream
 * @tparam TLength The integral type used to encode the string length
 */
template <typename TLength>
class StreamStringView {
public:
    StreamStringView() {
        mView = ml::EmptyString;
    }

    StreamStringView(std::string_view view) {
        mView = view;
    }

    StreamStringView(const char* str, TLength length) {
        mView = std::string_view(str, length);
    }

    StreamStringView(const char* str) : StreamStringView(str, std::strlen(str)) {

    }

    /**
     * Writes the length and the string into a memory stream
     * @param writer The writer to write the string to
     */
    void serialize(SpanWriter* writer) const {
        writer->write<TLength>(mView.length());
        writer->write(mView.data(), mView.length());
    }

    /**
     * Reads a length-prefixed string from the reader
     * @param reader The reader to read the string from
     */
    void deserialize(SpanReader* reader) {
        TLength length = reader->read<TLength>();
        mView = std::string_view(reader->cursor(), length);
        reader->skip(length);
    }

    bool hasData() const { return mView.length() > 0; }

    size_t size() const { return mView.size(); }
    size_t length() const { return mView.length(); }

    const char* cstr() const { return mView.data(); }
    std::string_view strView() const { return mView; }

private:
    std::string_view mView;
};

}
