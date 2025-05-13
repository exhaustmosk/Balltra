#include "DatabaseHelper.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <sqlext.h>
#include "Windows/HideWindowsPlatformTypes.h"

bool DatabaseHelper::RunSQLQuery(const std::string& Query, std::string& Result)
{
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;
	SQLRETURN RetCode;

	// Allocate environment handle
	RetCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

	// Allocate connection handle
	RetCode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	// Connect to Oracle DB via ODBC
	RetCode = SQLConnect(hDbc, (SQLTCHAR*)TEXT("FREEPDB1"), SQL_NTS,
		(SQLTCHAR*)TEXT("SYSTEM"), SQL_NTS,
		(SQLTCHAR*)TEXT("YourOraclePassword"), SQL_NTS);

	if (RetCode == SQL_SUCCESS || RetCode == SQL_SUCCESS_WITH_INFO)
	{
		// Allocate statement handle
		RetCode = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

		// Execute query
		RetCode = SQLExecDirect(hStmt, (SQLTCHAR*)Query.c_str(), SQL_NTS);

		if (RetCode == SQL_SUCCESS || RetCode == SQL_SUCCESS_WITH_INFO)
		{
			SQLCHAR SqlResult[1024];
			SQLLEN Len;
			SQLFetch(hStmt);
			SQLGetData(hStmt, 1, SQL_C_CHAR, SqlResult, 1024, &Len);
			Result = std::string((char*)SqlResult);
		}

		// Cleanup
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		SQLDisconnect(hDbc);
	}

	// Free handles
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return (RetCode == SQL_SUCCESS || RetCode == SQL_SUCCESS_WITH_INFO);
}
