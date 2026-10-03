#include <contracts>
#include <cstdio>
#include <cstdlib>

void handle_contract_violation(const std::contracts::contract_violation& v)
{
    const auto loc = v.location();
    std::fprintf(stderr,
                 "[CONTRATO VIOLADO] %s:%u em %s\n  condição: %s\n",
                 loc.file_name(),
                 static_cast<unsigned>(loc.line()),
                 loc.function_name(),
                 v.comment());

    std::abort();
}
