#include <iostream>
#include <array>


namespace sc{
    // Modelo de template
    template < typename T >
    class array
    {
        public:
            // Handy alias
            using value_type = T;
            using pointer = T*;
            using const_reference = const T&;
            using reference = T&;
            using size_type = size_t;

        private:
            size_t m_capacity;
            size_t m_end;
            T* m_data;
        public:
            array(size_type sz=0)
                :   m_capacity(sz),
                    m_end(0),
                    m_data(new T[m_capacity])
            {/*empty*/}

            ~array(){
                if(m_data != nullptr) delete [] m_data;
            }

            bool full(void) const{
                return m_end == m_capacity;
            }

            void push_back(const value_type& value ){
                // Verificar se há espaço
                if(full())
                    throw std::length_error{"Array tá cheio!!!"};
                m_data[m_end++];
                
            };

            std::string to_string(void) const{
                std::ostringstream oss;
                oss << "[ ";
            }
        };
        
        // array::array(/* args */)
        // {
        // }
        
        // array::~array()
        // {
        // }
    
}

int main(){
    sc::array<int> A(10);
    A.push_back();

    return 0;
}