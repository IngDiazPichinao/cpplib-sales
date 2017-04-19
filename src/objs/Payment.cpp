//
//
//
#include "Payment.hpp"


namespace cns {
namespace sales {


PaymentsData::PaymentsData(int64_t            amount,
                           int64_t            number_cheque,
                           int64_t            account,
                           int64_t            number_transfer,
                           int32_t            daysExpiry,
                           const std::string& type,
                           const std::string& bank,
                           const std::string& finish)
    : _amount(amount)
    , _number_cheque(number_cheque)
    , _account(account)
    , _number_transfer(number_transfer)
    , _daysExpiry(daysExpiry)
    , _type(type)
    , _bank(bank)
    , _finish(finish)
{
}


int64_t PaymentsData::change(int64_t total, int64_t amount)
{
    int64_t change = 0;

    if (amount > total)
        change = amount - total;

    return change;
}

int64_t PaymentsData::totalPayment(std::vector<PaymentsData> data)
{
    int64_t total = 0;

    for (auto& amount : data)
    {
        total += amount._amount;
    }

    return total;
}


Totals::Totals(int64_t subTotal,
               int64_t discountMoney,
               int64_t net,
               int64_t amount_iva,
               int64_t total,
               float   percentajeDiscount,
               float   iva)
    : subTotal(subTotal)
    , discountMoney(discountMoney)
    , net(net)
    , amount_iva(amount_iva)
    , total(total)
    , percentajeDiscount(percentajeDiscount)
    , iva(iva)
{
}


int64_t Totals::totalPayment(int64_t net, float iva)
{
    cns::money total;
    total = net * (1 + iva / 100);
    return static_cast<int64_t>(total);
}


int64_t Totals::valueAdded(int64_t net, float iva)
{
    cns::money value;
    value = (iva / 100) * net;
    return static_cast<int64_t>(value);
}


int64_t Totals::amountGeneralDcto(int64_t subtotal, float dcto)
{
    cns::money amount{(dcto * subtotal)};
    amount /= 100;
    return static_cast<int64_t>(amount);
}


int64_t Totals::netGeneralDcto(int64_t subtotal, int64_t amount)
{
    return subtotal - amount;
}


Payment::Payment(int64_t            amount,
                 int64_t            doc_id,
                 int32_t            company,
                 int32_t            customer,
                 const std::string& type,
                 const std::string& doc_type,
                 const std::string& uuid,
                 bool               cash)
    : _amount(amount)
    , _doc_id(doc_id)
    , _company(company)
    , _customer(customer)
    , _type(type)
    , _doc_type(doc_type)
    , _uuid(uuid)
    , _cash(cash)
{
}


std::map<PaymentType, std::string> Payment::sql_type{{PaymentType::Cash, "cash"},
                                                     {PaymentType::Cheque, "cheque"},
                                                     {PaymentType::Card, "card"}};


// int64_t Payment::id     (void) const { return this->_id;       }
int64_t Payment::amount(void) const
{
    return this->_amount;
}

int32_t Payment::company(void) const
{
    return this->_company;
}

int32_t Payment::customer(void) const
{
    return this->_customer;
}

int32_t Payment::PaymentType_codeCash(void)
{
    return static_cast<int32_t>(sales::PaymentType::Cash);
}

int32_t Payment::PaymentType_codeCheque(void)
{
    return static_cast<int32_t>(sales::PaymentType::Cheque);
}

int32_t Payment::PaymentType_codeCard(void)
{
    return static_cast<int32_t>(sales::PaymentType::Card);
}

std::string Payment::type(void) const
{
    return this->_type;
}

bool Payment::cash(void) const
{
    return this->_cash;
}


sales::PaymentType Payment::Payments_code(int32_t type)
{
    switch (type)
    {
        case 1:
            return sales::PaymentType::Cash;
            break;

        case 2:
            return sales::PaymentType::Cheque;
            break;

        case 3:
            return sales::PaymentType::Card;
            break;

        default:
            throw cns::Exception("Unsupported type: <" + std::to_string(static_cast<int8_t>(type))
                                 + ">");
            break;
    }
}


const std::string Payment::PaymentType_nameCash(void)
{
    return sales::TranslatePaymentType[sales::PaymentType::Cash];
}

const std::string Payment::PaymentType_nameCheque(void)
{
    return sales::TranslatePaymentType[sales::PaymentType::Cheque];
}

const std::string Payment::PaymentType_nameCard(void)
{
    return sales::TranslatePaymentType[sales::PaymentType::Card];
}

const std::string Payment::PaymentType_sqlCash(void)
{
    return sql_type[sales::PaymentType::Cash];
}

const std::string Payment::PaymentType_sqlCheque(void)
{
    return sql_type[sales::PaymentType::Cheque];
}

const std::string Payment::PaymentType_sqlCard(void)
{
    return sql_type[sales::PaymentType::Card];
}

std::string Payment::selectLastUuid(std::shared_ptr<Connection> conn)
{
    std::string uuid;

    Query query{select_last_transactions_q};

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        uuid = get<std::string>(row["id"], "");
    }

    return uuid;
}


void Payment::insertCash(std::shared_ptr<Connection> conn, std::vector<Payment> Payments)
{
    Query query{insert_payment_q};

    for (auto& data : Payments)
    {
        query["pay_company"] << data._company;
        query["pay_customer"] << data._customer;
        query["pay_type"] << data._type;
        query["pay_cash"] << data._cash;
        query["pay_amount"] << data._amount;
        query["pay_uuid"] << data._uuid;
        query["company"] << data._company;
        query["pd_pay_company"] << data._company;
        query["pd_pay_customer"] << data._customer;
        query["pd_doc_company"] << data._company;
        query["pd_doc_id"] << data._doc_id;
        query["pd_doc_type"] << data._doc_type;
        query["pd_amount"] << data._amount;
        query["pd_uuid"] << data._uuid;

        std::shared_ptr<Result> result = conn->execute(query);
        result->fetchall();
    }
}


void Payment::insertTransactions(std::shared_ptr<Connection> conn, const std::string& dateFinish)
{
    Query query{insert_transactions_q};
    query["closed"] << dateFinish;

    std::shared_ptr<Result> result = conn->execute(query);
    result->fetchall();
}

}  // end sales
}  // end cns
