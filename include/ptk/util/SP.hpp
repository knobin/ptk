//
//  util/SPointer.hpp
//  pTK
//
//  Created by Robin Gustafsson on 2019-07-10.
//

#ifndef PTK_UTIL_SPOINTER_HPP
#define PTK_UTIL_SPOINTER_HPP

// C++ Headers
#include <algorithm>
#include <atomic>
#include <cassert>

// Assert
#define SP_ASSERT(x) assert(x)

namespace pTK
{
    class SPCount
    {
    public:
        SPCount() noexcept
            : m_count{0}
        {
        }
        
        SPCount(int count) noexcept
            : m_count{count}
        {
        }
        
        void addRef() noexcept
        {
            m_count++;
        }
        
        int release() noexcept
        {
            return --m_count;
        }
        
    private:
        std::atomic<int> m_count;
    };
    
    template<typename T>
    class SP
    {
    public:
        SP() noexcept
            : m_data{nullptr}, m_count{nullptr}
        {
        }
        
        explicit SP(T* data)
        try : m_data{data}, m_count{new SPCount(1)}
        {}
        catch (...)
        {
            delete data;
            throw;
        }
        
        ~SP() noexcept
        {
            if (m_count != nullptr)
            {
                if (m_count->release() == 0)
                {
                    delete m_data;
                    delete m_count;
                }
            }
        }
        
        // Copy
        SP(const SP& rhs) noexcept
            : m_data{rhs.m_data}, m_count{rhs.m_count}
        {
            if (m_count != nullptr)
                m_count->addRef();
        }
        
        SP& operator=(SP rhs) noexcept
        {
            rhs.swap(*this);
            return *this;
        }
        
        SP& operator=(T* data) noexcept
        {
            SP_ASSERT(data != nullptr);
            
            SP tmp(data);
            tmp.swap(*this);
            return *this;
        }
        
        void swap(SP& rhs) noexcept
        {
            std::swap(m_data, rhs.m_data);
            std::swap(m_count, rhs.m_count);
        }
        
        template<typename U>
        SP(const SP<U>& rhs)
            : m_data{rhs.m_data}, m_count{rhs.m_count}
        {
            if (m_count != nullptr)
                m_count->addRef();
        }
        
        void reset() noexcept
        {
            if (m_count != nullptr)
            {
                if (m_count->release() == 0)
                {
                    delete m_data;
                    delete m_count;
                }
                
                m_data = nullptr;
            }
        }
        
        void reset(T* data)
        {
            SP_ASSERT(data != nullptr);
            reset();
            
            m_data = data;
            try
            {
                m_count = new SPCount(1);
            }
            catch (...)
            {
                delete data;
                throw;
            }
        }
        
        T* operator->() const noexcept
        {
            SP_ASSERT(m_data != nullptr);
            return m_data;
        }
        
        T& operator*() const noexcept
        {
            SP_ASSERT(m_data != nullptr);
            return *m_data;
        }
        
        T* get() const noexcept
        {
            return m_data;
        }
        
        explicit operator bool() const noexcept
        {
            return m_data == nullptr;
        }
    private:
        template<typename U>
        friend class SP;
        
        T* m_data;
        SPCount* m_count;
    };
}

#endif // PTK_UTIL_SPOINTER_HPP
