# ChibiC

ChibiC is a minimal C compiler (work in progress).

Based on the approach outlined in [baby steps to a C compiler](http://www.wilfred.me.uk/blog/2014/08/27/baby-steps-to-a-c-compiler/), the goal is to test drive features of the compiler until a reasonable subset of C is supported.

The [tapc](https://github.com/zorgnax/libtap) library is used for unit testing.

## Progress

This simple C program was used to drive a simple pass through the lexer, parser and code generator.

```
int main() {
  return 0;
}
```

In order to compile this we need:

  - A tokeniser which can support type (int), identifier (main), brackets, curly braces, numbers, the return keyword and ignore whitespace.
  - A parser which can parse this function and expression.
  - Code generation to execute the main function.

## Testing

Currently, the default make target runs the tests. To make tests explicitly:

`
make test
`

To build `chibic`

`
make chibic
`
