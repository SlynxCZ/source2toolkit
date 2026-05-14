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
#include "mysql.h"
#include "pluginapi.h"
#include "utils/log.h"

namespace mysql
{
    MySQLManager mysqlManager;

    void TMySQLConnectOp::RunThreadPart()
    {
        m_szError[0] = '\0';
        MYSQL *mysql = mysql_init(NULL);

        if (!mysql)
        {
            FP_ERROR("Uh oh, mysql is null!");
        }

        const char *host = NULL, *socket = NULL;

        int timeout = 60;

        mysql_options(mysql, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&timeout);
        mysql_options(mysql, MYSQL_OPT_READ_TIMEOUT, (const char *)&timeout);
        mysql_options(mysql, MYSQL_OPT_WRITE_TIMEOUT, (const char *)&timeout);

        bool my_true = true;
        mysql_options(mysql, MYSQL_OPT_RECONNECT, (const char *)&my_true); // deprecated

        if (m_pCon->m_info.host[0] == '/')
        {
            host = "localhost";
            socket = host;
        }
        else
        {
            host = m_pCon->m_info.host;
            socket = NULL;
        }

        if (!mysql_real_connect(mysql, host, m_pCon->m_info.user, m_pCon->m_info.pass, m_pCon->m_info.database, m_pCon->m_info.port, socket, ((1) << 17)))
        {
            mysql_close(mysql);
            strncpy(m_szError, mysql_error(mysql), sizeof m_szError);
            return;
        }

        m_pDatabase = mysql;
    }

    void TMySQLConnectOp::RunThinkPart()
    {
        if (m_szError[0])
        {
            FP_ERROR("Failed to establish a MySQL connection: {}", m_szError);
        }

        m_pCon->SetDatabase(m_pDatabase);
        m_callback(m_pDatabase != nullptr);
    }

    void TMySQLConnectOp::CancelThinkPart()
    {
        mysql_close(m_pDatabase);
        m_pCon->SetDatabase(nullptr);
    }

    TMySQLQueryOp::~TMySQLQueryOp()
    {
        delete m_pQuery;
    }

    void TMySQLQueryOp::RunThreadPart()
    {
        auto pDatabase = m_pCon->GetDatabase();
        m_szError[0] = '\0';
        if (mysql_query(pDatabase, m_szQuery.c_str()))
        {
            V_snprintf(m_szError, sizeof m_szError, "MySQL query error: %s\n", mysql_error(pDatabase));
            return;
        }

        if (mysql_field_count(pDatabase))
        {
            m_res = mysql_store_result(pDatabase);
        }
    }

    void TMySQLQueryOp::RunThinkPart()
    {
        if (m_szError[0])
        {
            FP_ERROR("{}", m_szError);
            return;
        }

        m_pQuery = new CMySQLQuery(m_pCon, m_res);
        m_callback(m_pQuery);
    }

    void TMySQLQueryOp::CancelThinkPart()
    {
        mysql_close(m_pCon->GetDatabase());
        m_pCon->SetDatabase(nullptr);
    }

    TMySQLTransactOp::~TMySQLTransactOp()
    {
        for (auto query : m_pQueries)
        {
            delete query;
        }
        m_pQueries.clear();
    }

    void TMySQLTransactOp::RunThreadPart()
    {
        if (!this->DoSimpleQuery("BEGIN"))
        {
            return;
        }
        for (size_t i = 0; i < this->m_txn.queries.size(); i++)
        {
            CMySQLQuery *result = DoQuery(this->m_txn.queries[i].c_str());
            if (!result)
            {
                this->DoSimpleQuery("ROLLBACK");
                m_failIndex = (int)i;
                return;
            }
            this->m_pQueries.push_back(result);
        }
        if (!this->DoSimpleQuery("COMMIT"))
        {
            this->DoSimpleQuery("ROLLBACK");
            return;
        }
    }

    void TMySQLTransactOp::CancelThinkPart()
    {
        mysql_close(m_pCon->GetDatabase());
        m_pCon->SetDatabase(nullptr);
    }

