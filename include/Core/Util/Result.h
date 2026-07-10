#pragma once

#include "CoreMod/Misc/UtilConcepts.h"
#include "optional"

namespace ml {

template <EnumClass E>
struct Result final {
public:
    static Result Success() {
        return Result();
    }

    static Result Failure(E error) {
        return Result(error);
    }

    bool isSuccess() const {
        return !mError.has_value();
    }

    bool isFailed() const {
        return mError.has_value();
    }

    E error() const {
        return mError.value();
    }

    operator bool() const {
        return !mError.has_value();
    }

private:
    std::optional<E> mError;

    Result() {}

    Result(E error) {
        mError = std::optional<E>(error);
    }
};

template <typename T, EnumClass E>
struct ResultData final {
public:
    template <typename F>
    static ResultData Success(F&& data) {
        return ResultData(std::forward<F>(data));
    }

    static ResultData Failure(E error) {
        return ResultData(error);
    }

    bool isSuccess() const {
        return !mError.has_value();
    }

    bool isFailed() const {
        return mError.has_value();
    }

    T& data() & {
        return mData.value();
    }

    const T& data() const& {
        return mData.value();
    }

    T&& data() && {
        return std::move(mData.value());
    }

    E error() const {
        return mError.value();
    }

    operator bool() const {
        return !mError.has_value();
    }

private:
    std::optional<T> mData;
    std::optional<E> mError;

    template <typename F>
    ResultData(F&& data) : mData(std::forward<F>(data)) {}

    ResultData(E error) : mError(error) {}
};

}
