
//
//
//

#include "Branch.hpp"


namespace cns {
namespace sales {


Branch::Branch()
{
}

std::vector<std::string> Branch::queryBranchNameByRut(std::shared_ptr<Connection> conn, int32_t rut)
{
    std::vector<std::string> branch;

    Query query{select_filter_branch_by_rut_q};
    query["company"] << rut;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        branch.push_back(get<std::string>(row["nameBranches"]));
    }

    return branch;
}


int32_t Branch::company(std::shared_ptr<Connection> conn, int32_t company)
{
    int32_t company_rut = 0;

    Query query{select_company_q};
    query["company"] << company;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        company_rut = get<int32_t>(row["rut"], 0);
    }

    return company_rut;
}


std::string Branch::branch(std::shared_ptr<Connection> conn, int32_t company, const std::string& branch)
{
    std::string company_branch = "";

    Query query{select_branch_q};
    query["company"] << company;
    query["branch"] << branch;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        company_branch = get<std::string>(row["branch"], "");
    }

    return company_branch;
}


std::string Branch::name(std::shared_ptr<Connection> conn, int32_t company, const std::string& identifier)
{
    std::string company_name = "";

    Query query{check_company_name_q};
    query["company_rut"] << company;
    query["company_identifier"] << identifier;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        company_name = get<std::string>(row["identifier"], "");
    }

    return company_name;
}


std::string Branch::address(
    std::shared_ptr<Connection> conn, int32_t company, const std::string& branch, const std::string& address)
{
    std::string company_address = "";

    Query query{check_company_address_q};
    query["company_rut"] << company;
    query["company_branch"] << branch;
    query["company_address"] << address;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        company_address = get<std::string>(row["address"], "");
    }

    return company_address;
}

}  // end Sale
}  // end cns