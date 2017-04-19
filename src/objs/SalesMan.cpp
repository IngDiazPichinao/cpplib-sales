//
//
//


#include "SalesMan.hpp"


namespace cns {
namespace sales {


std::vector<SalesMan> SalesMan::querySelectSalesMan(std::shared_ptr<Connection> conn)
{
    std::vector<SalesMan> salesman;

    Query query{select_salesman_q};

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        salesman.emplace_back(get<int32_t>(row["rut"]), get<std::string>(row["name"]));
    }

    return salesman;
}


std::string SalesMan::queryGetNameSalesman(std::shared_ptr<Connection> conn, int32_t rut)
{
    std::string salesman = "";

    Query query(select_filter_by_salesman_q);
    query["sal_rut"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        salesman = get<std::string>(row["name"], "");
    }

    return salesman;
}


int32_t SalesMan::check_salesman(std::shared_ptr<Connection> conn, int32_t rut)
{
    int32_t salesman_rut = 0;

    Query query{check_salesman_q};
    query["salesman"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        salesman_rut = get<int32_t>(row["rut"], 0);
    }

    return salesman_rut;
}


SalesMan::SalesMan(int32_t rut, const std::string& name) : rut(rut), name(name)
{
}

}  // sale
}  // cns