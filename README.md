# GLFW-hpp

A C++ binding for the GLFW library

## Compatibility

GLFW-hpp is currently compatible with GLFW 3.3

## Including into your project

You only need to include glfw3.hpp in place of glfw3.h and/or glfw3native.h

## Building

GLFW-hpp is header-only with one file: glfw3.hpp, so no extra building is required

## Implementation

This GLFW binding is implemented similarly to the vulkan.hpp binding for the Vulkan API

## Configuring

There are many macros that can be defined before including glfw3.hpp to configure the implementation
These macros are specified in glfw3.hpp

## State

GLFW-hpp is currently still in progress and not ready for use in projects
The features that have been implemented are:

- Macro configurations
- Enum classes
- to_string functions (for enums)
- Helper types (Flags class, "using" keyword for type safety etc.)
- Function pointer types
- API structures
- Basic API functions (init, terminate etc.)
- 1/3 Main classes complete
  - Complete: Monitor
  - Incomplete: Window, Cursor
