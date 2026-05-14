/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
 * AlliedModders LLC give you permission to link the code of this program
 * (as well as its derivative works) to "Counter-Strike 2," "Source 2,"
 * "Steam," and any Game MODs or server software running on software by
 * Valve Corporation. You must obey the GNU General Public License in all
 * respects for all other code used.
 *
 * Additionally, this exception applies to all derivative works unless
 * otherwise stated in LICENSE.txt.
 *
 * Authors:
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once
#include "source2toolkit/IToolkitMySQL.h"

#ifdef WIN32
#include <WinSock2.h>
#include <mysql.h>
#else
#include <mysql.h>
#endif

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace mysql {
    class CMySQLQuery;
    class MySQLConnection;

    class ThreadOperation
    {
    public:
        virtual ~ThreadOperation() = default;

        virtual void RunThreadPart() = 0;
        virtual void CancelThinkPart() = 0;
        virtual void RunThinkPart() = 0;
    };

    class TMySQLConnectOp : public ThreadOperation
    {
    public:
        TMySQLConnectOp(MySQLConnection *con, ToolkitMySQLConnectCallbackFunc func) : m_pCon(con), m_callback(func) {}

        void RunThreadPart();
        void CancelThinkPart();
        void RunThinkPart();

    private:
        MySQLConnection *m_pCon;
        ToolkitMySQLConnectCallbackFunc m_callback;
        MYSQL *m_pDatabase = nullptr;
        char m_szError[255] {};
    };

    class TMySQLQueryOp : public ThreadOperation
    {
    public:
        TMySQLQueryOp(MySQLConnection *con, std::string query, ToolkitMySQLQueryCallbackFunc func) : m_pCon(con), m_szQuery(query), m_callback(func) {}

        ~TMySQLQueryOp();

        void RunThreadPart();
        void CancelThinkPart();
        void RunThinkPart();

    private:
        MySQLConnection *m_pCon;
        std::string m_szQuery;
        ToolkitMySQLQueryCallbackFunc m_callback;
        MYSQL_RES *m_res = nullptr;
        CMySQLQuery *m_pQuery = nullptr;
        char m_szError[255] {};
    };

    class TMySQLTransactOp : public ThreadOperation
    {
    public:
        TMySQLTransactOp(MySQLConnection *con, ToolkitMySQLTransaction txn, ToolkitMySQLTransactionSuccessCallbackFunc success, ToolkitMySQLTransactionFailureCallbackFunc failure)
            : m_pCon(con), m_txn(txn), m_successCallback(success), m_failureCallback(failure)
        {
        }

        ~TMySQLTransactOp();

        void RunThreadPart();
        void CancelThinkPart();
        void RunThinkPart();

    private:
        MySQLConnection *m_pCon;
        ToolkitMySQLTransaction m_txn;
        ToolkitMySQLTransactionSuccessCallbackFunc m_successCallback;
        ToolkitMySQLTransactionFailureCallbackFunc m_failureCallback;
        std::vector<IToolkitMySQLQuery *> m_pQueries;
        char m_szError[255] {};
        int m_failIndex;

        bool DoSimpleQuery(const char *query);
        CMySQLQuery *DoQuery(const char *query);
    };

    class CMySQLResult : public IToolkitMySQLResult, IToolkitMySQLRow
    {
        friend class CMySQLQuery;

    public:
        CMySQLResult(MYSQL_RES *res);

        void Update();

        int GetRowCount();
        int GetFieldCount();
        bool FieldNameToNum(const char *name, unsigned int *columnId);
        const char *FieldNumToName(unsigned int colId);
        bool MoreRows();
        IToolkitMySQLRow *FetchRow();
        IToolkitMySQLRow *CurrentRow();
        bool Rewind();
        int GetFieldType(unsigned int field);
        const char *GetString(unsigned int columnId, size_t *length = nullptr);
        size_t GetDataSize(unsigned int columnId);
        float GetFloat(unsigned int columnId);
        int GetInt(unsigned int columnId);
        bool IsNull(unsigned int columnId);
        int64_t GetInt64(unsigned int columnId);

    private:
        // MYSQL* m_pDatabase;
        MYSQL_RES *m_pRes;

        unsigned int m_ColCount = 0;
        unsigned int m_RowCount = 0;
        unsigned int m_CurRow = 0;
        MYSQL_ROW m_Row;
        unsigned long *m_Lengths = 0;
    };

    class CMySQLQuery : public IToolkitMySQLQuery
    {
        friend class CMySQLResult;

    public:
        CMySQLQuery(MySQLConnection *db, MYSQL_RES *res);
        ~CMySQLQuery();
        IToolkitMySQLResult *GetResultSet();
        bool FetchMoreResults();
        unsigned int GetInsertId();
        unsigned int GetAffectedRows();

    private:
        MySQLConnection *m_pDatabase;
        CMySQLResult m_res;
        unsigned int m_insertId;
        unsigned int m_affectedRows;
    };

    class MySQLConnection : public IToolkitMySQLConnection
    {
    public:
        MySQLConnection(const ToolkitMySQLConnectionInfo info);
        ~MySQLConnection() override;

        void Connect(ToolkitMySQLConnectCallbackFunc callback) override;
        void Query(char *query, ToolkitMySQLQueryCallbackFunc callback) override;
        void Query(const char *query, ToolkitMySQLQueryCallbackFunc callback, ...) override;
        void ExecuteTransaction(ToolkitMySQLTransaction txn, ToolkitMySQLTransactionSuccessCallbackFunc success, ToolkitMySQLTransactionFailureCallbackFunc failure) override;

        void Destroy() override;
        void RunFrame();

        void SetDatabase(MYSQL *db)
        {
            m_pDatabase = db;
        }

        MYSQL *GetDatabase()
        {
            return m_pDatabase;
        }

        unsigned int GetInsertID();
        unsigned int GetAffectedRows();
        std::string Escape(char *string) override;
        std::string Escape(const char *string) override;

        ToolkitMySQLConnectionInfo m_info;

    private:
        void ThreadRun();
        void AddToThreadQueue(ThreadOperation *threadOperation);

        std::queue<ThreadOperation *> m_threadQueue;
        std::queue<ThreadOperation *> m_ThinkQueue;
        std::unique_ptr<std::thread> m_thread;
        std::condition_variable m_QueueEvent;
        std::mutex m_Lock;
        std::mutex m_ThinkLock;
        bool m_Terminate = false;
        MYSQL *m_pDatabase = nullptr;
    };

    class MySQLManager final : public IToolkitMySQL
    {
    public:
        IToolkitMySQLConnection* CreateConnection(ToolkitMySQLConnectionInfo info) override;
    public:
        std::vector<MySQLConnection*> m_vecMysqlConnections;
    };

    extern MySQLManager mysqlManager;
}
