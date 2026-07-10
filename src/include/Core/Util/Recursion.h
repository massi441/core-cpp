#pragma once

// inspired from https://www.scs.stanford.edu/~dm/blog/va-opt.html

#define STR(x) #x,
#define IDENT(x) x,

#define PARENS ()
#define EXPAND(...)  EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH_RECURSE(m, a, ...) \
    m(a) \
    __VA_OPT__(FOR_EACH_AGAIN PARENS (m, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_RECURSE