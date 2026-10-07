
## Introdução aos testes

Para implementação das técnicas de teste por contrato, aplicou a feature da Biblioteca padrão de C++: Contract assertions

Em src/fizz_buzz.cpp, onde foi feita a solução do problema Leetcode, são aplicadas asserções de contrato, bem como gerenciamento de threads para código concorrente.

As técnicas previstas em Design by Contracts preveem a definição de pré-condições, pós-condições e invariantes. Mas alertam para como essa separação não garante funcionamento em caso de concorrência. Para isso, utilizou-se do segundo artigo (Contracts for Concurrency), no qual buscou-se apresentar uma solução para as limitações deixadas pelo primeiro. 

Para um programa concorrente, define-se que as pré-condições devem se tornar as condições de espera do programa, portanto:

   	bool ehFizz(int i) const { return i % 3 == 0 && i % 5 != 0; }
    bool ehBuzz(int i) const { return i % 3 != 0 && i % 5 == 0; }
    bool ehFizzBuzz(int i) const { return i % 3 == 0 && i % 5 == 0; }
    bool ehNumber(int i) const { return i % 3 != 0 && i % 5 != 0; }
	
    cv.wait(lck, [this] { return i > n || (ehFizz(i)); });

Além disso, a invariante foi definida para delimitar a iteração, de forma que 1 <= i <= n, como previsto no método invariant():
	    
	bool invariant() const { 
		return 1 <= i && i <= n+1 
			&& results.size() == static_cast<std::size_t>(i - 1);
    }

Para os cabeçalhos, define-se a pré-condição de que o n de input deve estar dentro do intervalo especificado na descrição do problema no Leetcode. Além disso, como pós-condição, o método done() informa se i > n, que é o caso de retorno das threads.
Essa condição, de que i > n, sinaliza que a iteração foi finaliza e cada um dos métodos retorna. 
	
	void fizz(std::function<void()> printFizz)
        pre(1 <= n && n <= 50)
        post(done());

		...
		
    bool done() const 
    {
        std::lock_guard<std::mutex> lck(mtx);
        return i > n;
    }

Por meio de asserções internas do método buscou-se realizar verificações internas de funcionamento. Primeiro, ao sair da espera, verifica-se se a condição de espera foi de fato satisfeita para que a espera tenha chegado ao fim. 

		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [this] { return i > n || (ehFizz(i)); });
		if(i > n) return;

        contract_assert(ehFizz(i));    
		
        printFizz();
        results.push_back("fizz");
        i++;
        
        contract_assert(invariant());

        cv.notify_all();

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

## Aplicação das técnicas

### Design by Contract (Meyer, 1992)

| Técnica do artigo | No código |
| --- | --- |
| **Pré-condição como obrigação do cliente** | `pre(1 <= n && n <= 50)` no construtor |
| **Pós-condição como obrigação do fornecedor** | `post(invariant())` no construtor e `post(done())` nos métodos, que garante que a sequência foi completamente consumida |
| **Invariante de classe** | `invariant()`: $1 \le i \le n+1$ e `results.size() == i - 1` |
| **Monitoramento de asserções para depurar** | Os `contract_assert` só falham se houver bug de implementação |
| **Contrato como parte da interface** | `pre` e `post` declarados explicitamente na interface da classe no `.h` |

---

### Contracts for Concurrency

| Ideia do artigo | No código |
| --- | --- |
| **Pré-condição como condição de espera** | Em cv.wait a execução do método é adiada até a condição se tornar verdadeira |
| **Espera no lado do fornecedor** | A thread chamadora bloqueia dentro do próprio objeto |
| **A pré-condição vale na entrada do corpo** | O `contract_assert(ehFizz(i))` confirma que a sincronização funcionou corretamente |
| **Atomicidade** | O `std::unique_lock` cobre a espera, a ação executada e o incremento `i++`, o que garante a atomicidade sem brecha de acesso a outras threads. |

---

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
