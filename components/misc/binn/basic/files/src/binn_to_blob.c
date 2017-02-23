
#include "private/binn_p.h"

/*************************************************************************************/
int binn_to_blob(const binn_t item, char **pvalue, unsigned int *psize) {
    int _ret=1;
    binn_internal_t* p=0;
           
    p = binn_get_internal(item);
    if(p && (p->type==BINN_TYPE_BLOB)) {
		(*pvalue)=p->data.str.s;
		(*psize)=p->data.str.len;
		_ret=0;
    }
	
	return _ret;
}