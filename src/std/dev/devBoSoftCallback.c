/*************************************************************************\
* Copyright (c) 2002 The University of Chicago, as Operator of Argonne
*     National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
*     Operator of Los Alamos National Laboratory.
* EPICS BASE Versions 3.13.7
* and higher are distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/

/* devBoCallbackSoft.c */
/*
 *      Author:  Marty Kraimer
 *      Date:    04NOV2003
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alarm.h"
#include "dbDefs.h"
#include "dbLock.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "boRecord.h"
#include "epicsExport.h"

/* Create the dset for devBoCallbackSoft */
static long write_bo(boRecord *prec);

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	write_bo;
}devBoSoftCallback={
	5,
	NULL,
	NULL,
	NULL,
	NULL,
	write_bo
};
epicsExportAddress(dset,devBoSoftCallback);

static long write_bo(boRecord *prec)
{
    struct link *plink = &prec->out;
    long status;

    if(prec->pact) return(0);
    if(plink->type!=CA_LINK) {
        status = dbPutLink(plink,DBR_USHORT,&prec->val,1);
        return(status);
    }
    status = dbCaPutLinkCallback(plink,DBR_USHORT,&prec->val,1,
        dbCaCallbackProcess,plink);
    if(status) {
        recGblSetSevr(prec,LINK_ALARM,INVALID_ALARM);
        return(status);
    }
    prec->pact = TRUE;
    return(0);
}
