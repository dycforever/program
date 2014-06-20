#include "log.h"
namespace dyc {

#ifndef STDOUT_LOG
log4c_category_t* gDYCLogObj;
#endif

DYC_GLOBAL dyc_global;

}

