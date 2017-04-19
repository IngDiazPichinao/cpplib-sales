//
// Payment Object in a Sale
//
#pragma once

#include <cns/currency.hpp>
#include <cns/except.hpp>
#include <cns/pgsql/Connection.hpp>

#include <memory>
#include <string>
#include <vector>

#include "../sql/queries.hpp"
#include "defs.hpp"


namespace cns {
namespace sales {


class PaymentsData
{
public:
    const int64_t _amount;
    const int64_t _number_cheque;
    const int64_t _account;
    const int64_t _number_transfer;

    const int32_t _daysExpiry;

    const std::string _type;
    const std::string _bank;
    const std::string _finish;

    PaymentsData(int64_t            amount,
                 int64_t            number_cheque,
                 int64_t            account,
                 int64_t            number_transfer,
                 int32_t            daysExpiry,
                 const std::string& type,
                 const std::string& bank,
                 const std::string& finish);
    ~PaymentsData() = default;

    static int64_t totalPayment(std::vector<PaymentsData> data);
    static int64_t change(int64_t total, int64_t amount);
};


class Totals
{
public:
    const int64_t subTotal;
    const int64_t discountMoney;
    const int64_t net;
    const int64_t amount_iva;
    const int64_t total;
    const float   percentajeDiscount;
    const float   iva;

    Totals(int64_t subTotal,
           int64_t discountMoney,
           int64_t net,
           int64_t amount_iva,
           int64_t total,
           float   percentajeDiscount,
           float   iva);
    ~Totals() = default;

    static int64_t totalPayment(int64_t net, float iva);
    static int64_t valueAdded(int64_t net, float iva);
    static int64_t amountGeneralDcto(int64_t subtotal, float dcto);
    static int64_t netGeneralDcto(int64_t subtotal, int64_t amount);
};


class Payment
{
public:
    ~Payment() = default;

    static std::map<PaymentType, std::string> sql_type;

    int64_t amount(void) const;

    int32_t company(void) const;
    int32_t customer(void) const;

    std::string type(void) const;

    bool cash(void) const;

    cns::money totalCash(void);
    cns::money totalCredit(void);
    cns::money totalCreditBacked(void);

    static int32_t PaymentType_codeCash(void);
    static int32_t PaymentType_codeCheque(void);
    static int32_t PaymentType_codeCard(void);

    static const std::string PaymentType_nameCash(void);
    static const std::string PaymentType_nameCheque(void);
    static const std::string PaymentType_nameCard(void);
    static const std::string PaymentType_sqlCash(void);
    static const std::string PaymentType_sqlCheque(void);
    static const std::string PaymentType_sqlCard(void);

    static std::string selectLastUuid(std::shared_ptr<Connection> conn);

    static sales::PaymentType Payments_code(int32_t type);

    static void insertTransactions(std::shared_ptr<Connection> conn, const std::string& dateFinish);
    static void insertCash(std::shared_ptr<Connection> conn, std::vector<Payment> Payments);

    // protected:
    int64_t _amount;
    int64_t _doc_id;

    int32_t _company;
    int32_t _customer;

    const std::string _type;
    const std::string _doc_type;
    const std::string _uuid;

    bool _cash;

    explicit Payment(int64_t            amount,
                     int64_t            doc_id,
                     int32_t            company,
                     int32_t            customer,
                     const std::string& type,
                     const std::string& doc_type,
                     const std::string& uuid,
                     bool               cash);
};

}  // sale
}  // cns
