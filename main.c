#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;

typedef struct
{
    u16 length;
    u8 *data;
}String;

// how much that letter ocurrs in string
u16 
string_how_much(String *string, u8 letter)
{
    u16 count = 0;
    
    u8 *cur_letter = string->data;
    
    for(u8 *cur_letter = string->data;
        *cur_letter;
        cur_letter++)
    {
        if(*cur_letter == letter)
        {
            count++;
        }
    }
    
    return count;
}

String*
string_reverse(String *string)
{
    String *reversed_string = (String*)malloc(sizeof(String));
    reversed_string->data = (u8*)malloc(string->length);
    reversed_string->length = string->length;
    
    u8 *rvrsd_p_start = string->data;
    u8 *rvrsd_p_end   = string->data + string->length;
    u8 *dst_str = reversed_string->data;
    
    u16 count = 0;
    for(; 
        rvrsd_p_start != rvrsd_p_end;
        rvrsd_p_start++,count++)
    {
        *dst_str++ = *(u8*)(rvrsd_p_end - count - 1);
    }
    
    return reversed_string;
}

u16 
string_strlen(char *string)
{
    
    u16 src_string_length = 0;
    for(u8 *letter = string; 
        *letter;
        letter++)
    {
        src_string_length++;
    }
    return src_string_length;
}


u8*
string_duplicate(char *src_string)
{
    u16 src_string_length = string_strlen(src_string);
    u8 *dst_string = malloc(src_string_length);
    
    u8 *src_p   = src_string;
    u8 *src_end = src_p + src_string_length;
    u8 *p = dst_string;
    while(src_p != src_end)
    {
        *p++ = *src_p++;
    }
    return dst_string;
}

String*
string_clone(char *src_string)
{
    String *string = (String*)malloc(sizeof(String));
    if(!string)
    {
        assert(!"Allocation for string failed!");
    }
    string->data    = string_duplicate(src_string);
    string->length  = string_strlen(src_string);
    return string;
}


String*
string_new(u16 string_length)
{
    String *string = (String*)malloc(sizeof(String));
    if(!string)
    {
        assert(!"Allocation for string failed!");
    }
    
    string->data    = (u8*)malloc(string_length);
    string->length  = string_length;
    return string;
}


void
string_free(String *string)
{
    if(string)
    {
        if(string->data)
        {
            free(string->data);
        }
        free(string);
    }
}

void
string_print(String *string, FILE *file)
{
    static char buf[65537];
    memcpy(&buf,string->data,string->length);
    buf[string->length] = '\0';
    fprintf(file, "%s", buf);
    
}

u16
string_length(String *string)
{
    assert(string != 0);
    assert(string->data != 0);
    
    return string->length;
}

String*
string_concatenate(String *left_string, String *right_string)
{
    assert(left_string != 0);
    assert(right_string != 0);
    
    String *concatenated_string = malloc(sizeof(String));
    u16 total_string_length = left_string->length + right_string->length;
    concatenated_string->data = (u8*)malloc(total_string_length);
    concatenated_string->length = total_string_length;
    if(concatenated_string->data)
    {
        memcpy(concatenated_string->data, left_string->data, left_string->length);
        memcpy(concatenated_string->data + left_string->length, right_string->data, right_string->length);
    }
    return concatenated_string;
}

String*
string_left(String *src_string,u16 length)
{
    String *string = (String*)malloc(sizeof(String));
    string->data   = (u8*)malloc(length);
    string->length = length;
    
    if(string)
    {
        memcpy(string->data, src_string->data, length);
    }
    return string;
}

String*
string_right(String *src_string, u16 length)
{
    String *string = (String*)malloc(sizeof(String));
    string->data   = (u8*)malloc(length);
    string->length = length;
    
    if(string)
    {
        memcpy(string->data, src_string->data + src_string->length - length - 1, length);
    }
    return string;
}

int main(int argc,char *argv[])
{
    String *my_first_string = string_clone("Hello world! ");
    String *my_second_string = string_clone("world Hello!");
    
    string_print(my_first_string,stdout);
    fprintf(stdout,"\n");
    string_print(my_second_string,stdout);
    fprintf(stdout,"\n");
    
    String *string_concatenated = string_concatenate(my_first_string, my_second_string);
    string_print(string_concatenated,stdout);
    
    fprintf(stdout,"\n");
    
    u16 my_first_string_length = string_length(my_first_string);
    fprintf(stdout,"length: [%d]", my_first_string_length);
    
    fprintf(stdout,"\n");
    
    u8 *data = string_duplicate(my_first_string->data);
    
    fprintf(stdout,"string: [%s]", data);
    
    fprintf(stdout,"\n");
    
    String *str_left_test = string_left(my_first_string,5);
    string_print(str_left_test,stdout);
    
    fprintf(stdout,"\n");
    
    String *str_right_test = string_right(my_first_string,6);
    string_print(str_right_test,stdout);
    
    fprintf(stdout,"\n");
    
    String *reversed_string_test = string_reverse(my_second_string);
    string_print(reversed_string_test,stdout);
    
    fprintf(stdout,"\n");
    
    u16 n = string_how_much(my_first_string, 'o');
    
    fprintf(stdout,"The letter:[%c]: occurs [%d] times in string: [%s]", 'o',n,my_first_string->data);
    
    fprintf(stdout,"\n");
    
    
    string_free(reversed_string_test);
    string_free(str_left_test);
    string_free(my_first_string);
    string_free(my_second_string);
    string_free(string_concatenated);
    return 0;
}