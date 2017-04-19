//
// Root Object of a Sale
//
#pragma once

#include "Item.hpp"
#include "Customer.hpp"
#include "Payment.hpp"

#include "defs.hpp"

#include <cns/except.hpp>

#include <vector>
#include <functional>

namespace cns {
    namespace sales {


class Sale
{
public:
// ctor and dtors
     Sale(std::shared_ptr<Connection> conn);
    ~Sale() = default;

// signaling
    // modification triggers
    void regChangedItems    (std::function<void(const std::vector<std::shared_ptr<Item>>&    /*items*/)>    clb);
    void regChangedPayments (std::function<void(const std::vector<std::shared_ptr<Payment>>& /*payments*/)> clb);
    void regChangedDocType  (std::function<void(DocumentType    /*type*/)>                                  clb);
    void regChangedCustomer (std::function<void(const Customer& /*customer*/)>                              clb);

    // other
    void regCommitedDocument (std::function<void(int64_t /*id*/)> clb);  // Finished and persisted document, passes ID of created doc

// queries
    std::vector<std::shared_ptr<Customer>> queryCustomers (void); // TODO duplicate code?
    std::vector<std::shared_ptr<Product>>  queryProducts  (void); // TODO duplicate code?


// setters/modifiers/commiters
    void setDocType  (DocumentType type);
    void setCustomer (std::shared_ptr<Customer> customer);

    void addItem    (std::shared_ptr<Item>    item);     // constructed from Product&
    void addPayment (std::shared_ptr<Payment> payment);

    void delItem    (int64_t id);
    void delPayment (size_t index);

    void commit (void);

// factories
    // XMLNode generateXml(void);  // TODO  (libcns-sii, libcns-xml)
    // Pdf     generatePdf(void);  // TODO  (libcns-sii)

private:
// signaling
    std::function<void(const std::vector<std::shared_ptr<Item>>&)>    changedItems;
    std::function<void(const std::vector<std::shared_ptr<Payment>>&)> changedPayments;
    std::function<void(DocumentType)>                                 changedDocType;
    std::function<void(const Customer&)>                              changedCustomer;
    std::function<void(int64_t)>                                      commitedDocument;

// operational state
    std::shared_ptr<Connection> conn;

// object state
    int64_t      id   = 0;                      // Document ID
    DocumentType type = DocumentType::Unknown;  // Document Type

    std::vector<std::shared_ptr<Item>>    items;
    std::vector<std::shared_ptr<Payment>> payments;

    std::shared_ptr<Customer> customer {nullptr};

// validation and verification
    bool verify (void);  // returns wether state is fit for commit or not
};


    }  // sale
}  // cns
