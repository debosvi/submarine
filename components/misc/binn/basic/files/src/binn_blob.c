
#include "private/binn_p.h"

/*************************************************************************************/
binn_t binn_blob(const char const *value, const unsigned int size) {
    return binn_new(BINN_TYPE_BLOB, value, size);
}