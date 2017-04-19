//
// Root Object of a Sale
//
#include "Sale.hpp"


namespace cns {
    namespace sales {


Sale::Sale(std::shared_ptr<Connection> conn)
:
changedItems    ([] (const std::vector<std::shared_ptr<Item>>&)    -> void { }),
changedPayments ([] (const std::vector<std::shared_ptr<Payment>>&) -> void { }),
changedDocType  ([] (DocumentType)                                 -> void { }),
changedCustomer ([] (const Customer&)                              -> void { }),
commitedDocument([] (int64_t)                                      -> void { }),
conn(conn),
id(0)
{
    // default clb's do nothing
    // this->changedItems     = [] (const std::vector<std::shared_ptr<Item>>&)    -> void { };
    // this->changedPayments  = [] (const std::vector<std::shared_ptr<Payment>>&) -> void { };
    // this->changedDocType   = [] (DocumentType)                                 -> void { };
    // this->changedCustomer  = [] (const Customer&)                              -> void { };
    // this->commitedDocument = [] (int64_t)                                      -> void { };
}


void Sale::regChangedItems(std::function<void(const std::vector<std::shared_ptr<Item>>&)> clb)
{
    this->changedItems = clb;
}


void Sale::regChangedPayments(std::function<void(const std::vector<std::shared_ptr<Payment>>&)> clb)
{
    this->changedPayments = clb;
}


void Sale::regChangedDocType(std::function<void(DocumentType)> clb)
{
    this->changedDocType = clb;
}


void Sale::regChangedCustomer(std::function<void(const Customer&)> clb)
{
    this->changedCustomer = clb;
}


void Sale::regCommitedDocument(std::function<void(int64_t)> clb)
{
    this->commitedDocument = clb;
}


void Sale::setDocType(DocumentType type)
{
    this->type = type;

    // TODO verify state, invalidate state, complete state

    this->changedDocType(this->type);
}


void Sale::setCustomer(std::shared_ptr<Customer> customer)
{
    this->customer = customer;

    // TODO verify state, invalidate state, complete state

    this->changedCustomer(*this->customer);
}


void Sale::addItem(std::shared_ptr<Item> item)
{
    this->items.push_back(item);

    // TODO verify state, invalidate state, complete state

    this->changedItems(this->items);
}


void Sale::addPayment(std::shared_ptr<Payment> payment)
{
    this->payments.push_back(payment);

    // TODO verify state, invalidate state, complete state

    this->changedPayments(this->payments);
}


void Sale::delItem(int64_t id)
{
    auto it  = std::begin(this->items);
    auto end = std::end(this->items);

    for (; it != end; ++it)
    {
        if ((*it)->getId() == id)
        {
            this->items.erase(it);
            this->changedItems(this->items);
            return;
        }
    }
}


void Sale::delPayment(size_t index)
{
    auto it  = std::begin(this->payments);
    auto end = std::end(this->payments);
    auto pos = it + static_cast<std::ptrdiff_t>(index);

    if (it <= pos && pos <= end)  // TEST if we have nailed the boundaries correctly
    {
        this->payments.erase(pos);
        this->changedPayments(this->payments);
    }
}


void Sale::commit(void)
{
    this->verify();

    // TODO query, begin, insert, commit, check result, throw if necessary

    this->commitedDocument(this->id);
}


bool Sale::verify(void)
{
    return false;
}


    }  // sale
}  // cns
