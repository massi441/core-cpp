#pragma once

namespace ml {
//
/**
 * Represents a struct that can be iterated over in a memory stream.
 * Must provide a deserialize function that accepts a const void* source,
 * and returns a const void* to the start of next node
 */
struct StreamIterableNode {};
//
// /**
//  * Represents a struct that can be serialized into a memory stream.
//  * Must provide a serialize function that accepts a void* source,
//  * and returns the amount of bytes written in the memory stream
//  */
// struct SerializableStruct {};
//
// /**
//  * Represents a struct that can be serialized into a memory stream as an inner struct.
//  * Must provide a serialize function that accepts a pointer to a SpanWriter,
//  * ensuring that the writer properly advances in the memory stream after serialization
//  */
// struct SerializableInnerStruct {};
//
// /**
//  * Represents a struct that can be deserialized from a memory stream.
//  * Must provide a deserialize function that accepts a const void* source.
//  */
// struct DeserializableStruct {};
//
// /**
//  * Represents a deserializable inner struct of a memory stream
//  * Must provide a deserialize function that accepts a pointer to a SpanReader,
//  * ensuring that the reader properly advances in the memory stream after deserialization
//  */
// struct DeserializableInnerStruct {};
//
}
