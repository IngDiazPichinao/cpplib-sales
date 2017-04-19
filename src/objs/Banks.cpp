//
//
//

#include "Banks.hpp"

namespace cns {
namespace sales {

Banks::Banks(const std::string& iban, const std::string& name, int32_t number)
    : iban(iban), name(name), number(number)
{
}


std::vector<Banks> Banks::querySelectBanks(std::shared_ptr<Connection> conn)
{
    std::vector<Banks> banks;

    Query query{select_bank_q};

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        banks.emplace_back(get<std::string>(row["iban"], ""),
                           get<std::string>(row["name"], ""),
                           get<int32_t>(row["number"], 0));
    }

    return banks;
}

}  // end Sales
}  // end cns