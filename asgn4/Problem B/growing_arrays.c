#include "growing_arrays.h"
#include "test_growing_arrays.c"

int add_record(Record record) {
    // double the size if full
    if (table.nval == table.max) {
        table.max *= GROW_SIZE;
        table.record = realloc(table.record, sizeof(Record) * table.max);
    }

    // Add the new record to the array
    table.record[table.nval] = record;
    int res = table.nval;
    table.nval++;

    return res;
}

int del_record(const char *name) {
    int occured = 0; //record was found

    // use name to compare
    for (int i = 0; i < table.nval; i++) {
        if (strcmp(table.record[i].name, name) == 0) {
            occured = 1;
            break;
        }
    }

    if (occured) {
        int i = 0;
        int j = 0;
        
        // Shift elements to overwrite the matched record
        while (i < table.nval) {
            if (strcmp(table.record[i].name, name) != 0) {
                // printf("Array before moving records:\n");
                // for (int k = 0; k < table.nval; k++) {
                    // printf("Record %d - Name: %s, ID: %d\n", k, table.record[k].name, table.record[k].id);
                // }
                table.record[j] = table.record[i];
                j++;
                
                // printf("Array after moving records:\n");
                // for (int k = 0; k < table.nval; k++) {
                    // printf("Record %d - Name: %s, ID: %d\n", k, table.record[k].name, table.record[k].id);
    // }
            }
            i++;
        }
        
        table.nval--; // decrement
        return 1; // means successfully deleted
    } else {
        return 0; // Error or no matching occured
    }
}


int get_id(const char *name) {
    int i = 0;
    while (i < table.nval) {
        if (strcmp(table.record[i].name, name) == 0) {
            // found, get the id
            return table.record[i].id;
        }
        i++;
    }

    return 0; // not found
}

Record get_record(int index) {
    if (0 <= index && index < table.nval) {
        return table.record[index];
    } else {
        // Have a Record structure with empty name and ID 0
        return (Record){"", 0};
    }
}



