#include <array>
#include <algorithm>
#include <assert.h>
#include <stdexcept>

template<typename T, const size_t N>
class basic_string_on_stack {
    static_assert(N != 0, "Cannot invoke container with 0 size");
public:
    basic_string_on_stack() : m_len(0) {}
    basic_string_on_stack(size_t count, T chars) : m_len(count){
        DO_BOUNDS_CHECK();
        std::fill(this->begin(), this->begin() + count, chars);
    }
    basic_string_on_stack(const T* ch, size_t count) : m_len(count){
        DO_BOUNDS_CHECK();
        std::copy(ch, ch + count, m_container.data());
    }
    explicit basic_string_on_stack(const T* ch) : basic_string_on_stack(ch, get_string_length(ch)) {}
    template<typename U, const size_t paramCapacity>
    basic_string_on_stack(const basic_string_on_stack<U, paramCapacity> &param) : m_len(param.m_len){
        static_assert(paramCapacity <= N, "trying to initialize string with a larger size than allocated");
        std::fill(param.begin(), param.end(), m_container.data());
    }
    basic_string_on_stack(basic_string_on_stack<T, N> &&param) : m_len(param.m_len){
        m_container = move(param.m_container);
    }
    basic_string_on_stack<T, N> substr(size_t idx, size_t count) const {
        if (idx + count >= m_len){
            throw std::out_of_range();
        }
        return basic_string_on_stack<T, N> {begin() + idx, count};
    }
    
    constexpr size_t capacity() const noexcept { return N; }
    constexpr size_t size() const noexcept { return m_len; }
    constexpr size_t length() const noexcept { return m_len; }
    const T* begin() const noexcept { return m_container.begin(); }
    const T* end() const noexcept { return m_container.data() + m_len; }
    const T* data() const noexcept { return m_container.data(); }
    
    // operators
    template <typename U, const size_t paramCapacity>
    bool operator<(const basic_string_on_stack<U, paramCapacity> &rhs) const{
        bool greater = m_len > rhs.m_len;
        for(size_t idx = 0; !greater && idx < rhs.m_len && idx < m_len; ++idx){
            greater = m_container[idx] < rhs.m_container[idx];
        }
        return (!greater);
    }
    template<T, const size_t paramCapacity>
    basic_string_on_stack<T,N>& operator=(const basic_string_on_stack<T, paramCapacity> &param){
        static_assert(paramCapacity <= N, "cannot copy the bigger string into a smaller string");
        m_len = param.m_len;
        DO_BOUNDS_CHECK();
        std::copy(param.begin(), param.end(), m_container.data());
        return *this;
    }
    basic_string_on_stack<T,N>& operator=(const T* ch){
        auto length = get_string_length(ch);
        m_len = length;
        DO_BOUNDS_CHECK();
        std::copy(ch, ch + length, m_container.data());
        return *this;
    }
    basic_string_on_stack<T,N>& operator=(basic_string_on_stack<T, N> &&param) noexcept {
        m_len = param.m_len;
        m_container = move(param.m_container);
        return *this;
    }
    
    template<T, const size_t paramCapacity>
    bool operator==(const basic_string_on_stack<T, paramCapacity> &param) const{
        return !(*this < param) && !(param < *this);
    }
    template<T, const size_t paramCapacity>
    bool operator>(const basic_string_on_stack<T, paramCapacity> &param) const{
        return !(*this < param) && !(*this == param);
    }
    operator const T*() { return m_container.data(); }
private:
    constexpr void DO_BOUNDS_CHECK() const{
        assert(m_len <= N);
    }
    constexpr size_t get_string_length(const T* ch){
        auto startIdx = ch;
        while(*(++ch));
        return (ch - startIdx);
    }
    std::array<T, N> m_container;
    size_t m_len = 0;
};
template<const size_t capacity>
using stack_string = basic_string_on_stack<char, capacity>;
