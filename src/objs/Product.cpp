//
//
//
#include "Product.hpp"


namespace cns {
namespace sales {


std::vector<Product> Product::querySelectProducts(std::shared_ptr<Connection> conn,
                                                  ProductType                 type,
                                                  int32_t                     company,
                                                  const std::string&          branch)
{
    std::vector<Product> products;

    Query query{select_products_q};

    switch (type)
    {
        case ProductType::Unknown:
            throw cns::Exception("Must provide a valid product type!");
            break;

        case ProductType::Timber:
        case ProductType::Flour:
            query["type"] << product_type_sql.at(type);
            break;
    }

    query["company"] << company;
    query["branch"] << branch;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        products.emplace_back(get<int64_t>(row["id"]),
                              get<int32_t>(row["ordinal"]),
                              0,
                              get<double>(row["price"]),
                              get<std::string>(row["descriptor"]));
    }

    return products;
}


int64_t Product::idProduct(std::shared_ptr<Connection> conn, const std::string& product)
{
    int64_t id = 0;

    Query query{select_idProduct_q};
    query["descriptor"] << product;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        id = get<int64_t>(row["id"]);
    }

    return id;
}


Product::Product(int64_t            id,
                 int32_t            ordinal,
                 int32_t            stock,
                 double             price,
                 const std::string& descriptor /*, const std::vector<tax_t>& taxes*/)
    : id(id), ordinal(ordinal), stock(stock), price(price), descriptor(descriptor)
{
}


LoadingProducts::LoadingProducts(int64_t            quantity,
                                 int64_t            price,
                                 int64_t            amount_dcto,
                                 int64_t            total_with_dcto,
                                 int64_t            total_without_dcto,
                                 int64_t            product,
                                 int16_t            discount,
                                 const std::string& descriptor)
    : quantity(quantity)
    , price(price)
    , amount_dcto(amount_dcto)
    , total_with_dcto(total_with_dcto)
    , total_without_dcto(total_without_dcto)
    , product(product)
    , discount(discount)
    , descriptor(descriptor)
{
}


}  // sale
}  // cns
