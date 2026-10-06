
## Aplicação dos testes

Para implementação das técnicas de teste por contrato, aplicou a feature da Biblioteca padrão de C++: Contract assertions

Em src/fizz_buzz.cpp, onde foi feita a solução do problema Leetcode, são aplicadas asserções de contrato. 

As técnicas previstas em Design by Contracts preveem a definição de pré-condições, pós-condições e invariantes. Mas alertam para como essa separação não garante funcionamento em caso de concorrência. Para isso, utilizou-se do segundo artigo, no qual buscou-se apresentar uma solução para as limitações deixadas pelo primeiro.

Para um programa concorrente, define-se que as pré-condições devem se tornar as condições de espera do programa, portanto:

    
    cv.wait(lck, [this] { return i > n || (i % 3 == 0 && i % 5 != 0); });

Além disso, a invariante foi definida para delimitar a iteração:

    1 <= i <= n + 1

Por fim, como pós-condições, espera-se que i tenha sido incrementado apenas uma vez. Portanto, o bloco de código que realiza esses testes está definido como:

        contract_assert(invariant());           
        contract_assert(i % 3 == 0 && i % 5 != 0);    
		
        printFizz();
        int savedIndex = i;
        i++;
        
        contract_assert(i == savedIndex + 1);
        contract_assert(invariant());

A biblioteca também espera que um método seja definido para chamada caso um contrato seja violado. Em src/contract_handler.cpp:

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

## Casos de teste
    
### Para testar n >= 1

    TEST(FizzBuzzContrato, NMenorQueMinimo)
    {
        EXPECT_DEATH(FizzBuzz(0), "CONTRATO VIOLADO");
    }

### Para testar resultado 
    
    TEST(FizzBuzz, SequenciaCorreta1)
    {
        std::vector<std::string> expected = {"1","2","fizz","4","buzz","fizz","7","8","fizz","buzz","11","fizz","13","14","fizzbuzz"};
        auto st = MethodTest(15);

        ASSERT_EQ(st.size(), expected.size()) << "Stacks results and expected are of unequal length";

        for (int i = 0; i < expected.size(); i++) 
        {
            EXPECT_EQ(expected[i], st[i]) << "Vectors results and expected differ at index " << i;
        }
    }


### Para testar resultado 2

    TEST(FizzBuzz, SequenciaCorreta2)
    {
        std::vector<std::string> expected = {"1","2","fizz","4","buzz","fizz","7","8","fizz","buzz"};
        auto st = MethodTest(10);

        ASSERT_EQ(st.size(), expected.size()) << "Stacks results and expected are of unequal length";

       for (int i = 0; i < expected.size(); i++) 
        {
            EXPECT_EQ(expected[i], st[i]) << "Vectors results and expected differ at index " << i;
        }
    }
	

<img width="1289" height="510" alt="Captura de tela de 2026-10-06 07-49-01" src="https://github.com/user-attachments/assets/5323069a-f9ce-410d-b463-dfe52da3068e" />
