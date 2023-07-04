# serializer
Simple serializer for C++, works out of the box with trivially copyable types, ranges, aggregates, and classes that define a structured binding which can also be constructed with the types in the structured binding. For other classes simply specialize the `serialize` class.

Requires my [Type Utils](https://github.com/KaixoCode/type_utils) library to work.

## Examples

See `example.cpp` for a list of examples.
