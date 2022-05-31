#include <iostream>
#include <array>
#include <sstream>

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

            array(size_type sz, const value_type& value)
                :   m_capacity(sz),
                    m_end(m_capacity),
                    m_data(new T[m_capacity])
            { std::fill(m_data, m_data+m_capacity, value); }

            array(const array& other)
                : m_capacity{other.m_capacity}
                , m_end{other.m_end}
                , m_data{new value_type[m_capacity]}
            { std::copy(other.m_data, other.m_data+m_end, m_data); }

            ~array(){
                if(m_data != nullptr) delete [] m_data;
                // m_data = ttr
            }

            bool full(void) const{
                return m_end == m_capacity;
            }

            void push_back(const value_type& value ){
                // Verificar se há espaço
                if(full())
                    throw std::length_error{"Array tá cheio!!!"};
                m_data[m_end++] = value;
                
            };

            size_type capacity(void) const{
                return m_capacity;
            }

            std::string to_string(void) const{
                std::ostringstream oss;
                oss << "[ ";
                for(size_type i{0}; i < m_end; ++i)
                    oss << m_data[i] << " ";
                oss << "| ";
                for(size_type i{m_end}; i < m_capacity; ++i)
                    oss << m_data[i] << " ";
                oss << "]";
                return oss.str();
            }

            size_type insert(size_type pos, const value_type& value){
                if(full()){
                    throw std::length_error{"Array is full!!!"};
                }

                if(pos >= m_capacity){
                    throw std::out_of_range{"Location informed is beyond the array's limit."};
                }

                if(pos >= m_end){
                    for(/*empty*/; m_end < pos; ++m_end){
                        m_data[m_end] = value_type{};
                    }
                }
                else{
                    std::copy_backward(m_data+pos, m_data+m_end, m_data+m_end+1);
                }
                m_data[pos] = value;
                m_end++;

                return pos;
            }

            bool empty(void) const{
                return m_end == 0;
            }

            size_type remove(size_type pos){
                if(pos >= m_end) return pos;
                else{
                    m_data[pos].~T();

                    std::copy(m_data+pos+1, m_data+m_end, m_data+pos);
                    m_end--;
                    return pos;
                }
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
    sc::array<int> B(10);

    try{
        for( int i = {1}; i <= A.capacity()+1; ++i) {
            A.push_back(i);

        }
    }
    catch(const std::length_error& e){
        std::cout << ">>> Capturei o erro!!! \n";
        std::cout << "Msg = " << e.what() << std::endl;
    }

    B.push_back(3);
    B.push_back(4);
    B.push_back(5);

    std::cout << B.to_string();
    std::cout << std::endl;
    B.insert(1, 8);

    // std::cout << A.to_string();
    std::cout << B.to_string();
    std::cout << std::endl;
    B.insert(6, 10);

    std::cout << B.to_string();
    std::cout << std::endl;

    B.remove(2);
    std::cout << B.to_string();
    std::cout << std::endl;

    return 0;
}