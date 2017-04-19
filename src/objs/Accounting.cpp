//
//
//

#include "Accounting.hpp"

namespace cns {
namespace sales {


Closure::Closure(int64_t docID, int32_t company, const std::string& branch, const std::string& docType, bool value)
    : _docID(docID), company(company), branch(branch), docType(docType), value(value)
{
}

Accounting::Accounting(
    int64_t            docID,
    int64_t            docTotal,
    const std::string& created,
    const std::string& docType,
    const std::string& payType,
    bool               unAccounted)
    : _docID(docID)
    , _docTotal(docTotal)
    , _created(created)
    , _docType(docType)
    , _payType(payType)
    , _unAccounted(unAccounted)
{
}

std::vector<Accounting> Accounting::Unaccounted(
    std::shared_ptr<Connection> conn, int32_t rut, const std::string& from, const std::string& expiry)
{
    std::vector<Accounting> accounting;

    Query query{select_docs_unaccounted};

    query["company"] << rut;
    query["dateinit"] << from;
    query["datefinish"] << expiry;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        const std::string& pay_type           = get<std::string>(row["pay_type"]);
        std::string        translate_pay_type = "";

        if (pay_type == Payment::PaymentType_sqlCash())
            translate_pay_type = Payment::PaymentType_nameCash();

        if (pay_type == Payment::PaymentType_sqlCheque())
            translate_pay_type = Payment::PaymentType_nameCheque();

        if (pay_type == Payment::PaymentType_sqlCard())
            translate_pay_type = Payment::PaymentType_nameCard();

        accounting.emplace_back(
            get<int64_t>(row["doc_id"], 0),
            get<int64_t>(row["doc_total"], 0),
            get<std::string>(row["created"], ""),
            get<std::string>(row["doc_type"], ""),
            translate_pay_type,
            get<bool>(row["unacconunted"], false));
    }

    return accounting;
}

void Accounting::UpdateAccounting(std::shared_ptr<Connection> conn, std::vector<Closure> closure)
{
    Query query{update_docs_accounted};

    for (auto& data : closure)
    {
        query["value"] << data.value;
        query["company"] << data.company;
        query["branch"] << data.branch;
        query["doc_id"] << data.doc_id;
        query["doc_type"] << data.doc_type;

        std::shared_ptr<Result> result = conn->execute(query);
        std::vector<Row>        rows   = result->fetchall();
    }
}

}  // edn sales
}  // end cns