    void TMySQLTransactOp::RunThinkPart()
    {
        if (!m_szError[0])
        {
            m_successCallback(m_pQueries);
            m_pQueries.clear();
            return;
        }
        FP_ERROR("TMySQLTransactOp ERROR: {}", m_szError);
        m_failureCallback(m_szError, m_failIndex);
    }

    bool TMySQLTransactOp::DoSimpleQuery(const char *query)
    {
        auto pQuery = DoQuery(query);
        if (!pQuery)
        {
            return false;
        }
        delete pQuery;
        return true;
    }

    CMySQLQuery *TMySQLTransactOp::DoQuery(const char *query)
    {
        auto pDatabase = m_pCon->GetDatabase();
        if (mysql_query(pDatabase, query))
        {
            V_snprintf(m_szError, sizeof m_szError, "MySQL query error: %s\n", mysql_error(pDatabase));
            return NULL;
        }

        MYSQL_RES *res = NULL;
        if (mysql_field_count(pDatabase))
        {
            res = mysql_store_result(pDatabase);
            if (!res)
            {
                return NULL;
            }
        }
        return new CMySQLQuery(m_pCon, res);
    }

    CMySQLResult::CMySQLResult(MYSQL_RES *res) : m_pRes(res)
    {
        Update();
    }

    void CMySQLResult::Update()
    {
        if (!m_pRes)
        {
            m_ColCount = 0;
            m_RowCount = 0;
        }
        else
        {
            m_ColCount = mysql_num_fields(m_pRes);
            m_RowCount = mysql_num_rows(m_pRes);
        }
    }

    int CMySQLResult::GetRowCount()
    {
        return m_RowCount;
    }

    int CMySQLResult::GetFieldCount()
    {
        return m_ColCount;
    }

    bool CMySQLResult::FieldNameToNum(const char *name, unsigned int *columnId)
    {
        unsigned int total = GetFieldCount();

        for (unsigned int i = 0; i < total; i++)
        {
            if (strcmp(FieldNumToName(i), name) == 0)
            {
                *columnId = i;
                return true;
            }
        }

        return false;
    }

    const char *CMySQLResult::FieldNumToName(unsigned int colId)
    {
        if (colId >= GetFieldCount())
        {
            return NULL;
        }

        MYSQL_FIELD *field = mysql_fetch_field_direct(m_pRes, colId);
        return field ? (field->name ? field->name : "") : "";
    }

    bool CMySQLResult::MoreRows()
    {
        return m_CurRow < m_RowCount;
    }

    IToolkitMySQLRow *CMySQLResult::FetchRow()
    {
        if (m_CurRow >= m_RowCount)
        {
            /* Put us one after so we know to block CurrentRow() */
            m_CurRow = m_RowCount + 1;
            return NULL;
        }
        m_Row = mysql_fetch_row(m_pRes);
        m_Lengths = mysql_fetch_lengths(m_pRes);
        m_CurRow++;
        return this;
    }

    IToolkitMySQLRow *CMySQLResult::CurrentRow()
    {
        if (!m_pRes || !m_CurRow || m_CurRow > m_RowCount)
        {
            return NULL;
        }

        return this;
    }

    bool CMySQLResult::Rewind()
    {
        mysql_data_seek(m_pRes, 0);
        m_CurRow = 0;
        return true;
    }

    int CMySQLResult::GetFieldType(unsigned int field)
    {
        if (field >= m_ColCount)
        {
            return TOOLKIT_MYSQL_TYPE_UNKNOWN;
        }

        MYSQL_FIELD *fld = mysql_fetch_field_direct(m_pRes, field);
        if (!fld)
        {
            return TOOLKIT_MYSQL_TYPE_UNKNOWN;
        }

        return fld->type;
    }

    bool CMySQLResult::IsNull(unsigned int columnId)
    {
        if (columnId >= m_ColCount)
        {
            return true;
        }

        return (m_Row[columnId] == NULL);
    }

