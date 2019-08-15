#ifndef ___PROPERTY_H___
#define ___PROPERTY_H___

void add(string, mixed);
void delete(string);
varargs mixed query(string, int);
void set(string, mixed);

void add_temp(string, mixed);
void delete_temp(string);
varargs mixed query_temp(string, int);
void set_temp(string, mixed);

#endif
