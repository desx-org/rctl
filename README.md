# rctl
Resource Constrained Template Library

This is a collection of c and c++ libraries put together to support embedded development. General principles are This is a work in progress and 

 1. Modulo Int: An class that behaves like a signed integer but instead of rolling over at INT_MAX, it rolls over at a template defined value.
 2. mdata_view: Similar to a std::span but it points to fragmented memory 
 3. pp_utils: Collection of pre-processor tools particulalry targeted at providing iteration over variadic macros
 4. circular_buffer: Proveds circular buffere where unlimited number of readers can pull data in thread safe way.
