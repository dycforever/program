#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits/function_traits.hpp>

template<typename CFuncType, typename ClosureSignature>  
class c_func_wraper : boost::noncopyable  
{
    public:  
        c_func_wraper()
        {
            m_wrapped_func = new boost::function<ClosureSignature>;
        }
        ~c_func_wraper()
        {
            delete m_wrapped_func;
            m_wrapped_func = NULL;
        }
        template<typename T>
            c_func_wraper(const T &bindedfuntor)
            {
                m_wrapped_func = new boost::function<ClosureSignature>;
                *m_wrapped_func = bindedfuntor;
            }
        template<typename T>
            c_func_wraper<CFuncType, ClosureSignature>& operator = (const T &bindedfuntor)
            {
                *m_wrapped_func = bindedfuntor;
                return *this;
            }
        void * c_void_ptr()
        {
            return new boost::function<ClosureSignature>(*m_wrapped_func);
        }
        CFuncType c_func_ptr()
        {
            return (CFuncType)wrapperd_callback;
        }
    private:  
        //
        // because the cast below, so compiler can deduce the return type
        //
        template<typename R>
            static R wrapperd_callback(void* user_data)
            {
                boost::scoped_ptr<boost::function<ClosureSignature>  > wrapped_func(
                        reinterpret_cast<boost::function<ClosureSignature> *>(user_data));
                return (R)(*wrapped_func)();
            }
        template< typename R, typename ARG1>
            static R wrapperd_callback(ARG1 arg1, void* user_data)
            {
                boost::scoped_ptr<boost::function<ClosureSignature>  > wrapped_func(
                        reinterpret_cast<boost::function<ClosureSignature> *>(user_data));
                return (*wrapped_func)(arg1);
            }
    private:  
        boost::function<ClosureSignature> * m_wrapped_func;
};


static void * my_thread_func(int a, int b,  int c)  
{
    std::cout <<  a <<  b <<  c <<  std::endl;
    return NULL;
}

int main(int, char*[])  
{
    c_func_wraper<void *(*) (void *),  void*()> func;
    func = boost::bind(&my_thread_func, 1, 2, 3);
    pthread_t new_thread;
    pthread_create(&new_thread, NULL, func.c_func_ptr(), func.c_void_ptr());
    pthread_join(new_thread, NULL);
    return 0;
}
