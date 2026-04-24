
# evalground

This project is a command-line tool for simple arithmetic operations.

## Command Line Options
Case 1:
	$ eval
	- Does nothing. (Yep, absolute nothing, just finishes.)

Case 2:
	$ eval prompt
	- Prompts the user for an operation.

## User Interface (Prompt)

Evaluation of one single arithmetic operation.
Bad expressions imply a Portuguese message before finishing.
Variable substitution is interactive only.

Case 1:
	Informe a operação> 3 + 4
	Resultado: 7

Case 2:
	Informe a operação> x - 7
	Informe o valor de x> 10
	Resultado: 17

Case 3:
	Informe a operação> a * b
	Informe o valor de a> 5
	Informe o valor de b> 3
	Resultado: 15

## Requirements
- Programming Language: C++17
- Build using make and cmake (cmake is required for testing)
- The executable must be named "eval"
- User interface must be in Portuguese
- Programming identifiers must be in Portuguese (without accents)

## Implementation Details
- Create classes for numbers, variables, and operations
- Do not use derived classes

## File Organization
- main.cpp
    - all classes, declarations and definitions, except prompt and parser inner essentials
    - The main representation of the operation
    - prompt and parser should provide functions to access input data from prompt, to fill operation
    - evaluation happens here
- prompt_parser.cpp
    - as above
- Namespace std: open it


## Future Work
- The project should be prepared for the future inclusion of a test framework, mainly GoogleTest.

## C Version (future)
- Use structs instead of classes
