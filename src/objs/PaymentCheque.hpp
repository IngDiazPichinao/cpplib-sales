//
//
//
#pragma once

#include <cns/currency.hpp>
#include <cns/pgsql/Connection.hpp>

#include <memory>
#include <string>
#include <vector>

#include "defs.hpp"
#include "Payment.hpp"
#include "../sql/queries.hpp"


namespace cns {
    namespace sales {


class PaymentCheque : public Payment
{
public:
    int64_t id     (void) const;
    int64_t number (void) const;

    int32_t days (void) const;

    std::string bank   (void) const;
    std::string expiry (void) const;

    explicit PaymentCheque(int64_t id, int64_t amount, int64_t doc_id, int64_t number, int32_t company, int32_t customer, int32_t days, const std::string& type, const std::string& doc_type, const std::string& bank, const std::string& expiry, const std::string& uuid, bool cash);
    ~PaymentCheque() = default;

    //bool        rejected (void) const;

    // cns::money totalCash         (void) override;
    // cns::money totalCredit       (void) override;
    // cns::money totalCreditBacked (void) override;

    static void insertCheque (std::shared_ptr<Connection> conn, std::vector<PaymentCheque> PaymentCheque);

private:
    int64_t _id;
    int64_t _number;
    int32_t _days;

    std::string _bank;
    std::string _expiry;

    bool _rejected;
};

    }
}
