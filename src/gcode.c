#include "gcode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void gcode_init(gcode* code)
{
    memset(code, 0, sizeof(gcode));
    code->g.value.i_value = -1;
    code->m.value.i_value = -1;
    code->n.value.i_value = -1;
    code->next = NULL;
}

void gcode_free(gcode* code)
{
    if(code) {
        gcode* tmp = code->next;
        free(code);
        gcode_free(tmp);
    }
}

gcode* gcode_parse(const char* line) {

    #define PARSE_GCODE_LETTER_FLOAT(_det, _value, _line)  \
    if (_det == (_line)[0]) {\
        _value.value.f_value = atof(_line + 1); \
        _value.display = 1; \
        i++; \
        continue; \
    }
	
    #define PARSE_GCODE_LETTER_INT(_det, _value, _line)  \
    if (_det == (_line)[0]) {\
        _value.value.i_value = atoi(_line + 1); \
        _value.display = 1; \
        i++; \
        continue; \
    }

    #define PARSE_GCODE_CMD_TYPE(_det, _value, _line)  \
    if(_det == (_line)[0]) { \
        if( _value.display == 0 ) { \
            _value.value.i_value = atoi(_line + 1); \
            _value.display = 1; \
            i++; \
        } \
        else \
        { \
            presult->next = malloc(sizeof(gcode)); \
            presult = presult->next; \
            gcode_init(presult); \
            _value.value.i_value = atoi(_line + 1); \
            _value.display = 1; \
            i++; \
        } \
    }
	
    gcode* result = malloc(sizeof(gcode));
    gcode_init(result);
    
    gcode* presult = result;
    if(line) {
        int i = 0;
        while(line[i] != '\0') {
            /* parse command type G code or M code*/
            PARSE_GCODE_CMD_TYPE('G', presult->g, line + i);
            PARSE_GCODE_CMD_TYPE('M', presult->m, line + i);
            PARSE_GCODE_LETTER_INT('N', presult->n, line + i);
            /* parse variable*/
            PARSE_GCODE_LETTER_FLOAT('A', presult->a, line + i);
            PARSE_GCODE_LETTER_FLOAT('B', presult->b, line + i);
            PARSE_GCODE_LETTER_FLOAT('C', presult->c, line + i);
            PARSE_GCODE_LETTER_FLOAT('D', presult->d, line + i);
            PARSE_GCODE_LETTER_FLOAT('E', presult->e, line + i);
            PARSE_GCODE_LETTER_FLOAT('F', presult->f, line + i);
            PARSE_GCODE_LETTER_FLOAT('H', presult->h, line + i);
            PARSE_GCODE_LETTER_FLOAT('I', presult->i, line + i);
            PARSE_GCODE_LETTER_FLOAT('J', presult->j, line + i);
            PARSE_GCODE_LETTER_FLOAT('K', presult->k, line + i);
            PARSE_GCODE_LETTER_FLOAT('O', presult->o, line + i);
            PARSE_GCODE_LETTER_FLOAT('P', presult->p, line + i);
            PARSE_GCODE_LETTER_FLOAT('Q', presult->q, line + i);
            PARSE_GCODE_LETTER_FLOAT('R', presult->r, line + i);
            PARSE_GCODE_LETTER_FLOAT('S', presult->s, line + i);
            PARSE_GCODE_LETTER_FLOAT('T', presult->t, line + i);
            PARSE_GCODE_LETTER_FLOAT('U', presult->u, line + i);
            PARSE_GCODE_LETTER_FLOAT('V', presult->v, line + i);
            PARSE_GCODE_LETTER_FLOAT('W', presult->w, line + i);
            PARSE_GCODE_LETTER_FLOAT('X', presult->x, line + i);
            PARSE_GCODE_LETTER_FLOAT('Y', presult->y, line + i);
            PARSE_GCODE_LETTER_FLOAT('Z', presult->z, line + i);
            
            if(line[i] == '#' 
            || line[i] == ';' 
            || line[i] == '[') {
                return result;
            }
            i++;
        }
    }
    return result;
}

void gcode_to_string(gcode* code, char* text)
{    
    char* p = text;

    #define GCODE_INT_TO_STR(_type, _value, _out) \
    if( _value.display ) { \
        sprintf(_out, "%s%02d ", _type, _value.value.i_value); \
        _out = _out + strlen(_out); \
    }

    #define GCODE_FLOAT_TO_STR(_type, _value, _out) \
    if( _value.display ) { \
        sprintf(_out, "%s%g ", _type, _value.value.f_value); \
        _out = _out + strlen(_out); \
    }
    
    GCODE_INT_TO_STR("N", code->n, p);
    GCODE_INT_TO_STR("G", code->g, p);
    GCODE_INT_TO_STR("M", code->m, p);

    GCODE_FLOAT_TO_STR("A", code->a, p);
    GCODE_FLOAT_TO_STR("B", code->b, p);
    GCODE_FLOAT_TO_STR("C", code->c, p);
    GCODE_FLOAT_TO_STR("D", code->d, p);
    GCODE_FLOAT_TO_STR("E", code->e, p);
    GCODE_FLOAT_TO_STR("F", code->f, p);
    GCODE_FLOAT_TO_STR("H", code->h, p);
    GCODE_FLOAT_TO_STR("I", code->i, p);
    GCODE_FLOAT_TO_STR("J", code->j, p);
    GCODE_FLOAT_TO_STR("K", code->k, p);
    GCODE_FLOAT_TO_STR("O", code->o, p);
    GCODE_FLOAT_TO_STR("P", code->p, p);
    GCODE_FLOAT_TO_STR("Q", code->q, p);
    GCODE_FLOAT_TO_STR("R", code->r, p);
    GCODE_FLOAT_TO_STR("S", code->s, p);
    GCODE_FLOAT_TO_STR("T", code->t, p);
    GCODE_FLOAT_TO_STR("V", code->u, p);
    GCODE_FLOAT_TO_STR("V", code->v, p);
    GCODE_FLOAT_TO_STR("W", code->w, p);
    GCODE_FLOAT_TO_STR("X", code->x, p);
    GCODE_FLOAT_TO_STR("Y", code->y, p);
    GCODE_FLOAT_TO_STR("Z", code->z, p);
    
    if (code->next) {
        gcode_to_string(code->next, p);
    }
}