    const char *CMySQLResult::GetString(unsigned int columnId, size_t *length)
    {
        if (columnId >= m_ColCount)
        {
            return nullptr;
        }
        else if (m_Row[columnId] == NULL)
        {
            if (length)
            {
                *length = 0;
            }
            return nullptr;
        }

        if (length)
        {
            *length = (size_t)m_Lengths[columnId];
        }

        return m_Row[columnId];
    }

    size_t CMySQLResult::GetDataSize(unsigned int columnId)
    {
        if (columnId >= m_ColCount)
        {
            return 0;
        }

        return (size_t)m_Lengths[columnId];
    }

    float CMySQLResult::GetFloat(unsigned int columnId)
    {
        if (columnId >= m_ColCount)
        {
            return 0.0f;
        }
        else if (m_Row[columnId] == NULL)
        {
            return 0.0f;
        }

        return (float)atof(m_Row[columnId]);
    }

    int64_t CMySQLResult::GetInt64(unsigned int columnId)
    {
        if (columnId >= m_ColCount)
        {
            return 0;
        }
        else if (m_Row[columnId] == NULL)
        {
            return 0;
        }

        return atoll(m_Row[columnId]);
    }

    int CMySQLResult::GetInt(unsigned int columnId)
    {
        if (columnId >= m_ColCount)
        {
            return 0;
        }
        else if (m_Row[columnId] == NULL)
        {
            return 0;
        }

        return atoi(m_Row[columnId]);
    }

    CMySQLQuery::CMySQLQuery(MySQLConnection *db, MYSQL_RES *res) : m_pDatabase(db), m_res(res)
    {
        m_insertId = m_pDatabase->GetInsertID();
        m_affectedRows = m_pDatabase->GetAffectedRows();
    }

    IToolkitMySQLResult *CMySQLQuery::GetResultSet()
    {
        if (m_res.m_pRes == NULL)
        {
            return NULL;
        }

        return &m_res;
    }

    bool CMySQLQuery::FetchMoreResults()
    {
        auto pDatabase = m_pDatabase->GetDatabase();
        if (m_res.m_pRes == NULL)
        {
            return false;
        }
        else if (!mysql_more_results(pDatabase))
        {
            return false;
        }

        mysql_free_result(m_res.m_pRes);
        m_res.m_pRes = NULL;

        if (mysql_next_result(pDatabase) != 0)
        {
            return false;
        }

        m_res.m_pRes = mysql_store_result(pDatabase);
        m_res.Update();

        return (m_res.m_pRes != NULL);
    }

    CMySQLQuery::~CMySQLQuery()
    {
        while (FetchMoreResults())
        {
            /* Spin until all are gone */
        }

        /* Free the last, if any */
        if (m_res.m_pRes != NULL)
        {
            mysql_free_result(m_res.m_pRes);
        }
    }

    unsigned int CMySQLQuery::GetInsertId()
    {
        return m_insertId;
    }

    unsigned int CMySQLQuery::GetAffectedRows()
    {
        return m_affectedRows;
    }

    MySQLConnection::MySQLConnection(const ToolkitMySQLConnectionInfo info)
    {
        this->m_info = info;
    }

    MySQLConnection::~MySQLConnection()
    {
        FP_DEBUG("Destroying MySQL connection {}", m_info.database);
        if (m_thread)
        {
            {
                std::lock_guard<std::mutex> lock(m_Lock);
                m_Terminate = true;
                m_QueueEvent.notify_all();
            }

            m_thread->join();
            m_thread.reset();
            m_Terminate = false;
        }

        while (!m_ThinkQueue.empty())
        {
            ThreadOperation *op = m_ThinkQueue.front();
            m_ThinkQueue.pop();

            op->CancelThinkPart();
            delete op;
        }

        if (m_pDatabase)
        {
            mysql_close(m_pDatabase);
        }
    }

    void MySQLConnection::Connect(ToolkitMySQLConnectCallbackFunc callback)
    {
        TMySQLConnectOp *op = new TMySQLConnectOp(this, callback);

        AddToThreadQueue(op);
    }

