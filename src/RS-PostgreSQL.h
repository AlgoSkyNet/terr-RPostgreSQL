#ifndef _RS_POSTGRESQL_H
#    define _RS_POSTGRESQL_H 1

/*
 * RS-PostgreSQL.h
 *
 * $Id: RS-PostgreSQL.h 189 2011-10-01 13:16:39Z dirk.eddelbuettel $
 *
 * This package was developed as a part of Summer of Code program organized by Google.
 * Thanks to David A. James & Saikat DebRoy, the authors of RMySQL package.
 * Code from RMySQL package was reused with the permission from the authors.
 * Also Thanks to my GSoC mentor Dirk Eddelbuettel for helping me in the development.
 *
 * Processed with
 * indent --verbose -br -brs -i4 -nut -ppi 4 --line-length120 --comment-line-length120 --leave-preprocessor-space -npcs
 *
 */

#    ifdef _cplusplus
extern "C" {
#    endif

#    include "libpq-fe.h"
#    include <string.h>
#    include "RS-DBI.h"

/* Note that the default number of maximum connections to the PostgreSQL server is typically 100
 *  connections, but may be less if your kernel settings will not support it (as determined during initdb)
 * Refer to: http://www.postgresql.org/docs/8.2/interactive/runtime-config-resource.html for details
 */


    typedef struct st_sdbi_conParams {
        char *user;
        char *password;
        char *host;
        char *dbname;
        char *port;
        char *tty;
        char *options;
    } RS_PostgreSQL_conParams;

    RS_PostgreSQL_conParams *RS_PostgreSQL_allocConParams(void);

    void RS_PostgreSQL_freeConParams(RS_PostgreSQL_conParams * conParams);

    /* The following functions are the S/R entry points into the C implementation
     * (i.e., these are the only ones visible from R/S) we use the prefix
     * "RS_PostgreSQL" in function names to denote this.
     * These functions are  built on top of the underlying RS_DBI manager,
     * connection, and resultsets structures and functions (see RS-DBI.h).
     *
     * Note: A handle is just an R/S object (see RS-DBI.h for details), i.e.,
     *       Mgr_Handle, Con_Handle, Res_Handle, Db_Handle are s_object
     *       (integer vectors, to be precise).
     */

    /* dbManager */
    SEXP RS_PostgreSQL_init(SEXP config_params, SEXP reload);
    SEXP RS_PostgreSQL_close(SEXP mgrHandle);

    /* dbConnection */
    SEXP RS_PostgreSQL_newConnection(SEXP mgrHandle, SEXP con_params);
    SEXP RS_PostgreSQL_cloneConnection(SEXP conHandle);
    SEXP RS_PostgreSQL_closeConnection(SEXP conHandle);
    SEXP RS_PostgreSQL_getException(SEXP conHandle);       /* err No, Msg */

    /* dbResultSet */
    SEXP RS_PostgreSQL_exec(SEXP conHandle, SEXP statement);
    SEXP RS_PostgreSQL_fetch(SEXP rsHandle, SEXP max_rec);
    SEXP RS_PostgreSQL_closeResultSet(SEXP rsHandle);

    SEXP RS_PostgreSQL_copyin(SEXP conHandle, SEXP filename);

    SEXP RS_PostgreSQL_validHandle(SEXP handle);    /* boolean */

    RS_DBI_fields *RS_PostgreSQL_createDataMappings(SEXP resHandle);
    /* the following funs return named lists with meta-data for
     * the manager, connections, and  result sets, respectively.
     */
    SEXP RS_PostgreSQL_managerInfo(SEXP mgrHandle);
    SEXP RS_PostgreSQL_connectionInfo(SEXP conHandle);
    SEXP RS_PostgreSQL_resultSetInfo(SEXP rsHandle);

    /*  OID"S mapping taken from pg_type.h */
#    define BOOLOID			16
#    define BYTEAOID		17
#    define CHAROID			18
#    define NAMEOID			19
#    define INT8OID			20
#    define INT2OID			21
#    define INT2VECTOROID	        22
#    define INT4OID			23
#    define REGPROCOID		24
#    define TEXTOID			25
#    define OIDOID			26
#    define TIDOID		 	27
#    define XIDOID 			28
#    define CIDOID 			29
#    define OIDVECTOROID		30
#    define PG_TYPE_RELTYPE_OID 	71
#    define PG_ATTRIBUTE_RELTYPE_OID 75
#    define PG_PROC_RELTYPE_OID 	81
#    define PG_CLASS_RELTYPE_OID 	83
#    define XMLOID 			142
#    define POINTOID		600
#    define LSEGOID			601
#    define PATHOID			602
#    define BOXOID			603
#    define POLYGONOID		604
#    define LINEOID			628
#    define FLOAT4OID 		700
#    define FLOAT8OID 		701
#    define ABSTIMEOID		702
#    define RELTIMEOID		703
#    define TINTERVALOID		704
#    define UNKNOWNOID		705
#    define CIRCLEOID		718
#    define CASHOID 		790
#    define MACADDROID 		829
#    define INETOID 		869
#    define CIDROID 		650
#    define INT4ARRAYOID		1007
#    define FLOAT4ARRAYOID 		1021
#    define ACLITEMOID		1033
#    define CSTRINGARRAYOID		1263
#    define BPCHAROID		1042
#    define VARCHAROID		1043
#    define DATEOID			1082
#    define TIMEOID			1083
#    define TIMESTAMPOID		1114
#    define TIMESTAMPTZOID		1184
#    define INTERVALOID		1186
#    define TIMETZOID		1266
#    define BITOID			1560
#    define VARBITOID	  	1562
#    define NUMERICOID		1700
#    define REFCURSOROID		1790
#    define REGPROCEDUREOID 	2202
#    define REGOPEROID		2203
#    define REGOPERATOROID		2204
#    define REGCLASSOID		2205
#    define REGTYPEOID		2206
#    define REGTYPEARRAYOID 	2211
#    define TSVECTOROID		3614
#    define GTSVECTOROID		3642
#    define TSQUERYOID		3615
#    define REGCONFIGOID		3734
#    define REGDICTIONARYOID	3769
#    define RECORDOID		2249
#    define CSTRINGOID		2275
#    define ANYOID			2276
#    define ANYARRAYOID		2277
#    define VOIDOID			2278
#    define TRIGGEROID		2279
#    define LANGUAGE_HANDLEROID	2280
#    define INTERNALOID		2281
#    define OPAQUEOID		2282
#    define ANYELEMENTOID		2283
#    define ANYNONARRAYOID		2776
#    define ANYENUMOID		3500

    SEXP RS_PostgreSQL_typeNames(SEXP typeIds);
    extern const struct data_types RS_dataTypeTable[];

#    ifdef _cplusplus
}
#    endif

#endif /* _RS_PostgreSQL_H */
