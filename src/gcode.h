#ifndef G_CODE_H
#define G_CODE_H

typedef struct _list {
    struct _list*  next;
    int value;
} list;

typedef struct _letter {
    char display;
    union _value { 
        int i_value;
        float f_value;
    } value;
} letter;

typedef struct _gcode {
	letter g, m, n;
    letter a, b, c, d, e, f, h, i, j, k, o, p, q, r, s, t, u, v, w, x, y, z;
    struct _gcode* next;
} gcode ;

void gcode_init(gcode* code);
void gcode_free(gcode* code);

gcode* gcode_parse(const char* line);
void gcode_to_string(gcode* code, char* text);

#endif
