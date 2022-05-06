#include "../include/errors.h"

void handle_error(const errors &code)
{
    switch (code)
    {
        case READ_FILE_ERR:
            QMessageBox::critical(NULL, "User error", "При чтениии файла произошла ошибка.");
            break;
        case OPEN_FILE_ERR:
            QMessageBox::critical(NULL, "User error", "При открытии файла произошла ошибка.");
            break;
        case MEMORY_ERROR:
            QMessageBox::critical(NULL, "Sistem error", "Ошибка выделения памяти.");
            break;
        case INVALID_FIURE:
            QMessageBox::critical(NULL, "User error", "Фигура не построена.");
        break;
        case INVALID_VALUE_SIZE:
            QMessageBox::critical(NULL, "User error", "Неправильные размеры фигуры.");
        break;
        case INVALID_CONNECTION:
            QMessageBox::critical(NULL, "User error", "Связи берут больше точек.");
        break;
        default:
            QMessageBox::critical(NULL, "Critical error", "Неизвестная комманда.");
    }
    return;
}
