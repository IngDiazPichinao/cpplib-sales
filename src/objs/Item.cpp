//
// Item object in a Sale (source)
//
#include "Item.hpp"


namespace cns {
    namespace sales {


Item::Item(const Product& product)
: prod(product)
{ }

int64_t Item::total_items (int64_t value, int32_t quantity)
{
    cns::money total {value};
    total *= quantity;

    return static_cast<int64_t>(total);
}


int64_t Item::amountLessDcto (int64_t value, float dcto)
{
    cns::money total {value};
    total -= std::lround((dcto / 100) * value);

    return static_cast<int64_t>(total);
}


int64_t Item::discounted (int64_t total, int64_t amountLessDcto)
{
    cns::money discounted {total};
    discounted -= amountLessDcto;

    return static_cast<int64_t>(discounted);
}


int16_t Item::percentaje (float value)
{
    float percentaje = value * 100.0;

    return static_cast<int16_t>(percentaje);
}


float_t Item::parse_percentaje (int16_t value) { return static_cast<float_t>(value / 100.0) ; }


void Item::setQuantity (int32_t quantity) { Quantity = quantity; }
void Item::setDiscount (int8_t discount)
{
    if (! (0 <= discount) && (discount <= 100))
    {
        throw cns::Exception("Percentage must be within 0 and 100!");
    }
    this->discount = discount;
}

int64_t     Item::getId         (void) const { return this->prod.id;         }
int32_t     Item::getOrdinal    (void) const { return this->prod.ordinal;    }
double      Item::getPrice      (void) const { return this->prod.price;      }
int32_t     Item::getStock      (void) const { return this->prod.stock;      }
std::string Item::getDescriptor (void) const { return this->prod.descriptor; }
// std::vector<tax_t> Item::getTaxes      (void) const { return this->; }


cns::money Item::getDiscount (void) { return static_cast<cns::money>(this->getPrice()) * this->Quantity * (this->discount / 100); }
cns::money Item::getNet      (void) { return static_cast<cns::money>(this->getPrice()) * this->Quantity - this->getDiscount();    }
cns::money Item::getVat      (void) { return this->getNet() * 0.19;                                                                }


void Item::insert (std::shared_ptr<Connection> conn, int32_t company, int64_t doc_id, const std::string& doc_type, std::vector<LoadingProducts> items)

{
    Query query {insert_items_q};

    for (auto& data : items)
    {
        query["company"]     << company;
        query["doc_id"]      << doc_id;
        query["doc_type"]    << doc_type;
        query["product"]     << data.product;
        query["quantity"]    << data.quantity;
        query["price"]       << data.price;
        query["discount"]    << data.discount;
        query["amount_dcto"] << data.amount_dcto;
        query["total"]       << data.total_with_dcto;

        std::shared_ptr<Result> result = conn->execute(query);
        result->fetchall();
    }
}

// std::vector<tax_t> Item::taxes (void);  // std::vector<tax_t<"IHA", 19%, 16800$>, ...>


// void Item::commit (std::shared_ptr<Connection> conn);


    }  // sales
}  // cns
