//
//
//
#include "Customer.hpp"


namespace cns {
    namespace sales {

Customer::Customer(int64_t credit_used, int64_t credit_backed, int32_t rut, const std::string& trade_name, const std::string& region, const std::string& address, const std::string& comune, const std::string& city, const std::string& fono, const std::string& movil, const std::string& email, const std::string& commercial_business)
:
_credit_used(credit_used),
_credit_backed(credit_backed),
_rut(rut),
_trade_name(trade_name),
_region(region),
_address(address),
_comune(comune),
_city(city),
_fono(fono),
_movil(movil),
_email(email),
_commercial_business(commercial_business)
{ }


std::vector<Customer> Customer::querySelectCustomers(std::shared_ptr<Connection> conn)
{
    std::vector<Customer> customers;

    Query query {select_customers_q};

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        customers.emplace_back(
            0,
            0,
            get<int32_t>(row["rut"]),
            get<std::string>(row["name"]),
            get<std::string>(row["region"]),
            "",
            get<std::string>(row["comune"]),
            get<std::string>(row["city"]),
            "",
            "",
            "",
            get<std::string>(row["activity"])
        );
    }

    return customers;
}


std::vector<Customer> Customer::readCustomerInformation (std::shared_ptr<Connection> conn, int32_t rut)
{
    std::vector<Customer> info;

    Query query {select_CustomerInformation_q};
    query["cust_rut"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        info.emplace_back(
            0,
            0,
            0,
            get<std::string>(row["name"], ""),
            "",
            get<std::string>(row["address"], ""),
            get<std::string>(row["comune"], ""),
            get<std::string>(row["city"], ""),
            "",
            "",
            "",
            get<std::string>(row["activity"], "")
        );
    }

    return info;
}


std::vector<Customer> Customer::dataCustomer (std::shared_ptr<Connection> conn, int32_t rut)
{
    std::vector<Customer> dataCustomer;

    Query query {select_Info_Customer_q};
    query["rut"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        dataCustomer.emplace_back(
            get<int64_t>(row["customer_credit_used"],     0),
            get<int64_t>(row["customer_credit_backed"],   0),
            get<int32_t>(row["customer_rut"],             0), //
            get<std::string>(row["customer_trade_name"], ""), //
            "",
            get<std::string>(row["customer_address"],             ""),//
            get<std::string>(row["customer_commune"],             ""),//
            get<std::string>(row["customer_city"],                ""),//
            get<std::string>(row["customer_fono"],                ""),//
            get<std::string>(row["customer_movil"],               ""),//
            get<std::string>(row["customer_email"],               ""),//
            get<std::string>(row["customer_commercial_business"], "") //
        );
    }

    return dataCustomer;
}

    }  // sale
}  // cns
