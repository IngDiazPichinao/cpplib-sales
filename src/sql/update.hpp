//
//
//

#pragma once

namespace cns {
namespace sales {

static const std::string update_docs_accounted{
    R"(
        UPDATE sales.documents
           SET flag_accounted =:value
        WHERE company =:company
          AND branch =:branch
          AND doc_id =:doc_id
          AND doc_type =:doc_type
    ;)"};
}
}