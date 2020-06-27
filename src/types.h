#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define true 1
#define false 0

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

#define NULL 0

typedef s32 bool;
typedef float  f32;
typedef double f64;

typedef u8  bool8;
typedef u16 bool16;
typedef u32 bool32;

typedef void (*command)(void);

#endif /* ENGINE_TYPES_H */
