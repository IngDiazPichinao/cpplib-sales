//
//
//

// Payment Object in a Sale
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


class PaymentCard : public Payment
{

public:

    int64_t id              (void) const;
    int64_t transfer_number (void) const;

    explicit PaymentCard(int64_t id, int64_t amount, int64_t doc_id, int64_t transfer_number, int32_t company, int32_t customer, const std::string& type, const std::string& doc_type, const std::string& uuid, bool cash);
            ~PaymentCard() = default;

    // cns::money totalCash         (void) override;
    // cns::money totalCredit       (void) override;
    // cns::money totalCreditBacked (void) override;
    static void insertCard (std::shared_ptr<Connection> conn, std::vector<PaymentCard> PaymentsCard);

private:
    int64_t _id;
    int64_t _transfer_number;
};

    }
}
