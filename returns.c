/**
 * @file returns.c
 * @author Roman Janiczek (xjanic25@vutbr.cz)
 * @brief Implementation of helper functions
 * @version 0.1
 * @date 2020-11-14
 */
#include "returns.h"

void iPrint(eRC code, bool error, char* opMsg) {
    fprintf(stderr, (!opMsg) ? "%s: %s" : "%s: %s %s", (error) ? "[ERROR]" : "[INFO]",
    (code == RC_ERR_INTERNAL) ? errorString[10] : errorString[code], (!opMsg) ? opMsg : NULL);
}