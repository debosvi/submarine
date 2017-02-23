
#include "private/binn_p.h"

/*************************************************************************************/
int binn_to_string(const binn_t item, char **pvalue) {
    int _ret=1;
    binn_internal_t* p=0;
           
    p = binn_get_internal(item);
    if(p && (p->type==BINN_TYPE_STRING)) {
		(*pvalue)=p->data.str.s;
		_ret=0;
    }
	
	return _ret;
}