
## Test of date and datetime types, based on earlier version in inst/devTests
##
## Dirk Eddelbuettel, 21 Oct 2008

dbTypeTests <- function(con, dateclass="timestamp without time zone") {
    cat("\n\n**** Trying with ", dateclass, "\n")

    if (dbExistsTable(con, "tempostgrestable"))
        dbRemoveTable(con, "tempostgrestable")

    dbGetQuery(con, paste("create table tempostgrestable (tt ", dateclass, ", zz integer);", sep=""))
    dbGetQuery(con, "insert into tempostgrestable values('2008-07-01 14:15:16.123', 1);")

    now <- ISOdatetime(2000,1,2,3,4,5.678)
    dbGetQuery(con, paste("insert into tempostgrestable values('", format(now), "', 2);", sep=""))

    res <- dbReadTable(con, "tempostgrestable")
    print(res)

    res <- dbSendQuery(con, "select tt from tempostgrestable;")
    data <- fetch(res, n=-1)
    print(dbColumnInfo(res))

    times <- data[,1]
    print(times)
    print(class(times[1]))

    print(diff(times))

    dbRemoveTable(con, "tempostgrestable")
    invisible(NULL)
}

## only run this if this env.var is set correctly
if ((Sys.getenv("POSTGRES_USER") != "") &
    (Sys.getenv("POSTGRES_HOST") != "") &
    (Sys.getenv("POSTGRES_DATABASE") != "")) {

    ## try to load our module and abort if this fails
    stopifnot(require(RPostgreSQL))

    ## Force a timezone to make the tests comparable at different locations
    Sys.setenv("PGDATESTYLE"="German")
    Sys.setenv("TZ"="UTC")

    ## load the PostgresSQL driver
    drv <- dbDriver("PostgreSQL")
    ## can't print result as it contains process id which changes  print(summary(drv))

    ## connect to the default db
    con <- dbConnect(drv,
                     user=Sys.getenv("POSTGRES_USER"),
                     password=Sys.getenv("POSTGRES_PASSWD"),
                     host=Sys.getenv("POSTGRES_HOST"),
                     dbname=Sys.getenv("POSTGRES_DATABASE"),
                     port=ifelse((p<-Sys.getenv("POSTGRES_PORT"))!="", p, 5432))

    dbTypeTests(con, "timestamp")
    dbTypeTests(con, "timestamp with time zone")
    dbTypeTests(con, "date")

    dbDisconnect(con)
}

