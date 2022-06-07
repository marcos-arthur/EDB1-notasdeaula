#include <iostream>

namespace sc{ //Sequence container
    template <typename T, size_t SIZE=10>
    class stack{
        private:
            T m_data[SIZE]; // !< Area de armazenamento.
            size_t m_top;   // !< Índice do topo da pilha

        public:
            stack() : m_top(0)
            {/*empty*/}
            ~stack() = default;
            stack(const stack&) = default;
            stack& operator=(const stack&) = default;

            // == métodos
            bool push(const T& value){
                if(full())
                    return false;
                m_data[m_top++] = value;
                return true;
            }

            // Atribui em 'value' o conteúdo armazenado no topo da pilha
            /**
             * @param [out] value Valor do top da pilha
             * @return true Se a pilha possui um ou mais elementos
             * @return false 
             */
            bool top(T& value) const{
                if(empty()) return false;

                value = m_data[m_top-1];
                return true;
            }

            bool pop(T& value){
                if(empty()) return false;

                value = m_data[--m_top];
                return true;
            }

            bool empty(void) const
            {return m_top == 0;}

            bool full(void) const
            {return m_top == SIZE;}
    };

    template <typename T, size_t SIZE=10>
    class queue{
        private:
            T m_data[SIZE]; // !< Area de armazenamento.
            int m_f;   // !< Frente da pilha
            int m_r;   // !< Retaguarda da pilha
        private:
            // Caulcula o avanço do índice indicando no argumento
            int advance(int idx)
            { return (idx+1)%SIZE; }
        public:
            queue() : m_f(0), m_r{-1}
            {/*empty*/}
            ~queue() = default;
            queue(const queue&) = default;
            queue& operator=(const queue&) = default;

            // == métodos
            bool empty() const
            {return m_f == -1;}

            bool full() const
            {
                    return (not empty() and advance(m_r) == m_f);
            }

            //Atribui em "value" o elemento da frente da fila se existir (true).
            bool front(T& value) const{
                if(not empty()) return false;

                value = m_data[m_f];
                return true;
            }

            bool enqueue(const T& value){
                if(full()) return false;

                // Caso especial
                if(empty()) 
                    m_f = m_r = 0;
                else 
                    m_r = advance(m_r);
                
                m_data[m_r] = value;
                return true;
            }

            bool dequeue(T& value){
                if(empty()) return false;

                value = m_data[m_f];
                if(m_f == m_r) // Vai ficar vazio!!
                    m_f = m_r = -1;
                else
                    m_f = advance(m_f);
                
                return true;
            }

            size_t size(void) const {
                if(empty()) return 0;
                if(full()) return SIZE;
                if(m_f >= m_r) return (m_f - m_r + 1);
                else return (SIZE + m_f - m_r + 1);
            }               
    };

}


int main(void){
    sc::stack<int> s;

    for(int i{0}; i < 10; ++i){
        if(s.push(i+1))
            std::cout << "Inserido " << i+1 << "\n";
        else
            std::cout << "Inserção falhou " << i+1 << "\n";
    }

    int v{0};
    while(not s.empty()){
        if(s.pop(v))
            std::cout << ">>> Pop = " << v << "\n";
        else
            std::cout << "Ops! pilha vazia" << "\n";
    }

    return 1;
}