//
//
//

#include "Debts.hpp"


namespace cns {
    namespace sales {

Debts::Debts (int64_t doc_id, int64_t amount_paid, int64_t doc_total, int64_t remaining, int32_t company, int32_t customer, int32_t salesman, const std::string& created, const std::string& branch, const std::string& doc_type, const std::string& trade_name, const std::string& address)
:
_doc_id(doc_id),
_amount_paid(amount_paid),
_doc_total(doc_total),
_remaining(remaining),
_company(company),
_customer(customer),
_salesman(salesman),
_created(created),
_branch(branch),
_doc_type(doc_type),
_trade_name(trade_name),
_address(address)
{ }


std::vector<Debts> Debts::queryFilterDebtsByCustomer(std::shared_ptr<Connection> conn, int32_t rut)
{
    std::vector<Debts> debts;

    Query query{select_filter_debts_by_customer_q};

    query["customer"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        std::string address = get<std::string>(row["customer_address"]) + ", " + get<std::string>(row["city"]);

        debts.emplace_back(
            get<int64_t>(row["doc_id"],       0),
            get<int64_t>(row["pay_amount"],   0),
            get<int64_t>(row["doc_total"],    0),
            get<int64_t>(row["remaining"],    0),
            get<int32_t>(row["doc_company"],  0),
            get<int32_t>(row["doc_customer"], 0),
            get<int32_t>(row["salesman"],     0),
            get<std::string>(row["doc_created"], ""),
            get<std::string>(row["doc_branch"],  ""),
            get<std::string>(row["doc_type"],   ""),
            get<std::string>(row["trade_name"], ""),
            address
        );
    }

    return debts;
}


std::vector<Debts> Debts::queryFilterDebtsBySalesMan(std::shared_ptr<Connection> conn, int32_t rut)
{
    std::vector<Debts> debts;

    Query query {select_filter_debts_by_salesman_q};

    query["salesman"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        std::string address = get<std::string>(row["customer_address"]) + ", " + get<std::string>(row["city"]);

        debts.emplace_back(
            get<int64_t>(row["doc_id"],       0),
            get<int64_t>(row["pay_amount"],   0),
            get<int64_t>(row["doc_total"],    0),
            get<int64_t>(row["remaining"],    0),
            get<int32_t>(row["doc_company"],  0),
            get<int32_t>(row["doc_customer"], 0),
            get<int32_t>(row["salesman"],     0),
            get<std::string>(row["doc_created"], ""),
            get<std::string>(row["doc_branch"],  ""),
            get<std::string>(row["doc_type"],   ""),
            get<std::string>(row["trade_name"], ""),
            address
        );
    }

    return debts;
}


std::vector<Debts> Debts::queryFilterDebtsByCustomerDate(std::shared_ptr<Connection> conn, int32_t rut, std::string date)
{
    std::vector<Debts> debts;

    Query query {select_filter_debts_by_customer_date_q};

    query["customer"] << rut;
    query["date"]     << date;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        std::string address = get<std::string>(row["customer_address"]) + ", " + get<std::string>(row["city"]);

        debts.emplace_back(
            get<int64_t>(row["doc_id"],       0),
            get<int64_t>(row["pay_amount"],   0),
            get<int64_t>(row["doc_total"],    0),
            get<int64_t>(row["remaining"],    0),
            get<int32_t>(row["doc_company"],  0),
            get<int32_t>(row["doc_customer"], 0),
            get<int32_t>(row["salesman"],     0),
            get<std::string>(row["doc_created"], ""),
            get<std::string>(row["doc_branch"],  ""),
            get<std::string>(row["doc_type"],   ""),
            get<std::string>(row["trade_name"], ""),
            address
        );
    }

    return debts;
}
    }
}