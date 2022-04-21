#ifndef ERROR_H
#define ERROR_H


#include <QMessageBox>

typedef enum 
{
    OK,
    READ_FILE_ERR,
    OPEN_FILE_ERR,
    MEMORY_ERROR,
    INVALID_FIURE,
    INVALID_VALUE_SIZE,
    INVALID_CONNECTION
}errors;

void handle_error(const errors &code);

#endif