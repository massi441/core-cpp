#pragma once

#define NO_COPY(ClassName)                           \
    ClassName(const ClassName&) = delete;            \
    ClassName& operator=(const ClassName&) = delete; \

#define NO_MOVE(ClassName)                           \
    ClassName(ClassName&&) = delete;                 \
    ClassName& operator=(ClassName&&) = delete;      \

#define NO_COPY_NO_MOVE(ClassName)                   \
    NO_COPY(ClassName)                               \
    NO_MOVE(ClassName)                               \

#define NO_HEAP_ALLOC(ClassName)                     \
    void* operator new(size_t) = delete;             \
    void* operator new[](size_t) = delete;           \

#define NO_CONSTRUCTOR(ClassName)                    \
    ClassName() = delete;
