# How to write bloem

## In short, how does bloem work

## Syntax

```bloem
1 2 3;
4;
5 6 7 8 9;
```

Here above is a sample of bloem code. The first argument is the function called, all the next arguments are the parameters that will be written in the memory cells. The program will end if it reaches the end of the program, or if the function `0` is called in the program.
_I will support pointer like types in the furure, but still need to figure out how to make them work_

## Adding own C++ functions

There are some standard function supported by the language, but there is an easy way to add more functions to the language.

### Main setup

First write a `C++` function. After this, run the program by running `bloem_class.run()`. Use the function `bloem_class.add_function(index, function)` with first the number used for the funcion, and second the function. This overwrites the current function for the program.

### Parameters and return values

For using parameters and return values, there are memory cells available. For using the memory cells, there is a global pointer to the current class/bloem program that the code is running, if you want to use this use `global_bloem->memory_cells`. The standard return values will be index `0`, and the filling of the memory cells using the parameter way in the bloem code starts at index `1`, so the program:

```bloem
5 4 3;
```

Will fill `global_bloem->memory_cells[1]` with value 5, index 2 will be 4, ect.
<!-- markdownlint-disable MD028 -->
> [!IMPORTANT]
> The language only supports `void(void)` functions, so no return values or parameters, they should be handled by by the memory cells.

> [!WARNING]
> Make sure there is enough memory reserved for the extra functions with `#extra_functions` or changing the `bloem_class.extra_functions` varable.
<!-- markdownlint-enable MD028 -->