    void MySQLConnection::Query(char *query, ToolkitMySQLQueryCallbackFunc callback)
    {
        if (!m_pDatabase)
        {
            FP_WARN("Failed querying a disconnected database ({}).", m_info.host);
            return;
        }

        TMySQLQueryOp *op = new TMySQLQueryOp(this, std::string(query), callback);

        AddToThreadQueue(op);
    }

    void MySQLConnection::Query(const char *query, ToolkitMySQLQueryCallbackFunc callback, ...)
    {
        va_list args;
        va_start(args, callback);

        va_list vaCopy;
        va_copy(vaCopy, args);
        const int iLen = std::vsnprintf(NULL, 0, query, vaCopy);
        va_end(vaCopy);

        std::vector<char> zc(iLen + 1);
        std::vsnprintf(zc.data(), zc.size(), query, args);
        va_end(args);

        if (!m_pDatabase)
        {
            FP_WARN("Failed querying a disconnected database ({}).", m_info.host);
            return;
        }

        TMySQLQueryOp *op = new TMySQLQueryOp(this, std::string(zc.data(), zc.size()), callback);

        AddToThreadQueue(op);
    }

    void MySQLConnection::ExecuteTransaction(ToolkitMySQLTransaction txn, ToolkitMySQLTransactionSuccessCallbackFunc success, ToolkitMySQLTransactionFailureCallbackFunc failure)
    {
        TMySQLTransactOp *op = new TMySQLTransactOp(this, txn, success, failure);
        AddToThreadQueue(op);
    }

    void MySQLConnection::Destroy()
    {
        std::erase(mysqlManager.m_vecMysqlConnections, this);
        delete this;
    }

    void MySQLConnection::RunFrame()
    {
        if (!m_ThinkQueue.size())
        {
            return;
        }

        ThreadOperation *op;
        {
            std::lock_guard<std::mutex> lock(m_ThinkLock);
            op = m_ThinkQueue.front();
            m_ThinkQueue.pop();
        }

        op->RunThinkPart();
        delete op;
    }

    void MySQLConnection::ThreadRun()
    {
        if (mysql_thread_safe())
        {
            mysql_thread_init();
        }

        std::unique_lock<std::mutex> lock(m_Lock);

        while (true)
        {
            if (m_threadQueue.empty())
            {
                if (m_Terminate)
                {
                    return;
                }

                m_QueueEvent.wait(lock);
                continue;
            }

            ThreadOperation *op = m_threadQueue.front();
            m_threadQueue.pop();

            lock.unlock();
            op->RunThreadPart();

            {
                std::lock_guard<std::mutex> think_lock(m_ThinkLock);
                m_ThinkQueue.push(op);
            }

            lock.lock();
        }

        mysql_thread_end();
    }

    void MySQLConnection::AddToThreadQueue(ThreadOperation *threadOperation)
    {
        if (!m_thread)
        {
            m_thread = std::unique_ptr<std::thread>(new std::thread(&MySQLConnection::ThreadRun, this));
        }

        {
            std::lock_guard<std::mutex> lock(m_Lock);
            m_threadQueue.push(threadOperation);
            m_QueueEvent.notify_one();
        }
    }

    unsigned int MySQLConnection::GetInsertID()
    {
        return mysql_insert_id(m_pDatabase);
    }

    unsigned int MySQLConnection::GetAffectedRows()
    {
        return mysql_affected_rows(m_pDatabase);
    }

    std::string MySQLConnection::Escape(const char *string)
    {
        return Escape(const_cast<char *>(string));
    }

    std::string MySQLConnection::Escape(char *string)
    {
        size_t size = strlen(string);
        char *buffer = new char[size * 2 + 1];

        mysql_real_escape_string(m_pDatabase, buffer, string, size);

        std::string out(buffer);
        delete[] buffer;
        return out;
    }

    IToolkitMySQLConnection* MySQLManager::CreateConnection(ToolkitMySQLConnectionInfo info)
    {
        auto connection = new MySQLConnection(info);
        m_vecMysqlConnections.push_back(connection);

        return connection;
    }
}
